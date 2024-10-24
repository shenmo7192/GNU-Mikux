/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_BINFMTS_H
#define _MIKUX_BINFMTS_H

#include <mikux/sched.h>
#include <mikux/unistd.h>
#include <asm/exec.h>
#include <uapi/mikux/binfmts.h>

struct filename;
struct coredump_params;

#define CORENAME_MAX_SIZE 128

/*
 * This structure is used to hold the arguments that are used when loading binaries.
 */
struct mikux_binprm {
#ifdef CONFIG_MMU
	struct vm_area_struct *vma;
	unsigned long vma_pages;
	unsigned long argmin; /* rlimit marker for copy_strings() */
#else
# define MAX_ARG_PAGES	32
	struct page *page[MAX_ARG_PAGES];
#endif
	struct mm_struct *mm;
	unsigned long p; /* current top of mem */
	unsigned int
		/* Should an execfd be passed to userspace? */
		have_execfd:1,

		/* Use the creds of a script (see binfmt_misc) */
		execfd_creds:1,
		/*
		 * Set by bprm_creds_for_exec hook to indicate a
		 * privilege-gaining exec has happened. Used to set
		 * AT_SECURE auxv for glibc.
		 */
		secureexec:1,
		/*
		 * Set when errors can no longer be returned to the
		 * original userspace.
		 */
		point_of_no_return:1;
	struct file *executable; /* Executable to pass to the interpreter */
	struct file *interpreter;
	struct file *file;
	struct cred *cred;	/* new credentials */
	int unsafe;		/* how unsafe this exec is (mask of LSM_UNSAFE_*) */
	unsigned int per_clear;	/* bits to clear in current->personality */
	int argc, envc;
	const char *filename;	/* Name of binary as seen by procps */
	const char *interp;	/* Name of the binary really executed. Most
				   of the time same as filename, but could be
				   different for binfmt_{misc,script} */
	const char *fdpath;	/* generated filename for execveat */
	unsigned interp_flags;
	int execfd;		/* File descriptor of the executable */
	unsigned long loader, exec;

	struct rlimit rlim_stack; /* Saved RLIMIT_STACK used during exec. */

	char buf[BINPRM_BUF_SIZE];
} __randomize_layout;

#define BINPRM_FLAGS_ENFORCE_NONDUMP_BIT 0
#define BINPRM_FLAGS_ENFORCE_NONDUMP (1 << BINPRM_FLAGS_ENFORCE_NONDUMP_BIT)

/* filename of the binary will be inaccessible after exec */
#define BINPRM_FLAGS_PATH_INACCESSIBLE_BIT 2
#define BINPRM_FLAGS_PATH_INACCESSIBLE (1 << BINPRM_FLAGS_PATH_INACCESSIBLE_BIT)

/* preserve argv0 for the interpreter  */
#define BINPRM_FLAGS_PRESERVE_ARGV0_BIT 3
#define BINPRM_FLAGS_PRESERVE_ARGV0 (1 << BINPRM_FLAGS_PRESERVE_ARGV0_BIT)

/*
 * This structure defines the functions that are used to load the binary formats that
 * mikux accepts.
 */
struct mikux_binfmt {
	struct list_head lh;
	struct module *module;
	int (*load_binary)(struct mikux_binprm *);
	int (*load_shlib)(struct file *);
#ifdef CONFIG_COREDUMP
	int (*core_dump)(struct coredump_params *cprm);
	unsigned long min_coredump;	/* minimal dump size */
#endif
} __randomize_layout;

#if IS_ENABLED(CONFIG_BINFMT_MISC)
struct binfmt_misc {
	struct list_head entries;
	rwlock_t entries_lock;
	bool enabled;
} __randomize_layout;

extern struct binfmt_misc init_binfmt_misc;
#endif

extern void __register_binfmt(struct mikux_binfmt *fmt, int insert);

/* Registration of default binfmt handlers */
static inline void register_binfmt(struct mikux_binfmt *fmt)
{
	__register_binfmt(fmt, 0);
}
/* Same as above, but adds a new binfmt at the top of the list */
static inline void insert_binfmt(struct mikux_binfmt *fmt)
{
	__register_binfmt(fmt, 1);
}

extern void unregister_binfmt(struct mikux_binfmt *);

extern int __must_check remove_arg_zero(struct mikux_binprm *);
extern int begin_new_exec(struct mikux_binprm * bprm);
extern void setup_new_exec(struct mikux_binprm * bprm);
extern void finalize_exec(struct mikux_binprm *bprm);
extern void would_dump(struct mikux_binprm *, struct file *);

extern int suid_dumpable;

/* Stack area protections */
#define EXSTACK_DEFAULT   0	/* Whatever the arch defaults to */
#define EXSTACK_DISABLE_X 1	/* Disable executable stacks */
#define EXSTACK_ENABLE_X  2	/* Enable executable stacks */

extern int setup_arg_pages(struct mikux_binprm * bprm,
			   unsigned long stack_top,
			   int executable_stack);
extern int transfer_args_to_stack(struct mikux_binprm *bprm,
				  unsigned long *sp_location);
extern int bprm_change_interp(const char *interp, struct mikux_binprm *bprm);
int copy_string_kernel(const char *arg, struct mikux_binprm *bprm);
extern void set_binfmt(struct mikux_binfmt *new);
extern ssize_t read_code(struct file *, unsigned long, loff_t, size_t);

int kernel_execve(const char *filename,
		  const char *const *argv, const char *const *envp);

#endif /* _MIKUX_BINFMTS_H */
