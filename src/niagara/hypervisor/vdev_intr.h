/*
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _VDEV_INTR_H
#define	_VDEV_INTR_H

#pragma ident	"@(#)vdev_intr.h	1.6	05/11/23 SMI"

#ifdef __cplusplus
extern "C" {
#endif

#include <hypervisor.h>
#include <niagara/hprivregs.h>

/* BEGIN CSTYLED */

/*
 *                                                   vino2inst
 *                                                   +--------+
 *     dev2inst                                   0x0|        |
 *    +--------+                                     +--------+
 * 0x0|        |           devinstances              |        |
 *    +--------+       +---------+--------+          +--------+
 *    |        |       |         |        |          |        |
 *    +--------+       +---------+--------+          +--------+
 *    | inst  -+-------> *cookiep| *ops   |    +-----|  inst  |
 *    +--------+       +---------+--------+    |     +--------+
 *    |        |       |         |        |    |     ..........
 *    +--------+       +---------+--------+    |     ..........
 *    ..........       | *cookiep| *ops   <----+     ..........
 *    ..........       +---------+--------+          ..........
 *    ..........       |         |        |          |        |
 *    ..........       +---------+--------+          +--------+
 *    |        |       | *cookiep| *ops   |--+       |        |
 *    +--------+       +---------+--------+  |       +--------+
 *    |        |                             |       |        |
 *    +--------+             devops          |       +--------+
 *    |        |           +----------+<---- +       |        |
 *    +--------+           | dev2vino |              +--------+
 *    |        |           +----------+         0x7ff|        |
 *    +--------+           | getvalid |              +--------+
 *0x1f|        |           +----------+
 *    +--------+           | setvalid |
 *                         +----------+
 *                         | getstate |
 *                         +----------+
 *                         | setstate |
 *                         ............
 *                         ............
 *                         ............
 *                         ............
 *                         +----------+
 *                         |          |
 *                         +----------+
 *                         |          |
 *                         +----------+
 *
 */


#define	NDEVIDS		0x20
#define	DEVIDMASK	(NDEVIDS - 1)
#define	NINOSPERDEV	64
#define	DEVINOMASK	(NINOSPERDEV - 1)
#define	NVINOS		(NINOSPERDEV * NDEVIDS)

#define	DEVCFGPA_MASK	0x1f
#define	DEVCFGPA_SHIFT	6


/*
 * Find the "opsvec" structure for a "vino"
 */
#define	VINO2DEVINST(guest, vino, devinst, faillabel)	\
	cmp	vino, NVINOS				;\
	bgeu,pn	%xcc, faillabel				;\
	sethi	%hi(GUEST_VINO2INST), devinst		;\
	or	devinst, %lo(GUEST_VINO2INST), devinst	;\
	add	guest, devinst, devinst			;\
	ldub	[devinst + vino], devinst		;\
	brz,pn	devinst, faillabel			;\
	nop

/*
 * Get the cookie for a devinst
 *
 * devinst and cookie may be the same register
 */
#define	DEVINST2COOKIE(guest, devinst, cookie, scr, faillabel)	\
	brz,pn	devinst, faillabel			;\
	sllx	devinst, DEVINST_SIZE_SHIFT, cookie	;\
	ldx	[guest + GUEST_ROOT], scr		;\
	ldx	[scr + CONFIG_DEVINSTANCES], scr	;\
	add	scr, cookie, cookie			;\
	ldx	[cookie + DEVINST_COOKIE], cookie
	
/*
* Find the "opsvec" structure for devhandle "handle"
*/
#define	DEVHANDLE2DEVINST(handle, opsvec)	\
	srlx	handle, DEVCFGPA_SHIFT, opsvec	;\
	and	opsvec, DEVIDMASK, opsvec 

#define	DEVINST2INDEX(guest, devinst, index, scr, label)	\
	add	guest, GUEST_DEV2INST, scr	;\
	ldub	[scr + devinst], index		;\
	brz	index, label			;\
	nop

#define	DEVHANDLE2OPSVEC(guest, handle, opsvec, scr, label)	\
	DEVHANDLE2DEVINST(handle, opsvec)	;\
	DEVINST2INDEX(guest, opsvec, opsvec, scr, label)

/*
 * Jump to a opsvec[devop] with a pointer to the "cookie"
 */
