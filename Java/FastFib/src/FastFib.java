import java.io.PrintStream;
import java.math.BigInteger;
import java.util.Scanner;

public class FastFib
{
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        PrintStream out = new PrintStream(System.out);
        int N = in.nextInt();
        int deg = N-1;
        // Очевидно, что превый столбец матрицы {{1 1} {1 0}}^n равен матрице-столбцу {{1 1} {1 0}}^(n-1) * {{1} {1}},
        // и элемент (1, 1) этих матриц есть (n+1)-e число Фибоначчи
        Matrix A = new Matrix(BigInteger.ONE, BigInteger.ONE, BigInteger.ONE, BigInteger.ZERO);
        Matrix res = new Matrix(BigInteger.ONE, BigInteger.ZERO, BigInteger.ZERO, BigInteger.ONE); //Единичная матрица - нейтральный элемент умножения
        while(deg > 0){
            if(deg % 2 == 1){
                res.multiply(A);
                deg--;
            } else {
                A.multiply(A);
                deg /= 2;
            }
        }
        out.println(res.get(1, 1));
    }
}



class Matrix{
    private BigInteger [][] A = new BigInteger[2][2];

    public Matrix(BigInteger a11, BigInteger a12, BigInteger a21, BigInteger a22){
        A[0][0] = a11;
        A[0][1] = a12;
        A[1][0] = a21;
        A[1][1] = a22;
    }

    public BigInteger get(int x, int y) {
        return this.A[x-1][y-1];
    }

    public void set(int x, int y, BigInteger val) {
        this.A[x-1][y-1] = val;
    }

    public void multiply(Matrix B){
        Matrix C = new Matrix(BigInteger.ONE, BigInteger.ZERO, BigInteger.ZERO, BigInteger.ONE);
        C.set(1, 1, this.A[0][0].multiply(B.get(1, 1)).add(this.A[0][1].multiply(B.get(2, 1))));
        C.set(1, 2, this.A[0][0].multiply(B.get(1, 2)).add(this.A[0][1].multiply(B.get(2, 2))));
        C.set(2, 1, this.A[1][0].multiply(B.get(1, 1)).add(this.A[1][1].multiply(B.get(2, 1))));
        C.set(2, 2, this.A[1][0].multiply(B.get(1, 2)).add(this.A[1][1].multiply(B.get(2, 2))));
        this.A = C.A;
        /*for(int i = 1; i <= 2; i++){
            for(int j = 1; j <= 2; j++){
                this.set(i, j, C.get(i, j));
            }
        }*/
    }

    @Override
    public String toString() {
        return A[0][0] + " " + A[0][1] + "\n" + A[1][0] + " " + A[1][1];
    }
}
