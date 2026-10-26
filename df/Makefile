#
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	@(#)Makefile	5.19 (Berkeley) 5/22/86
#
DESTDIR=/usr/local/
CFLAGS=	-O ${INCPATH}

# Programs that live in subdirectories, and have makefiles of their own.
#
SUBDIR=	


# Programs that run set-group-id operator
#
OPERATOR= df

BINS=	${OPERATOR} 

all:	${BINS}
	

${OPERATOR} :
	${CC} ${CFLAGS} -o $@ $@.c

install:	${OPERATOR}
	install -m 2755 -s df ${DESTDIR}/bin/df

clean:
	rm -f ${BINS} -g operator a.out core *.s *.o errs

depend: expr.c
	for i in ${BINS}; do \
	    cc -M ${INCPATH} $$i.c | sed 's/\.o//' | \
	    awk ' { if ($$1 != prev) \
		{ if (rec != "") print rec; rec = $$0; prev = $$1; } \
		else { if (length(rec $$2) > 78) { print rec; rec = $$0; } \
		else rec = rec " " $$2 } } \
		END { print rec } ' >> makedep; done
	echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	cp Makefile Makefile.bak
	ed - Makefile < eddep
	rm eddep makedep
	echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	echo '# see make depend above' >> Makefile

# DO NOT DELETE THIS LINE -- make depend uses it

df: df.c /usr/include/sys/param.h /usr/include/machine/machparam.h
df: /usr/include/signal.h /usr/include/sys/types.h /usr/include/sys/fs.h
df: /usr/include/sys/stat.h /usr/include/errno.h /usr/include/stdio.h
df: /usr/include/fstab.h /usr/include/mtab.h
