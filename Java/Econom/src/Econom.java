import java.io.PrintStream;
import java.util.Scanner;

public class Econom {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        PrintStream out = new PrintStream(System.out);

        String str, temp;
        str = in.next();
        int count = 0, len = str.length(), start = 0, brackets = 0;
        for(int i = 0; i < len; i++){
            if(str.charAt(i) == '('){
                brackets = 1;
                start = i;
                boolean flag = false;
                int k = start + 1;
                while(true){
                    if(str.charAt(k) == ')'){
                        if(brackets == 1){
                            if(str.indexOf(str.substring(i, k + 1)) == i){
                                //out.println(str.substring(i, k + 1));
                                count++;
                            }
                            //out.println(start);
                            i = (flag ? start-1 : k);
                            break;
                        }
                        else
                            brackets--;
                    }
                    if(str.charAt(k) == '(' && !flag){
                        brackets++;
                        start = k;
                        flag = true;
                    }
                    k++;
                }
            }
        }
        out.println(count);
    }
}
