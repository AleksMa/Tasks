import java.util.ArrayList;
import java.util.Stack;

public class Vertex<T> extends ArrayList<Vertex<T>> implements Hintable {
    private T attr;
    private int hint;

    public Vertex(T attr) { this.attr = attr; }

    public T attr() { return attr; }

    @Override
    public void setHint(int hint) { this.hint = hint; }

    @Override
    public int hint() { return hint; }

    @Override
    public String toString() { return attr.toString(); }

    public static <T> Iterable<Vertex<T>> preorder(Vertex<T> v) {
        SparseSet<Vertex<T>> marks = new SparseSet<>();
        Stack<Vertex<T>> stack = new Stack<>();
        stack.push(v);
        while (!stack.empty()) {
            v = stack.pop();
            marks.add(v);
            for (Vertex<T> u : v) {
                if (!marks.contains(u)) stack.push(u);
            }
        }
        return marks;
    }
}