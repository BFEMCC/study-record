import java.io.*;
import java.util.*;

public class JBT2402 {
    public static void main(String[] arg) {
        Scanner stdin = new Scanner(System.in);
        System.out.print("输入岗位等级：");
        int grade = stdin.nextInt();
        System.out.println("");
        int wage = 0;
        if(grade == 1)
            wage = 2800;
        else if (grade == 2)
            wage = 1900;
        else if (grade == 3)
            wage = 1630;
        else if (grade == 4)
            wage = 1420;
        else if (grade == 5)
            wage = 1180;
        else if (grade == 6)
            wage = 1040;
        else if (grade == 7)
            wage = 930;
        else if (grade == 8)
            wage = 780;
        else if (grade == 9)
            wage = 730;
        else if (grade == 10)
            wage = 680;
        else if (grade == 11)
            wage = 620;
        else if (grade == 12)
            wage = 590;

        System.out.printf("岗位等级%2d的岗位工资=%4d\n",grade,wage);
    }
}
