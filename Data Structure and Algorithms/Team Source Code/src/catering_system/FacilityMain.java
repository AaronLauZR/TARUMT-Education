/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package catering_system;

import adt.*;
import entity.*;
//import java.util.HashMap;
import java.util.Scanner;

/**
 *
 * @author THENG CHIA CHIA
 */
public class FacilityMain {
    Scanner input = new Scanner(System.in);
    HashMap<String, Integer> FCLmap = new HashMap<String, Integer>();
    StackLibrary<FacilityMenu> stack = new StackLibrary<FacilityMenu>(100);
    
    FacilityMenu[] fclMenu = {   
        new FacilityMenu("TB1", "Table", 3.50),
        new FacilityMenu("CH1", "Dining Chair", 10.50),
        new FacilityMenu("CH2", "Childrens Chair", 10.00), 
        new FacilityMenu("TN1", "20' x 20'", 10.00), 
        new FacilityMenu("TN2", "40' x 20'", 10.00), 
    };
    
    public void FCLmap(){
        FacilityMain fclType = new FacilityMain();
        FacilityMenu selectFCL;
        String key = " ";
        int value = 0;
        
        selectFCL = fclType.bookFCL();
        key = selectFCL.getId();
        value = selectFCL.getQty();
                
      
        if(FCLmap.contains(key)){
            System.out.println("Fail to add. \nFacility booking already exists.");
        }else{
            FCLmap.put(key, value);
            if(FCLmap.getValue(key) == null){
                FCLmap.put(key, value);
            }
            System.out.println("Facility with id "+key+" successfully booked.\n");
        }
        
    }

    public String CHKCart(){
        System.out.println("Enter Facility ID: ");
        String id = input.next().toUpperCase();
        return id;
    }
    
    public int fclCHK(){
       int option = 0;
       System.out.println("\n~~~~~~~~~~ Facility checking ~~~~~~~~~~~~");
       System.out.println("    1. Display cart "); 
       System.out.println("    2. Delete facility ");
       System.out.println("    3. Update facility");
       System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        do{
            try 
            { 
               
                System.out.println("Enter an option: ");
                option = Integer.parseInt(input.next());
                System.out.println(" ");

            }  
            catch (NumberFormatException e)  
            { 
                System.out.println("\nWrong! Option must be numeric. \nPlease enter again.\n"); 
            } 
            
        } while ((option < 1 || option > 3) && !Character.isDigit(option));
        
        return option;
    }
    
    public void displayOrder() {
        
        System.out.println("--------------------------------------------------------------------");
        System.out.format("%-6s %-20s %-15s %-10s %-8s", "ID", "Type", "Price Per Unit", "Quantity", "SubTotal");
        System.out.println("\n--------------------------------------------------------------------");
        FacilityMenu key;
        for (int i = 0; i < fclMenu.length ; i++) {
                if(FCLmap.contains(fclMenu[i].getId()))
                {
                    fclMenu[i].setQty(FCLmap.getValue(fclMenu[i].getId()));
                    System.out.print(fclMenu[i].toString());
                    System.out.println("");
                }
        }
        System.out.println("--------------------------------------------------------------------");
    }

    
    public char ContinueConfirm(){
        char cont = 'Y';
        do{
            System.out.println("\nChoose next facility(Y/N): ");
            cont = Character.toUpperCase(input.next().charAt(0));
        }while(cont != 'N' && cont != 'Y');
        return cont;
    }
    
    
    public FacilityMenu bookFCL() {
        String fclID = "";
        
        FacilityMenu selectFCL = new FacilityMenu();
        
        System.out.println("=================================================");
        System.out.format("%-6s %-20s %-8s", "ID", "TABLE TYPE", "PRICE");
        System.out.println("\n=================================================");
   
        for (int i = 0; i < fclMenu.length ; i++) {
            System.out.println(fclMenu[i].displayMenu());
        }
         System.out.println("=================================================");
        
        //input.nextLine();
        do {    
            System.out.println("Enter Facility ID: ");
            fclID = input.nextLine().toUpperCase();
         
            for (int i = 0; i < fclMenu.length; i++) {
                if (fclID.equals(fclMenu[i].getId())) {
                    selectFCL.setId(fclMenu[i].getId());
                    selectFCL.setType(fclMenu[i].getType());
                    selectFCL.setPrice(fclMenu[i].getPrice());
                }
            }
        } while (!"TB1".equals(fclID) && !"CH1".equals(fclID) && !"CH2".equals(fclID) && !"TN1".equals(fclID) && !"TN2".equals(fclID)); 
        
        int quantity = -1;
        do{
            try 
            { 
                System.out.println("\nEnter Quantity : ");
                quantity = Integer.parseInt(input.next());
                selectFCL.setQty(quantity);
                selectFCL.getQty();
            }  
            catch (NumberFormatException e)  
            { 
                System.out.println("\nWrong! quantity must be numeric. \nPlease enter again.\n"); 
            } 
        }while(quantity < 0);
       
        input.nextLine();
        return selectFCL; 
    }
    
    public void FCLStackIn(){

        String finalFcl;
        String key;
        int sizeKey = FCLmap.getSize();
        while(sizeKey > 0){
            for (int i = 0; i < fclMenu.length ; i++) {
                if(FCLmap.contains(fclMenu[i].getId())){
                    if(FCLmap.contains(fclMenu[i].getId()))
                    {
                        fclMenu[i].setQty(FCLmap.getValue(fclMenu[i].getId()));
                        System.out.println("");
                        stack.insert(fclMenu[i]);
                        FCLmap.remove(fclMenu[i].getId());
                    }
                    
                }
                    
               
            }
            sizeKey = FCLmap.getSize();
        } 
    }
    
    public void FCLStackOut(){
         while(stack.countLength() > 0){
            stack.undo();
        }
    }

}
