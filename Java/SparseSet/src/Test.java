import java.util.*;

public class Test {
    public static void main(String[] args) {
        Vertex<String> a = new Vertex<>("A"), b = new Vertex<>("B"), c = new Vertex<>("C"),
                d = new Vertex<>("D"), e = new Vertex<>("E"), f = new Vertex<>("F"),
                g = new Vertex<>("G"), h = new Vertex<>("H"), i = new Vertex<>("I");

        a.addAll(Arrays.asList(d, c, b));
        b.add(e);
        c.add(f);
        d.add(g);
        e.add(h);
        f.add(h);
        g.addAll(Arrays.asList(d, c, b, i));
        h.add(b);
        i.add(a);

        for (Vertex<String> v : Vertex.preorder(a)) System.out.println(v);
    }
}