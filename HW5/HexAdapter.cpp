#include "AbstractHex.h"
#include "HexAdapter.h"

using namespace std;

namespace MustafaKarakas1801042627{

	template <template <class ...>class T>
	HexAdapter<T> ::HexAdapter():AbstractHex(){
		createBoard();
	}

	template <template <class ...>class T>
	HexAdapter<T>:: HexAdapter(int _size):AbstractHex(_size){
		createBoard();
	}

	template <template <class ...>class T>
	HexAdapter<T>:: HexAdapter(int _size,bool _againt_cpu):AbstractHex(_size,_againt_cpu){
		createBoard();
	}
	template <template <class ...>class T>
	Cell& HexAdapter<T>:: operator()(int y,int x)throw (OutOfIndexError){
		if(valid_point_but_full(y,x))//return hexCells[y][x];
			return hexCells.at(y).at(x);
		else{
			throw OutOfIndexError();
		}
	}
	template <template <class ...>class T>
	const Cell& HexAdapter<T>:: operator()(int y,int x,int ignoreMe)throw (OutOfIndexError){
		if(valid_point_but_full(y,x))//return hexCells[y][x];
			return hexCells.at(y).at(x);
		else{
			throw OutOfIndexError();
		}
	}
	template <template <class ...>class T>
	void HexAdapter<T> :: createBoard(){
		//AbstractHex :: createBoard();
		int Size=getSize();
	    hexCells.resize(1);
	    //hexCells[0].resize(1);
	    hexCells.at(0).resize(1);
	    for(int i=1;i<Size;i++){
	    	hexCells.push_back(hexCells[0]);
	    }
	    for(int i=0;i<Size;i++){
	        hexCells[i]=T<Cell>(Size);
	    }
	    for(int i=1;i<=Size;i++){
	    	for(char j='A';j<Size+'A';j++){
	    		//hexCells[i-1][j-'A'].setCoordinate(j,i);
	    		hexCells.at(i-1).at(j-'A').setCoordinate(j,i);
	    	}
	    }
	}
	template <template <class ...>class T>
	void HexAdapter<T> :: createBoard( AbstractHex& rSide){
		
		createBoard();
		HexAdapter* new_d = dynamic_cast<HexAdapter*>(&rSide);
		if(new_d){

			for(int i=0;i<getSize();i++){
				//hexCells.at(i) = new_d->hexCells.at(i);
				for(int j = 0;j<getSize();j++){
					hexCells.at(i).at(j).setVariable(new_d -> hexCells.at(i).at(j).getVariable());
				}
			}
		}

	}

	template <template <class ...>class T>
	const HexAdapter<T>&  HexAdapter <T> :: operator = (HexAdapter<T> &rhs){
		AbstractHex :: operator = (rhs);
		return (*this);
		
	}
}