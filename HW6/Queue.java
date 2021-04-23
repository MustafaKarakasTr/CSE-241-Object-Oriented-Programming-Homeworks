package mustafa.karakas.hw6;
import mustafa.karakas.hw6.Collection;
import mustafa.karakas.hw6.NoMoreElementException;

public interface Queue<E> extends Collection<E> {
   // void add(E e);
    E element()throws NoMoreElementException;
    boolean offer(E e);
    E poll()throws NoMoreElementException; // throws exception if this queue is empty
}
