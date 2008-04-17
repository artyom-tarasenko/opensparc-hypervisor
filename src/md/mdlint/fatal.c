/*
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#pragma ident	"@(#)fatal.c	1.1	05/03/31 SMI"

#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "basics.h"

extern void vfatal(bool_t quit, char *fmt, va_list args);

void
fatal(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	vfatal(true, fmt, args);
	va_end(args);
}
