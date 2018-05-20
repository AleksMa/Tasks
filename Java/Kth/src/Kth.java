import java.util.Scanner;

public class Kth {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        long k = in.nextLong();
        long i = 0, n = 0;

        while(k >= n){
            n += 9 * (long)Math.pow(10, i) * ++i;
        }
        n-= i-- * 9 * (long)Math.pow(10, i++);

        long num = (long)Math.pow(10, i-1) + (k - n) / i;
        long digit = (long)Math.pow(10, i - 1 - (k - n) % i);

        System.out.println(num / digit % 10);
    }
}
