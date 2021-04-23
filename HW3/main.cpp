#include "func.h"
int Hex :: index=0;
string Hex :: numbers_of_nonEmpty_cells="";
int main(){
   Hex a;
   a.playGame();

   Hex b;
   b.playGame();
   
   Hex c;
   c.playGame();
   
   Hex d;   
   d.playGame();
   
   Hex e;   
   e.playGame();

   cout<<"First game has "<<a.getNumberOfNonEmptyCells()<<" cells\nSecond Game has "<<b.getNumberOfNonEmptyCells()<<" cells\nThird game has "<<c.getNumberOfNonEmptyCells()<<" cells\nFourth game has "<<d.getNumberOfNonEmptyCells()<<" cells\nFifth game has "<<e.getNumberOfNonEmptyCells()<<" cells.\n"<<endl;
 	if(a.compare(b)){
 		cout<<"First game has more cells than second game";
 	}
 	else
 		cout<<"First game does not have more cells than second game";  
   
   cout<<endl<<"width and height of first game is :"<<a.width_height()<<endl<<endl;

}