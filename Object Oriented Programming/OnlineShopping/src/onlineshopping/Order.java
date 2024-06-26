package onlineshopping;

import java.text.DecimalFormat;
import java.util.List;

public class Order {
    private static final DecimalFormat df = new DecimalFormat("0.00");
    
    List<OrderLine> orderLine;
    private static double shippingFee = 10.0;
    private double discount;

    public Order() {
    }
    
    public Order(List<OrderLine> orderLine) {
        this.orderLine = orderLine;
    }
  
    public List<OrderLine> getOrderLine() {
        return orderLine;
    }

    public void setOrderLine(List<OrderLine> orderLine) {
        this.orderLine = orderLine;
    }

    public static double getShippingFee() {
        return shippingFee;
    }

    public static void setShippingFee(double shippingFee) {
        Order.shippingFee = shippingFee;
    }

    public double getDiscount() {
        return discount;
    }

    public void setDiscount(double discount) {
        this.discount = discount;
    }
    
    public double calcTotal() {
        double total = 0.0;
        
        for (OrderLine order: this.orderLine) {
            //total += order.getQuantity() * order.getProductPrice();
            total += order.calcSubTotal();
        }
        return total;
    }
     
    public double calcDiscount(){
        
        if(calcTotal() > 500){
            discount = calcTotal() * 0.1;
            if(discount > 100){
                discount = 100.0;
            }
        }
        else if(calcTotal() > 300){
            discount = calcTotal() * 0.05;
        }
        else{
            discount = 0;
        }
        return discount;
    }
    
    public double calcGrandTotal(){ 
       return this.calcTotal() - this.getDiscount() + Order.shippingFee;
    }
    
    public String toString() {
        String output = "";
        
        System.out.println("\n======================================= Order List ========================================");
        System.out.format("%-3s %-18s %-9s %-9s %-8s %-15s %-10s %-9s", "ID", "Name", "Price(RM)", "Color", "Size", "Brand", "Quantity", "Subtotal(RM)" + "\n");
        System.out.println("-------------------------------------------------------------------------------------------");
        
        for (OrderLine order: this.orderLine) {
            output += String.format("%-30s %-10s %-9s", order.getProduct(), order.getQuantity(), df.format(order.calcSubTotal()));
            output += "\n";
        }
        
        output += "\n===========================================================================================\n";
        output += "Total Price : RM " + df.format(this.calcTotal()) + "\n" + 
                "Shipping Fee: RM " + df.format(Order.shippingFee) + "\n" +
                "Discount    : RM " + df.format(this.calcDiscount()) + "\n" +
                "Grand Total : RM " + df.format(this.calcGrandTotal()) + "\n"; 
        return output; 
        
    }
    
}





