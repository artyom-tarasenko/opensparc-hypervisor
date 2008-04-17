/*
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _NIAGARA_CPU_ERRS_H
#define	_NIAGARA_CPU_ERRS_H

#pragma ident	"@(#)cpu_errs.h	1.40	05/10/31 SMI"

#ifdef __cplusplus
extern "C" {
#endif

#include "niagara/jbi_regs.h"
#include <niagara/cache.h>


/*
 * CPU2ERPT_STRUCT - get the erpt from a cpu
 *
 * Delay Slot: safe in a delay slot
 */
#define	CPU2ERPT_STRUCT(BUF, cpu, erpt)		\
	add	cpu, BUF, erpt

/*
 * CPU_ERPT_STRUCT - get both the cpu and erpt from scratch
 *
 * Delay Slot: safe in a delay slot
 * Register overlap: if cpu and erpt are the same then only the erpt
 *     is returned
	CPU2ERPT_STRUCT(BUF, cpu, erpt)
 */
#define	CPU_ERPT_STRUCT(BUF, cpu, erpt)		\
	CPU_STRUCT(cpu)				;\
	CPU2ERPT_STRUCT(BUF, cpu, erpt)


#define	CEEN			0x1
#define	NCEEN			0x2

/*
 * Sparc_error_status_reg
 * ---------------------------------------------------------------------
 * | Rsvd | MEU | MEC | PRIV | Rsvd | Rsvd | IMDU | IMTU | DMDU | DMTU |
 * ---------------------------------------------------------------------
 *  63..32  31    30     29     28    27..26  25     24    23      22
 * ---------------------------------------------------------------------
 * | IDC | ITC | DDC | DTC | IRC | IRU | FRC | FRU | LDAU | NCU | DMSU |
 * ---------------------------------------------------------------------
 *   21     20    19    18    17    16    15    14    13     12     11
 * ---------------------
 * | Rsvd | MAU | Rsvd |
 * ---------------------
 *   10      9     8..0
 */
#define	SPARC_ESR_MEU		(1 << 31)
#define	SPARC_ESR_MEC		(1 << 30)
#define	SPARC_ESR_PRIV		(1 << 29)
#define	SPARC_ESR_IMDU		(1 << 25)
#define	SPARC_ESR_IMTU		(1 << 24)
#define	SPARC_ESR_DMDU		(1 << 23)
#define	SPARC_ESR_DMTU		(1 << 22)
#define	SPARC_ESR_IDC		(1 << 21)
#define	SPARC_ESR_ITC		(1 << 20)
#define	SPARC_ESR_DDC		(1 << 19)
#define	SPARC_ESR_DTC		(1 << 18)
#define	SPARC_ESR_IRC		(1 << 17)
#define	SPARC_ESR_IRU		(1 << 16)
#define	SPARC_ESR_FRC		(1 << 15)
#define	SPARC_ESR_FRU		(1 << 14)
#define	SPARC_ESR_LDAU		(1 << 13)
#define	SPARC_ESR_NCU		(1 << 12)
#define	SPARC_ESR_DMSU		(1 << 11)
#define	SPARC_ESR_MAU		(1 << 9)

#define	SPARC_CE_BITS	(SPARC_ESR_MEC | SPARC_ESR_IDC | SPARC_ESR_ITC |\
			 SPARC_ESR_DDC | SPARC_ESR_DTC | SPARC_ESR_IRC |\
			 SPARC_ESR_FRC)

#define	SPARC_UE_BITS	(SPARC_ESR_IMDU | SPARC_ESR_IMTU | SPARC_ESR_DMDU |\
			 SPARC_ESR_DMTU | SPARC_ESR_IRU | SPARC_ESR_FRU |\
			 SPARC_ESR_LDAU | SPARC_ESR_NCU | SPARC_ESR_DMSU |\
			 SPARC_ESR_MAU)
#define	SPARC_UE_MEU_BITS	(SPARC_UE_BITS | SPARC_ESR_MEU)
#define	SPARC_ESR_ERR_BITS	(SPARC_UE_BITS | SPARC_CE_BITS)

/*
 * SPARC Error Address Register Fields
 */
#define	SPARC_EAR_FPREG_MASK	0x3F0
#define	SPARC_EAR_FPREG_SHIFT	4
#define	SPARC_EAR_IREG_MASK	0xFF0
#define	SPARC_EAR_IREG_SHIFT	4
#define	SPARC_EAR_GL_MASK	0xE00
#define	SPARC_EAR_GL_SHIFT	9
#define	SPARC_EAR_REG_MASK	0x1F0
#define	SPARC_EAR_REG_SHIFT	4
#define	SPARC_EAR_CWP_MASK	0xE00
#define	SPARC_EAR_CWP_SHIFT	9

/*
 * Return codes for register file errors
 */
#define	RF_TRANSIENT	0x0
#define	RF_PERSISTENT	0x1
#define	RF_FAILURE	0x2

/*
 * L2 Error Status Register Bit Combinations:
 */
#define	L2_ESR_DRAM_CE_BITS	(L2_ESR_DAC | L2_ESR_DRC | L2_ESR_DSC)
#define	L2_ESR_CE_BITS		(L2_ESR_MEC | L2_ESR_LDAC | L2_ESR_LDWC |\
				 L2_ESR_LDRC | L2_ESR_LDSC | L2_ESR_LTC |\
				 L2_ESR_VEC | L2_ESR_DRAM_CE_BITS)

#define	L2_ESR_DRAM_CLEAR	L2_ESR_DRAM_CE_BITS
#define	L2_ESR_RD_WR		L2_ESR_LDRC
#define	L2_ESR_FLUSH_LINE	L2_ESR_DAC

#define	L2_ESR_DRAM_UE_BITS	(L2_ESR_DAU | L2_ESR_DRU | L2_ESR_DSU)
#define	L2_ESR_UE_BITS		(L2_ESR_LDAU | L2_ESR_LDWU | L2_ESR_LDRU |\
				L2_ESR_LDSU | L2_ESR_LRU | L2_ESR_LVU |\
				L2_ESR_DRAM_UE_BITS)
#define	L2_ESR_DUE_BITS		(L2_ESR_LDAU | L2_ESR_LDWU | L2_ESR_LDRU |\
				L2_ESR_LDSU | L2_ESR_DRAM_UE_BITS)

#define	L2_ESR_ERR_BITS		(L2_ESR_CE_BITS | L2_ESR_UE_BITS)

/* Can only Vector to Error Steer */
#define	L2_ESR_ES_CE_BITS	(L2_ESR_LDWC | L2_ESR_LDRC | L2_ESR_LDSC |\
				L2_ESR_LTC | L2_ESR_DRC | L2_ESR_DSC)
#define	L2_ESR_ES_UE_BITS	(L2_ESR_LDWU | L2_ESR_LDRU | L2_ESR_LDSU |\
				L2_ESR_LRU | L2_ESR_LVU)
/* May Vector to Error Steer, may not */
#define	L2_ESR_MAY_ES_CE_BITS	L2_ESR_DAC
#define	L2_ESR_MAY_ES_UE_BITS	L2_ESR_DAU
/* May Vector to Modular Arithmetic, may not */
#define	L2_ESR_MAY_MA_CE_BITS	(L2_ESR_LDAC | L2_ESR_DAC)
/* Can not Vector to Error Steer */
#define	L2_ESR_NO_ES_CE_BITS	L2_ESR_LDAC
/* Not Vector to Error Steer */
#define	L2_ESR_NONS_CE_BITS	(L2_ESR_MAY_ES_CE_BITS |\
				 L2_ESR_MAY_MA_CE_BITS |\
				 L2_ESR_NO_ES_CE_BITS)

#define	L2_ESR_FATAL_BITS	(L2_ESR_LVU | L2_ESR_LRU)

#define	L2_EAR_DRAM_MASK	0x3F



#define	ERPT_BANK_OFF(erpt, bank, scr1) \
	sllx	bank, BANK_SHIFT, scr1			;\
	inc	CPU_VBSC_ERPT + EVBSC_BANK, scr1	;\
	add	erpt, scr1, scr1

/*
 * Error Descriptor values (ENUM)
 */
#define	EDESC_UNDEF			0x0
#define	EDESC_UE_RESUMABLE		0x1
#define	EDESC_PRECISE_NONRESUMABLE	0x2
#define	EDESC_DEFERRED_NONRESUMABLE	0x3
#define	EDESC_WARN_RESUMABLE		0x4	/* Shutdown Warning */

/*
 * Error Attributes values (Bit position Mask)
 */
#define	EATTR_CPU		(1 << 0)
#define	EATTR_MEM		(1 << 1)
#define	EATTR_PIO		(1 << 2)
#define	EATTR_IRF		(1 << 3)
#define	EATTR_FRF		(1 << 4)
#define	EATTR_SECS		(1 << 5)
#define	ERR_ATTR_MODE_SHIFT	24
#define	ERR_ATTR_MODE(mode)	((mode) << ERR_ATTR_MODE_SHIFT)

/*
 * Error Execution Mode (Bit position Mask)
 */
#define	ERR_MODE_UNKNOWN	0x0
#define	ERR_MODE_USER		0x1
#define	ERR_MODE_PRIV		0x2
#define	ERR_MODE_RSVD		0x3


/*
 * The size of any memory errors is always the same.
 * For N1 the err boundry is L2_LINE_SIZE
 */
#define	ERPT_MEM_SIZE		L2_LINE_SIZE

/* PRIV bit position in TSTATE register - bit 10 */
#define	TSTATE_PSTATE_PRIV	(PSTATE_PRIV << TSTATE_PSTATE_SHIFT)


/*
 * Error handling flag bits
 */
#define	ERR_FLAG_POLLD		(1 << 0)	/* poll daemon */
#define	ERR_FLAG_SPARC		(1 << 3)	/* sparc handler */
#define	ERR_FLAG_L2DRAM		(1 << 4)	/* l2/dram handlers */
#define	ERR_FLAG_L2DRAM_B0	(1 << 4)	/*   bank 0 */
#define	ERR_FLAG_L2DRAM_B1	(2 << 4)	/*   bank 1 */
#define	ERR_FLAG_L2DRAM_B2	(4 << 4)	/*   bank 2 */
#define	ERR_FLAG_L2DRAM_B3	(8 << 4)	/*   bank 3 */

/*
 * These macros are used to manipulate the local bank number
 *   storage during error processing.
 * A non-negative number indicates a valid entry.
 * It is the bank that an error was detected on.
 */
/* BEGIN CSTYLED */
#define	GET_CPU_L2BANK(cpup, scr1) \
	ldsh	[cpup + CPU_L2BANK], scr1

#define	SET_CPU_L2BANK(bank, cpup, scr1) \
	mov	bank, scr1		;\
	sth	scr1, [cpup + CPU_L2BANK]

#define	CLR_CPU_L2BANK(cpup, scr1) \
	mov	-1, scr1			;\
	sth	scr1, [cpup + CPU_L2BANK]

#define	GET_CPU_RPTFLAGS(cpup, reg) \
	lduh	[cpup + CPU_RPTFLAGS], reg

#define	SET_CPU_RPTFLAGS(cpup, flags) \
	sth	flags, [cpup + CPU_RPTFLAGS]
/* END CSTYLED */

#define	ERR_SEND_DIAG		(1<<9)

/*
 * Check all the DRAM status registers for a DBU error and
 *   return the status in the condition codes.
 */
/* BEGIN CSTYLED */
#define	CHECK_DRAM_DBU(scr1, scr2, scr3, scr4)				 \
	set	DRAM_BANK_STEP, scr4					;\
	setx	DRAM_ESR_BASE, scr1, scr3				;\
	ldx	[scr3], scr2						;\
	add	scr3, scr4, scr3					;\
	ldx	[scr3], scr1						;\
	add	scr3, scr4, scr3					;\
	bset	scr1, scr2						;\
	ldx	[scr3], scr1						;\
	add	scr3, scr4, scr3					;\
	bset	scr1, scr2						;\
	ldx	[scr3], scr1						;\
	setx	DRAM_ESR_DBU, scr4, scr3				;\
	bset	scr1, scr2						;\
	btst	scr3, scr2			/* DBU? */
/* END CSTYLED */

/*
 * Create a base diagnostic error report
 */
