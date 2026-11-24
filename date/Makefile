INCLUDES=-I. -I../library 
LIBRARY=-L../library -lkew
DESTDIR=/bin

.c.o: ; cc -g -c ${CFLAGS} ${INCLUDES} -o $@ $*.c

all: date test

date:	date.o ../library/libkew.a
	cc -g -o date date.o ${LIBRARY} 

date.o: date.c

test: date  test-date.sh
	date
	./test-date.sh
	./test-date.sh -u

../library/libkew.a: ../library/strftime.c
	( cd ../library ; make )

# Unlike most of the programs in this repository, we installed into the
# original location because one of its functions is set the system date 
# and the original binary could not set it in the 2000s.
install: all 
	install -c -s date ${DESTDIR}

clean:
	rm -f core date *.o *.bak *~
