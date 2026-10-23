
bin_PROGRAMS = udpc rdatet


rdate_SOURCES = rdate.c rdate.h

CFLAGS= -O
DESTDIR=

.c.o: ; cc -c ${CFLAGS} -o $@ $*.c

all: udpc rdatet ${MAN}

e: everything

everything: clean all



udpc.c: udpc.o 

rdatet: rdatet.o 
	cc ${CFLAGS} -o rdatet rdatet.o

udpc: udpc.o 
	cc ${CFLAGS} -o udpc udpc.o

rdate.o: rdate.c 
	cc ${CFLAGS} -c rdate.c

install: all 
	install -c -s rdatet ${DESTDIR}/bin


clean:
	rm -f *.o rdate rdatet udpc *.1 *.l
