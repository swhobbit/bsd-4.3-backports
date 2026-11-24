%{
/*
 *  sudo version 1.1 allows users to execute commands as root
 *  Copyright (C) 1991  The Root Group, Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 1, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  If you make modifications to the source, we would be happy to have
 *  them to include in future releases.  Feel free to send them to:
 *      Jeff Nieusma                       nieusma@rootgroup.com
 *      3959 Arbol CT                      (303) 447-8093
 *      Boulder, CO 80301-1752             
 */
/*******************************************************************************
* visudo.yacc, sudo project
* David R. Hieb
* February 17, 1991
*
* Yacc Specification file for the visudo command in the sudo project.
*******************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/param.h>
#include "sudo.h"

extern int status;
extern int yyerrok, yylineno, err_line_no;

yyerror(s)
char *s;
{
/* we don't want any output here */
}

yywrap()
{
return(1);
}
%}

%start file				/* special start symbol */
%token <char_val> IDENT1		/* identifier type 1*/
%token <char_val> IDENT2		/* identifier type 2*/
%token <char_val> IDENT3		/* identifier type 3*/
%token <int_val>  COMMENT		/* comment and/or carriage return */
%token <int_val>  ERROR			/* error character(s) */
%token <int_val> ':' '=' ',' '!'	/* union member tokens */
%%
file		:	entry
		|	file entry
		;

entry		:	COMMENT
		|	error COMMENT
			{ yyerrok; if (status == 0) status = yylineno; }
		|	IDENT1 access_series COMMENT
		;

access_series	:	access_group
		|	access_series ':' access_group
		;

access_group	:	IDENT2 '=' cmnd_list
		;

cmnd_list	:	cmnd_type
		|	cmnd_list ',' cmnd_type
		;

cmnd_type	:	IDENT3
		|	'!' IDENT3
		|	IDENT2
		|	'!' IDENT2
		;
%%
