/*
* ========== Copyright Header Begin ==========================================
*
* Hypervisor Software File: mau.h
* 
* Copyright (c) 2006 Sun Microsystems, Inc. All Rights Reserved.
* 
*  - Do no alter or remove copyright notices
* 
*  - Redistribution and use of this software in source and binary forms, with 
*    or without modification, are permitted provided that the following 
*    conditions are met: 
* 
*  - Redistribution of source code must retain the above copyright notice, 
*    this list of conditions and the following disclaimer.
* 
*  - Redistribution in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution. 
* 
*    Neither the name of Sun Microsystems, Inc. or the names of contributors 
* may be used to endorse or promote products derived from this software 
* without specific prior written permission. 
* 
*     This software is provided "AS IS," without a warranty of any kind. 
* ALL EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, 
* INCLUDING ANY IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE OR NON-INFRINGEMENT, ARE HEREBY EXCLUDED. SUN 
* MICROSYSTEMS, INC. ("SUN") AND ITS LICENSORS SHALL NOT BE LIABLE FOR 
* ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR 
* DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES. IN NO EVENT WILL SUN 
* OR ITS LICENSORS BE LIABLE FOR ANY LOST REVENUE, PROFIT OR DATA, OR 
* FOR DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR PUNITIVE 
* DAMAGES, HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, 
* ARISING OUT OF THE USE OF OR INABILITY TO USE THIS SOFTWARE, EVEN IF 
* SUN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* 
* You acknowledge that this software is not designed, licensed or
* intended for use in the design, construction, operation or maintenance of
* any nuclear facility. 
* 
* ========== Copyright Header End ============================================
*/
/*
 * Copyright 2007 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _PLATFORM_MAU_H
#define	_PLATFORM_MAU_H

#pragma ident	"@(#)mau.h	1.3	07/07/27 SMI"

/*
 * Niagara2 MAU definitions
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <resource.h>
#include <config.h>
#include <rng.h>


/*
 * MA Control Register
 *	Field	Bits	R/W
 *	-----	----	---
 *	HWE	22	RO
 *	INVOP	21	RO
 *	STRAND	20:18	R/W
 *	INTR	17	R/W
 *	BUSY	16	RO
 *	OP	12:8	R/W
 *	LENGTH	7:0	R/W
 */
#define	MA_CTL_HWE_SHIFT	22
#define	MA_CTL_HWE_MASK		0x1
#define	MA_CTL_INVOP_SHIFT	21
#define	MA_CTL_INVOP_MASK	0x1
#define	MA_CTL_STRAND_SHIFT	18
#define	MA_CTL_BUSY_SHIFT	16
#define	MA_CTL_INTR_SHIFT	17
#define	MA_CTL_INTR_MASK	0x1
#define	MA_CTL_OP_SHIFT		8
#define	MA_CTL_OP_MASK		0x1f
#define	MA_CTL_LENGTH_MASK	0xff


#ifdef _ASM

/* BEGIN CSTYLED */

/* Range check and real to phys conversion macro */
#define	REAL_TO_PHYS(raddr, size, paddr, fail_label, gstruct, scr2)	\
	GUEST_STRUCT(gstruct)						;\
	RA2PA_RANGE_CHECK(gstruct, raddr, size, fail_label, scr2)	;\
	RA2PA_CONV(gstruct, raddr, paddr, scr2)

#define	REAL_TO_PHYS_G(raddr, size, paddr, fail_label, gstruct, scr2)	\
	RA2PA_RANGE_CHECK(gstruct, raddr, size, fail_label, scr2)	;\
	RA2PA_CONV(gstruct, raddr, paddr, scr2)

/*
 * MAU_LOAD preps and loads MAU registers.
 * If a Load or Store operation is being performed, then the
 * MA address is translated to a physical address.
 * Leaves an errno result in 'ret' if there is an
 * alignment issue with the MA address.
 *
 * membar #Sync prior to storing Control register
 * is due to NIAGARA_ERRATUM_41.
 */
#define	MAU_LOAD1(mau_struct, nhd, tid, ret, intr, errlbl, chklbl, scr1, scr2, scr3)	\
	.pushlocals					; \
	ldx	[nhd + MR_CTL], scr1			; \
	srlx	scr1, MA_CTL_OP_SHIFT, scr2		; \
	and	scr2, MA_CTL_OP_MASK, scr2		; \
	cmp	scr2, MA_OP_STORE			; \
	bne	%xcc, 2f				; \
	 nop						;\
