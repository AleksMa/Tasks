import java.io.File;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class Sync {
    public static void main(String[] args) throws IOException {
        PrintStream out = new PrintStream(System.out);
        String S = args[0];
        String D = args[1];
        //out.println(S + " " + D);
        File dirS = new File("/home/alexey/"+S);
        File dirD = new File("/home/alexey/"+D);


        out.println(dirD);
        out.println(dirS);

        //CompareDirs a = new CompareDirs(dirS, dirD);
    }
}

class CompareDirs{
    private TreeSet<String> delete, copy;

    public CompareDirs(File S, File D) throws IOException {
        this.delete = new TreeSet<>();
        this.copy = new TreeSet<>();
        compare(S, D, "");
        if(delete.size() == 0 && copy.size() == 0)
            System.out.println("IDENTICAL");
        else{
            for(String item : delete){
                System.out.println(item);
            }
            for(String item : copy){
                System.out.println(item);
            }
        }
    }

    public void compare(File dirS, File dirD, String add) throws IOException {
        Map <String, File>  S = new HashMap<>(), D = new HashMap<>();
        for(File item : dirS.listFiles()){
            S.put(item.getName(), item);
        }
        for(File item : dirD.listFiles()){
            D.put(item.getName(), item);
        }
        Iterator<Map.Entry<String, File>> it = S.entrySet().iterator();
        while(it.hasNext()){
            Map.Entry<String, File> e = it.next();
            if(D.containsKey(e.getKey())){

                File s = e.getValue(), d = D.get(e.getKey());
                if(!s.isDirectory()){

                    byte [] byteS = Files.readAllBytes(Paths.get(s.getAbsolutePath()));
                    byte [] byteD = Files.readAllBytes(Paths.get(d.getAbsolutePath()));

                    if(!Arrays.equals(byteS, byteD)){
                        delete.add("DELETE " + add + d.getName());
                        copy.add("COPY " + add + d.getName());
                    }
                }
                else{
                    compare(s, d, add+s.getName()+"/");
                }
            }else{
                if(!e.getValue().isDirectory())
                    copy.add("COPY " + add + e.getValue().getName());
                else{
                    copyDirectory(e.getValue(), add+e.getValue().getName()+"/");
                }
            }
        }

        Iterator<Map.Entry<String, File>> jt = D.entrySet().iterator();
        while(jt.hasNext()){
            Map.Entry<String, File> e = jt.next();
            if(S.containsKey(e.getKey())){
                File d = e.getValue(), s = S.get(e.getKey());
                if(d.isDirectory()){
                    compare(s, d, add+s.getName()+"/");
                }
            }
            else{
                if(!e.getValue().isDirectory()){
                    delete.add("DELETE " + add + e.getValue().getName());
                } else{
                    deleteDirectory(e.getValue(), add+e.getValue().getName()+"/");
                }
            }
        }
    }

    public void copyDirectory(File f, String add){
        for(File item : f.listFiles()){
            if(item.isDirectory())
                copyDirectory(item, ""+item.getName()+"/");
            else
                copy.add("COPY " + add + item.getName());
        }
    }

    public void deleteDirectory(File f, String add){
        for(File item : f.listFiles()){
            if(item.isDirectory())
                deleteDirectory(item, ""+item.getName()+"/");
            else
                copy.add("COPY " + add + item.getName());
        }
    }
}