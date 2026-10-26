#
# Modified 2024-0924 by ahd@kew.com (Drew Derbyshire) make gneeric and to use
# /usr/local as destination.
#

CFLAGS= -O ${INCPATH}
MAN=	xtitle.0
MANSRC=	xtitle.1
DESTDIR=/usr/local

all: xtitle ${MAN}

xtitle: xtitle.o strstr.o
	cc -o xtitle xtitle.o strstr.o

xtitle.o: xtitle.c 
	cc ${CFLAGS} -c xtitle.c

xtitle.c:
	@[ -f xtitle.c ] && echo "xtitle.c not built (already exists)"

strstr.o: strstr.c 
	cc ${CFLAGS} -c strstr.c

strstr.c:
	@[ -f strstr.c ] && echo "strstr.c not built (already exists)"


xtitle.1:
	@[ -f xtitle.1 ] && echo "xtitle.1 not built (already exists)"

xtitle.l: xtitle.1
	rm -f xtitle.l
	cp xtitle.1 xtitle.l 

xtitle.0: xtitle.1
	# /usr/man/manroff ${MANSRC} > ${MAN}
	nroff -man -h ${MANSRC} > ${MAN}

install: all
	install -c -s xtitle ${DESTDIR}/bin
	install -c -o root -g staff -m 444 ${MAN} ${DESTDIR}/man/cat1
	install -c -o root -g staff -m 444 ${MANSRC} ${DESTDIR}/man/man1
	install -c -o root -g staff -m 444 xtitle.l ${DESTDIR}/man/man1

clean:
	rm -f *.o xtitle ${MAN}
