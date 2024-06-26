package entity;

import adt.*;
import catering_system.Order;
import entity.*;
import java.text.DecimalFormat;
import java.util.Scanner;

public class Installment {

    Scanner input = new Scanner(System.in);
    private static final DecimalFormat df = new DecimalFormat("0.00");
    
    private static double monthlyPayment;
    private static int installmentMonth;

    public Installment() {
    }
    
    public Installment(double monthlyPayment) {
        Installment.monthlyPayment = monthlyPayment;
    }
    
    public static double getMonthlyPayment() {
        return monthlyPayment;
    }

    public void setMonthlyPayment(double monthlyPayment) {
        Installment.monthlyPayment = monthlyPayment;
    }

    public static int getInstallmentMonth() {
        return installmentMonth;
    }

    public static void setInstallmentMonth(int installmentMonth) {
        Installment.installmentMonth = installmentMonth;
    }

    public static Installment MonthlyInstallment(Order order, int installmentMonth){
        
        Installment installment = new Installment();
        
        Installment.monthlyPayment = order.totalPrice()/ installmentMonth;
        installment.setMonthlyPayment(Installment.monthlyPayment);
        
        return installment;
    }
    
    @Override
    public String toString() {
        return String.format("%-4s ", df.format(monthlyPayment)) ;

    }        
}
