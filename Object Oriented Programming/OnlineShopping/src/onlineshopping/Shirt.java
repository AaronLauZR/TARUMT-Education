/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package onlineshopping;

/**
 *
 * @author andre
 */
public class Shirt extends Product{
    private String shirtSize;
    private static int shirtId;
    private ShirtBrands shirtBrands;
    
    public enum ShirtBrands {
        Topman,
        Gucci,
        VanHeusen,
        PoloAssn,
    }
    
    Shirt() {
        
    }
    
    Shirt(String productName, double price, Color color, ShirtBrands shirtBrands) {
        super("T" + shirtId++, productName, price, color);
        this.shirtSize = shirtSize;
        this.shirtBrands = shirtBrands;
    }

    public String getShirtSize() {
        return shirtSize;
    }

    public void setShirtSize(String shirtSize) {
        this.shirtSize = shirtSize;
    }
    
    public String displayBrands() {
        return shirtBrands.toString();
    }
    
    public String displayProduct() {
        return String.format("%-20s %-15s", super.toString(), this.displayBrands());
    }
    
    public String toString() {
        return String.format("%-20s %-8s %-15s", super.toString(), this.shirtSize, this.displayBrands());
    }
    
}
