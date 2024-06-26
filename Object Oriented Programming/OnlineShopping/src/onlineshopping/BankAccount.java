/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package onlineshopping;

import java.text.DecimalFormat;

/**
 *
 * @author andre
 */
public class BankAccount implements Transaction{
    private static final DecimalFormat df = new DecimalFormat("0.00");
    
    private int accNumber;
    private double balance;
    

    BankAccount(){
        this(0,0);
    }
    BankAccount(int num,double bal){
        this.accNumber=num; 
        this.balance=bal;
        
    }
    public double getBalance() {
        return balance;
    }

    public int getAccNumber() {
        return accNumber;
    }
    public double deposit(double amount) {
        this.balance+=amount; 
        return this.balance;
    }

    public boolean withdraw(double amount) {
        boolean amountSufficient = true;
        
        if(amount>balance){
            amountSufficient = false;
        }else{
            this.balance-=amount;
        }
        return amountSufficient;
    }
    
    @Override
    public String toString() {
        return "Account number: " + accNumber + "\nBalance: RM " + df.format(balance);
    }
    

}
