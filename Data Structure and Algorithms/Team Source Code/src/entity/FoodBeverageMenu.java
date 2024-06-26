/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package entity;

import java.text.DecimalFormat;

/**
 *
 * @author andre
 */
public class FoodBeverageMenu {
    
    private static final DecimalFormat df = new DecimalFormat("0.00");
    
    private String ID;
    private String Name;
    private double Price;
    private int Pax;
    private String Remark;
    
    public FoodBeverageMenu() {
        this("", "", 0.00);
    }

    public FoodBeverageMenu(String ID, String Name, double Price) {
        this.ID = ID;
        this.Name = Name;
        this.Price = Price;
    }

    public String getID() {
        return ID;
    }

    public void setID(String ID) {
        this.ID = ID;
    }

    public String getName() {
        return Name;
    }

    public void setName(String Name) {
        this.Name = Name;
    }

    public double getPrice() {
        return Price;
    }

    public void setPrice(double Price) {
        this.Price = Price;
    }

    public int getPax() {
        return Pax;
    }

    public void setPax(int Pax) {
        this.Pax = Pax;
    }

    public String getRemark() {
        return Remark;
    }

    public void setRemark(String Remark) {
        this.Remark = Remark;
    }
    
    public double calcSubTotal() {
        return this.Price * this.Pax;
    }
    
    public String displayMenu() {
        return String.format("%-12s %-18s %-2s %-11s", this.ID, this.Name, "RM", df.format(this.Price));
    }

    @Override
    public String toString() {
        return String.format("%-4s %-18s %-2s %-13s %-10s %-20s %-2s %-8s", this.ID, this.Name, "RM", df.format(this.Price), Pax, Remark, "RM", df.format(calcSubTotal()));
    }
    
}