#define	JMPL_DEVOP(guest, devinst, devop, cookie, faillabel) \
	sllx	devinst, DEVINST_SIZE_SHIFT, devinst	;\
	ldx	[guest + GUEST_ROOT], cookie		;\
	ldx	[cookie + CONFIG_DEVINSTANCES], cookie	;\
	add	cookie, devinst, cookie			;\
	ldx	[cookie + DEVINST_OPS], devinst		;\
	brz,pn	devinst, faillabel			;\
	ldx	[cookie + DEVINST_COOKIE], cookie	;\
	ldx	[devinst + devop], devinst		;\
	brz,pn	devinst, faillabel			;\
	jmpl	devinst, %g0				;\
	nop

/*
 * Jmp to "devop" for "vino" with pointer to the "cookie"
 */
#define	JMPL_VINO2DEVOP(vino, devop, cookie, scr, label) \
	GUEST_STRUCT(cookie)				;\
	VINO2DEVINST(cookie, vino, scr, label)		;\
	JMPL_DEVOP(cookie, scr, devop, cookie, label)

/*
 * Jmp to "devop" of device "handle" with "cookie"
 */
#define	JMPL_DEVHANDLE2DEVOP(handle, devop, cookie, scr1, scr2, label)	\
	GUEST_STRUCT(cookie)					;\
	DEVHANDLE2OPSVEC(cookie, handle, scr1, scr2, label)	;\
	JMPL_DEVOP(cookie, scr1, devop, cookie, label)
/* END CSTYLED */

/*
 * The virtual interrupt management framework.
 * When a guest binds to a vintr we lookup the virtual->physical
 * mapping and store the physical cpu info in the vintr table.
 */

#define	NUM_VINTRS	64	/* Must be a power of two */
#define	VINTR_INO_MASK	(NUM_VINTRS - 1)


/*
 * The Niagara vector dispatch priorities
 */
#define	VECINTR_CPUINERR 63
#define	VECINTR_XCALL	62
#define	VECINTR_SSIERR	61
#define	VECINTR_DEV	31
#define	VECINTR_FPGA	16
#define	VECINTR_VDEV	15


/* guest and vdevstate may be the same register */
#define	GUEST2VDEVSTATE(guest, vdevstate)		\
	add	guest, GUEST_VDEV_STATE, vdevstate

/* vino and mapreg may be the same register */
#define	VINO2MAPREG(state, vino, mapreg)		\
	and	vino, DEVINOMASK, mapreg		;\
	sllx	mapreg, MAPREG_SHIFT, mapreg		;\
	add	state, mapreg, mapreg			;\
	add	mapreg, VDEV_STATE_MAPREG, mapreg


#ifndef _ASM

struct devinst {
	void		*cookie;
	struct devopsvec *ops;
};

/*
 * Virtual INO to Device Instance
 *
 * This byte array contains the indexes into array of struct devinst
 *
 * It is used to go from vINO => device instance
 */
struct vino2inst {
	uint8_t	vino[NINOSPERDEV][NDEVIDS];
};



/*
 * Virtual Interrupt Mapping Register (vmapreg), one per interrupt
 *
 * The virtual mapping register is split into two 32-bit words.  The
 * first word is modified by the hypervisor asynchronously.  The
 * second word contains state that is modified by the guest.
 *
 * The state field contains a sun4v interrupt state:
 * INTR_IDLE (0), INTR_RECEIVED (1), INTR_DELIVERED (2)
 *
 * The physical cpu number (pcu) is cached in the vmapreg and
 * is a translation of the guest's virtual cpu number.
 * This framework will require changes to support Dynamic
 * Reconfiguration (DR) of processors.
 * pcpu is never returned to a guest; this is for reverse lookup
 *
 * XXX have a flag or a pointer to 7 words to use in addition to data0
 */
struct vdev_mapreg {
	uint8_t		state;
	uint8_t		valid;
	uint16_t	pcpu;
	uint16_t	vcpu;
	uint8_t		ino;
	uint8_t		reserved;
	uint64_t	data0;
	uint64_t	devcookie;
	uint64_t	getstate;
};


/*
 * vdev nexus state structure, one per guest
 */
struct vdev_state {
	uint64_t	handle;
	struct vdev_mapreg mapreg[NUM_VINTRS];
	uint16_t	inomax;		/* Max INO */
	uint16_t	vinobase;	/* First Vino */
};


#endif /* !_ASM */

#ifdef __cplusplus
}
#endif

#endif /* _VINTR_H */
