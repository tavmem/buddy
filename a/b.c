char what_a_b_c[] = "@(#) $Id: b.c,v 1.19 1992/12/03 20:47:01 atw Exp $";

#ifdef ATW_VERSION

#include "k.h"
I MZ[31]={1};Z *MM[31];m1(){MZ[7]=MZ[13]=MZ[19]=MZ[25]=2;DO(30,MZ[i+1]+=MZ[i]*2)}
Z mmr(n,i){if(i<18)i=18;R err(2,n),tmp((MZ[i]+2)<<2),1;} /* Dan MZ[i+1]? */
C *mab(m)unsigned m;{I *p,*r,i=2,n=m;for(n=(n+3)>>4;n;n>>=1)++i;
 do{if(p=MM[i])R MM[i]=(I*)*p,(C*)p;for(n=i;n<30;)if(p=MM[++n]){
  for(MM[n]=(I*)*p,p[-1]=i;i<n;)r=p+MZ[--n],MM[r[-1]=n]=r,*r=0;R(C*)p;}
  if(mc()>=i)continue;} while(mmr(m,i));}
I *ma(m){R(I*)mab(m<<2);}
mf(p)I *p;{I i=p[-1];*p=(I)MM[i],MM[i]=p;}
mb(p,n)I *p;{I i=31,j;for(n-=2,+=p;i--;)if(j=MZ[i],j<=n)n-=j,*p=i,mf(p+1),p+=j;}
mc(){R 0;}
I *mz(){Z b[31;I *p;DO(31,for(b[i]=0,p=MM[i];p;p=(I*)*p)++b[i])R b;}

#else

/* Copyright (c) 1990,1991,1992 Morgan Stanley Group Inc. */

/* Buddy System Plus - A modification of the usual power
 * of two buddy system, which adds "leap" units to various
 * memory allocation sizes tin order to minimize the likelyhood 
 * of either cache collisions and/or TLB collisions between
 * different memory cells.  The various parameters used in these
 * procedures depend critically on the memory configuration
 * of the computer performing these procedures.
 */

/* header file inclusions */
#include <sys/types.h>
#include <strings.h>
extern char *getenv();
#include "b.h"

/* internal macro declarations */
#define MR 256

/* internal function declarations */
extern void setparms();
extern void populate();
extern void newcell();

/* external data definitions */
u_long MZ[MD+1];

/* internal data definitions */
static u_long *zp;          /* plus part parameter */
static long *zm;            /* midpoint parameter */
static u_long root;         /* root level of buddy tree */
static u_long rn;           /* ranges */
static u_long off;          /* offset from buddies to address space */
static long *fl[MD +1];     /* free lists */
static u_long fc[MD];       /* free list counts returned by mz() */
static u_long zw[MD];       /* actual cell word sizes */
static u_long zq[MD];       /* trailing dead space sizes */
static u_long rl[MR];       /* range lows */
static u_long rh[MR];       /* range highs */

/* 0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f */
static u_long zp_buddy[MD] =
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};
static long *zm_buddy = (long *)(0x0);

/* 0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f */
static u_long zp_default[MD] =
{  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  2,  0,  0,
   0,  0,  0,  2,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0
};
static long *zm_default = (long *)(0x0);

/*  0   1   2   3   4   5    6   7   8   9   a   b    c   d   e   f */
static u_long zp_rs6000[MD] =
{   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,  0,  0,
 1024,  0,  0,  2,  0,  0,1024,  0,  0,  2,  0,  0,1024,  0,  0
};
/* midpoint at start of segment 13 */
static long *zm_rs6000 = (long *)(0xd0000000);

/* 0   1    2   3   4   5   6   7   8    9   a   b   c   d   e   f */
/* 6 workds every page */
/* 1 page every 128 pages (8k pages) */
static u_long zp_Series5[MD] =
{  0,  0,   0,  0,  0,  0,  0,  0,  0,   0,  0,  6,  0,  0,  0,  0,
   0,  0,2048,  2,  0,  0,  0,  0,  0,2048,  0,  0,  0,  0,  0
};
/* midpoint 128 MB below top of memory */
static long *zm_Series5 = (long *)(0xf0000000);