/* BEGIN CSTYLED */
#define	LOAD_BASIC_ERPT(cpup, erpt, scr1, scr2)				 \
	rdpr	%tl, scr1				/* get %tl */	;\
	sllx	scr1, EHDL_CPUTL_SHIFT, scr2		/* position */	;\
	dec	scr1					/* guest trap */;\
	stub	scr1, [erpt + CPU_VBSC_ERPT + EVBSC_TL]			;\
	ldx	[cpup + ERR_SEQ_NO], scr1		/* seq # */	;\
	add	scr1, 1, scr1				/* +1 = new # */;\
	stx	scr1, [cpup + ERR_SEQ_NO]		/* save */	;\
	sllx	scr1, 64 - EHDL_CPUTL_SHIFT, scr1	/* clear upper */;\
	srlx	scr1, 64 - EHDL_CPUTL_SHIFT, scr1	/*  bits */	;\
	or	scr2, scr1, scr1			/* tl | seq */	;\
	ldub	[cpup + CPU_PID], scr2			/* get CPUID */	;\
	stuh	scr2, [erpt + CPU_VBSC_ERPT + EVBSC_CPUID]		;\
	ldub	[cpup + CPU_VID], scr2			/* guest cpuid */;\
	stuh	scr2, [erpt + CPU_SUN4V_ERPT + ESUN4V_G_CPUID]		;\
	sllx	scr2, EHDL_CPUTL_SHIFT + EHDL_TL_BITS, scr2 /* position */;\
	or	scr2, scr1, scr1			/* cpuid|tl|seq */;\
	stx	scr1, [erpt + CPU_VBSC_ERPT + EVBSC_EHDL]		;\
	stx	scr1, [erpt + CPU_SUN4V_ERPT + ESUN4V_G_EHDL]		;\
	rd	STICK, scr1				/* stick */	;\
	stx	scr1, [erpt + CPU_VBSC_ERPT + EVBSC_STICK]		;\
	stx	scr1, [erpt + CPU_SUN4V_ERPT + ESUN4V_G_STICK]		;\
	set	ERPT_TYPE_CPU, scr1			/* cpu/mem */	;\
	stx	scr1, [erpt + CPU_VBSC_ERPT + EVBSC_REPORT_TYPE]	;\
	rdhpr	%hver, scr1				/* cpu version */;\
	stx	scr1, [erpt + CPU_VBSC_ERPT + EVBSC_CPUVER]		;\
	setx	IOBBASE + PROC_SER_NUM, scr1, scr2 /* ->cpu serial # */	;\
	ldx	[scr2], scr1				/* cpu serial # */;\
	stx	scr1, [erpt + CPU_VBSC_ERPT + EVBSC_CPUSERIAL]		;\
	rdpr	%tstate, scr1				/* tstate */	;\
	stx	scr1, [erpt + CPU_VBSC_ERPT + EVBSC_TSTATE]		;\
	rdhpr	%htstate, scr1				/* htstate */	;\
	stx	scr1, [erpt + CPU_VBSC_ERPT + EVBSC_HTSTATE]		;\
	rdpr	%tpc, scr1				/* tpc */	;\
	stx	scr1, [erpt + CPU_VBSC_ERPT + EVBSC_TPC]		;\
	rdpr	%tt, scr1				/* trap type */	;\
	stuh	scr1, [erpt + CPU_VBSC_ERPT + EVBSC_TT]
/* END CSTYLED */

/*
 * Get and compare the PID to the ERRORSTEER
 */
/* BEGIN CSTYLED */
#define	IS_PID_STEER(cpup, pid, sid)	/* pid & sid are returned */	 \
	setx	L2_CONTROL_REG, pid, sid	/* get the steer cpu */	;\
	ldx	[sid], sid						;\
	srlx	sid, L2_ERRORSTEER_SHIFT, sid				;\
	and	sid, NCPUS - 1, sid					;\
	ldub	[cpup + CPU_PID], pid	/* my pid */			;\
	cmp	pid, sid		/* am I the steer target? */
/* END CSTYLED */

/*
 * Macros to:
 *   - clear status bits in Sparc, L2, DRAM ESR
 *   - set the Real Address into the error report
 *   - set the Memory Line Size into the error report
 */
/* BEGIN CSTYLED */
#define	CLEAR_L2_ESR(BNUM, l2esr, scr1, scr2)				 \
	setx	L2_ESR_BASE + BNUM * L2_BANK_STEP, scr1, scr2		;\
	stx	l2esr, [scr2]
/* END CSTYLED */
/* BEGIN CSTYLED */
#define	CLEAR_DRAM_ESR(BNUM, erpt, scr1, scr2)				 \
	setx	DRAM_ESR_BASE + BNUM * DRAM_BANK_STEP, scr1, scr2	;\
	ldx	[erpt + CPU_EVBSC_DRAM_AFSR(BNUM)], scr1		;\
	stx	scr1, [scr2]	/* clear DRAM ESR */
/* END CSTYLED */

/*
 * Fill the error descriptor and attributes of guest error report
 *	ERPT_OFFSET_VAL - offset of error report in cpu structure
 *	EATTR_VAL - error attribute, eg, MEM, IRF, FRF, etc
 *	EDESC_VAL - error description, eg, resumable, nonresumable.
 */
/* BEGIN CSTYLED */
#define	SET_ERPT_EDESC_EATTR(ERPT_OFFSET_VAL, EATTR_VAL, EDESC_VAL, reg1,\
			reg2, reg3)					 \
	rdpr	%tstate, reg1						;\
	and	reg1, TSTATE_PSTATE_PRIV, reg1				;\
	cmp	%g0, reg1						;\
	move	%xcc, ERR_MODE_USER, reg3	/* priv is 0 */		;\
	movne	%xcc, ERR_MODE_PRIV, reg3	/* priv is 1 */		;\
	sllx	reg3, ERR_ATTR_MODE_SHIFT, reg3				;\
	or	reg3, EATTR_VAL, reg3		/* error attributes */	;\
	mov	EDESC_VAL, reg2			/* error description */	;\
	CPU_STRUCT(reg1)			/* cpu pointer */	;\
	add	reg1, ERPT_OFFSET_VAL, reg1	/* ereport pointer */	;\
	stw	reg2, [reg1 + CPU_SUN4V_ERPT + ESUN4V_EDESC] /* err desc */;\
	stw	reg3, [reg1 + CPU_SUN4V_ERPT + ESUN4V_ATTR]
/* END CSTYLED */

/*
 * Read the afsr to see if the certain error bit is set. If it is, check
 * afar to see if it is the same as saved one in cpu structure. If they
 * are the same, clear afsr and afar since the error was caused by
 * re-read in error handler.
 *      ERPT_OFFSET_VAL - offset of error report in cpu structure
 *      ERR_BIT - error bit we want to check
 */
/* BEGIN CSTYLED */
#define	CLEAR_SPARC_ESR(ERPT_OFFSET_VAL, ERR_BIT, scr1, scr2, scr3, scr4)\
	.pushlocals							;\
	ldxa	[%g0]ASI_SPARC_ERR_STATUS, scr2	/* SPARC afsr */	;\
	set	ERR_BIT, scr3						;\
	btst	scr3, scr2		/* is the bit set in afsr? */	;\
	bz	%xcc, 1f		/* not set, we are done */	;\
	nop								;\
	ldxa	[%g0]ASI_SPARC_ERR_ADDR, scr3	/* SPARC afar */	;\
	CPU_STRUCT(scr1)			/* cpu pointer */	;\
	add	scr1, ERPT_OFFSET_VAL, scr1	/* scr1 - erpt pointer */;\
	ldx	[scr1 + CPU_VBSC_ERPT + EVBSC_SPARC_AFAR], scr4 /* saved afar */;\
	cmp	scr3, scr4		/* are they same? */		;\
	bnz	1f		/* different addr, we are done */	;\
	nop								;\
	stxa	scr2, [%g0]ASI_SPARC_ERR_STATUS	/* clear SPARC afsr */	;\
1:	nop								;\
	.poplocals
/* END CSTYLED */

/*
 * Error Handler Macros
 */
/*
 * There is a little problem for us in polling the L2DRAM errors.
 * The L2 ERRORSTEER and MOD STRAND fields are used to control where the
 * interrupt is delivered, most of the time, for most errors.
 * Therein lies the problem: "most" not "all".
 * It is delivered to ERRORSTEER/STRAND if it is available.
 *
 * For DRAM DAC, DAU, the error will be reported to the initiator depending
 * on whether it is available (12.6.1).
 *
 * For DRAM DAC, the error will be reported to the initiator depending
 * on when the error occured (12.6.2, 12.8.1.1-2).
 *
 * For DRAM DAU, the error will be reported to the initiator depending
 * on when the error occured (12.8.3.1-2)
 *
 * All this means is that we may not have all the variants covered yet!
 */

/*
 * LDAC and DAC are "synchronous" errors, i.e. the CPU that
 * induced the error usually gets the error trap. The CPUID is saved
 * in the L2 ESR.VCID field. We compare the VCID for a match
 * before owning the LDAC or DAC errors. If there is a match,
 * then we handle the LDAC or DAC and skip checking the rest
 * of the banks.
 * For all other errors we handle them as if it is ours and
 * continue to check the other L2 banks for errors.
 */
/*
 * DAC: DRAM Data Correctable ECC Error
 */
/* BEGIN CSTYLED */
#define	DAC_HANDLER(BNUM, cpup, erpt, l2esr, reg1, reg2, reg3)		 \
	PRINT("DAC DIAG\r\n")						;\
	CPU_PUSH(erpt, reg1, reg2, reg3)				;\
	CPU_PUSH(cpup, reg1, reg2, reg3)				;\
	mov	BNUM, %g1						;\
	HVCALL(err_determine_disposition)				;\
	CPU_POP(cpup, reg1, reg2, reg3)					;\
	CPU_POP(erpt, reg1, reg2, reg3)					;\
	/* Clear DAC status bit in DRAM ESR */				;\
	CLEAR_DRAM_ESR(BNUM, erpt, reg1, reg2)
/* END CSTYLED */

/*
 * DRC: DRAM Data Correctable ECC Error on DMA Read/Write Partial
 */
/* BEGIN CSTYLED */
#define	DRC_HANDLER(BNUM, cpup, erpt, reg1, reg2, reg3)			 \
	mov	BNUM, %g1						;\
	HVCALL(err_determine_disposition)				;\
	CPU_ERPT_STRUCT(CPU_CE_RPT, cpup, erpt)	/* restore */		;\
	/* Clear DRC status bit in DRAM ESR */				;\
	CLEAR_DRAM_ESR(BNUM, erpt, reg1, reg2)				;\
	PRINT("DRC DIAG\r\n")
/* END CSTYLED */

/*
 * DSC: DRAM Data Correctable Error for Scrub
 * Hardware corrects the memory.
 */
/* BEGIN CSTYLED */
#define	DSC_HANDLER(BNUM, erpt, reg1, reg2, reg3)			 \
	/* Clear DSC status bit in DRAM ESR */				;\
	CLEAR_DRAM_ESR(BNUM, erpt, reg1, reg2)				;\
	PRINT("DSC DIAG\r\n")
/* END CSTYLED */


/*
 * LDAC and DAC are "synchronous" errors, i.e. the CPU that
 * induced the error usually gets the error trap. The CPUID is saved
 * in the L2 ESR.VCID field. We compare the VCID for a match
 * before owning the LDAC or DAC errors. If there is a match,
 * then we handle the LDAC or DAC and skip checking the rest
 * of the banks.
 * For all other errors we handle them as if it is ours and
 * continue to check the other L2 banks for errors.
 */
/*
 * LDAC: L2$ Data Correctable ECC Error
 * The HW corrected the error but didn't correct the version on the
 * L2. We need to read the address in error and write it back in
 * order to clear the error from the L2
 * we saved the error address before in the cput.  We need to just
 * get it from there
 */
/* BEGIN CSTYLED */
#define	LDAC_HANDLER(BNUM, cpup, erpt, l2esr, reg1, reg2, scr1)		 \
	/* Correct the error source */					;\
	.pushlocals							;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], reg1			;\
	set	N_LONG_IN_LINE, reg2					;\
1:	ldx	[reg1], scr1	/* reread error address */		;\
	stx	scr1, [reg1]	/* writeback h/w corrected data */	;\
	dec	reg2		/* walk the cache line */		;\
	brnz	reg2, 1b						;\
	add	reg1, SIZEOF_UI64, reg1					;\
	/* clear the LDAC bit that was logged when clearing the error */;\
	setx	L2_ESR_BASE + BNUM*L2_BANK_STEP, scr1, reg1		;\
	setx	(L2_ESR_VEC|L2_ESR_MEC|L2_ESR_LDAC), scr1, reg2		;\
	stx	reg2, [reg1]	/* clear LDAC ???? right way?? */	;\
	PRINT("LDAC DIAG\r\n")						;\
	.poplocals
