/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package FoodBeverage;

import java.util.Scanner;

/**
 *
 * @author Lau Zhong Ren
 */
public class FoodBeverageMain {
    Scanner input = new Scanner(System.in);
    
    FoodBeverageMenu[] foodMenu = {   
        new FoodBeverageMenu("F1", "White Rice", 2.20),
        new FoodBeverageMenu("F2", "Egg Fried Rice", 5.00), 
        new FoodBeverageMenu("F3", "Fried Noodles", 4.50),
        new FoodBeverageMenu("F4", "Garlic Shrimp", 13.50),
        new FoodBeverageMenu("F5", "Fried Chicken", 4.30),
        new FoodBeverageMenu("F6", "Chicken Curry", 5.50),
        new FoodBeverageMenu("F7", "Mixed Vegetables", 3.20),
        new FoodBeverageMenu("F8", "Fried Snacks", 5.00)
    };
    
    FoodBeverageMenu[] beverageMenu = {   
        new FoodBeverageMenu("B1", "Orange Juice", 3.20),
        new FoodBeverageMenu("B2", "Black Coffee", 3.50), 
        new FoodBeverageMenu("B3", "Chinese Tea", 1.50),
        new FoodBeverageMenu("B4", "Lemon Tea", 2.30),
        new FoodBeverageMenu("B5", "Coca-Cola", 3.80)
    };
    
    public int displayTitle() {
        int pax = 0;
        boolean validpaxRange = false;
        
        System.out.println("===============================");
        System.out.println("   Welcome to JiaJi Catering   ");
        System.out.println("===============================");
        
        do {
            System.out.print("Please Enter Total of Pax: ");
            while(!input.hasNextInt()){
                System.out.println("Please only enter number.\n");
                input.nextLine();
                System.out.print("Please Enter Total of Pax: ");
            }      
            pax = input.nextInt();

            if (pax > 0) {
                validpaxRange = true;
            } else {
                System.out.println("Please enter at least 1 pax.\n");
            }
        } while (validpaxRange != true); 
        
        return pax;
    }
    
    public int SelectMenu() {
        int choice = 0;
        boolean choiceValid = false;

        System.out.println("\n1. Food Menu");
        System.out.println("2. Beverage Menu");
        System.out.println("3. View Order");
        System.out.println("4. Clear All Order");
        System.out.println("5. Exit Module");
        
        do {
           System.out.print("Select Your Choice[1/2/3/4/5]: ");
           input.nextLine();
           
            while(!input.hasNextInt()){
                System.out.println("Please only enter number.\n");
                input.nextLine();
                System.out.print("Select Your Choice[1/2/3/4/5]: ");
            }

            choice = input.nextInt();
            
            if (choice >= 1 && choice <= 5) {
                choiceValid = true;
            } else {
                System.out.println("Please only enter valid choices.\n");
            }       
        } while (choiceValid != true);
        
        return choice;
    }
    
    public FoodBeverageMenu orderFood() {
        String foodID = "";
        boolean validpaxRange = false;
        
        FoodBeverageMenu choosenItem = new FoodBeverageMenu();
                
        System.out.println("\n==============================================");
        System.out.format("%-9s %-18s %-14s", "Food ID", "Food Type", "Price Per Unit");
        System.out.println("\n==============================================");
        for (int i = 0; i < foodMenu.length ; i++) {
            System.out.println(foodMenu[i].displayMenu());
        }
        System.out.println("==============================================");
        
        input.nextLine();
        do {    
            System.out.print("Enter Food ID: ");
            foodID = input.nextLine().toUpperCase();
         
            for (int i = 0; i < foodMenu.length; i++) {
                if (foodID.equals(foodMenu[i].getID())) {
                    choosenItem.setID(foodMenu[i].getID());
                    choosenItem.setName(foodMenu[i].getName());
                    choosenItem.setPrice(foodMenu[i].getPrice());
                }
            }
        } while (!"F1".equals(foodID) && !"F2".equals(foodID) && !"F3".equals(foodID) && !"F4".equals(foodID) && !"F5".equals(foodID) && !"F6".equals(foodID) && !"F7".equals(foodID) && !"F8".equals(foodID)); 
        
        do {
            System.out.print("Enter Order Pax [1-999]: ");
            while(!input.hasNextInt()){
                System.out.println("Please only enter number.\n");
                input.nextLine();
                System.out.print("Enter Order Pax [1-999]: ");
            }      
            int pax = input.nextInt();

            if (pax > 0 && pax <= 999) {
                validpaxRange = true;
                choosenItem.setPax(pax);
            } else {
                System.out.println("Please only enter valid range.\n");
            }

        } while (validpaxRange != true); 
        
        input.nextLine();
        System.out.print("Enter Order Remark: ");
        String remark = input.nextLine();
        
        if (remark.isEmpty()) {
            choosenItem.setRemark("NONE");
        }
        else {
            choosenItem.setRemark(remark);
        }
        
        return choosenItem;
    }
    
