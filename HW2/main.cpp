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
	clearTable(table);
	decltype(select_game_type()) against_cpu = select_game_type(); //returns true if user wants to play vs cpu ,return 0 if user wants to play against another user
	showTable(table,size);
	cin.ignore();
	play(table,size,against_cpu);
	return 0;
	
}















