/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */

package FoodBeverage;

import StackADT.StackLibrary;
import java.util.Scanner;

/**
 *
 * @author Window
 */
public class FoodBeverage {

    public static void main(String[] args) {
// TODO code application logic here
        Scanner input = new Scanner(System.in);
              
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
                        System.out.println("\nYour current F&B cart");
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
    }
}