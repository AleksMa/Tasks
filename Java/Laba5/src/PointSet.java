import java.util.*;
import java.util.stream.Stream;

public class PointSet {

    LinkedHashSet <Point> points;

    public PointSet(LinkedHashSet <Point> points){
        this.points = points;
    }

    public Stream <Circle> makeStream(int k){
        return points.stream()
                .map(p -> new Circle(p, (Double) points.stream()
                        .filter(t -> !t.equals(p))
                        .map(t -> Math.sqrt((p.getX() - t.getX())*(p.getX() - t.getX()) + (p.getY() - t.getY())*(p.getY() - t.getY())))
                        .sorted()
                        .toArray()[k-1]));
    }


    public Optional <Double> makeRectSquare(){
        Object [] xs = points.stream().map(p -> (Double) p.getX()).sorted().toArray(),
                ys = points.stream().map(p -> p.getY()).sorted().toArray();

        Double res = ((Double) xs[xs.length-1] - (Double) xs[0]) *
                ((Double) ys[ys.length-1] - (Double) ys[0]);

        return (res > 0 ? Optional.of(res) : Optional.empty());
    }




}

class Point{
    private double x, y;
    public Point(double x, double y){
        this.x = x;
        this.y = y;
    }

    public double getX(){
        return this.x;
    }

    public double getY(){
        return this.y;
    }

    public static double RectSquare(Point lt, Point rb){
        return (lt.y - rb.y) * (rb.x - lt.x);
    }
}

class Circle {
    private Point c;
    private double r;

    public Circle(Point c, double r) {
        this.c = c;
        this.r = r;
    }

    public Point getPoint(){
        return this.c;
    }

    public double getR(){
        return this.r;
    }

}

