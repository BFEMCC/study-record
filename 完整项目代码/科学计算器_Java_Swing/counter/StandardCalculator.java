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

public class StandardCalculator extends JFrame implements ActionListener
{
    private final JButton[] button_array = new JButton[24];             //按钮
    private final JTextField line_edit_history = new JTextField("");    //历史记录单行文本框
    private final JTextField line_edit_show = new JTextField("0");      //显示过程和结果单行文本框

    private final String[] operand = new String[2];                     //存储操作数
    private final String[] operator = new String[2];                    //存储操作符
    private final String[] special_operations_history = new String[2];  //存储非四则运算时的操作符和操作数,便于显示历史记录

    private String button_text;                                         //按钮上的文字
    private boolean is_point_alive = false;                             //是否存在小数点
    private boolean is_delete_left_operand = false;                     //显示输入的右操作数前要清除左操作数，只能清除一次的，使用bool控制次数
    private boolean is_delete_last_result = false;                      //得出结果后直接点击数字，清除上一次的结果，只能清除一次，使用bool控制次数
    private boolean is_special_operation = false;                       //非四则运算时退位无效，用bool记录状态
    private double result;                                              //存储运算结果

    public StandardCalculator() throws UnsupportedLookAndFeelException, ClassNotFoundException, InstantiationException, IllegalAccessException
    {
        inItUi();       //初始化UI
        inItMember();   //初始化成员变量
    }

    //初始化Ui控件
    private void inItUi() throws UnsupportedLookAndFeelException, ClassNotFoundException, InstantiationException, IllegalAccessException
    {
        UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());    //使用当前系统UI样式
        setSize(550, 690);
        setTitle("标准计算器");
        setAlwaysOnTop(true);                                                   //窗口置顶
        setLocationRelativeTo(null);                                            //初始时窗口居中
        getContentPane().setBackground(new Color(239, 244, 249));       //设置背景颜色
        setLayout(null);                                                        //取消默认布局
        setResizable(false);                                                    //禁止调整大小

