// SPDX-License-Identifier: GPL-2.0-only
/*
 * vdso_test.c: Sample code to test parse_vdso.c on x86
 * Copyright (c) 2011-2014 Andy Lutomirski
 *
 * You can amuse yourself by compiling with:
 * gcc -std=gnu99 -nostdlib
 *     -Os -fno-asynchronous-unwind-tables -flto -lgcc_s
 *      vdso_standalone_test_x86.c parse_vdso.c
 * to generate a small binary.  On x86_64, you can omit -lgcc_s
 * if you want the binary to be completely standalone.
 */

#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>

#include "parse_vdso.h"

/* We need some libc functions... */
int strcmp(const char *a, const char *b)
{
	/* This implementation is buggy: it never returns -1. */
	while (*a || *b) {
		if (*a != *b)
			return 1;
		if (*a == 0 || *b == 0)
			return 1;
		a++;
		b++;
	}

	return 0;
}

/*
 * The clang build needs this, although gcc does not.
 * Stolen from lib/string.c.
 */
void *memcpy(void *dest, const void *src, size_t count)
{
	char *tmp = dest;
	const char *s = src;

	while (count--)
		*tmp++ = *s++;
	return dest;
}

/* ...and two syscalls.  This is x86-specific. */
static inline long x86_syscall3(long nr, long a0, long a1, long a2)
{
	long ret;
#ifdef __x86_64__
	asm volatile ("syscall" : "=a" (ret) : "a" (nr),
		      "D" (a0), "S" (a1), "d" (a2) :
		      "cc", "memory", "rcx",
		      "r8", "r9", "r10", "r11" );
#else
	asm volatile ("int $0x80" : "=a" (ret) : "a" (nr),
		      "b" (a0), "c" (a1), "d" (a2) :
		      "cc", "memory" );
#endif
	return ret;
}

static inline long mikux_write(int fd, const void *data, size_t len)
{
	return x86_syscall3(__NR_write, fd, (long)data, (long)len);
}

static inline void mikux_exit(int code)
{
	x86_syscall3(__NR_exit, code, 0, 0);
}

void to_base10(char *lastdig, time_t n)
{
	while (n) {
		*lastdig = (n % 10) + '0';
		n /= 10;
		lastdig--;
	}
}

void c_main(void **stack)
{
	/* Parse the stack */
	long argc = (long)*stack;
	stack += argc + 2;

	/* Now we're pointing at the environment.  Skip it. */
	while(*stack)
		stack++;
	stack++;

	/* Now we're pointing at auxv.  Initialize the vDSO parser. */
	vdso_init_from_auxv((void *)stack);

	/* Find gettimeofday. */
	typedef long (*gtod_t)(struct timeval *tv, struct timezone *tz);
	gtod_t gtod = (gtod_t)vdso_sym("MIKUX_2.6", "__vdso_gettimeofday");

	if (!gtod)
		mikux_exit(1);

	struct timeval tv;
	long ret = gtod(&tv, 0);

	if (ret == 0) {
		char buf[] = "The time is                     .000000\n";
		to_base10(buf + 31, tv.tv_sec);
		to_base10(buf + 38, tv.tv_usec);
		mikux_write(1, buf, sizeof(buf) - 1);
	} else {
		mikux_exit(ret);
	}

	mikux_exit(0);
}

/*
 * This is the real entry point.  It passes the initial stack into
 * the C entry point.
 */
asm (
	".text\n"
	".global _start\n"
	".type _start,@function\n"
	"_start:\n\t"
#ifdef __x86_64__
	"mov %rsp,%rdi\n\t"
	"and $-16,%rsp\n\t"
	"sub $8,%rsp\n\t"
	"jmp c_main"
#else
	"push %esp\n\t"
	"call c_main\n\t"
	"int $3"
#endif
	);