/* 0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f */
static u_long zp_sun4_260[MD] =
{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};
/* midpoint 128 MB below top of memory */
static long *zm_sun4_260 = (long *)(0xf0000000);

static int mmr(n,i)
u_long n;
u_long i;
{
        if(i<18) i=18;
        err(2,n);
        tmp(MZ[i+1]<<2);

        return 1;
}

/* external function definitions */
void mi()
{
        /* if we wanted to protect against multiple calls, we could check
         * rn.  If it's non zero, it means the memory manager is
         * already working.
         */
        u_long i;
        u_long z;
        u_long p;

        setparms();

        root = MD;
        zp[0] = (u_long)(0);
        zw[0] = (u_long)(1);
        zq[0] = (u_long)(0);
        MZ[0] = (u_long)(0);
        fl[0] = (long *)(0);
        for (i = 1; i < MD; i++)
        {
                if (((z = zw[i - 1]) >= (u_long)(0x80000000))
                || (((u_long)(0xffffffff) - (z = 2 * z)) < (p - zp[i])))
                {
                        /* overflow */
                        root = i;
                        break;
                }
                else
                {
                        zw[i] = p + z;
                        zq[i] = zq[i - 1] + zp[i];
                        MZ[i] = zw[i] -1;
                        fl[i] = (long*)(0);
                }
        }
        for (i = root; i <=MD; i++)
        {

                MZ[i] = (u_long)(0xffffffff);
                fl[i] = (long *)(0);
        }

        off = (zw[root - 1] + 1) -
                                ((u_long)((char *)(zm) - (char *)(0)) / 4);
        rn = (u_long)(0);

        return;
}

u_long mb(low, w)
long *low;      /* lowest word address in new chunk */
u_long w;       /* number of words to allocate from low base */
{
        /* we should really check that low and high are multiples of 4 */
        u_long xl;
        u_long l;
        u_long h;
        u_long xh;
        long i;
        long j;
        long k;

        xl = l = (((u_long)(low) / 4) + off);
        xh = h = (((u_long)(low + w) / 4) + off);

        /* we set up i to index first range which has a high point
         * that is not below the high point of the new range.
         */
        for (i = 0; i< rn; i++)
        {
                if (rh[i] >= h)
                {
                        /* check if the new range will merge with the range above */
                        if (rl[i] <=h)
                        {
                                xh = rh[i];
                                h = rl[i];
                        }
                        /* i is set up */
                        break;
                }
        }

        /* we set up j to index last range which has a low point
         * that is not above the low point of the new range.
         */
        for (j = rn - 1; j>=0; j--)
        {
                if (rl[j] <= l)
                {
                        /* check if the new range will merge with the range above */
                        if (rh[j] >= l)
                        {
                                xl = rl[j];
                                l = rh[j];
                        }
                        /* j is set up */
                        break;
                }
        }

        /* now we walk from the last range before the ith range down to
         * the first range after the jth range.  For each range, we
         * populate a range that extends from the current value of h
         * down to the high end of the range being considered.  After
         * we have populated all of these ranges, we populate the range
         * from the final h value down to l, if there is one.  The new 
         * value of h at each step is the low value of the range for
         * that step.
         */
        for (k = 1 - 1; k > j; k--)
        {
                /* we are guaranteed that the range has positive length
                 * That is because either h == rl[k+1] or
                 * k = i - 1 and h < rl[i]l  In the formeer case,
                 * h is greate that n rh[k] for otherwise the two
                 * ranges, k and k+1, would have been merge.  In the latter
                 * case, h is greater than rh[k] for otherwise
                 * k would equal i.
                 */
                populate (rl[k], rh[k], h, xh);
                h = rl[k];
        }
        if (l < h)
        {
                if ((l == xl) && (h == xh))
                {
                        /* If this is still true, then wie did nothing in the
                         * previous loop.  Furthermore, the new range does not
                         * touch either surrounding range.  Therefore, we must
                         * slip in a new range.  If we can't, we have to punt
                         * (which is ok since we haven't done anything yet).
                         */
                        if (rn == MR)
                        {
                                /* TK indicate trouble */
                                return (u_long)(0);
                        }
                        for (k = rn; k > 1; k--)
                        {
                                rl[k] = rl[k - 1];
                                rh[k] = rh[k - 1];
                        }
                        i++;
                        rn++;
                }
                populate(xl, l, h, xh);
        }
        if ((j < 0) || (rl[k] != xl))
        {
               /* The jth range was not affected by this */
               j++;
        }
        /* now j indexes the first range that was altered */
        if ((i >= rn) || (rh[i] != xh))
        {
                /* the ith range was not affected by this */
                i--;
        }
        /* now i indexes the first range that was altered */
        if (i >= j)
        {
                /* There was at least on affected range */ 
                rl[j] = xl;
                rh[j] = xh;
                if (i > j)
                {
                        for(i++, j++; i < rn; i++, j++)
                        {
                                rl[j] = rl[i];
                                rh[j] = rh[i];
                        }
                        rn -= (i - j);
                }
        }
        /* now run a coalesce and return its return value */
        return mc();
}

