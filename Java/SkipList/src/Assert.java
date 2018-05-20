
public class Assert {
    public static <T> void assertNull(T obj) {
        if (obj != null) report("expected null value");
    }

    public static void assertTrue(boolean b) {
        if (!b) report("expected true value");
    }

    public static void assertFalse(boolean b) {
        if (b) report("expected false value");
    }

    public static <T> void assertEquals(T expected, T actual) {
        if (!expected.equals(actual)) report("" + expected + " expected, but " + actual + " found");
    }

    public static <T extends Number> void assertEquals(T expected, T actual, double eps) {
        double a = expected.doubleValue(), b = actual.doubleValue();
        if (Math.abs(a-b) > eps) report("" + expected + " expected, but " + actual + " found");
    }

    private static void report(String s) {
        System.out.println(s);
        System.exit(0);
    }
}