/* END CSTYLED */

/*
 * LDWC: L2 Cache Data Correctable ECC Error for Writeback
 * Hardware corrects the error on the data being written to memory.
 */
/* BEGIN CSTYLED */
#define	LDWC_HANDLER(BNUM, erpt, reg1, reg2, reg3)			\
	PRINT("LDWC DIAG\r\n")
/* END CSTYLED */

/*
 * LTC: L2$ Tag Correctable ECC Error
 * Hardware corrects all the errors in the set.
 * DocErratum #44: L2 Tag Errors Not Always Scrubbed by Hardware
 * In the PRM's < 1.8, is stated that the HW will correct a LTC error.
 * It was later found that the error would only get corrected by HW, if there
 * was a miss on that index.
 * PRM 1.8 and plus should now state that SW needs to cause a miss (not a
 * hit) in that index to cause the HW correction
 *
 * Need to cause a cache miss so the HW scrubber clears the err:
 *	read L2 EAR
 *	extract index
 *	for way 0..11
 *		extract tag at way/index via L2_TAG_DIAG
 *		create address using tag/index
 *		load on new address
 *
 * This approach may cause an extra async trap (if tag at way 0 is a hit)
 * This new trap will have no errors set
 *
 * NOTE: We don't validate the PA.  In not expected circumstances, the lack
 * of check can cause an out_of_bounds error. HW folks don't believe this
 * case to be very likely.
 */
/* BEGIN CSTYLED */
#define	LTC_HANDLER(BNUM, erpt, reg1, reg2, reg3, reg4)			 \
	.pushlocals							;\
	PRINT("LTC DIAG\r\n")						;\
	/*								;\
	 * Need to cause a cache miss (aka. not a hit) so the HW	;\
	 * scrubber clears the err					;\
	 */								;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], reg1			;\
	setx	L2_TAG_DIAG_SELECT << L2_TAG_DIAG_SELECT_SHIFT, reg3, reg4;\
	set	L2_INDEX_MASK, reg3					;\
	and	reg1, reg3, reg1	/* extract index */		;\
	or	reg1, reg4, reg4					;\
	mov	(L2_NUM_WAYS - 1), reg2	/* reg2-> way */		;\
1:									;\
	sllx	reg2, L2_WAY_SHIFT, reg3				;\
	or	reg4, reg3, reg3	/* set addr for L2_TAG_DIAG */	;\
	ldx	[reg3], reg3		/* get tag */			;\
	/* reg3 contains tag */						;\
	/* build the new address (tag/index) */				;\
	srlx	reg3, L2_TAG_SHIFT, reg3	/* clear ecc bits */	;\
	sllx	reg3, L2_PA_TAG_SHIFT, reg3	/* set tag for new addr */;\
	or	reg1, reg3, reg3		/* include index */	;\
	ldx	[reg3], %g0						;\
	deccc	reg2							;\
	bgeu,pt	%xcc, 1b						;\
	nop								;\
	.poplocals

/* END CSTYLED */

/*
 * LDSC: L2$ Data Correctable ECC Error for Scrub
 * Hardware does the correction.
 */
/* BEGIN CSTYLED */
#define	LDSC_HANDLER(BNUM, erpt, reg1, reg2, reg3)			\
	PRINT("LDSC DIAG\r\n")
/* END CSTYLED */

/*
 * MEC: Just the MEC bit is set in L2 ESR.
 * Send a diagnostic error report.
 */
/* BEGIN CSTYLED */
#define	JUST_L2_MEC_HANDLER(BNUM, erpt, reg1, reg2, reg3)		\
	PRINT("JUST_L2_MEC\r\n")
/* END CSTYLED */

/*
 * LDRC: L2$ Data Correctable Error on DMA access.
 * XXX The check for transient or persistent error is not implemented yet.
 * This handler rereads the L2$ data and writes the corrected back.
 * The physical address is stored in the cpu structure.
 */
/* BEGIN CSTYLED */
#define	LDRC_HANDLER(BNUM, erpt, reg1, reg2, reg3)			 \
	/* Correct the error source */					;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], reg1			;\
	ldx	[reg1], reg2	/* reread error address */		;\
	stx	reg2, [reg1]	/* writeback h/w corrected data */	;\
	PRINT("LDRC DIAG\r\n")
/* END CSTYLED */

/*
 * Macro to save the state of the line
 *   cpup or erpt MUST NOT be %g4
 *
 * Since all the registers are clobbered in check_l2_state(), we will just
 *   call them out directly here and avoid the restrictions of having them
 *   correctly declared in the macro.
 * Only the cpup and erpt registers are declared so they can be properly used
 *   and restored.
 */
/* BEGIN CSTYLED */
#define	SAVE_L2_LINE_STATE(BNUM, E_OFF, cpup, erpt)			 \
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], %g1			;\
	/* Input pa is in %g1, get the line state, result is in %g4 */	;\
	HVCALL(check_l2_state)	/* all other regs get garbled */	;\
	PRINT("L2 Line State ")						;\
	PRINTW(%g4)							;\
	PRINT("\r\n")							;\
	CPU_ERPT_STRUCT(E_OFF, cpup, erpt)	/* restore */		;\
	stx	%g4, [cpup + CPU_L2_LINE_STATE]
/* END CSTYLED */

/*
 * Macro to process CE bits logged in the L2 ESR
 */
/* BEGIN CSTYLED */
#define	PROCESS_CE_IN_L2_ESR(BNUM, cpup, erpt, l2esr, reg1, reg2, reg3)	 \
	.pushlocals							;\
	PRINT("PROCESS CE Bank ")					;\
	/*	PRINTB(BNUM)	*/					;\
	PRINT("\r\n")							;\
	add	cpup, CPU_CE_RPT, erpt					;\
	setx	L2_ESR_LDAC, reg3, reg1		/* LDAC */		;\
	btst	reg1, l2esr			/* LDAC? */		;\
	bz,pt	%xcc, 1f			/* no, goto 1 */	;\
	nop								;\
	LDAC_HANDLER(BNUM, cpup, erpt, l2esr, reg1, reg2, reg3)		;\
	ba,a	9f							;\
1:	  setx	L2_ESR_DAC, reg3, reg1		/* DAC */		;\
	btst	reg1, l2esr			/* DAC? */		;\
	bz,pt	%xcc, 2f			/* no, goto 2 */	;\
	nop								;\
	DAC_HANDLER(BNUM, cpup, erpt, l2esr, reg1, reg2, reg3)		;\
	ba,a	9f							;\
2:	  setx	L2_ESR_LDWC, reg3, reg1		/* LDWC */		;\
	btst	reg1, l2esr			/* LDWC? */		;\
	bz,pt	%xcc, 3f			/* no, goto 3 */	;\
	nop								;\
	LDWC_HANDLER(BNUM, erpt, reg1, reg2, reg3)			;\
	ba,a	9f							;\
3:	  setx	L2_ESR_LDRC, reg3, reg1		/* LDRC */		;\
	btst	reg1, l2esr			/* LDRC? */		;\
	bz,pt	%xcc, 4f			/* no, goto 4 */	;\
	nop								;\
	LDRC_HANDLER(BNUM, erpt, reg1, reg2, reg3)			;\
	ba,a	9f							;\
4:	  setx	L2_ESR_LDSC, reg3, reg1		/* LDSC */		;\
	btst	reg1, l2esr			/* LDSC? */		;\
	bz,pt	%xcc, 5f			/* no, goto 5 */	;\
	nop								;\
	LDSC_HANDLER(BNUM, erpt, reg1, reg2, reg3)			;\
	ba,a	9f							;\
5:	  setx	L2_ESR_LTC, reg3, reg1		/* LTC */		;\
	btst	reg1, l2esr			/* LTC? */		;\
	bz,pt	%xcc, 6f			/* no, goto 6 */	;\
	nop								;\
	LTC_HANDLER(BNUM, erpt, reg1, reg2, reg3, l2esr)		;\
	ba,a	9f							;\
6:	  setx	L2_ESR_DRC, reg3, reg1		/* DRC */		;\
	btst	reg1, l2esr			/* DRC? */		;\
	bz,pt	%xcc, 7f			/* no, goto 7 */	;\
	nop								;\
	DRC_HANDLER(BNUM, cpup, erpt, reg1, reg2, reg3)			;\
	ba,a	9f							;\
7:	  setx	L2_ESR_DSC, reg3, reg1		/* DSC */		;\
	btst	reg1, l2esr			/* DSC? */		;\
	bz,pn	%xcc, 8f			/* no, goto 8 */	;\
	nop								;\
	DSC_HANDLER(BNUM, erpt, reg1, reg2, reg3)			;\
	ba,a	9f							;\
8:	  setx	L2_ESR_MEC | L2_ESR_VEC, reg3, reg1 /* MEC VEC */	;\
	btst	reg1, l2esr			/* MEC? */		;\
	bz,a	%xcc, 0f			/* no */		;\
	  mov	-1, l2esr			/* invalid: no err */	;\
	JUST_L2_MEC_HANDLER(BNUM, erpt, reg1, reg2, reg3)		;\
9:	mov	BNUM, l2esr			/* return bank # */	;\
	bset	ERR_SEND_DIAG, l2esr		/* action: send diag */	;\
0:/* WARNING: label is also a target from DAC_HANDLER LDAC_HANDLER macros */;\
	.poplocals
/* END CSTYLED */


/*
 * Check the L2 ESR for the specified bank for UE bits
 * Disrupting errors are captured in CPU.ce_rpt
 */
/* BEGIN CSTYLED */
#define	DIS_UE_CHECK_L2_ESR(BNUM, l2esr, scr2, scr3, scr4)		 \
	CPU_STRUCT(scr2)			/* cpu pointer */	;\
	add	scr2, CPU_CE_RPT, scr2		/* CE error report */	;\
	ldx	[scr2 + CPU_EVBSC_L2_AFSR(BNUM)], l2esr			;\
	/* l2esr has L2 ESR */						;\
	setx	L2_ESR_DUE_BITS | L2_ESR_MEU, scr3, scr4/* DUE bits */	;\
	btst	scr4, l2esr				/* any set? */
/* END CSTYLED */

/*
 * Check the L2 ESR for the specified bank for UE bits
 * This is for precise UEs.
 */
/* BEGIN CSTYLED */
#define	UE_CHECK_L2_ESR(BNUM, l2esr, scr2, scr3, scr4)			 \
	CPU_STRUCT(scr2)			/* cpu pointer */	;\
	add	scr2, CPU_UE_RPT, scr2		/* UE error report */	;\
	ldx	[scr2 + CPU_EVBSC_L2_AFSR(BNUM)], l2esr			;\
	/* l2esr has L2 ESR */						;\
	setx	L2_ESR_UE_BITS | L2_ESR_MEU, scr3, scr4	/* UE bits */	;\
	btst	scr4, l2esr				/* any set? */
/* END CSTYLED */

/*
 * Check Sparc and all the L2 ESR's for UE bits
 */
/* BEGIN CSTYLED */
#define	UE_CHECK(SP_BITS, L2_BITS, esr, scr1, scr2, scr3)		 \
	.pushlocals							;\
	setx	SP_BITS | SPARC_ESR_MEU, scr1, scr2 /* SPARC bits */	;\
	btst	scr2, esr			/* any set? */		;\
	bnz,pn	%xcc, 9f			/*   yes: go process */	;\
	clr	scr3				/* get all bank bits */	;\
	setx	L2_ESR_BASE, scr1, scr2					;\
	ldx	[scr2 + 0*L2_BANK_STEP], scr1				;\
	bset	scr1, scr3						;\
	ldx	[scr2 + 1*L2_BANK_STEP], scr1				;\
	bset	scr1, scr3						;\
	ldx	[scr2 + 2*L2_BANK_STEP], scr1				;\
	bset	scr1, scr3						;\
	ldx	[scr2 + 3*L2_BANK_STEP], scr1				;\
	bset	scr1, scr3			/* & test together */	;\
	setx	L2_BITS | L2_ESR_MEU, scr1, scr2 /* L2/DRAM bits */	;\
	btst	scr2, scr3			/* Any set? */		;\