        int width_interval = 130;
        int height_interval = 75;
        int x = 10;
        int y = 200;
        int width = 125;
        int height = 70;

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                button_array[i * 4 + j] = new JButton();
                button_array[i * 4 + j].setBounds(x + width_interval * (j % 4), y + (i * height_interval), width, height);  //设置按钮坐标
                button_array[i * 4 + j].setFocusPainted(false);         //去除焦点时的文字边框
                button_array[i * 4 + j].setFocusable(false);            //默认无法获取焦点
                button_array[i * 4 + j].setFont(new Font("微软雅黑",Font.PLAIN,23));    //设置按钮字体，默认样式，字号
                button_array[i * 4 + j].addActionListener(this);      //添加鼠标事件
                getContentPane().add(button_array[i * 4 + j]);          //添加到内容布局中
            }
        }

        // 设置文本框的位置和大小
        line_edit_show.setBounds(13,75,510, 110);
        line_edit_history.setBounds(13 , 35, 510, 30);
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
        button_array[0].setText("ln(x)");       //ln x
        button_array[1].setText("CE");          //ce
        button_array[2].setText("C");           //c
        button_array[3].setText("←");           //←

        button_array[4].setText("1/x");         //1/x
        button_array[5].setText("x²");          //x²
        button_array[6].setText("√x");          //√x
        button_array[7].setText("÷");           //÷

        button_array[8].setText("7");           //7
        button_array[9].setText("8");           //8
        button_array[10].setText("9");          //9
        button_array[11].setText("×");          //×

        button_array[12].setText("4");          //4
        button_array[13].setText("5");          //5
        button_array[14].setText("6");          //6
        button_array[15].setText("-");          //-

        button_array[16].setText("1");          //1
        button_array[17].setText("2");          //2
        button_array[18].setText("3");          //3
        button_array[19].setText("+");          //+

        button_array[20].setText("+/-");        //+/-
        button_array[21].setText("0");          //0
        button_array[22].setText(".");          //.
        button_array[23].setText("=");          //=

    }

    //初始化成员变量
    private void inItMember()
    {
        //初始化成员变量
        operand[0] = "0";     //show初始默认0
        operand[1] = "";
        operator[0] = "";
        operator[1] = "";
        special_operations_history[0] = operand[0];
        special_operations_history[1] = operand[1];
        is_point_alive = false;
        is_delete_left_operand = false;
        is_delete_last_result = false;
        is_special_operation = false;
    }

    //清空,全部恢复初始状态
    private void clearC()
    {
        line_edit_show.setText("0");
        line_edit_history.setText("");
        inItMember();//清空，全部回归初始状态
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

    //显示结果
    private void showResult()
    {
        String R = Double.toString(result);// 将结果转换为字符串
        if (!R.isEmpty() && R.charAt(R.length() - 1) == '.') // 如果结果不为空且最后一个字符是小数点，移除尾部的小数点
            R = R.substring(0, R.length() - 1);
        line_edit_show.setText(R);
    }

    //显示历史记录
    private void showHistory(int choose)
    {
        //根据choose值显示不同的历史记录
        if (!operand[0].isEmpty() && operand[0].charAt(operand[0].length() - 1) == '.')
        {
            operand[0] = operand[0].substring(0, operand[0].length() - 1);//去除末尾小数点
            special_operations_history[0] = operand[0];
        }
        if (choose == 1)
            line_edit_history.setText(special_operations_history[0] + operator[0]);
        else if (choose == 2)
            line_edit_history.setText(special_operations_history[0] + operator[0] + special_operations_history[1]+ operator[1]);
    }

    //进行四则运算存并储结果
    private void performFourOperations()
    {
        result = switch (operator[0])
        {
            case "+" ->
                    Double.parseDouble(operand[0]) + Double.parseDouble(operand[1]);
            case "-" ->
                    Double.parseDouble(operand[0]) - Double.parseDouble(operand[1]);
            case "×" ->
                    Double.parseDouble(operand[0]) * Double.parseDouble(operand[1]);
            case "÷" ->
                    Double.parseDouble(operand[0]) / Double.parseDouble(operand[1]);
            default -> result;
        };
        showResult();
    }

    //处理运算类型、操作符和操作数
    private void processingArithmeticTypes(String operator_)
    {
        //进行非四则运算时
        is_special_operation = false;

        if (!operator[0].isEmpty() && !operand[1].isEmpty() && operator[1].equals("="))
        {
            operator[0] = operator_;
            operand[0] = line_edit_show.getText();
            special_operations_history[0] = operand[0];
            showHistory(1);
            operand[1] = line_edit_show.getText();
            special_operations_history[1] = operand[1];
            operator[1] = "";
            is_delete_left_operand = false;
            return;
        }

        //进行四则运算时
        operator[1] = "";       //先将第二个操作符的等号清除置空
        is_point_alive = false;     //点击后，下次输入右操作数，pointAlive复位

        //第一个操作符为空，说明刚输入完左操作数，直接存储操作符
        if (operator[0].isEmpty())
        {
            operator[0] = operator_;
            operand[1] = operand[0];
            special_operations_history[1] = operand[1];
        }

        //第一个操作符不为空，但为等号
        else if (operator[0].equals("="))
            operator[0] = operator_;

        //第一个操作符不为空，且右操作数为空，这时候点击操作符表示要更改运算方式
        else if (operand[1].isEmpty())
            operator[0] = operator_;

        //第一个操作符不为空，且右操作数不为空，直接求出结果，后续如果不输入右操作数只能求一次
        else
        {
            performFourOperations();

            //根据按下的操作符按钮更改对应的操作符
            operand[0] = Double.toString(result);     //左操作数变为result
            operand[1] = "";
            special_operations_history[0] = operand[0];
            special_operations_history[1] = operand[1];
            is_delete_left_operand = false;
            switch (button_text)
            {
                case "+" -> operator[0] = "+";
                case "-" -> operator[0] = "-";
                case "×" -> operator[0] = "×";
                case "÷" -> operator[0] = "÷";
            }
            operand[1] = "";
            special_operations_history[1] = operand[1];
        }
        showHistory(1);     //每次点击操作符，显示历史记录
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        button_text = ((JButton) e.getSource()).getText();

        //点击数字
        if(button_text.matches("[0-9]"))
        {
            if(line_edit_show.getText().equals("0")  && !button_text.equals(".")) //清除默认的0
                line_edit_show.setText("");
            if (operator[0].isEmpty() || operator[1].equals("=")) //如果第一个操作符为空，或者上一次运算得出结果后直接点击数字,说明是左操作数
            {
                if (operator[1].equals("=") && !is_delete_last_result)//得出结果后直接点击数字要清除上一次的结果，只能清除一次
                {
                    line_edit_show.setText("");
                    line_edit_history.setText("");
                    is_delete_last_result = true;
                }
                line_edit_show.setText(line_edit_show.getText()+ button_text);
                result = Double.parseDouble(line_edit_show.getText());
                operand[0] = line_edit_show.getText();                //左操作数更新
                special_operations_history[0] = operand[0];
            }
            else//右操作数
            {
                if (!is_delete_left_operand)//显示输入的右操作数前要清除左操作数，只能清除一次
                {
                    line_edit_show.setText("");
                    is_delete_left_operand = true;
                }
                line_edit_show.setText(line_edit_show.getText()+ button_text);
                operand[1] = line_edit_show.getText();            //右操作数更新
                special_operations_history[1] = operand[1];
            }
        }

        //点击小数点
        else if (button_text.equals("."))//小数点不主动存储
        {
            checkPoint();
            if (!is_point_alive)//小数点不存在
            {
                line_edit_show.setText(line_edit_show.getText()+ button_text);
                is_point_alive = true;
            }
        }

        //点击C清空
        else if (button_text.equals("C"))
            clearC();//清空全部内容，全部恢复默认

        //退位
        else if (button_text.equals("←"))//退位，清除一个字符
        {
            //第一个操作符为空，说明是在退位左操作数
            if (operator[0].isEmpty() && !is_special_operation)
            {
                if (line_edit_show.getText().length() == 1)//如果只剩1个字符并且按下了退位，相当于清空
                    clearC();
                else//删除光标前的一个字符
                {
                    line_edit_show.setText(line_edit_show.getText().substring(0, line_edit_show.getText().length() - 1));//直接删掉最后一个字符，然后重新设置文本内容
                    operand[0] = line_edit_show.getText();//重新存储左操作数
                    special_operations_history[0] = operand[0];
                }
            }

            //当第一个操作符不为空，右操作数不为空，且第二个操作符为空，说明是在退位右操作数
            else if (!operator[0].isEmpty() && !operand[1].isEmpty() && operator[1].isEmpty() && !is_special_operation)
            {
                //重新存右操作数
                if (line_edit_show.getText().length() == 1)//如果只剩1个字符并且按下了退位
                    line_edit_show.setText("0");
                else//删除光标前的一个字符
                    line_edit_show.setText(line_edit_show.getText().substring(0, line_edit_show.getText().length() - 1));
                operand[1] = line_edit_show.getText();//存储右操作数为0
                special_operations_history[1] = operand[1];
            }

            //当第二个操作数为等号时，只清除历史记录
            if (operator[1].equals("="))
                line_edit_history.setText("");

            //第一个操作符为等号时，退位无效

            //当第一个操作符不为空，且右操作数为空时，退位无效

            checkPoint();//每退位一次，检测是否还有小数点
        }

        //等号
        else if (button_text.equals ("="))
        {
            is_delete_last_result = false;

            //1、第一个操作符为空，说明刚输入完左操作数，按等号直接显示
            if (operator[0].isEmpty())
            {
                operator[0] = "=";
                result = Double.parseDouble(operand[0]);
                operand[1] = operand[0];
                special_operations_history[1] = operand[1];
                showResult();
                showHistory(1);
            }

            //2、第二操作符不是等号的情况下，按等号求值，并且第一个操作符不是等号
            else if (!operator[0].equals("=") && !operator[1].equals("="))
            {
                if(operator[0].equals("÷") && Double.parseDouble(operand[1]) == 0.0)
                    JOptionPane.showMessageDialog(this, "The dividend cannot be zero!\n被除数不能为零！", "错误", JOptionPane.ERROR_MESSAGE);
                else
                {
                    operator[1] = "=";
                    operand[1] = line_edit_show.getText();
                    showHistory(2);
                    performFourOperations();
                    special_operations_history[1] = operand[1];
                }
            }

            //3、持续按等号，右操作数不变
            else if (operator[1].equals("="))
            {
                operand[0] = Double.toString(result);
                special_operations_history[0] = operand[0];
                showHistory(2);
                performFourOperations();
            }
        }

        //CE
        else if (button_text.equals("CE"))
        {
            if (operator[0].isEmpty())//在输入左操作数，等效于按C
                clearC();
            else if (operator[1].isEmpty())//在输入右操作数
            {
                //左操作数保留，第一个操作符保留，右操作数归零，右操作数历史记录更新
                operand[1] = "0";
                special_operations_history[1] = operand[1];
                line_edit_show.setText("0");
            }
            else if (operator[1].equals("="))//得出结果后
            {
                //左操作数归零，右操作数和第一个操作符不变，左操作数历史记录更新，result值归零
                operand[0] = "0";
                special_operations_history[0] = operand[0];
                result = 0.0;
                line_edit_show.setText("0");
                line_edit_history.setText("");
            }
        }

        /*—————————————运算部分—————————————*/
        /*左操作数永远不会为空，默认是0，右操作数默认为空。输入左操作数再点击运算符后，右操作数默认等于左操作数*/

        //四则运算
        else if(button_text.equals("+")||
                button_text.equals("-")||
                button_text.equals("×")||
                button_text.equals("÷"))
            processingArithmeticTypes(button_text);

        //倒数
        else if (button_text.equals("1/x"))
        {
            if (operator[0].isEmpty() && Double.parseDouble(operand[0]) != 0.0)//左操作数//分母不为0
            {
                is_special_operation = true;
                special_operations_history[0] = "1/(" + special_operations_history[0] + ")";
                line_edit_history.setText(special_operations_history[0]);
                result = 1 / Double.parseDouble(operand[0]);
                showResult();
                operand[0] = Double.toString(result);
            }
            else if (!operator[0].isEmpty()&& !operator[0].equals("=") && !operator[1].equals("=") && Double.parseDouble(operand[1]) != 0.0)//右操作数//分母不为0
            {
                is_special_operation = true;
                special_operations_history[1] = "1/(" + operand[1]+ ")";
                operand[1] =Double.toString(1 / Double.parseDouble(operand[1]));
                line_edit_history.setText(special_operations_history[0] + operator[0] + special_operations_history[1]);
                line_edit_show.setText(operand[1]);
            }
            else if (!operator[0].isEmpty() && (operator[1].equals("=") || operator[0].equals("=")) && result != 0.0)//对上次的结果求值//分母不为0
            {
                is_special_operation = true;
                special_operations_history[0] = "1/(" + line_edit_show.getText() + ")";
                operand[0]= Double.toString(1 / result);
                result = Double.parseDouble(operand[0]);
                line_edit_history.setText(special_operations_history[0]);
                showResult();
            }
            else//分母为零，提示错误
                JOptionPane.showMessageDialog(this, "The denominator cannot be zero!\n分母不能为零！", "错误", JOptionPane.ERROR_MESSAGE);
        }

        //平方
        else if (button_text.equals("x²"))
        {
            if (operator[0].isEmpty())//左操作数
            {
                is_special_operation = true;
                special_operations_history[0] = "(" + special_operations_history[0] + ")²";
                line_edit_history.setText(special_operations_history[0]);
                result = Math.pow(Double.parseDouble(operand[0]), 2);
                showResult();
                operand[0] = Double.toString(result);
            }
            else if (!operator[0].equals("=") && !operator[1].equals("="))//右操作数
            {
                is_special_operation = true;
                special_operations_history[1] = "(" + operand[1]+ ")²";
                operand[1] = Double.toString(Math.pow(Double.parseDouble(operand[1]), 2));
                line_edit_history.setText(special_operations_history[0] + operator[0] + special_operations_history[1]);
                line_edit_show.setText(operand[1]);
            }
            else if (result != 0.0)//对上次的结果求值
            {
                is_special_operation = true;
                special_operations_history[0] = "(" + line_edit_show.getText() + ")²";
                operand[0] = Double.toString(Math.pow(result, 2));
                result =Double.parseDouble(operand[0]);
                line_edit_history.setText(special_operations_history[0]);
                showResult();
            }
        }

        //开二次方
        else if (button_text.equals("√x"))
        {
            if (operator[0].isEmpty() && Double.parseDouble(operand[0]) >= 0.0)//左操作数
            {
                is_special_operation = true;
                special_operations_history[0] = "√(" + special_operations_history[0] + ")";
                line_edit_history.setText(special_operations_history[0]);
                result = Math.sqrt(Double.parseDouble(operand[0]));
                showResult();
                operand[0] =Double.toString(result);
            }
            else if (!operator[0].isEmpty() && !operator[0].equals("=") && !operator[1].equals("=") &&Double.parseDouble(operand[1]) >= 0)//右操作数
            {
                is_special_operation = true;
                special_operations_history[1] = "√(" + operand[1] + ")";
                operand[1] = Double.toString(Math.sqrt(Double.parseDouble(operand[1])));
                line_edit_history.setText(special_operations_history[0] + operator[0] + special_operations_history[1]);
                line_edit_show.setText(operand[1]);
            }
            else if (!operator[0].isEmpty() && (operator[1].equals("=") || operator[0].equals("=")) && result >= 0.0)//对上次的结果求值
            {
                is_special_operation = true;
                special_operations_history[0] = "√(" + line_edit_show.getText() + ")";
                operand[0] = Double.toString(Math.sqrt(result));
                result =Double.parseDouble(operand[0]);
                line_edit_history.setText(special_operations_history[0]);
                showResult();
            }
            else
                JOptionPane.showMessageDialog(this, """
                        Standard standardCalculator does not currently support complex numbers.
                        The square root of a number with an even exponent cannot be a negative number within the real number domain.
                        标准计算器，暂不支持虚数！
                        实数范围内，偶次方根的被开方数不能为负数！""", "错误", JOptionPane.ERROR_MESSAGE);
        }

        //自然对数
        else if (button_text.equals("ln(x)"))//被操作数大于0
        {
            if (operator[0].isEmpty() && Double.parseDouble(operand[0]) > 0.0)//左操作数
            {
                is_special_operation = true;
                special_operations_history[0] = "ln(" + special_operations_history[0] + ")";
                line_edit_history.setText(special_operations_history[0]);
                result = Math.log(Double.parseDouble(operand[0]));
                showResult();
            }
            else if (!operator[0].isEmpty()&& !operator[0].equals("=") && !operator[1].equals("=")  && Double.parseDouble(operand[1]) > 0.0)//右操作数
            {
                is_special_operation = true;
                special_operations_history[1] = "ln(" + operand[1] + ")";
                operand[1] = Double.toString(Math.log(Double.parseDouble(operand[1])));
                line_edit_history.setText(special_operations_history[0] + operator[0] + special_operations_history[1]);
                line_edit_show.setText(operand[1]);
            }
            else if (!operator[0].isEmpty() && (operator[1].equals("=") || operator[0].equals("="))  && result > 0.0)//对上一次的结果求值
            {
                is_special_operation = true;
                special_operations_history[0] = "ln(" + line_edit_show.getText()+ ")";
                operand[0] = Double.toString(Math.log(result));
                result = Double.parseDouble(operand[0]);
                line_edit_history.setText(special_operations_history[0]);
                showResult();
            }
            else
                JOptionPane.showMessageDialog(this, """
                        The operand of a logarithmic operation must be greater than zero!
                        对数运算的被操作数必须大于零！""", "错误", JOptionPane.ERROR_MESSAGE);
        }

        //正负取反
        else if (button_text.equals("+/-"))//对0取反无效//大于0加上负号//小于0删掉负号
        {
            if (operator[0].isEmpty())//左操作数
            {
                if (Double.parseDouble(operand[0]) > 0.0)
                    operand[0] = "-" + operand[0];
                else if (Double.parseDouble(operand[0]) < 0.0)
                    operand[0] = operand[0].substring(1);//效果：删去第一个字符
                special_operations_history[0] = operand[0];
                line_edit_show.setText(special_operations_history[0]);
            }
            else if (!operator[0].equals("=") && !operator[1].equals("="))//右操作数
            {
                if (Double.parseDouble(operand[1]) > 0.0)
                    operand[1] = "-" + operand[1];
                else if (Double.parseDouble(operand[1]) < 0.0)
                    operand[1] = operand[1].substring(1);
                special_operations_history[1] = operand[1];
                line_edit_show.setText(special_operations_history[1]);
            }
            else
            {
                //结果值是double，直接取反
                operand[0] =Double.toString(-result);
                special_operations_history[0] = operand[0];
                result = Double.parseDouble(operand[0]);
                line_edit_history.setText(special_operations_history[0]);
                showResult();
            }
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
