import java.util.*;

public class SparseSet <T extends Hintable> extends AbstractSet<T> {

    private ArrayList <T> dense;

    public SparseSet() {
        this.dense = new ArrayList<>(10);
    }

    @Override
    public Iterator<T> iterator() {
        return new Itr();
    }

    @Override
    public int size() {
        return dense.size();
    }

    @Override
    public boolean contains(Object o) {
        T x = (T) o;
        return dense.size() > x.hint() && dense.get(x.hint()) == x;
    }

    @Override
    public boolean add(T x) {
        boolean t = !this.contains(x);
        if(t){
            int i = dense.size();
            x.setHint(i);
            dense.add(x);
        }
        return t;
    }

    @Override
    public boolean remove(Object o) {
        T x = (T) o;
        boolean t = this.contains(x);
        if(t){
            int i = x.hint();
            T y = dense.get(dense.size() - 1);
            dense.set(i, y);
            y.setHint(i);
            dense.remove(dense.size() - 1);
        }
        return t;
    }

    @Override
    public void clear() {
        dense.clear();
    }

    private class Itr implements Iterator<T> {
        int cursor;

        @Override
        public boolean hasNext() {
            return cursor < dense.size();
        }

        @Override
        public T next() {
            int i = cursor;
            if(i >= dense.size())
                throw new NoSuchElementException();
            cursor = i + 1;
            return dense.get(i);
        }

        @Override
        public void remove() {
            SparseSet.this.remove(dense.get(--cursor));
        }
    }
}