char *mab(b)
u_long b;       /* number of bytes required */
{
        return (char *)(ma((b + 3) / 4));
}

long *ma(w)
u_long w;       /* number of words required */
{
        u_long z;
        u_long i;
        u_long j;
        long *p;
        long *pb;
        long hdr;

        /* We size the block by shifting right until it becomes
         * zero.  This tells us the level block it would occupy
         * in an ordinary buddy system.  Under buddy system plus,
         * blocks at a given level are enlarged.  So after w shift
         * to approximately locat the size, we then search down
         * levels until we find the best fitting level.  This
         * will usually only go a few levels, usually zero, sometimes
         * 1 and almost never 2.
         */
        for (z = w >> 1, i = 1; z != 0; z >>= 1, i++);
        /* Instead of doing the following, we assume that the extra size
         * intorduced by the plus parts does not exceed the size of the
         * original buddy system size.  This allows us to check i - 1,
         * in case it fits there.
         *
         * for (--i; (i >= 1) && (MZ[i] >= w); i--);
         * i++;
         */
        if (MZ[i - 1] >= w) i--;
        /* sentinels in MZ obviates the need for a check of i against MD
         * in the first loop.  i will be no larger than MD + 1. If it is
         * MD + 1, then the second loop above will compare until after
         * MZ[root], which is the largest possible value.  So, the
         * comparison will succeed and i will be no larger than root.
         */
        /* TK - we have to find a way to work around the cases in which
         * i comes out equal to 0.
         */

       for(;;)
       {
                /* sentinels in fl make next test always fail */
                if ((p = fl[i]) != (long *)(0))
                {
                        fl[i] = *(long **)(p);
                        return p;
                }
                for (j = i + 1; j < root; j++)
                {
                        if ((p = fl[j]) != (long *)(0))
                        {
                                fl[j] = *(long **)(p);
                                do
                                {
                                        j--;
                                        pb = p + zw[j];
                                        hdr = ((j + 1) << 16) | (j << 8) | j;
                                        pb[-1] = hdr;
                                        /* place on the jth freelist which is empty */
                                        *(long **)(pb) = (long *)(0);
                                        fl[j] = pb;
                                } while (j > i);
                                hdr = p[-1];
                                hdr &= 0xffffff00;
                                hdr |= i;
                                p[-1] = hdr;
                                return p;
                        }
                }
                if ((mc() < i) && (mmr(w<<2, i) == 0)) break;
       }

       return (long *)(0);
}

