import java.util.*;
import java.io.*;

public class Test {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        PrintStream out = new PrintStream(System.out);

        File dir = new File(args[0]);

        ArrayList <SourceCode> arr = new ArrayList<>();

        for(File item : dir.listFiles()){
            SourceCode e = new SourceCode(item);
            arr.add(e);
        }

        SourceCode [] a = arr.toArray(new SourceCode[arr.size()]);
        for(SourceCode file : a)
            out.println(file);
        out.println();
        Arrays.sort(a);
        for(SourceCode file : a)
            out.println(file);

        out.println();

        out.println(a[1].size());
        out.println(a[1].getComments());

        out.println(a[a.length - 1].size());
        out.println(a[a.length - 1].getComments());

    }
}
