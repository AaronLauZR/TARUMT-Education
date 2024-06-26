/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package adt;

import java.io.Serializable;

/**
 *
 * @author Window
 */
public class StackLibrary<T> implements StackInterface<T>, Serializable{
    
    private T[] storage;
    private int stackLength; 
    private static int capacity = 0;
    
    public StackLibrary() {
        this(capacity);
    }
    
    public StackLibrary(int capacity) {
        storage = (T[]) new Object[capacity];
    }
    
    public void insert(T newInput) {
        stackLength++;
        
        if (stackLength < storage.length) {
            storage[stackLength - 1] = newInput;
        }
    }
     
    public T undo() {
        T topValue = null;
        
        if (!emptyStack()) {
            topValue = storage[stackLength - 1];
            storage[stackLength - 1] = null;
            stackLength--;
        }
        return topValue;
    }
    
    public T undoReturn() {
        T topValue = null;
        
        if (!emptyStack()) {
            topValue = storage[stackLength - 1];
            storage[stackLength - 1] = null;
            stackLength--;
        }
        
        return topValue;
    }
       
    public boolean emptyStack() {
        return stackLength < 0;
    }
    
    public int countLength() {
        return stackLength;
    }
    
    public StackLibrary clearStack(StackLibrary stack) {
        for (int i = 0; i < stack.countLength(); i++) {
           stack.undo();
        }
        
        return stack;
    }
    
    public void viewreverseStack(StackLibrary stack) {
        for (int i = 0; i < stack.countLength(); i++) {
            System.out.println(storage[i]);
        }  
    }
}