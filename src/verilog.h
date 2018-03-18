//====================================================================
//        Copyright (c) 2018 Carsten Wulff Software, Norway 
// ===================================================================
// Created       : wulff at 2018-2-17
// ===================================================================
//  The MIT License (MIT)
// 
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
// 
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//  
//====================================================================
 
#ifndef CIC_PRINTER_VERILOG
#define CIC_PRINTER_VERILOG

#include <QObject>
#include <QString>
#include "printer/designprinter.h"

namespace cIcPrinter{
    using namespace cIcCore;

    class Verilog : public DesignPrinter{

    public:

        Verilog(QString filename);
        ~Verilog(){

        }


    private:
        virtual void startCell(Cell * cell);
        virtual void endCell();
        virtual void startLib(QString name) ;
        virtual void endLib() ;
        virtual void printPort(Port *);
        virtual void printText(Text *);
        virtual void printRect(Rect * rect);
        virtual void printReference(Cell * o);

        void openCellFile(QString name);
        void closeCellFile();
        int toNano(int angstrom);
        double toMicron(int angstrom);
        QString libname;
        QFile  cellfile;
        QString libstr;
    };

    inline int Verilog::toNano(int angstrom){ return angstrom/10;}
    inline double Verilog::toMicron(int angstrom){
        return ((double) (angstrom/10))/1000.0;
    }
};

#endif