9:	.poplocals				/* nz = error */
/* END CSTYLED */

/*
 * Check the L2 ESR for the specified bank for CE bits
 * Disrupting errors are captured in CPU.ce_rpt
 *
 * STEER and Steer error bits are checked so the correct cpu handles them.
 */
/* BEGIN CSTYLED */
#define	CHECK_L2_ESR_CE(cpup, l2esr, scr1, scr2)			 \
	.pushlocals							;\
	setx	L2_ESR_CE_BITS, scr1, scr2	/* Correctable bits */	;\
	btst	scr2, l2esr			/* Any set? */		;\
	bz,a,pn	%xcc, 9f			/*   no */		;\
	  nop					/* z == skip */	;\
	IS_PID_STEER(cpup, scr1, scr2)		/* steer target? */	;\
	bz,a,pt	%xcc, 9f			/*   yes: go do it */	;\
	  cmp	%g0, 1				/* nz = process */	;\
	setx	L2_ESR_NONS_CE_BITS, scr1, scr2 /* non-steer bits are */;\
	andcc	scr2, l2esr, scr2		/*  done here */	;\
9:	.poplocals			/* z == skip, nz = process */
/* END CSTYLED */

/* BEGIN CSTYLED */
#define	CE_CHECK_L2_ESR(BNUM, cpup, scr1, scr2, scr3)		 	 \
	.pushlocals							;\
	mov	BNUM, scr2						;\
	BTST_L2_BANK_EEN(scr2, CEEN, scr2, scr3)/* Bank blackout? */	;\
	bz,a	%xcc, 9f			/*   yes: skip */	;\
	  nop					/* z == skip */		;\
	ldx	[cpup + CPU_CE_RPT + CPU_EVBSC_L2_AFSR(BNUM)], scr1	;\
	CHECK_L2_ESR_CE(cpup, scr1, scr2, scr3)	/* scr1 = l2esr */	;\
9:	.poplocals			/* z == skip, nz = process */
/* END CSTYLED */

/*
 * This macro is meant to be fast and result in a simple "yes" "no"
 * It is used for the polling and at the interrupt entry to validate quickly
 *
 * On input esr = sparc esr, it is clobbered.
 * Check the Sparc & L2 ESR's (all banks) for CE bits
 * STEER and Steer error bits are checked so the correct cpu handles them.
 */
/* BEGIN CSTYLED */
#define	CE_CHECK(cpup, esr, scr1, scr2, scr3)			 	 \
	.pushlocals							;\
	lduw	[cpup + CPU_ERR_FLAG], scr3	/* blackout bits */	;\
	btst	ERR_FLAG_SPARC, scr3		/* blackout? */		;\
	bnz,pn	%xcc, 0f			/*   yes: skip */	;\
	set	SPARC_CE_BITS, scr1		/* valid CE bits */	;\
	btst	esr, scr1			/* any set? */		;\
	bnz,pn	%xcc, 9f			/*   yes: go process */	;\
0:	mov	%g0, esr			/* get all bank bits */	;\
	setx	L2_ESR_BASE, scr1, scr2					;\
	BTST_L2_BANK_EEN(%g0, CEEN, scr1, scr3)	/* Bank 0 blackout? */	;\
	bz,pn	%xcc, 1f			/*   yes: skip */	;\
	mov	1, scr1							;\
	ldx	[scr2 + 0*L2_BANK_STEP], scr3				;\
	bset	scr3, esr						;\
1:	BTST_L2_BANK_EEN(scr1, CEEN, scr1, scr3)/* Bank 1 blackout? */	;\
	bz,pn	%xcc, 2f			/*   yes: skip */	;\
	mov	2, scr1							;\
	ldx	[scr2 + 1*L2_BANK_STEP], scr3				;\
	bset	scr3, esr						;\
2:	BTST_L2_BANK_EEN(scr1, CEEN, scr1, scr3)/* Bank 2 blackout? */	;\
	bz,pn	%xcc, 3f			/*   yes: skip */	;\
	mov	3, scr1							;\
	ldx	[scr2 + 2*L2_BANK_STEP], scr3				;\
	bset	scr3, esr						;\
3:	BTST_L2_BANK_EEN(scr1, CEEN, scr1, scr3)/* Bank 3 blackout? */	;\
	bz,a,pn %xcc, 4f			/*   yes: skip */	;\
	  nop								;\
	ldx	[scr2 + 3*L2_BANK_STEP], scr3				;\
	bset	scr3, esr						;\
4:	CHECK_L2_ESR_CE(cpup, esr, scr1, scr2)	/* nz = process */	;\
9:	.poplocals			/* z == skip, nz = process */
/* END CSTYLED */

/*
 * Dump the L2 and DRAM error log registers in the CPU error report
 * area.
 * NOTE: cpup and erpt are input arguments.
 */
/* BEGIN CSTYLED */
#define	DUMP_L2_DRAM_ERROR_LOGS(cpup, erpt, scr3, scr4, scr5, scr6, scr7)\
	/* save the L2 & DRAM ESRs in the diagnostic report area */	;\
	setx	L2_ESR_BASE, scr3, scr4	/* scr4 = L2_ESR_BASE */	;\
	setx	L2_EAR_BASE, scr3, scr5	/* scr4 = L2_EAR_BASE */	;\
	ldx	[scr4], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_L2_AFSR(0)]			;\
	ldx	[scr5], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_L2_AFAR(0)]			;\
	add	scr4, L2_BANK_STEP, scr4		/* next bank */	;\
	add	scr5, L2_BANK_STEP, scr5				;\
	ldx	[scr4], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_L2_AFSR(1)]			;\
	ldx	[scr5], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_L2_AFAR(1)]			;\
	add	scr4, L2_BANK_STEP, scr4		/* next bank */	;\
	add	scr5, L2_BANK_STEP, scr5				;\
	ldx	[scr4], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_L2_AFSR(2)]			;\
	ldx	[scr5], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_L2_AFAR(2)]			;\
	add	scr4, L2_BANK_STEP, scr4		/* next bank */	;\
	add	scr5, L2_BANK_STEP, scr5				;\
	ldx	[scr4], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_L2_AFSR(3)]			;\
	ldx	[scr5], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_L2_AFAR(3)]			;\
	/* store DRAM ESRs in diagnostic report area */			;\
	setx	DRAM_ESR_BASE, scr3, scr4  /* scr4 = DRAM_ESR_BASE */	;\
	setx	DRAM_EAR_BASE, scr3, scr5  /* scr5 = DRAM_EAR_BASE */	;\
	set	DRAM_BANK_STEP, scr6					;\
	ldx	[scr4], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_AFSR(0)]			;\
	ldx	[scr5], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_AFAR(0)]			;\
	add	scr4, scr6, scr4		/* next bank */		;\
	add	scr5, scr6, scr5					;\
	ldx	[scr4], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_AFSR(1)]			;\
	ldx	[scr5], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_AFAR(1)]			;\
	add	scr4, scr6, scr4		/* next bank */		;\
	add	scr5, scr6, scr5					;\
	ldx	[scr4], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_AFSR(2)]			;\
	ldx	[scr5], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_AFAR(2)]			;\
	add	scr4, scr6, scr4		/* next bank */		;\
	add	scr5, scr6, scr5					;\
	ldx	[scr4], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_AFSR(3)]			;\
	ldx	[scr5], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_AFAR(3)]			;\
	/* store DRAM error counter registers and error location registers*/;\
	setx	DRAM_ECR_BASE, scr3, scr4	/* scr4 = DRAM_ECR_BASE */;\
	setx	DRAM_ELR_BASE, scr3, scr5	/* scr4 = DRAM_ELR_BASE */;\
	set	DRAM_BANK_STEP, scr6					;\
	ldx	[scr4], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_CNTR(0)]			;\
	ldx	[scr5], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_LOC(0)]			;\
	add	scr4, scr6, scr4		/* next bank */		;\
	add	scr5, scr6, scr5					;\
	ldx	[scr4], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_CNTR(1)]			;\
	ldx	[scr5], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_LOC(1)]			;\
	add	scr4, scr6, scr4		/* next bank */		;\
	add	scr5, scr6, scr5					;\
	ldx	[scr4], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_CNTR(2)]			;\
	ldx	[scr5], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_LOC(2)]			;\
	add	scr4, scr6, scr4		/* next bank */		;\
	add	scr5, scr6, scr5					;\
	ldx	[scr4], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_CNTR(3)]			;\
	ldx	[scr5], scr3						;\
	stx	scr3, [erpt + CPU_EVBSC_DRAM_LOC(3)]
/* END CSTYLED */

/*
 * Dump all 12 ways of the l2 information to the passed buffer
 * reg1 must be passed as %g1 (may be the same as cpup)
 * reg2 must be passed as %g2 (may be the same as erpt)
 */
/* BEGIN CSTYLED */
#define	DUMP_L2_SET_TAG_DATA(BNUM, ERPT_OFFSET_VAL, cpup, erpt, reg1, reg2)\
	PRINT("DUMPING THE L2\r\n")					;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], reg1			;\
	add	erpt, CPU_VBSC_ERPT + EVBSC_DIAG_BUF, reg2		;\
	HVCALL(dump_l2_set_tag_data_ecc)	/* %g1-6 clobbered */	;\
	CPU_ERPT_STRUCT(ERPT_OFFSET_VAL, cpup, erpt)
/* END CSTYLED */

/*
 * Dump the icache tag and data information for all ways
 */
/* BEGIN CSTYLED */
#define	DUMP_ICACHE_INFO(ERPT_OFFSET_VAL, scr1, scr2, scr3, scr4, scr5,	 \
			scr6, scr7)					 \
	.pushlocals							;\
	CPU_STRUCT(scr1)			/* cpu pointer */	;\
	add	scr1, ERPT_OFFSET_VAL, scr1	/* ereport pointer */	;\
	ldx	[scr1 + CPU_VBSC_ERPT + EVBSC_SPARC_AFAR], scr2 /* addr */;\
	add	scr1, CPU_VBSC_ERPT + EVBSC_DIAG_BUF, scr1 /* diag buf */;\
	ldxa	[%g0]ASI_LSUCR, scr3		/* lsu-diag */		;\
	stx	scr3, [scr1 + ICACHE_LSU_DIAG_REG] /* save it to buf */;\
	set	(ICACHE_MAX_WAYS - 1) , scr3				;\
1:						/* loop for way */	;\
	mulx	scr3, ICACHE_WAY_INCR, scr6	/* offset into entry */	;\
	add	scr1, scr6, scr6					;\
	add	scr6, ICACHE_WAY, scr6					;\
	sllx	scr3, ICACHE_INSTR_WAY_SHIFT, scr4 /* set way for access */;\
	and	scr2, ICACHE_PA2SET_MASK, scr5	/* get set from pa */	;\
	sllx	scr5, ICACHE_SETFROMPA_SHIFT, scr5 /* put in place */	;\
	or	scr4, scr5, scr4					;\
	ldxa	[scr4] ASI_ICACHE_TAG, scr5	/* get tag */		;\
	stx	scr5, [scr6 + DIAG_BUF_ICACHE + ICACHE_TAG] /* save tag */;\
	set	ICACHE_TAG_VALID, scr7		/* valid bit */		;\
	btst	scr7, scr5			/* is it valid tag */	;\
	bz	%xcc, 2f						;\
	nop								;\
	set	(0 << ICACHE_INSTR_WORD_SHIFT), scr5 /* first word */	;\
	or	scr4, scr5, scr5		/* create address */	;\
	ldxa	[scr5]ASI_ICACHE_INSTR, scr5	/* get data */		;\
	stx	scr5, [scr6 + CPU_EVBSC_ICACHE_DIAG_DATA(0)] /* save data */;\
	set	(1 << ICACHE_INSTR_WORD_SHIFT), scr5 /* first word */	;\
	or	scr4, scr5, scr5		/* create address */	;\
	ldxa	[scr5]ASI_ICACHE_INSTR, scr5	/* get data */		;\
	stx	scr5, [scr6 + CPU_EVBSC_ICACHE_DIAG_DATA(1)] /* save data */;\
	set	(2 << ICACHE_INSTR_WORD_SHIFT), scr5 /* first word */	;\
	or	scr4, scr5, scr5		/* create address */	;\
	ldxa	[scr5]ASI_ICACHE_INSTR, scr5	/* get data */		;\
	stx	scr5, [scr6 + CPU_EVBSC_ICACHE_DIAG_DATA(2)] /* save data */;\
	set	(3 << ICACHE_INSTR_WORD_SHIFT), scr5 /* first word */	;\
	or	scr4, scr5, scr5		/* create address */	;\
	ldxa	[scr5]ASI_ICACHE_INSTR, scr5	/* get data */		;\
	stx	scr5, [scr6 + CPU_EVBSC_ICACHE_DIAG_DATA(3)] /* save data */;\
	set	(4 << ICACHE_INSTR_WORD_SHIFT), scr5 /* first word */	;\
	or	scr4, scr5, scr5		/* create address */	;\
	ldxa	[scr5]ASI_ICACHE_INSTR, scr5	/* get data */		;\
	stx	scr5, [scr6 + CPU_EVBSC_ICACHE_DIAG_DATA(4)] /* save data */;\
	set	(5 << ICACHE_INSTR_WORD_SHIFT), scr5 /* first word */	;\
	or	scr4, scr5, scr5		/* create address */	;\
	ldxa	[scr5]ASI_ICACHE_INSTR, scr5	/* get data */		;\
	stx	scr5, [scr6 + CPU_EVBSC_ICACHE_DIAG_DATA(5)] /* save data */;\
	set	(6 << ICACHE_INSTR_WORD_SHIFT), scr5 /* first word */	;\
	or	scr4, scr5, scr5		/* create address */	;\
	ldxa	[scr5]ASI_ICACHE_INSTR, scr5	/* get data */		;\
	stx	scr5, [scr6 + CPU_EVBSC_ICACHE_DIAG_DATA(6)] /* save data */;\
	set	(7 << ICACHE_INSTR_WORD_SHIFT), scr5 /* first word */	;\
	or	scr4, scr5, scr5		/* create address */	;\
	ldxa	[scr5]ASI_ICACHE_INSTR, scr5	/* get data */		;\
	stx	scr5, [scr6 + CPU_EVBSC_ICACHE_DIAG_DATA(7)] /* save data */;\
