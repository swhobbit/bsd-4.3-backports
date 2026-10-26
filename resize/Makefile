#
# @(#)Makefile  1.1 (2.11BSD) 2020/3/23
#

CFLAGS= -O ${INCPATH}
SEPFLAG= -i
MANSRC=	resize.1
MAN=resize.0
DESTDIR=/usr/local

all: resize ${MAN}

resize: resize.o 
	cc -i -o resize resize.o -lcurses -ltermcap

resize.o: resize.c 
	cc ${CFLAGS} -c resize.c

resize.0: resize.1
	nroff -man -h  ${MANSRC} > ${MAN}

install: all
	install -c -s resize ${DESTDIR}/bin
	install -c -o root -g staff -m 444 ${MANSRC} ${DESTDIR}/man/man1

clean:
	rm -f resize.o psdb.o resize ${MAN}
