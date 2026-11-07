.c.o: ; cc -c ${CFLAGS} $(INCLUDES) -o $@ $*.c

all: date

date:	date.o
	cc -o date $<

date.o: date.c

clean:
	rm -f date *.o *.bak *~
