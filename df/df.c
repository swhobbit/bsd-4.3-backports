/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef lint
char copyright[] =
"@(#) Copyright (c) 1980 Regents of the University of California.\n\
 All rights reserved.\n";
#endif not lint

#ifndef lint
static char sccsid[] = "@(#)df.c	5.1 (Berkeley) 4/30/85";
#endif not lint

#define MEGABYTE	(1024*1024)	/* Report filesystem in MB */
#define KILOBYTE	1024		/* Report filesystem in KB */
#define AUTOSCALE	0		/* Autoscale filesytem report */

#include <sys/param.h>
#include <sys/fs.h>
#include <sys/stat.h>
#include <errno.h>

#include <stdio.h>
#include <fstab.h>
#include <mtab.h>

/*
 * df
 */
struct	mtab mtab[NMOUNT];
char	root[32];
char	*mpath();

pretty_print();

int	iflag;

static  fs_scale = KILOBYTE;

union {
	struct fs iu_fs;
	char dummy[SBSIZE];
} sb;
#define sblock sb.iu_fs

int	fi;
daddr_t	alloc();
char	*strcpy();



main(argc, argv)
	int argc;
	char **argv;
{
	int i;

	while (argc > 1 && argv[1][0]=='-') {
		switch (argv[1][1]) {

		case 'i':
			iflag++;
			break;

		case 'm':
			fs_scale = MEGABYTE;
			break;

		case 'h':
			fs_scale = AUTOSCALE;
			break;

		default:
			fprintf(stderr, "usage: df [ -i ] [ filsys... ]\n");
			exit(0);
		}
		argc--, argv++;
	}
	i = open("/etc/mtab", 0);
	if (i >= 0) {
		(void) read(i, (char *)mtab, sizeof (mtab));
		(void) close(i);
	}
	sync();

	printf("Filesystem ");
	switch (fs_scale) {
		case MEGABYTE:
			printf("1M-blocks");
			break;
	
		case KILOBYTE:
			printf("1K-blocks");
			break; 

		case AUTOSCALE:
			printf("     Size");
			break;

		default:
			abort();
	}

	printf("    used   avail capacity");
	if (iflag)
		printf(" iused   ifree  %%iused");
	printf("  Mounted on\n");
	if (argc <= 1) {
		struct fstab *fsp;

		if (setfsent() == 0)
			perror(FSTAB), exit(1);
		while (fsp = getfsent()) {
			if (strcmp(fsp->fs_type, FSTAB_RW) &&
			    strcmp(fsp->fs_type, FSTAB_RO) &&
			    strcmp(fsp->fs_type, FSTAB_RQ))
				continue;
			if (root[0] == 0)
				(void) strcpy(root, fsp->fs_spec);
			dfree(fsp->fs_spec, 1);
		}
		endfsent();
		exit(0);
	}
	for (i=1; i<argc; i++)
		dfree(argv[i], 0);
}

dfree(file, infsent)
	char *file;
	int infsent;
{
	long totalblks, availblks, avail, free, used;
	struct stat stbuf;
	struct fstab *fsp;

	if (stat(file, &stbuf) == 0 &&
	    (stbuf.st_mode&S_IFMT) != S_IFCHR &&
	    (stbuf.st_mode&S_IFMT) != S_IFBLK) {
		if (infsent) {
			fprintf(stderr, "%s: screwy /etc/fstab entry\n", file);
			return;
		}
		setfsent();
		while (fsp = getfsent()) {
			struct stat stb;

			if (stat(fsp->fs_spec, &stb) == 0 &&
			    stb.st_rdev == stbuf.st_dev) {
				file = fsp->fs_spec;
				endfsent();
				goto found;
			}
		}
		endfsent();
		fprintf(stderr, "%s: mounted on unknown device\n", file);
		return;
	}
found:
	fi = open(file, 0);
	if (fi < 0) {
		perror(file);
		return;
	}
	if (bread(SBLOCK, (char *)&sblock, SBSIZE) == 0) {
		(void) close(fi);
		return;
	}
	printf("%-12.12s", file);
	totalblks = sblock.fs_dsize;
	free = sblock.fs_cstotal.cs_nbfree * sblock.fs_frag +
	    sblock.fs_cstotal.cs_nffree;
	used = totalblks - free;
	availblks = totalblks * (100 - sblock.fs_minfree) / 100;
	avail = availblks > used ? availblks - used : 0;
	pretty_print(fs_scale, totalblks, sblock.fs_fsize);
	pretty_print(fs_scale, used, sblock.fs_fsize);
	pretty_print(fs_scale, avail, sblock.fs_fsize);
	printf("%6.0f%%",
	    availblks == 0 ? 0.0 : (double) used / (double) availblks * 100.0);
	if (iflag) {
		int inodes = sblock.fs_ncg * sblock.fs_ipg;
		used = inodes - sblock.fs_cstotal.cs_nifree;
		printf("%8ld%8ld%6.0f%% ", used, sblock.fs_cstotal.cs_nifree,
		    inodes == 0 ? 0.0 : (double)used / (double)inodes * 100.0);
	} else 
		printf("  ");
	printf("  %s\n", mpath(file));
	(void) close(fi);
}

long lseek();

bread(bno, buf, cnt)
	daddr_t bno;
	char *buf;
{
	int n;
	extern errno;

	(void) lseek(fi, (long)(bno * DEV_BSIZE), 0);
	if ((n=read(fi, buf, cnt)) != cnt) {
		/* probably a dismounted disk if errno == EIO */
		if (errno != EIO) {
			printf("\nread error bno = %ld\n", bno);
			printf("count = %d; errno = %d\n", n, errno);
		}
		return (0);
	}
	return (1);
}

/*
 * Given a name like /dev/rrp0h, returns the mounted path, like /usr.
 */
char *
mpath(file)
	char *file;
{
	register struct mtab *mp;

	if (eq(file, root))
		return ("/");
	for (mp = mtab; mp < mtab + NMOUNT; mp++)
		if (eq(file, mp->m_dname))
			return (mp->m_path);
	return "";
}

eq(f1, f2)
	char *f1, *f2;
{

	if (strncmp(f1, "/dev/", 5) == 0)
		f1 += 5;
	if (strncmp(f2, "/dev/", 5) == 0)
		f2 += 5;
	if (!strcmp(f1, f2))
		return (1);
	if (*f1 == 'r' && !strcmp(f1+1, f2))
		return (1);
	if (*f2 == 'r' && !strcmp(f1, f2+1))
		return (1);
	if (*f1 == 'r' && *f2 == 'r' && strcmp(f1+1, f2+1) == 0)
		return (1);
	return (0);
}

pretty_print(fs_scale, block_count, fssize)
	int fs_scale, block_count, fssize;
{
	char scale;

	block_count *= fssize;
	switch(fs_scale)
	{

		case MEGABYTE:
		case KILOBYTE:
			printf("%8d", block_count / fs_scale);
			break;

		case AUTOSCALE:
			if (block_count > (1024*1024*1024))
			{
				scale = 'G';
				block_count /= 1024*1024*1024;
			}
			else if (block_count > MEGABYTE)
			{
				scale = 'M';
				block_count /= MEGABYTE;
			}
			else 
			{
				scale = 'K';
				block_count /= KILOBYTE;
			}

			printf("%7d%c",block_count, scale);
			break;
	}
}
