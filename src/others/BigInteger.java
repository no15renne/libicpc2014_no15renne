import java.math.*;
import java.util.*;
class Main {
     public static void main(String[] args) {
          new Main().new pku1405().run();
     }
     class pku1405{
          void run(){
               int n;
               BigInteger ans[]=new BigInteger[20];
               Scanner sc=new Scanner(System.in);
              
               ans[1]=BigInteger.valueOf(2); ans[2]=BigInteger.valueOf(3);
               for(int i=3;i<=18;i++){
                    ans[i]=BigInteger.ONE;
                    for(int j=1;j<i;j++)ans[i]=ans[i].multiply(ans[j]);
                    ans[i]=ans[i].add(BigInteger.ONE);
               }
              
               n=sc.nextInt();
               for(int i=1;i<=n;i++)System.out.println(ans[i]);
          }
     }
}
