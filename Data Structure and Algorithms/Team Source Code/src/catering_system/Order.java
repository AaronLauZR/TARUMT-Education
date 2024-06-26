/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package catering_system;

import adt.*;
import entity.*;
import java.util.Scanner;

/**
 *
 * @author andre
 */
public class Order {
    
    Scanner input = new Scanner(System.in);
    ArrayList<FoodBeverageMenu> orderFB = new ArrayList();
    ArrayList<FacilityMenu> orderFacility = new ArrayList();
    
    Order() {
            
    }

    public void stackFBStoreIntoArrayList(StackLibrary stack) {
        int count = stack.countLength();
        
        orderFB.exceedLength(count); //Extend the array with double size
        
        for (int i = 0; i < count; i++) {
            orderFB.insert((FoodBeverageMenu)stack.undo());
        }
        
        orderFB.reverse(orderFB); //Reverse to store into arrayList
    }
    
    public void stackFacilityStoreIntoArrayList(StackLibrary stack) {
        int count = stack.countLength();

        orderFacility.exceedLength(count); //Extend the array with double size
        
        for (int i = 0; i < count; i++) {
            orderFacility.insert((FacilityMenu)stack.undo());
        }
        
        orderFacility.reverse(orderFacility); //Reverse to store into arrayList
    }
    
    
    
    public void displayFBCart() {
        System.out.println("This is your current Food & Beverage cart.");
        System.out.println("=======================================================================================");
        System.out.format("%-4s %-18s %-16s %-10s %-20s %-8s", "ID", "Name",  "Price Per Unit", "Quantity", "Remark", "SubTotal");
        System.out.println("\n=======================================================================================");
        
        if (orderFB.isEmptyList()) {
            System.out.println("Your cart is empty");
        } else {
            System.out.print(orderFB.toString()); 
        }
        System.out.println("=======================================================================================");
        
    }
    
    public void displayFacilityCart() {
        System.out.println("This is your current Facility cart.");
        System.out.println("========================================================================");
        System.out.format("%-6s %-20s %-15s %-10s %-8s", "ID", "Type", "Price Per Unit", "Quantity", "SubTotal");
        System.out.println("\n========================================================================");
        
        if (orderFacility.isEmptyList()) {
            System.out.println("Your cart is empty");
        } else {
            System.out.print(orderFacility.toString()); 
        }
        System.out.println("========================================================================");
        
    }
    
    public int optionMenu() {
        boolean choiceValid = false;
        int choice = 0;
        
        //---------- Choice Customise or Proceed Order ----------
        System.out.println("");
        System.out.println("--------------------------------------");
        System.out.println("              Order Menu              ");
        System.out.println("--------------------------------------");
        System.out.println("1. View Food & Beverage Cart\n" +
                           "2. View Facility Cart\n" +
                           "3. Customise Food & Beverage Cart\n" +
                           "4. Customise Facility Cart\n" +
                           "5. Confirm All Order\n" + 
                           "6. Cancel Order");
        System.out.println("--------------------------------------");
        
       do {
            System.out.print("Select Your Choice [1, 2 ,3, 4, 5, 6]: ");
            while(!input.hasNextInt()){
                System.out.println("Your should enter number. Please try again!\n");
                input.nextLine();
                System.out.print("Select Your Choice [1, 2 ,3, 4, 5, 6]: ");
            }

            choice = input.nextInt();
            
            if (choice > 0 && choice <= 6) {
                choiceValid = true;
            } else {
                System.out.println("You should enter valid choice [1 - 6]. Please try again!\n");
            }
            
        } while (choiceValid != true);
        
        System.out.println("");
        
        return choice;
    }
    
    public void printCustomizeFBMenu() {
        //---------- Choice Delete or Edit ----------
        System.out.println("\n--------------------------------------");
        System.out.println("             Customise F & B             ");
        System.out.println("--------------------------------------\n" + 
                           "1. Edit \n" +
                           "2. Delete \n" +
                           "3. Cancel \n" + 
                           "--------------------------------------");
    }
    
