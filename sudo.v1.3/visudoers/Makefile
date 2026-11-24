#*
#* CU sudo version 1.3 (based on Root Group sudo version 1.1)
#*
#* This software comes with no waranty whatsoever, use at your own risk.
#*
#* Please send bugs, changes, problems to sudo-bugs.cs.colorado.edu
#*

#*
#*  sudo version 1.1 allows users to execute commands as root
#*  Copyright (C) 1991  The Root Group, Inc.
#*
#*  This program is free software; you can redistribute it and/or modify
#*  it under the terms of the GNU General Public License as published by
#*  the Free Software Foundation; either version 1, or (at your option)
#*  any later version.
#*
#*  This program is distributed in the hope that it will be useful,
#*  but WITHOUT ANY WARRANTY; without even the implied warranty of
#*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#*  GNU General Public License for more details.
#*
#*  You should have received a copy of the GNU General Public License
#*  along with this program; if not, write to the Free Software
#*  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#*

#
#   This is the makefile for visudo
#

CCFLAGS  =
   LIBS  =-ly -ll
LDFLAGS  =
DEFINES  =
  CTAGS  = ctags

INCLUDES = sudo.h
   SRCS  = visudo.lex visudo.yacc visudo.c
   OBJS  = lex.yy.o y.tab.o visudo.o

visudo		:	$(OBJS)
	$(CC) $(CCFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

y.tab.o y.tab.h :       visudo.yacc sudo.h
	$(YACC) -d visudo.yacc
	$(CC) $(CCFLAGS) $(DEFINES) -c y.tab.c

lex.yy.o        :       visudo.lex y.tab.h sudo.h
	$(LEX) visudo.lex
	$(CC) $(CCFLAGS) $(DEFINES) -c lex.yy.c

visudo.o	:	visudo.c sudo.h
	$(CC) $(CCFLAGS) $(DEFINES) -c visudo.c

tags		:
	$(CTAGS) $(SRCS) $(INCLUDES)

clean		:
	-rm -f lex.yy.* y.tab.* *.o visudo core