2:									;\
	subcc	scr3, 1, scr3						;\
	bge,pt	%xcc, 1b			/* next way? */		;\
	nop								;\
	.poplocals
/* END CSTYLED */

/*
 * Dump the dcache tag and data information for all ways
 */
/* BEGIN CSTYLED */
#define	DUMP_DCACHE_INFO(ERPT_OFFSET_VAL, scr1, scr2, scr3, scr4, scr5,	 \
			scr6, scr7)					 \
	.pushlocals							;\
	CPU_STRUCT(scr1)			/* cpu pointer */	;\
	add	scr1, ERPT_OFFSET_VAL + CPU_VBSC_ERPT, scr1 /* erpt */	;\
	ldx	[scr1 + EVBSC_SPARC_AFAR], scr2	/* get addr */		;\
	and	scr2, DCACHE_SET, scr2		/* extract set */	;\
	add	scr1, EVBSC_DIAG_BUF, scr1	/* diag buf */		;\
	ldxa	[%g0]ASI_LSUCR, scr3		/* lsu-diag */		;\
	stx	scr3, [scr1 + DCACHE_LSU_DIAG_REG] /* save it to buf */	;\
	set	(DCACHE_MAX_WAYS - 1) , scr3				;\
1:						/* loop for way */	;\
	sllx	scr3, DCACHE_WAY_SHIFT, scr5				;\
	mulx	scr3, DCACHE_WAY_INCR, scr4				;\
	add	scr4, scr1, scr4					;\
	add	scr4, DCACHE_WAY, scr4					;\
	ldxa	[scr5 + scr2] ASI_DC_TAG, scr6	/* get tag */		;\
	set	DCACHE_TAG_VALID, scr7					;\
	btst	scr7, scr6						;\
	bz	%xcc, 2f						;\
	stx	scr6, [scr4 + DCACHE_TAG]	/* save tag */		;\
	set	DCACHE_TAG_MASK, scr7					;\
	and	scr6, scr7, scr6					;\
	sllx	scr6, DCACHE_TAG_SHIFT, scr6				;\
	ldxa	[scr6 + scr2] ASI_DC_DATA, scr5				;\
	stx	scr5, [scr4 + CPU_EVBSC_DCACHE_DATA(0)]			;\
	set	1, scr5							;\
	sllx	scr5, DCACHE_WORD_SHIFT, scr5				;\
	or	scr6, scr5, scr5					;\
	ldxa	[scr5 + scr2] ASI_DC_DATA, scr6				;\
	stx	scr6, [scr4 + CPU_EVBSC_DCACHE_DATA(1)]			;\
2:									;\
	deccc	scr3							;\
	bge,pt	%xcc, 1b			/* next way? */		;\
	nop								;\
	.poplocals
/* END CSTYLED */

/*
 * Dump the dram content for a l2 cache line size.
 * Align the address to with in a cache line,
 * perform simple loads for each word on the line,
 * and store them into the buffer
 */
/* BEGIN CSTYLED */
#define	DUMP_DRAM_CONTENTS(BNUM, ERPT_OFFSET_VAL, cpup, scr1, scr2, scr3)\
	.pushlocals							;\
	ldx	[cpup + ERPT_OFFSET_VAL + CPU_EVBSC_L2_AFAR(BNUM)], scr2;\
	add	cpup, ERPT_OFFSET_VAL + CPU_VBSC_ERPT + EVBSC_DIAG_BUF, scr1;\
	add	scr2, L2_LINE_SIZE, scr2		/* align addr */;\
	andn	scr2, L2_LINE_SIZE, scr2				;\
	ldx	[scr2 + (0 * SIZEOF_UI64)], scr3	/* read word */	;\
	stx	scr3, [scr1 + DRAM_CONTENTS(0)]		/* store word */;\
	ldx	[scr2 + (1 * SIZEOF_UI64)], scr3	/* read word */	;\
	stx	scr3, [scr1 + DRAM_CONTENTS(1)]		/* store word */;\
	ldx	[scr2 + (2 * SIZEOF_UI64)], scr3	/* read word */	;\
	stx	scr3, [scr1 + DRAM_CONTENTS(2)]		/* store word */;\
	ldx	[scr2 + (3 * SIZEOF_UI64)], scr3	/* read word */	;\
	stx	scr3, [scr1 + DRAM_CONTENTS(3)]		/* store word */;\
	ldx	[scr2 + (4 * SIZEOF_UI64)], scr3	/* read word */	;\
	stx	scr3, [scr1 + DRAM_CONTENTS(4)]		/* store word */;\
	ldx	[scr2 + (5 * SIZEOF_UI64)], scr3	/* read word */	;\
	stx	scr3, [scr1 + DRAM_CONTENTS(5)]		/* store word */;\
	ldx	[scr2 + (6 * SIZEOF_UI64)], scr3	/* read word */	;\
	stx	scr3, [scr1 + DRAM_CONTENTS(6)]		/* store word */;\
	ldx	[scr2 + (7 * SIZEOF_UI64)], scr3	/* read word */	;\
	stx	scr3, [scr1 + DRAM_CONTENTS(7)]		/* store word */;\
	.poplocals
/* END CSTYLED */

/*
 * LDAU: precise UE handler
 */
/* BEGIN CSTYLED */
#define	LDAU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label, ue_senddiag_resume_exit_label)\
	.pushlocals							;\
	PRINT("LDAU DIAG flush line\r\n")				;\
	CPU_PUSH(erpt, scr4, scr5, scr6)				;\
	CPU_STRUCT(cpup)			/* cpu pointer */	;\
	add	cpup, CPU_UE_RPT, cpup		/* UE error report */	;\
	ldx	[cpup + CPU_EVBSC_L2_AFAR(BNUM)], cpup			;\
	/* %g1 (cpup) has error address (PA) */				;\
	HVCALL(l2_flush_line)	/* flush the l2$ line */		;\
	CPU_POP(erpt, scr4, scr5, scr6)					;\
	CPU_STRUCT(cpup)						;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], scr4			;\
	REAL_OFFSET(cpup, scr4, scr4, scr5)				;\
	stx	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_RA]		;\
	mov	ERPT_MEM_SIZE, scr4					;\
	st	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_SZ]		;\
	ldx	[cpup + CPU_L2_LINE_STATE], scr4			;\
	cmp	scr4, 1							;\
	bne,pn	%xcc, 1f /* we only send a pkt if line is dirty */	;\
	nop								;\
	SET_ERPT_EDESC_EATTR(CPU_UE_RPT, EATTR_MEM,			 \
		EDESC_PRECISE_NONRESUMABLE, scr4, scr5, scr6)		;\
	/* return to UE handler epilogue to send pkts: guest, vbsc */	;\
	ba,a	sendnr_ue_resume_exit_label				;\
1:									;\
	ba,a	ue_senddiag_resume_exit_label				;\
	.poplocals
/* END CSTYLED */

/*
 * LDWU: precise UE handler
 */
/* BEGIN CSTYLED */
#define	LDWU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label, ue_senddiag_resume_exit_label) \
	.pushlocals							;\
	PRINT("LDWU DIAG\r\n")						;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], scr4			;\
	REAL_OFFSET(cpup, scr4, scr4, scr5)				;\
	stx	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_RA]		;\
	mov	ERPT_MEM_SIZE, scr4					;\
	st	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_SZ]		;\
	CPU_STRUCT(cpup)						;\
	ldx	[cpup + CPU_L2_LINE_STATE], scr4			;\
	cmp	scr4, 1							;\
	bne,pn	%xcc, 1f /* we only send a pkt if line is dirty */	;\
	nop								;\
	SET_ERPT_EDESC_EATTR(CPU_UE_RPT, EATTR_MEM,			 \
		EDESC_PRECISE_NONRESUMABLE, scr4, scr5, scr6)		;\
	/* return to UE handler epilogue to send pkts: guest, vbsc */	;\
	ba,a	sendnr_ue_resume_exit_label				;\
1:									;\
	ba,a	ue_senddiag_resume_exit_label				;\
	.poplocals
/* END CSTYLED */

/*
 * LRU
 * Fatal Error. We probably won't get to run when this happens
 */
/* BEGIN CSTYLED */
#define	LRU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label)				 \
	PRINT("LRU DIAG\r\n")						;\
	/* return to UE handler epilogue */				;\
	ba,a	sendnr_ue_resume_exit_label
/* END CSTYLED */

/*
 * LVU
 * Fatal Error. We probably won't get to run when this happens
 */
/* BEGIN CSTYLED */
#define	LVU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label)				 \
	PRINT("LVU DIAG\r\n")						;\
	ba,a	sendnr_ue_resume_exit_label
/* END CSTYLED */

/*
 * DAU: precise UE handler
 */
/* BEGIN CSTYLED */
#define	DAU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label)				 \
	/* Clear DAU from DRAM ESR */					;\
	ldx	[erpt + CPU_EVBSC_DRAM_AFSR(BNUM)], scr4		;\
	setx	DRAM_ESR_BASE + BNUM*DRAM_BANK_STEP, scr6, scr5		;\
	stx	scr4, [scr5]	/* clear DRAM ESR */			;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], scr4			;\
	REAL_OFFSET(cpup, scr4, scr4, scr5)				;\
	stx	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_RA]		;\
	mov	ERPT_MEM_SIZE, scr4					;\
	st	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_SZ]		;\
	/* XXX diag data */						;\
	PRINT("DAU DIAG\r\n")						;\
	SET_ERPT_EDESC_EATTR(CPU_UE_RPT, EATTR_MEM,			 \
		EDESC_PRECISE_NONRESUMABLE, scr4, scr5, scr6)		;\
	/* return to UE handler epilogue */				;\
	ba,a	sendnr_ue_resume_exit_label
/* END CSTYLED */

/*
 * LDRU: precise UE handler
 */
/* BEGIN CSTYLED */
#define	LDRU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label, ue_senddiag_resume_exit_label)\
	.pushlocals							;\
	PRINT("LDRU DIAG\r\n")						;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], scr4			;\
	REAL_OFFSET(cpup, scr4, scr4, scr5)				;\
	stx	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_RA]		;\
	mov	ERPT_MEM_SIZE, scr4					;\
	st	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_SZ]		;\
	ldx	[cpup + CPU_L2_LINE_STATE], scr4			;\
	cmp	scr4, 1							;\
	bne,pn	%xcc, 1f /* we only send a pkt if line is dirty */	;\
	nop								;\
	SET_ERPT_EDESC_EATTR(CPU_UE_RPT, EATTR_MEM,			 \
		EDESC_PRECISE_NONRESUMABLE, scr4, scr5, scr6)		;\
	/* return to UE handler epilogue */				;\
	ba,a	sendnr_ue_resume_exit_label				;\
