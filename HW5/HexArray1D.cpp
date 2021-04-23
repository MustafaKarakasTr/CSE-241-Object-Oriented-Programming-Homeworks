///*
#include "HexArray1D.h"
namespace MustafaKarakas1801042627{

	HexArray1D :: HexArray1D():AbstractHex(){
		createBoard();
	}
	HexArray1D :: HexArray1D(int _size):AbstractHex(_size){
		createBoard();
	}
	HexArray1D :: HexArray1D(int _size,bool _againt_cpu):AbstractHex(_size,_againt_cpu){
		createBoard();
	}
	HexArray1D :: HexArray1D(HexArray1D &rhs):AbstractHex(rhs){

		createBoard(rhs);
	}
	const HexArray1D& HexArray1D:: operator = (HexArray1D &rSide){
		if(this == &rSide){
			return (*this);
		}
		
		AbstractHex :: operator =(rSide);
		//createBoard(rSide);
		return (*this);

	} 

	 HexArray1D :: ~HexArray1D(){
	 	if(arr)
	 		free(arr);
	 }
	void HexArray1D :: createBoard(){
		if(arr)
	 		free(arr);
			
		arr = (Cell*) malloc (getSize()*getSize()* sizeof(Cell));
		int tempCounter = getCounter();
		reset();
		setCounter(tempCounter);
	}

	void HexArray1D :: createBoard(AbstractHex & rhs){
		if(arr)
			free(arr);
		arr = (Cell*) malloc (getSize()*getSize()* sizeof(Cell));
		HexArray1D * new_d = dynamic_cast<HexArray1D*>(&rhs);
		if(new_d){
			for(int i=0;i<getSize()*getSize();i++){
				arr[i] = new_d->arr[i];
			}
		}
	}
	Cell &  HexArray1D :: operator()(int y,int x)throw (OutOfIndexError){
		if(x*getSize()+y < getSize()*getSize())
			return arr[x*getSize()+y];
		throw OutOfIndexError();
	}
	const Cell &  HexArray1D :: operator()(int y,int x,int ignoreMe)throw (OutOfIndexError){
		if(x*getSize()+y < getSize()*getSize())
			return arr[x*getSize()+y];
		throw OutOfIndexError();
	}
}
//*/