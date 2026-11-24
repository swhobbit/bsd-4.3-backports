LIBRARY=-L../library -lkew
INCLUDES=-I.  -I../library
bin_PROGRAMS = rdate


rdate_SOURCES = rdate.c rdate.h tcpd.c udpc.c 

CFLAGS= -g $(INCLUDES)
DESTDIR=

.c.o: ; cc -c ${CFLAGS} -o $@ $*.c

all: rdate ${MAN}

rdate: rdate.o tcpc.o udpc.o
	: cc ${CFLAGS} -o rdate rdate.o tcpc.o udpc.o ${LIBRARY}
	cc ${CFLAGS} -o rdate rdate.o tcpc.o ${LIBRARY}

everything: clean all

udpc.c: udpc.o 

tcpc: tcpc.o 

rdate.o: rdate.c 

install: all 
	install -c -s rdate ${DESTDIR}/bin


clean:
	rm -f core *.bak *~ ._* *.o rdate *.1 *.l
