#include "AbstractHex.h"
namespace MustafaKarakas1801042627{
	AbstractHex :: AbstractHex(){
	    setSize();
	    setGameType();
	    createBoard();
	}

	AbstractHex :: AbstractHex (int _size){
		setSize(_size);
		setGameType();
		createBoard();
	}
	
	AbstractHex :: AbstractHex(int _size,int _against_cpu)
	{	
		setSize(_size);
		setGameType(_against_cpu);
		createBoard();
	}

	const AbstractHex& AbstractHex :: operator =(  AbstractHex &rSide){
		if(this == &rSide){
			return *this;
		}
		
		counter=rSide.counter;
		currentPlayer = rSide.currentPlayer;
		file_name = rSide.file_name;
		game_continue = rSide.game_continue;
		last_move[0] = rSide.last_move[0];
		last_move[1] = rSide.last_move[1];

		
		against_cpu = rSide.against_cpu;
		setSize(rSide.size);


		AbstractHex :: createBoard(rSide);
		createBoard(rSide);
		

		cout<<"Game Loaded with the help of overloaded assignment operator\nYou are playing against: ";
		if(against_cpu)
			cout<<"CPU\n\n";
		else
			cout<<"Your friend\n\n";
		return *this;
	}

	AbstractHex :: ~AbstractHex(){ /* Body initially empty */}


	void AbstractHex::setSize(){
	    bool invalid=true;
	    int temp; 
	    while(invalid){
	        cout<<"Enter size of the board:";
	        cin>>temp;
	        set_is_cinCalled(true);
	        if(temp>=6){
	            size=temp;
	            invalid=false;
	        }
	        else
	        	cerr<<"Size should be greater than 5. Please try again\n";
	    }

	}
	void AbstractHex::setSize(int _size){
	    bool invalid=true;
	    int temp; 
	    if(_size > 5){
			size = _size;
		}
		else{
			cerr<<"Size given as constructer argument is not valid\nTry again\n";
			setSize();
		}

	}
	void AbstractHex::setGameType(){
	    bool invalid = true;
	    int temp;
	    while(invalid){
	        cout<<"Enter 0 to play against friend, 1 to against computer: ";
	        cin>>temp;
	        set_is_cinCalled(true);
	        if(temp == 0 || temp == 1){
	            if(temp==0){
	                cout<<"Have fun with your friend\n";
	                against_cpu = false;
	            }
	            else{
	                cout<<"Have fun with your virtual friend\n";  
	            	against_cpu = true;
	            }
	            
	            invalid = false;
	                              
	        }

	        else
	        	cout<<"Invalid game type \nTry again\n";  
	    }
	}
	void AbstractHex::setGameType(int _against_cpu){
		if(_against_cpu == 1){
	        cout<<"Have fun with your virtual friend\n";  
			against_cpu = true;
		}
		
		else if(_against_cpu == 0){
			cout<<"Have fun with your friend\n";
			against_cpu = false;
		}
		else{
			cout<<"Invalid game type\nPlease Try Again\n";
			setGameType();
		}
	}



