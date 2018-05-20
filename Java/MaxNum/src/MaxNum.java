import java.io.PrintStream;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

class Compare implements Comparator<String>
{
    @Override
    public int compare(String str1, String str2)
    {
        String a, b;
        if(str1.length() >= str2.length()){
            a = str2;
            b = str1;
        } else {
            b = str2;
            a = str1;
        }

        int len = a.length(), maxlen = b.length(), i = 0;
        for(; i < len; i++){
            if(a.charAt(i) != b.charAt(i))
                return str1.charAt(i) - str2.charAt(i);
        }
        for(; i < maxlen; i++){
            if(b.charAt(i-len) != b.charAt(i))
                return (b.equals(str2)? b.charAt(i-len) - b.charAt(i) : b.charAt(i) - b.charAt(i - len));
        }
        return 0;
    }
}

public class MaxNum {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        PrintStream out = new PrintStream(System.out);

        int n = in.nextInt();
        String [] arr = new String[n];
        for(int i = 0; i < n; i++){
            arr[i] = in.next();
        }
        Arrays.sort(arr, new Compare());


        for(int i = n - 1; i >= 0; i--){
            out.print(arr[i]);
        }
    }
}
