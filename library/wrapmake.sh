#!/bin/sh

# *------------------------------------------------------------------- *
# *                         WRAPMAKE SH                                *
# *                                                                    *
# *       Fake WRAPMAKE program to invoke make (sans the true          *
# *       MAKEWRAP functionality) on BSD 4.3 the when the real         *
# *              program has been cleaned off the disk.                *
# *                                                                    *
# *               Date: 31 Oct 2026                                    *
# *             Author: ahd@kew.com (Drew Derbyshire)                  *
# *            Address: Kendra Electronic Wonderworks                  *
# *                     Kenmore, WA                                    *
# *------------------------------------------------------------------- *
echo "Using stand-in dummy scripts for $0"

# Drop options 
if [ $# -gt 0 ] ; then
	shift
fi
echo exec /bin/make "$@"
exec /bin/make "$@"