	void AbstractHex :: showBoard() {
	    int Size=getSize();
	    char letters='a';
		cout<<" ";
		for(int i=0;i<Size;i++){
			cout<<" "<<letters++;
		}
		cout<<endl;
		for(int i = 0; i < Size; ++i)
			{
				cout<<i+1<<" ";
				for(int a=0;a<i;a++){
					if(a==8){ // 2 digits ruin table to be able to prevent it I added this

					}
					else
						cout<<" ";
				}
				for(int x=0;x<Size; x++){
					cout<<(*this)(i,x).getVariable()<<" ";
					//hexCells[i][x].getCoordinate();
				}
				cout<<endl;
			}
		cout<<endl;
	}
	char AbstractHex :: makeMove(){
		
		char letter='\0';
		string input,file_name;
		char flag='\0';
		int x=-1;
		int y=-1; 
		char player=getCurrentPlayer();
		bool invalid = true;
		int game_continue=1;
		while(invalid){ // ask until take valid point
			input="";		
			
			cout<<"Enter the position:";// such as: A 5, B 2, C 10
			getline(cin,input);	
			flag=getCommandfromInput(input,letter,y);
			//flag=input_analyze(input,letter,y,file_name); //returns 'Y' if coordinates given, returns 'S' if save command has been seen,returns 'L' if load command has been seen else returns 'a'
			if(flag=='Y'){ // if input is a point 
				if(letter >= 'a' && letter <='z') // if user enters lowercase,make it uppercase
					letter=letter-'a'+'A';
				/* if input is A 1 we should use the index [0][0] so we made necessary changes*/
				x=letter-'A';
				y--;
				if(y>=0 && y<getSize() && x>=0 && x<getSize() && (*this)(y,x).getVariable() == Empty){
					play(y,x); // puts to player's icon in the y,x coordinate
					if(against_cpu)		
						collect_information_for_AI(y,x,5);//this function increase the value of the positions which ar near last move by 5
							
					// computer will consider where the last move is			
					setLastMove(0,y);
					setLastMove(1,x);
					

					
					invalid=false; // only point to leave loop is where the coordinates taken
				}
				
				else{
					cout<<(*this);
					cerr<<"Invalid input. Try again "<<endl;
				}
			} //flag=='Y' endif
			else if(flag=='S'){
				writeToFile(get_file_name());			
			}
			else if(flag=='L'){
				bool isFileOK=readFromFile(get_file_name());			
				if(isFileOK){	
					cout<<"Given file loaded\n";
					score1=0;
					score2=0;
					return 'L';
				}
				else{
					cerr<<"We continue from where we were\n";
					cout<<(*this);
					//showBoard();		
				}
			}
			else if(flag == 'Q' || flag == 'R' ||flag == 'E'){

				return flag;
			}

			else{
				cout<<(*this);

			}
		}
		return check();
	}

	bool AbstractHex :: neighbor_both_x_and_o(int y,int x){
		bool neighbor_of_x=false;
		bool neighbor_of_o=false;
		int indexHelper[6][2]={{-1,0},{-1,+1},{0,-1},{1,-1},{1,0},{0,1}};
		for(int i=0;i<6;i++){
			if(valid_point_but_full(y+indexHelper[i][0],x+indexHelper[i][1]) && (*this)(y+indexHelper[i][0],x+indexHelper[i][1]).getVariable() == X){
				neighbor_of_x=true;
				break;
			}

		}
		
		if(neighbor_of_x){
			for(int i=0;i<6;i++){
				if(valid_point_but_full(y+indexHelper[i][0],x+indexHelper[i][1]) && (*this)(y+indexHelper[i][0],x+indexHelper[i][1]).getVariable() == O){
					neighbor_of_x=true;
					break;
				}
			}
		}
		
		return (neighbor_of_x && neighbor_of_o);
	}

	bool  AbstractHex ::valid_point_but_full(int y,int x)const{
		return(y>=0 && x>=0 && y<getSize() && x<getSize());
	}

	int AbstractHex :: number_of_neighbors_same_type(int y,int x){
		int number_of_neighbors=0;
		char player = getCurrentPlayer();
		int indexHelper[6][2]={{-1,0},{-1,+1},{0,-1},{1,-1},{1,0},{0,1}};
		for(int i=0;i<6;i++){
			if(valid_point_but_full(y+indexHelper[i][0],x+indexHelper[i][1]) && (*this)(y+indexHelper[i][0],x+indexHelper[i][1]).getVariable()==player)
				number_of_neighbors++;
		}
		return number_of_neighbors;
	}
	bool AbstractHex :: valid_point(int y,int x){		
		return (y>=0 && x>=0 && y<getSize() && x<getSize() && (*this)(y,x).getVariable()==Empty);
	}
	void AbstractHex :: collect_information_for_AI(int y,int x,int add_value){
		int indexHelper[6][2]={{-1,0},{-1,+1},{0,-1},{1,-1},{1,0},{0,1}};
		for(int i=0;i<6;i++){
			if(valid_point(y+indexHelper[i][0],x+indexHelper[i][1])){
				value_table_of_AI[y+indexHelper[i][0]][x+indexHelper[i][1]]+=add_value;
				if((indexHelper[i][0] == 0 && indexHelper[i][1] == -1 ) || indexHelper[i][0] == 0 && indexHelper[i][1] == 1)
					if(add_value>0)
						value_table_of_AI[y+indexHelper[i][0]][x+indexHelper[i][1]]+=3;// left and right of opponent more important to be hold
					else
						value_table_of_AI[y+indexHelper[i][0]][x+indexHelper[i][1]]-=3; // after undo operation we should take what we have given

			}

		}
	}
	void AbstractHex :: fill_temp(int temp[6],int arry[6],int arrx[6],int y,int x){
		int indexHelper[6][2]={{-1,0},{-1,+1},{0,-1},{1,-1},{1,0},{0,1}};
		for(int i=0;i<6;i++){
			if(valid_point(y+indexHelper[i][0],x+indexHelper[i][1])){
				arry[i]=y+indexHelper[i][0];
				arrx[i]=x+indexHelper[i][1];
				temp[i]=number_of_neighbors_same_type(arry[i],arrx[i]);
			}
		}
	}

