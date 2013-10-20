/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) Siemens AG, 2013
 *
 * Authors:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#ifndef _JAILHOUSE_ASM_TYPES_H
#define _JAILHOUSE_ASM_TYPES_H

#define NULL				((void *)0)

#define BITS_PER_LONG			32

#ifndef __ASSEMBLY__

typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
typedef unsigned long long u64;

typedef s8 __s8;
typedef u8 __u8;

typedef s16 __s16;
typedef u16 __u16;

typedef s32 __s32;
typedef u32 __u32;

typedef s64 __s64;
typedef u64 __u64;

typedef enum { true=1, false=0 } bool;

struct cpu_set {
	unsigned long max_cpu_id;
	/* Note: The bitmap is supposed to be extended by embedding this
	 * struct into a larger buffer. */
	unsigned long bitmap[1];
};

#endif /* !__ASSEMBLY__ */

#endif /* !_JAILHOUSE_ASM_TYPES_H */
