import java.util.AbstractSet;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class IntSparseSet extends AbstractSet<Integer> {

    private int [] sparse;
    private int [] dense;
    private int n, u, low;

    public IntSparseSet(int low, int high) {
        this.u = high - low;
        this.low = low;
        this.sparse = new int[u];
        this.dense = new int[u];
        this.n = 0;
    }

    @Override
    public Iterator<Integer> iterator() {
        return new Itr();
    }

    @Override
    public int size() {
        return n;
    }

    @Override
    public boolean contains(Object o) {
        Integer X = (Integer) o;
        int x = X.intValue();
        return x >= low && x < u + low && 0 <= sparse[x - low] && sparse[x - low] < n && dense[sparse[x - low]] == x;
    }

    @Override
    public boolean add(Integer X) {
        int x = X.intValue();
        boolean t = x >= low && x < u + low && !contains(x);
        if(t){
            this.dense[n] = x;
            this.sparse[x - low] = n;
            n++;
        }
        return t;
    }

    @Override
    public boolean remove(Object o) {
        Integer X = (Integer) o;
        int x = X.intValue();
        boolean t = x >= low && x < u + low && contains(x);
        if(t){
            int i = sparse[x - low];
            n--;
            dense[i] = dense[n];
            sparse[dense[i] - low] = i;
        }
        return t;
    }

    @Override
    public void clear() {
        n = 0;
    }

    private class Itr implements Iterator<Integer> {
        int cursor;

        @Override
        public boolean hasNext() {
            return cursor < n;
        }

        @Override
        public Integer next() {
            int i = cursor;
            if(i >= n)
                throw new NoSuchElementException();
            cursor = i + 1;
            return dense[i];
        }

        @Override
        public void remove() {
            IntSparseSet.this.remove(dense[--cursor]);
        }
    }
}