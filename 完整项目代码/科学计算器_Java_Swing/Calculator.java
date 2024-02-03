import counter.ScientificCalculator;
import counter.StandardCalculator;

import javax.swing.JButton;
import javax.swing.UnsupportedLookAndFeelException;

import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Calculator implements ActionListener
{
    StandardCalculator standard_calculator = new StandardCalculator();//标准计算器
    ScientificCalculator scientific_calculator = new ScientificCalculator();//科学计算器

    private final JButton toggle_button_scientific = new JButton();//切换科学计算
    private final JButton toggle_button_standard = new JButton();//切换标准计算器

    //窗口坐标
    private int x;
    private int y;
    private final int w = standard_calculator.getWidth();
    private final int h = standard_calculator.getHeight();

    Calculator() throws
            UnsupportedLookAndFeelException,
            ClassNotFoundException,
            InstantiationException,
            IllegalAccessException {
        inItUi();
    }

    private void inItUi() {
        toggle_button_scientific.setBounds(13, 0, 54, 30);
        toggle_button_scientific.setFocusPainted(false);
        toggle_button_scientific.setFocusable(false);
        toggle_button_scientific.setFont(new Font("微软雅黑", Font.PLAIN, 11));
        toggle_button_scientific.setText("科学");
        toggle_button_scientific.addActionListener(this);
        standard_calculator.getContentPane().add(toggle_button_scientific);

        toggle_button_standard.setBounds(13, 0, 54, 30);
        toggle_button_standard.setFocusPainted(false);
        toggle_button_standard.setFocusable(false);
        toggle_button_standard.setFont(new Font("微软雅黑", Font.PLAIN, 11));
        toggle_button_standard.setText("标准");
        toggle_button_standard.addActionListener(this);
        scientific_calculator.getContentPane().add(toggle_button_standard);
    }

    private void recordCoordinates(int x_, int y_) {
        x = x_;
        y = y_;
    }

    public void exec(){
        standard_calculator.exec();
        scientific_calculator.exec();
        recordCoordinates(standard_calculator.getX(), standard_calculator.getY());
        scientific_calculator.setIsHidden(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String button_text = ((JButton) e.getSource()).getText();
        switch (button_text) {
            case "科学":
                recordCoordinates(standard_calculator.getX(), standard_calculator.getY());
                standard_calculator.setIsHidden(true);
                scientific_calculator.setBounds(x, y, w, h);
                scientific_calculator.setIsHidden(false);
                break;
            case "标准":
                recordCoordinates(scientific_calculator.getX(), scientific_calculator.getY());
                scientific_calculator.setIsHidden(true);
                standard_calculator.setBounds(x, y, w, h);
                standard_calculator.setIsHidden(false);
                break;
        }
    }
}
