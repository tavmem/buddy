#ifndef included_a_u_h
#define included_a_u_h

/* Copyright (c) 1990, Morgan Stanley Group Inc. */

/* @(#) $Id: u.h,v 1.10 1992/10/30 22:15:41 maus Exp $ */

typedef long I;typedef double F;typedef char C;typedef unsigned char UC;
#define R return
#define Z static
#define H printf
#define NL H("\n")
#define CS(n,x) case n:x;break;
#define DO(n,x) {I i=0,_i=(n);for(;i<_i;++i){x;}}
#define PERR(s,x) {if((I)(x)==-1)R perr(s),0;}

#endif
