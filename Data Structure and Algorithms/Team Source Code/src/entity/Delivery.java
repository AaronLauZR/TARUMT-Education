package entity;

import java.util.Scanner;

public class Delivery {
    
    private String homeNumber;
    private int poscode;
    private String street;
    private String city;
    private String state;
    private String DelDate;
    private String DelTime;

    public Delivery() {
    }

    public Delivery(String homeNumber, int poscode, String street, String city, String state, String DelDate, String DelTime) {
        this.homeNumber = homeNumber;
        this.poscode = poscode;
        this.street = street;
        this.city = city;
        this.state = state;
        this.DelDate = DelDate;
        this.DelTime = DelTime;
    }
    

    public String getHomeNumber() {
        return homeNumber;
    }

    public void setHomeNumber(String homeNumber) {
        this.homeNumber = homeNumber;
    }

    public int getPosscode() {
        return poscode;
    }

    public void setPosscode(int poscode) {
        this.poscode = poscode;
    }

    public String getStreet() {
        return street;
    }

    public void setStreet(String street) {
        this.street = street;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getState() {
        return state;
    }

    public void setState(String state) {
        this.state = state;
    }
    
    public String getDelDate() {
        return DelDate;
    }

    public void setDelDate(String DelDate) {
        this.DelDate = DelDate;
    }

    public String getDelTime() {
        return DelTime;
    }

    public void setDelTime(String DelTime) {
        this.DelTime = DelTime;
    }

    @Override
    public String toString() {
        return "Delivery Address: " + homeNumber + ", " + street + ", "
                + city + ", " + poscode + ", "
                + state + "." +
                "\nDelivery Date & Time: " + this.DelDate + "  " + this.DelTime + "\n";
    }

    public static Delivery EnterDeliveryDetails(){
        boolean invalid_input = true;
        Scanner address = new Scanner(System.in);
        Delivery del = new Delivery();
        
        System.out.print("Delivery Address:    ");
        
        System.out.printf("|Home Number = ");
        del.setHomeNumber(address.nextLine());
        
        System.out.printf("%31s","|Street = ");
        del.setStreet(address.nextLine());
        
        System.out.printf("%29s","|City = ");
        del.setCity(address.nextLine());
             

        do{
            System.out.printf("%32s","|Poscode = ");
            try{
                del.setPosscode(address.nextInt());
                invalid_input = false;
                
            }catch(Exception e) {
                    System.out.println("Invalid poscode. Please try again!");
                    address.next();
                    invalid_input = true;
            }       
         }while(invalid_input != false);
        
        address.nextLine();
        
        System.out.printf("%30s","|State = ");
        del.setState(address.nextLine());
        
        System.out.print("Delivery Date: ");
        del.setDelDate(address.nextLine());
        
        System.out.print("Delivery Time: ");
        del.setDelTime(address.nextLine());
            
        return del;
    }
}
