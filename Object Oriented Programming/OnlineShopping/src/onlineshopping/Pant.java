/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package onlineshopping;

/**
 *
 * @author andre
 */
public class Pant extends Product{
    private String pantSize;
    private static int pantId;
    private PantBrands pantBrands;
    
    public enum PantBrands {
        Levi,
        CalvinKlein,
        PepeJeans,
        LeeJeans,
        Wrangler
    }
    
    Pant() {
        
    }
    
    Pant(String productName, double price, Color color, PantBrands pantBrands) {
        super("P" + pantId++, productName, price, color);
        this.pantSize = pantSize;
        this.pantBrands = pantBrands;
        
    }

    public String getPantSize() {
        return pantSize;
    }

    public void setPantSize(String pantSize) {
        this.pantSize = pantSize;
    }
    
    public String displayBrands() {
        return pantBrands.toString();
    }
    
    public String displayProduct() {
        return String.format("%-20s %-15s", super.toString(), this.displayBrands());
    }
    
    public String toString() {
        return String.format("%-20s %-8s %-15s", super.toString(), this.pantSize, this.displayBrands());
    }
    
}
