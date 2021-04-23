#ifndef _CELL_H
#define _CELL_H
#include <iostream>
using namespace std;
namespace MustafaKarakas1801042627{

    enum cellVariables{X='x',O='o',Empty='.'};

    class Cell{
        private:
            char position; // A,B,C etc.
            int rowNum; // 1,2,3 etc.
            char variable=Empty; // as default all cells are empty
        public:
            Cell() {variable = Empty;}
            char getVariable() const {return variable;}
            void setVariable(char player);
            void setCoordinate(char pos,int row);
            void getCoordinate() const;
            int getPosition()const{return position-'A';}
            int getRow()const{return rowNum-1;};
            void makeUpperCase();
    };
}
#endif