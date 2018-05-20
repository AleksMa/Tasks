import java.util.Iterator;
import java.util.Map;

public class Test {
    public static void main(String[] args) {
        Map<Integer, Integer> a = new SkipList<Integer, Integer>(10) {{
            for (int i = 0; i < 1000; i++) put(i, i);
        }};

        Iterator<Map.Entry<Integer, Integer>> it = a.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry<Integer, Integer> e = it.next();
            if (e.getKey() % 3 == 0) it.remove();
            else e.setValue(e.getValue()*1000);
        }

        Assert.assertEquals(666, a.size());

        for (int i = 0; i < 1000; i++) {
            if (i % 3 != 0) Assert.assertEquals(i*1000, (int)a.get(i));
            else Assert.assertFalse(a.containsKey(i));
        }

        System.out.println("PASSED");
    }
}