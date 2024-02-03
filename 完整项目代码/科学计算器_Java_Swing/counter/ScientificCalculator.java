package counter;

import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.UIManager;
import javax.swing.JTextField;
import javax.swing.JOptionPane;
import javax.swing.WindowConstants;
import javax.swing.UnsupportedLookAndFeelException;

import java.awt.Font;
import java.awt.Color;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import java.util.ArrayList;

public class ScientificCalculator extends JFrame implements ActionListener
{
    private final JButton[] button_array = new JButton[35];             //按钮
    private final JTextField line_edit_history = new JTextField("");    //历史记录单行文本框
    private final JTextField line_edit_show = new JTextField("0");      //显示过程和结果单行文本框

    private final ArrayList<String> infixTokens = new ArrayList<>();            //中缀表达式
    private final ArrayList<String> history_input = new ArrayList<>();          //历史步骤
    private boolean is_point_alive = false;
    private boolean input_right_operations = false;                       //输入右操作数状态
    private boolean special_operator = false;

    private int left_bracket = 0;             //左括号数量
    private int right_bracket = 0;            //右括号数量


    public ScientificCalculator()throws UnsupportedLookAndFeelException, ClassNotFoundException, InstantiationException, IllegalAccessException
    {
        inItUi();
    }

    private void inItUi() throws UnsupportedLookAndFeelException, ClassNotFoundException, InstantiationException, IllegalAccessException
    {
        UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());    //使用当前系统UI样式
        setSize(550, 690);
        setTitle("科学计算器");
        setAlwaysOnTop(true);                                                   //窗口置顶
        setLocationRelativeTo(null);                                            //初始时窗口居中
        getContentPane().setBackground(new Color(239, 244, 249));       //设置背景颜色
        setLayout(null);                                                        //取消默认布局
        setResizable(false);                                                    //禁止调整大小

