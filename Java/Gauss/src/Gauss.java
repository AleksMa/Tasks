import java.io.PrintWriter;
import java.util.Scanner;

public class Gauss {
    public static void main(String[] args) throws CloneNotSupportedException {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);

        int n = in.nextInt();
        Ratio [][] matrix = new Ratio[n][n+1];

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n + 1; j++){
                matrix[i][j] = new Ratio(in.nextLong(), 1);
            }
        }
        //Опускаемся
        for(int i = 0; i < n; i++){

            if(matrix[i][i].getN() == 0) {
                int k = i;
                while(k < n){
                    if(matrix[k][i].getN() != 0){
                        Ratio [] C = new Ratio[n+1];
                        for(int j = 0; j < n + 1; j++){
                            C[j] = matrix[i][j];
                            matrix[i][j] = matrix[k][j];
                            matrix[k][j] = C[j];
                        }
                        break;
                    }
                    k++;
                }
                if(k >= n){
                    out.println("No solution");
                    System.exit(0);
                }
            }

            long numer = matrix[i][i].getN(), denom = matrix[i][i].getD();

            for(int j = i; j < n + 1; j++) {
                matrix[i][j].mul(new Ratio(denom, numer));
            }
            for(int k = i + 1; k < n; k++){
                Ratio [] temp = new Ratio [n+1];
                for(int j = i; j < n + 1; j++){
                    temp[j] = (Ratio) matrix[i][j].clone();
                    temp[j].mul(matrix[k][i]);
                    temp[j].mul(new Ratio(-1, 1));
                }
                for(int j = i; j < n + 1; j++){
                    matrix[k][j].add(temp[j]);
                }
            }

        }

        //Поднимаемся
        for(int i = n - 1; i > 0; i--){


            for(int k = i - 1; k >= 0; k--){

                Ratio [] temp = new Ratio [n+1];
                for(int j = i; j < n + 1; j++){
                    temp[j] = (Ratio) matrix[i][j].clone();
                    temp[j].mul(matrix[k][i]);
                    temp[j].mul(new Ratio(-1, 1));
                }
                for(int j = i; j < n + 1; j++){
                    matrix[k][j].add(temp[j]);
                }
            }

        }

        for(int i = 0; i < n; i++){
            out.println(matrix[i][n]);
        }

        in.close();
        out.flush();
        out.close();
    }
}




class Ratio implements Cloneable{
    private long n, d;

    public Ratio(long n, long d){
        this.n = n;
        this.d = d;
    }

    public static long gcd(long a, long b) {
        if (b==0) return a;
        return gcd(b,a % b);
    }

    private static long lcm(long a, long b)
    {
        return a * (b / gcd(a, b));
    }

    public long getN(){
        return this.n;
    }

    public long getD(){
        return this.d;
    }

    public void reduce(){
        long gcd = gcd(n, d);
        n /= gcd;
        d /= gcd;


        if(d < 0){
            n *= -1;
            d *= -1;
        }
    }

    public Ratio add(Ratio y){
        long newDenom = lcm(this.d, y.getD());
        this.n = n * newDenom / d + y.getN() * newDenom / y.getD();
        this.d = newDenom;
        this.reduce();
        return this;
    }

    public Ratio mul(Ratio y){
        this.n *= y.getN();
        this.d *= y.getD();
        this.reduce();
        return this;
    }

    @Override
    public String toString() {
        return this.n + "/" + this.d;
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        return super.clone();
    }
}