#include"func.h"
inline void Hex :: set_index_of_game(int index) {index_of_game = index;}
inline void Hex :: increase_index_of_game(){index_of_game++;}
inline int Hex :: get_index_of_game()const{return index_of_game;}
//inline int Hex :: width_height()const {return getSize();}
void Hex :: Cell :: setCoordinate(char pos,int row){
	position = pos;
	rowNum = row;
}
void Hex :: Cell :: getCoordinate()const{
	cout<<position<<rowNum<<" ";
}


Hex :: Hex(){
	set_index_of_game(index);
	
	//index_of_game = index;
    setSize();
    setGameType();
    createBoard();
    cout<<(*this);
    
    index++;
}
Hex :: Hex (int _size){
	//index_of_game = index;
	set_index_of_game(index);

	setSize(_size);
	setGameType();
	createBoard();
	cout<<(*this);
	//showBoard();
	index++;

}
Hex :: Hex(int _size,int _against_cpu)
{	
	//index_of_game = index;
	set_index_of_game(index);
	setSize(_size);
	setGameType(_against_cpu);
	createBoard();
	cout<<(*this);
	//showBoard();
	index++;

}

Hex :: Hex(const Hex &rSide){
	// automatic variables
	//index_of_game = rSide.index_of_game;
	set_index_of_game(index);
	size =rSide.size;
	against_cpu= rSide.against_cpu;
	is_cinCalled = rSide.is_cinCalled;
	counter=rSide.counter;
	currentPlayer = rSide.currentPlayer;
	file_name = rSide.file_name;
	game_continue = rSide.game_continue;
	last_move[0] = rSide.last_move[0];
	last_move[1] = rSide.last_move[1];
	// dynamic copies
	index++;
	createBoard(rSide);

	cout<<"Game Loaded with the help of copy constructer\nYou are playing against: ";
	if(against_cpu)
		cout<<"CPU\n\n";
	else
		cout<<"Your friend\n\n";


	cout<<(*this);
}
const Hex& Hex :: operator =(const Hex &rSide){
	if(this == &rSide){
		return *this;
	}
	//index_of_game = rSide.index_of_game;
	
	//is_cinCalled = rSide.is_cinCalled;
	counter=rSide.counter;
	currentPlayer = rSide.currentPlayer;
	file_name = rSide.file_name;
	game_continue = rSide.game_continue;
	last_move[0] = rSide.last_move[0];
	last_move[1] = rSide.last_move[1];

	makeArraysEmpty();

	against_cpu= rSide.against_cpu;
	size =rSide.size;

	createBoard(rSide);
	cout<<"Game Loaded with the help of overloaded assignment operator\nYou are playing against: ";
	if(against_cpu)
		cout<<"CPU\n\n";
	else
		cout<<"Your friend\n\n";
	cout<<(*this);
	return *this;
}
Hex :: ~Hex(){
	if(hexCells)
	{
		for(int i=0;i<getSize();i++){
			delete[] hexCells[i];
			
		}

		delete[] hexCells;
	}

	if(check_table)
	{
		for(int i=0;i<getSize();i++){

			delete[] check_table[i];
		}

		delete[] check_table;
	}
	if(against_cpu && value_table_of_AI){
		for(int i=0;i<getSize();i++){
			delete[] value_table_of_AI[i];
		}
		delete[] value_table_of_AI;
		
	}

}

