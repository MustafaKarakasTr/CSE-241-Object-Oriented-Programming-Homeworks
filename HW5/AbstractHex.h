#ifndef _ABSTRACTHEX_H
#define _ABSTRACTHEX_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include <deque>
#include "Cell.h"
//#include "HexVector.h"

using namespace std;
namespace MustafaKarakas1801042627{

    class OutOfIndexError : public exception {
       public:
       const char * what () const throw () {
          return "OutOfIndexError occured\n";
       }
    };
    class ThereIsNoLastMove : public exception {
       public:
       const char * what () const throw () {
          return "There is no last move to show\n";
       }
    };
    class AbstractHex{
    public:
        AbstractHex();
        explicit AbstractHex(int _size);  // explicit keyword is used
        AbstractHex(int _size,int _against_cpu);
        //Big Three
        
        virtual ~AbstractHex();
        
        //AbstractHex(const AbstractHex &rSide);
        
        const AbstractHex& operator =( AbstractHex &rSide);
        
        //--------
        bool operator ==(AbstractHex & other);
        int numberOfMoves();

        //------
        void playGame();
        int width_height()const{return getSize();} 
        
        friend ostream & operator <<(ostream & outputStream,AbstractHex& h); // it calls operator() and it is not constant so h must be non-const
        friend istream & operator >>(istream & inputStream,AbstractHex & h);
        //------------------------------------------------------------
        void print();
        bool isEnd();
        
        int getSize() const {return size;}
        virtual const Cell& operator()(int y,int x,int ignoreMe)=0;
        const Cell& lastMove()throw (ThereIsNoLastMove);

    protected:
    	 bool _GET_OUT_OF_INDEX_EXCEPTION = false;// If you make it true then my exception handling works (there is a dummy code in playGame() function)
    	 bool _GET_NO_LAST_MOVE_EXCEOTION = false;// same for ThereIsNoLastMove exception
    	
        bool game_continue=true;
       	int size=0;
        void setSize();
        void setSize(int _size); // checks if _size is valid if not then calls setSize()

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
    	const Cell& play(); // play AI
    	bool is_there_chance_to_put_next_to_last_move(int &y,int &x);
    	bool valid_point(int y,int x);
    	void collect_information_for_AI(int y,int x,int add_value);
        bool valid_point_but_full(int y,int x)const;
    	bool neighbor_both_x_and_o(int y,int x);
    	int number_of_neighbors_same_type(int y,int x);
    	void fill_temp(int temp[6],int arry[6],int arrx[6],int y,int x);

    	//void writeToFile(const string &file)const;
        void setGameType();
        void setGameType(int _against_cpu);

        virtual void createBoard();
        virtual void createBoard( AbstractHex& rSide); // for copy constructer

        void showBoard();
        char makeMove(); // returns check function
        char check(); // if the game ends returns name of winner, else returns '\0' 
        bool check_neighbors(int y,int x);
        char getCommandfromInput(string& input,char &position,int &index); // helps to read command from input
        bool is_load_save_command_taken(const string &input1)const;
        bool is_setSize_taken(const string &input1)const;
        void makeUpperCase(int y,int x);
        int  setScores(int y,int x,bool *_check);
        void showScore(bool *_check);
        //--------------------------------------------------------
        void writeToFile(const string &file);
    	bool readFromFile(const string &file);

        void reset();
        void setSize(int width,int height);
        virtual Cell& operator()(int y,int x)=0;
        //--------------------------------------------------------

        int score1=0,score2=0; 
        
       
    	vector<vector<bool> > check_table = vector<vector<bool> >(1);
        vector<vector<int> > value_table_of_AI=vector<vector <int > >(1);
        Cell * movements=nullptr;
    };
}
#endif