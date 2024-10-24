#ifndef __MIKUX_SPINLOCK_TYPES_UP_H
#define __MIKUX_SPINLOCK_TYPES_UP_H

#ifndef __MIKUX_SPINLOCK_TYPES_RAW_H
# error "please don't include this file directly"
#endif

/*
 * include/mikux/spinlock_types_up.h - spinlock type definitions for UP
 *
 * portions Copyright 2005, Red Hat, Inc., Ingo Molnar
 * Released under the General Public License (GPL).
 */

#ifdef CONFIG_DEBUG_SPINLOCK

typedef struct {
	volatile unsigned int slock;
} arch_spinlock_t;

#define __ARCH_SPIN_LOCK_UNLOCKED { 1 }

#else

typedef struct { } arch_spinlock_t;

#define __ARCH_SPIN_LOCK_UNLOCKED { }

#endif

typedef struct {
	/* no debug version on UP */
} arch_rwlock_t;

#define __ARCH_RW_LOCK_UNLOCKED { }

#endif /* __MIKUX_SPINLOCK_TYPES_UP_H */
