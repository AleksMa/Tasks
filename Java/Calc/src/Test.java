
import java.util.ArrayList;

public class Test
{
    public static void main(String[] args)
    {
        Element<Double> a = new Element<Double>(1.5), b = new Element<Double>(2.3);
        a.union(b);

        Element<Double> c = new Element<Double>(0.1), d = new Element<Double>(5.0);
        c.union(d);

        Element<Double> e = new Element<Double>(3.5), f = new Element<Double>(1.0);
        e.union(f);

        Element<Double> g = new Element<Double>(-2.5), h = new Element<Double>(2.5);
        g.union(h);

        a.union(c);
        e.union(g);
        a.union(g);

        report(b,h);
    }

    private static <T> void report(Element<T> a, Element<T> b)
    {
        System.out.println("" + a.x() + "=" + b.x() + ": " + a.equivalent(b));
    }
}