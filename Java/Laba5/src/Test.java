import java.lang.reflect.Array;
import java.util.*;
import java.util.stream.Collectors;


public class Test {
    public static void main(String[] args) {
        LinkedHashSet<Point> p = new LinkedHashSet<>();
        Collections.addAll(p, new Point[]{
                new Point(0,0), new Point(0, 2), new Point(0, 5), new Point(1, 1), new Point(10, 10)
        });
        int K = 2;
        PointSet s = new PointSet(p);

        s.makeStream(2).forEach(c -> System.out.println(c.getR()));


        System.out.println("<10:");
        s.makeStream(K).filter(c -> 2*Math.PI*c.getR() < 10).map(c -> c.getR()).forEach(System.out::println);
        System.out.println("<20:");
        s.makeStream(K).filter(c -> 2*Math.PI*c.getR() >= 10 && 2*Math.PI*c.getR() < 20).map(c -> c.getR()).forEach(System.out::println);
        System.out.println("<30:");
        s.makeStream(K).filter(c -> 2*Math.PI*c.getR() >= 20 && 2*Math.PI*c.getR() < 30).map(c -> c.getR()).forEach(System.out::println);
        System.out.println("<40:");
        s.makeStream(K).filter(c -> 2*Math.PI*c.getR() >= 30 && 2*Math.PI*c.getR() < 40).map(c -> c.getR()).forEach(System.out::println);
        System.out.println("<50:");
        s.makeStream(K).filter(c -> 2*Math.PI*c.getR() >= 40 && 2*Math.PI*c.getR() < 50).map(c -> c.getR()).forEach(System.out::println);
        System.out.println("<60:");
        s.makeStream(K).filter(c -> 2*Math.PI*c.getR() >= 50 && 2*Math.PI*c.getR() < 60).map(c -> c.getR()).forEach(System.out::println);
        System.out.println("<70:");
        s.makeStream(K).filter(c -> 2*Math.PI*c.getR() >= 60 && 2*Math.PI*c.getR() < 70).map(c -> c.getR()).forEach(System.out::println);
        System.out.println("<80:");
        s.makeStream(K).filter(c -> 2*Math.PI*c.getR() >= 70 && 2*Math.PI*c.getR() < 80).map(c -> c.getR()).forEach(System.out::println);
        System.out.println("<90:");
        s.makeStream(K).filter(c -> 2*Math.PI*c.getR() >= 80 && 2*Math.PI*c.getR() < 90).map(c -> c.getR()).forEach(System.out::println);
        System.out.println("<100:");
        s.makeStream(K).filter(c -> 2*Math.PI*c.getR() >= 90 && 2*Math.PI*c.getR() < 100).map(c -> c.getR()).forEach(System.out::println);

        System.out.println();

        s.makeRectSquare().ifPresent(System.out::println);
    }
}
