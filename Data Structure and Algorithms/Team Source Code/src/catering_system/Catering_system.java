/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package catering_system;

import java.util.Scanner;
import adt.*;
import entity.*;
import entity.FoodBeverageMenu;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Stack;

/**
 *
 * @author andre
 */
public class Catering_system {
    
    private static final DecimalFormat df = new DecimalFormat("0.00");
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Scanner input = new Scanner(System.in);
        String reorder = "";
        
        BankAccount[] bankacc = {
                new BankAccount(456123,4562,"P456123"),
                new BankAccount(123456,5000,"P123456"),
                new BankAccount(789456,50,"P789456"),
                new BankAccount(456789,456,"P456789")
        };
        
        do {                     
            //-------------------------------------------------------------------------------------------
            System.out.println("\n****************************************************");
            System.out.println("                     F & B Module                      ");
            System.out.println("****************************************************\n");

            FoodBeverageMain fbMain = new FoodBeverageMain();
            FoodBeverageMenu choosenItem = new FoodBeverageMenu();
            StackLibrary orderStack = new StackLibrary(100);
            int Continue = 0, choice = 0;
            String displayreverseStack = "";

            fbMain.displayTitle();

            do {
                do {
                    choice = fbMain.SelectMenu();

                    if (choice == 1) {
                        choosenItem = fbMain.orderFood();
                    }
                    else if (choice == 2) {
                        choosenItem = fbMain.orderBeverage();
                    }
                    else if (choice == 3) {
                        if (orderStack.emptyStack()) {
                            System.out.println("\nPlease order anything first before viewing your cart.");
                        }
                        else {
                            System.out.println("\nYour current F&B cart: ");
                            fbMain.displayOrder();
                            orderStack.viewreverseStack(orderStack);
                            System.out.println("=======================================================================================");
                        }
                    }
                    else if (choice == 4) {
                        if (orderStack.emptyStack()) {
                            System.out.println("\nThe cart is already empty.");
                        }
                        else {
                            orderStack.clearStack(orderStack);
                            System.out.println("All order has been successful clear.");
                        }
                    }
                    else if (choice == 5){
                        System.out.println("\nThank you! See you next time!");
                        System.exit(0); 
                    }
                } while (choice == 3 || choice == 4);


                orderStack.insert(choosenItem);

                int confirm = fbMain.confirmOrder(choosenItem);

                if (confirm == 1) {
                    System.out.println("Order confirm."); 
                }
                else if (confirm == 2) {
                    orderStack.undo();
                    System.out.println("Order has been cancel.");
                }

                Continue = fbMain.continueOrder();

            } while (Continue == 1);

            //Output
            System.out.println("\nYour selected Food & Beverage: ");
            fbMain.displayOrder();
            orderStack.viewreverseStack(orderStack);
            System.out.println("=======================================================================================");


            //-------------------------------------------------------------------------------------------
            System.out.println("\n****************************************************");
            System.out.println("                   Facility Module                      ");
            System.out.println("****************************************************\n");

            FacilityMain fclType = new FacilityMain();
            FacilityMenu selectFCL = new FacilityMenu();
            //String key = " ";
            //int value = 0;
            char ans = 'Y';
            char redo = 'N';
            do{
                fclType.FCLmap();
                ans = fclType.ContinueConfirm();
                System.out.println("");
            }while(ans == 'Y');

            System.out.println("\nSelected Facility: ");
            fclType.displayOrder();

            fclType.FCLStackIn(); //Map store into Stack



            //-------------------------------------------------------------------------------------------
            System.out.println("\n****************************************************");
            System.out.println("                     Order Module                     ");
            System.out.println("****************************************************");

            int optionMenu = 0;
            int optionCustomizeItem = 0;
            boolean proceedOrder = false; 
            Order order = new Order();

            //Stack store into ArrayList
            order.stackFBStoreIntoArrayList(orderStack); //Store F & B Stack into Arraylist
            order.stackFacilityStoreIntoArrayList(fclType.stack); //Store F & B Stack into Arraylist (ERROR)

            do {

                optionMenu = order.optionMenu();

                switch(optionMenu) {
                    case 1: 
                        order.displayFBCart();
                        break;
                    case 2: 
                        order.displayFacilityCart();
                        break;
                    case 3: //Customise F & B
                        order.printCustomizeFBMenu();
                        optionCustomizeItem = order.optionCustomizeItem();

                        if (optionCustomizeItem == 1) {
                            //Edit Food & Beverage
                            order.editFood_BeverageOrder();
                        }
                        else if (optionCustomizeItem == 2) {
                            //Delete Food & Beverage
                            order.deleteFood_BeverageOrder();
                        }
                        break;
                    case 4: //Customise Facility
                        order.printCustomizeFacilityMenu();
                        optionCustomizeItem = order.optionCustomizeItem();

                        if (optionCustomizeItem == 1) {
                            //Edit Facility
                            order.editFacilityOrder();
                        }
                        else if (optionCustomizeItem == 2) {
                            //Delete Facility
                            order.deleteFacilityOrder();
                        }
                        break;
                    case 5: //Confirm the Order
                        proceedOrder = true; 
                        System.out.println("The total price is RM " + df.format(order.totalPrice()));
                        System.out.println("\nProceed to Payment.");        
                        break;
                    case 6: //Terminate the program
                        System.out.println("\nExit the program");
                        System.exit(0);
                        break;
                    default:
                        System.out.println("The option is invalid.");
                }

            } while (proceedOrder != true);


            //-------------------------------------------------------------------------------------------
            System.out.println("\n****************************************************");
            System.out.println("                    Payment Module                       ");
            System.out.println("****************************************************\n");

                //Bank Account Verification
                boolean accountValid = false;
                boolean amountSufficient = false;
                //boolean VerifyWithdrawal = false;

            if(proceedOrder){

                System.out.println("Invoice need to write how many person name? ");
                while(!input.hasNextInt()){
                        System.out.println("Your should enter number. \n");
                        input.nextLine();
                        System.out.println("Invoice need to write how many person name? ");
                }
                int custNo = input.nextInt();

                CircularArrayQueue <Customer> currentCust = new CircularArrayQueue<>();
                CircularArrayQueue <Delivery> delivery = new CircularArrayQueue<>();
                CircularArrayQueue <Installment> installment = new CircularArrayQueue<>();


                System.out.println("\n----------- Record Customer Details-----------");

                for (int i = 0; i < custNo; i++) {
                    //Store customer details in a queue
                    currentCust.enterQueue(Customer.EnterDetails()); 
                    //System.out.println("\n");
               }
                System.out.println("\nThe customer details is recorded.");
                System.out.println("------------------------------------------------");

                System.out.println("\n----------- Record Delivery Details-----------\n");
                delivery.enterQueue(Delivery.EnterDeliveryDetails()); 
                System.out.println("\nThe customer details is recorded.");
                System.out.println("------------------------------------------------");

                int PaymentMethod = SelectPaymentMethod();

                    if(PaymentMethod == 1){
                        System.out.println("Buy Now Pay Later (Installment)");
                        System.out.println("\nHow many month installment? (2/3/4 months): ");

                        while(!input.hasNextInt()){
                            System.out.println("Your should enter number. \n");
                            input.nextLine();
                            System.out.println("How many month installment? (2/3/4 months): ");
                        }
                        int installmentMonth = input.nextInt();

                        for (int i = 0; i < installmentMonth; i++) {
                            installment.enterQueue(Installment.MonthlyInstallment(order,installmentMonth));
                        }
                            CurrentPaymentQueue(installment, installmentMonth);

                            while(!installment.isEmpty()){
                            int confirmPayment = confirmPayment();
                                if(confirmPayment == 1){
                                    amountSufficient = BankAccPayment(PaymentMethod, bankacc, accountValid, amountSufficient,order,currentCust, delivery, installment);
                                    if(amountSufficient == true){
                                       installment.removeQueue();
                                       CurrentPaymentQueue(installment, installmentMonth); 
                                    }
                                    else{
                                        System.out.println("Your balance is insufficient.");
                                        break;
                                    }
                                }
                                else{
                                    SelectPaymentMethod();
                                }
                            }
                            if (amountSufficient == true) {
                                invoice(accountValid, order, currentCust, delivery);
                            }
                            else {
                                System.out.println("You have failed to make the payment.");
                            }

                    }
                    else{
                        amountSufficient = BankAccPayment(PaymentMethod, bankacc, accountValid, amountSufficient,order,currentCust, delivery, installment);
                        if (amountSufficient == true) {
                            invoice(accountValid, order, currentCust, delivery);
                        }
                        else {
                            System.out.println("You have failed to make the payment.");
                        }
                    }  
                } 
            
            boolean verifyReorder = false;
            
            do {
                System.out.print("\nDo you want to continue ordering? [Y/N]: ");
                reorder = input.nextLine().toUpperCase();
                
                if (reorder.equals("Y") || reorder.equals("N")) {
                    verifyReorder = true;
                }else{
                    verifyReorder = false;
                    System.out.println("Please enter [Y/N] only.");
                }
                
            } while (verifyReorder != true);
            
        } while (!reorder.equals("N"));
        
