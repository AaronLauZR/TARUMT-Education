/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package onlineshopping;

/**
 *
 * @author andre
 */
public class Shoe extends Product{
    private int shoeSize;
    private static int shoeId;
    private ShoeBrands shoeBrands;
    
    public enum ShoeBrands {
        Nike,
        Adidas,
        Puma,
        NewBalance,
    }
    
    Shoe() {
        
    }
    
    Shoe(String productName, double price, Color color, ShoeBrands shoeBrands) {
        super("S" + shoeId++, productName, price, color);
        this.shoeSize = shoeSize;
        this.shoeBrands = shoeBrands;
    }

    public int getShoeSize() {
        return shoeSize;
    }

    public void setShoeSize(int shoeSize) {
        this.shoeSize = shoeSize;
    }
    
    @Override
    public String displayBrands() {
        return shoeBrands.toString();
    }
    
    public String displayProduct() {
        return String.format("%-20s %-15s", super.toString(), this.displayBrands());
    }
    
    public String toString() {
        return String.format("%-20s %-8s %-15s", super.toString(), this.shoeSize, this.displayBrands());
    }
    
}
