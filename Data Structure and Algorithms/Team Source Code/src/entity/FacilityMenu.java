/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package entity;

import java.text.DecimalFormat;

/**
 *
 * @author THENG CHIA CHIA
 */
public class FacilityMenu {
    private static final DecimalFormat df = new DecimalFormat("0.00");
    
    private String id;
    private String type;
    private double price;
    private int qty;
    
    public FacilityMenu() {
        this("TH1", "Round Table", 10.50);
    }

    public FacilityMenu(String ID, String Type, double Price) {
        this.id = ID;
        this.type = Type;
        this.price = Price;
    }

    public static DecimalFormat getDf() {
        return df;
    }

    public String getId() {
        return id;
    }

    public String getType() {
        return type;
    }

    public double getPrice() {
        return price;
    }

    public int getQty() {
        return qty;
    }

    public void setId(String id) {
        this.id = id;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public void setQty(int qty) {
        this.qty = qty;
    }
    
    public double calcSubTotal() {
        return this.price * this.qty;
    }

    public String displayMenu() {
        return String.format("%-6s %-20s %-2s %-6s", this.id, this.type, "RM", df.format(this.price));
    }
    
    @Override
    public String toString() {
        return String.format("%-6s %-20s %-2s %-12s %-10s %-2s %-6s", this.id, this.type, "RM", df.format(this.price), this.qty, "RM", df.format(this.calcSubTotal()));
    }
}