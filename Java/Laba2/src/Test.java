import java.io.PrintStream;
import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        PrintStream out = new PrintStream(System.out);

        //Расширенная таблица умножения
        for(int i = 0; i<=20; i++){
            for(int j = 0; j<=9; j++){
                MulUnsigned n = new MulUnsigned(Integer.toString(i));
                n.multiply(j);
                out.print(i + " * " + j + " = " + n + "   ");
            }
            out.println();
        }

        //Число * {0, ..., 9}
        String str = in.next();
        MulUnsigned t = new MulUnsigned(str);
        int k = in.nextInt();
        t.multiply(k);
        out.println(t);
    }
}