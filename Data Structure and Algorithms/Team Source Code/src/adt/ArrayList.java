/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package adt;

import java.io.Serializable;

/**
 *
 * @author andre
 */
public class ArrayList<T> implements ListInterface<T>, Serializable {
    
    private T[] array;
    
    private int count;
    
    private static int DEFAULT_CAPACITY = 5;
    
    public ArrayList() {
        this(DEFAULT_CAPACITY);
    }
    
    public ArrayList(int initialCapacity) {
        count = 0;
        array = (T[]) new Object[initialCapacity];
    }

    public boolean insert(T newEntry) {

        array[count] = newEntry;
        count++;
        return true;
    }
    
    public boolean insert(int newLocation, T newEntry) {
        boolean isSuccessful = true;
        
        if ((newLocation >= 1) && (newLocation <= count + 1)) {
            adjustLocation(newLocation);
            array[newLocation - 1] = newEntry;
            count++;
        }else {
            isSuccessful = false;
        }
        
        return isSuccessful;
    }
    
    private void adjustLocation(int newLocation) {
        int newIndex = newLocation - 1;
        int lastIndex = count - 1;

        for (int index = lastIndex; index >= newIndex; index--) {
            array[index + 1] = array[index];
        }
    }
    
    public int length() {
        return count;
    }
    
    public int fullLength() {
        return array.length;
    }
    
    public void clear() {
        count = 0;
    }
    
    public boolean replace(int givenLocation, T newEntry) {
        boolean isSuccessful = true;
        
        if ((givenLocation >= 1) && (givenLocation) <= count) {
            array[givenLocation - 1] = newEntry;
        }else {
            isSuccessful = false;
        }
        
        return isSuccessful;
        
    }
    
    public T getEntry(int givenLocation) {
        T result = null;
        
        if ((givenLocation >= 1) && (givenLocation) <= count) {
            result = array[givenLocation - 1];
        }
        
        return result;
    }
    
    public boolean contains(T anEntry) {
        boolean found = false;
        
        for (int index = 0; !found && (index < count); index++) {
            if (anEntry.equals(array[index])) {
                found = true;
            }        
        }
        
        return found;
    }
    
    public int getNumberOfEntries() {
        return count;
    }
    
    public boolean isEmptyList() {
        return count == 0;
    }
    
    
    public boolean isFullList() {
        return count == array.length;
    }
    
    public String toString() {
        String output = "";
        for (int index = 0; index < count; index++) {
            output += array[index] + "\n";
        }
        
        return output;
    }
    
    public void exceedLength(int length) {
        T[] oldArray = array;
        
        if (length >= DEFAULT_CAPACITY) {
            array = (T[]) new Object[2 * length];
            
            for (int i = 0; i < oldArray.length; i++) {
                array[i] = oldArray[i];
            }  
        }
    }

    public T reverse(ArrayList<T> newEntry) {
        int length = newEntry.length();
        T temp;
        
        for (int i = 0; i < length / 2; i++) {
            temp = array[i];
            array[i] = array[length - i - 1];
            array[length - i - 1] = temp;
        }

        return (T)array;
    }
    
    public boolean replaceAndMoveToLast(int givenLocation, T newEntry) {
        boolean isSuccessful = false;
        
        int replaceIndex = givenLocation - 1;
        int lastIndex = count - 1;
        T replace = null;
        
        if (givenLocation >= 1 && givenLocation <= count) {
            replace = newEntry;
            
            if (givenLocation < count) {
                removeGap(givenLocation);
            }
            isSuccessful = false;
        }
        
        array[lastIndex] = replace;
        return isSuccessful;

    }
    
    private void removeGap(int givenLocation) {
        int removeIndex = givenLocation - 1;
        int lastIndex = count - 1;
        
        for (int index = removeIndex; index <= lastIndex; index++) {
            array[index] = array[index + 1];
        }
    }
    
    public T delete(int givenLocation) {
        if (givenLocation < count) {
            T obj = array[givenLocation];
            int temp = givenLocation;
            array[givenLocation] = null;
            
            while (temp < count) {
                array[temp] = array[temp + 1];
                array[temp + 1] = null;
                temp++;
            }
            
            count--;
            return obj;
        } else {
            throw new ArrayIndexOutOfBoundsException();
        }
    }
    
}
