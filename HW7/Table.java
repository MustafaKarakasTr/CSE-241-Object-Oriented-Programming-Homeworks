
package HexGame;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Random; // for computer moves
import java.io.FileWriter;   // Import the FileWriter class
import java.io.IOException;
import java.io.File;
import java.io.FileNotFoundException;  // Import this class to handle errors
import java.util.Scanner;

public class Table implements ActionListener,Cloneable{
	JFrame frame;
	JButton[][] buttons;
	JLabel label;
	JButton undoButton=new JButton("Undo");
	JButton saveButton = new JButton("Save");
	JButton loadButton = new JButton("Load");
	JButton resetButton = new JButton("Reset");
	public Object clone()throws CloneNotSupportedException{
		Table temp = (Table)super.clone();
		temp.hexCells = new Cell[size][size];
		temp.buttons = new JButton[size][size];
    	int k=0;
    	for(int i=0;i<size;i++){
    		for(int j = 0;j<size;j++){
    			temp.movements[k] = (Cell)movements[k].clone();
    			k++; 
    			temp.hexCells[i][j] = (Cell)hexCells[i][j].clone();
    			temp.buttons[i][j] = new JButton(".");
    			temp.buttons[i][j].setText(buttons[i][j].getText());
    			temp.buttons[i][j].setBackground(buttons[i][j].getBackground());
    		}
    	}
    	temp.check_table = new boolean[size][size];
    	temp.frame.dispose();
    	temp.frame = new JFrame("HexGame");
		temp.frame.setSize(new Dimension((size*50) + (size*25)+ 500,size*50+300));
		temp.frame.add(undoButton);
		temp.frame.add(saveButton);
		temp.frame.add(loadButton);
		temp.frame.add(resetButton);

		return temp;

	}

	int size;
	boolean against_cpu;
	private boolean game_end = false;
	public int _row,_column;
	
	public Cell [][] hexCells;
    public boolean [][] check_table; 
    public Cell [] movements;
    public int [][] value_table_of_AI;

    private int counter=0;
    private int getCounter(){return counter;}
    private void increaseCounter(){counter++;}
    private void setCounter(int _counter){counter = _counter;}
	private char X = 'x';
    private char Empty = '.';
    private char O = 'o';
    private int[] last_move = new int[2];
    char currentPlayer;        
    char getCurrentPlayer(){
    	return (getCounter() % 2 == 0) ? X: O;
    }
    void setCurrentPlayer(char player){ currentPlayer = player;}

