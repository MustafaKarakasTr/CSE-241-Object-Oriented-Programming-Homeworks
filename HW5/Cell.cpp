#include "Cell.h"
using namespace std;
namespace MustafaKarakas1801042627{

	void Cell :: setVariable(char player){
	    if(player == X || player==O || player == X -'a' + 'A' || player == O -'a' +'A' || player == Empty)
	  		variable = player;
	    else
	       	cerr<<"Invalid player\n";  
	}
	void Cell :: setCoordinate(char pos,int row){
		position = pos;
		rowNum = row;
	}
	void  Cell :: getCoordinate()const{
		cout<<position<<" "<<rowNum<<" ";
	}
	void  Cell :: makeUpperCase(){
		setVariable(getVariable() +'A' -'a');
	} 
}