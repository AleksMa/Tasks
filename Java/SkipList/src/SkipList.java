import java.util.*;

public class SkipList<K extends Comparable<K>,V> extends AbstractMap<K,V> {
    private int levels;
    private List l;
    private int size;

    public SkipList(int levels) {
        this.levels = levels;
        this.l = new List();
        this.size = 0;
    }

    @Override
    public boolean isEmpty() {
        return l.next(0) == null;
    }

    public int size(){
        return this.size;
    }

    public List succ(List x){
        return x.next(0);
    }

    public List [] skip(List l, K k){
        List x = l;
        List [] p = new List [levels];
        int i = this.levels - 1;
        while(i >= 0){
            while(x.next(i) != null && x.next(i).getKey().compareTo(k) < 0){
                x = x.next(i);
            }
            p[i] = x;
            i--;
        }
        return p;
    }

    @Override
    public boolean containsKey(Object key) {
        K k = (K) key;
        List [] p = this.skip(l, k);
        List x = this.succ(p[0]);
        return x != null && x.getKey().equals(k);
    }

    @Override
    public V get(Object key) {
        K k = (K) key;
        List [] p = this.skip(l, k);
        List x = this.succ(p[0]);
        V ret = null;
        if(x != null && x.getKey().equals(k)){
            ret = (V) x.getValue();
        }
        return ret;
    }

    @Override
    public V put(K k, V v) {
        List [] p = this.skip(l, k);
        List x = new List(k, v), m = this.succ(p[0]);
        V ret = null;
        if(m != null && m.getKey().equals(k)){
            ret = (V) m.getValue();
            size--;
        }
        final Random random = new Random();
        int r = random.nextInt() * 2, i = 0;
        while(i < levels && r % 2 == 0){
            x.setNext(i, p[i].next(i));
            p[i].setNext(i, x);
            i++;
            r /= 2;
        }
        while(i < levels){
            x.setNext(i, null);
            i++;
        }
        size++;
        return ret;
    }

    @Override
    public V remove(Object key) {
        K k = (K) key;
        List [] p = this.skip(l, k);
        List x = this.succ(p[0]);
        V ret = null;
        if(x != null && x.getKey().equals(k)){
            ret = (V) x.getValue();
            int i = 0;
            while( i < levels && p[i].next(i) == x){
                p[i].setNext(i, x.next(i));
                i++;
            }
            size--;
        }
        return ret;
    }

    @Override
    public void clear() {
        size = 0;
        l = new List();
    }

    @Override
    public Set<Entry<K, V>> entrySet() {
        return new ListSet();
    }

    class List < K extends Comparable<K>,V > implements Map.Entry<K,V>{
        private K k;
        private V v;
        private List [] next;

        public List(){
            next = new List[SkipList.this.levels];
        }

        public List(K k, V v){
            this.k = k;
            this.v = v;
            next = new List[SkipList.this.levels];
        }

        public List next(int i){
            return next[i];
        }

        public void setNext(int i, List l){
            next[i] = l;
        }

        @Override
        public V getValue() {
            return v;
        }

        @Override
        public K getKey() {
            return k;
        }

        @Override
        public V setValue(V value) {
            v = value;
            return value;
        }
    }

    private class ListSet<K,V> extends AbstractSet {

        private class ListIterator implements Iterator {
            private List x;

            public ListIterator() {
                x = l;
            }

            @Override
            public boolean hasNext() {
                return x.next(0)!= null;
            }

            @Override
            public Map.Entry<K, V> next() {
                x = x.next(0);
                return x;
            }

            public void remove() {
                SkipList.this.remove(x.getKey());
            }

        }

        public Iterator iterator() {
            return new ListIterator();
        }

        @Override
        public int size() {
            return size;
        }

        public ListSet() {
        }
    }
}

