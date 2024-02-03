//int 最大值 2147483647
//int 最小值 -2147483647

public class JBT2203
{
    public static void main(String [] arg)
    {
        byte a = 120;
        short b = 225;
        int c = 2200;
        long d = 2147483649L;
        float f1;
        float f2;
        double g = 0.1234567812345678;

        b = a; //低精度赋值给高精度
        c = (int)a;//高精度强制转换赋值给低精度
        f1 = a;//低精度赋值给高精度
        f2 = (float)g;//高精度强制转换赋值给低精度

        System.out.println("a = " + a);
        System.out.println("b = " + b);
        System.out.println("c = " + c);
        System.out.println("d = " + d);
        System.out.println("f1 = " + f1);
        System.out.println("f2 = " + f2);
        System.out.println("g = " + g);
        
    }
}