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
k, KSQL, q, KDB+, and shakti.  The notation he uses is significant.

2) The study of Domain Specific Languages:  Ostensibly Arthur uses C.
Actually, he uses the C preprocessor to create a terse language of his
own.  The style is referred to as the "ATW_VERSION" in the file a/b.c.

3) A study of ATW-C directly carries over to k, q/KDB+, or shakti.
The style of using very short functions is helpful.  Supposedly, 
Arthur never bothered to learn GDB (or other debugging tools
normally used with C).  You would not use such tools with q/KDB+ 
either. Comments are sparse (or nonexistent).

4) Code as Poetry.  Read, study, and enjoy.
An extreme example of contrasting styles is contained in file a/b.c.
There are 2 versions of the buddy memory allocation system.  The 
"ATW_VERSION" has 11 lines.  The second is in well documented 
traditional C (almost 750 lines).

Why does the code compile on a 32-bit Linux, but not work? (See issues)

Again, it may have to do with file a/b.c.  The traditional C version in 
a/b.c has a comment stating that "these procedures depend critically on
the memory configuration of the computer performing these procedures".
The code in a/b.c is tuned for Solaris on Sun workstattions. It undoubtedly
needs modification to work with Linux or Windows or macOS on Intel processors.
Another strong possibility is that there are typos that remain (see partial
fix to issue 3).  This entire repository was keyed in from source documents.

-------------------------------------------------------------------------

A+ and the A+ Reference Manual are Copyright Morgan Stanley Dean Witter &
Co.  They are distributed under the GNU General Public License and the GNU
Free Documentation License and available from http://www.aplusdev.org/.
See the file LICENSE and the appendix titled GNU Free Documentation
License of the reference manual regarding the terms under which A+
software and documentation is being made available.

