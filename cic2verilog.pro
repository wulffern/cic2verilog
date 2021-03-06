######################################################################
##        Copyright (c) 2018 Carsten Wulff Software, Norway 
## ###################################################################
## Created       : wulff at 2018-2-17
## ###################################################################
##  The MIT License (MIT)
## 
##  Permission is hereby granted, free of charge, to any person obtaining a copy
##  of this software and associated documentation files (the "Software"), to deal
##  in the Software without restriction, including without limitation the rights
##  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
##  copies of the Software, and to permit persons to whom the Software is
##  furnished to do so, subject to the following conditions:
## 
##  The above copyright notice and this permission notice shall be included in all
##  copies or substantial portions of the Software.
## 
##  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
##  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
##  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
##  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
##  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
##  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
##  SOFTWARE.
##  
######################################################################

  CONFIG += qt console debug
  TEMPLATE = app
  TARGET = cic2verilog

  
  QT += core
  CONFIG += c++11
  
  mac {
  #- This needs to point to the SDK usually in /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/
  mac::QMAKE_MAC_SDK = macosx10.15
  }
  osx:DESTDIR = bin/darwin
  linux:DESTDIR = bin/linux
  win32:DESTDIR = bin/windows

  #- Add coverage information
  QMAKE_CFLAGS += $$(CFLAGS) --coverage
  QMAKE_LFLAGS += $$(LDFLAGS) --coverage

  OBJECTS_DIR=build
  MOC_DIR=build

  DEPENDPATH +=.

  INCLUDEPATH += src/ ../ciccreator/cic-core/src/ ../ciccreator/cic-core/external/libgds_dist/

  # Input
  HEADERS += src/verilog.h
  
  SOURCES +=         src/main.cpp \
  src/verilog.cpp
  

  
win32: LIBS += -L$$PWD/../ciccreator/lib/windows/ -lcic
else:linux: LIBS += -L$$PWD/../ciccreator/lib/linux/ -lcic
else:mac: LIBS += -L$$PWD/../ciccreator/lib/darwin/ -lcic


mac:PRE_TARGETDEPS += ../ciccreator/lib/darwin/libcic$${LIBSUFFIX}.a
mac:INCLUDEPATH += $$PWD/../ciccreator/lib/darwin
mac:DEPENDPATH += $$PWD/../ciccreator/lib/darwin

                   
linux:PRE_TARGETDEPS += ../ciccreator/lib/linux/libcic$${LIBSUFFIX}.a
linux:INCLUDEPATH += $$PWD/../ciccreator/lib/linux
linux:DEPENDPATH += $$PWD/../ciccreator/lib/linux

win32:PRE_TARGETDEPS += ../ciccreator/lib/windows/libcic$${LIBSUFFIX}.a
win32:INCLUDEPATH += $$PWD/../ciccreator/lib/windows
win32:DEPENDPATH += $$PWD/../ciccreator/lib/windows