    public FoodBeverageMenu orderBeverage() {
        String beverageID = "";
        boolean validpaxRange= false;     
        
        FoodBeverageMenu choosenItem = new FoodBeverageMenu();
                
        System.out.println("\n==============================================");
        System.out.format("%-12s %-18s %-14s", "Beverage ID", "Beverage Type", "Price Per Pax");
        System.out.println("\n==============================================");
        for (int i = 0; i < beverageMenu.length ; i++) {
            System.out.println(beverageMenu[i].displayMenu());
        }
        System.out.println("==============================================");
        
        input.nextLine();
        do {
            System.out.print("Enter Beverage ID: ");
            beverageID = input.nextLine().toUpperCase();
         
            for (int i = 0; i < beverageMenu.length; i++) {
                if (beverageID.equals(beverageMenu[i].getID())) {
                    choosenItem.setID(beverageMenu[i].getID());
                    choosenItem.setName(beverageMenu[i].getName());
                    choosenItem.setPrice(beverageMenu[i].getPrice());
                }
            }
        } while (!"B1".equals(beverageID) && !"B2".equals(beverageID) && !"B3".equals(beverageID) && !"B4".equals(beverageID) && !"B5".equals(beverageID)); 
        
        
        do {
            System.out.print("Enter Order Pax [1-999]: ");
            while(!input.hasNextInt()){
                System.out.println("Please only enter number.\n");
                input.nextLine();
                System.out.print("Enter Order Pax [1-999]: ");
            }      
            int pax = input.nextInt();

            if (pax > 0 && pax <= 999) {
                validpaxRange = true;
                choosenItem.setPax(pax);
            } else {
                System.out.println("Please only enter valid choice [1-999].\n");
            }

        } while (validpaxRange != true); 
        
        input.nextLine();
        System.out.print("Enter Order Remark: ");
        String remark = input.nextLine();
        
        if (remark.isEmpty()) {
            choosenItem.setRemark("NONE");
        }
        else {
            choosenItem.setRemark(remark);
        }
        
        return choosenItem;
    }
    
    public void displayOrder() {
        System.out.println("=======================================================================================");
        System.out.format("%-4s %-18s %-16s %-10s %-20s %-8s", "ID", "Name",  "Price Per Pax", "Quantity", "Remark", "SubTotal");
        System.out.println("\n=======================================================================================");
    }
    
    public int confirmOrder(FoodBeverageMenu choosenItem) {
        int confirm = 0;
        boolean validInput = false;
        
        System.out.println("\nYour Choice: ");
        displayOrder();
        System.out.println(choosenItem);
        System.out.println("=======================================================================================");
        
        System.out.println("1. Yes");
        System.out.println("2. No");

        do {
            System.out.print("Confirm Order[1/2]: ");
            while(!input.hasNextInt()){
                System.out.println("Please only enter number.\n");
                input.nextLine();
                System.out.print("Confirm Order[1/2]: ");
            }      
            confirm = input.nextInt();

            if (confirm > 0 && confirm <= 2) {
                validInput = true;
            } else {
                System.out.println("Please only enter valid choices.\n");
            }
        } while (validInput != true); 
        
        return confirm;
    }
    
    public int continueOrder() {
        int Continue = 0;
        boolean validInput = false;
        
        System.out.println("\n1. Continue Order");
        System.out.println("2. Proceed Facility");
        
        do {
            System.out.print("Enter Choice[1/2]: ");
            while(!input.hasNextInt()){
                System.out.println("Please only enter number.\n");
                input.nextLine();
                System.out.print("Enter Choice[1/2]: ");
            }      
            Continue = input.nextInt();

            if (Continue > 0 && Continue <= 2) {
                validInput = true;
            } else {
                System.out.println("Please only enter valid choices.\n");
            }
        } while (validInput != true); 
        
        return Continue;
    }

}