public class MulUnsigned {
    private int [] num;

    public MulUnsigned(String str){
        num = new int [str.length()];
        for(int i = 0; i<num.length; i++){
            num[i] = Character.getNumericValue(str.charAt(i));
        }
    }

    public void multiply(int k){
        for(int i = 0; i < num.length; i++){
            num[i]*=k;
        }
        for(int j = num.length - 1; j > 0; j--){
            if(num[j]>9){
                num[j-1]+=num[j]/10;
                num[j]%=10;
            }
        }
        if(num[0]>9){
            int [] newNum = new int [num.length+1];
            newNum[0] = num[0]/10;
            num[0]%=10;
            for(int i = 1; i < num.length; i++){
                newNum[i] = num[i-1];
            }
            num = newNum;
        }
    }

    @Override
    public String toString() {
        String str = "", substr;
        boolean flag = false;
        for(int i = 0; i < num.length; i++){
            if(i == num.length - 1 || num[i] != 0) flag = true;
            if(num[i]==0 && !flag) continue;
            str = str.concat(Integer.toString(num[i]));
        }
        return str;
    }
}
