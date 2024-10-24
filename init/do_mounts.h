/* SPDX-License-Identifier: GPL-2.0 */
#include <mikux/kernel.h>
#include <mikux/blkdev.h>
#include <mikux/init.h>
#include <mikux/syscalls.h>
#include <mikux/unistd.h>
#include <mikux/slab.h>
#include <mikux/mount.h>
#include <mikux/major.h>
#include <mikux/root_dev.h>
#include <mikux/init_syscalls.h>
#include <mikux/task_work.h>
#include <mikux/file.h>

void  mount_root_generic(char *name, char *pretty_name, int flags);
void  mount_root(char *root_device_name);
extern int root_mountflags;

static inline __init int create_dev(char *name, dev_t dev)
{
	init_unlink(name);
	return init_mknod(name, S_IFBLK | 0600, new_encode_dev(dev));
}

#ifdef CONFIG_BLK_DEV_RAM

int __init rd_load_disk(int n);
int __init rd_load_image(char *from);

#else

static inline int rd_load_disk(int n) { return 0; }
static inline int rd_load_image(char *from) { return 0; }

#endif

#ifdef CONFIG_BLK_DEV_INITRD
bool __init initrd_load(char *root_device_name);
#else
static inline bool initrd_load(char *root_device_name)
{
	return false;
	}

#endif

/* Ensure that async file closing finished to prevent spurious errors. */
static inline void init_flush_fput(void)
{
	flush_delayed_fput();
	task_work_run();
}