void Hex :: Cell :: setVariable(char player){
    if(player == X || player==O || player == X -'a' + 'A' || player == O -'a' +'A' || player == Empty)
  		variable = player;
    else
       	cerr<<"Invalid player\n";  
}
void Hex::setSize(){
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
void Hex::setSize(int _size){
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
void Hex::setGameType(){
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
void Hex::setGameType(int _against_cpu){
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
void Hex :: makeArraysEmpty(){
	for(int i=0;i<getSize();i++){
		delete[] hexCells[i];

		delete[] check_table[i];
		if(is_against_cpu())
			delete[] value_table_of_AI[i];
	}
	delete[] movements;
	delete[]hexCells;
	
	delete[]check_table;

	if(against_cpu){

		delete[]value_table_of_AI;
		
	}


	//hexCells.clear();
	/*check_table.clear();
	value_table_of_AI.clear();
	hexCells = vector<vector<Cell> >(1);
	check_table = vector<vector<bool> >(1);
	value_table_of_AI = vector<vector<int> >(1);
	*/
}
void Hex :: createBoard() {
    int Size=getSize();
    
    /*for(int i=1;i<Size;i++){
    	hexCells.push_back(hexCells[0]);
    	check_table.push_back(check_table[0]);
    	if(is_against_cpu())
    		value_table_of_AI.push_back(value_table_of_AI[0]);
    	
    }*/
    hexCells = new Cell* [getSize()];
    check_table = new bool* [getSize()];
    movements = new Cell[getSize()*getSize()]; // The board can hold size² number of cells 
    if(is_against_cpu())
    	value_table_of_AI = new int* [getSize()];
    /*
    for(int i=0;i<Size;i++){
        hexCells[i]=vector<Cell>(Size);
        check_table[i]=vector<bool>(Size);
        if(is_against_cpu())
        	value_table_of_AI[i] = vector<int>(Size);
    }
    */
    for(int i=0;i<getSize();i++){
    	hexCells[i] = new Cell [getSize()];
    	check_table[i] = new bool [getSize()];
    	if(is_against_cpu()){
    		value_table_of_AI[i]=new int [getSize()];
    	}
    }
    for(int i=1;i<=Size;i++){
    	for(char j='A';j<Size+'A';j++){
    		hexCells[i-1][j-'A'].setCoordinate(j,i);
    		check_table[i-1][j-'A'] = false; // if the coordinate has false in it, check function will understand that it is not visited
    		if(is_against_cpu())
    			value_table_of_AI[i-1][j-'A'] =0;
    	}
    }
}
void Hex :: createBoard(const Hex& rSide){
	int Size=getSize();
    
    /*for(int i=1;i<Size;i++){
    	hexCells.push_back(hexCells[0]);
    	check_table.push_back(check_table[0]);
    	if(is_against_cpu())
    		value_table_of_AI.push_back(value_table_of_AI[0]);
    	
    }*/
    hexCells = new Cell* [getSize()];
    check_table = new bool* [getSize()];
    movements = new Cell[getSize()*getSize()]; // The board can hold size² number of cells 
    if(is_against_cpu())
    	value_table_of_AI = new int* [getSize()];
    /*
    for(int i=0;i<Size;i++){
        hexCells[i]=vector<Cell>(Size);
        check_table[i]=vector<bool>(Size);
        if(is_against_cpu())
        	value_table_of_AI[i] = vector<int>(Size);
    }
    */
    for(int i=0;i<getSize();i++){
    	hexCells[i] = new Cell [getSize()];
    	check_table[i] = new bool [getSize()];
    	if(is_against_cpu()){
    		value_table_of_AI[i]=new int [getSize()];
    	}
    }
    for(int i=1;i<=Size;i++){
    	for(char j='A';j<Size+'A';j++){
    		hexCells[i-1][j-'A'].setCoordinate(j,i);
    		char var=rSide.hexCells[i-1][j-'A'].getVariable();
    		hexCells[i-1][j-'A'].setVariable(var);
    		check_table[i-1][j-'A'] = rSide.check_table[i-1][j-'A']; // if the coordinate has false in it, check function will understand that it is not visited
    		if(is_against_cpu())
    			value_table_of_AI[i-1][j-'A'] =rSide.value_table_of_AI[i-1][j-'A'];
    	}
    }
    
	for(int i=0;i<counter;i++){
		char pos=rSide.movements[i].getPosition()+'A';
		int row=rSide.movements[i].getRow()+1;
		char _var = rSide.movements[i].getVariable();
		movements[i].setCoordinate(pos,row);
		movements[i].setVariable(_var);
	
	}
}
void Hex :: showBoard() const {
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
				cout<<hexCells[i][x].getVariable()<<" ";
				//hexCells[i][x].getCoordinate();
			}
			cout<<endl;
		}
	cout<<endl;
}
char Hex :: makeMove(){
	
	char letter='\0';
	string input,file_name;
	char flag='\0';
	int x=-1;
	int y=-1; 
	char player=getCurrentPlayer();
	bool invalid = true;
	int game_continue=1;
	//player = getCurrentPlayer();
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
			//if(letter >= 'A' && letter <='Z' && y>=0 && y< getSize() && x>=0 && x< getSize() && hexCells[y][x].getVariable() == Empty){
			if(y>=0 && y<getSize() && x>=0 && x<getSize() && hexCells[y][x].getVariable() == Empty){
				play(y,x); // puts to player's icon in the y,x coordinate
				if(against_cpu)		
					collect_information_for_AI(y,x,5);//this function increase the value of the positions which ar near last move by 5
						
				// computer will consider where the last move is			
				setLastMove(0,y);
				setLastMove(1,x);
				movements[counter].setCoordinate(letter,y+1);
				movements[counter].setVariable(getCurrentPlayer());
				/*last_move[0]=y;
				last_move[1]=x;
				*/
				invalid=false; // only point to leave loop is where the coordinates taken
			}
			
			else{
				cout<<(*this);
				//showBoard();
				cerr<<"Invalid input. Try again "<<endl;
			}
		} //flag=='Y' endf
		else if(flag=='S'){
			saveGame();			
		}
		else if(flag=='L'){
			bool isFileOK=loadGame();			
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
		else if(flag == 'Q'){

			return 'Q';
		}
		//else if((flag == 'U' && against_cpu) || (flag == 'u' && against_cpu) || ){ // if user enters --undo or undo or user is playing against cpu then flag == 'U' 
		else if(((flag =='U' || flag == 'u') && against_cpu) || (flag =='U' && !against_cpu)){
			--(*this); // takes 2 step back if user writes --undo
			score1=0;
			score2=0;
			return 'U';				
		}
		else if(flag =='u' && !against_cpu ){ // if user enters undo-- flag=='u'
			(*this)--;//takes 1 step back if user writes undo--
			//if(getCurrentPlayer() ==X)
				score1=0;
			//else
				score2=0;
			return 'U'; // main do not have to know that how much step we went back
		}
		
		else{
			cout<<(*this);

		}
	}
	return check();
}
inline void Hex ::play(int y,int x){ 
	char player = getCurrentPlayer();
	hexCells[y][x].setVariable(player);
}
bool Hex :: neighbor_both_x_and_o(int y,int x)const{
	bool neighbor_of_x=false;
	bool neighbor_of_o=false;
	int indexHelper[6][2]={{-1,0},{-1,+1},{0,-1},{1,-1},{1,0},{0,1}};
	for(int i=0;i<6;i++){
		if(valid_point_but_full(y+indexHelper[i][0],x+indexHelper[i][1]) && hexCells[y+indexHelper[i][0]][x+indexHelper[i][1]].getVariable() == X){
			neighbor_of_x=true;
			break;
		}

	}
	
	if(neighbor_of_x){
		for(int i=0;i<6;i++){
			if(valid_point_but_full(y+indexHelper[i][0],x+indexHelper[i][1]) && hexCells[y+indexHelper[i][0]][x+indexHelper[i][1]].getVariable() == O){
				neighbor_of_x=true;
				break;
			}
		}
	}
	
	return (neighbor_of_x && neighbor_of_o);
}
const Hex::Cell& Hex :: play(){
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
				hexCells[i][j].setVariable(getCurrentPlayer()); //if there is 1 move to win do not hesitate to do it
								
				auto winner=check(); // auto was used in here
				if(winner==player){
					cout<<"Computer played to: "<<static_cast<char>('A'+j)<<" "<<i+1<<endl;
					return hexCells[i][j];
					//return winner;
									
				}				
				else{
					
					hexCells[i][j].setVariable(Empty); // if there is no chance to win with 1 move then continue
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
	if(is_there_move)
		return hexCells[y][x];// no need to check if the game ends because we now that there is no chance to win with 1 move 
	
	// if you are here table stays same still and there is no place to put something next to last move and there is no chance to finish the game
	// tempy and tempx hold the y and x value of indexes which hold the maximum value which collected collect_information_for_AI function
	hexCells[tempy][tempx].setVariable(getCurrentPlayer());
	cout<<"Computer played to:"<<static_cast<char>('A'+tempx)<<" "<<tempy+1<<endl;
	collect_information_for_AI(tempy,tempx,5);
	return hexCells[tempy][tempx];
}
inline bool  Hex ::valid_point_but_full(int y,int x)const{
	return(y>=0 && x>=0 && y<getSize() && x<getSize());
}

int Hex :: number_of_neighbors_same_type(int y,int x)const{
	int number_of_neighbors=0;
	char player = getCurrentPlayer();
	int indexHelper[6][2]={{-1,0},{-1,+1},{0,-1},{1,-1},{1,0},{0,1}};
	for(int i=0;i<6;i++){
		if(valid_point_but_full(y+indexHelper[i][0],x+indexHelper[i][1]) && hexCells[y+indexHelper[i][0]][x+indexHelper[i][1]].getVariable()==player)
			number_of_neighbors++;
	}
	return number_of_neighbors;
}
bool Hex :: valid_point(int y,int x)const{		
	return (y>=0 && x>=0 && y<getSize() && x<getSize() && hexCells[y][x].getVariable()==Empty);
}
void Hex :: collect_information_for_AI(int y,int x,int add_value){
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
void Hex :: fill_temp(int temp[6],int arry[6],int arrx[6],int y,int x)const{
	int indexHelper[6][2]={{-1,0},{-1,+1},{0,-1},{1,-1},{1,0},{0,1}};
	for(int i=0;i<6;i++){
		if(valid_point(y+indexHelper[i][0],x+indexHelper[i][1])){
			arry[i]=y+indexHelper[i][0];
			arrx[i]=x+indexHelper[i][1];
			temp[i]=number_of_neighbors_same_type(arry[i],arrx[i]);
		}
	}
}

bool Hex :: is_there_chance_to_put_next_to_last_move(int &y,int &x){
	x=-1;
	y=-1;
	int arrx[6]={-1,-1,-1,-1,-1,-1};
	int arry[6]={-1,-1,-1,-1,-1,-1};
//,y1=0,x1=0, y2=0,x2=0, y3=0,x3=0, y4=0,x4=0, y5=0,x5=0, y6=0,x6=0;
	int temp[6]={-1,-1,-1,-1,-1,-1};
	int number_of_connections_with_same_type=0;
	int max=0;
	/*int last_y=last_move[0];
	int last_x=last_move[1];
	*/
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
	
	hexCells[y][x].setVariable(getCurrentPlayer());
	cout<<"Computer played to:"<<static_cast<char>('A'+x)<<" "<<y+1<<endl;
	return true; // if one of the condition holds return true player1's turn
}
void Hex :: showScore(bool *_check){
	for(int i=0;i<getSize();i++){
		for(int j=0;j<getSize();j++){
			check_table[i][j] = false;
		}
	}
	int tempScore;
	for(int i=0;i<getSize();i++){
		for (int j = 0; j< getSize(); j++)
		{
			char cell=hexCells[i][j].getVariable();
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
void Hex :: playGame(){
	bool *_check;
	if(is_cinCalled){
			cin.ignore();
			set_is_cinCalled(false);
	}
	char winner='\0';
	while(game_continue){
		_check=new bool[getSize()];
		for(int i=0;i<getSize();i++){
			_check[i]=false;
		}
		//showScore(_check);

		if(getCurrentPlayer() == X){
			winner =makeMove();
			if(winner == 'Q'){
				cout<<"Game Cancelled\n";
				numbers_of_nonEmpty_cells += (to_string(getCounter())+" ");
				// we dont change that game continues to be able to keep playing it when we call copy construter with this Hex game
				//showScore(_check);
				
				delete[] _check;
				return;
			}
			/*int score =setScores(last_move[0],last_move[1],_check);
			if(score > score1)
				score1=score;
			*/
			showScore(_check);

			cout<<(*this);
			//cout<<"X score: "<<score1<<endl;
			//showBoard();
			if(winner == getCurrentPlayer())
			{

				cout<<"Winner:"<<winner<<endl;
				//cout<<"Score : "<<getSize()*10<<endl; // no need to call showScore function max point must be shown and this works other function does not
				increaseCounter();
				
				numbers_of_nonEmpty_cells += (to_string(getCounter())+" ");
				game_continue = false;
				delete[] _check;
				
				return;
			}
			if(winner =='L' || winner == 'S' || winner =='U'){
				showScore(_check);
				continue;
			}
			
			//movements[counter]=
			increaseCounter();
		}
		else if(is_against_cpu()==0){
			winner =makeMove();
			//score1 =setScores(last_move[0],last_move[1],check);

			cout<<(*this);
			//showBoard();
			if(winner =='L' || winner =='S'|| winner =='U'){
				showScore(_check);
				continue;
			}
			if(winner == 'Q'){
				cout<<"Game Cancelled\n";
				numbers_of_nonEmpty_cells += (to_string(getCounter())+" ");
				showScore(_check);
				delete[] _check;

				return;
			}
			showScore(_check);
			if(winner == getCurrentPlayer())
			{
				cout<<"Winner:"<<winner<<endl;
				increaseCounter();
				game_continue = false;
				
				numbers_of_nonEmpty_cells += (to_string(getCounter())+" ");
				delete[] _check;
				
				return;
			}
			increaseCounter();

		}
		else if(is_against_cpu() == true && getCurrentPlayer()==O){
			cout<<"Computer's turn:\n";
			Hex :: Cell temp=play();
			movements[getCounter()]=temp; // there is no pointer in Cell so default assignment is enough
			winner = check();
			//winner =play().getVariable();

			cout<<(*this);
			//showBoard();
			//if(winner == getCurrentPlayer() || (winner +('a'-'A') == getCurrentPlayer()))
			if(temp.getVariable() == 'O')
			{
				last_move[0] = temp.getRow();
				last_move[1] =temp.getPosition();
				showScore(_check);
				cout<<"Winner:O"<<endl;
				increaseCounter();
				game_continue = false;
				
				numbers_of_nonEmpty_cells += (to_string(getCounter())+" ");
				delete[] _check;
				
				return;
			}
			last_move[0] = temp.getRow();
			last_move[1] =temp.getPosition();
			showScore(_check);
			increaseCounter();
			
		}
		
		delete[] _check;
	
	}
	cout<<"Copied game has already ended\nSee you next time\n";
}


inline bool Hex :: is_load_save_command_taken(const string &input1 )const{
	return (input1.compare(0,4,"LOAD")==0 || input1.compare(0,4,"Load") == 0 || input1.compare(0,4,"load") == 0) || (input1.compare(0,4,"SAVE")==0 || input1.compare(0,4,"save")==0|| input1.compare(0,4,"Save") == 0);
}
bool Hex ::isNumber(const string &indexCandidate)const{ // checks if string consist of only digits
    int size=indexCandidate.length();
    for(int i=0;i<size;i++){
        if(indexCandidate[i]<'0' || indexCandidate[i]>'9')
            return false;
    }
    return true;
}

char Hex :: getCommandfromInput(string& str,char &position,int &index)
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
        else if(a == "quit" || a=="Quit"){
        	return 'Q';
        }
        else if(a == "undo" || a=="Undo" || a=="UNDO" || a == "--undo" || a=="--Undo" || a=="--UNDO"){
        	return 'U';
        }
        else if(a == "undo--" || a=="Undo--" || a=="UNDO--"){
        	return 'u';
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
    return '\0';
}
char Hex :: check(){
	bool reach_to_end=false;
	int Size = getSize();
	char player =getCurrentPlayer();
	if(player== X){
	// If it goes A to end then playerX wins, x value should be A to end that means we should go table[y][0] to table[y][size-1] consistently
		for(int i=0;i<Size;i++){
			if(hexCells[i][0].getVariable()==player){
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
			if(hexCells[0][i].getVariable()==player){
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
bool Hex ::check_neighbors(int y,int x){
	int Size=getSize();
	char player =getCurrentPlayer();
	if(y<0 || x< 0 || x>=Size || y>=Size || hexCells[y][x].getVariable()!=player || check_table[y][x]==true)
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
void Hex ::makeUpperCase(int y,int x){
	int Size =getSize();
	char player = getCurrentPlayer();
	if(y<0 || x< 0 || x>=Size || y>=Size || hexCells[y][x].getVariable()!=player) // hexCells[y][x]!=player checks if its . or other player or this position already was made uppercase
		return ;
	hexCells[y][x].makeUpperCase();

	makeUpperCase(y-1,x);
	makeUpperCase(y-1,x+1);
	makeUpperCase(y,x-1);
	makeUpperCase(y+1,x-1);
	makeUpperCase(y+1,x);
	makeUpperCase(y,x+1);
}
void Hex :: Cell :: makeUpperCase(){
	setVariable(getVariable() +'A' -'a');
} 
void Hex ::saveGame()const{
	
	ofstream fp;
	fp.open(get_file_name());
	fp<<is_against_cpu()<<" "<<getSize()<<" "<<getCurrentPlayer()<<" "<<getCounter()<<" "<<score1<<" "<<score2<<endl;
	fp<<(*this);
	/*for(int i=0;i<getSize();i++){
		for(int j=0;j<getSize();j++){
			fp<<hexCells[i][j].getVariable();
		}
		fp<<"\n";
	}*/
	fp<<"-1\n";// to indicate that these are movements
	for(int i=0;movements[i].getVariable()!=Empty;i++){
		fp<<movements[i].getPosition()<<" "<<movements[i].getRow()<<movements[i].getVariable()<<endl;
	}
	fp<<"-1"<<endl;// ends of movements
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
bool Hex :: loadGame(){
	
	ifstream fp(get_file_name());
	char var;
	bool _against_cpu;
	int _size;
	int _counter;
	char _currentPlayer;
	

	if(!fp){
		cerr<<"There is no file which has name:"<<get_file_name()<<endl;		
		return false;	
	}
	if(getSize()>0) // If game has just started there is no array to clear
		makeArraysEmpty();
	fp>>_against_cpu>>_size>>_currentPlayer>>_counter>>score1>>score2;
	set_against_cpu(_against_cpu);
	setCurrentPlayer(_currentPlayer);
	setSize(_size);
	setCounter(_counter);
	_size=getSize();
	/*if(size>0)
		makeArraysEmpty(); // make all Arrays empty
	*/
	
	createBoard(); // create them again
	fp>>(*this);
	/*for(int i=0;i<_size;i++){
		for(int j=0;j<_size;j++){
			fp>>var;
			hexCells[i][j].setVariable(var);
		}
	}*/
	int temp;
	int pos,row;
	char _var;
	fp>>temp; // reads -1
	for(int i=0;i<counter;i++){
		fp>>pos;
		fp>>row;
		fp>>_var;
		movements[i].setCoordinate(pos+'A',row+1);
		movements[i].setVariable(_var);
	}
	fp>>temp;//reads -1
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
int Hex :: getNumberOfNonEmptyCells()const{
    stringstream ss;        	    
	ss << numbers_of_nonEmpty_cells; 
	int temp; 		
	int found; 
	int i=0;
	while(1){
		ss>>temp;
		if(get_index_of_game()==i){
			return temp;
		}
		i++;
	}
			
    		
}
bool Hex :: compare(const Hex &other)const{
	return (getNumberOfNonEmptyCells() > other.getNumberOfNonEmptyCells());
}
bool Hex :: operator == (const Hex &other)const{
	return (getNumberOfNonEmptyCells() == other.getNumberOfNonEmptyCells());
}
void Hex :: operator --() // 2 steps back 
{ // if we are playing against cpu then this function will work 
	if(counter == 0)
		return;
	movements[counter-1].setVariable(Empty);
	if(counter>1)
		movements[counter-2].setVariable(Empty);
	
	hexCells[movements[counter-1].getRow()][movements[counter-1].getPosition()].setVariable(Empty);
	if(against_cpu)
		collect_information_for_AI(movements[counter-1].getRow(),movements[counter-1].getPosition(),-5);// -5 because we have added +5 previously when there is a player in there
	if(counter>1){
		hexCells[movements[counter-2].getRow()][movements[counter-2].getPosition()].setVariable(Empty);
		if(against_cpu)
			collect_information_for_AI(movements[counter-2].getRow(),movements[counter-2].getPosition(),-5);// -5 because we have added +5 previously when there is a player in there
		
	}
	if(counter>1){
		counter-=2;
	}
	else if(counter==1){
		counter--;
	}
	else{
		return;
	}
}
void Hex :: operator --(int ignoreMe) // 1 steps back
{
	if(counter == 0)
		return;
	movements[counter-1].setVariable(Empty);
	
	hexCells[movements[counter-1].getRow()][movements[counter-1].getPosition()].setVariable(Empty);
	/*cout<<"**************"<<endl;
	showBoard();
	cout<<"**************"<<endl;
	*/
	if(counter>1){
		counter--;
	}
	else{
		return;
	}
}
ostream & operator <<(ostream & outputStream,const Hex& h){
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
				outputStream<<h.hexCells[i][x].getVariable()<<" ";
				//hexCells[i][x].getCoordinate();
			}
			outputStream<<endl;
		}
	outputStream<<endl;
    return outputStream;
}
istream & operator >>(istream & inputStream,Hex & h){
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
			h.hexCells[i][j].setVariable(cellVar);

		}
		
	}
	return inputStream;
}

int Hex :: setScores(int y,int x,bool *_check){

	int indexHelper[6][2]={{-1,0},{-1,+1},{0,-1},{1,-1},{1,0},{0,1}}; // add elements to reach all neighbors 
	int a;
	int sum=0;
	if(valid_point_but_full(y,x) && (hexCells[y][x].getVariable() == getCurrentPlayer() || hexCells[y][x].getVariable() == getCurrentPlayer()+'A'-'a') && check_table[y][x]==false){
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

