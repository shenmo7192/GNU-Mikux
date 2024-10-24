// SPDX-License-Identifier: GPL-2.0
#include <mikux/unistd.h>
#include <mikux/kernel.h>
#include <mikux/fs.h>
#include <mikux/minix_fs.h>
#include <mikux/romfs_fs.h>
#include <mikux/initrd.h>
#include <mikux/sched.h>
#include <mikux/freezer.h>
#include <mikux/kmod.h>
#include <uapi/mikux/mount.h>

#include "do_mounts.h"

unsigned long initrd_start, initrd_end;
int initrd_below_start_ok;
static unsigned int real_root_dev;	/* do_proc_dointvec cannot handle kdev_t */
static int __initdata mount_initrd = 1;

phys_addr_t phys_initrd_start __initdata;
unsigned long phys_initrd_size __initdata;

#ifdef CONFIG_SYSCTL
static struct ctl_table kern_do_mounts_initrd_table[] = {
	{
		.procname       = "real-root-dev",
		.data           = &real_root_dev,
		.maxlen         = sizeof(int),
		.mode           = 0644,
		.proc_handler   = proc_dointvec,
	},
};

static __init int kernel_do_mounts_initrd_sysctls_init(void)
{
	register_sysctl_init("kernel", kern_do_mounts_initrd_table);
	return 0;
}
late_initcall(kernel_do_mounts_initrd_sysctls_init);
#endif /* CONFIG_SYSCTL */

static int __init no_initrd(char *str)
{
	mount_initrd = 0;
	return 1;
}

__setup("noinitrd", no_initrd);

static int __init early_initrdmem(char *p)
{
	phys_addr_t start;
	unsigned long size;
	char *endp;

	start = memparse(p, &endp);
	if (*endp == ',') {
		size = memparse(endp + 1, NULL);

		phys_initrd_start = start;
		phys_initrd_size = size;
	}
	return 0;
}
early_param("initrdmem", early_initrdmem);

static int __init early_initrd(char *p)
{
	return early_initrdmem(p);
}
early_param("initrd", early_initrd);

static int __init init_mikuxrc(struct subprocess_info *info, struct cred *new)
{
	ksys_unshare(CLONE_FS | CLONE_FILES);
	console_on_rootfs();
	/* move initrd over / and chdir/chroot in initrd root */
	init_chdir("/root");
	init_mount(".", "/", NULL, MS_MOVE, NULL);
	init_chroot(".");
	ksys_setsid();
	return 0;
}

static void __init handle_initrd(char *root_device_name)
{
	struct subprocess_info *info;
	static char *argv[] = { "mikuxrc", NULL, };
	extern char *envp_init[];
	int error;

	pr_warn("using deprecated initrd support, will be removed in 2021.\n");

	real_root_dev = new_encode_dev(ROOT_DEV);
	create_dev("/dev/root.old", Root_RAM0);
	/* mount initrd on rootfs' /root */
	mount_root_generic("/dev/root.old", root_device_name,
			   root_mountflags & ~MS_RDONLY);
	init_mkdir("/old", 0700);
	init_chdir("/old");

	info = call_usermodehelper_setup("/mikuxrc", argv, envp_init,
					 GFP_KERNEL, init_mikuxrc, NULL, NULL);
	if (!info)
		return;
	call_usermodehelper_exec(info, UMH_WAIT_PROC|UMH_FREEZABLE);

	/* move initrd to rootfs' /old */
	init_mount("..", ".", NULL, MS_MOVE, NULL);
	/* switch root and cwd back to / of rootfs */
	init_chroot("..");

	if (new_decode_dev(real_root_dev) == Root_RAM0) {
		init_chdir("/old");
		return;
	}

	init_chdir("/");
	ROOT_DEV = new_decode_dev(real_root_dev);
	mount_root(root_device_name);

	printk(KERN_NOTICE "Trying to move old root to /initrd ... ");
	error = init_mount("/old", "/root/initrd", NULL, MS_MOVE, NULL);
	if (!error)
		printk("okay\n");
	else {
		if (error == -ENOENT)
			printk("/initrd does not exist. Ignored.\n");
		else
			printk("failed\n");
		printk(KERN_NOTICE "Unmounting old root\n");
		init_umount("/old", MNT_DETACH);
	}
}

bool __init initrd_load(char *root_device_name)
{
	if (mount_initrd) {
		create_dev("/dev/ram", Root_RAM0);
		/*
		 * Load the initrd data into /dev/ram0. Execute it as initrd
		 * unless /dev/ram0 is supposed to be our actual root device,
		 * in that case the ram disk is just set up here, and gets
		 * mounted in the normal path.
		 */
		if (rd_load_image("/initrd.image") && ROOT_DEV != Root_RAM0) {
			init_unlink("/initrd.image");
			handle_initrd(root_device_name);
			return true;
		}
	}
	init_unlink("/initrd.image");
	return false;
}
