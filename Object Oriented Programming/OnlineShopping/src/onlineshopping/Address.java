/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package onlineshopping;

/**
 *
 * @author Windows10
 */
public class Address {
    
    private String homeNumber;
    private int poscode;
    private String street;
    private String city;
    private String state;
    
    Address() {
        this("13520",53300,"Jalan Maju","Kuala Lumpur","Selangor");
    }
    
    Address(String homeNumber, int poscode, String street, String city, String state) {
        this.homeNumber = homeNumber;
        this.poscode = poscode;
        this.street = street;
        this.city = city;
        this.state = state;
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
    
    @Override
    public String toString() {
        return homeNumber + ", " + street + ", \n" 
                + "         " + city + ", " + poscode + ", \n"
                + "         " + state + ".";
    }
    
}
