#ifndef included_a_s_h
#define included_a_s_h

/* Copyright (c) 1990, Morgan Stanley Group Inc. */

/* @(#) $Id: s.h,v 1.6 1992/10/30 22:15:41 maus Exp $ */

#include "f.h"
#include <stdio.h>

#ifdef _AIX
#define Vol volatile
#include <sys/termio.h>
#define SH(x) sprintf(b,s,x)
#else
#define Vol
#include <sys/termios.h>
//#include <sys/filio.h>
#define SH(x) strlen(springf(b,s,x))
#endif

/* HP like AIS
 mmap?
 getrusage - times
 atanh acosh asinh
 ransom srandom - rand srand
*/

#endif
