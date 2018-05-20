import java.io.PrintStream;
import java.util.Scanner;

public class MinDist {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        PrintStream out = new PrintStream(System.out);
        String s = in.nextLine();
        char x = in.next().charAt(0), y = in.next().charAt(0);

        int flag = 0, i = 0, dist = 0, minDist = 1000001, len = s.length();
        while(flag == 0){
            if(s.charAt(i) == x)
                flag = 1;
            else if(s.charAt(i) == y)
                flag = -1;
            i++;
        }
        for(; i < len; i++){
            if(s.charAt(i) == x){
                if(flag == 1)
                    dist = 0;
                else if(flag == -1){
                    minDist = Math.min(minDist, dist);
                    flag *= -1;
                    dist = 0;
                }
            }
            else if(s.charAt(i) == y){
                if(flag == -1)
                    dist = 0;
                else if(flag == 1){
                    minDist = Math.min(minDist, dist);
                    flag *= -1;
                    dist = 0;
                }
            }
            else
                dist++;
        }

        out.println(minDist);

    }
}