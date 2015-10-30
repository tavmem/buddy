#ifndef included_a_b_h
#define incleded_a_b_h

/* Copyright (c) 1990, Morgan Stanley Group, Inc */

/* @(#) $Id: b.h, v 1.7 1992/08/31 05:31:19 dff Exp $ */

/* header file inclusions */
#include <sys/types.h>

/* external macro declarations */
#define MD      31

/* external data declarations */
/* number of words in block of given scale */
extern u_long MZ[];

/* external function declarations */
/* allocate block of memory to hold the given number of words */
extern long *ma();              /* return pointer to allocated memory */

/* allocate block of memeory to hold the given number of bytes */
extern char *mab();             /* return the pointer to allocated memory */

/* free a previously allocated block of memory */
extern void mf();               /* does not return anything */

/* initialize the memory allocator */
extern void mi();               /* does not return anything */

/* coalesce free fragments into larger free fragments */
extern u_long mc();             /* returns scale of largest free block */

/* bring additional memory under managment */
extern u_long mb();             /* returns scale of largest block */

/* recompute the count of free blocks at each scale */
extern u_long *mz();            /* return a pointer to the counts */

/* function for adding more temporary workspace */
extern tmp();

/* A's error function */
extern err();

#endif
