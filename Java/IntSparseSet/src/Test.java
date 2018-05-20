import java.util.Iterator;
import java.util.Set;

public class Test {
    public static void main(String[] args) {
        int[] in = new int[] { 60, 10, 50, 40, 30, 100 };
        Set<Integer> a = new IntSparseSet(-100, 101) {{
            for (int x : in) add(x);
        }};

        Iterator<Integer> it = a.iterator();
        while (it.hasNext()) {
            int x = it.next();
            if (x == 10 || x == 30) it.remove();
        }

        int i = 0;
        int[] out = new int[] { 60, 100, 50, 40 };
        for (int x : a) Assert.assertEquals(out[i++], x);

        System.out.println("PASSED");
    }
}