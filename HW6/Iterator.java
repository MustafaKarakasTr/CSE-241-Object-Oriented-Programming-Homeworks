package mustafa.karakas.hw6;

public class Iterator<E> {
    private E[] arr;
    private int used;
    private int index = 0;
    public Iterator (E[] e,int _used){
        setArr(e);
        setUsed(_used);
    }
    public boolean hasNext(){
        /*if(index == used)
            return false;
        return true;
        */
        return !(index == used);
    }
    public E next()throws NoMoreElementException{
        if(hasNext())
            return arr[index++];
        
        throw new NoMoreElementException();

    }
    public void remove()throws NoMoreElementException{
        if(index>0){
           // System.out.println(arr[0] + " " + used +" "+index);
            for(int i=index-1;i<used-1;i++){
                arr[i] = arr[i+1];
            }
            used--;
            index--;
            /*
            for(int i=0;i<used;i++){
                System.out.print(arr[i]+"-");
            }
            System.out.println("?s");
            */

        }
        else{
            throw new NoMoreElementException();
        }

    }
    private void setArr(E[] arr2){
        arr = arr2;
        index = 0;
        
    }
    private void setUsed(int _used){
        used = _used;
    }
}