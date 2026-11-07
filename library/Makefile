INCLUDES=-I.  -I../library
LIBRARY=-L. -lkew
CFLAGS=${INCLUDES} -O
DESTDIR=/usr/local
WRAPMAKE=$${PWD}/wrapmake $${PWD}/wrapmake.txt
MAKE=${WRAPMAKE}

HEADER_FILES=herror.h	kewstr.h	stdlib.h	unistd.h strdup.c

.c.o: ; cc -c ${CFLAGS} -o $@ $*.c

all: libkew.a wrapmake
	
test:	wrapmake wrapmake.txt
	ls -l wrapmake.*
	echo ${WRAPMAKE} wrapmake.txt innertest
	${WRAPMAKE} wrapmake.txt innertest

innertest:
	echo xxx="${xxx}" MFLAGSs="${MFLAGS}" __DATE__="${DATE}" __TIME__="${TIME}"

# Rebuild of live wrapmake will be forced at next build because
# first line removes its prerequisite object file
clean:
	rm -f *.o *.a *.bak wrapmake core
	ln -s wrapmake.sh wrapmake

install:	${DESTDIR}/include ${DESTDIR}/lib

libkew.a:	herror.o strcasecmp.o strerror.o strstr.o strdup.o
	ar cr $@ $?
	ranlib $@

wrapmake: wrapmake.o libkew.a Makefile
	rm -f wrapmake
	cc ${CFLAGS} -o $@ wrapmake.o ${LIBRARY} -L/usr/lib

${DESTDIR}/lib: libkew.a
	[ -d $@ ] || mkdir $@
	cp $? $@

${DESTDIR}/include: ${HEADER_FILES}
	[ -d $@ ] || mkdir $@
	cp $? $@
