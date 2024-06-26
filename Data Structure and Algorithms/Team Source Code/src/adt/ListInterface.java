/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Interface.java to edit this template
 */
package adt;

/**
 *
 * @author andre
 */
public interface ListInterface<T> {
    public boolean insert(T newEntry);
    
    public boolean insert(int newLocation, T newEntry);
    
    public int length();
            
    public int fullLength();
    
    public void clear();
    
    public boolean replace(int givenLocation, T newEntry);
    
    public T getEntry(int givenLocation);
    
    public boolean contains(T anEntry);
    
    public int getNumberOfEntries();
    
    public boolean isEmptyList();
    
    public boolean isFullList();
    
    public T reverse(ArrayList<T> newEntry);
    
    public boolean replaceAndMoveToLast(int givenLocation, T newEntry);
    
    public void exceedLength(int length);
    
    public T delete(int givenLocation);
    
}
