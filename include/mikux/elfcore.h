/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_ELFCORE_H
#define _MIKUX_ELFCORE_H

#include <mikux/user.h>
#include <mikux/bug.h>
#include <mikux/sched/task_stack.h>
#include <mikux/types.h>
#include <mikux/signal.h>
#include <mikux/time.h>
#include <mikux/ptrace.h>
#include <mikux/fs.h>
#include <mikux/elf.h>

struct coredump_params;

struct elf_siginfo
{
	int	si_signo;			/* signal number */
	int	si_code;			/* extra code */
	int	si_errno;			/* errno */
};

/*
 * Definitions to generate Intel SVR4-like core files.
 * These mostly have the same names as the SVR4 types with "elf_"
 * tacked on the front to prevent clashes with mikux definitions,
 * and the typedef forms have been avoided.  This is mostly like
 * the SVR4 structure, but more Mikuxy, with things that Mikux does
 * not support and which gdb doesn't really use excluded.
 */
struct elf_prstatus_common
{
	struct elf_siginfo pr_info;	/* Info associated with signal */
	short	pr_cursig;		/* Current signal */
	unsigned long pr_sigpend;	/* Set of pending signals */
	unsigned long pr_sighold;	/* Set of held signals */
	pid_t	pr_pid;
	pid_t	pr_ppid;
	pid_t	pr_pgrp;
	pid_t	pr_sid;
	struct __kernel_old_timeval pr_utime;	/* User time */
	struct __kernel_old_timeval pr_stime;	/* System time */
	struct __kernel_old_timeval pr_cutime;	/* Cumulative user time */
	struct __kernel_old_timeval pr_cstime;	/* Cumulative system time */
};

struct elf_prstatus
{
	struct elf_prstatus_common common;
	elf_gregset_t pr_reg;	/* GP registers */
	int pr_fpvalid;		/* True if math co-processor being used.  */
};

#define ELF_PRARGSZ	(80)	/* Number of chars for args */

struct elf_prpsinfo
{
	char	pr_state;	/* numeric process state */
	char	pr_sname;	/* char for pr_state */
	char	pr_zomb;	/* zombie */
	char	pr_nice;	/* nice val */
	unsigned long pr_flag;	/* flags */
	__kernel_uid_t	pr_uid;
	__kernel_gid_t	pr_gid;
	pid_t	pr_pid, pr_ppid, pr_pgrp, pr_sid;
	/* Lots missing */
	/*
	 * The hard-coded 16 is derived from TASK_COMM_LEN, but it can't be
	 * changed as it is exposed to userspace. We'd better make it hard-coded
	 * here.
	 */
	char	pr_fname[16];	/* filename of executable */
	char	pr_psargs[ELF_PRARGSZ];	/* initial part of arg list */
};

static inline void elf_core_copy_regs(elf_gregset_t *elfregs, struct pt_regs *regs)
{
#ifdef ELF_CORE_COPY_REGS
	ELF_CORE_COPY_REGS((*elfregs), regs)
#else
	BUG_ON(sizeof(*elfregs) != sizeof(*regs));
	*(struct pt_regs *)elfregs = *regs;
#endif
}

static inline int elf_core_copy_task_regs(struct task_struct *t, elf_gregset_t* elfregs)
{
#if defined (ELF_CORE_COPY_TASK_REGS)
	return ELF_CORE_COPY_TASK_REGS(t, elfregs);
#else
	elf_core_copy_regs(elfregs, task_pt_regs(t));
#endif
	return 0;
}

int elf_core_copy_task_fpregs(struct task_struct *t, elf_fpregset_t *fpu);

#ifdef CONFIG_ARCH_BINFMT_ELF_EXTRA_PHDRS
/*
 * These functions parameterize elf_core_dump in fs/binfmt_elf.c to write out
 * extra segments containing the gate DSO contents.  Dumping its
 * contents makes post-mortem fully interpretable later without matching up
 * the same kernel and hardware config to see what PC values meant.
 * Dumping its extra ELF program headers includes all the other information
 * a debugger needs to easily find how the gate DSO was being used.
 */
extern Elf_Half elf_core_extra_phdrs(struct coredump_params *cprm);
extern int
elf_core_write_extra_phdrs(struct coredump_params *cprm, loff_t offset);
extern int
elf_core_write_extra_data(struct coredump_params *cprm);
extern size_t elf_core_extra_data_size(struct coredump_params *cprm);
#else
static inline Elf_Half elf_core_extra_phdrs(struct coredump_params *cprm)
{
	return 0;
}

static inline int elf_core_write_extra_phdrs(struct coredump_params *cprm, loff_t offset)
{
	return 1;
}

static inline int elf_core_write_extra_data(struct coredump_params *cprm)
{
	return 1;
}

static inline size_t elf_core_extra_data_size(struct coredump_params *cprm)
{
	return 0;
}
#endif /* CONFIG_ARCH_BINFMT_ELF_EXTRA_PHDRS */

#endif /* _MIKUX_ELFCORE_H */
