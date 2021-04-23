import mustafa.karakas.hw6.Iterator;
import mustafa.karakas.hw6.NoMoreElementException;
import java.util.Scanner;
public class main {
    public static void main(String [] args){
        System.out.println("To test  HashSet Enter 1");
        System.out.println("To test  ArrayList Enter 2");
        System.out.println("To test LinkedList Enter 3");
        Scanner input = new Scanner(System.in);
        int choice =input.nextInt();
        if(choice == 1){
            HashSet<Integer> h1 = new HashSet<>();
            //ArrayList<Integer> h1 = new ArrayList<>();
            //LinkedList<Integer> h1 = new LinkedList<>();

            h1.add(11);

            h1.add(220);
            h1.show();


            h1.add(330);

            h1.show();

            h1.add(10);
            h1.add(20);
            h1.add(40);
            h1.remove(20);
            h1.show();
            for(int i=0;i<10;i++){
                h1.add(i*10);
            }
            h1.show();
            h1.remove(11);
            h1.show();
            System.out.println(h1.isEmpty());
            HashSet<Integer> h2 =new HashSet<>();
            //ArrayList<Integer> h2 =new ArrayList<>();
            //LinkedList<Integer> h2 = new LinkedList<>();
            
            h2.addAll(h1);
            h2.show();
            //h1.clear();
            System.out.println("------------------");
            h1.remove(10);
            h1.remove(0);
            h1.remove(90);

            h1.show();
            h2.show();
            System.out.println("------------------");
            
            System.out.println(h2.isEmpty());
            h2.removeAll(h1);
            h2.show();
            System.out.println("------------------");
            
            h2.addAll(h1);
            h1.show();
            h2.show();
            System.out.println("------------------");
            h2.remove(10);
            h2.remove(220);
            h2.remove(80);
            h2.add(1000);
            h1.add(9999);

            System.out.println("------------------");

            h1.show();
            h2.show();
            System.out.println("------------------");

            h2.retainAll(h1);
            h1.show();
            h2.show();
            System.out.println("------------------");
            h1.clear();
            System.out.println("Is h1 empty = "+ h1.isEmpty());                               
            
        }
        else if(choice == 2){
            //HashSet<Integer> h1 = new HashSet<>();
            ArrayList<Integer> h1 = new ArrayList<>();
            //LinkedList<Integer> h1 = new LinkedList<>();

            h1.add(11);

            h1.add(220);
            h1.show();


            h1.add(330);

            
            h1.show();
            for(int i=0;i<5;i++){
                h1.add(i*10);
            }
            h1.show();
            System.out.println("------------------");

            ArrayList<Integer> h2 =new ArrayList<>();
            h2.addAll(h1);
            System.out.println("h1 was copied to h2");

            h1.show();
            h2.show();
            //h1.clear();
            System.out.println("------------------");
            h1.remove(10);
            h1.remove(0);
            h1.remove(90);

            h1.show();
            h2.show();
            System.out.println("------------------");
            
            System.out.println(h2.isEmpty());
            h2.removeAll(h1);
            h2.show();
            System.out.println("------------------");
            
            h2.addAll(h1);
            h1.show();
            h2.show();
            System.out.println("------------------");
            h2.remove(10);
            h2.remove(220);
            h2.remove(80);
            h2.add(1000);
            h1.add(9999);

            System.out.println("------------------");

            h1.show();
            h2.show();
            System.out.println("------------------");

            h2.retainAll(h1);
            h1.show();
            h2.show();
            System.out.println("------------------");
            ArrayList<String> h3 = new ArrayList<>();
            ArrayList<String> h4 = new ArrayList<>();
          

            System.out.println(h4.isEmpty());

            for(int i=0;i<5;i++){
                h3.add("CSE 24"+i);
            }
            try{
                h4.addAll(h3);
                h3.add("Mustafa",5);
                h3.add("Mustafa",0);
                h3.add("Karakas",2);

                
                System.out.println("------------------");

                h3.show();
                h4.show();
                System.out.println("------------------");

                h3.remove("Karakas");
               // h3.removeAll(h4);
                h4.add("1801042627");
                h3.retainAll(h4); 
                System.out.println("------------------");

                h3.show();
                h4.show();
                System.out.println("------------------");

                System.out.println("Does h3 contains h4 : "+h3.containsAll(h4));
                
                

                h4.removeAll(h3);
                System.out.println("------------------");
                h3.show();
                h4.show();
                System.out.println("Is h4 empty ?: "+h4.isEmpty());
            }
            catch(IndexOutOfBoundsException e){
                System.out.println(e);
            }
            
        }
        if(choice == 3){
            //HashSet<Integer> h1 = new HashSet<>();
            //ArrayList<Integer> h1 = new ArrayList<>();
            LinkedList<Integer> h1 = new LinkedList<>();
 	    LinkedList<String> h3 = new LinkedList<>();
	    LinkedList<String> h4 = new LinkedList<>();
            try{
		    h1.add(11);

		    h1.add(220);
		    h1.show();


		    h1.add(330);

		    h1.show();

		    h1.add(10);
		    h1.add(20);
		    h1.add(40);
		    h1.remove(20);
		    h1.show();
		    for(int i=0;i<10;i++){
		        h1.add(i*10);
		    }
		    h1.show();
		    h1.remove(11);
		    h1.show();
		    System.out.println(h1.isEmpty());
		    //HashSet<Integer> h2 =new HashSet<>();
		    //ArrayList<Integer> h2 =new ArrayList<>();
		    LinkedList<Integer> h2 = new LinkedList<>();
		    
		    h2.addAll(h1);
		    h2.show();
		    //h1.clear();
		    System.out.println("------------------");
		    h1.remove(10);
		    h1.remove(0);
		    h1.remove(90);

		    h1.show();
		    h2.show();
		    System.out.println("------------------");
		    
		    System.out.println(h2.isEmpty());
		    h2.removeAll(h1);
		    h2.show();
		    System.out.println("------------------");
		    
		    h2.addAll(h1);
		    h1.show();
		    h2.show();
		    System.out.println("------------------");
		    h2.remove(10);
		    h2.remove(220);
		    h2.remove(80);
		    h2.add(1000);
		    h1.add(9999);

		    System.out.println("------------------");

		    h1.show();
		    h2.show();
		    System.out.println("------------------");

		    h2.retainAll(h1);
		    h1.show();
		    h2.show();
		    System.out.println("------------------");
		    //ArrayList<String> h3 = new ArrayList<>();
		    //ArrayList<String> h4 = new ArrayList<>();
		   

		    System.out.println(h4.isEmpty());

		    for(int i=0;i<5;i++){
		        h3.offer("CSE 24"+i);
		    }
		}
		catch(IllegalStateException e){
			System.out.println(e);
		}
            try{
                h4.addAll(h3);
                h3.add("Mustafa",5);
                h3.add("Mustafa",0);
                h3.add("Karakas",0);

                

                h3.show();
                h4.show();
                h3.remove("Karakas");
            // h3.removeAll(h4);
            h4.add("1801042627");
            h3.retainAll(h4); 
            h3.show();
                h4.show();


                // h4.clear();
            System.out.println("Does h3 contains h4 : "+h3.containsAll(h4));
            System.out.println("head :" +h4.element() );
            /*for(int i=0;i<1;i++)
                    h4.poll();
                */
                h4.show();
                h4.poll();
                h4.poll();
                h4.poll();
            



                h4.show();
		System.out.println("-----------------");
                h4.removeAll(h3);
                h4.show();
                System.out.println("Is h4 empty ?: "+h4.isEmpty());
                //System.out.println(h4.get(4));
            }
            catch(IndexOutOfBoundsException e){
                System.out.println(e);
            }
            catch(NoMoreElementException e){
                System.out.println(e);

            } 
        }
   
    }



    
    public static  <E> void showArr(E[] e){
        for(E a:e){
            System.out.printf("%d ",a);
        }
    }
}
