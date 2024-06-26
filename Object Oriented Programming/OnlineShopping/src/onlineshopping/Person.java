/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package onlineshopping;

/**
 *
 * @author admin
 */
public class Person {
    private String name;
    private int age;
    private char gender;
    private String ic;
    private Address address;
    private String contactNo; 
    
    Person(){
        this("Tan Yee Wei", 25,'F', "12341254612", new Address(),"0123456789");
    }
    
    Person(String name, int age, char gender, String ic, Address address, String contactNo){
        this.name = name;
        this.age = age;
        this.gender = gender;
        this.ic = ic;
        this.address = address;
        this.contactNo = contactNo;
    }
    
    public String getName() {
        return this.name;
    }

    public int getAge() {
        return this.age;
    }

    public char getGender() {
        return this.gender;
    }

    public String getIc() {
        return this.ic;
    }

    public Address getAddress() {
        return this.address;
    }

    public String getContactNo() {
        return this.contactNo;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void setGender(char gender) {
        this.gender = gender;
    }

    public void setIc(String ic) {
        this.ic = ic;
    }

    public void setAddress(Address address) {
        this.address = address;
    }

    public void setContactNo(String contactNo) {
        this.contactNo = contactNo;
    }

    @Override
    public String toString() {
        return "Name: " + this.name + "\nAge: " + this.age + "\nGender: " + this.gender + "\nIC Number: " + this.ic + "\nAddress: " + this.address + "\nContact No: " + this.contactNo;
    }
   
}