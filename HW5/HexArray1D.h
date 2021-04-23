
#ifndef _HEX_ARRAY_1D
#define _HEX_ARRAY_1D
#include <iostream>
#include <cstdlib>
#include "AbstractHex.h"
#include "Cell.h"
namespace MustafaKarakas1801042627{

	class HexArray1D:public AbstractHex {
	public:
		HexArray1D();
		HexArray1D(int _size);
		HexArray1D(int _size,bool _againt_cpu);
		//Big three

	    HexArray1D(HexArray1D &rhs);
	    const HexArray1D& operator = (HexArray1D &rSide); 
		~HexArray1D();	
	    const Cell& operator()(int y,int x,int ignoreMe)throw (OutOfIndexError); 
		
	private:
		Cell *arr = nullptr;
		void createBoard();
		void createBoard(AbstractHex & rhs);

	    Cell& operator()(int y,int x)throw (OutOfIndexError); 

	};
}
#endif