    public void printCustomizeFacilityMenu() {
        //---------- Choice Delete or Edit ----------
        System.out.println("\n--------------------------------------");
        System.out.println("           Customise Facility             ");
        System.out.println("--------------------------------------\n" + 
                           "1. Edit \n" +
                           "2. Delete \n" +
                           "3. Cancel \n" + 
                           "--------------------------------------");
    }
    
    public int optionCustomizeItem() {
        boolean choiceValid = false;
        int choice = 0;
        
        input.nextLine();
        
        do {
            System.out.print("Select Your Choice [1, 2 ,3]: ");
            while(!input.hasNextInt()){
                System.out.println("Your should enter number. Please try again!\n");
                input.nextLine();
                System.out.print("Select Your Choice [1, 2 ,3]: ");
            }

            choice = input.nextInt();

            if (choice > 0 && choice <= 3) {
                choiceValid = true;
            } else {
                System.out.println("You should enter valid choice [1 - 3]. Please try again!\n");
            }

        } while (choiceValid != true);
        
        System.out.println("");
        
        return choice;
    }
    
    public void editFood_BeverageOrder() {
        ArrayList<FoodBeverageMenu> editItem = new ArrayList();
        
        String inputID = "";
        boolean validInput = false;
        int editPosition = 0;
        
        if (orderFB.isEmptyList()) {
            System.out.println("Your item can't be edited because the cart is empty.\n");
        }
        else {
            displayFBCart();
            input.nextLine();

            do {

                System.out.print("Insert the ID to EDIT the item: ");
                inputID = input.nextLine().toUpperCase();

                for (int i = 0; i < orderFB.length(); i++) {
                    if (inputID.equals(orderFB.getEntry(i + 1).getID())) {
                        editPosition = i;
                        validInput = true;
                    }
                }

                if (validInput == false) {
                    System.out.println("Please enter the valid ID.\n");
                } else {
                    orderFB.replaceAndMoveToLast(editPosition + 1, changeFBDescription(editPosition));
                    System.out.println(orderFB.getEntry(orderFB.getNumberOfEntries()).getName() + " has edited from the cart.\n");
                }

            } while (validInput != true);
        }

    }
    
    private FoodBeverageMenu changeFBDescription(int index) {

        boolean validPaxRange = false;

        //Edit the food & beverage quantity
        System.out.println("\n--------------------------------------");
        System.out.println("         Customise F & B Quantity             ");
        System.out.println("--------------------------------------");
        
        do {
            System.out.print("Enter Pax [1-999]: ");
            //input.nextLine();
            while(!input.hasNextInt()){
                System.out.println("Your should enter number. Please try again!\n");
                input.nextLine();
                System.out.print("Enter Order Pax: ");
            }      
            int pax = input.nextInt();

            if (pax > 0 && pax <= 999) {
                validPaxRange = true;
                orderFB.getEntry(index + 1).setPax(pax);
            } else {
                System.out.println("You should enter valid choice [1-999]. Please try again!\n");
            }

        } while (validPaxRange != true);

        
        //Edit the food & beverage remark
        input.nextLine();
        System.out.println("\n--------------------------------------");
        System.out.println("         Customise F & B Remark             ");
        System.out.println("--------------------------------------");
        System.out.print("Enter Remark: ");
        String remark = input.nextLine();
        
        if (remark.equals("")) {
            orderFB.getEntry(index + 1).setRemark("None");
        }
        else {
            orderFB.getEntry(index + 1).setRemark(remark);
        }
        System.out.println("");
        
        return orderFB.getEntry(index + 1);

    }
    