	bool AbstractHex :: is_there_chance_to_put_next_to_last_move(int &y,int &x){
		x=-1;
		y=-1;
		int arrx[6]={-1,-1,-1,-1,-1,-1};
		int arry[6]={-1,-1,-1,-1,-1,-1};
	//,y1=0,x1=0, y2=0,x2=0, y3=0,x3=0, y4=0,x4=0, y5=0,x5=0, y6=0,x6=0;
		int temp[6]={-1,-1,-1,-1,-1,-1};
		int number_of_connections_with_same_type=0;
		int max=0;
		
		int last_y=getLastMove(0);
		int last_x=getLastMove(1);
		// priority : the position which has most number of neighbor which is same type for o->o etc.
		fill_temp(temp,arry,arrx,last_y,last_x);
		
		max=0;
		for(int i=0;i<6;i++){
			if(max<temp[i] && temp[i]<2){
				max=temp[i];	
				x=arrx[i];
				y=arry[i];
				break;
			}
		}
		if(x==-1 || y==-1 || max==0 || max>2)
			return false;// no place to put player next to last move
		
		collect_information_for_AI(y,x,5);
		
		(*this)(y,x).setVariable(getCurrentPlayer());
		//cout<<"Computer played to:"<<static_cast<char>('A'+x)<<" "<<y+1<<endl;
		return true; // if one of the condition holds return true player1's turn
	}
	void AbstractHex :: showScore(bool *_check){
		for(int i=0;i<getSize();i++){
			for(int j=0;j<getSize();j++){
				check_table[i][j] = false;
			}
		}
		int tempScore;
		for(int i=0;i<getSize();i++){
			for (int j = 0; j< getSize(); j++)
			{
				char cell=(*this)(i,j).getVariable();
				if(cell!=Empty){
					tempScore=setScores(i,j,_check);
					if(cell == X || cell == X+'A'-'a'){
						if(tempScore > score1)
						score1=tempScore;
					}
					else{
						if(tempScore>score2)
						score2=tempScore;	
					}
				}
			}
		}
		//int score =setScores(last_move[0],last_move[1],_check);
		
			
			cout<<"X's Score: "<<score1<<endl;
			 
			cout<<"O's Score: "<<score2<<endl;
		for(int i=0;i<getSize();i++){
			for(int j=0;j<getSize();j++){
				check_table[i][j] = false;
			}
		}
	}
	void AbstractHex :: playGame(){
		bool *_check;
		if(is_cinCalled){
				cin.ignore();
				set_is_cinCalled(false);
		}

		char winner='\0';
		if(_GET_NO_LAST_MOVE_EXCEOTION){///AbstractHex.h class has this constant if you make it true then you get exception
			Cell a=lastMove();
		}
		while(game_continue){
			cout<<(*this);
			if(_GET_OUT_OF_INDEX_EXCEPTION) // AbstractHex.h class has this constant if you make it true then you get exception
			 	(*this)(-5,10); 
			
			_check=new bool[getSize()];
			for(int i=0;i<getSize();i++){
				_check[i]=false;
			}
			//showScore(_check);

			if(getCurrentPlayer() == X){
				winner =makeMove();
				if(winner == 'Q'){
					cout<<"Game Cancelled\n";
					// we dont change that game continues to be able to keep playing it when we call copy construter with this Hex game
					//showScore(_check);
					
					delete[] _check;
					return;
				}
				else if(winner == 'R'){
					reset();
					counter =0;
					continue;
				}
			
				if(winner == getCurrentPlayer())
				{

					cout<<"Winner:"<<winner<<endl;
					//cout<<"Score : "<<getSize()*10<<endl; // no need to call showScore function max point must be shown and this works other function does not
					increaseCounter();
					cout<<(*this);
					
					game_continue = false;
					delete[] _check;
					
					return;
				}
				if(winner =='L' || winner == 'S' || winner =='U' || winner == 'E'){
					//showScore(_check);
					continue;
				}
				
				//movements[counter]=
				increaseCounter();
			}
			else if(is_against_cpu()==0){
				winner =makeMove();
				//score1 =setScores(last_move[0],last_move[1],check);

				//showBoard();
				if(winner =='L' || winner =='S'|| winner =='U' || winner == 'E'){
					//showScore(_check);
					continue;
				}
				else if(winner == 'R'){
					reset();
					counter =0;
					continue;
				}
				if(winner == 'Q'){
					cout<<"Game Cancelled\n";
					//showScore(_check);
					delete[] _check;

					return;
				}
				//showScore(_check);
				if(winner == getCurrentPlayer())
				{
					cout<<(*this);

					cout<<"Winner:"<<winner<<endl;
					increaseCounter();
					game_continue = false;
					
					delete[] _check;
					
					return;
				}
				increaseCounter();

			}
			else if(is_against_cpu() == true && getCurrentPlayer()==O){
				cout<<"Computer's turn:\n";
				Cell temp=play();
				
				winner = check();
				Cell a=lastMove();
				cout << "Computer played to: ";
				a.getCoordinate();
				cout<<endl;

				if(temp.getVariable() == 'O')
				{
					last_move[0] = temp.getRow();
					last_move[1] =temp.getPosition();
					cout<<(*this);

					cout<<"Winner:O"<<endl;
					increaseCounter();
					game_continue = false;
					
					delete[] _check;
					
					return;
				}
				last_move[0] = temp.getRow();
				last_move[1] =temp.getPosition();
				increaseCounter();
				
			}
			
			delete[] _check;
		
		}
		
		cout<<"Copied game has already ended\nSee you next time\n";
	}


