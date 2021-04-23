#include <iostream>
#include "AbstractHex.h"
#include "HexVector.h"
#include "HexArray1D.h"
#include "HexAdapter.h"
#include "HexAdapter.cpp"
using namespace std;
using namespace MustafaKarakas1801042627;

bool isGameValid(AbstractHex *game){
	int number_of_x=0;
	int number_of_o=0;
	for(int i=0;i<game->getSize();i++){
		for(int j=0;j<game->getSize();j++){
			char board_character = game->operator()(i,j,0).getVariable();
			if(board_character != 'X' && board_character != 'O' && board_character != 'x' && board_character != 'o' && board_character != '.'){
				return false;
			}
			else if(board_character == 'X' || board_character == 'x'){
				number_of_x++;
			}
			else if(board_character == 'O' || board_character == 'o'){
				number_of_o++;
			}
		}

	}
	if(number_of_o - number_of_x > 1 || number_of_x -number_of_o > 1){
		return false;
	}
	return true;
}
bool isSequenceValid(AbstractHex ** games,int size){
	bool flag = true;
	for(int i=0;i<size;i++){
		if(!isGameValid(games[i])){
			cout<<i+1<<". game is not valid\n";
			flag = false;
		} 
	}
	return flag;
}
int main(){
	try{

		HexVector a(6,false); //6x6 && vs Computer
		a.playGame();
		
		/*
	    //last move function
		Cell cell =a.lastMove();
		cell.getCoordinate();
		cout<<endl;
		*/
		HexVector b(a); // copy constructer
		b.playGame();
		
		HexAdapter <deque> h;
		h.playGame();

		HexAdapter<vector> vect;
		vect.playGame();  
		
		HexArray1D d(6,1);
		d.playGame();
		cout<<"Number of moves made in the game: "<<d.numberOfMoves()<<endl;

		HexArray1D v;
		v = d;
		v.playGame();
		cout<<"Number of moves made in the game: "<<v.numberOfMoves()<<endl;

		if(d == v){
			cout<<"They are same\n";
		}
		else{
			cout<<"They are not same\n";
		}

		AbstractHex *games[] = {&a,&b,&h,&vect,&d,&v};

		if(isSequenceValid(games,6))
			cout<<"Sequence has only valid games\n";
		else{
			cout<<"Sequence has non valid game(s)";
		}

	}
	catch(OutOfIndexError &er){ // operator () throws but there is no way for user to take this exception
		cout<<er.what();
	}
	catch(ThereIsNoLastMove& lm){ // operator () throws but there is no way for user to take this exception
		cout<<lm.what();
	}

	
}