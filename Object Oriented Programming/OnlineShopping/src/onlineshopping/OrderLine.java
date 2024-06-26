/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package onlineshopping;

import java.text.DecimalFormat;

/**
 *
 * @author andre
 */
public class OrderLine {
    private static final DecimalFormat df = new DecimalFormat("0.00");
    
    private int quantity;
    private Product product;
    
    OrderLine() {
        
    }
    
    OrderLine(int quantity, Product product) {
        this.quantity = quantity;
        this.product = product;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public Product getProduct() {
        return product;
    }

    public void setProduct(Product product) {
        this.product = product;
    }
    
    public double getProductPrice() {
        return product.getPrice();
    }
    
    public double calcSubTotal(){
        double subtotal = 0.0;
        
        subtotal = this.getQuantity() * this.getProductPrice();

        return subtotal;
    }
    
    public String toString() {
        return String.format("%-30s %-9s %-9s", this.product.toString(), this.quantity, df.format(this.calcSubTotal()));
    }
}
