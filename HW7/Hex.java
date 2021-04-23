package HexGame;
import javax.swing.JOptionPane;
import javax.swing.*;
import java.awt.event.*;   

public class Hex implements HexGame,Cloneable{
    public  int size;
    private boolean against_cpu;
    private Cell [][] hexCells;
    private boolean [][] check_table; 
    private Cell [] movements;
   // private int [][] value_table_of_AI;
    
    private boolean flag = false;
    private Table table; 
    public Object clone()throws CloneNotSupportedException{
    	Hex temp = (Hex)super.clone();
    	
    	temp.hexCells = new Cell[size][size];
    	int k=0;
    	for(int i=0;i<size;i++){
    		for(int j = 0;j<size;j++){
    			temp.movements[k] = (Cell)movements[k].clone();
    			k++; 
    			temp.hexCells[i][j] = (Cell)hexCells[i][j].clone();
    		}
    		
    	}
    	temp.check_table = new boolean[size][size];
    	temp.table = (Table) table.clone();
    	return temp;

    }
    public Hex(){
        setSize();
        set_against_cpu();
        createBoard();
        //print();
        while(true){
        	if(flag){
        		table =new Table(getSize(),against_cpu);
        		table.hexCells = hexCells;
        		table.check_table = check_table;
        		table.movements = movements;
        		//table.value_table_of_AI = value_table_of_AI;
        		break;
        	}	
        }

       
       

		
        
    }
    private void setSize(){
        String firstNum=JOptionPane.showInputDialog("Enter size of the board");
        int num1 = Integer.parseInt(firstNum);
        //int num2 = Integer.parseInt(secondNum);
        //int add= num1+num2;

        //JOptionPane.showMessageDialog(null,firstNum+" + "+secondNum +" = "+add, "Toplama", JOptionPane.INFORMATION_MESSAGE);
        if(num1>5){
            size = num1;
        }
        else{
            //JOptionPane.showMessageDialog(null,"Cok iyi girdin reis ","ERROR", JOptionPane.INFORMATION_MESSAGE);
            setSize();
        }
    }
    public int getSize(){
    	return size;
    }
    private void set_against_cpu(){
        new TakeGameType();
	}
	private boolean is_against_cpu(){return against_cpu;}
	private class TakeGameType extends JFrame implements ActionListener{
	    JRadioButton rb1,rb2;    
	    JButton b;    
	    TakeGameType(){      
	        rb1=new JRadioButton("Player vs Player");    
	        rb1.setBounds(100,50,150,30);      
	        rb2=new JRadioButton("Player vs Computer");    
	        rb2.setBounds(100,100,200,30);    
	        ButtonGroup bg=new ButtonGroup();    
	        bg.add(rb1);
	        bg.add(rb2);    
	        b=new JButton("Okey");    
	        b.setBounds(100,150,80,30);    
	        b.addActionListener(this);    
	        add(rb1);add(rb2);add(b);    
	        setSize(300,300);    
	        setLayout(null);    
	        setVisible(true);    
	    }    
	    public void actionPerformed(ActionEvent e){    
	        if(rb1.isSelected()){    
	            //JOptionPane.showMessageDialog(this,"You are playing vs Player");    
	            against_cpu = false;
	        }    
	        if(rb2.isSelected()){    
	            //JOptionPane.showMessageDialog(this,"You are playing vs Computer");    
	            against_cpu = true;
	            
	        }    
	        super.dispose(); // closes window
	        flag = true; // program can go to the next step input was taken
	    }
	}

	private void createBoard(){
		/*hexCells = new Cell* [getSize()];
    	check_table = new bool* [getSize()];
    	movements = new Cell[getSize()*getSize()]; // The board can hold size² number of cells 
    	if(is_against_cpu())
    		value_table_of_AI = new int* [getSize()];

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
		*/
		hexCells = new Cell[getSize()][getSize()];
		
		check_table = new boolean[getSize()][getSize()];
		movements = new Cell[getSize()*getSize()];
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
		for(int i=0;i<size*size;i++){
			movements[i] = new Cell();
		}		

	}
	private void print(){
		int Size=getSize();
		    char letters='a';
			System.out.print(" ");
			for(int i=0;i<Size;i++){
				System.out.print(" "+letters++);
			}
			System.out.println();
			for(int i = 0; i < Size; ++i)
				{
					System.out.print((i+1)+" ");
					for(int a=0;a<i;a++){
						if(a==8){ // 2 digits ruin table to be able to prevent it I added this

						}
						else
							System.out.print(" ");
					}
					for(int x=0;x<Size; x++){
						System.out.print(hexCells[i][x].getVariable()+" ");
						//hexCells[i][x].getCoordinate();
						
						//System.out.print()
						//hexCells[i][x].getCoordinate();
					}
					System.out.println();
				}
			System.out.println();
		    //return outputStream;
	}
	


}