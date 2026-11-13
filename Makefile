SUBDIRS=library	\
	bin	\
	date df	\
	host	\
	id	\
	less	\
	rdate	\
	resize	\
	tcsh	\
	top	\
	vim-3.7	\
	xtitle

ROOT_FILES= LICENSE Makefile README.md 
FULL_TAR=backup/43bsd_full_backport.tar
Z_FULL_TAR=${FULL_TAR}.Z
WRAPMAKE=$${PWD}/library/wrapmake $${PWD}/library/wrapmake.txt
MAKE=${WRAPMAKE}

build: all

clean install all: ${SUBDIRS} clean_root 
	cd library ; make wrapmake
	for i in ${SUBDIRS} ;	\
		do (cd $$i ;	\
		 echo ;	\
		 echo ">>> $@ in $$i" ;	\
		 ${WRAPMAKE} ${MFLAGS} $@ );	\
	   done

clean_root : 
	rm  -f *.bak

backup: backup_tar

tar:  clean full_tar baby_tars FRC

full_tar:	clean ${Z_FULL_TAR} FRC

backup_tar: clean ${Z_FULL_TAR} FRC
	[ -d backup ] || mkdir backup
	- mv backup/`basename ${Z_FULL_TAR}`.8 backup/`basename ${Z_FULL_TAR}`.9
	- mv backup/`basename ${Z_FULL_TAR}`.7 backup/`basename ${Z_FULL_TAR}`.8
	- mv backup/`basename ${Z_FULL_TAR}`.6 backup/`basename ${Z_FULL_TAR}`.7
	- mv backup/`basename ${Z_FULL_TAR}`.5 backup/`basename ${Z_FULL_TAR}`.6
	- mv backup/`basename ${Z_FULL_TAR}`.4 backup/`basename ${Z_FULL_TAR}`.5
	- mv backup/`basename ${Z_FULL_TAR}`.3 backup/`basename ${Z_FULL_TAR}`.4
	- mv backup/`basename ${Z_FULL_TAR}`.2 backup/`basename ${Z_FULL_TAR}`.3
	- mv backup/`basename ${Z_FULL_TAR}`.1 backup/`basename ${Z_FULL_TAR}`.2
	- mv backup/`basename ${Z_FULL_TAR}`   backup/`basename ${Z_FULL_TAR}`.1
	cp  ${Z_FULL_TAR} backup

${Z_FULL_TAR}:	${FULL_TAR}
	compress -f ${FULL_TAR}

${FULL_TAR}:	${SUBDIRS} ${ROOT_FILES} 
	tar cf ${FULL_TAR}  $? 

baby_tars: clean ${SUBDIRS} tar/43bsd_root.tar.Z
	for i in ${SUBDIRS}; do tar cvf tar/43bsd_$${i}.tar $${i} ; done

tar/43bsd_root.tar: ${ROOT_FILES}
	tar cf $@ ${ROOT_FILES}

tar/43bsd_root.tar.Z: tar/43bsd_root.tar
	compress -f $?

FRC:
	# Forced recompilation (make)