/* #ifdef	ERRATA_192 */ \
	andn	mau_struct, 7, scr1			; \
	mov	1, scr3					; \
	stx	scr3, [scr1 + MAU_STORE_IN_PROGR]	; \
	ba	0f					; \
	 nop						; \
/* #endif  */\
2:							; \
	cmp	scr2, MA_OP_LOAD			; \
	bne,a	%xcc, 1f				; \
	 ldx	[nhd + MR_MPA], scr1			; \
0:							; \
	and	scr1, MA_CTL_LENGTH_MASK, scr1		; \
	inc	scr1					; \
	sllx	scr1, MA_WORDS2BYTES_SHIFT, scr2	; \
	ldx	[nhd + MR_MPA], scr1			; \
	btst	NCS_PTR_ALIGN - 1, scr1			; \
	bnz,a,pn %xcc, chklbl				; \
	 mov	EINVAL, ret				; \
	REAL_TO_PHYS(scr1, scr2, scr1, errlbl, scr3, ret)       ; \
1:							; \
	mov	ASI_MAU_MPA, scr2			; \
	stxa	scr1, [scr2]ASI_STREAM			; \
	ldx	[nhd + MR_MA], scr1			; \
	mov	ASI_MAU_ADDR, scr2			; \
	stxa	scr1, [scr2]ASI_STREAM			; \
	ldx	[nhd + MR_NP], scr1			; \
	mov	ASI_MAU_NP, scr2			; \
	stxa	scr1, [scr2]ASI_STREAM			; \
/*#ifdef	ERRATA_192 */ \
	andn	mau_struct, 7, scr1			; \
	ldx	[scr1 + MAU_STORE_IN_PROGR], scr3	; \
	sub	scr3, 1, scr3				; \
	brnz,pn	scr3, 3f				; \
	 nop						; \
/*** stop the cwq if it is not stopped ***/ \
	mov	ASI_SPU_CWQ_CSR, scr1			; \
	ldxa	[scr1]ASI_STREAM, scr2			; \
	stxa	%g0, [scr1]ASI_STREAM			;  \
	and	scr2, 1, scr2				; \
	andn	mau_struct, 7, scr1			; \
	stx	scr2, [scr1 + MAU_ENABLE_CWQ]		; \
	mov	ASI_SPU_CWQ_SYNC, scr1			; \
	ldxa	[scr1]ASI_STREAM, %g0			; \
3:							; \
/*#endif */ \
	ldx	[nhd + MR_CTL], scr1			; \
	sll	tid, MA_CTL_STRAND_SHIFT, scr2		; \
	or	scr1, scr2, scr1			; \
	mov	ASI_MAU_CONTROL, scr2			; \
	membar	#Sync					; \
	mov	MA_CTL_INTR_MASK, scr3			; \
	sllx	scr3, MA_CTL_INTR_SHIFT, scr3		; \
	andn	scr1, scr3, scr1			; \
	mov	intr, scr3				; \
	and	scr3, MA_CTL_INTR_MASK, scr3		; \
	sllx	scr3, MA_CTL_INTR_SHIFT, scr3		; \
	or	scr1, scr3, scr1			; \
	stxa	scr1, [scr2]ASI_STREAM			; \
	.poplocals

#define	MAU_LOAD(nhd, tid, ret, intr, errlbl, chklbl, scr1, scr2, scr3)	\
	.pushlocals					; \
	ldx	[nhd + MR_CTL], scr1			; \
	srlx	scr1, MA_CTL_OP_SHIFT, scr2		; \
	and	scr2, MA_CTL_OP_MASK, scr2		; \
	cmp	scr2, MA_OP_LOAD			; \
	be	%xcc, 0f				; \
	cmp	scr2, MA_OP_STORE			; \
	bne,a	%xcc, 1f				; \
	  ldx	[nhd + MR_MPA], scr1			; \
0:							; \
	and	scr1, MA_CTL_LENGTH_MASK, scr1		; \
	inc	scr1					; \
	sllx	scr1, MA_WORDS2BYTES_SHIFT, scr2	; \
	ldx	[nhd + MR_MPA], scr1			; \
	btst	NCS_PTR_ALIGN - 1, scr1			; \
	bnz,a,pn %xcc, chklbl				; \
	  mov	EINVAL, ret				; \
	REAL_TO_PHYS(scr1, scr2, scr1, errlbl, scr3, ret)       ; \
