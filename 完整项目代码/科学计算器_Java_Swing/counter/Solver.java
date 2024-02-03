package counter;

import java.util.ArrayList;
import java.util.Stack;

public class Solver
{
    // 检查字符是否为操作符（+、-、*、/）
    private static boolean isOperator(char c)
    {
        return (c == '+' || c == '-' || c == '*' || c == '/');
    }

    // 检查字符串是否可转换为双精度浮点数
    private static boolean isConvertibleToDouble(String str)
    {
        try
        {
            Double.parseDouble(str);
            return true;
        }
        catch (NumberFormatException e)
        {
            return false;
        }
    }

    // 获取操作符的优先级
    private static int getPrecedence(char op)
    {
        if (op == '+' || op == '-')
            return 1;
        else if (op == '*' || op == '/')
            return 2;
        return 0;
    }

    // 将分割好的中缀表达式转换为后缀表达式
    private static ArrayList<String> infixToPostfix(ArrayList<String> infixTokens)
    {
        Stack<Character> operators = new Stack<>();    // 用于存储操作符的栈
        ArrayList<String> postfix = new ArrayList<>(); // 存储后缀表达式的ArrayList

        for (String token : infixTokens)
        {
            if (isConvertibleToDouble(token))
                postfix.add(token);
            else if (token.equals("("))
                operators.push('(');
            else if (token.equals(")"))
            {
                // 处理括号
                while (!operators.isEmpty() && operators.peek() != '(')
                {
                    postfix.add(String.valueOf(operators.peek()));
                    operators.pop();
                }
                operators.pop(); // 弹出左括号
            }
            else if (isOperator(token.charAt(0)))
            {
                // 处理操作符
                while (!operators.isEmpty() && getPrecedence(operators.peek()) >= getPrecedence(token.charAt(0)))
                {
                    postfix.add(String.valueOf(operators.peek()));
                    operators.pop();
                }
                operators.push(token.charAt(0));
            }
        }

        // 处理剩余的操作符
        while (!operators.isEmpty())
        {
            postfix.add(String.valueOf(operators.peek()));
            operators.pop();
        }

        return postfix; // 返回后缀表达式
    }

    // 根据后缀表达式求值
    private static double postfixToValue(ArrayList<String> postfix)
    {
        Stack<Double> stack = new Stack<>();

        for (String token : postfix)
        {
            if (token.equals("+") || token.equals("-") || token.equals("*") || token.equals("/"))
            {
                double b = stack.pop();
                double a = stack.pop();
                switch (token)
                {
                    case "+":
                        stack.push(a + b);
                        break;
                    case "-":
                        stack.push(a - b);
                        break;
                    case "*":
                        stack.push(a * b);
                        break;
                    case "/":
                        stack.push(a / b);
                        break;
                }
            }
            else
            {
                stack.push(Double.parseDouble(token));
            }
        }
        return stack.peek();
    }

    public static double infixToValue(ArrayList<String> expression)
    {
        return postfixToValue(infixToPostfix(expression));
    }
}