        int width_interval = 105;
        int height_interval = 50;
        int x = 5;
        int y = 300;
        int width = 105;
        int height = 45;

        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                button_array[i * 5 + j] = new JButton();
                button_array[i * 5 + j].setBounds(x + width_interval * (j % 5), y + (i * height_interval), width, height);  //设置按钮坐标
                button_array[i * 5 + j].setFocusPainted(false);         //去除焦点时的文字边框
                button_array[i * 5 + j].setFocusable(false);            //默认无法获取焦点
                button_array[i * 5 + j].setFont(new Font("微软雅黑",Font.PLAIN,23));    //设置按钮字体，默认样式，字号
                button_array[i * 5 + j].addActionListener(this);      //添加鼠标事件
                getContentPane().add(button_array[i * 5 + j]);          //添加到内容布局中
            }
        }

        // 设置文本框的位置和大小
        line_edit_show.setBounds(13,105,510, 110);
        line_edit_history.setBounds(13 , 65, 510, 30);
        //右对齐
        line_edit_show.setHorizontalAlignment(JTextField.RIGHT);
        line_edit_history.setHorizontalAlignment(JTextField.RIGHT);
        //只读
        line_edit_show.setEditable(false);
        line_edit_history.setEditable(false);
        //设置字体
        line_edit_show.setFont(new Font(line_edit_show.getFont().getFontName(),Font.PLAIN,40));
        line_edit_history.setFont(new Font(line_edit_history.getFont().getFontName(),Font.PLAIN,18));
        //无法获取焦点
        line_edit_show.setFocusable(false);
        line_edit_history.setFocusable(false);
        getContentPane().add(line_edit_show);
        getContentPane().add(line_edit_history);

        //设置按钮文字
        button_array[0].setText("sin");       //sin
        button_array[1].setText("π");         //π
        button_array[2].setText("e");         //e
        button_array[3].setText("C");         //C
        button_array[4].setText("←");         //←

        button_array[5].setText("cos");       //cos
        button_array[6].setText("1/x");       //1/x
        button_array[7].setText("|x|");       //|x|
        button_array[8].setText("10^x");      //10^x
        button_array[9].setText("³√x");       //³√x

        button_array[10].setText("tan");      //tan
        button_array[11].setText("(");        //(
        button_array[12].setText(")");        //)
        button_array[13].setText("e^x");      //e^x
        button_array[14].setText("÷");        //÷

        button_array[15].setText("x²");       //x²
        button_array[16].setText("7");        //7
        button_array[17].setText("8");        //8
        button_array[18].setText("9");        //9
        button_array[19].setText("×");        //×

        button_array[20].setText("√x");       //+/-
        button_array[21].setText("4");        //0
        button_array[22].setText("5");        //.
        button_array[23].setText("6");        //=
        button_array[24].setText("-");        //-

        button_array[25].setText("log");      //log
        button_array[26].setText("1");        //1
        button_array[27].setText("2");        //2
        button_array[28].setText("3");        //3
        button_array[29].setText("+");        //+

        button_array[30].setText("ln");       //ln
        button_array[31].setText("-/+");      //-/+
        button_array[32].setText("0");        //0
        button_array[33].setText(".");        //.
        button_array[34].setText("=");        //=
    }

    //检查小数点存在情况
    private void checkPoint()
    {
        is_point_alive = false; //状态复位
        for(char t :  line_edit_show.getText().toCharArray())
        {
            if(t == '.')
            {
                is_point_alive = true;
                break;
            }
        }
    }

    //获取完整的中缀表达式
    private String getAllToken(ArrayList<String> Tokens)
    {
        StringBuilder tonkens = new StringBuilder();
        for(String token : Tokens)
            tonkens.append(token);
        return tonkens.toString();
    }

    //替换数学乘除号为ASCII乘除号
    private void replaceMatchToASCII(ArrayList<String> Tokens)
    {
        for (int i = 0; i < Tokens.size(); i++)
        {
            String t = Tokens.get(i);
            if (t.equals("×"))
                Tokens.set(i, "*");
            else if (t.equals("÷"))
                Tokens.set(i, "/");
        }
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        String button_text = ((JButton) e.getSource()).getText();

        //点击数字
        if(button_text.matches("[0-9]"))
        {
            if (line_edit_show.getText().equals("0") && !button_text.equals("."))//清除默认的0
                line_edit_show.setText("");
            if(!input_right_operations)
                line_edit_show.setText(line_edit_show.getText() + button_text);
            else
            {
                line_edit_show.setText("");
                line_edit_show.setText(button_text);
                input_right_operations = false;
            }
            //如果是上一次求值后直接输入数字
            if(line_edit_history.getText().contains("="))
            {
                line_edit_history.setText("");
                line_edit_show.setText(button_text);
                infixTokens.clear();
                infixTokens.add(button_text);
                history_input.clear();
                history_input.add(button_text);
            }
        }

        //点击小数点
        else if (button_text.equals("."))
        {
            checkPoint();
            if (!is_point_alive)//小数点不存在
            {
                line_edit_show.setText(line_edit_show.getText()+ button_text);
                is_point_alive = true;
            }
        }

        //清空
        else if (button_text.equals("C"))
        {
            line_edit_history.setText("");
            line_edit_show.setText("0");
            infixTokens.clear();
            history_input.clear();
            is_point_alive = false;
            special_operator = false;
            left_bracket = 0;
            right_bracket = 0;
        }

        //加减乘除
        else if(button_text.equals("+")||
                button_text.equals("-")||
                button_text.equals("×")||
                button_text.equals("÷"))
        {
            System.out.println(infixTokens);
            if(line_edit_history.getText().contains("="))
                infixTokens.clear();//要先清空

            //最后是右括号
            else if (!infixTokens.isEmpty() && infixTokens.getLast().equals(")"))
            {
                infixTokens.add(button_text);
                history_input.add(button_text);
            }

            //为空或者最后是运算符或者最后是左括号
            else if (infixTokens.isEmpty()||
                    infixTokens.getLast().equals("(") ||
                    infixTokens.getLast().equals("+") || infixTokens.getLast().equals("-")||
                    infixTokens.getLast().equals("×") || infixTokens.getLast().equals("÷"))
            {
                infixTokens.add(line_edit_show.getText());//存入已有的数字
                history_input.add(line_edit_show.getText());
                infixTokens.add(button_text);
                history_input.add(button_text);
            }
            //一元运算或特殊符号之后
            else if (special_operator)
            {
                infixTokens.add(button_text);
                history_input.add(button_text);
            }

            line_edit_history.setText(getAllToken(history_input));  //显示已输入内容
            input_right_operations = true;                          //输入右操作数状态
            special_operator = false;                               //重置状态
        }

        //等号
        else if (button_text.equals ("="))
        {
            if(infixTokens.isEmpty())
            {
                line_edit_history.setText(line_edit_show.getText()+"=");
                return;
            }

            //最后一个不是数字,也不是右括号,先将show中的数字存储
            if(!infixTokens.getLast().matches("-?\\d+(\\.\\d+)?") && !infixTokens.getLast().equals(")"))
            {
                infixTokens.add(line_edit_show.getText());
                history_input.add(line_edit_show.getText());
            }

            //自动添加右括号
            while(left_bracket!=right_bracket)
            {
                infixTokens.add(")");
                history_input.add(")");
                right_bracket++;
            }

            //显示运算结果
            ArrayList<String> temp = new ArrayList<>(infixTokens);//拷贝副本
            replaceMatchToASCII(temp);//替换数学乘除号为ASCII乘除号
            try
            {
                //显示运算结果
                line_edit_show.setText(Double.toString(Solver.infixToValue(temp)));
                //显示输入记录
                line_edit_history.setText(getAllToken(history_input)+"=");
                //修改第一个token为上次运算结果
                infixTokens.set(0,line_edit_show.getText());
                history_input.set(0,line_edit_show.getText());
            }
            catch (Exception ignored)
            {
                JOptionPane.showMessageDialog(this,
                        "未知错误", "错误", JOptionPane.ERROR_MESSAGE);
            }
        }

        //左括号
        else if (button_text.equals("("))
        {
            //为空或者最后是运算符
            if(infixTokens.isEmpty()||
                    infixTokens.getLast().equals("+") || infixTokens.getLast().equals("-")||
                    infixTokens.getLast().equals("×") || infixTokens.getLast().equals("÷"))
            {
                infixTokens.add(button_text);
                history_input.add(button_text);
            }

            else//最后一个是数字
            {
                infixTokens.add("×");//先添加乘号
                infixTokens.add(button_text);//再添加左括号
                history_input.add("×");
                history_input.add(button_text);
            }
            left_bracket++;//左括号数量加1

            line_edit_history.setText(getAllToken(history_input));
            line_edit_show.setText("0");

        }

        //右括号
        else if(button_text.equals(")")) {
            //没有左括号,输入无效,直接返回
            if (left_bracket == 0)
                return;
            //最后不是数字
            if (!infixTokens.getLast().matches("-?\\d+(\\.\\d+)?"))
            {
                infixTokens.add(line_edit_show.getText());//存储show中数字
                history_input.add(line_edit_show.getText());
            }
            //最后是数字
            infixTokens.add(button_text);//添加右括号
            history_input.add(button_text);
            line_edit_history.setText(getAllToken(history_input));//显示输入步骤
            right_bracket++;
        }

        else if(button_text.equals("sin"))
        {
            //计算结果存入中缀表达式
           infixTokens.add(Double.toString(Math.sin(Double.parseDouble(line_edit_show.getText()))));
           //历史步骤存入数学符号
           history_input.add("sin("+line_edit_show.getText()+")");
           //显示历史步骤
           line_edit_history.setText(getAllToken(history_input));

           special_operator = true;
        }
        else if(button_text.equals("cos"))
        {
            infixTokens.add(Double.toString(Math.cos(Double.parseDouble(line_edit_show.getText()))));
            history_input.add("cos("+line_edit_show.getText()+")");
            line_edit_history.setText(getAllToken(history_input));
            special_operator = true;
        }
        else if(button_text.equals("tan"))
        {
            if(Double.parseDouble(line_edit_show.getText()) % (Math.PI/2)==0.0)
            {
                JOptionPane.showMessageDialog(this, """
                        tan运算的被操作数不能为π/2的奇数倍""", "错误", JOptionPane.ERROR_MESSAGE);
                return;
            }
            infixTokens.add(Double.toString(Math.tan(Double.parseDouble(line_edit_show.getText()))));
            history_input.add("tan("+line_edit_show.getText()+")");
            line_edit_history.setText(getAllToken(history_input));
            special_operator = true;
        }
        else if (button_text.equals("x²"))
        {
            infixTokens.add(Double.toString(Math.pow(Double.parseDouble(line_edit_show.getText()),2)));
            history_input.add(line_edit_show.getText()+"²");
            line_edit_history.setText(getAllToken(history_input));
            special_operator = true;
        }
        else if (button_text.equals("√x"))
        {
            if(Double.parseDouble(line_edit_show.getText()) < 0)
            {
                JOptionPane.showMessageDialog(this, """
                        Do not currently support complex numbers.
                        The square root of a number with an even exponent cannot be a negative number within the real number domain.
                        暂不支持虚数！
                        实数范围内，偶次方根的被开方数不能为负数！""", "错误", JOptionPane.ERROR_MESSAGE);
                return;
            }
            infixTokens.add(Double.toString(Math.sqrt(Double.parseDouble(line_edit_show.getText()))));
            history_input.add("√"+line_edit_show.getText());
            line_edit_history.setText(getAllToken(history_input));
            special_operator = true;
        }
        else if (button_text.equals("log"))
        {
            if(Double.parseDouble(line_edit_show.getText()) <= 0)
            {
                JOptionPane.showMessageDialog(this, """
                        The operand of a logarithmic operation must be greater than zero!
                        对数运算的被操作数必须大于零！""", "错误", JOptionPane.ERROR_MESSAGE);
                return;
            }
            infixTokens.add(Double.toString(Math.log10(Double.parseDouble(line_edit_show.getText()))));
            history_input.add("log("+line_edit_show.getText()+")");
            line_edit_history.setText(getAllToken(history_input));
            special_operator = true;
        }
        else if (button_text.equals("ln"))
        {
            if(Double.parseDouble(line_edit_show.getText()) <= 0)
            {
                JOptionPane.showMessageDialog(this, """
                        The operand of a logarithmic operation must be greater than zero!
                        对数运算的被操作数必须大于零！""", "错误", JOptionPane.ERROR_MESSAGE);
                return;
            }
            infixTokens.add(Double.toString(Math.log(Double.parseDouble(line_edit_show.getText()))));
            history_input.add("ln("+line_edit_show.getText()+")");
            line_edit_history.setText(getAllToken(history_input));
            special_operator = true;
        }
        else if(button_text.equals("π"))
        {
            infixTokens.add(Double.toString(Math.PI));
            history_input.add("π");
            line_edit_history.setText(getAllToken(history_input));
            special_operator = true;
        }
        else if (button_text.equals("1/x"))
        {
            if(Double.parseDouble(line_edit_show.getText())==0.0)
            {
                JOptionPane.showMessageDialog(this,
                        "The denominator cannot be zero!\n分母不能为零！", "错误", JOptionPane.ERROR_MESSAGE);
                return;
            }
            infixTokens.add(Double.toString(1/Double.parseDouble(line_edit_show.getText())));
            history_input.add("(1/"+line_edit_show.getText()+")");
            line_edit_history.setText(getAllToken(history_input));
            special_operator = true;
        }
        else if (button_text.equals("-/+"))
        {
            if (Double.parseDouble(line_edit_show.getText())>0)
            {
                line_edit_show.setText("-"+line_edit_show.getText());
            }
            else if(Double.parseDouble(line_edit_show.getText())<0)
            {
                line_edit_show.setText(line_edit_show.getText().substring(1));
            }
        }
        else if (button_text.equals("e"))
        {
            infixTokens.add(Double.toString(Math.E));
            history_input.add("e");
            line_edit_history.setText(getAllToken(history_input));
            special_operator = true;
        }
        else if(button_text.equals("|x|"))
        {
            infixTokens.add(Double.toString(Math.abs(Double.parseDouble(line_edit_show.getText()))));
            history_input.add("|"+line_edit_show.getText()+"|");
            line_edit_history.setText(getAllToken(history_input));
            special_operator = true;
        }
        else if(button_text.equals("10^x"))
        {
            infixTokens.add(Double.toString(Math.pow(10,Double.parseDouble(line_edit_show.getText()))));
            history_input.add("10^"+line_edit_show.getText());
            line_edit_history.setText(getAllToken(history_input));
            special_operator = true;
        }
        else if(button_text.equals("e^x"))
        {
            infixTokens.add(Double.toString(Math.pow(Math.E,Double.parseDouble(line_edit_show.getText()))));
            history_input.add("e^"+line_edit_show.getText());
            line_edit_history.setText(getAllToken(history_input));
            special_operator = true;
        }
        else if (button_text.equals("³√x"))
        {
            infixTokens.add(Double.toString(Math.cbrt(Double.parseDouble(line_edit_show.getText()))));
            history_input.add("³√"+line_edit_show.getText());
            line_edit_history.setText(getAllToken(history_input));
            special_operator = true;
        }
        else if (button_text.equals("←"))
        {
            if (line_edit_show.getText().length() == 1)
                line_edit_show.setText("0");
            else
                line_edit_show.setText(line_edit_show.getText().substring(0, line_edit_show.getText().length() - 1));
        }
    }

    //显示界面,设置退出策略,阻塞等待窗口关闭
    public void exec()
    {
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);//设置关闭模式
        setVisible(true);//显示界面
    }

    //设置是否隐藏界面
    public void setIsHidden(boolean isHidden)
    {
        setVisible(!isHidden);
    }
}