1:									;\
	ba,a	ue_senddiag_resume_exit_label				;\
	.poplocals
/* END CSTYLED */

/*
 * DRU: precise UE handler
 */
/* BEGIN CSTYLED */
#define	DRU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label)				 \
	/* Clear DRU from DRAM ESR */					;\
	ldx	[erpt + CPU_EVBSC_DRAM_AFSR(BNUM)], scr4		;\
	setx	DRAM_ESR_BASE + BNUM*DRAM_BANK_STEP, scr6, scr5		;\
	stx	scr4, [scr5]	/* clear DRAM ESR */			;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], scr4			;\
	REAL_OFFSET(cpup, scr4, scr4, scr5)				;\
	stx	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_RA]		;\
	mov	ERPT_MEM_SIZE, scr4					;\
	st	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_SZ]		;\
	PRINT("DRU DIAG\r\n")						;\
	SET_ERPT_EDESC_EATTR(CPU_UE_RPT, EATTR_MEM,			 \
		EDESC_PRECISE_NONRESUMABLE, scr4, scr5, scr6)		;\
	/* return to UE handler epilogue */				;\
	ba,a	sendnr_ue_resume_exit_label
/* END CSTYLED */

/*
 * LDSU: precise UE handler
 */
/* BEGIN CSTYLED */
#define	LDSU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label, ue_senddiag_resume_exit_label)\
	.pushlocals							;\
	PRINT("LDSU DIAG\r\n")						;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], scr4			;\
	REAL_OFFSET(cpup, scr4, scr4, scr5)				;\
	stx	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_RA]		;\
	mov	ERPT_MEM_SIZE, scr4					;\
	st	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_SZ]		;\
	ldx	[cpup + CPU_L2_LINE_STATE], scr4			;\
	cmp	scr4, 1							;\
	bne,pn	%xcc, 1f /* we only send a pkt if line is dirty */	;\
	nop								;\
	SET_ERPT_EDESC_EATTR(CPU_UE_RPT, EATTR_MEM,			 \
		EDESC_PRECISE_NONRESUMABLE, scr4, scr5, scr6)		;\
	/* return to UE handler epilogue */				;\
	ba,a	sendnr_ue_resume_exit_label				;\
1:									;\
	ba,a	ue_senddiag_resume_exit_label				;\
	.poplocals
/* END CSTYLED */
/*
 * DSU: precise UE handler
 */
/* BEGIN CSTYLED */
#define	DSU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		ue_senddiag_resume_exit_label)				 \
	/* Clear DSU from DRAM ESR */					;\
	ldx	[erpt + CPU_EVBSC_DRAM_AFSR(BNUM)], scr4		;\
	setx	DRAM_ESR_BASE + BNUM*DRAM_BANK_STEP, scr6, scr5		;\
	stx	scr4, [scr5]	/* clear DRAM ESR */			;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], scr4			;\
	REAL_OFFSET(cpup, scr4, scr4, scr5)				;\
	stx	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_RA]		;\
	mov	ERPT_MEM_SIZE, scr4					;\
	st	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_SZ]		;\
	PRINT("DSU DIAG\r\n")						;\
	SET_ERPT_EDESC_EATTR(CPU_UE_RPT, EATTR_MEM,			 \
		EDESC_PRECISE_NONRESUMABLE, scr4, scr5, scr6)		;\
	/* return to UE handler epilogue */				;\
	ba,a	ue_senddiag_resume_exit_label
/* END CSTYLED */

/*
 * MEU: Just the MEU bit is set in L2 ESR.
 * Send a diagnostic error report.
 */
/* BEGIN CSTYLED */
#define	JUST_L2_MEU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6,	 \
		scr7, ue_resume_exit_label)				 \
	PRINT("dis JUST_L2_MEU\r\n")					;\
	ba,a	ue_resume_exit_label
/* END CSTYLED */

/*
 * Macro to process precise uncorrectable errors in L2/DRAM
 * All registers %g1-%g7 are used.
 */
/* BEGIN CSTYLED */
#define	PROCESS_UE_IN_L2_ESR(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6,	 \
		scr7, sendnr_ue_resume_exit_label,			 \
		ue_senddiag_resume_exit_label,				 \
		ue_resume_exit_label)					 \
	.pushlocals							;\
	PRINT("PROCESS UE\r\n")						;\
	CPU_ERPT_STRUCT(CPU_UE_RPT, cpup, erpt)	/* cpu, erpt pointer */	;\
	ldx	[erpt + CPU_EVBSC_L2_AFSR(BNUM)], l2esr			;\
	/* l2esr has L2 ESR value */					;\
	setx	L2_ESR_LDAU, scr5, scr4		/* LDAU */		;\
	btst	scr4, l2esr			/* LDAU? */		;\
	bz	%xcc, 1f			/* no, goto 1 */	;\
	nop								;\
	LDAU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label, ue_senddiag_resume_exit_label);\
1:	setx	L2_ESR_DAU, scr5, scr4		/* DAU */		;\
	btst	scr4, l2esr			/* DAU? */		;\
	bz	%xcc, 2f			/* no, goto 2 */	;\
	nop								;\
	DAU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label)				;\
2:	setx	L2_ESR_LDWU, scr5, scr4		/* LDWU */		;\
	btst	scr4, l2esr			/* LDWU? */		;\
	bz	%xcc, 3f			/* no, goto 3 */	;\
	nop								;\
	LDWU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label, ue_senddiag_resume_exit_label);\
3:	setx	L2_ESR_LDRU, scr5, scr4		/* LDRU */		;\
	btst	scr4, l2esr			/* LDRU? */		;\
	bz	%xcc, 4f			/* no, goto 4 */	;\
	nop								;\
	LDRU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label, ue_senddiag_resume_exit_label);\
4:	setx	L2_ESR_LDSU, scr5, scr4		/* LDSU */		;\
	btst	scr4, l2esr			/* LDSU? */		;\
	bz	%xcc, 5f			/* no, goto 5 */	;\
	nop								;\
	LDSU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label, ue_senddiag_resume_exit_label);\
5:	setx	L2_ESR_LRU, scr5, scr4		/* LRU */		;\
	btst	scr4, l2esr			/* LRU? */		;\
	bz	%xcc, 6f			/* no, goto 6 */	;\
	nop								;\
	LRU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label)				;\
6:	setx	L2_ESR_DRU, scr5, scr4		/* DRU */		;\
	btst	scr4, l2esr			/* DRU? */		;\
	bz	%xcc, 7f			/* no, goto 7 */	;\
	nop								;\
	DRU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label)				;\
7:	setx	L2_ESR_DSU, scr5, scr4		/* DSU */		;\
	btst	scr4, l2esr			/* DSU? */		;\
	bz	%xcc, 8f			/* no, goto 8 */	;\
	nop								;\
	DSU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		ue_senddiag_resume_exit_label)				;\
8:	setx	L2_ESR_LVU, scr5, scr4		/* LVU */		;\
	btst	scr4, l2esr			/* LVU? */		;\
	bz	%xcc, 9f			/* no, goto 9 */	;\
	nop								;\
	LVU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,	 \
		sendnr_ue_resume_exit_label)				;\
9:	setx	L2_ESR_MEU, scr5, scr4		/* MEU */		;\
	btst	scr4, l2esr			/* MEU? */		;\
	bz	%xcc, 0f			/* no, goto 0 */	;\
	nop								;\
	JUST_L2_MEU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,\
		ue_resume_exit_label)					;\
0:	nop								;\
	PRINT("PROCESS UE END\r\n")					;\
	.poplocals
/* END CSTYLED */

/*
 * Disrupting UE error handlers
 * Use CE error report buffer for dis_ues
 */
/* BEGIN CSTYLED */
#define	DIS_LDWU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,\
			dis_ue_err_ret_label)				 \
	PRINT("dis LDWU DIAG\r\n")					;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], scr4			;\
	REAL_OFFSET(cpup, scr4, scr4, scr5)				;\
	stx	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_RA]		;\
	mov	ERPT_MEM_SIZE, scr4					;\
	st	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_SZ]		;\
	SET_ERPT_EDESC_EATTR(CPU_CE_RPT, EATTR_MEM,			 \
		EDESC_UE_RESUMABLE, scr4, scr5, scr6)			;\
	/* return to UE handler epilogue */				;\
	ba,a	dis_ue_err_ret_label
/* END CSTYLED */

/* BEGIN CSTYLED */
#define	DIS_LDRU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,\
			dis_ue_err_ret_label, ue_resume_exit_label)	 \
	.pushlocals							;\
	PRINT("dis LDRU DIAG\r\n")					;\
	ldx	[cpup + CPU_L2_LINE_STATE], scr4			;\
	cmp	scr4, 1							;\
	bne,pn	%xcc, 1f/* we only send a pkt if line is dirty */;\
	nop								;\
	SET_ERPT_EDESC_EATTR(CPU_CE_RPT, EATTR_MEM, EDESC_UE_RESUMABLE,	 \
		scr4, scr5, scr6)					;\
	/* return to UE handler epilogue */				;\
	ba,a	dis_ue_err_ret_label					;\
1:									;\
	ba,a	ue_resume_exit_label					;\
	.poplocals
/* END CSTYLED */

/* BEGIN CSTYLED */
#define	DIS_LDSU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,\
			dis_ue_err_ret_label, ue_resume_exit_label)	 \
	.pushlocals							;\
	PRINT("dis LDSU DIAG\r\n")					;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], scr4			;\
	REAL_OFFSET(cpup, scr4, scr4, scr5)				;\
	stx	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_RA]		;\
	mov	ERPT_MEM_SIZE, scr4					;\
	st	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_SZ]		;\
	ldx	[cpup + CPU_L2_LINE_STATE], scr4			;\
	cmp	scr4, 1							;\
	bne,pn	%xcc, 1f /* we only send a pkt if line is dirty */	;\
	nop								;\
	SET_ERPT_EDESC_EATTR(CPU_CE_RPT, EATTR_MEM, EDESC_UE_RESUMABLE,	 \
		scr4, scr5, scr6)					;\
	/* return to UE handler epilogue */				;\
	ba,a	dis_ue_err_ret_label					;\
1:									;\
	ba,a	ue_resume_exit_label					;\
	.poplocals
/* END CSTYLED */

/* BEGIN CSTYLED */
#define	DIS_LDAU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,\
			dis_ue_err_ret_label, ue_resume_exit_label)	 \
	.pushlocals							;\
	PRINT("dis LDAU DIAG\r\n")					;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], scr4			;\
	REAL_OFFSET(cpup, scr4, scr4, scr5)				;\
	stx	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_RA]		;\
	mov	ERPT_MEM_SIZE, scr4					;\
	st	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_SZ]		;\
	ldx	[cpup + CPU_L2_LINE_STATE], scr4			;\
	cmp	scr4, 1							;\
	bne,pn	%xcc, 1f /* we only send a pkt if line is dirty */	;\
	nop								;\
	SET_ERPT_EDESC_EATTR(CPU_CE_RPT, EATTR_MEM, EDESC_UE_RESUMABLE,	 \
		scr4, scr5, scr6)					;\
	ba,a	dis_ue_err_ret_label					;\
1:									;\
	ba,a	ue_resume_exit_label					;\
	.poplocals
/* END CSTYLED */

/* BEGIN CSTYLED */
#define	DIS_DRU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7, \
			dis_ue_err_ret_label)				 \
	/* Clear DRU from DRAM ESR */					;\
	ldx	[erpt + CPU_EVBSC_DRAM_AFSR(BNUM)], scr4		;\
	setx	DRAM_ESR_BASE + BNUM*DRAM_BANK_STEP, scr6, scr5		;\
	stx	scr4, [scr5]	/* clear DRAM ESR */			;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], scr4			;\
	REAL_OFFSET(cpup, scr4, scr4, scr5)				;\
	stx	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_RA]		;\
	mov	ERPT_MEM_SIZE, scr4					;\
	st	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_SZ]		;\
	PRINT("dis DRU DIAG\r\n")					;\
	SET_ERPT_EDESC_EATTR(CPU_CE_RPT, EATTR_MEM, EDESC_UE_RESUMABLE,	 \
		scr4, scr5, scr6)					;\
	/* return to UE handler epilogue */				;\
	ba,a	dis_ue_err_ret_label
