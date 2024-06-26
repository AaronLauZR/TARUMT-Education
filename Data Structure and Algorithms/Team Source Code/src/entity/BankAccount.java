package entity;

import java.text.DecimalFormat;
import java.util.Scanner;

public class BankAccount {
    
    private static final DecimalFormat df = new DecimalFormat("0.00");
    
    private int accNumber;
    private double balance;
    private String password;
    
    BankAccount(){
    }

    public BankAccount(int accNumber, double balance, String password) {
        this.accNumber = accNumber;
        this.balance = balance;
        this.password = password;
    }
    
    public double getBalance() {
        return balance;
    }

    public int getAccNumber() {
        return accNumber;
    }

    public String getPassword() {
        return password;
    }

    public void setBalance(double balance) {
        this.balance = balance;
    }
      

    public double withdraw(double amount) {
    
    double currentBalance = balance;

    if(amount < balance){
        currentBalance -= amount;
    }    
    return currentBalance;
    }
        
    public boolean VerifyWithdrawal(double amount) {
        boolean amountSufficient = true;
        
        if(amount > balance){
            amountSufficient = false;
  
    }
        return amountSufficient;
    }
    

    @Override
    public String toString() {
        return "Account number: " + accNumber + "\nBalance: RM " + df.format(balance);
    }
    
    public void EnterBankDetails(){
        Scanner scan = new Scanner(System.in);
        System.out.println("\n----------- Insert Saving Bank Account -----------");
                System.out.print("Please insert the bank account number: ");
                while(!scan.hasNextInt()){
                    System.out.println("Your should enter number \n");
                    scan.nextLine();
                    System.out.print("Please insert the bank account number: ");
                }
                int bank = scan.nextInt();
                
                System.out.print("Please insert password: ");
                String pass = scan.next();
    }
    
    
}