	bool AbstractHex :: is_load_save_command_taken(const string &input1 )const{
		return (input1.compare(0,4,"LOAD")==0 || input1.compare(0,4,"Load") == 0 || input1.compare(0,4,"load") == 0) || (input1.compare(0,4,"SAVE")==0 || input1.compare(0,4,"save")==0|| input1.compare(0,4,"Save") == 0);
	}
	bool AbstractHex ::isNumber(const string &indexCandidate)const{ // checks if string consist of only digits
	    int size=indexCandidate.length();
	    for(int i=0;i<size;i++){
	        if(indexCandidate[i]<'0' || indexCandidate[i]>'9')
	            return false;
	    }
	    return true;
	}
	bool AbstractHex :: is_setSize_taken(const string &input1)const{
		return (input1.compare(0,7,"setSize")==0 || input1.compare(0,7,"setsize") == 0 || input1.compare(0,7,"SetSize") == 0) || (input1.compare(0,7,"SETSIZE")==0 );
	}

	char AbstractHex :: getCommandfromInput(string& str,char &position,int &index)
	{
		stringstream ss;        	    
	    ss << str; 
	    string temp; 
	    string a;
	    string command;
	    int found; 
		
	    string save_or_load;
	    char coordinate;        
	    ss >> temp; 
		
	    if (stringstream(temp) >>a ){
		
	    	int size=a.length();
	        if(is_load_save_command_taken(a)){
	        	set_file_name("");
				command=a;
	                while(!ss.eof()){ // this loop allow us to take file name which consists of multiple words
	                    ss>>temp;
	                    if(stringstream(temp) >> a){
	                        //file_name+=(a+" ");                  
	                    	set_file_name(get_file_name()+a+" ");
	                    }
	                }
			
	                if(command[0]=='S' || command[0]=='s' ){
	                	return 'S'; // that implies save command and file name are taken
	                }
	                else{
	                	return 'L'; // that implies load command and file name are taken
	                }
	        }
	        else if(is_setSize_taken(a)){
	        	int _width,_height;
	        	ss>>_width;
	        	char x;
	        	ss>>x;
	        	ss>>_height;
	        	setSize(_width,_height);
	        	return 'E';
	        }
	        else if(a == "quit" || a=="Quit"){
	        	return 'Q';
	        }
	        else if(a == "reset" || a == "Reset"){
	        	return 'R';
	        }
	      
	        else if(size==1){
	                position=a[0];
	                ss>>temp;
	                if(stringstream(temp) >> index && isNumber(temp))
	                    return 'Y'; // that implies that coordinates taken
	                
	                else{ 
	                    cerr<<"Invalid Input\n";
	                    return 'a';
	                }
	        }
	        else if(size>1){
	                if(!(isNumber(a[0]))){
	                    position=a[0];
	                    index=0;
	                    for(int i=1;i<size;i++){
	                        
	                        if(isNumber(a[i])){ // iteration version of atoi
	                            index=index*10+a[i]-'0';
	                        }
	                        else{
	                            cerr<<"invalid input\n"; //if index has character other than digit
	                            return 'a';
	                            
	                        }
	                    }
			    return 'Y';// input coordinate taken succesfully    
	                }
	                else{
	                    cerr<<"Invalid Input\n";
	                    return 'a';
	                }
	        }   
	        else {
	            cerr<<"Command invalid\n";
	            return 'a';
	        }
	                         
	    }
	}
	char AbstractHex :: check(){
		bool reach_to_end=false;
		int Size = getSize();
		char player =getCurrentPlayer();
		if(player== X){
		// If it goes A to end then playerX wins, x value should be A to end that means we should go table[y][0] to table[y][size-1] consistently
			for(int i=0;i<Size;i++){
				if((*this)(i,0).getVariable()==player){
					reach_to_end=check_neighbors(i,0);
					if(reach_to_end==true){
						makeUpperCase(i,0);
						return player;
					}
				}
			}

		}
		else if(player == O){
			for(int i=0;i<Size;i++){
				if((*this)(0,i).getVariable()==player){
					reach_to_end=check_neighbors(0,i);
					if(reach_to_end==true){
						makeUpperCase(0,i);
						return player;
					}
				}
			}

		}
		return '\0';
	}
	bool AbstractHex ::check_neighbors(int y,int x){
		int Size=getSize();
		char player =getCurrentPlayer();
		if(y<0 || x< 0 || x>=Size || y>=Size || (*this)(y,x).getVariable()!=player || check_table[y][x]==true)
			return false;
		if((player==X && x==Size-1) || (player==O && y==Size-1) ) //we reach to destination		
			return true;
		

		check_table[y][x]=true; /* to protect infinite loop we put 'true' to our initial position so that these recursive calls cannot call it again because of the first if statement:*/
		bool b1=check_neighbors(y-1,x);
		bool b2=check_neighbors(y-1,x+1);
		bool b3=check_neighbors(y,x-1);
		bool b4=check_neighbors(y+1,x-1);
		bool b5=check_neighbors(y+1,x);
		bool b6=check_neighbors(y,x+1);
		check_table[y][x]=false; // clearing table
		bool won=b1||b2||b3||b4||b5||b6;//if one of them is true,then won is true
		return (won); //if one of them true return true else return false
	}
	void AbstractHex ::makeUpperCase(int y,int x){
		int Size =getSize();
		char player = getCurrentPlayer();
		if(y<0 || x< 0 || x>=Size || y>=Size || (*this)(y,x).getVariable()!=player) // (*this)(y,x)!=player checks if its . or other player or this position already was made uppercase
			return ;
		(*this)(y,x).makeUpperCase();

		makeUpperCase(y-1,x);
		makeUpperCase(y-1,x+1);
		makeUpperCase(y,x-1);
		makeUpperCase(y+1,x-1);
		makeUpperCase(y+1,x);
		makeUpperCase(y,x+1);
	}
	 