/* END CSTYLED */

/* BEGIN CSTYLED */
#define	DIS_DSU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7, \
			dis_ue_err_ret_label)				 \
	/* Clear DSU from DRAM ESR */					;\
	ldx	[erpt + CPU_EVBSC_DRAM_AFSR(BNUM)], scr4		;\
	setx	DRAM_ESR_BASE + BNUM*DRAM_BANK_STEP, scr6, scr5		;\
	stx	scr4, [scr5]	/* clear DRAM ESR */			;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], scr4			;\
	REAL_OFFSET(cpup, scr4, scr4, scr5)				;\
	stx	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_RA]		;\
	mov	ERPT_MEM_SIZE, scr4					;\
	st	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_SZ]		;\
	PRINT("dis DSU DIAG\r\n")					;\
	SET_ERPT_EDESC_EATTR(CPU_CE_RPT, EATTR_MEM, EDESC_UE_RESUMABLE,	 \
		scr4, scr5, scr6)					;\
	/* return to UE handler epilogue */				;\
	ba,a	dis_ue_err_ret_label
/* END CSTYLED */

/* BEGIN CSTYLED */
#define	DIS_DAU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7, \
			dis_ue_err_ret_label)				 \
	PRINT("dis DAU DIAG\r\n")					;\
	/* Clear DAU from DRAM ESR */					;\
	ldx	[erpt + CPU_EVBSC_DRAM_AFSR(BNUM)], scr4		;\
	setx	DRAM_ESR_BASE + BNUM*DRAM_BANK_STEP, scr6, scr5		;\
	stx	scr4, [scr5]	/* clear DRAM ESR */			;\
	ldx	[erpt + CPU_EVBSC_L2_AFAR(BNUM)], scr4			;\
	REAL_OFFSET(cpup, scr4, scr4, scr5)				;\
	stx	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_RA]		;\
	mov	ERPT_MEM_SIZE, scr4					;\
	st	scr4, [erpt + CPU_SUN4V_ERPT + ESUN4V_SZ]		;\
	SET_ERPT_EDESC_EATTR(CPU_CE_RPT, EATTR_MEM, EDESC_UE_RESUMABLE,	 \
		scr4, scr5, scr6)					;\
	/* return to UE handler epilogue */				;\
	ba,a	dis_ue_err_ret_label
/* END CSTYLED */

/*
 * MEU: Just the MEU bit is set in L2 ESR.
 * Send a diagnostic error report.
 */
/* BEGIN CSTYLED */
#define	DIS_JUST_L2_MEU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5,	 \
			scr6, scr7, ue_resume_exit_label)		 \
	PRINT("dis JUST_L2_MEU\r\n")					;\
	ba,a	ue_resume_exit_label
/* END CSTYLED */

/*
 * Macro to process disrupting UE errors in L2/DRAM
 * All %g1-%g7 registers are used.
 * The disrupting error logs are saved in cpu.ce_rpt.
 */
/* BEGIN CSTYLED */
#define	PROCESS_DIS_UE_IN_L2_ESR(BNUM, cpup, erpt, l2esr, scr4, scr5,	 \
			scr6, scr7, dis_ue_err_ret_label,		 \
			ue_resume_exit_label)				 \
	.pushlocals							;\
	PRINT("PROCESS DIS UE\r\n")					;\
	CPU_ERPT_STRUCT(CPU_CE_RPT, cpup, erpt)	/* cpu pointer */	;\
	ldx	[erpt + CPU_EVBSC_L2_AFSR(BNUM)], l2esr			;\
	/* l2esr has L2 ESR value */					;\
	setx	L2_ESR_LDAU, scr5, scr4		/* LDAU */		;\
	btst	scr4, l2esr			/* LDAU? */		;\
	bz	%xcc, 1f			/* no, goto 1 */	;\
	nop								;\
	DIS_LDAU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,\
		dis_ue_err_ret_label, ue_resume_exit_label)		;\
1:	setx	L2_ESR_DAU, scr5, scr4		/* DAU */		;\
	btst	scr4, l2esr			/* DAU? */		;\
	bz	%xcc, 2f			/* no, goto 2 */	;\
	nop								;\
	DIS_DAU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7, \
		dis_ue_err_ret_label)					;\
2:	setx	L2_ESR_LDWU, scr5, scr4		/* LDWU */		;\
	btst	scr4, l2esr			/* LDWU? */		;\
	bz	%xcc, 3f			/* no, goto 3 */	;\
	nop								;\
	DIS_LDWU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,\
		dis_ue_err_ret_label)					;\
3:	setx	L2_ESR_LDRU, scr5, scr4		/* LDRU */		;\
	btst	scr4, l2esr			/* LDRU? */		;\
	bz	%xcc, 4f			/* no, goto 4 */	;\
	nop								;\
	DIS_LDRU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,\
		dis_ue_err_ret_label, ue_resume_exit_label)		;\
4:	setx	L2_ESR_LDSU, scr5, scr4		/* LDSU */		;\
	btst	scr4, l2esr			/* LDSU? */		;\
	bz	%xcc, 5f			/* no, goto 5 */	;\
	nop								;\
	DIS_LDSU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7,\
		dis_ue_err_ret_label, ue_resume_exit_label)		;\
5:	setx	L2_ESR_DRU, scr5, scr4		/* DRU */		;\
	btst	scr4, l2esr			/* DRU? */		;\
	bz	%xcc, 6f			/* no, goto 7 */	;\
	nop								;\
	DIS_DRU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7, \
		dis_ue_err_ret_label)					;\
6:	setx	L2_ESR_DSU, scr5, scr4		/* DSU */		;\
	btst	scr4, l2esr			/* DSU? */		;\
	bz	%xcc, 7f			/* no, goto 8 */	;\
	nop								;\
	DIS_DSU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5, scr6, scr7, \
		dis_ue_err_ret_label)					;\
7:	setx	L2_ESR_MEU, scr5, scr4		/* MEU */		;\
	btst	scr4, l2esr			/* MEU? */		;\
	bz	%xcc, 0f			/* no, goto 0 */	;\
	nop								;\
	DIS_JUST_L2_MEU_HANDLER(BNUM, cpup, erpt, l2esr, scr4, scr5,	 \
		scr6, scr7, ue_resume_exit_label)			;\
0:	.poplocals
/* END CSTYLED */

/*
 * Dump the DTLB entries into the erpt.diag_buf area
 * NOTE: cpup and erpt are input args.
 *
 * There is no safe way of obtaining TLB information after an error has
 * occurred. Parity is still checked. We could end up in an error after error
 * situation since NCEEN is turned ON. We try our best and we dump the tags
 * in case of a TLB data parity error.
 */
/* BEGIN CSTYLED */
#define	DUMP_DTLB(cpup, erpt, reg3, reg4, reg5, reg6, reg7)		 \
	.pushlocals							;\
	add	erpt, CPU_VBSC_ERPT + EVBSC_DIAG_BUF, erpt /* diag buf */;\
	set	0, reg3				/* TLB entry = 0 */	;\
1:	ldxa	[reg3] ASI_DTLB_TAG, reg6	/* tag */		;\
	stx	reg6, [erpt + DIAG_BUF_DTLB + TLB_TAG] /* save tag */	;\
	setx	0xcafefeedfeedcafe, reg5, reg6	/* data */		;\
	stx	reg6, [erpt + DIAG_BUF_DTLB + TLB_DATA]			;\
	add	reg3, 0x8, reg3			/* entry++ */		;\
	cmp	reg3, 0x200			/* done? */		;\
	bnz	1b				/* loop back */		;\
	add	erpt, DIAG_BUF_DTLB_INCR, erpt	/* increment */		;\
	nop								;\
	.poplocals
/* END CSTYLED */

/*
 * Dump the ITLB entries into the erpt.diag_buf area
 * NOTE: cpup and erpt are input args.
 *
 * There is no safe way of obtaining TLB information after an error has
 * occurred. Parity is still checked. We could end up in an error after error
 * situation since NCEEN is turned ON. We try our best and we dump the tags
 * in case of a TLB data parity error.
 */
/* BEGIN CSTYLED */
#define	DUMP_ITLB(cpup, erpt, reg3, reg4, reg5, reg6, reg7)		 \
	.pushlocals							;\
	add	erpt, CPU_VBSC_ERPT + EVBSC_DIAG_BUF, erpt /* diag buf */;\
	set	0, reg3				/* TLB entry = 0 */	;\
1:	ldxa	[reg3] ASI_ITLB_TAG, reg6	/* tag */		;\
	stx	reg6, [erpt + DIAG_BUF_ITLB + TLB_TAG] /* save tag */	;\
	setx	0xcafefeedfeedcafe, reg5, reg6	/* data */		;\
	stx	reg6, [erpt + DIAG_BUF_ITLB + TLB_DATA]			;\
	add	reg3, TLB_SIZE, reg3		/* entry++ */		;\
	cmp	reg3, 0x200			/* done? */		;\
	bnz	1b				/* loop back */		;\
	add	erpt, DIAG_BUF_ITLB_INCR, erpt	/* increment */		;\
	nop								;\
	.poplocals
/* END CSTYLED */

/*
 * Macro to read the ESRs and print them to the console
 */
#ifdef NIAGARA_BRINGUP
/* BEGIN CSTYLED */
#define	CONSOLE_PRINT_ESRS(scr1, scr2, scr3, scr4)			 \
	PRINT("LSU_CONTROL\r\n")					;\
	ldxa	[%g0]ASI_LSUCR, scr1					;\
	PRINTX(scr1)							;\
	PRINT("\r\n")							;\
	PRINT("SPARC ESR/EAR\r\n")					;\
	ldxa	[%g0]ASI_SPARC_ERR_STATUS, scr1				;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	ldxa	[%g0]ASI_SPARC_ERR_ADDR, scr1				;\
	PRINTX(scr1)							;\
	PRINT("\r\n")							;\
	PRINT("L2 ESRs\r\n")						;\
	setx	L2_ESR_BASE, scr2, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	setx	L2_ESR_BASE, scr2, scr3					;\
	add	scr3, 0x40, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	setx	L2_ESR_BASE, scr2, scr3					;\
	add	scr3, 0x80, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	setx	L2_ESR_BASE, scr2, scr3					;\
	add	scr3, 0xC0, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("\r\n")							;\
	PRINT("L2 EARs\r\n")						;\
	setx	L2_EAR_BASE, scr2, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	setx	L2_EAR_BASE, scr2, scr3					;\
	add	scr3, 0x40, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	setx	L2_EAR_BASE, scr2, scr3					;\
	add	scr3, 0x80, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	setx	L2_EAR_BASE, scr2, scr3					;\
	add	scr3, 0xC0, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("\r\n")							;\
	PRINT("DRAM ESRs\r\n")						;\
	setx	DRAM_ESR_BASE, scr2, scr3				;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	setx	DRAM_ESR_BASE, scr2, scr3				;\
	set	0x1000, scr4						;\
	add	scr3, scr4, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	setx	DRAM_ESR_BASE, scr2, scr3				;\
	set	2* 0x1000, scr4						;\
	add	scr3, scr4, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	setx	DRAM_ESR_BASE, scr2, scr3				;\
	set	3* 0x1000, scr4						;\
	add	scr3, scr4, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("\r\n")							;\
	PRINT("DRAM EARs\r\n")						;\
	setx	DRAM_EAR_BASE, scr2, scr3				;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	setx	DRAM_EAR_BASE, scr2, scr3				;\
	set	0x1000, scr4						;\
	add	scr3, scr4, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	setx	DRAM_EAR_BASE, scr2, scr3				;\
	set	2* 0x1000, scr4						;\
	add	scr3, scr4, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	setx	DRAM_EAR_BASE, scr2, scr3				;\
	set	3* 0x1000, scr4						;\
	add	scr3, scr4, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("\r\n")							;\
	PRINT("JBI_ERR_CONFIG\r\n")					;\
	setx	JBI_ERR_CONFIG, scr2, scr3				;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("\r\n")							;\
	PRINT("SPARC EEN\r\n")						;\
	ldxa	[%g0]ASI_SPARC_ERR_EN, scr1				;\
	PRINTX(scr1)							;\
	PRINT("\r\n")							;\
	PRINT("L2 EENs\r\n")						;\
	setx	L2_EEN_BASE, scr2, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	setx	L2_EEN_BASE, scr2, scr3					;\
	add	scr3, 0x40, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	setx	L2_EEN_BASE, scr2, scr3					;\
	add	scr3, 0x80, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("  ")							;\
	setx	L2_EEN_BASE, scr2, scr3					;\
	add	scr3, 0xC0, scr3					;\
	ldx	[scr3], scr1						;\
	PRINTX(scr1)							;\
	PRINT("\r\n======================\r\n")