1:							; \
	mov	ASI_MAU_MPA, scr2			; \
	stxa	scr1, [scr2]ASI_STREAM			; \
	ldx	[nhd + MR_MA], scr1			; \
	mov	ASI_MAU_ADDR, scr2			; \
	stxa	scr1, [scr2]ASI_STREAM			; \
	ldx	[nhd + MR_NP], scr1			; \
	mov	ASI_MAU_NP, scr2			; \
	stxa	scr1, [scr2]ASI_STREAM			; \
	ldx	[nhd + MR_CTL], scr1			; \
	sll	tid, MA_CTL_STRAND_SHIFT, scr2		; \
	or	scr1, scr2, scr1			; \
	mov	ASI_MAU_CONTROL, scr2			; \
	membar	#Sync					; \
	mov	MA_CTL_INTR_MASK, scr3			; \
	sllx	scr3, MA_CTL_INTR_SHIFT, scr3		; \
	andn	scr1, scr3, scr1			; \
	mov	intr, scr3				; \
	and	scr3, MA_CTL_INTR_MASK, scr3		; \
	sllx	scr3, MA_CTL_INTR_SHIFT, scr3		; \
	or	scr1, scr3, scr1			; \
	stxa	scr1, [scr2]ASI_STREAM			; \
	.poplocals


/*
 * MAU_CHECK_ERR checks the contents of the Control
 * register following a MAU operation.  The HWE and
 * INVOP bits indicate if the operation was successully
 * performed or not.
 * Leaves an errno result in 'ret'.
 */
#define	MAU_CHECK_ERR(ret, scr1, scr2)			\
	.pushlocals					; \
	mov	ND_ERR_OK, ret				; \
	mov	ASI_MAU_CONTROL, scr1			; \
	ldxa	[scr1]ASI_STREAM, scr1			; \
	srlx	scr1, MA_CTL_HWE_SHIFT, scr2		; \
	btst	MA_CTL_HWE_MASK, scr2			; \
	bnz,a,pn %xcc, 0f				; \
	  or	ret, ND_ERR_HWE, ret			; \
0:							; \
	srlx	scr1, MA_CTL_INVOP_SHIFT, scr2		; \
	btst	MA_CTL_INVOP_MASK, scr2			; \
	bnz,a,pn %xcc, 1f				; \
	  or	ret, ND_ERR_INVOP, ret			; \
1:							; \
	.poplocals

#ifndef	NCS_HANDLE_DEFS
#define	NCS_HANDLE_DEFS

#define	HANDLE_SIGMASK		0xfff
#define	HANDLE_IDMASK		0xfff
#define	HANDLE_IDSHIFT		16
#define	HANDLE2ID(hdl, idx)			\
	srlx	hdl, HANDLE_IDSHIFT, idx	; \
	and	idx, HANDLE_IDMASK, idx
#define	ID2HANDLE(idx, sig, hdl)		\
	and	idx, HANDLE_IDMASK, hdl		; \
	sllx	hdl, HANDLE_IDSHIFT, hdl	; \
	or	hdl, sig, hdl

#endif	/* NCS_HANDLE_DEFS */

#define	MAU_HANDLE_SIG		0x0864
#define	HANDLE_IS_MAU(hdl, scr)			\
	and	hdl, HANDLE_SIGMASK, scr	; \
	cmp	scr, MAU_HANDLE_SIG
/*
 * MAU_HANDLE2ID_VERIFY
 *	Translates and verifies a MAU specific handle
 *	for a valid signature and ID.
 */
#define	MAU_HANDLE2ID_VERIFY(hdl, lbl, id)	\
	HANDLE_IS_MAU(hdl, id)			; \
	bne,pn	%xcc, lbl			; \
	nop					; \
	HANDLE2ID(hdl, id)			; \
	cmp	id, NMAUS			; \
	bgeu,pn	%xcc, lbl			; \
	nop

