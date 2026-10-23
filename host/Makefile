
bin_PROGRAMS = host


host_SOURCES = host.c strcasecmp.c herror
MAN = host.1

CFLAGS= -g
DESTDIR=/usr/local

.c.o: ; cc -c ${CFLAGS} -o $@ $*.c

all: ${MAN} host 

e: everything

everything: clean all

host: host.o herror.o strcasecmp.o
	cc ${CFLAGS} -o $@ herror.o host.o strcasecmp.o

install: all 
	install -c -s host ${DESTDIR}/bin
	install -c -m 444 ${MAN} ${DESTDIR}/man/man1

clean:
	rm -f *.o host core

# herror.o:	herror.c
# strcasecmp.o:	strcasecmp.c
