# bsd-4.3-backports
Back ports/recreations of modern utilities useful on emulated BSD 4.3 systems
- `date` sets the curremt date in the 21st century. This is the only program which exists on BSD 4.3. This version corrects the Y2K bug which only prevents setting the current date as being after 1999.
- `df` display free disk space
- `host` Look up a an Internet host by name or IPv4 address.
- `id` Report a user name, numeric id, and the name & numbers of groups the user is member of.
- `rdate` Sets/adjusts the system time using the Time protocol (RFC868).  
- `resize` Updates the system's idea of the current session's screen size.   
- `tcsh` Enhanced csh which adds filename and command completion and command line editing concepts borrowed from the TENEX operating system. (The command
line editing includes scrolling to previous commands in the history list.)
- `top` displays sorted information about processes
- `xtitle` sets the text bar text of modern terminal emulators (`xterm`,
`MacOS Terminal`, `PuTTY` etc.)

Most of these programs are backports of OSS programs writen in 1980s or
soon after. 

Many programs (like BSD 4.3 itself) are obsolete in modern
environments, but do the job in the target BSD 4.3 environment.

For example, `rdate` is an implementation of the RFC868 Time protocol
(with only full second resolution and no compensation for network lag,
it's been replaced by NTP), but it's suitable for a simulated
VAX-11/780 when the real machine had the clock set in the pre-NTP era
by an operator looking at a wall clock of questionable accuracy.
