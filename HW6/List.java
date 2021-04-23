package mustafa.karakas.hw6;
import mustafa.karakas.hw6.Collection;

public interface List<E> extends Collection<E> {
    E get(int index);
    void add(E e,int _index);
}