#ifdef ERRATA_192
#define	MAU_CLEAR_QSTATE(mau)			\
	stx	%g0, [mau + MAU_STORE_IN_PROGR]		; \
	stx	%g0, [mau + MAU_ENABLE_CWQ]		; \
	stx	%g0, [mau + MAU_QUEUE + MQ_LOCK]	; \
	stx	%g0, [mau + MAU_QUEUE + MQ_BASE_RA]	; \
	stx	%g0, [mau + MAU_QUEUE + MQ_BASE]	; \
	stx	%g0, [mau + MAU_QUEUE + MQ_END]		; \
	stx	%g0, [mau + MAU_QUEUE + MQ_HEAD]	; \
	stx	%g0, [mau + MAU_QUEUE + MQ_HEAD_MARKER]	; \
	stx	%g0, [mau + MAU_QUEUE + MQ_TAIL]	; \
	stx	%g0, [mau + MAU_QUEUE + MQ_NENTRIES]	; \
	st	%g0, [mau + MAU_QUEUE + MQ_BUSY]
#else
#define	MAU_CLEAR_QSTATE(mau)			\
	stx	%g0, [mau + MAU_QUEUE + MQ_LOCK]	; \
	stx	%g0, [mau + MAU_QUEUE + MQ_BASE_RA]	; \
	stx	%g0, [mau + MAU_QUEUE + MQ_BASE]	; \
	stx	%g0, [mau + MAU_QUEUE + MQ_END]		; \
	stx	%g0, [mau + MAU_QUEUE + MQ_HEAD]	; \
	stx	%g0, [mau + MAU_QUEUE + MQ_HEAD_MARKER]	; \
	stx	%g0, [mau + MAU_QUEUE + MQ_TAIL]	; \
	stx	%g0, [mau + MAU_QUEUE + MQ_NENTRIES]	; \
	st	%g0, [mau + MAU_QUEUE + MQ_BUSY]
#endif

#define	GUEST_MID_GETMAU(guest, id, mau)	\
	sllx	id, GUEST_MAUS_SHIFT, mau	; \
	add	mau, GUEST_MAUS, mau		; \
	ldx	[guest + mau], mau

#define	GUEST_MID_SETMAU(guest, id, mau, scr)	\
	sllx	id, GUEST_MAUS_SHIFT, scr	; \
	add	scr, GUEST_MAUS, scr		; \
	stx	mau, [guest + scr]

#define	MAU_LOCK_ENTER(mau, lck, scr1, scr2)	\
	add	mau, MAU_QUEUE, lck		; \
	add	lck, MQ_LOCK, lck		; \
	SPINLOCK_ENTER(lck, scr1, scr2)
#define	MAU_LOCK_EXIT(mau, lck)			\
	add	mau, MAU_QUEUE, lck		; \
	add	lck, MQ_LOCK, lck		; \
	SPINLOCK_EXIT(lck)
#define	MAU_LOCK_EXIT_L(lck)			\
	SPINLOCK_EXIT(lck)

/*
 *	We wait for the MAU to stop by doing a sync-load.
 *	If the MAU is currently busy running a job on behalf
 *	of the current strand (cpu) being stopped then the
 *	sync-load will wait for it to complete.  If the MAU
 *	is busy running a job for a different strand (cpu)
 *	then the sync-load will immediately return.  Since
 *	the job being executed is on behalf of a different
 *	cpu then the immediate return is okay since we only
 *	care about the local cpu being stopped.
 *
 * 	Reading the %halt hyper-privileged register has the
 * 	side-effect of clearing any pending CWQ/MAU interrupts
 */
#define	CRYPTO_STOP(scr1, scr2)				\
	.pushlocals					;\
	rdhpr   %hver, scr1				;\
	srlx    scr1, VER_MASK_MAJOR_SHIFT, scr1	;\
	and     scr1, VER_MASK_MAJOR_MASK, scr1		;\
	cmp     scr1, 1	/* Check for Niagara2 1.x */	;\
	bleu,pt %xcc, 1f				;\
	nop						;\
	read_halt					;\
1:							;\
	/*						;\
	 * Do a synchronous load to wait for 		;\
	 * MAU to idle.					;\
	 */						;\
	mov	ASI_MAU_SYNC, scr2			;\
	ldxa	[scr2]ASI_STREAM, %g0			;\
							;\
	.poplocals


#endif	/* _ASM */

/* END CSTYLED */

#ifdef __cplusplus
}
#endif

#endif /* _PLATFORM_MAU_H */
