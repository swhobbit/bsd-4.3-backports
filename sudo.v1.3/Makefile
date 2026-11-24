#*
#* CU sudo version 1.3 (based on Root Group sudo version 1.1)
#*
#* This software comes with no waranty whatsoever, use at your own risk.
#*
#* Please send bugs, changes, problems to sudo-bugs.cs.colorado.edu
#*

#*  sudo version 1.1 allows users to execute commands as root
#*  Copyright (C) 1991  The Root Group, Inc.
#*
#*  This program is free software; you can redistribute it and/or modify
#*  it under the terms of the GNU General Public License as published by
#*  the Free Software Foundation; either version 1, or (at your option)
#*  any later version.
#*
#*  This program is distributed in the hope that it will be useful,
#*  but WITHOUT ANY WARRANTY; without even the implied warranty of
#*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#*  GNU General Public License for more details.
#*
#*  You should have received a copy of the GNU General Public License
#*  along with this program; if not, write to the Free Software
#*  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#*
#
# Top level sudo Makefile which generates and calls Makefile.real
#    Make all architecture independent changes to Makefile.common
#    Make architecture dependent changes in the config directory
#

SHELL = /bin/sh
MAKE  = make

sudo		:
	@$(MAKE) all

.DEFAULT	:
	@if [ \( -z "$@" -o "$@" = ".DEFAULT" -o "$@" = "sudo" -o \
	      "$@" = "visudo" -o "$@" = "clean" -o "$@" = "all" -o \
	      "$@" = "install" -o "$@" = "install-all" -o \
	      "$@" = "install-sudoers" -o "$@" = "install-binaries" -o \
	      "$@" = "install-man" -o "$@" = "tags" -o "$@" = "dist" \
	      \) -a -f Makefile.real ]; then \
		make -f Makefile.real $@ ; \
	elif [ -f config/$@ ]; then \
		rm -f Makefile.real ; \
		cat config/$@ Makefile.common > Makefile.real ; \
		make -f Makefile.real ; \
	else \
		echo "Please choose one of the following OS types:" ; \
		echo "" ; \
		echo "generic		- generic system" ; \
		echo "sunos		- SunOS 4.x" ; \
		echo "solaris		- SunOS 5.x" ; \
		echo "solaris_gcc	- SunOS 5.x with gcc" ; \
		echo "hpux		- hpux 8.x or 9.x" ; \
		echo "bsd43		- 4.3 BSD" ; \
		echo "next		- NextStep 3.x" ; \
		echo "hpbsd		- Utah HPBSD 2" ; \
		echo "bsdi		- BSDI BSD/386" ; \
		echo "ultrix		- Ultrix 4.x" ; \
		echo "aix		- AIX 3.x" ; \
		echo "irix		- Irix 4.x" ; \
		echo "osf		- DEC OSF/1" ; \
		echo "ksros		- KSR OS" ; \
		echo "convex		- Convex OS 9.1 with gcc" ; \
		echo "linux		- Linux" ; \
		echo "linux_shadow	- Linux with shadow passwords" ; \
		echo "" ; \
		echo "and 'make os-type' where os-type is one of the above." ; \
		echo "" ; \
	fi

clean		:
	@$(MAKE) -f Makefile.common $@

dist		:
	@$(MAKE) -f Makefile.common $@

