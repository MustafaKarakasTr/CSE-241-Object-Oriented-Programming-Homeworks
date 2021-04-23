#ifndef _HEXVECTOR_H
#define _HEXVECTOR_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "AbstractHex.h"
#include "Cell.h"

using namespace std;

namespace MustafaKarakas1801042627{

	class HexVector : public AbstractHex{
	public:
		HexVector();
		HexVector(int _size);
		HexVector(int _size,bool _againt_cpu);
		//Big three
		//default destructer & Copy constructer works well
	    //HexVector(HexVector &rhs);
	    const HexVector& operator = (HexVector &rSide); 
		
		void createBoard();

	    void createBoard( AbstractHex& rSide); 
	    const Cell& operator()(int y,int x,int ignoreMe)throw (OutOfIndexError); 

	private:
		vector<vector<Cell> > hexCells = vector<vector<Cell> >(1);
	    
	    Cell& operator()(int y,int x)throw (OutOfIndexError); 


	};
}
#endif