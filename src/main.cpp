//====================================================================
//        Copyright (c) 2018 Carsten Wulff Software, Norway 
// ===================================================================
// Created       : wulff at 2018-3-18
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

#include "cic-core.h"
#include "verilog.h"
#include <iostream>
#include <QDebug>
#include <QString>

int main(int argc, char *argv[])
{
    try
    {
        if(argc >=  2){

            QString file = argv[1];
            QString rules = argv[2];
            QString library = argv[3];

            if(library == ""){
                QRegularExpression re("/?([^\\/]+)\\.json");
                QRegularExpressionMatch m = re.match(file);
                library = m.captured(1);
            }
            
            //Load rules
            cIcCore::Rules::loadRules(rules);

            //Load design, this is where the magic happens
            cIcCore::Design * d= new cIcCore::Design();
            d->readJsonFile(file);

            cIcPrinter::Verilog * s = new cIcPrinter::Verilog(library);
            s->print(d);
            

        }else{
            qWarning() << "Usage: cic2verilog <JSON file> <Technology file> [<Output Library>]";
        }

    }catch(...){
      
        return -1;
    }





}