	bool AbstractHex :: readFromFile(const string & theFile){
		
		ifstream fp(theFile);
		char var;
		bool _against_cpu;
		int _size;
		int _counter;
		char _currentPlayer;
		

		if(!fp){
			cerr<<"There is no file which has name:"<<theFile<<endl;		
			return false;	
		}

		fp>>_against_cpu>>_size>>_currentPlayer>>_counter>>score1>>score2;
		set_against_cpu(_against_cpu);
		setCurrentPlayer(_currentPlayer);
		setSize(_size);
		setCounter(_counter);
		_size=getSize();

		AbstractHex :: createBoard();
		createBoard(); // create them again
		cerr<<"Tablo yeniden olusturuldu\n";
		fp>>(*this);

		int temp;
		int pos,row;
		char _var;
		
		if(is_against_cpu()){ // if against_cpu it should read value table of AI too
			for(int i=0;i<_size;i++){
				for(int j=0;j<_size;j++){
					fp>>value_table_of_AI[i][j];
				}
			}
		}
		cout<<"Game Loaded \nYou are playing against ";
		if(is_against_cpu())
			cout<<"computer\n";
		else
			cout<<"your friend\n";
		
		//showBoard();
		return true;
	}

	
	ostream & operator <<(ostream & outputStream, AbstractHex& h){
	 	int Size=h.getSize();
	    char letters='a';
		outputStream<<" ";
		for(int i=0;i<Size;i++){
			outputStream<<" "<<letters++;
		}
		outputStream<<endl;
		for(int i = 0; i < Size; ++i)
			{

				outputStream<<i+1<<" ";
				for(int a=0;a<i;a++){
					if(a==8){ // 2 digits ruin table to be able to prevent it I added this

					}
					else
						outputStream<<" ";
				}

				for(int x=0;x<Size; x++){

					outputStream<<(h(i,x).getVariable())<<" ";
					//hexCells[i][x].getCoordinate();
				}

				outputStream<<endl;
			}
		outputStream<<endl;
	    return outputStream;
	}
	istream & operator >>(istream & inputStream,AbstractHex & h){
		char unnecessary_char,cellVar;
		int unnecessary_number;
		for(int i=0;i<h.getSize();i++){
			inputStream>>unnecessary_char; // reads a b c d
		}
		for(int i=0;i<h.getSize();i++){

			inputStream>>unnecessary_number; // reads 1,2,3
			cellVar =' ';
			for (int j = 0; j < h.getSize(); ++j)
			{	

				inputStream>>cellVar;

				h(i,j).setVariable(cellVar);

			}
			
		}

		return inputStream;
	}

