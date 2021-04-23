#include "HexVector.h"
#include "AbstractHex.h"
using namespace std;

namespace MustafaKarakas1801042627{

	HexVector :: HexVector():AbstractHex(){
		createBoard();

	}
	HexVector :: HexVector(int _size):AbstractHex(_size){
		createBoard();

	}
	HexVector :: HexVector(int _size,bool _against_cpu):AbstractHex(_size,_against_cpu){
		createBoard();

	}
	
	 Cell& HexVector :: operator()(int y,int x)throw (OutOfIndexError){
		if(valid_point_but_full(y,x))
			return hexCells[y][x];
		else{
			throw OutOfIndexError();
		}
	}
	const Cell& HexVector :: operator()(int y,int x,int ignoreMe)throw (OutOfIndexError){
		if(valid_point_but_full(y,x))
			return hexCells[y][x];
		else{
			throw OutOfIndexError();
		}
	}

	void HexVector :: createBoard(){
		//AbstractHex :: createBoard();
		int Size=getSize();
	    hexCells.resize(1);
	    hexCells[0].resize(1);
	    for(int i=1;i<Size;i++){
	    	hexCells.push_back(hexCells[0]);
	    }
	    for(int i=0;i<Size;i++){
	        hexCells[i]=vector<Cell>(Size);
	    }
	    for(int i=1;i<=Size;i++){
	    	for(char j='A';j<Size+'A';j++){
	    		hexCells[i-1][j-'A'].setCoordinate(j,i);
	    	}
	    }
	}
	void HexVector :: createBoard( AbstractHex& rSide){
		
		createBoard();
		HexVector * new_d = dynamic_cast<HexVector*>(&rSide);

		for(int i=0;i<getSize();i++){
			if(new_d){
				hexCells[i] = new_d->hexCells[i];
			}
		}

	}

	const HexVector& HexVector :: operator = (HexVector &rhs){
		AbstractHex :: operator = (rhs);
		return (*this);
		
	}
}


