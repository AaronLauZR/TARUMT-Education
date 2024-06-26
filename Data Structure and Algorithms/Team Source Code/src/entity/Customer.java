package entity;

import java.util.Scanner;

public class Customer {

    private String name;
    private String contactNo; 
    //private Delivery delivery;
    
    Customer(){
        this("Tan Yee Wei","0123456789");
    }
    
    Customer(String name, String contactNo){
        this.name = name;
        //this.delivery = delivery;
        this.contactNo = contactNo;
    }
    
    public String getName() {
        return this.name;
    }

    public String getContactNo() {
        return this.contactNo;
    }
    
//    public Delivery getDelivery() {
//        return this.delivery;
//    }

    public void setName(String name) {
        this.name = name;
    }

    public void setContactNo(String contactNo) {
        this.contactNo = contactNo;
    }

//    public void setDelivery(Delivery delivery) {
//        this.delivery = delivery;
//    }
    
    @Override
    public String toString() {
        return String.format("%-20s %-10s", this.name , "(Phone No: " + this.contactNo + ")") ;
               
    }
    
        public static Customer EnterDetails(){

        boolean invalid_input = false;
        Scanner scan = new Scanner(System.in);

        Customer cust = new Customer();
        

        System.out.print("\nName: ");
        cust.setName(scan.nextLine());

        System.out.print("Contact number: ");
        cust.setContactNo(scan.nextLine());
       
        return cust;
    }
  
    //Check whether is alphabetic character or not
    public static boolean isAlpha(String s) {
        return s != null && s.matches("^[a-zA-Z]*$");
    }
    
   
}