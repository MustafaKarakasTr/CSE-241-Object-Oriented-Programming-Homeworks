/*
 * gum.cpp
 *
 *  Created on: Oct 13, 2020
 *      Author: Mustafa Karakaş
 */

#include"myHeader.h"

int main(){
	
	int size=takeSize();
	char table[12][12];
	
	for(int i=0;i<12;i++)
	{
		for(int j=0;j<12;j++){
			table[i][j]='.';
		}
	}
	bool against_cpu = select_game_type(); //returns true if user wants to play vs cpu ,return 0 if user wants to play against another user
	if(against_cpu){
		cout<<"Play against CPU"<<endl;
	}
	else
		cout<<"Have fun with your friend\n";
	showTable(table,size);
	play(table,size,against_cpu);
	return 0;
}