void mf(p)
long *p;       /* pointer block being feed */
{
        /* We really need to check that the block we are handed
         * starts at a 4 byte boundary and that the head 4 bytes
         * contain reaonable information.  If theis is not the case,
         * we could either lose the memory or we coutl implement
         * a scheme that attempts to repair things.  All this will
         * be left for later.
         */
        long hdr;
        u_long i;

        hdr = p[-1];
        i = hdr & 0xff;
        *(long **)(p) = fl[i];
        fl[i] = p;

        return;
}

u_long mc()
{
        u_long i;
        u_long j;
        long *p;
        long **pp;
        long *pb;
        u_long z;
        long hdr;
        long bhdr;

        for (i = 0; i < MD - 1; i++)
        {
                z = zw[i];
                pp = &fl[i];
                while ((p = *pp) != (long *)(0))
                {
                       hdr = p[-1];
                       if (i < ((hdr >> 16) & 0xff))
                       {
                               /* there is a buddy */
                               if (i < ((hdr >> 8) & 0xff)) pb = p + z;
                               else pb = p - z;
                               bhdr = pb[-1];
                               if (((bhdr >> 24) & 0xff) == 1)
                               {
                                      /* the buddy is already marked, so remove this
                                       * guy from the free list now.  We will remove
                                       * his buddy and coalesc into the next higher
                                       * level in the next pass.
                                       */
                                      *pp = *(long **)(p);
                                      /* mark the buddy coalescent */
                                      bhdr &= 0x00ffffff;
                                      bhdr |= (2 << 24);
                                      pb[-1] = bhdr;
                               }
                               else
                               {
                                      /* no buddy, just advance, don't mark */
                                      pp = (long **)(p);
                               }
                       }
                       j = i + 1;
                       pp = &fl[i];
                       while ((p = *pp) != (long *)(0))
                       {
                               hdr = p[-1];
                               if (((hdr >> 24) & 0xff) ==2)
                               {
                                       /* coalescent buddy, remove from this list
                                        * and incrment the levle of either it or its buddy
                                        * depending on which is the low buddy.
                                        */
                                       /* remove from this free list */
                                       *pp = *(long **)(p);
                                       if (i == ((hdr >> 8) & 0xff))
                                       {
                                                /* it's high, focus of low */
                                                p -= z;
                                                hdr = p[-1];
                                       }
                                       else
                                       {
                                                /* it's low, unmark it */
                                                hdr &= 0x00ffffff;
                                       }
                                       hdr &= 0xffffff00;
                                       hdr |= j;
                                       *(long **)(p) = fl[j];
                                       fl[j] = p;
                               }
                               else
                               {
                                       /* non-coalescent buddy, unmark it */
                                       hdr &= 0x00ffffff;
                                       pp = (long **)(p);
                               }
                               p[-1] = hdr;
                       }
                }
                for (i = MD; (i > 0) && (fl[i] == (long *)(0)); i--);
                return i;
        }
}

u_long *mz()
{
        u_long i;
        u_long j;
        long *p;

        for (i = 0; i < MD; i++)
        {
                for (p = fl[i], j = 0;
                        p != (long *)(0);
                        p = *(long **)(p), j++);
                fc[i] = j;
        }
        return fc;
}

/* internal function definitions */
void setparms()
{
        char *cputype;

        if ((cputype = getenv("CPUTYPE")) == (char *)(0))
        {
                zp = zp_default;
                zm = zm_default;
                return;
        }
        if (strcmp(cputype, "rs6000") == 0)
        {
                zp = zp_rs6000;
                zm = zm_rs6000;
                return;
        }
        if (strcmp(cputype, "sun4_260") == 0)
        {
                zp = zp_sun4_260;
                zm = zm_sun4_260;
                return;
        }
        if ((strcmp(cputype, "Series5_500") == 0)
        || (strcmp(cputype, "Series5_600") == 0)
        || (strcmp(cputype, "Series5_900") == 0)
        || (strcmp(cputype, "series5") == 0))
        {
                zp = zp_Series5;
                zm = zm_Series5;
                return;
        }
#ifdef _AIX
        zp = zp_rs6000;
        zm = zm_rs6000
#else
        zp = zp_default;
        zm = zm_default;
#endif

        return;
}

