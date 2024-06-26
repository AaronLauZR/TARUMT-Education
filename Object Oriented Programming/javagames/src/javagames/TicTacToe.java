/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package javagames;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

/**
 *
 * @author andre
 */
public class TicTacToe extends JFrame implements ActionListener{
  TicTacToe t;
  Random rdm=new Random();
  JPanel panel1=new JPanel();
  JPanel panel2=new JPanel();
  JLabel label=new JLabel();
  JButton[] btn=new JButton[9];
  JButton Reset=new JButton("Reset");
  JButton Exit=new JButton("Exit");
  boolean player_turn=true;
  boolean pwin =false;

  TicTacToe(){
    setTitle("TicTacToe");
    setSize(600,600);
    getContentPane().setBackground(Color.black);
    setLayout(new BorderLayout());
    // setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
    setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
    addWindowListener(new WindowAdapter(){
      public void windowClosing(WindowEvent e){
        JFrame frame = (JFrame)e.getSource();
        exitPanel();
      }
    });
    setVisible(true);
    label.setBackground(Color.GRAY);
    label.setForeground(Color.WHITE);
    label.setFont(new Font("Arial",Font.ITALIC,60));
    label.setHorizontalAlignment(JLabel.CENTER);
    label.setText("Tic-Tac-Toe");
    label.setOpaque(true);
    panel1.setLayout(new BorderLayout());
    panel1.setBounds(0,0,800,100);
    panel1.add(label);
    add(panel1,BorderLayout.NORTH);
    panel2.setLayout(new GridLayout(3,3));
    for(int i=0;i<btn.length;i++){
      btn[i]=new JButton();
      panel2.add(btn[i]);
      btn[i].setFont(new Font("Arial",Font.BOLD,120));
      btn[i].setFocusable(false);
      btn[i].addActionListener(this);
    }
    add(panel2);
  }
  int chance=9;
  @Override
  public void actionPerformed(ActionEvent e) {
    wincondition();
    for(int i=0;i<9;i++){
      if(e.getSource()==btn[i]){
        if(player_turn==true){
          if(btn[i].getText()==""){
            btn[i].setForeground(Color.red);
            btn[i].setText("X");
            wincondition();
            player_turn=false;
            // label.setText("Player 2 turn");
            chance-=1;
          }
        }
      }
    }
    if(player_turn==false){
      int com=rdm.nextInt(9);
      try {
        Robot r=new Robot();
        int button=InputEvent.BUTTON1_DOWN_MASK;
        r.mousePress(button);
        r.mouseRelease(button);
        if(btn[com].getText()==""){
          btn[com].setForeground(Color.blue);
          btn[com].setText("O");
          player_turn=true;
          // label.setText("Player 1 turn");
          chance-=1;
        }
      } catch (Exception eq) {
        System.out.println(eq);
      }
    }
    
    //Draw condition
    if(chance== 0 && !pwin){
      label.setText("Draw");
      for(int a=0;a<9;a++){
        btn[a].setEnabled(false);
      }
      resetPanel();
    }
  }
  public void wincondition() {
    //_ _ _  0 1 2
    //_ _ _  3 4 5
    //_ _ _  6 7 8
    int [][] win={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int a1=0;
    int b1=0;
    int c1=0;
    for(int row=0;row<win.length;row++){
        a1=win[row][0];
        b1=win[row][1];
        c1=win[row][2];
      
      if ((btn[a1].getText()=="X")&&(btn[b1].getText()=="X")&&(btn[c1].getText()=="X")){
        for(int i=0;i<9;i++){
          btn[i].setEnabled(false);
        }
        win(a1,b1,c1,1);
        return;
      }
      else if ((btn[a1].getText()=="O")&&(btn[b1].getText()=="O")&&(btn[c1].getText()=="O")){
          win(a1,b1,c1,2);
      }
    }
    
  }
  String str;
  public void win(int num1,int num2,int num3,int num4){
    for(int i=0;i<9;i++){
      btn[i].setEnabled(false);
    }
    btn[num1].setBackground(Color.GREEN);
    btn[num2].setBackground(Color.GREEN);
    btn[num3].setBackground(Color.GREEN);
    if(num4==1){
      label.setText("Player 1 Win");
      pwin=true;
      resetPanel();
      
    }else if( num4 ==2){
      label.setText("Player 2 Win");
      pwin=true;
      resetPanel();
    }
  }
  public void resetPanel(){
    String[] options = {"Reset","Exit"};
      int x = JOptionPane.showOptionDialog(null, "Do u want play agian?","Information",JOptionPane.DEFAULT_OPTION, JOptionPane.INFORMATION_MESSAGE, null, options, null);
      if(x==0){
        reset();
      }
      if(x==1){
        this.dispose();
      }
  }
  public void exitPanel() {
    String[] options = {"Yes","No"};
      int x = JOptionPane.showOptionDialog(null, "Do u want exit?","Information",JOptionPane.DEFAULT_OPTION, JOptionPane.INFORMATION_MESSAGE, null, options, null);
      if(x==0){
        this.dispose();
      }
  }
  public void reset() {    
    this.dispose();
    new TicTacToe();
  }
}