	public Table(int _size,boolean _against_cpu){
		size = _size;
		against_cpu = _against_cpu;
		//value_table_of_AI = new int[size][size];
		buttons = new JButton[_size][_size];
		for(int i=0;i<_size;i++){
			for(int j=0;j<_size;j++){
				buttons[i][j] =new JButton(".");
			}
		}
		int x=150;
		int tempX=x;
		int y=50;
		for(int i=0;i<_size;i++){
			for(int j=0;j<_size;j++){
				buttons[i][j].setBounds(x,y,50,50);
				buttons[i][j].addActionListener(this);
				buttons[i][j].setFocusable(false);
				buttons[i][j].setFont(new Font("Comic Sans",Font.BOLD,20));
				x+=50;
			}
			y+=50;
			x=tempX+25;
			tempX=x;
		}
	
		frame = new JFrame("HexGame");
		frame.setSize(new Dimension((_size*50) + (_size*25)+ 500,_size*50+300));
		//undoButton.setBounds((_size*50) + (_size*25)+ 500,100,50,50);
		
		undoButton.setBounds(0,0,100,50);
		undoButton.addActionListener(this);
		undoButton.setFocusable(false);
		undoButton.setText("Undo");
		frame.add(undoButton);

		saveButton.setBounds(0,50,100,50);
		saveButton.addActionListener(this);
		saveButton.setFocusable(false);
		saveButton.setText("Save");
		frame.add(saveButton);

		loadButton.setBounds(0,100,100,50);
		loadButton.addActionListener(this);
		loadButton.setFocusable(false);
		loadButton.setText("Load");
		frame.add(loadButton);

		resetButton.setBounds(0,150,100,50);
		resetButton.addActionListener(this);
		resetButton.setFocusable(false);
		resetButton.setText("Reset");
		frame.add(resetButton);

		frame.setLayout(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		for(int i=0;i<_size;i++){
			for(int j=0;j<_size;j++){
				frame.add(buttons[i][j]);
			}
		}
		//frame.add(button[1]);

		frame.setVisible(true);
	}
	public void actionPerformed(ActionEvent e){
		if(!game_end){
			if(e.getSource() == undoButton){
				undo();
				return;
			}
			if(e.getSource()== saveButton){
				String file_name=getFileName();
				saveGame(file_name);
				return;
			}
			if(e.getSource() == loadButton){
				String file_name = getFileName();
				loadGame(file_name);
				return;
			}
			if(e.getSource() == resetButton){
				reset();
				return;
			}
			
			for(int i=0;i<size;i++){
				for(int j=0;j<size;j++){

					if(e.getSource()==buttons[i][j] && hexCells[i][j].getVariable() == '.')
					{
						
						_row = i;
						_column = j;
						String player = Character.toString(getCurrentPlayer());
						buttons[i][j].setText(player);
						if(getCurrentPlayer() == X){
							buttons[i][j].setBackground(new Color(0,10,250));
						}
						else if(getCurrentPlayer() == O){
							buttons[i][j].setBackground(new Color(250,10,0));
						}
						buttons[i][j].setFont(new Font("Comic Sans",Font.BOLD,20));					
						hexCells[i][j].setVariable(getCurrentPlayer());
						char winner =check();
						if(winner == X){
							game_end=true;
							showWinner(winner);
							return;
						}
						else if(winner == O){
							game_end=true;
							showWinner(winner);
							return;
						}
						/*if(against_cpu)		
							collect_information_for_AI(i,j,5);
						*/
						movements[counter] = hexCells[i][j];
						increaseCounter();
						
						
						if(against_cpu){
							/*System.out.println("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa\n");
							//cout<<"Computer's turn:\n";
							Cell temp=play();
							movements[getCounter()]=temp; // there is no pointer in Cell so default assignment is enough
							char winner2 = check();
							//winner =play().getVariable();

							//cout<<(*this);
							//showBoard();
							//if(winner == getCurrentPlayer() || (winner +('a'-'A') == getCurrentPlayer()))
							//----------
							String player2 = Character.toString(getCurrentPlayer());
							buttons[temp.getRow()][temp.getPosition()].setText(player2);
							
							buttons[temp.getRow()][temp.getPosition()].setBackground(new Color(250,10,0));
							buttons[temp.getRow()][temp.getPosition()].setFont(new Font("Comic Sans",Font.BOLD,20));
							collect_information_for_AI(temp.getRow(),temp.getPosition(),5);
							System.out.println("AAAAAAAAA "+temp.getRow()+" "+temp.getPosition());				
							hexCells[temp.getRow()][temp.getPosition()].setVariable(getCurrentPlayer());
							//-------
							if(winner2 != '\0'){
								System.out.println("COMPUTER WON\n");
							}
							if(temp.getVariable() == 'O')
							{
								last_move[0] = temp.getRow();
								last_move[1] =temp.getPosition();
								//showScore(_check);
								//cout<<"Winner:O"<<endl;
								System.out.println("Winner O");
								increaseCounter();
								game_end = true;
								
								//numbers_of_nonEmpty_cells += (to_string(getCounter())+" ");
								//delete[] _check;
								
								return;
							}
							last_move[0] = temp.getRow();
							last_move[1] =temp.getPosition();
							
							*/
							boolean flag_ = true;
							Random rand = new Random(); 
							int r1=0,r2=0;
							while(flag_){
			        			 r1 = rand.nextInt(size);
			        			 r2= rand.nextInt(size);
			        			if(hexCells[r1][r2].getVariable() == Empty){
			        				//hexCells[r1][r1].setVariable(getCurrentPlayer());
			        				flag_=false;
			        			}
			        		}
			        		i=r1;
			        		j=r2;
							String player2 = Character.toString(getCurrentPlayer());
							buttons[i][j].setText(player2);
							buttons[i][j].setBackground(new Color(250,10,0));
							buttons[i][j].setFont(new Font("Comic Sans",Font.BOLD,20));					
							hexCells[i][j].setVariable(getCurrentPlayer());
							movements[counter] = hexCells[i][j];
							char winner2 =check();

							if(winner2 == O){
								System.out.println("Winner : O");
								game_end=true;
								JFrame frame = new JFrame("Nice Try");
								frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
								frame.setSize(150,150);
								JLabel label = new JLabel("Winner : Computer");
								frame.add(label);
								frame.setVisible(true);
								//showWinner(winner);
								return;
							}

							//showScore(_check);
							increaseCounter();

							
						

						}

					}



				}

			}
			
			
		}
		
	}
	private void showWinner(char winner){
		if(winner == '\0'){
			return;
		}
		if(!against_cpu || winner == X){
			JFrame frame = new JFrame("Congratulations!");
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.setSize(300,150);
			JLabel label = new JLabel("Winner :" + winner);
			frame.add(label);
			frame.setVisible(true);

		}
		else{
			JFrame frame = new JFrame("Nice Try");
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.setSize(150,150);
			JLabel label = new JLabel("Winner : Computer");
			frame.add(label);
			frame.setVisible(true);
		}
	}
	private char check(){
		boolean reach_to_end=false;
		//int Size = size;
		char player =getCurrentPlayer();
		if(player== X){
		// If it goes A to end then playerX wins, x value should be A to end that means we should go table[y][0] to table[y][size-1] consistently
			for(int i=0;i<size;i++){
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
			for(int i=0;i<size;i++){
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
	private boolean check_neighbors(int y,int x){
		int Size=getSize();
		char player =getCurrentPlayer();
		if(y<0 || x< 0 || x>=Size || y>=Size || hexCells[y][x].getVariable()!=player || check_table[y][x]==true)
			return false;
		if((player==X && x==Size-1) || (player==O && y==Size-1) ) //we reach to destination		
			return true;
		

		check_table[y][x]=true; /* to protect infinite loop we put 'true' to our initial position so that these recursive calls cannot call it again because of the first if statement:*/
		boolean b1=check_neighbors(y-1,x);
		boolean b2=check_neighbors(y-1,x+1);
		boolean b3=check_neighbors(y,x-1);
		boolean b4=check_neighbors(y+1,x-1);
		boolean b5=check_neighbors(y+1,x);
		boolean b6=check_neighbors(y,x+1);
		check_table[y][x]=false; // clearing table
		boolean won=b1||b2||b3||b4||b5||b6;//if one of them is true,then won is true
		return (won); //if one of them true return true else return false
	}
	private void makeUpperCase(int y,int x){
		int Size =getSize();
		char player = getCurrentPlayer();
		if(y<0 || x< 0 || x>=Size || y>=Size || hexCells[y][x].getVariable()!=player) // hexCells[y][x]!=player checks if its . or other player or this position already was made uppercase
			return ;
		hexCells[y][x].makeUpperCase();
		if(getCurrentPlayer() == X)
			buttons[y][x].setBackground(new Color(0,100,255));
		if(getCurrentPlayer() == O)
			buttons[y][x].setBackground(new Color(255,100,0));
		makeUpperCase(y-1,x);
		makeUpperCase(y-1,x+1);
		makeUpperCase(y,x-1);
		makeUpperCase(y+1,x-1);
		makeUpperCase(y+1,x);
		makeUpperCase(y,x+1);
	}
	private int getSize(){
    	return size;
    }
    private Cell play(){
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
								
				char winner=check();
				if(winner==player){
					System.out.println("Computer Played To : "+ (char)('A'+j) + (i+1));
					//cout<<"Computer played to: "<<static_cast<char>('A'+j)<<" "<<i+1<<endl;
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
	int [] arr = {y,x};
	boolean is_there_move=is_there_chance_to_put_next_to_last_move(arr);// returns true if it can change the table else false
	y=arr[0];
	x=arr[1];
	if(is_there_move)
		return hexCells[y][x];// no need to check if the game ends because we now that there is no chance to win with 1 move 
	
	// if you are here table stays same still and there is no place to put something next to last move and there is no chance to finish the game
	// tempy and tempx hold the y and x value of indexes which hold the maximum value which collected collect_information_for_AI function
	hexCells[tempy][tempx].setVariable(getCurrentPlayer());
	//cout<<"Computer played to:"<<static_cast<char>('A'+tempx)<<" "<<tempy+1<<endl;
	System.out.println("Computer Played To : "+ (char)('A'+tempx) + (tempy+1));
	
	collect_information_for_AI(tempy,tempx,5);
	return hexCells[tempy][tempx];
    }
    private int getLastMove(int _index){
    	if(_index>1 || _index<0){
    		System.out.println("Invalid index");
    		//cerr<<"Invalid index\n";
    		return -1;
    	}
    	return last_move[_index];
    }
    private boolean is_there_chance_to_put_next_to_last_move(int[] arr){ // [0] = y [1] = x
		int x=-1;
		int y=-1;
		int []arrx={-1,-1,-1,-1,-1,-1};
		int []arry={-1,-1,-1,-1,-1,-1};
	//,y1=0,x1=0, y2=0,x2=0, y3=0,x3=0, y4=0,x4=0, y5=0,x5=0, y6=0,x6=0;
		int []temp={-1,-1,-1,-1,-1,-1};
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
		//cout<<"Computer played to:"<<static_cast<char>('A'+x)<<" "<<y+1<<endl;
		System.out.println("Computer Played To : "+ (char)('A'+x) + (y+1));
		arr[0] = y;
		arr[1] = x;
		return true; // if one of the condition holds return true player1's turn
	}
	private void fill_temp(int []temp,int []arry,int []arrx,int y,int x){
		int [][]indexHelper={{-1,0},{-1,+1},{0,-1},{1,-1},{1,0},{0,1}};
		for(int i=0;i<6;i++){
			if(valid_point(y+indexHelper[i][0],x+indexHelper[i][1])){
				arry[i]=y+indexHelper[i][0];
				arrx[i]=x+indexHelper[i][1];
				temp[i]=number_of_neighbors_same_type(arry[i],arrx[i]);
			}
		}
	}
	private boolean  valid_point(int y,int x){		
		return (y>=0 && x>=0 && y<getSize() && x<getSize() && hexCells[y][x].getVariable()==Empty);
	}
	private void collect_information_for_AI(int y,int x,int add_value){
	int[][] indexHelper={{-1,0},{-1,+1},{0,-1},{1,-1},{1,0},{0,1}};
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
private int  number_of_neighbors_same_type(int y,int x){
	int number_of_neighbors=0;
	char player = getCurrentPlayer();
	int[][] indexHelper={{-1,0},{-1,+1},{0,-1},{1,-1},{1,0},{0,1}};
	for(int i=0;i<6;i++){
		if(valid_point_but_full(y+indexHelper[i][0],x+indexHelper[i][1]) && hexCells[y+indexHelper[i][0]][x+indexHelper[i][1]].getVariable()==player)
			number_of_neighbors++;
	}
	return number_of_neighbors;
}
boolean valid_point_but_full(int y,int x){
	return(y>=0 && x>=0 && y<getSize() && x<getSize());
}
boolean neighbor_both_x_and_o(int y,int x){
	boolean neighbor_of_x=false;
	boolean neighbor_of_o=false;
	int [][]indexHelper={{-1,0},{-1,+1},{0,-1},{1,-1},{1,0},{0,1}};
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
private void undo()
{  
	if(counter == 0)
		return;
	movements[counter-1].setVariable(Empty);
	if(counter>1)
		movements[counter-2].setVariable(Empty);
	
	hexCells[movements[counter-1].getRow()][movements[counter-1].getPosition()].setVariable(Empty);
	buttons[movements[counter-1].getRow()][movements[counter-1].getPosition()].setText(".");
	buttons[movements[counter-1].getRow()][movements[counter-1].getPosition()].setBackground(new JButton().getBackground());//default color
	//buttons[movements[counter-1].getRow()][movements[counter-1].getPosition()].setFont(new Font("Comic Sans",Font.BOLD,20));					

//btn.setBackground(new JButton().getBackground());

	
	/*if(against_cpu)
		collect_information_for_AI(movements[counter-1].getRow(),movements[counter-1].getPosition(),-5);// -5 because we have added +5 previously when there is a player in there
	*/
	if(counter>1){
		hexCells[movements[counter-2].getRow()][movements[counter-2].getPosition()].setVariable(Empty);
		buttons[movements[counter-2].getRow()][movements[counter-2].getPosition()].setText(".");
		buttons[movements[counter-2].getRow()][movements[counter-2].getPosition()].setBackground(new JButton().getBackground());
		//buttons[movements[counter-2].getRow()][movements[counter-2].getPosition()].setFont(new Font("Comic Sans",Font.BOLD,20));

		/*if(against_cpu)
			collect_information_for_AI(movements[counter-2].getRow(),movements[counter-2].getPosition(),-5);// -5 because we have added +5 previously when there is a player in there
		*/
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
	private void saveGame(String fileName){
		try{
			//ofstream fp;
			FileWriter myWriter = new FileWriter(fileName);
			int against_cpu_int=(against_cpu)?1:0;
			myWriter.write(against_cpu_int+" "+getSize()+ " " + getCurrentPlayer()+" " + getCounter()+"\n");
			//fp.open(get_file_name());
			//fp<<is_against_cpu()<<" "<<getSize()<<" "<<getCurrentPlayer()<<" "<<getCounter()<<" "<<score1<<" "<<score2<<endl;
			//fp<<(*this);
			for(int i=0;i<getSize();i++){
				for(int j=0;j<getSize();j++){
					myWriter.write(hexCells[i][j].getVariable()+" ");
				}
				myWriter.write("\n");
			}
			//fp<<"-1\n";// to indicate that these are movements
			myWriter.write("-1\n");
			for(int i=0;i<counter;i++){
				//fp<<movements[i].getPosition()<<" "<<movements[i].getRow()<<movements[i].getVariable()<<endl;
				myWriter.write(movements[i].getPosition()+" "+movements[i].getRow()+" "+movements[i].getVariable()+"\n");
			}
			myWriter.write("-1\n");
			myWriter.close();
			//fp<<"-1"<<endl;// ends of movements
			/*if(is_against_cpu()){ // the value table which holds information for AI to make it make moves little more smarter to make
				for(int i=0;i<getSize();i++){
					for(int j=0;j<getSize();j++){
						fp<<value_table_of_AI[i][j]<<" ";
					}
					fp<<"\n";
				}
			}*/
			//fp.close();
			//cout<<"Game Saved\n";
			//cout<<(*this);
			//showBoard();	
		}
		catch (IOException e) {
      		e.printStackTrace();
    }
	}
	private String getFileName(){
		String fileStr=JOptionPane.showInputDialog("Enter the file name");
        return fileStr;
	}
	private void loadGame(String fileName){
		try{
			File reader = new File(fileName);
			Scanner	input = new Scanner(reader);
			String cpu =input.next();
			if(cpu.charAt(0) == '1'){
				against_cpu = true;
			}
			else{
				against_cpu = false;
			}
			String _Size=input.next();
			size = Integer.parseInt(_Size);
			
			String curPlay=input.next();
			currentPlayer = curPlay.charAt(0);
			String coun=input.next();

			counter = Integer.parseInt(coun);
			
			hexCells = null;
			check_table = null;
			movements = null;
			value_table_of_AI = null;

			buttons = null;

			hexCells = new Cell[getSize()][getSize()];
		
			check_table = new boolean[getSize()][getSize()];
			movements = new Cell[getSize()*getSize()];

			//buttons =new JButton[getSize()][getSize()];
			//-------------
			/*hexCells = new Cell[getSize()][getSize()];
		
			check_table = new boolean[getSize()][getSize()];
			movements = new Cell[getSize()*getSize()];
			*/
			/*if(is_against_cpu()){
				value_table_of_AI = new int[getSize()][getSize()];
			}*/
			char pos = 'A';
			int row = 1;
			char[] alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray();
			for(int i=0;i<getSize();i++){
				//movements[i] = new Cell();
				for(int j=0;j<getSize();j++){
					hexCells[i][j] = new Cell();
					hexCells[i][j].setCoordinate((char)('A'+j),i+1);

					//hexCells[i][j].setCoordinate(alphabet[j],row);
				
				

			}
			//pos='A';
			//row++;
		}
			for(int i=0;i<getSize()*getSize();i++){
				movements[i]=new Cell();
			}
			

			//----
			for(int i=0;i<size;i++){
				for(int j=0;j<size;j++){
					String var = input.next();
					char Variable = var.charAt(0);
					hexCells[i][j].setVariable(Variable);
				}
			}
			//##############
			//frame.setVisible(false); // maybe cause error 

			buttons = new JButton[size][size];
			for(int i=0;i<size;i++){
				for(int j=0;j<size;j++){
					char c = hexCells[i][j].getVariable();
					String s = String.valueOf(c);
					buttons[i][j] =new JButton(s);
					buttons[i][j].setText(s);
					frame.add(buttons[i][j]);
					if(s.equals("x")){
							buttons[i][j].setBackground(new Color(0,10,250));
						}
					else if(s.equals("o")){
							buttons[i][j].setBackground(new Color(250,10,0));
						}
				}
				}
			
			int x=150;
			int tempX=x;
			int y=50;
			for(int i=0;i<size;i++){
				for(int j=0;j<size;j++){
					buttons[i][j].setBounds(x,y,50,50);
					buttons[i][j].addActionListener(this);
					buttons[i][j].setFocusable(false);
					buttons[i][j].setFont(new Font("Comic Sans",Font.BOLD,20));
					x+=50;
				}
				y+=50;
				x=tempX+25;
				tempX=x;
			}
			/*for(int i=0;i<size;i++){
				for(int j=0;j<size;j++){
					frame.add(buttons[i][j]);
				}
			}*/
			//frame.setVisible(true);
			//##############
			input.next();
			for(int i=0;i<counter;i++){
				String a = input.next();
				String b = input.next();
				String c = input.next();
				int pos_,row_;
				char _var;
				pos_ = Integer.parseInt(a);
				row_ = Integer.parseInt(b);
				_var = c.charAt(0);
				movements[i].setCoordinate((char)(pos_+'A'),row_+1);
				movements[i].setVariable(_var);


			}
			input.next();
			input.close();
			//frame.dispatchEvent(new WindowEvent(frame, WindowEvent.WINDOW_CLOSING));
			frame.dispose();
			//frame = null;
			frame = new JFrame("HexGame");
			frame.setSize(new Dimension((size*50) + (size*25)+ 500,size*50+300));
			//undoButton.setBounds((_size*50) + (_size*25)+ 500,100,50,50);
			
			/*undoButton.setBounds(0,0,100,50);
			undoButton.addActionListener(this);
			undoButton.setFocusable(false);
			undoButton.setText("Undo");*/
			frame.add(undoButton);

			/*saveButton.setBounds(0,50,100,50);
			saveButton.addActionListener(this);
			saveButton.setFocusable(false);
			saveButton.setText("Save");*/
			frame.add(saveButton);

			/*loadButton.setBounds(0,200,100,50);
			loadButton.addActionListener(this);
			loadButton.setFocusable(false);
			loadButton.setText("Load");*/
			frame.add(loadButton);
			frame.add(resetButton);
			frame.setLayout(null);
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			for(int i=0;i<size;i++){
				for(int j=0;j<size;j++){
					frame.add(buttons[i][j]);
				}
			}
		//frame.add(button[1]);

		frame.setVisible(true);
			/* 
			for(int i=0;i<counter;i++){
		fp>>pos;
		fp>>row;
		fp>>_var;
		movements[i].setCoordinate(pos+'A',row+1);
		movements[i].setVariable(_var);
	}
			*/
			
			//while(input.hasNextLine()){
			/*int against_cpu_int  = reader.nextInt();
			(against_cpu_int == 1) ? against_cpu = true:against_cpu = false;
			size = reader.nextInt();
			currentPlayer = reader.nextChar();
			counter = reader.nextInt();
			hexCells = null;
			check_table = null;
			movements = null;
			value_table_of_AI = null;
			createBoard();
			for(int i=0;i<size;i++){
				for(int j = 0;j<size;j++){
					hexCells[i][j] = reader.nextChar();
					System.out.print(hexCells[i][j]);
				}
				Systeme.out.println();
			}
			Systeme.out.println();
			reader.nextInt();
			for(int i=0;i<counter;i++){
				movements[i].setCoordinate((char)('A'+reader.nextInt()),reader.nextInt()+1);
				movements[i].setVariable(reader.nextChar());
			}
			reader.nextInt();
				//myWriter.write(movements[i].getPosition()+" "+movements[i].getRow()+" "+movements[i].getVariable()+"\n");
			

			*/
			
		}
		catch(FileNotFoundException e){
			System.out.println("File is not found");
			e.printStackTrace();
		}
		//int against_cpu_int = Integer.parseInt(data); 
		//}
	}
	/*private void createBoard(){
		hexCells = new Cell[getSize()][getSize()];
		
		check_table = new boolean[getSize()][getSize()];
		movements = new Cell[getSize()*getSize()];*/
		/*if(is_against_cpu()){
			value_table_of_AI = new int[getSize()][getSize()];
		}*/
		/*char pos = 'A';
		int row = 1;
		char[] alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray();
		for(int i=0;i<getSize();i++){
			movements[i] = new Cell();
			for(int j=0;j<getSize();j++){
				hexCells[i][j] = new Cell();
				hexCells[i][j].setCoordinate((char)('A'+j),i+1);
				//hexCells[i][j].setCoordinate(alphabet[j],row);
				
				

			}
			//pos='A';
			//row++;
		}
	}*/
	private void reset(){
		for(int i=0;i<size;i++){
			for(int j = 0;j<size;j++){
				hexCells[i][j].setVariable(Empty);
				buttons[i][j].setText(".");
				buttons[i][j].setBackground(new JButton().getBackground());

			}

		}
		counter = 0;

	}
}
