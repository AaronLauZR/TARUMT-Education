/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package onlineshopping;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;

/**
 *
 * @author andre
 */
public class OnlineShopping {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Scanner scan = new Scanner(System.in);
        
        //Person Arraylist
        //Existing Customer dummy information
        ArrayList<Person> persons = existingCustomer();
        //Current customer
        Person currentUser = new Person();

        int invoicenum = 1;
        char again = 'a';

        do {
        boolean userValid = false;
        
        do{
            System.out.print("Are you a new customer? (Y/N): ");
            char ans = scan.next().charAt(0);
            ans = Character.toUpperCase(ans);
            
            switch(ans) {
                case 'Y':
                    persons.add((Customer)EnterRegister());
                    System.out.println("You have successfully registered!");
                    currentUser = EnterLogin(persons);
                    userValid = true;
                    break;
                case 'N':
                    currentUser = EnterLogin(persons);  
                    userValid = true;
                    break;
                default:
                    System.out.println("The input is invalid. Please try again!\n");
                    break;
            }
        
        }while(userValid != true);

        
        int optionInput = 0;
        boolean proceedOrder = false;
             
        Product[] product = {   
            new Shoe("Nike Air Jordan", 50, Product.Color.White, Shoe.ShoeBrands.Nike),
            new Shirt("Topman T-Shirt", 150, Product.Color.Blue, Shirt.ShirtBrands.Topman), 
            new Pant("Calvin Klein Jean", 150, Product.Color.Green, Pant.PantBrands.CalvinKlein),
            new Shoe("Adidas Forum Low", 150, Product.Color.Black, Shoe.ShoeBrands.Adidas),
            new Pant("Levi Amazing Jean", 95, Product.Color.Blue, Pant.PantBrands.Levi),
            new Shirt("Gucci Graphic T", 116, Product.Color.Yellow, Shirt.ShirtBrands.Gucci)
        };
        
        //Cart
        ArrayList<OrderLine> cart = new ArrayList<OrderLine>();
        //Order
        //ArrayList<Order> Order = new ArrayList<Order>();
        Order order = new Order();
        
        scan.nextLine();
        
            try{
                do {
                    
                    printMenu();
                    while(!scan.hasNextInt()){
                        System.out.println("Your should enter number. Please try again!\n");
                        scan.nextLine();
                        printMenu();
                    }
                    optionInput = scan.nextInt();
                    System.out.println("");

                    if (optionInput == 1 || optionInput == 2 || optionInput == 3 || optionInput == 4) {

                        //Print the product
                        printProduct(product, optionInput);  
                        
                        //Prompt user to choose the product
                        scan.nextLine();
                        System.out.print("Choose the product ID: ");
                        String productIDInput = scan.nextLine();

                        //Check the product is available or not based on the user input
                        boolean productAvailable = false;
                        for (int i = 0; i < product.length; i++) {
                            if (productIDInput.equals(product[i].getProductNo())) {
                    
                                if (product[i] instanceof Shoe) {
                                    ((Shoe)product[i]).setShoeSize(chooseShoeSize());
                                    
                                }else if(product[i] instanceof Shirt) {
                                    ((Shirt)product[i]).setShirtSize(chooseClothSize());    
                                }else{
                                    ((Pant)product[i]).setPantSize(chooseClothSize());    
                                }
                                
                                System.out.print("Choose the quantity: ");
                                while(!scan.hasNextInt()){
                                    System.out.println("Your should enter number \n");
                                    scan.nextLine();
                                    System.out.print("Choose the quantity: ");
                                }
                                int quantityInput = scan.nextInt();

                                OrderLine orderLine = new OrderLine(quantityInput, product[i]);
                                cart.add(orderLine);
                                System.out.println("You have added " + quantityInput + " " + product[i].getProductName() + " into the cart.");
                                System.out.println("");
                                productAvailable = true;
                            }
                        }

                        if (productAvailable == false) {
                            System.out.println("Sorry, this product ID is unavailable. Please try again!");
                            System.out.println("");
                        }
                    }
                    
                    if (optionInput == 5) {
                        System.out.println("");

                        if (!cart.isEmpty()) {
                            System.out.println("========================================== Cart ===========================================");
                            System.out.format("%-3s %-18s %-9s %-9s %-8s %-15s %-9s %-9s", "ID", "Name", "Price(RM)", "Color", "Size", "Brand", "Quantity" ,"Subtotal(RM)" + "\n");
                            System.out.println("-------------------------------------------------------------------------------------------");
                            for (OrderLine o: cart) {
                                System.out.println(o.toString());
                            }
                            System.out.println("===========================================================================================");
                            System.out.println("");

                            String comfirmOrder = "";

                            System.out.print("Do you want to proceed to order? (Y/N): ");
                            scan.nextLine();
                            comfirmOrder = scan.nextLine();
                            comfirmOrder = comfirmOrder.toUpperCase();

                            if (comfirmOrder.equals("Y")) {
                                
                                proceedOrder = true;
                            }

                        }else{
                            System.out.println("Your cart is currently empty.");
                            System.out.println("");
                        }

                    }
                    if (optionInput == 6) {
                        System.out.println("\nThanks for using!");
                        System.out.println("See you again!");
                        System.exit(0);
                    }
                    
                    if (optionInput < 1 || optionInput > 6) {
                        System.out.println("Please enter the number in the range between 1 to 6.\n");
                    }

                }while(optionInput != 6 && proceedOrder != true);
                
            }catch(Exception e) {
                System.out.println("The input is invalid.");
            }

        if (proceedOrder) {
            
            //Make an order
            order.setOrderLine(cart);
            //printPersons(prsArray);
            System.out.println(order.toString());
            
            //Bank Account Verification
            boolean accountValid = false;
            boolean amountSufficient = false;
            
            //Dummy bank saving accounts
            //bankacc：456123 password：P456123
            // bankacc:123456 password：P123456
            // bankacc：789456 password：P789456
            // bankacc：456789 password：P456789
            
            savingAcc[] bankacc = {
                // new savingAcc(accnumber,balance,password),
                new savingAcc(456123,4562,"P456123"),
                new savingAcc(123456,5000,"P123456"),
                new savingAcc(789456,50,"P789456"),
                new savingAcc(456789,456,"P456789")
            };
            
            do {
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
                
                for(int j=0;j<bankacc.length;j++){
                    if(((savingAcc)bankacc[j]).getAccNumber() == bank && pass.equals(((savingAcc)bankacc[j]).getPass())){
                        accountValid = true;
                        amountSufficient = ((savingAcc)bankacc[j]).withdraw(order.calcGrandTotal());
                        
                        System.out.println("\nThis bank account " + ((savingAcc)bankacc[j]).getAccNumber() + " is valid.");
                        
                        System.out.println("\n===== Account Info =====");
                        System.out.println(((savingAcc)bankacc[j]).toString());
                    }
                }
                
                if (accountValid == false) {
                    System.out.println("Your bank account number and password are invalid. Please try again!");
                }
                
            } while (accountValid != true);
            
            if (accountValid && amountSufficient) {
                //Invoice
                //Enough amount && account is valid
                SimpleDateFormat formatter = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
                Date date = new Date();

                System.out.println("\n");
                System.out.println("#############################################################################################"); 
                System.out.println("                                       INVOICE");
                System.out.println("                                                   Invoice No   : IV" + String.format("%04d", invoicenum));
                System.out.println("                                                   Date & Time  : " + formatter.format(date));
                System.out.println("                                                   Customer ID  : " + ((Customer)currentUser).getCustomerID());
                System.out.println(" Bill To:                                          Customer Name: " + ((Customer)currentUser).getName());
                System.out.println("\t " + ((Customer)currentUser).getAddress().getHomeNumber() + ", " + ((Customer)currentUser).getAddress().getStreet() + ", ");
                System.out.println("\t " + ((Customer)currentUser).getAddress().getPosscode() + ", " + ((Customer)currentUser).getAddress().getCity() + ", ");
                System.out.print("\t " + ((Customer)currentUser).getAddress().getState());
                System.out.print(order.toString());
                System.out.println("#############################################################################################");

                invoicenum++;

                System.out.println("\nSuccesful Order!");
                
            }else{
                System.out.println("Your amount is insufficient. You have failed to make the payment.");
            }
            
        }
        
        //Prompt customer to buy the product again
        boolean errorInput = true;
        
        do {
            do {
                try {
                    System.out.print("\nDo you want to buy again? (Y/N): ");
                    again = scan.next().charAt(0);
                    again = Character.toUpperCase(again);
                    errorInput = false;
                }
                catch (Exception e) {        
                    System.out.println("Invalid input! Please only enter avaliable character.");
                }
            } while (errorInput);

            if ( again == 'Y') {
                System.out.println("\nWelcome again!");
            }
            else if ( again == 'N') {
                System.out.println("Thanks for ordering!");
                System.out.println("See you next time!");
            }
            else {
                System.out.println("Invalid input! Please only enter avaliable character.");
            }
        
        } while (again != 'Y' && again !='N');
        
        } while(again == 'Y');
        
    }
    
    public static void printMenu() {
        System.out.println("1. Display All Product");
        System.out.println("2. Display Shoe");
        System.out.println("3. Display Shirt");
        System.out.println("4. Display Pant");
        System.out.println("5. Display Cart");
        System.out.println("6. Exit");
        System.out.print("Choose your option [1-6]: ");
    }
    
    public static void printProduct(Object[] product, int optionInput) {
        
        System.out.println("============================== Product ===============================");
        System.out.format("%-3s %-18s %-9s %-9s %-9s", "ID", "Name", "Price(RM)", "Color", "Brand");
        System.out.println("\n----------------------------------------------------------------------");
        
        for (int i = 0; i < product.length; i++) {
            
            switch(optionInput) {
                case 1: //Product items
                    if (product[i] instanceof Product) {
                        System.out.println(((Product)product[i]).displayProduct());
                    }
                    break;  
                case 2: //Shoe items
                    if (product[i] instanceof Shoe) {
                        System.out.println(((Shoe)product[i]).displayProduct());
                    }
                    break;      
                case 3: //Shirt items
                    if (product[i] instanceof Shirt) {
                        System.out.println(((Shirt)product[i]).displayProduct());
                    }
                    break;
                case 4: //Pant items
                    if (product[i] instanceof Pant) {
                        System.out.println(((Pant)product[i]).displayProduct());
                    }
                    break;  
                default:
                    System.out.println("No Product");
                    break;
            }
        }
        System.out.println("======================================================================");
    }
    
    public static int chooseShoeSize() {
        Scanner scan = new Scanner(System.in);
        
        int shoeSize = 0;
        boolean sizeAvailable = false;

        do {
            System.out.print("Please choose the shoe size(EU) that you want[35 - 45]: ");
            shoeSize = scan.nextInt();
            
            if (shoeSize >= 35 && shoeSize <= 45) {
                sizeAvailable = true;
            }else{
                System.out.println("The input is invalid. Please enter from 35 to 45 only.\n");
            }
            
        } while (sizeAvailable != true);
        
        return shoeSize;
    }
    
    public static String chooseClothSize() {
        Scanner scan = new Scanner(System.in);
        String[] clothSize = {"XS", "S", "M", "L", "XL", "XXL"};
        
        int clothSizeOption = 0;
        boolean sizeAvailable = false;

        do {
            System.out.println("");
            System.out.println("=================== Cloth Size ==================");
            for (int i = 0; i < clothSize.length; i++) {
                System.out.println((i + 1) + ". " + clothSize[i]);  
            }
            System.out.println("=================================================");
            System.out.print("Please choose the shoe size that you want[1 - " + clothSize.length + "]: ");
            clothSizeOption = scan.nextInt();
            
            if (clothSizeOption >= 1 && clothSizeOption <= clothSize.length) {
                sizeAvailable = true;
            }else{
                System.out.println("The input is invalid. Please enter from 1 to 6 only.");
            }
            
        } while (sizeAvailable != true);
        
        return clothSize[clothSizeOption - 1];
    }
   
    
    public static Customer EnterRegister(){

        boolean invalid_input = false;
        Scanner scan = new Scanner(System.in);

        Customer cust = new Customer();
        System.out.println("\n----------- Customer Registration -----------");

        System.out.print("Customer ID: " + Customer.getNextCustomerID());
        cust.setCustomerID(Customer.getNextCustomerID());

        System.out.print("\nName: ");
        cust.setName(scan.nextLine());

        do{
            System.out.print("Age: ");
            try{
                cust.setAge(scan.nextInt());
                invalid_input = false;

            }catch(Exception e) {
                    System.out.println("Invalid age. Please try again!");
                    scan.next();
                    invalid_input = true;
            }       
         }while(invalid_input != false);

        scan.nextLine();

        do{
        System.out.print("Gender (M/F): ");
        char gender = scan.next().charAt(0);
            if(Character.toUpperCase(gender)== 'M' || Character.toUpperCase(gender) == 'F'){
                cust.setGender(Character.toUpperCase(gender));
                invalid_input = false;
            }
            else{
               System.out.println("Invalid gender. Please try again!");
               invalid_input = true;
            }
        }while(invalid_input != false);

        scan.nextLine();

        System.out.print("IC Number: ");
        cust.setIc(scan.nextLine());

        System.out.print("Contact number: ");
        cust.setContactNo(scan.nextLine());

        System.out.print("Address:    ");
        cust.setAddress(EnterAddress());

        System.out.println("------------------------------------------");

        return cust;
    }

    
    public static Address EnterAddress(){
        boolean invalid_input = true;
        Scanner address = new Scanner(System.in);
        Address adr = new Address();

        System.out.printf("|Home Number = ");
        adr.setHomeNumber(address.nextLine());
        
        System.out.printf("%22s","|Street = ");
        adr.setStreet(address.nextLine());
        
        do{
            System.out.printf("%20s","|City = ");
            String city = address.nextLine();
            if(isAlpha(city) == true){
                adr.setCity(city);
                invalid_input = false;
            }
            else{
                System.out.println("Invalid city. Please try again!");
                invalid_input = true;
            }
        }while(invalid_input != false);

        do{
            System.out.printf("%23s","|Poscode = ");
            try{
                adr.setPosscode(address.nextInt());
                invalid_input = false;
                
            }catch(Exception e) {
                    System.out.println("Invalid poscode. Please try again!");
                    address.next();
                    invalid_input = true;
            }       
         }while(invalid_input != false);
        
        address.nextLine();
        
        do{
            System.out.printf("%21s","|State = ");
            String state = address.nextLine();
            if(isAlpha(state) == true){
                adr.setState(state);
                invalid_input = false;
            }
            else{
                System.out.println("Invalid State. Please try again!");
                invalid_input = true;
            }
        }while(invalid_input != false);
       
        return adr;
    }
    
    
    public static boolean isAlpha(String s) {
        return s != null && s.matches("^[a-zA-Z]*$");
    }
    
    public static ArrayList<Person> existingCustomer() {
        
        ArrayList<Person> persons = new ArrayList<Person>();
        
        Address[] address = {
            new Address("12A", 45100, "Jalan Gajah", "Tanjung Bungah", "Pulau Penang"),
            new Address("20B", 53300, "Jalan Maju", "Taman Maju Jaya", "Johor Bahru")
        };

        Customer[] customer = {
            new Customer("Zhongren", 25, 'M', "010528154210", address[0], "0125022341"),
            new Customer("Yongyue", 20, 'F', "020805274102", address[1], "0176895210")
        };

        for (int i = 0; i < customer.length; i++) {
            persons.add(customer[i]);
        }
        
        return persons;
    }
    
    public static Person EnterLogin(ArrayList<Person> persons) {
        Scanner scan = new Scanner(System.in); 
        Person currentUser = new Person();
        boolean loginValid = false;
        
        do {
            System.out.println("\n----------- Customer Login -----------");
            System.out.print("Customer Name: ");
            String customerNameInput = scan.nextLine();

            for (Person p: persons) {
                if (customerNameInput.equals(p.getName())) {
                    currentUser = p;   
                    System.out.println("You have successfully login with account.");
                    System.out.println("Welcome, " + p.getName() + ".");
                    System.out.println("");
                    loginValid = true;
                }
            }
            
            if (!loginValid) {
                System.out.println("Invalid name. Please try again!");
            }
            
        } while (loginValid != true);
        
        return currentUser;
    }
    
}
