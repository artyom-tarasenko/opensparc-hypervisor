/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#pragma ident   "@(#)sram.h 1.1     04/08/02 SMI"

/*
 * SRAM definitions 
 */

#define SRAM_PROTOCOL_VERSION 1

#define SSI_BASE              0xfff0000000
#define SRAM_ADDR             ( SSI_BASE + 0x0000800000 )

#define SRAM_RESET_CTL_OFFSET		0x8
#define SRAM_RESET_CTL_LEN		0xc
#define SRAM_RESET_DATA_OFFSET		0x10
#define SRAM_RESET_DATA_LEN		0x14
#define SRAM_HOST_LOG_OFFSET		0x18
#define SRAM_HOST_LOG_LEN		0x1c
#define SRAM_HOST_LOG_INSERT		0x20
#define SRAM_HOST_LOG_MUTEX		0x24

#define SRAM_MEMBASE			0x28
#define SRAM_MEMSIZE			0x30
#define SRAM_PARTITION_DESC_OFFSET	0x38

/*
 * Format of SRAM LOG entries are:
 * byte 0 = cpu id
 * byte 1 = message len n
 * next n bytes = message
 *
 */

#define SRAM_LOG_HDR_SIZE               2
#define SRAM_MIN_MSG_SIZE               ( SRAM_LOG_HDR_SIZE + 1 )

/* define reset_control bits
 * bit 31    ACK/GO
 * bit 30    Error
 * bit 24-29 unused
 * bit 16-23 offset into data_blk for any data related to cmd (in 8 byte increments)
 * bit 0-15  cmd
*/
#define RESET_CTL_ACK_GO 31
#define RESET_CTL_ERROR  30
#define RESET_CTL_DATA   16
#define RESET_CTL_CMD     0
#define RESET_CMD_MASK	0xffff

#define RESET_CMD_NOP             0     
#define RESET_STATE_MACHINE       1		! debug cmd to start reset state machine
#define RESET_CMD_SIGNON      	  2
#define RESET_CMD_READ      	  3
#define RESET_CMD_WRITE      	  4
#define RESET_CMD_READ_ASI        5
#define RESET_CMD_WRITE_ASI       6
#define RESET_CMD_BOOTLOAD        7

#define RESET_CMD_START_CPU       8  
#define RESET_CMD_IDLE_CPU        9
#define RESET_CMD_RESUME_CPU      10

#define RESET_CMD_INIT_REGFILE    11		! all threads
#define RESET_CMD_INIT_CLOCK      12 		! boot core
#define RESET_CMD_CHANGE_SPEED	  13		 
#define RESET_CMD_DO_RESET        14
#define RESET_CMD_L1_BIST         15		! per core
#define RESET_CMD_L2_BIST         16		! boot core
#define RESET_CMD_INIT_TLB        17		! per core
#define RESET_CMD_INIT_DRAM_CTL0  18		! boot core
#define RESET_CMD_INIT_DRAM_CTL1  19		! boot core
#define RESET_CMD_INIT_DRAM_CTL2  20		! boot core
#define RESET_CMD_INIT_DRAM_CTL3  21		! boot core
#define RESET_CMD_INIT_LSU        22		! per core
#define RESET_CMD_INIT_JBUS_CFG   23		! boot core
#define RESET_CMD_INIT_L2_CTL_REG 24		! boot core
#define RESET_CMD_INIT_IOBRIDGE   25		! boot core
#define RESET_CMD_INIT_IOB	  26		! boot core
#define RESET_CMD_INIT_SSI	  27		! boot core
#define RESET_CMD_INIT_JBI	  28		! boot core
#define RESET_CMD_INIT_L2_ERR	  29		! boot core
#define RESET_CMD_INIT_INTR_QUEUE 30		! all threads
#define RESET_CMD_INIT_MEM        31
#define RESET_CMD_INIT_DRAM_RFR   32

#define RESET_CMD_INIT_ICACHE_TAG 33		! per core
#define RESET_CMD_INIT_DCACHE_TAG 34		! per core

#define RESET_CMD_INIT_ICACHE     35		! per core
#define RESET_CMD_INIT_DCACHE     36		! per core
#define RESET_CMD_INIT_L2CACHE    37		! boot core
#define RESET_CMD_INIT_UART       38            ! debug
#define RESET_CMD_COPY_RESET 	  39            ! copy reset code
#define RESET_CMD_RESET_JUMP	  40            ! make sram poller jump

#define RESET_CMD_START_MASTER    50
#define RESET_CMD_START_SLAVE     51

#define RESET_CMD_START_MASTER_ADDR    100		! debug - pass addr to jump to
#define RESET_CMD_START_SLAVE_ADDR     101		! debug - pass addr to jump to

#define RESET_CMD_ITLBFIXUP	102
#define RESET_CMD_DTLBFIXUP	103

#define RESET_CMD_COMPLETED       0xffff
