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
public abstract class Product{
    private static final DecimalFormat df = new DecimalFormat("0.00");
    
    private String productNo;
    private String productName;
    private double price;
    private String color;
    
    public enum Color{
        Red,
        Blue,
        Green,
        Yellow,
        White,
        Black
    }
    
    Product() {
        //this("", "", 0.0,"","");
    }

    public Product(String productNo, String productName, double price, Color color) {
        this.productNo = productNo;
        this.productName = productName;
        this.price = price;
        this.color = color.toString();
    }

    public String getProductNo() {
        return productNo;
    }
    
    public String getProductName() {
        return productName;
    }
    
    public double getPrice() {
        return price;
    }
    
    public String getColor() {
        return color;
    }
    
    public void setProductName(String productName) {
        this.productName = productName;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public void setColor(String color) {
        this.color = color;
    }
    
    public abstract String displayBrands();
    
    public String displayProduct() {
        return String.format("%-3s %-18s %-9s %-9s", this.productNo, this.productName, df.format(this.price), this.color);
    }

    @Override
    public String toString() {
        return String.format("%-3s %-18s %-9s %-9s", this.productNo, this.productName, df.format(this.price), this.color);
    }

}

