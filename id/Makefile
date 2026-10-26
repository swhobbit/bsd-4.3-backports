#
# Modified 2024-0924 by ahd@kewm.com (Drew Derbyshire) make gneeric and to use
# /usr/local as destination.
#

CFLAGS= -O ${INCPATH}
MAN=	id.0
MANSRC=	id.1
DESTDIR=/usr/local

all: id ${MAN}

id: id.o 
	cc -o id id.o 

id.o: id.c 
	cc ${CFLAGS} -c id.c

id.c:
	[ -f id.c ] && echo "id.c not built (already exists)"


id.1:
	[ -f id.1 ] && echo "id.1 not built (already exists)"

id.l: id.1
	cp id.1 id.l 

id.0: id.1
	# /usr/man/manroff ${MANSRC} > ${MAN}
	nroff -man -h ${MANSRC} > ${MAN}

install: all
	install -c -s id ${DESTDIR}/bin
	install -c -o root -g staff -m 444 ${MAN} ${DESTDIR}/man/cat1
	install -c -o root -g staff -m 444 ${MANSRC} ${DESTDIR}/man/man1
	install -c -o root -g staff -m 444 id.l ${DESTDIR}/man/man1

clean:
	rm -f *.o id ${MAN}
