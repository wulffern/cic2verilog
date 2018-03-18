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

#include "verilog.h"

namespace cIcPrinter{

    Verilog::Verilog(QString filename):DesignPrinter(filename){

    }

    void Verilog::startLib(QString name){
        if(!QDir(name).exists()){
            QDir().mkdir(name);
        }
        openFile(name + ".fl");
        libname = name;
        

    }

    void Verilog::endLib(){
        closeFile();
    }


    void Verilog::printPort(Port * p){

        QString layer = p->layer();
        QString name = p->name();
        QString direction = "inputOutput";
        
        Rect * r = new Rect(p);
        r->setLayer(p->pinLayer());
        this->printRect(r);

    }

    void Verilog::printText(Text * p){
    }


    void Verilog::printReference(Cell * o){
        if(Cell::isEmpty(o)){return ;}
        if(!o->isInstance()){return;}

        Instance * inst = (Instance *) o;

        QTextStream ts_cell(&cellfile);


    }

    void Verilog::openCellFile(QString filename){
        cellfile.setFileName(filename);
        cellfile.open(QIODevice::WriteOnly );

    }

    void Verilog::closeCellFile(){
        cellfile.close();
    }



    void Verilog::printRect(Rect * o){

  
    };


    void Verilog::startCell(Cell *cell){


        QString file_name_cell = libname  + "/" + cell->name() + ".v";

        QTextStream ts_lib(&file);

        ts_lib << "-f " << file_name_cell << "\n";

        //Start new skill file for the layout, and add ref to library
        openCellFile(file_name_cell);
        QTextStream ts_cell(&cellfile);
//        qDebug() << "Test" << cell->name() << cell->subckt()<<"\n";

        cIcSpice::Subckt * ckt = cell->subckt();
        
        if(!ckt){return;}


        
        ts_cell << "\n";
        ts_cell << "//-------------------------------------------------------------\n";
        ts_cell << "// " << cell->name() << " (" << cell->metaObject()->className() <<")\n";
        ts_cell << "//-------------------------------------------------------------\n";
    if(ckt->name() != ""){
        ts_cell << "module " << ckt->name() << " ( " << ckt->nodes().join(" , ")  << ");\n";
        foreach(cIcSpice::SubcktInstance* sd,ckt->instances()){
            ts_cell << sd->subcktName() << " " << sd->name() << " (" << sd->nodes().join(" , ") << ");\n";
            
            qDebug() << sd->name() << sd->subcktName() << sd->nodes()<< "\n";
            
        }
        
      }
        
        
        
        ts_cell.flush();


    }

    void Verilog::endCell(){

        QTextStream ts_cell(&cellfile);
        ts_cell << "endmodule\n";
        
        closeCellFile();
    }


};
