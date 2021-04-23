#include"myHeader.h"


int takeSize(){
	bool invalid=true;
	int size=0;
	while(invalid) {
		cout<<"Enter the board size (range is 6 to 12): ";
		cin>>size;
		if(size>5 && size<13){ // table should be in this range
			invalid=false;
		}
		else{
			cout<<"Invalid input try again"<<endl;
		}
	}
	return size;
}
void showTable(char table[][12],int size){
	char letters='a';
	cout<<" ";
	for(int i=0;i<size;i++){
		cout<<" "<<letters++;
	}
	cout<<endl;
	for(int i = 0; i < size; ++i)
		{
			cout<<i+1<<" ";
			for(int a=0;a<i;a++){
				if(a==8){ // 2 digits ruin table to be able to prevent it I added this

				}
				else
					cout<<" ";
			}
			for(int x=0;x<size; x++){
				cout<<table[i][x]<<" ";
			}
			cout<<endl;
		}
	cout<<endl;
}
void play(char table[][12],int size,bool against_cpu){
	//int upper_limit_for_counter=size*size;
	int counter=0;
	int check_table[12][12]={0};
	char a;
	int winner=0;
	int upper_limit_for_counter=size*size;
	int last_move[2];
	int value_table_of_AI[12][12]={0};
	while(counter != upper_limit_for_counter){ // if table is filled then stop playing

		if(counter%2==0){
			a='x';
			winner=yourTurn(table,size,a,check_table,last_move,value_table_of_AI,against_cpu);
			if(winner==a){
				showTable(table,size);
			
				cout<<endl<<endl<<"Winner:"<<a<<endl;

				return;
			}
 		}
		else if(against_cpu){
			a='o';
			
			winner=play_AI(table,size,a,check_table,last_move,value_table_of_AI);
			if(winner==a){
				showTable(table,size);
				cout<<endl<<endl<<"Winner:"<<a<<endl;

				return;		
			}
		}
		else{
			a='o';
			winner=yourTurn(table,size,a,check_table,last_move,value_table_of_AI,against_cpu);
			if(winner==a){
				showTable(table,size);

				cout<<endl<<endl<<"Winner:"<<a<<endl;

				return;
			}
		}


		showTable(table,size);
		counter++;
	}
}
bool select_game_type(){
	bool invalid=true;
	bool choice=0;
	while(invalid) {
		cout<<"Enter 0 to play with your friend\n"<<"Enter 1 to play against computer"<<endl<<"Answer: ";
		cin>>choice;
		if(choice ==1 || choice ==0){ // input should be in this range
			invalid=false;
		}
		else{
			cout<<"Invalid input try again"<<endl;
		}
	}
		return (choice);
}
int yourTurn(char table[][12],int size,char player,int check_table[][12],int last_move[2],int value_table_of_AI[][12],bool against_cpu){
// with a parameter when we write yourTurn function we will able to understand which sides are wanted to connected
//if if returns 0 game continues, if it returns int value of 'player' then the player wins
	char letter;
	int x,y;
	bool invalid=true;
	int game_continue=1;
	while(invalid){ // ask until take valid point
		cout<<"Enter the position:";// such as: A 5, B 2, C 10
		cin>>letter>>y;
		
		if(letter >= 'a' && letter <='z') // if user enters lowercase,make it uppercase
			letter=letter-'a'+'A';
		/* if input is A 1 we should use the index [0][0] so we made necessary changes*/
		x=letter-'A';
		y--;
		if(letter >= 'A' && letter <='Z' && y>=0 && y< size && x>=0 && x<= size && table[y][x] =='.'){
			table[y][x]=player;
			if(against_cpu)		
				collect_information_for_AI(table,size,y,x,value_table_of_AI,5);//this function increase the value of the positions which ar near last move by 5
						
			// computer will consider where the last move is			
			last_move[0]=y;
			last_move[1]=x;
			invalid=false;
		}
		else{
			cout<<"Invalid input. Try again "<<endl;
		}

	}
	cout<<endl;
	return check(table,size,player,check_table);
}
int play_AI(char table[][12],int size,char player,int check_table[][12],int last_move[2],int value_table_of_AI[][12]){
	int winner=0;	
	int max=0;
	int tempy=0,tempx=0;
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(valid_point(table,size,i,j)){
				if(max<value_table_of_AI[i][j]){ // we will not use these values in here just to be able to do less iteration I keep them I will use them later in this function
					if(neighbor_both_x_and_o(table,size,i,j)){ // to protect it put o in the middle of bunch of x
						value_table_of_AI[i][j]+=20;	
										
					}
					max=value_table_of_AI[i][j];
					tempy=i;
					tempx=j;
				}				
				table[i][j]=player; //if there is 1 move to win do not hesitate to do it
								
				winner=check(table,size,player,check_table);
				if(winner==player){
					cout<<"Computer played to:"<<static_cast<char>('A'+j)<<" "<<i+1<<endl;
					return winner;
									
				}				
				else
					table[i][j]='.'; // if there is no chance to win with 1 move then continue
			}
		}
	}
	int y=last_move[0];
	int x=last_move[1];
	
	bool is_there_move=is_there_chance_to_put_next_to_last_move(table,size,player,y,x,value_table_of_AI);// returns true if it can change the table else false
	if(is_there_move)
		return 0;// no need to check if the game ends because we now that there is no chance to win with 1 move 
	
	// if you are here table stays same still and there is no place to put something next to last move and there is no chance to finish the game
	// tempy and tempx hold the y and x value of indexes which hold the maximum value which collected collect_information_for_AI function
	table[tempy][tempx]=player;
	cout<<"Computer played to:"<<static_cast<char>('A'+tempx)<<" "<<tempy+1<<endl;
	collect_information_for_AI(table,size,tempy,tempx,value_table_of_AI,5);
	return 0;
}
int check(char table[][12],int size,char player,int check_table[][12]){
	bool reach_to_end=0;
	if(player=='x'){
	// If it goes A to end then playerX wins, x value should be A to end that means we should go table[y][0] to table[y][size-1] consistently
		for(int i=0;i<size;i++){
			if(table[i][0]==player){
				reach_to_end=check_neighbors(table,size,i,0,player,check_table);
				if(reach_to_end==true){
					makeUpperCase(table,size,i,0,player);
					return player;
				}
			}
		}

	}
	else if(player=='o'){
		for(int i=0;i<size;i++){
			if(table[0][i]==player){
				reach_to_end=check_neighbors(table,size,0,i,player,check_table);
				if(reach_to_end==true){
					makeUpperCase(table,size,0,i,player);
					return player;
				}
			}
		}

	}
	return 0;
}
bool valid_point(char table[][12],int size,int y,int x){
		
	return (y>=0 && x>=0 && y<size && x<size && table[y][x]=='.');
}
bool valid_point_but_full(char table[][12],int size,int y,int x){
	return(y>=0 && x>=0 && y<size && x<size);
}
void collect_information_for_AI(char table[][12],int size,int y,int x,int value_table_of_AI[][12],int add_value){
	if(valid_point(table,size,y-1,x))
		value_table_of_AI[y-1][x] += add_value;
	if(valid_point(table,size,y-1,x+1))
		value_table_of_AI[y-1][x+1] += add_value;
	if(valid_point(table,size,y,x-1))
		value_table_of_AI[y][x-1] += (add_value+3);// left and right of opponent more important to be hold
	if(valid_point(table,size,y+1,x-1))
		value_table_of_AI[y+1][x-1] += add_value;
	if(valid_point(table,size,y+1,x))
		value_table_of_AI[y+1][x] += add_value;
	if(valid_point(table,size,y,x+1))
		value_table_of_AI[y][x+1] += (add_value+3);// left and right of opponent more important to be hold
}
bool check_neighbors(char table[][12],int size,int y,int x,char player,int check_table[][12]){
	if(y<0 || x< 0 || x>=size || y>=size || table[y][x]!=player || check_table[y][x]==1)
		return false;
	if((player=='x' && x==size-1) || (player=='o' && y==size-1) ){ //we reach to destination
		//table[y][x]=player+('A'-'a'); 
		return true;
	}

	check_table[y][x]=1; /* to protect infinite loop we put 1 to our initial position so that these recursive calls cannot call it again because of the first if statement:*/
																	/* if(check_table[y][x]==1) return false; */
	bool b1=check_neighbors(table,size,y-1,x,player,check_table);
	bool b2=check_neighbors(table,size,y-1,x+1,player,check_table);
	bool b3=check_neighbors(table,size,y,x-1,player,check_table);
	bool b4=check_neighbors(table,size,y+1,x-1,player,check_table);
	bool b5=check_neighbors(table,size,y+1,x,player,check_table);
	bool b6=check_neighbors(table,size,y,x+1,player,check_table);
	check_table[y][x]=0; // clearing table
	bool won=b1||b2||b3||b4||b5||b6;//if one of them is true,then won is true
	return (won); //if one of them true return true else return false
}
void makeUpperCase(char table[][12],int size,int y,int x,char player){
	if(y<0 || x< 0 || x>=size || y>=size || table[y][x]!=player) // table[y][x]!=player checks if its . or other player or this position already was made uppercase
		return ;
	table[y][x]=player+('A'-'a');

	makeUpperCase(table,size,y-1,x,player);
	makeUpperCase(table,size,y-1,x+1,player);
	makeUpperCase(table,size,y,x-1,player);
	makeUpperCase(table,size,y+1,x-1,player);
	makeUpperCase(table,size,y+1,x,player);
	makeUpperCase(table,size,y,x+1,player);
}
bool neighbor_both_x_and_o(char table[][12],int size,int y,int x){
	bool neighbor_of_x,neighbor_of_o;
	if(valid_point_but_full(table,size,y-1,x) && table[y-1][x]=='x'){
		neighbor_of_x=true;
		
	}
	else if(valid_point_but_full(table,size,y-1,x+1) && table[y-1][x+1]=='x'){
		neighbor_of_x=true;
	}	
	else if(valid_point_but_full(table,size,y,x-1) && table[y][x-1]=='x'){
		neighbor_of_x=true;
	}
	else if(valid_point_but_full(table,size,y+1,x-1) && table[y+1][x-1]=='x'){
		neighbor_of_x=true;
	}
	else if(valid_point_but_full(table,size,y+1,x) && table[y+1][x]=='x'){
		neighbor_of_x=true;
	}
	else if(valid_point_but_full(table,size,y,x+1) && table[y][x+1]=='x'){
		neighbor_of_x=true;
	}
	else{
		
		neighbor_of_x=false;
	}
	if(neighbor_of_x){
			
		if(valid_point_but_full(table,size,y-1,x) && table[y-1][x]=='o'){
			neighbor_of_o=true;
		
		}
		else if(valid_point_but_full(table,size,y-1,x+1) && table[y-1][x+1]=='o'){
			neighbor_of_o=true;
		}	
		else if(valid_point_but_full(table,size,y,x-1) && table[y][x-1]=='o'){
			neighbor_of_o=true;
		}
		else if(valid_point_but_full(table,size,y+1,x-1) && table[y+1][x-1]=='o'){
			neighbor_of_o=true;
		}
		else if(valid_point_but_full(table,size,y+1,x) && table[y+1][x]=='o'){
			neighbor_of_o=true;
		}
		else if(valid_point_but_full(table,size,y,x+1) && table[y][x+1]=='o'){
			neighbor_of_o=true;
		}
		else{
			neighbor_of_o=false;
		}
	}
	
	return (neighbor_of_x && neighbor_of_o);
}
int number_of_neighbors_same_type(char table[][12],int size,char player,int y,int x){
	int number_of_neighbors=0;
	if(valid_point_but_full(table,size,y,x-1) && table[y][x-1]==player){
		number_of_neighbors++;
	} 
	if(valid_point_but_full(table,size,y,x+1) && table[y][x+1]==player)
		number_of_neighbors++;

	if(valid_point_but_full(table,size,y-1,x+1) && table[y-1][x+1]==player)
		number_of_neighbors++;
	if(valid_point_but_full(table,size,y+1,x-1) && table[y+1][x-1]==player)
		number_of_neighbors++;
	if(valid_point_but_full(table,size,y-1,x) && table[y-1][x]==player)
		number_of_neighbors++;
	if(valid_point_but_full(table,size,y+1,x) && table[y+1][x]==player)
		number_of_neighbors++;
	return number_of_neighbors;
}
bool is_there_chance_to_put_next_to_last_move(char table[][12],int size,char player,int last_y,int last_x,int value_table_of_AI[][12]){
	int x=-1,y=-1;
	int arrx[6]={-1,-1,-1,-1,-1,-1};
	int arry[6]={-1,-1,-1,-1,-1,-1};
//,y1=0,x1=0, y2=0,x2=0, y3=0,x3=0, y4=0,x4=0, y5=0,x5=0, y6=0,x6=0;
	int temp[6]={-1,-1,-1,-1,-1,-1};
	int number_of_connections_with_same_type=0;
	int max=0;
	// priority : the position which has most number of neighbor which is same type for o->o etc.
	if(valid_point(table,size,last_y,last_x-1)){
		//table[last_y][last_x-1]=player;
		arry[0]=last_y;
		arrx[0]=last_x-1;
		temp[0]=number_of_neighbors_same_type(table,size,player,arry[0],arrx[0]);
			
	}
	if(valid_point(table,size,last_y,last_x+1)){
		//table[last_y][last_x+1]=player;
		arry[1]=last_y;
		arrx[1]=last_x+1;
		temp[1]=number_of_neighbors_same_type(table,size,player,arry[1],arrx[1]);
	}
		
	if(valid_point(table,size,last_y-1,last_x+1)){
		//table[last_y-1][last_x+1]=player;
		arry[2]=last_y-1;
		arrx[2]=last_x+1;	
		temp[2]=number_of_neighbors_same_type(table,size,player,arry[2],arrx[2]);
	}
	
	if(valid_point(table,size,last_y+1,last_x-1)){	
		//table[last_y+1][last_x-1]=player;
		arry[3]=last_y+1;
		arrx[3]=last_x-1;	
		temp[3]=number_of_neighbors_same_type(table,size,player,arry[3],arrx[3]);
	}
	
	if(valid_point(table,size,last_y-1,last_x)){
		//table[last_y-1][last_x]=player;
		arry[4]=last_y-1;
		arrx[4]=last_x;
		temp[4]=number_of_neighbors_same_type(table,size,player,arry[4],arrx[4]);	
	}

	if(valid_point(table,size,last_y+1,last_x)){
		//table[last_y+1][last_x]=player;
		arry[5]=last_y+1;
		arrx[5]=last_x;	
		temp[5]=number_of_neighbors_same_type(table,size,player,arry[5],arrx[5]);	
	}
	max=0;
	for(int i=0;i<6;i++){
		/*if(max<temp[i]){
			max=temp[i];
			x=arrx[i];
			y=arry[i];
		}
		*/
		if(max<temp[i] && temp[i]<2){
			max=temp[i];	
			x=arrx[i];
			y=arry[i];
			break;
		}
	}
	if(x==-1 || y==-1 || max==0 || max>2)
		return false;// no place to put player next to last move
	
	collect_information_for_AI(table,size,y,x,value_table_of_AI,5);
	
	table[y][x]=player;
	cout<<"Computer played to:"<<static_cast<char>('A'+x)<<" "<<y+1<<endl;
	return true; // if one of the condition holds return true player1's turn

}
