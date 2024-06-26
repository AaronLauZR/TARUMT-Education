/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Interface.java to edit this template
 */
package StackADT;

/**
 *
 * @author Window
 */
public interface StackInterface<T> {
    public void insert(T newInput);
    
    public void undo();
    
    public T undoReturn();
    
    public boolean emptyStack();
    
    public int countLength();
    
    public StackLibrary clearStack(StackLibrary stack);
    
    public void viewreverseStack(StackLibrary stack);
}
