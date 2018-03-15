The focus of this repository is the version of the interpreter
portion of the A+ system distributed by Morgan Stanley that
existed when Arthur Whitney left MS (to cofound Kx Systems).
In particular, it shows the buddy space management system that
was eliminated in later versions, and shows more of Arthur's
unique coding style.

Note that this version is 32-bit, and dates from 4/30/1993.
An open source 64-bit version was not released til 3/27/2008.

Why is this relevant?

1) "Notation as a tool of thought" (Ken Iverson).
Arthur Whitney is a talented implementor of computer languages, eg.,
a version of Scheme, a port of IPSA APL to limited hardware, A+,
k, KSQL, q, and KDB+.  The notation he uses is significant.

2) The study of Domain Specific Languages:  Ostensibly Arthur uses C.
Actually, he uses the C preprocessor to create a terse language of his
own.  I call it ATWC.

3) Mastery of q/KDB+:  A study of ATWC directly carries over to q/KDB+.
The style of using very short functions is helpful in successful q/KDB+.
Supposedly, Arthur never bothered to learn GDB (or other debugging tools
normally used with C).  You would not use such tools with q/KDB+ either.
Comments are sparse (or nonexistent).

4) Code as Poetry.  Read, study, and enjoy.
An extreme example is file a/b.c.  It conatins 2 versions of the buddy
memory allocation system.  The first is in 11 lines of ATWC.
The second is in well documented traditional C (almost 750 lines).

Why does the code compile on a 32-bit Linux, but not work? (See issues)

Again, it may have to do with file a/b.c.  Both versions of the code in
a/b.c are tuned for Solaris on Sun workstattions. The code may
neeed modification to work with Linux on Intel processors.

-------------------------------------------------------------------------

A+ and the A+ Reference Manual are Copyright Morgan Stanley Dean Witter &
Co.  They are distributed under the GNU General Public License and the GNU
Free Documentation License and available from http://www.aplusdev.org/.
See the file LICENSE and the appendix titled GNU Free Documentation
License of the reference manual regarding the terms under which A+
software and documentation is being made available.

