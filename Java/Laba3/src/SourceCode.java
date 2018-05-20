import java.io.*;
import java.nio.*;
import java.util.*;

public class SourceCode implements Comparable <SourceCode>{
    //private File file;
    private String filename;
    private ArrayList<String> comments, src;
    private int size;

    public SourceCode(File file) throws IOException{
        makeEverything(file);
    }

    public SourceCode(String path) throws IOException{
        makeEverything(new File(path));
    }

    private void makeEverything(File file) throws IOException{
        this.filename = file.getName();
        this.size = 0;
        this.comments = new ArrayList<>();
        this.src = new ArrayList<>();
        Scanner in = new Scanner(new BufferedReader(new FileReader(file.getAbsolutePath())));
        while(in.hasNext()){
            src.add(in.nextLine());
        }

        String buf = "";
        boolean isComment = false;
        for(String str : src){
            char ch;
            for(int  i = 0; i < str.length(); i++){
                ch = str.charAt(i);
                if(ch == '/' && i < str.length() - 1 && !isComment){
                    if(str.charAt(i+1) == '/'){
                        String sub = str.substring(i+2);
                        comments.add(sub);
                        size += sub.length();
                        break;
                    }
                    else if(str.charAt(i+1) == '*'){
                        buf = "";
                        isComment = true;
                        i++;
                        continue;
                    }
                }
                if(isComment){
                    if(ch == '*' && i < str.length() - 1 && str.charAt(i+1) == '/'){
                        isComment = false;
                        comments.add(buf);
                        size += buf.length();
                    }
                    else{
                        buf+=ch;
                    }
                    if(i == str.length() - 1){
                        buf+="\n";
                    }
                }
            }
        }
    }

    @Override
    public String toString() {
        String res = this.filename;
        /*
        for(String item : src){
            res += item + "\n";
        }
        */
        return res;
    }



    public String getComments(){
        String res = "";
        for(String item : comments){
            res += item + "\n";
        }
        return res;
    }

    public int size(){
        return this.size;
    }

    @Override
    public int compareTo(SourceCode o) {
        return this.size - o.size;
    }
}