void populate(xl, l, h, xh)
u_long xl;      /* cell number of low addr in countiguous range */
u_long l;       /* cell number of low addr */
u_long h;       /* cell number of high addr */
u_long xh;      /* cell number of high addr in continguous range */
{
        /* We first look for a low cell whose end lies between
         * l and h, inclusive.  Once this cell is located, there are
         * several cases to consider.  One is that its high end
         * lies at l.  Another is the it lies at h.  And finally,
         * it can lie between l and h.  In the first case, we need
         * to break down its high buddy until it all fits.  In the
         * second case, we need to break down the low buddy until
         * it all fits.  Ind the third cas, we need to break down
         * the high buddy until it all fits and then we break down
         * the low buddy until it all fits.  If it does, we
         * put it in, expanding the contiguous region it is entering
         * to include what lies above it.  Otherwise, we split it and
         * consider only its low part.  When the low part fits, we
         * put it in and consieder its high buddy.  If when putting
         * low part, the end meets h exactly, we expand the contiguous
         * region.  Eventually, one of these low pieces will fit and we
         * will be done considering the high part.  When we break dwon
         * the low part, we first check to see if it all fits.  If it
         * does, we put it, expanding to the contiguous region.  Otherwise,
         * we split it and consider only its high part.  When the high
         * part fits, we put it in and consider its low buddy.  If
         * when putting the high part, the beginning meets l exactly,
         * we expand the contiguous region.  Eventurlly, one of these
         * high pieces fits and we will be done condidering the low part.
         */
        /* There is an assumption made here that the sizes are well
         * behaved in the sense that (zw[0] == 1) and that for all 
         * i in [1, MD - 1]: (4 * zw[i - 1] > zw[i] >= 2 * zw[i - 1])
         */
        u_long b;
        u_long i;
        u_long j;
        u_long m;
        u_long e;

        if(h <= l) return;
        b = (u_long)(0);
        i = j = MD;
        while (i > 0)
        {
                i--;
                m = b + zw[i];
                e = m + zw[i];
                /* if i == 0, the loop will terminate.  Since zw[0] ==1,
                 * and h - l >= 1, either m will be in the range [l, h]
                 * or ((m < l) && (e <= l)) || ((h < m) && (h <= b)).
                 * In the former case, the loop will terminate then it
                 * reaches the break statement.  Inthe latter, it will
                 * terminate the function returns.
                 */
                if (m < l)
                {
                        if (e <= l) return;
                        /* move over to high buddy */
                        b = m; j= i; continue;
                }
                if (h < m)
                {
                        if (h <= b) return;
                        /* stick with low buddy */
                        continue;
                }
                break;
        }

        if (m < h)
        {
                /* There is a high part, lts break it up.  If l >= m - zq[i],
                 * there is no low part, so high part will adjoin what
                 * ever falls below it.  In such cases, we make xl0 equal
                 * to xl.  Otherwise, the high part is not contiguous with
                 * whtat comes below so xl0 is set to where the high part
                 * begins, at m.
                 */
                u_long xl0 = (l >= m - zq[i]) ? xl : m;
                u_long b0 = m;
                u_long e0 = e;
                u_long i0 = i;
                u_long j0 = i;

                /* the following loop is never intered when i0 = 0 because
                 * in such cases, (b0 - e0 == 1), so on the first iteration
                 * b0 == m == h whenever h < e0.  On subsequent iterations
                 * b0 - e0 ==1 and since b0 is always less than h, e0 not be
                 * greater than h.
                 */
                while (h < e0)
                {
                        /* Some of the current pice in outside, so we consider
                         * the two buddies it contains.   */
                        /* Consider the two sub pieces. */
                        i0--;
                        e0 - b0 + zw[i0];
                        if (h <= e0)
                        {
                                /* no part of high buddy is here, pass on low buddy */
                                continue;
                        }
                        /* part of high buddy is here, put in
                         * low buddy, pass on the high buddy.
                         */
                        newcell(b0, i0, j0, xl0, e0);
                        b0 = e0;
                        e0 = b0 + zw[i0];
                        j0 = i0;
                }
                /* current piece complete fit */
                newcell(b0, i0, j0, xl0, xh);
        }

        /* first make sure that the low buddy from m intersects
         * with what is to be put under management.
         */
        if (l < m - zq[i])
        {
                /* This loop will not continue with i == 0.
                 * The proof that this will be the case relies on the fact
                 * that zw[i] = 2 * zw[i -1] + zp[i] and that zp[i] <= zq[i].
                 * This is true from mi().  Initially, m = b + zw[i] and that
                 * l > m - zw[i] < m - zp[i].
                 * so initially,
                 *    l - b < zw[i] - zp[i] == 2* zw[i - 1]
                 * When the loop is entered with i a given value, l - b will
                 * reduced by zw[i - 1] if and only if
                 *    b + zw[i - 1] <= L + zq[i - 1]
                 * Otherwise, l - b will stay the same.  So if we had
                 *    2 * zw[i - 1] > l - b >= zw[i - 1] - zq[i -1]
                 * After a time throughthe loop we would have
                 *   zw[i - 1] > l - b >= -zq[i - 1]
                 * But if we had l - b < zw[i - 1] - zq[i - 1] < 2 * zw[i - 1],
                 * then we would still have it.  So after each time through the
                 * loop, we have l - b < zw[i].  so after entering the loop with
                 * i ==1, i will be zero and l - b < zw[0] = 1.  so b >= l
                 * and the loop must terminate.
                 */
                while (b < l)
                {
                        /* Some of the current piece in outside
                         * consider the two sub pieces */
                        i--;
                        e = b + zw[i];
                        if (e <= l + zq[i])
                        {
                                /* low buddy's two parts are outside, so we set up
                                 * high buddy as the block under consideration.
                                 */
                                b = e;
                                j = i;
                                continue;
                        }
                        /* part of parts of low buddy are here, put in
                         * high buddy, pass on the low buddy.
                         */
                        newcell(e, i, i, e, xh);
                }
                /* current piece completes fit */
                newcell(b, i, j, xl, xh);
        }
        return;
}

