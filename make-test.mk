#************************************************************************
#	Package:	intensity
#	File:		make-test.mk
#	Purpose:	Making Automated Test Batteries for Project intensity
#	Author:		jromero
#************************************************************************
#	Copyright (C) 2023 
#	Jacob Romero, Creative Engineering Solutions, LLC
#	cesllc876@gmail.com
#
#	This program is free software; you can redistribute it
#	and/or modify it under the terms of the GNU General Public 
#	License as published by the Free Software Foundation, version 2.
#
#	This program is distributed in the hope that it will be
#	useful, but WITHOUT ANY WARRANTY; without even the implied 
#	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#	
#	See the GNU General Public License for more details.
#	
#	You should have received a copy of the GNU General Public
#	License along with this program; if not, write to:
#	The Free Software Foundation, Inc.
#	59 Temple Place, Suite 330
#	Boston, MA 02111-1307 USA
#************************************************************************
## https://stackoverflow.com/questions/12778430/creating-unit-testing-using-makefile
## https://www.brendanlong.com/unit-testing-c-with-check-and-autotools.html
#************************************************************************

CC=gcc
CFLAGS=-Wall -g
DEPS =	main.c \
	intensity.c intensity.h \
	circuit.c circuit.h \
		
OBJ = 	main.o \
	circuit.o \
	intensity.o \
	intensitytest.o \
	circuittest.o
	
DEBUG=-g
LIBS=-lcheck -lm -lpthread -lrt -lsubunit -lcheck_pic

#************************************************************************
##### AUTOMATED TEST BATTERIES ##### 
all: main circuit intensity intensitytest circuittest

## TARGETS
main: $(OBJ)
	$(CC) $(CFLAGS) -o main main.o $(LIBS)

circuit: $(OBJ)
	$(CC) $(CFLAGS) -o circuit circuit.o $(LIBS)

intensity: $(OBJ)
	$(CC) $(CFLAGS) -o intensity intensity.o $(LIBS)

intensitytest.o: $(DEPS) 
	checkmk intensitytest.check >intensitytest.c
	$(CC) $(CFLAGS) -c intensitytest.c	
	
intensitytest: intensitytest.o 
	$(CC) -o intensitytest intensitytest.o $(LIBS)

circuittest.o: $(DEPS) 
	checkmk circuittest.check >circuittest.c
	$(CC) $(CFLAGS) -c circuittest.c	
	
circuittest: circuittest.o 
	$(CC) -o circuittest circuittest.o $(LIBS)

clean:
	rm -f $(OBJ)
	
#************************************************************************
