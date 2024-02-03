#include <iostream>
#include <string>
#include <vector>
#include <stack>

// 检查字符是否为操作符（+、-、*、/）
bool isOperator(const char& c)
{
    // static const std::string operators = "+-*/";
    // return operators.find(c) != std::string::npos;
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// 将数学表达式转换为标记（token）序列
std::vector<std::string> tokenizeMathExpression(const std::string &expression)
{
    std::vector<std::string> tokens; // 存储表达式标记的向量
    std::string currentToken;        // 当前标记

    // 遍历给定的表达式
    for (size_t i = 0; i < expression.length(); ++i)
    {
        char currentChar = expression[i]; // 获取当前字符

        // 跳过空格
        if (isspace(currentChar))
            continue;

        // 判断字符是否是操作符或括号
        if (isOperator(currentChar) || currentChar == '(' || currentChar == ')')
        {
            // 如果当前标记不为空，将其添加到标记向量中并清空当前标记
            if (!currentToken.empty())
            {
                tokens.push_back(currentToken);
                currentToken.clear();
            }

            // 考虑负数的情况
            if (currentChar == '-' && (i == 0 || expression[i - 1] == '('))
                currentToken += currentChar;
            else
                tokens.push_back(std::string(1, currentChar));
        }
        else
        {
            // 将字符添加到当前标记，并检查是否为完整的标记
            currentToken += currentChar;
            if (i == expression.length() - 1 || isOperator(expression[i + 1]) || expression[i + 1] == '(' || expression[i + 1] == ')')
            {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        }
    }
    return tokens; // 返回标记向量
}

// 检查字符串是否可转换为双精度浮点数
bool isConvertibleToDouble(const std::string str)
{
    try
    {
        size_t pos = 0;
        (void)std::stod(str, &pos);
        return pos == str.length();
    }
    catch (...)
    {
        return false;
    }
}

// 获取操作符的优先级
int getPrecedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0;
}

// 将中缀表达式转换为后缀表达式
std::vector<std::string> infixToPostfix(const std::vector<std::string> &infixTokens)
{
    std::stack<char> operators;       // 用于存储操作符的栈
    std::vector<std::string> postfix; // 存储后缀表达式的向量

    // 遍历中缀表达式的标记
    for (const std::string &token : infixTokens)
    {
        if (isConvertibleToDouble(token))
        {
            postfix.push_back(token);
        }
        else if (token == "(")
        {
            operators.push('(');
        }
        else if (token == ")")
        {
            // 处理括号
            while (!operators.empty() && operators.top() != '(')
            {
                postfix.push_back(std::string(1, operators.top()));
                operators.pop();
            }
            operators.pop(); // 弹出左括号
        }
        else if (isOperator(token[0]))
        {
            // 处理操作符
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(token[0]))
            {
                postfix.push_back(std::string(1, operators.top()));
                operators.pop();
            }
            operators.push(token[0]);
        }
    }

    // 处理剩余的操作符
    while (!operators.empty())
    {
        postfix.push_back(std::string(1, operators.top()));
        operators.pop();
    }
    return postfix; // 返回后缀表达式
}

// 根据后缀表达式求值
long double postfixToVaule(std::vector<std::string> &postfix)
{
    std::stack<long double> sk;
    for (int i = 0; i < postfix.size(); i++)
    {
        if (postfix[i] == "+" || postfix[i] == "-" || postfix[i] == "*" || postfix[i] == "/")
        {
            long double b = sk.top();
            sk.pop();
            long double a = sk.top();
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
    std::string mathExpression = "9.1+(3.2-1.3)*3.4+(-15-(-19.8))-10.5/2.6-(-1.7)"; // 18.0215
    // std::string mathExpression = "9+(3-1)*3+10/2";//20

    std::vector<std::string> infix = tokenizeMathExpression(mathExpression);
    std::cout << "中缀表达式：";
    for (const auto &token : infix)
        std::cout << token << " , ";
    std::cout << std::endl;

    std::vector<std::string> postfix = infixToPostfix(infix);
    std::cout << "后缀表达式：";
    for (const auto &token : postfix)
        std::cout << token << " , ";
    std::cout << std::endl;

    std::cout << mathExpression << " = " << postfixToVaule(postfix);

    return 0;
}