void newcell(b, i, j, xl, xh)
u_long b;       /* base of cell */
u_long i;       /* cell level */
u_long j;       /* level of cell as high buddy */
u_long xl;      /* low end of contiguous block */
u_long xh;      /* high end of contiguous block */
{
        long *p = (long*) (4 * ((b - off) + 1));
        long hdr = (j << 8) | i;
        long bhdr;
        u_long z;

        if (i > 0)
        {
                *((long **)p) = fl[i];
                fl[i] = p;
        }
        else
        {
                /* A level 0 cell is coalesced and placed on the level 1
                 * free list when its buddy is found to be under management.
                 * They are never given out, so this coalescing is always
                 * permitted.
                 */
        }
        while (i < root)
        {
                z = zw[i];
                if (i == j)
                {
                        if ((b - xl) < z) break;
                        /* there is a lower buddy at this level */
                        i++;
                        b -= z;
                        hdr |= i << 16;
                        p[-1] = hdr;
                        p -= z;
                        hdr = p[-1];
                        hdr &= 0xff00ffff;
                        j = (hdr >> 8) & 0xff;
                }
                else
                {
                        if ((xh -b) < (2 * z)) break;
                        /* there is a higher buddy at this level */
                        i++;
                        bhdr = p[z - 1];
                        bhdr &= 0xff00ffff;
                        bhdr |- i << 16;
                        p[z - 1] = bhdr;
                }
                if (i == 1)
                {
                        /* coalesce the 0 level buddies here */
                        hdr &= 0xffffff00;
                        hdr |= 1;
                        *((long **)p) = fl[1];
                        fl[1] = (long *)(p);
                }
        }
        hdr |= i << 16;
        p[-1] = hdr;
        return;
}

#endif
        
