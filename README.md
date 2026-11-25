# bsd-4.3-backports
Backports/recreations of modern utilities useful on emulated `BSD 4.3`
systems

- `date` sets the current date in the 21st century. 
  This version corrects the Y2K bug which prevents setting the current date being after 1999. This version also has a custom version of `strftime` to support the command `date +"format"` option.

  This is the only program in this collection which installs in its **original** location on `BSD 4.3` (to make accessible it at boot). 
- `df` displays free disk space.  The program is based on the version in the original `BSD 4.3` Distribution, but this supports both the `-h` and the `-m` options for better display formats.

  **Note**: `df` is best installed in `/usr/local/bin`, which in turn should be added to the front of your path.
- `host` Look up a an Internet host by name or IPv4 address.
- `id` Reports the current or specfied user name, numeric id, and the name & numbers of groups the user is member of.
- `less` (668) the improver pager to replace `more`.
- `rdate` Sets/adjusts the system time using the [Time protocol](https://www.rfc-editor.org/info/rfc868/).
- `resize` Updates the system's idea of the current session's screen size.
- `sudo` Executes single command as superuser, or (with the wrapper program `wrapsudo` to support the newer `-s` option) opens a shell as superuser.
- `tcsh` Enhanced csh which adds filename, command completion and command line editing concepts borrowed from the `TENEX` operating system. 

  (The `tcsh` command line supports for scrolling to previous commands in the history list. *Hallelujah!*)
- `top` displays sorted information about processes
- `xtitle` sets the window title text of modern terminal emulators (`xterm`, `MacOS Terminal`, `PuTTY` etc.) 

Most of these programs are backports of OSS programs written in 1980s or soon after, and each have their own specfic license.

Many programs (like `BSD 4.3` itself) are obsolete in modern
environments, but do the job in the target `BSD 4.3` environment. For example, `rdate` is an implementation of the simple [Time protocol](https://www.rfc-editor.org/info/rfc868/) with a coarse full second resolution. The Time Protocol was replaced by the more complex [NTP protocol](https://www.rfc-editor.org/info/rfc5905/) because of rdate's low resolution and no compensation for network lag. `rdate` *is* suitable for `BSD 4.3` on a simulated `VAX-11/780` when in 1986 the real machine had the clock set by an operator with suspect reflexes setting the time after looking at a wall clock of questionable accuracy.
