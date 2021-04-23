#ifndef _FUNC_H
#define _FUNC_H

#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;
enum cellVariables{X='x',O='o',Empty='.'};
class Hex{
private:
	static int index;
	static string numbers_of_nonEmpty_cells;
	int index_of_game;
	void set_index_of_game(int index);
	int get_index_of_game()const;
	void increase_index_of_game();

   	int size=0;
    void setSize();
    void setSize(int _size); // checks if _size is valid if not then calls setSize()
    int getSize() const {return size;}

    bool against_cpu;
    bool is_against_cpu()const{return against_cpu;}
    void set_against_cpu(bool type){against_cpu = type;}

    bool is_cinCalled=false; // if it is true we will call cin.ignore()
    void set_is_cinCalled(bool prop){ is_cinCalled = prop; }

    int counter=0;
    int getCounter()const{return counter;}
    int increaseCounter(){counter++;}
    void setCounter(int _counter){counter = _counter;}

    char currentPlayer;        
    char getCurrentPlayer()const{
    	return (getCounter() % 2 == 0) ? X: O;
    }
    void setCurrentPlayer(char player){ currentPlayer = player;}

	string file_name;
	void set_file_name(const string &_file_name){ file_name = _file_name;}
	string get_file_name()const{return file_name;}

    int last_move[2]={0};
    int getLastMove(int _index){
    	if(_index>1 || _index<0){
    		cerr<<"Invalid index\n";
    		return -1;
    	}
    	return last_move[_index];
    }
    void setLastMove(int _index,int value){
    	if(_index>1 || _index<0){
    		cerr<<"Invalid index\n";
    		return ;
    	}
    	last_move[_index]=value;
    }
	bool isNumber(const string &indexCandidate)const; // checks if string consist of only digits
	bool isNumber(char chr)const{ return (chr>='0' && chr<='9');}// checks if string consist of only digits
	  
	void play(int y,int x);
	char play(); // play AI
	bool is_there_chance_to_put_next_to_last_move();
	bool valid_point(int y,int x)const;
	void collect_information_for_AI(int y,int x,int add_value);
    bool valid_point_but_full(int y,int x)const;
	bool neighbor_both_x_and_o(int y,int x)const;
	int number_of_neighbors_same_type(int y,int x)const;
	void fill_temp(int temp[6],int arry[6],int arrx[6],int y,int x)const;

	void saveGame()const;
	bool loadGame();
    void setGameType();
    void setGameType(int _against_cpu);

    void createBoard();
	void makeVectorsEmpty(); // make all vectors empty

    void showBoard()const;
    char makeMove(); // returns check function
    char check(); // if the game ends returns name of winner, else returns '\0' 
    bool check_neighbors(int y,int x);
    char getCommandfromInput(string& input,char &position,int &index); // helps to read command from input
    bool is_load_save_command_taken(const string &input1)const;
    void makeUpperCase(int y,int x);

    class Cell{
    private:
        char position; // A,B,C etc.
        int rowNum; // 1,2,3 etc.
        char variable=Empty; // as default all cells are empty
    public:
        Cell() {variable = Empty;}
        char getVariable() const {return variable;}
        void setVariable(char player);
        void setCoordinate(char pos,int row);
        void getCoordinate() const;
        void makeUpperCase();
    };

    vector<vector<Cell> > hexCells = vector<vector<Cell> >(1);
    vector<vector<bool> > check_table = vector<vector<bool> >(1);
    vector<vector<int> > value_table_of_AI=vector<vector <int > >(1);
public:
	    Hex();
	    Hex(int _size);	 
	    Hex(int _size,int _against_cpu);
	    void playGame();
        int width_height()const{return getSize();} 
        static int getIndex(){return index;} 
        static string get_numbers_of_nonEmpty_cells(){return numbers_of_nonEmpty_cells;}        
        int getNumberOfNonEmptyCells()const;
        bool compare(const Hex &other)const;
};

#endif