/* END CSTYLED */
#else
#define	CONSOLE_PRINT_ESRS(scr1, scr2, scr3, scr4)
#endif

/*
 * For bringup: log the TLB entries on the console
 * TLB data is always in UE_RPT
 */
#ifdef NIAGARA_BRINGUP
/* BEGIN CSTYLED */
#define	CONSOLE_PRINT_TLB_DATA_2(x, reg1, reg2, reg3, reg4, reg5, reg6,	 \
			reg7)						 \
	.pushlocals							;\
	CPU_STRUCT(reg6)			/* cpu pointer */	;\
	add	reg6, CPU_UE_RPT, reg6		/* cpu.ue_rpt */	;\
	add	reg6, CPU_VBSC_ERPT + EVBSC_DIAG_BUF, reg6 /* diag buf */;\
	add	reg6, 1024, reg6		/* after demap */	;\
	PRINT(x)							;\
1:	ldx	[reg6], reg1			/* tag */		;\
	PRINTX(reg1)				/* print tag */		;\
	PRINT("    ")				/* space */		;\
	ldx	[reg6 + 0x8], reg1		/* data */		;\
	PRINTX(reg1)				/* print data */	;\
	PRINT("\r\n")				/* newline */		;\
	add	reg6, 0x10, reg6		/* next entry */	;\
	CPU_STRUCT(reg1)			/* cpu pointer */	;\
	add	reg1, CPU_UE_RPT, reg1					;\
	add	reg1, CPU_VBSC_ERPT + EVBSC_DIAG_BUF, reg1		;\
	add	reg1, 0x400, reg1					;\
	add	reg1, 0x400, reg1					;\
	cmp	reg6, reg1						;\
	bnz	1b							;\
	nop								;\
	.poplocals
/* END CSTYLED */
#else
#define	CONSOLE_PRINT_TLB_DATA_2(x, reg1, reg2, reg3, reg4, reg5, reg6, reg7)
#endif

/*
 * For bringup: log the TLB entries on the console
 * TLB data is always in UE_RPT
 */
#ifdef NIAGARA_BRINGUP
/* BEGIN CSTYLED */
#define	CONSOLE_PRINT_TLB_DATA(x, reg1, reg2, reg3, reg4, reg5, reg6, reg7)\
	.pushlocals							;\
	CPU_STRUCT(reg6)			/* cpu pointer */	;\
	add	reg6, CPU_UE_RPT, reg6		/* cpu.ue_rpt */	;\
	add	reg6, CPU_VBSC_ERPT + EVBSC_DIAG_BUF, reg6 /* diag buf */;\
	PRINT(x)							;\
1:	ldx	[reg6], reg1			/* tag */		;\
	PRINTX(reg1)				/* print tag */		;\
	PRINT("    ")				/* space */		;\
	ldx	[reg6 + 0x8], reg1		/* data */		;\
	PRINTX(reg1)				/* print data */	;\
	PRINT("\r\n")				/* newline */		;\
	add	reg6, 0x10, reg6		/* next entry */	;\
	CPU_STRUCT(reg1)			/* cpu pointer */	;\
	add	reg1, CPU_UE_RPT, reg1					;\
	add	reg1, CPU_VBSC_ERPT + EVBSC_DIAG_BUF, reg1		;\
	add	reg1, 0x400, reg1					;\
	cmp	reg6, reg1						;\
	bnz	%xcc, 1b						;\
	nop								;\
	.poplocals
/* BEGIN CSTYLED */
#else
#define	CONSOLE_PRINT_TLB_DATA(x, reg1, reg2, reg3, reg4, reg5, reg6, reg7)
#endif

/*
 * Dump the JBI and SSI error logs into the erpt.diag_buf area
 * NOTE: cpup and erpt are input args.
 */
/* BEGIN CSTYLED */
#define	DUMP_JBI_SSI(cpup, erpt, reg3, reg4, reg5, reg6, reg7)		 \
	add	erpt, CPU_VBSC_ERPT + EVBSC_DIAG_BUF, erpt /* diag buf */;\
	setx	JBI_ERR_CONFIG, reg3, reg4				;\
	ldx	[reg4], reg5		/* reg5 = JBI_ERR_CONFIG */	;\
	stx	reg5, [erpt]		/* save JBI_ERR_CONFIG */	;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_ERR_LOG, reg3, reg4					;\
	ldx	[reg4], reg5		/* reg5 = JBI_ERROR_LOG */	;\
	stx	reg5, [erpt]		/* save JBI_ERROR_LOG */	;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_ERR_OVF, reg3, reg4					;\
	ldx	[reg4], reg5		/* reg5 = JBI_ERROR_OVF */	;\
	stx	reg5, [erpt]		/* save JBI_ERROR_OVF */	;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_LOG_ENB, reg3, reg4					;\
	ldx	[reg4], reg5		/* reg5 = JBI_LOG_ENB */	;\
	stx	reg5, [erpt]		/* save JBI_LOG_ENB */		;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_SIG_ENB, reg3, reg4					;\
	ldx	[reg4], reg5		/* reg5 = JBI_SIG_ENB */	;\
	stx	reg5, [erpt]		/* save JBI_SIG_ENB */		;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_LOG_ADDR, reg3, reg4				;\
	ldx	[reg4], reg5		/* reg5 = JBI_LOG_ADDR */	;\
	stx	reg5, [erpt]		/* save JBI_LOG_ADDR */		;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_LOG_DATA0, reg3, reg4				;\
	ldx	[reg4], reg5		/* reg5 = JBI_LOG_DATA0 */	;\
	stx	reg5, [erpt]		/* save JBI_LOG_DATA0 */	;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_LOG_DATA1, reg3, reg4				;\
	ldx	[reg4], reg5		/* reg5 = JBI_LOG_DATA1 */	;\
	stx	reg5, [erpt]		/* save JBI_LOG_DATA1 */	;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_LOG_CTRL, reg3, reg4				;\
	ldx	[reg4], reg5		/* reg5 = JBI_LOG_CTRL */	;\
	stx	reg5, [erpt]		/* save JBI_LOG_CTRL */		;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_LOG_PAR, reg3, reg4					;\
	ldx	[reg4], reg5		/* reg5 = JBI_LOG_PAR */	;\
	stx	reg5, [erpt]		/* save JBI_LOG_PAR */		;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_LOG_NACK, reg3, reg4				;\
	ldx	[reg4], reg5		/* reg5 = JBI_LOG_NACK */	;\
	stx	reg5, [erpt]		/* save JBI_LOG_NACK */		;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_LOG_ARB, reg3, reg4					;\
	ldx	[reg4], reg5		/* reg5 = JBI_LOG_ARB */	;\
	stx	reg5, [erpt]		/* save JBI_LOG_ARB */		;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_L2_TIMEOUT, reg3, reg4				;\
	ldx	[reg4], reg5		/* reg5 = JBI_L2_TIMEOUT */	;\
	stx	reg5, [erpt]		/* save JBI_L2_TIMEOUT */	;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_ARB_TIMEOUT, reg3, reg4				;\
	ldx	[reg4], reg5		/* reg5 = JBI_ARB_TIMEOUT */	;\
	stx	reg5, [erpt]		/* save JBI_ARB_TIMEOUT */	;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_TRANS_TIMEOUT, reg3, reg4				;\
	ldx	[reg4], reg5		/* reg5 = JBI_TRANS_TIMEOUT */	;\
	stx	reg5, [erpt]		/* save JBI_TRANS_TIMEOUT */	;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_MEMSIZE, reg3, reg4					;\
	ldx	[reg4], reg5		/* reg5 = JBI_MEMSIZE */	;\
	stx	reg5, [erpt]		/* save JBI_MEMSIZE */		;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	JBI_ERR_INJECT, reg3, reg4				;\
	ldx	[reg4], reg5		/* reg5 = JBI_ERR_INJECT */	;\
	stx	reg5, [erpt]		/* save JBI_ERR_INJECT */	;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	SSI_TIMEOUT, reg3, reg4					;\
	ldx	[reg4], reg5		/* reg5 = SSI_TIMEOUT */	;\
	stx	reg5, [erpt]		/* save SSI_TIMEOUT */		;\
	add	erpt, 0x8, erpt		/* increment */			;\
	setx	SSI_LOG, reg3, reg4					;\
	ldx	[reg4], reg5		/* reg5 = SSI_ERR_LOG */	;\
	stx	reg5, [erpt]		/* save SSI_ERR_LOG */		;\
/* END CSTYLED */

#ifdef NIAGARA_BRINGUP
/* BEGIN CSTYLED */
#define	CONSOLE_PRINT_JBI_SSI(x, reg1, reg2, reg3, reg4, reg5, reg6, reg7)\
	CPU_STRUCT(reg6)			/* cpu pointer */	;\
	add	reg6, CPU_UE_RPT, reg6		/* cpu.ue_rpt */	;\
	add	reg6, CPU_VBSC_ERPT + EVBSC_DIAG_BUF, reg6 /* diag buf */;\
	PRINT(x)							;\
	PRINT("JBI_ERR_CONFIG\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_ERROR_LOG\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_ERROR_OVF\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_LOG_ENB\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_SIG_ENB\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_LOG_ADDR\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_LOG_DATA0\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_LOG_DATA1\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_LOG_CTRL\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_LOG_PAR\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_LOG_NACK\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_LOG_ARB\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_L2_TIMEOUT\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_ARB_TIMEOUT\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_TRANS_TIMEOUT\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_MEMSIZE\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("JBI_ERR_INJECT\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("SSI_TIMEOUT\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	add	reg6, 0x8, reg6			/* next */		;\
	PRINT("SSI_ERR_LOG\r\n")					;\
	ldx	[reg6], reg1						;\
	PRINTX(reg1)							;\
	PRINT("\r\n")							;\
	nop
/* END CSTYLED */
#else
#define	CONSOLE_PRINT_JBI_SSI(x, reg1, reg2, reg3, reg4, reg5, reg6, reg7)
#endif


/* BEGIN CSTYLED */
#define	SPINLOCK_ENTER_SS_LOCK(scr1, scr2, scr3) \
	LOCK_ADDR(CONFIG_SINGLE_STRAND_LOCK, scr1)	/* ->lock */	;\
	SPINLOCK_ENTER(scr1, scr2, scr3)

#define	SPINLOCK_EXIT_SS_LOCK(scr1) \
	LOCK_ADDR(CONFIG_SINGLE_STRAND_LOCK, scr1)	/* ->lock */	;\
	SPINLOCK_EXIT(scr1)

#define	SPINLOCK_IDLE_ALL_STRAND(cpup, scr1, scr2, scr3, scr4) \
	SPINLOCK_ENTER_SS_LOCK(scr1, scr2, scr3)			;\
	IDLE_ALL_STRAND(cpup, scr1, scr2, scr3, scr4)

#define	SPINLOCK_RESUME_ALL_STRAND(cpup, scr1, scr2, scr3, scr4) \
	RESUME_ALL_STRAND(cpup, scr1, scr2, scr3, scr4)			;\
	SPINLOCK_EXIT_SS_LOCK(scr1)
/* END CSTYLED */


#ifdef DEBUG

/* BEGIN CSTYLED */
#define	SPINLOCK_ENTER_ERRORLOCK(scr1, scr2, scr3) \
	LOCK_ADDR(CONFIG_ERRORLOCK, scr1)	/* ->lock */	;\
	SPINLOCK_ENTER(scr1, scr2, scr3)

#define	SPINLOCK_EXIT_ERRORLOCK(scr1) \
	LOCK_ADDR(CONFIG_ERRORLOCK, scr1)	/* ->lock */	;\
	SPINLOCK_EXIT(scr1)
/* END CSTYLED */

#else /* DEBUG */

/* BEGIN CSTYLED */
#define	SPINLOCK_ENTER_ERRORLOCK(scr1, scr2, scr3)

#define	SPINLOCK_EXIT_ERRORLOCK(scr1)
/* END CSTYLED */

#endif /* DEBUG */


#ifdef __cplusplus
}
#endif

#endif /* _NIAGARA_CPU_ERRS_H */
