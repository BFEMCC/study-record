#include <string>
#include <vector>
#include <stack>
#include <functional>
#include <iostream>

// 中缀表达式求值
long double infixToValue(const std::string &expression) throw()
{
    static const std::function<bool(char)> isOperator{
        [](const char &c) -> bool
        { return (c == '+' || c == '-' || c == '*' || c == '/'); }};
    static const std::function<bool(const std::string)> isConvertibleToDouble{
        [](const std::string str) -> bool
        {
            try
            {
                size_t pos = 0;
                (void)std::stold(str, &pos);
                return pos == str.length();
            }
            catch (...)
            {
                return false;
            }
        }};
    static const std::function<int(char)> getPrecedence{
        [](const char &op) -> int
        {
            if (op == '+' || op == '-')
                return 1;
            else if (op == '*' || op == '/')
                return 2;
            return 0;
        }};
    std::vector<std::string> tokens;
    std::string currentToken;
    for (size_t i = 0; i < expression.length(); ++i)
    {
        char currentChar = expression[i];
        if (isspace(currentChar))
            continue;
        if (isOperator(currentChar) || currentChar == '(' || currentChar == ')')
        {
            if (!currentToken.empty())
            {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            if (currentChar == '-' && (i == 0 || expression[i - 1] == '('))
                currentToken += currentChar;
            else
                tokens.push_back(std::string(1, currentChar));
        }
        else
        {
            currentToken += currentChar;
            if (i == expression.length() - 1 || isOperator(expression[i + 1]) || expression[i + 1] == '(' || expression[i + 1] == ')')
            {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        }
    }
    std::stack<char> operators;
    std::vector<std::string> postfix;
    for (const std::string &token : tokens)
    {
        if (isConvertibleToDouble(token))
            postfix.push_back(token);
        else if (token == "(")
            operators.push('(');
        else if (token == ")")
        {
            while (!operators.empty() && operators.top() != '(')
            {
                postfix.push_back(std::string(1, operators.top()));
                operators.pop();
            }
            operators.pop();
        }
        else if (isOperator(token[0]))
        {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(token[0]))
            {
                postfix.push_back(std::string(1, operators.top()));
                operators.pop();
            }
            operators.push(token[0]);
        }
    }
    while (!operators.empty())
    {
        postfix.push_back(std::string(1, operators.top()));
        operators.pop();
    }

    std::stack<long double> sk;
    int size = postfix.size();
    long double a;
    long double b;
    for (int i = 0; i < size; i++)
    {
        if (postfix[i] == "+" || postfix[i] == "-" || postfix[i] == "*" || postfix[i] == "/")
        {
            b = sk.top();
            sk.pop();
            a = sk.top();
            sk.pop();
            switch (postfix[i][0])
            {
            case '+':
                sk.push(a + b);
                break;
            case '-':
                sk.push(a - b);
                break;
            case '*':
                sk.push(a * b);
                break;
            case '/':
                sk.push(a / b);
                break;
            }
        }
        else
        {
            sk.push(std::stold(postfix[i]));
        }
    }
    return sk.top();
}

int main()
{
    // std::string expression;
    // while (true)
    // {
    //     std::cin >> expression;
    //     std::cout << infixToValue(expression) << std::endl;
    // }

    
    // 测试案例
    std::vector<std::string> mathExpressions = {
        "9+(3-1)*3+10/2",
        "3.5+1/6.6+10/2",
        "7-4/2+8*2",
        "5*2+10/5-3",
        "-1+3*6/2.5",
        "4.8-2*1+7/2",
        "10-3+4*6/2",
        "7/2*8-9+4",
        "6.3-2/0.5+5*3",
        "2+4*5/2-3.5",
        "1-4/2+5*3.5",
        "9*2-7/1.4+3",
        "6/3+4-1*7",
        "5+8/2-4*1.2",
        "3.5-6/3+2*7",
        "10/5+3-1.5*2",
        "7*2-1+8/4",
        "3.5+2-4/2*5",
        "9-3*6/2+5",
        "8/2*5-3+6",
        "5+3.6/1.2-7",
        "6-4/2+9*1.5",
        "3+2*7/1.4-6",
        "10/2+6-2.5*4",
        "8*3-2/1+4.5",
        "4+5/1.25-3*2",
        "7/2-1+4*2.5",
        "5-3/1.5+6*2",
        "2*6/3-1+7.5",
        "9/3+2-1.25*4",
        "6*2-4/2+3.5",
        "3.5+7-2*1/0.5",
        "8-2.5/0.5+6*1.25",
        "4.5+3*1/0.75-2",
        "9-5/2.5+4*1.2",
        "6*2+8/4-1.5",
        "3.5-7/3+4*1.25",
        "8/4+2-1.5*3",
        "5-1/0.5+2*7",
        "3*5/1.5-2+6",
        "7-2/0.5+4*1.5",
        "6*3/1.2-2+5",
        "9/3+1-2.5*4",
        "8-4/1+5*1.5",
        "4+7/3-1.5*2",
        "7/1.4-3+2*5",
        "5-1*8/2+4",
        "3*2/1-4+5.5",
        "9/1.5-2*3+4",
        "6+2/1-3*4.5",
        "10/2-3*1+5",
        "8-4/2+1*3.5",
        "4*3/1.5-2+6",
        "7-3/1+5*2.5",
        "5*2/1-3+4.5",
        "3+1/0.5-2*6",
        "9*2/1.5-4+3",
        "6+2*5/2-3.5",
        "10/2*1-4+7.5",
        "8-2*4/1+5",
        "4+3*2/1.5-5",
        "7-3*1/0.5+4",
        "5*2/1-4+3.5",
        "3+2/1-5*1.2",
        "9*1/1.5-6+2",
        "6+2*4/2-3.5",
        "10/2*1-3+5.5",
        "8-2*3/1+4",
        "4+3*2/1.5-6",
        "7-3*1/0.5+3.5",
        "5*2/1-4+4.5",
        "3+2/1-5*1.5",
        "9*1/1.5-5+2",
        "6+2*4/2-4.5",
        "10/2*1-3+6.5",
        "8-2*3/1+3",
        "4+3*2/1.5-7",
        "7-3*1/0.5+5.5",
        "5*2/1-4+5.5",
        "3+2/1-6*1.2",
        "9*1/1.5-4+3",
        "6+2*4/2-5.5",
        "10/2*1-2+7.5",
        "8-2*3/1+2",
        "4+3*2/1.5-8",
        "7-3*1/0.5+6.5",
        "5*2/1-4+6.5",
        "3+2/1-7*1.2",
        "9*1/1.5-3+4",
        "6+2*4/2-6.5",
        "10/2*1-1+8.5",
        "8-2*3/1+1"};

    for (std::string &Expression : mathExpressions)
    {
        std::cout << Expression << "=" << infixToValue(Expression) << std::endl;
    }
}