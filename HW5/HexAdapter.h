#ifndef _HEX_ADAPTER_H
#define _HEX_ADAPTER_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "AbstractHex.h"
#include "Cell.h"
using namespace std;

namespace MustafaKarakas1801042627{

	template <template <class ... > class T> // https://en.cppreference.com/w/cpp/language/template_parameters
	class HexAdapter : public AbstractHex{
	public:
		HexAdapter();
		HexAdapter(int _size);
		HexAdapter(int _size,bool _againt_cpu);
		//Big three
		//default destructer works well

	        //HexVector(HexVector &rhs);
	        const HexAdapter<T>& operator = (HexAdapter<T> &rSide); 
	        
		void createBoard();
	        void createBoard( AbstractHex& rSide); 
	        const Cell& operator()(int y,int x,int ignoreMe)throw (OutOfIndexError); 
	private:
	    T <T<Cell>> hexCells = T <T<Cell>>(1);
	    Cell& operator()(int y,int x)throw (OutOfIndexError); 
	};
}
#endif