	int AbstractHex :: setScores(int y,int x,bool *_check){

		int indexHelper[6][2]={{-1,0},{-1,+1},{0,-1},{1,-1},{1,0},{0,1}}; // add elements to reach all neighbors 
		int a;
		int sum=0;
		if(valid_point_but_full(y,x) && ((*this)(y,x).getVariable() == getCurrentPlayer() || (*this)(y,x).getVariable() == getCurrentPlayer()+'A'-'a') && check_table[y][x]==false){
			check_table[y][x]=true;
			if(getCurrentPlayer() == X)
				a=x;
			
			else
				a=y;
			for(int i=0;i<6;i++){
				sum+= setScores(indexHelper[i][0]+y,indexHelper[i][1]+x,_check);
			}
			if(_check[a]==false)
			{	
				_check[a]=true;
				return 10+sum;
			}
			return sum;
		}
		return 0;
	}
	//----------------------------------------------------hw5

	void  AbstractHex :: print(){
		cout<<(*this);
	}
	void AbstractHex ::writeToFile(const string &theFile){
		
		ofstream fp;
		//set_file_name(theFile);
		fp.open(theFile);
		fp<<is_against_cpu()<<" "<<getSize()<<" "<<getCurrentPlayer()<<" "<<getCounter()<<" "<<score1<<" "<<score2<<endl;
		fp<<(*this);
		
		if(is_against_cpu()){ // the value table which holds information for AI to make it make moves little more smarter to make
			for(int i=0;i<getSize();i++){
				for(int j=0;j<getSize();j++){
					fp<<value_table_of_AI[i][j]<<" ";
				}
				fp<<"\n";
			}
		}
		fp.close();
		cout<<"Game Saved\n";
		cout<<(*this);
		//showBoard();	
		
	}
	 void AbstractHex ::play(int y,int x){ 
		char player = getCurrentPlayer();
	//	(*this)(y,x).setVariable(player);
		(*this)(y,x).setVariable(player);
	}
	const Cell& AbstractHex :: play(){
	 // PLAY AI
		char player = getCurrentPlayer();
		int Size = getSize();
		int max=0;
		int tempy=0,tempx=0;
		for(int i=0;i<Size;i++){
			for(int j=0;j<Size;j++){
				if(valid_point(i,j)){
					if(max<value_table_of_AI[i][j] ){ // we will not use these values in here just to be able to do less iteration I keep them I will use them later in this function
						if(neighbor_both_x_and_o(i,j)){ // to protect it put o in the middle of bunch of x
							value_table_of_AI[i][j]+=20;	
											
						}
						max=value_table_of_AI[i][j];
						tempy=i;
						tempx=j;
					}
					(*this)(i,j).setVariable(getCurrentPlayer()); //if there is 1 move to win do not hesitate to do it
									
					auto winner=check(); // auto was used in here
					if(winner==player){
						setLastMove(0,i);
						setLastMove(1,j);
						(*this)(i,j).setCoordinate(j+'A',i+1);

						//cout<<"Computer played to: "<<static_cast<char>('A'+j)<<" "<<i+1<<endl;
						
						return (*this)(i,j);
						//return winner;
										
					}				
					else{
						
						(*this)(i,j).setVariable(Empty); // if there is no chance to win with 1 move then continue
					}
				}
			}
		}
		/*
		int y=last_move[0];
		int x=last_move[1];
		*/
		int y=getLastMove(0);
		int x=getLastMove(1);

		bool is_there_move=is_there_chance_to_put_next_to_last_move(y,x);// returns true if it can change the table else false
		if(is_there_move){
			setLastMove(0,y);
			setLastMove(1,x);
			(*this)(y,x).setCoordinate(x+'A',y+1);

			return (*this)(y,x);// no need to check if the game ends because we now that there is no chance to win with 1 move 
		}
		
		// if you are here table stays same still and there is no place to put something next to last move and there is no chance to finish the game
		// tempy and tempx hold the y and x value of indexes which hold the maximum value which collected collect_information_for_AI function
		(*this)(tempy,tempx).setVariable(getCurrentPlayer());
		//cout<<"Computer played to:"<<static_cast<char>('A'+tempx)<<" "<<tempy+1<<endl;
		collect_information_for_AI(tempy,tempx,5);
		setLastMove(0,tempy);
		setLastMove(1,tempx);
		(*this)(tempy,tempx).setCoordinate(tempx+'A',tempy+1);

		return (*this)(tempy,tempx);
	}
	void AbstractHex :: reset(){
		for(int i=0;i<getSize();i++){
			for(int j=0;j<getSize();j++)
			{
				(*this)(i,j).setVariable(Empty);
				check_table[i][j]=false;
				if(against_cpu){
					value_table_of_AI[i][j] =0;
				}
			}
		}
		counter = 0;
	}
	void AbstractHex :: setSize(int width,int height){
		if(width != height || width<6 ){
			cerr<<"Invalid argumets\n";
			return;
		}
		setSize(width);
		counter = 0;
		//makeArraysEmpty();
		AbstractHex::createBoard();
		createBoard();

	}
	bool AbstractHex :: isEnd(){
		char _check=check();
		return (_check == '\0')?false : true; // if the game continues check returns '\0'
	}
	bool AbstractHex :: operator ==(AbstractHex & other){
		
		if(getSize()!=other.getSize()) return false;

		for(int i=0;i<getSize();i++){
			for(int j=0;j<getSize();j++){
				if((*this)(i,j).getVariable() != other(i,j).getVariable())
					return false;
			}
		}
		return true;
	}
	const Cell& AbstractHex ::lastMove()throw(ThereIsNoLastMove){
		if(counter == 0) 
			throw ThereIsNoLastMove();

		return (*this)(getLastMove(0),getLastMove(1));
	}
	int AbstractHex :: numberOfMoves()
	{ 
		return getCounter();
	}
	void AbstractHex :: createBoard(){
		int Size=getSize();
		check_table.resize(1);
		value_table_of_AI.resize(1);
	    
	    for(int i=1;i<Size;i++){
	    	check_table.push_back(check_table[0]);
	    	
	    	if(is_against_cpu()){
	    		value_table_of_AI.push_back(value_table_of_AI[0]);
	    	}
	    	
	    }
	    for(int i=0;i<Size;i++){
	        check_table[i]=vector<bool>(Size);
	        if(is_against_cpu())
	        	value_table_of_AI[i] = vector<int>(Size);


	    }
	    for(int i=1;i<=Size;i++){
	    	for(char j='A';j<Size+'A';j++){
	    		check_table[i-1][j-'A'] = false; // if the coordinate has false in it, check function will understand that it is not visited
	    		if(is_against_cpu())
	    			value_table_of_AI[i-1][j-'A'] =0;
	    	}
	    }
	}
	void AbstractHex :: createBoard(AbstractHex& rSide){
	    
	    AbstractHex::createBoard();
		int Size=getSize();

	    for(int i=1;i<=Size;i++){

	    	for(char j='A';j<Size+'A';j++){
	    		check_table[i-1][j-'A'] = rSide.check_table[i-1][j-'A']; // if the coordinate has false in it, check function will understand that it is not visited
	    		if(is_against_cpu())
	    			value_table_of_AI[i-1][j-'A'] =rSide.value_table_of_AI[i-1][j-'A'];
	    	}
	    }
	    
		
	}

}