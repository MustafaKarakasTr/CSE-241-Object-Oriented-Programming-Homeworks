#include "func.h"
int Hex :: index=0;
string Hex :: numbers_of_nonEmpty_cells="";
int main(){
   Hex a;
   a.playGame();

   Hex b(6,1);// it will continue to play a's game so I called this constructer, it will work even if you call default constructer 
   b=a; // assignent operator overloaded to continue a's play
   b.playGame();
   
   Hex c; // copy constructer called to continue Hex b's game
   c.playGame();
               
   Hex d(6,0);   // here it will not ask you to enter size and game type(if you remove parameters and call default constructer it will ask you what you want i but it will load the other game so I did not call it)
            //it will load to last game so you will keep playing with last game's table  
   d=c;
   d.playGame();
   
   Hex e;
   e.playGame();

   cout<<"First game has "<<a.getNumberOfNonEmptyCells()<<" cells\nSecond Game has "<<b.getNumberOfNonEmptyCells()<<" cells\nThird game has "<<c.getNumberOfNonEmptyCells()<<" cells\nFourth game has "<<d.getNumberOfNonEmptyCells()<<" cells\nFifth game has "<<e.getNumberOfNonEmptyCells()<<" cells.\n"<<endl;
 	if(a.compare(b)){
 		cout<<"First game has more cells than second game\n";
 	}
 	else
 		cout<<"First game does not have more cells than second game\n";  
   if(a==b){
      cout<<"First game and second game have same number of cells\n";
   }
   else 
      cout<<"First game does not have equal number of cells with second game\n";  

   cout<<endl<<"width and height of first game is :"<<a.width_height()<<endl<<endl;
   
}