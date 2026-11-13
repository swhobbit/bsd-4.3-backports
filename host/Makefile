INCLUDES=-I../library
MAKE=${MAKE}
CFLAGS=${CFLAGS} $(INCLUDES)
bin_PROGRAMS = host


host_SOURCES = host.c 
MAN = host.1

CFLAGS= -g ${INCPATH} -Llibrary
DESTDIR=/usr/local

.c.o: ; cc  -c ${CFLAGS} -o $@ $*.c

all: host  $(MAN)

e: everything

everything: clean all

host: host.o 
	cc ${CFLAGS} -o $@ host.o -L../library -lkew 

install: all 
	install -c -s host ${DESTDIR}/bin
	install -c -m 444 ${MAN} ${DESTDIR}/man/man1

clean:
	rm -f *.o *.bak host core
