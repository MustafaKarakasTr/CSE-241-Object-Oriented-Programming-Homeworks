package HexGame;
public class Cell implements Cloneable{
    private char X = 'x';
    private char Empty = '.';
    private char O = 'o';
	    private char position; // A,B,C etc.
	    private int rowNum; // 1,2,3 etc.
	    private char variable=Empty; // as default all cells are empty
    
        public Cell() {variable = Empty;}
        public Object clone()throws CloneNotSupportedException{
            return super.clone();
        }
        public char getVariable() {return variable;}
        public void setVariable(char player){
            if(player == X || player==O || player == X -'a' + 'A' || player == O -'a' +'A' || player == Empty)
                 variable = player;
            else
                System.out.println("Invalid player");
        }
        public void setCoordinate(char pos,int row){
            position = pos;
            rowNum = row;
        }
        public void getCoordinate(){
            //cout<<position<<rowNum<<" ";
            System.out.print(position);
            System.out.print(" "+rowNum+" ");

        }
        public int getPosition(){return position-'A';}
        public int getRow(){return rowNum-1;};
        public void makeUpperCase(){
            setVariable((char)(getVariable() +'A' -'a'));
        }
}
