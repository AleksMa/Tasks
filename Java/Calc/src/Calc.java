import java.io.PrintStream;
import java.util.*;

public class Calc {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        PrintStream out = new PrintStream(System.out);

        String src = in.nextLine();
        ArrayDeque <String> lexems = new ArrayDeque <String>();
        Map< String, Integer > variables = new HashMap< String, Integer >();

        //LEXER
        int i = 0;
        while(i < src.length()){
            if(Character.isDigit(src.charAt(i))){
                int k = i++;
                while(i < src.length() && Character.isDigit(src.charAt(i)))
                    i++;
                lexems.add(src.substring(k, i));
            }
            else if(Character.isLetter(src.charAt(i))){
                int k = i++;
                while(i < src.length() && (Character.isLetter(src.charAt(i)) || Character.isDigit(src.charAt(i))))
                    i++;
                String varName = src.substring(k, i);
                lexems.add(varName);
                if(variables.get(varName) == null){
                    int value = in.nextInt();
                    variables.put(varName, value);
                }
            }
            else if(src.charAt(i) == ' '){
                i++;
            }
            else
                lexems.add("" + src.charAt(i++));
        }

        //PARSER

        Parse p = new Parse(lexems, variables);
        out.println(p);
    }



}


class Parse{
    private int res;
    private Deque <String> lexems;
    private Map< String, Integer > variables;

    public Parse(Deque <String> lexems, Map< String, Integer > variables){
        this.lexems = lexems;
        this.variables = variables;
        this.res = ParseE();
        if(!lexems.isEmpty()){
            System.out.println("error");
            System.exit(0);
        }
    }

    @Override
    public String toString() {
        return "" + res;
    }

    public int ParseE(){
        int acc = ParseT();
        return ParseAdd(acc);
    }

    public int ParseAdd(int acc){
        if(lexems.isEmpty())
            return acc;
        else{
            String lexem = lexems.peek();
            char ch  = lexem.charAt(0);
            if(ch == '+'){
                lexems.pop();
                return ParseAdd(acc + ParseT());
            }
            else if(ch == '-'){
                lexems.pop();
                return ParseAdd(acc - ParseT());
            }
            else{
                return acc;
            }
        }
    }
    public int ParseT(){
        int acc = ParseF();
        return ParseMul(acc);
    }
    public int ParseMul(int acc){
        if(lexems.isEmpty())
            return acc;
        else{
            String lexem = lexems.peek();
            char ch  = lexem.charAt(0);
            if(ch == '*'){
                lexems.pop();
                return ParseMul(acc * ParseF());
            }
            else if(ch == '/'){
                lexems.pop();
                return ParseMul(acc / ParseF());
            }
            else{
                return acc;
            }
        }
    }
    public int ParseF(){
        if(lexems.isEmpty()){
            System.out.println("error");
            System.exit(0);
        }
        String lexem = lexems.pop();
        char ch  = lexem.charAt(0);
        if(Character.isDigit(ch)){
            return Integer.parseInt(lexem);
        }
        else if(Character.isLetter(ch))
            return variables.get(lexem);
        else if(ch == '('){
            int acc = ParseE();
            if(!lexems.isEmpty() && lexems.peek().charAt(0) == ')'){
                lexems.pop();
            }
            else{
                System.out.println("error");
                System.exit(0);
            }
            return acc;
        }
        else if(ch == '-'){
            return -1 * ParseF();
        }
        else{
            System.out.println("error");
            System.exit(0);
            return 0;
        }
    }
}
