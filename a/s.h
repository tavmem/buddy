#ifndef included_a_s_h
#define included_a_s_h

/* Copyright (c) 1990, Morgan Stanley Group Inc. */

/* @(#) $Id: s.h,v 1.6 1992/10/30 22:15:41 maus Exp $ */

#include "f.h"
#include <stdio.h>

#if defined(_AIX) || defined(HAVE_SVR4) || defined(__osf__) || defined(_HP)

# ifndef _HP
#  define Vol volatile
# else
#  define Vol
# endif

# include <sys/termio.h>
# define SH(x) (sprintf(b,s,x),strlen(b))
#else
# if defined(_LCC_LIB) || defined(__VISUAL_C_2_0__)
#  define Vol volatile
#  include <sys/termio.h>
#  define SH(x) ((unsigned long) (sprintf(b,s,x),strlen(b)))
# else
#  if defined(linux) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__APPLE__) || defined(__CYGWIN__)
#   define Vol
#   include <sys/termios.h>
#   define SH(x) (sprintf(b,s,x),strlen(b))
#  else
#   define Vol
#   include <sys/termios.h>
#   include <sys/filio.h>
#   define SH(x) strlen((DEV_STRARG)sprintf(b,s,x))
#  endif
# endif
#endif

/* HP like AIS
 mmap?
 getrusage - times
 atanh acosh asinh
 ransom srandom - rand srand
*/

#endif
