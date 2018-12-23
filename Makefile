######################################################################
##        Copyright (c) 2016 Carsten Wulff Software, Norway 
## ###################################################################
## Created       : wulff at 2016-1-29
## ###################################################################
##   This program is free software: you can redistribute it and/or modify
##   it under the terms of the GNU General Public License as published by
##   the Free Software Foundation, either version 3 of the License, or
##   (at your option) any later version.
## 
##   This program is distributed in the hope that it will be useful,
##   but WITHOUT ANY WARRANTY; without even the implied warranty of
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##   GNU General Public License for more details.
## 
##   You should have received a copy of the GNU General Public License
##   along with this program.  If not, see <http://www.gnu.org/licenses/>.
######################################################################

VERSION=0.1.0

PROG_NAME = cic2verilog

#- Figure out which platform we're running on
ifeq ($(OS),Windows_NT)
	#- Not compatible with windows yet
OSNAME=Windows
OSBIN=windows
GDS3D=WINDOWS
else
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
OSNAME=macOS
OSBIN=darwin
GDS3D=GDS3D/mac/GDS3D.app/Contents/MacOS/GDS3D
endif
ifeq ($(UNAME_S),Linux)
OSNAME=Linux
OSBIN=linux
GDS3D=GDS3D/linux/GDS3D
endif
endif

CICDIR = ../../ciccreator

ifeq ($(UNAME_S),Darwin)
PROG=time ../bin/${OSBIN}/${PROG_NAME}.app/Contents/MacOS/${PROG_NAME}
else
PROG= time ../bin/${OSBIN}/${PROG_NAME}
endif

ifeq ($(UNAME_S),Darwin)
CIC= ${CICDIR}/bin/${OSBIN}/cic.app/Contents/MacOS/cic
else
CIC= ${CICDIR}/ciccreator/bin/${OSBIN}/cic
endif


.PHONY: 

all: qmake compile

qmake:
	qmake -o qmake.make ${PROG_NAME}.pro 

#- Use a wrapper around qmake, I like defining my own makefiles
compile:
	${MAKE} -f qmake.make

lay:
	-mkdir lay

demo: lay
	cd lay; ${PROG} ${CICDIR}/lay/SAR_ESSCIRC16_28N.cic ../../ciccreator/examples/tech.json  SAR ${OPT}	


clean:
	${MAKE} -f qmake.make clean


help:
	@echo " make               Compile cic2verilog"
	@echo " make      demo 	   Demonstrate usage"


