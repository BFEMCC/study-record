public class JBT2404 {
    public static void main(String[] arg)    {
        int n =10;
        int m = 5;
        System.out.println("for循环求解下结果="+sum1(n,m));
        System.out.println("while循环求解下结果="+sum2(n,m));
        System.out.println("do while循环求解下结果="+sum3(n,m));
    }
    //for循环
    public static long sum1(int n, int m)    {
        long sum = 0;
        for(int i =0; i <= n; i++)        {
            if(i % m == 0)
                sum += i;
        }
        return  sum;
    }

    //while循环
    public static long sum2(int n, int m)    {
        long sum = 0;
        int i = 0;
        while(i <= n )        {
            if(i % m == 0)
                sum += i;
            i++;
        }
        return  sum;
    }
    public static long sum3(int n, int m)    {
        long sum = 0;
        int i = 0;
        do {
            if(i % m == 0)
                sum += i;
            i++;
        }while(i <= n);
        return  sum;
    }
}
