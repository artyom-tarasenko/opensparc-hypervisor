/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */
#ifndef _NIAGARA_DRAM_H
#define _NIAGARA_DRAM_H

#pragma ident	"@(#)dram.h	1.4	05/10/22 SMI"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Memory Controller definitions 
 */

#define	NO_DRAM_BANKS			4
#define	DRAM_BANK_SHIFT			12
#define	DRAM_BANK_STEP			(1 << DRAM_BANK_SHIFT)
#define	DRAM_BASE			(0x97 << 32)

#define DRAM_CSR_BASE  			DRAM_BASE
#define DRAM_PORT_SHIFT  		12
#define DRAM_MAX_PORT  			3

#define DRAM_CAS_ADDR_WIDTH_REG		0x00
#define DRAM_RAS_ADDR_WIDTH_REG		0x08
#define DRAM_CAS_LAT_REG		0x10
#define DRAM_SCRUB_FREQ_REG		0x18
#define DRAM_REFRESH_FREQ_REG		0x20

#define DRAM_OPEN_BANK_MAX		0x28	/* power management, 1 reg per each pair of channels */

#define DRAM_REFRESH_COUNT_REG		0x38
#define DRAM_SCRUB_ENABLE_REG		0x40

#define DRAM_PROG_TIME_CTR              0x48	/* Power management */

#define DRAM_TRRD_REG			0x80
#define DRAM_TRC_REG			0x88
#define DRAM_TRCD_REG			0x90
#define DRAM_TWTR_REG			0x98
#define DRAM_TRTW_REG			0xa0
#define DRAM_TRTP_REG			0xa8
#define DRAM_TRAS_REG			0xb0
#define DRAM_TRP_REG			0xb8
#define DRAM_TWR_REG			0xc0
#define DRAM_TRFC_REG			0xc8
#define DRAM_TMRD_REG			0xd0
#define DRAM_TIWTR_REG			0xe0
#define DRAM_PRECHARGE_WAIT_REG 	0xe8
#define DRAM_DIMM_STACK_REG 		0x108
#define DRAM_EXT_WR_MODE2_REG 		0x110
#define DRAM_EXT_WR_MODE1_REG 		0x118
#define DRAM_EXT_WR_MODE3_REG 		0x120
#define DRAM_WAIR_CONTROL_REG 		0x128
#define DRAM_RANK1_PRESENT_REG 		0x130
#define DRAM_CHANNEL_DISABLE_REG 	0x138
#define DRAM_SEL_LO_ADDR_BITS_REG 	0x140
#define DRAM_SW_DV_COUNT_REG 		0x1b0
#define DRAM_HW_DMUX_CLK_INV_REG 	0x1b8
#define DRAM_PAD_EN_CLK_INV_REG 	0x1c0
#define DRAM_DIMM_PRESENT_REG 		0x218
#define DRAM_FAILOVER_STATUS_REG 	0x220
#define DRAM_FAILOVER_MASK 		0x228


/* HW DEBUG */
#define DRAM_DBG_TRG_ENBL_REG 		0x230

/* ERROR Regs */
#define DRAM_ERROR_STATUS_REG 		0x280
#define DRAM_ERROR_ADDR_REG 		0x288
#define DRAM_ERROR_INJ_REG 		0x290
#define DRAM_ERROR_COUNTER_REG 		0x298
#define DRAM_ERROR_LOC_REG 		0x2a0

#define DRAM_ERROR_STATUS_INIT		0xfe00000000000000

/* Performance regs */
#define DRAM_PERF_CTL_REG 		0x400
#define DRAM_PERF_COUNT_REG 		0x408
#define	DRAM_PERF_CTL0			(DRAM_CSR_BASE + 0x0400)
#define	DRAM_PERF_COUNT0		(DRAM_CSR_BASE + 0x0408)
#define	DRAM_PERF_CTL1			(DRAM_CSR_BASE + 0x1400)
#define	DRAM_PERF_COUNT1		(DRAM_CSR_BASE + 0x1408)
#define	DRAM_PERF_CTL2			(DRAM_CSR_BASE + 0x2400)
#define	DRAM_PERF_COUNT2		(DRAM_CSR_BASE + 0x2408)
#define	DRAM_PERF_CTL3			(DRAM_CSR_BASE + 0x3400)
#define	DRAM_PERF_COUNT3		(DRAM_CSR_BASE + 0x3408)


/* Only 34 regs above are stored in scratch */ 
#define DRAM_SCRATCH_CSR_SIZE   	34 * 8	

#define DRAM_DIMM_INIT_REG 		0x1a0
#define DRAM_INIT_STATUS_REG 		0x210

#define DRAM_DIMM_INIT_ENBL     1
#define DRAM_DIMM_INIT_CKE_ENBL 2
#define DRAM_DIMM_INIT_CLK_ENBL 4

/*
 * DRAM Error Status Register (Count 4 Step 4096)
 */
#define	DRAM_ESR_OFFSET		DRAM_ERROR_STATUS_REG
#define	DRAM_ESR_BASE		(DRAM_BASE + DRAM_ESR_OFFSET)
#define	DRAM_ESR_MEU		(1 << 63)
#define	DRAM_ESR_MEC		(1 << 62)
#define	DRAM_ESR_DAC		(1 << 61)
#define	DRAM_ESR_DAU		(1 << 60)
#define	DRAM_ESR_DSC		(1 << 59)
#define	DRAM_ESR_DSU		(1 << 58)
#define	DRAM_ESR_DBU		(1 << 57)
#define	DRAM_ESR_SYND_MASK	0xffff
#define	DRAM_ESR_SYND_SHIFT	0

#define	DRAM_ESR_CE_BITS	(DRAM_ESR_MEC | DRAM_ESR_DAC | DRAM_ESR_DSC)
#define	DRAM_ESR_UE_BITS	(DRAM_ESR_MEU | DRAM_ESR_DAU | DRAM_ESR_DSU | DRAM_ESR_DBU)

/*
 * DRAM Error Address Register (Count 4 Step 4096)
 */
#define	DRAM_EAR_OFFSET		DRAM_ERROR_ADDR_REG
#define	DRAM_EAR_BASE		(DRAM_BASE + DRAM_EAR_OFFSET)

/*
 * DRAM Error injection register (Count 4 Step 4096)
 */
#define	DRAM_EIR_OFFSET		DRAM_ERROR_INJ_REG
#define	DRAM_EIR_BASE		(DRAM_BASE + DRAM_EIR_OFFSET)

/*
 * DRAM Error Counter Register (count 4 Step 4096)
 */
#define	DRAM_ECR_OFFSET		DRAM_ERROR_COUNTER_REG
#define	DRAM_ECR_BASE		(DRAM_BASE + DRAM_ECR_OFFSET)
#define	DRAM_ECR_ENB		(1 << 17)
#define	DRAM_ECR_VALID		(1 << 16)
#define	DRAM_ECR_COUNT_MASK	0xffff
#define	DRAM_ECR_COUNT_SHIFT	0

/*
 * DRAM Error Location Register (Count 4 Step 4096)
 */
#define	DRAM_ELR_OFFSET		DRAM_ERROR_LOC_REG
#define	DRAM_ELR_BASE		(DRAM_BASE + DRAM_ELR_OFFSET)
#define	DRAM_ELR_LOC_MASK	0xfffffffff

/*
 * DRAM Scrub Enable Register (Count 4 Step 4096)
 */
#define	DRAM_SCRUB_ENABLE_REG_ENAB	1


#ifdef __cplusplus
}
#endif

#endif /* _NIAGARA_DRAM_H */
