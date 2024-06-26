/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package onlineshopping;

/**
 *
 * @author admin
 */
public class Customer extends Person implements Comparable{
    private int customerID;
    //private userAccount account;
    private static int nextCustomerID = 1001;
    
    Customer(){
        super();
    }
    
    Customer(String name, int age, char gender, String ic, Address address, String contactNo){
        super(name, age, gender, ic, address, contactNo);
        this.customerID = nextCustomerID++;
    }

    public int getCustomerID() {
        return customerID;
    }

    public void setCustomerID(int customerID) {
        this.customerID = customerID;
    }

    public static int getNextCustomerID() {
        return nextCustomerID;
    }

    public static void setNextCustomerID(int nextCustomerID) {
        Customer.nextCustomerID = nextCustomerID;
    }
    
    public int compareTo(Object obj) {
        
        Customer other = (Customer) obj;
        if (this.getName().equals(other.getName())) {
            return 1;
        }else{
            return 0;
        }
    }

    @Override
    public String toString() {
        return "Customer ID: " + this.customerID + "\n" +super.toString();
    }
    
}
