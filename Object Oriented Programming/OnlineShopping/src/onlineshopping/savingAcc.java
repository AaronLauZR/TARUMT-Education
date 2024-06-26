package onlineshopping;

public class savingAcc extends BankAccount{
    private String password;

    savingAcc(){
        this(0,0,"###");
    }
    savingAcc(int num,double bal,String pass){
        super(num,bal);
        this.password=pass;
    }
    public String getPass(){
        return password;
    }
    
}