        System.out.println("\nThank you! See you next time!");
    } 
    
        public static int confirmPayment(){
        Scanner scan = new Scanner(System.in);
        int confirm = 0;
        boolean validInput = false;
        
        System.out.println("Want to Pay?");
       
        System.out.println("1. Yes");
        System.out.println("2. No");

        do {
            System.out.print("Enter your choice[1/2]: ");
            while(!scan.hasNextInt()){
                System.out.println("Please only enter number.\n");
                scan.nextLine();
                System.out.print("Enter your choice[1/2]: ");
            }      
            confirm = scan.nextInt();

            if (confirm > 0 && confirm <= 2) {
                validInput = true;
            } else {
                System.out.println("Please only enter valid choices.\n");
            }
        } while (validInput != true); 
        
        return confirm;
    }
    
    public static int SelectPaymentMethod() {
        Scanner scan = new Scanner(System.in);
        int choice = 0;
        boolean choiceValid = false;
        
        System.out.println("\n---------------");
        System.out.println("Payment Method");
        System.out.println("---------------");
        
        System.out.println("1. Buy Now Pay Later (Installment)");
        System.out.println("2. Pay in Full");
        
        do {
           System.out.print("\nChoose your payment method [1/2]: ");
           
            while(!scan.hasNextInt()){
                System.out.println("Please only enter number.\n");
                scan.nextLine();
                System.out.print("Choose your payment method [1/2]: ");
            }

            choice = scan.nextInt();
            
            if (choice >= 1 && choice <= 2) {
                choiceValid = true;
            } else {
                System.out.println("Please only enter valid payment method.\n");
            }       
        } while (choiceValid != true);
        
        return choice;
    }

    public static void CurrentPaymentQueue(CircularArrayQueue installment, int installmentMonth){

        System.out.println("\n==============================================");
        System.out.format("%-4s", "Current Installment Payment Status");
        System.out.println("\n==============================================");

        if (installment.isEmpty()) {
            System.out.println("All installment payment is cleared.");
        } else {
            for (int i = 0; i < installmentMonth; i++) {
                if(installment.printOneByOne(i) != null){
                    System.out.println("Installment " + (i+1) +": RM " + installment.printOneByOne(i));  
                }
                else{
                    System.out.println("Installment " + (i+1) +": Cleared"); 
                }
                 
            }

            System.out.println("==============================================");
            System.out.println("Number of Installment in queue: " + installment.initialQueueNum());
        }
        System.out.println("==============================================");
    }
    
    public static boolean BankAccPayment(int PaymentMethod, BankAccount[] bankacc, boolean accountValid, boolean amountSufficient, Order order, CircularArrayQueue currentCust, CircularArrayQueue<Delivery> delivery, CircularArrayQueue<Installment> installment){
               Scanner input = new Scanner(System.in);
               
           do {
                System.out.println("\n----------- Insert Saving Bank Account -----------");
                System.out.print("Please insert the bank account number: ");
                while(!input.hasNextInt()){
                    System.out.println("Your should enter number \n");
                    input.nextLine();
                    System.out.print("Please insert the bank account number: ");
                }
                int bank = input.nextInt();
                
                System.out.print("Please insert password: ");
                String pass = input.next();
                
                for(int j=0;j<bankacc.length;j++){
                    
                    if(bankacc[j].getAccNumber() == bank && pass.equals(bankacc[j].getPassword())){
                        accountValid = true;
                        double balanceAmount = 0;

                        switch(PaymentMethod){
                            
                            case 1:
                                if(bankacc[j].VerifyWithdrawal(Installment.getMonthlyPayment())){
                                    balanceAmount = bankacc[j].withdraw(Installment.getMonthlyPayment()); 
                                    bankacc[j].setBalance(balanceAmount);
                                    amountSufficient = true;

                                }else{
                                    System.out.println("Sorry, Your balance is insufficient.");
                                    amountSufficient = false;
                                }  
                                break;
                            
                            case 2:
                                
                                if(bankacc[j].getBalance() < order.totalPrice()){
                                    System.out.println("Sorry, Your balance is insufficient.");
                                    amountSufficient = false; 

                                }else{
                                    balanceAmount = bankacc[j].withdraw(order.totalPrice()); 
                                    bankacc[j].setBalance(balanceAmount);
                                    amountSufficient = true; 
                                }  
                                break;      
                            
                        }
                        System.out.println("\nThis bank account " + bankacc[j].getAccNumber() + " is valid.");
                        
                        System.out.println("\n===== Account Info =====");
                        System.out.println(bankacc[j].toString());
                    }
                }
                
                if (accountValid == false) {
                    System.out.println("Your bank account number and password are invalid. Please try again!");
                }
                
            } while (accountValid != true); 
           
           return amountSufficient;
    }     
    
    public static void invoice(boolean accountValid, Order order, CircularArrayQueue currentCust, CircularArrayQueue delivery){
           
        int invoicenum = 1;
           

                //Invoice
                //Enough amount && account is valid
                SimpleDateFormat formatter = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
                Date date = new Date();

                System.out.println("\n");
                System.out.println("#############################################################################################"); 
                System.out.println("                                       INVOICE");
                System.out.println("                                                   Invoice No   : IV" + String.format("%04d", invoicenum));
                System.out.println("                                                   Date & Time  : " + formatter.format(date));
                System.out.print("Bill To:\n"); 
                currentCust.displayAll();
                System.out.println(delivery.getFront());
                System.out.println("---------------------------------------------------------------------------------------------");
                System.out.print(order.toString());
                System.out.println("---------------------------------------------------------------------------------------------");
                System.out.println("Grand Total:                                                   RM " + df.format(order.totalPrice()));
                System.out.println("\n#############################################################################################");
                
                //currentCust.removeQueue();
                //currentCust.displayAll();
                invoicenum++;
           }
}