import mustafa.karakas.hw6.Iterator;
import mustafa.karakas.hw6.Collection;
import mustafa.karakas.hw6.NoMoreElementException;
import mustafa.karakas.hw6.List;

public class ArrayList<E> implements List<E>{
    private E[] arr = (E[]) new Object[2];
    private int used = 0;
    public E get(int _index)throws IndexOutOfBoundsException{
        if(_index>=used || _index<0){
            throw new IndexOutOfBoundsException();
        }
            return arr[_index];
    
        
    }
    public Iterator<E> iterator(){
        Iterator<E> iter = new Iterator<E>(arr,used);
        return iter;
    }
    public void add(E e){

        if(arr == null)
        {
            arr =(E[]) new Object[2];
            /*for(int i=0;i<2;i++){
                arr[i] = (E)new Object();
            }*/
        }
        else if(arr.length == used){
            E[] temp = (E[]) new Object[used*2]; 
               /* for(int i=0;i<used*2;i++){
                    temp[i] = (E)new Object();
                }*/
            for(int i=0;i<used;i++){
                temp[i] = arr[i];
            }
            arr = temp;
        }
        arr[used] = e;
        used++;
            
    }
    public void add(E e,int _index)throws IndexOutOfBoundsException{
        if(_index>used || _index<0){
            throw new IndexOutOfBoundsException();
        }
        add(e); // it adds to the end
        for(int i=used-1;i>_index;i--){
            arr[i]=arr[i-1];
        }
        arr[_index] = e;
    }

    public void addAll(Collection c){
        Iterator<E> iter = c.iterator();
        try{
            while(iter.hasNext()){
                add(iter.next());
            }
        }
        catch(NoMoreElementException e){
            System.out.print(e);
           
        }
    }
    public void clear(){
        arr = (E[])new Object[2];
        used = 0;

    }
    public boolean contains(E e){
        if(used != 0){
            for(int i=0;i<used;i++){
                if(arr[i].equals(e) ==true ){
                    return true;
                }
            }
        }
        return false;
    }
    public boolean containsAll(Collection c){
        Iterator<E> iter = c.iterator();
        try{
            while(iter.hasNext()){
                if(!contains(iter.next())){
                    return false;
                }
            }
            return true;
        }
        catch(NoMoreElementException e){
            System.out.print(e);
        }
        return true;
    }
    public boolean isEmpty(){
        return used==0;
    }
    public void remove(E e){
        for(int i=0;i<used;i++){
            if(arr[i].equals(e) == true){
                for(int j = i;j<used-1;j++){
                    arr[j] = arr[j+1];
                }
                used--;
                //return; deletes all elements which are equal to e
            }
        }
    }
    
    public void removeAll(Collection c){
        Iterator<E> iter = c.iterator();
        try{
            while(iter.hasNext()){
                E element = iter.next();
                remove(element);
            }
            
        }
        catch(NoMoreElementException e){
            System.out.print(e);
        }
    }
    
    public void retainAll(Collection c){
        boolean flag = false;
        try{
            for(int i=0;i<used;i++){
                for(Iterator<E> iter = c.iterator();iter.hasNext();){
                    E element = iter.next();
                    if(arr[i].equals(element)){
                        flag = true;
                        
                    }
                }
                if(flag == false){
                    remove(arr[i]);
                    i--;
                }
                flag = false;
                
            }
            
        }
        catch(NoMoreElementException e){
            System.out.print(e);
        }
    }
    
    public int size(){
        return used;
    }
    public void show(){
        try{
            for(int i=0;i<used;i++){
                System.out.print(get(i)+" ");
            }
            System.out.println();
        }
        catch(IndexOutOfBoundsException e){
            System.out.println(e);
        }
    }
}