    public void editFacilityOrder() {
        
        ArrayList<FacilityMenu> editItem = new ArrayList();
        
        String inputID = "";
        boolean validInput = false;
        int editPosition = 0;
        
        if (orderFacility.isEmptyList()) {
            System.out.println("Your Facility item can't be edited because the cart is empty.");
        }
        else {
            displayFacilityCart();
            input.nextLine();

            do {

                System.out.print("Insert the ID to EDIT the item: ");
                inputID = input.nextLine().toUpperCase();

                for (int i = 0; i < orderFacility.length(); i++) {
                    if (inputID.equals(orderFacility.getEntry(i + 1).getId())) {
                        editPosition = i;
                        validInput = true;
                    }
                }

                if (validInput == false) {
                    System.out.println("Please enter the valid ID.\n");
                } else {
                    orderFacility.replaceAndMoveToLast(editPosition + 1, changeFacilityDescription(editPosition));
                    System.out.println(orderFacility.getEntry(orderFacility.getNumberOfEntries()).getType() + " has edited from the cart.");
                }

            } while (validInput != true);
        }
        
    }
    
    private FacilityMenu changeFacilityDescription(int index) {

        boolean validPaxRange = false;

        //Edit the food & beverage quantity
        System.out.println("\n--------------------------------------");
        System.out.println("         Customise Facility Quantity             ");
        System.out.println("--------------------------------------");
        
        do {
            System.out.print("Enter Pax [1-999]: ");
            //input.nextLine();
            while(!input.hasNextInt()){
                System.out.println("Your should enter number. Please try again!\n");
                input.nextLine();
                System.out.print("Enter Order Pax: ");
            }      
            int qty = input.nextInt();

            if (qty > 0 && qty <= 999) {
                validPaxRange = true;
                orderFacility.getEntry(index + 1).setQty(qty);
            } else {
                System.out.println("You should enter valid choice [1-999]. Please try again!\n");
            }

        } while (validPaxRange != true);
        
        System.out.println("");
        
        return orderFacility.getEntry(index + 1);

    }
    
    public void deleteFood_BeverageOrder() {
        
        String inputID = "";
        boolean validInput = false;
        
        if (orderFB.isEmptyList()) {
            System.out.println("Your F&B item can't be deleted because the cart is empty.");
        }
        else {
            displayFBCart();
            input.nextLine();

            do {
                System.out.print("Insert the ID to DELETE the item: ");
                inputID = input.nextLine().toUpperCase();
                System.out.println("");

                for (int i = 0; i < orderFB.length(); i++) {
                    if (inputID.equals(orderFB.getEntry(i + 1).getID())) {
                        System.out.println(orderFB.getEntry(i + 1).getName() + " has deleted from the cart.");
                        orderFB.delete(i);
                        validInput = true;
                    }
                }

                if (validInput == false) {
                    System.out.println("Please enter the valid ID.");
                }

            } while (validInput != true);
        }
        
    }
    
    public void deleteFacilityOrder() {
        
        String inputID = "";
        boolean validInput = false;
        
        if (orderFacility.isEmptyList()) {
            System.out.println("Your facility item can't be deleted because the cart is empty.");
        }
        else {
            displayFacilityCart();
            input.nextLine();

            do {
                System.out.print("Insert the ID to DELETE the item: ");
                inputID = input.nextLine().toUpperCase();
                System.out.println("");

                for (int i = 0; i < orderFacility.length(); i++) {
                    if (inputID.equals(orderFacility.getEntry(i + 1).getId())) {
                        System.out.println(orderFacility.getEntry(i + 1).getType() + " has deleted from the cart.");
                        orderFacility.delete(i);
                        validInput = true;
                    }
                }

                if (validInput == false) {
                    System.out.println("Please enter the valid ID.");
                }

            } while (validInput != true);
        }
        
    }
    
    public double totalFBPrice() {
        double totalPrice = 0.0;
        
        for (int i = 0; i < orderFB.length(); i++) {
            totalPrice += orderFB.getEntry(i + 1).calcSubTotal();
        }
        return totalPrice;
    }
    
    public double totalFacilityPrice() {
        double totalPrice = 0.0;
        
        for (int i = 0; i < orderFacility.length(); i++) {
            totalPrice += orderFacility.getEntry(i + 1).calcSubTotal();
        }
        return totalPrice;
    }
    
    public double totalPrice() {
        return totalFBPrice() + totalFacilityPrice();
    }
    
    public String toString() {
        return orderFB.toString() + "\n" + orderFacility.toString();
    }
    
        
}
