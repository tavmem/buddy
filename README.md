The focus of this repository is on the earlist version that we could
find of the interpreter portion of the A+ system distributed by 
Morgan Stanley.  In particular, it shows the buddy space management
system that was eliminated in later versions, and shows more of the
coding style used by Arthur Whitney.

Note that this version is 32-bit, and dates from 4/30/1993.
A 64-bit version was not released as open source til 3/27/2008.

Why is this relevant?

1) "Notation as a tool of thought."  (Ken Iverson)
Arthur Whitney is a talented implementor of language interpreters, eg.,
his own version of Scheme, a port of IPSA APL to limited hardware, A+,
k, KSQL, q, and KDB+.  The notation he uses is key to that success.

2) The study of Domain Specific Languages:  Ostensibly Arthur uses C.
Actually, he uses the C preprocessor to create his own language.
I call it ATWC.

3) Mastery of q/KDB+:  A study of ATWC directly carries over to q/KDB+.
The style of using very short functions is key to successful q/KDB+.
Supposedly, Arthur never bothered to learn GDB (or other debugging tools
normally used with C).  You would not use such tools with q/KDB+ either.
Comments are sparse (or nonexistent).

4) Code as Poetry.  Read, study, and enjoy.
An extreme example is file a/b.c.  It conatins 2 versions of the buddy
memory allocation system.  The first is in 11 lines of ATWC.
The second is in well documented traditional C (almost 750 lines).

Why does the code compile on a 32-bit Linux, but not run?

Again, I think that is has to do with file a/b.c.  Arthur's version
of the buddy memory allocation system was tuned to Solaris on Sun 
workstattions. It would need to be rewritten to work with Linux on
Intel processors.

-------------------------------------------------------------------------

A+ and the A+ Reference Manual are Copyright Morgan Stanley Dean Witter &
Co.  They are distributed under the GNU General Public License and the GNU
Free Documentation License and available from http://www.aplusdev.org/.
See the file LICENSE and the appendix titled GNU Free Documentation
License of the reference manual regarding the terms under which A+
software and documentation is being made available.

