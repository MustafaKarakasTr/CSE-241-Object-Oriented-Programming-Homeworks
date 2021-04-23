#ifndef _MYHEADER_H
#define _MYHEADER_H

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

enum Player{X='x',O='o',Empty='.'}; // enumeration is done

int takeSize(); // takes size of the board from the user

void showTable(char table[][12],int size=12); // default argument has been used 
void play(char table[][12],int size,bool against_cpu); // it starts when table is ready to be played, it ends when game ends
bool select_game_type(); //where user vs user or user vs computer selection is made
int yourTurn(char table[][12],int &size,char &player,int check_table[][12],int last_move[2],int value_table_of_AI[][12],bool &against_cpu,int &counter);
	/*
	*	take moves from the user. Last 3 parameter (int last_move[2],int value_table_of_AI[][12],bool against_cpu) is not used if user vs user game is played
	*/
char input_analyze(string &str,char &position,int &index,string &file_name);
bool isNumber(const string &indexCandidate);
bool isNumber(char chr);
bool is_load_save_command_taken(const string &input1 );
void saveGame(char table[][12],const string &file_name,int size,char player,bool against_cpu,int &counter,int value_table_of_AI[][12]);

bool loadGame(char table[][12],const string &file_name,int &size,char &player,bool &against_cpu,int &counter,int value_table_of_AI[][12]); // constant parameter by reference is given
bool indexTrue(string input,int index,char target);
int play_AI(char table[][12],int size,char player,int check_table[][12],int last_move[2],int value_table_of_AI[][12]); 
	/*	
	*	if user wanted to play against computer instead of yourTurn function play_AI is called for make computer play the game
	*/
int check(char table[][12],int size,char player,int check_table[][12]); // decides if game over or not
bool valid_point(char table[][12],int size,int y,int x); // if the point is in table and  it has nothing yet, returns true , else returns false
bool valid_point_but_full(char table[][12],int size,int y,int x); // if the point is in table and it is taken already returns true, else returns false
void collect_information_for_AI(char table[][12],int size,int y,int x,int value_table_of_AI[][12],int add_value); // int value_table_of_AI[12][12] is redesigned, the points which are next to last move gain more points and that increase the chance of being selected by computer for these values
bool check_neighbors(char table[][12],int size,int y,int x,char player,int check_table[][12]);// this function helps to check function returns true if game ends, else returns false
void makeUpperCase(char table[][12],int size,int y,int x,char player);// if game ends makes uppercase all letters which are caused to game over
bool neighbor_both_x_and_o(char table[][12],int size,int y,int x); // if given point has x and o as neighbor returns true else returns false
int number_of_neighbors_same_type(char table[][12],int size,char player,int y,int x); // this function helps computer make decision ,returns number of neighbors which have same type with given point
bool is_there_chance_to_put_next_to_last_move(char table[][12],int size,char player,int last_y,int last_x,int value_table_of_AI[][12]); 
// if it is possible to make a move near last move returns true else returns false
void clearTable(char table[][12]);
#endif
