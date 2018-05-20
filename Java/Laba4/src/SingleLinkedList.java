import java.util.*;

public class SingleLinkedList <T> implements Iterable <T> {
    List l;

    public SingleLinkedList(){
        super();
    }

    public boolean isEmpty(){
        return l == null;
    }

    public int length(){
        int len = 0;
        List x = l;
        while(x != null){
            len++;
            x = x.next;
        }
        return len;
    }

    public void insertBeforeHead(T v){
        List y = new List (v);
        y.next = l;
        l = y;
    }

    public void insertAfter(List x, T v){
        List z = x.next, y = new List(v);
        x.next = y;
        y.next = z;
    }

    public List search(T v){
        List x = l;
        while(x != null && x.v != v)
            x = x.next;
        return x;
    }

    public void deleteAfter(List x){
        List y = x.next;
        x.next = y.next;
        y.next = null;
    }

    public void deleteHead(){
        List y = l;
        l = y.next;
        y.next = null;
    }

    public void searchAndDelete(T v){
        List y = null;
        List x = l;
        while(x != null){
            if(x.v == v){
                if(y == null)
                    this.deleteHead();
                else
                    this.deleteAfter(y);
                return;
            }
            y = x;
            x = x.next;
        }
    }


    @Override
    public Iterator<T> iterator() {
        return new ListIterator();
    }

    private class ListIterator implements Iterator <T> {
        private List x;

        public ListIterator(){
            x = l;
        }

        @Override
        public boolean hasNext() {
            return x != null;
        }

        public T next(){
            T val = (T) x.v;
            x = x.next;
            return val;
        }
    }

    private class List <T> {
        private T v;
        private List <T> next;

        public List(){
            super();
        }

        public List(T v){
            this.v = v;
        }

    }
}
