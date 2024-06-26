/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package adt;
import adt.MapInterface;

/**
 * HashedDictionary.java - A class that implements the ADT dictionary by using
 * hashing. - The dictionary is not sorted and has distinct search keys.
 *
 * @author Frank M. Carrano (Modified)
 * @version 2.0
 */
public class HashMap<K, V> implements MapInterface<K, V> {

  private TableEntry<K, V>[] hashTable;					     // dictionary entries
  private int numberOfEntries;
  // private int locationsUsed;	         // number of table locations not null
  private static final int DEFAULT_SIZE = 8; 		   // must be prime 

  public HashMap() {
    this(DEFAULT_SIZE); // call next constructor
  } // end default constructor

  public HashMap(int tableSize) {
    hashTable = new TableEntry[tableSize];
    numberOfEntries = 0;
    // locationsUsed = 0;
  } // end constructor

  public String toString() {
    String outputStr = "";
    for (int index = 0; index < hashTable.length; index++) {
      outputStr += String.format("%4d. ", index);
      if (hashTable[index] == null) {
        outputStr += "null " + "\n";
      } else if (hashTable[index].isRemoved()) {
        outputStr += "notIn " + "\n";
      } else {
        outputStr += hashTable[index].getKey() + " " + hashTable[index].getValue() + "\n";
      }
    } // end for
    outputStr += "\n";
    return outputStr;
  } 
// -------------------------

  // 20.14
  public V put(K key, V value) {
    V oldValue; // value to return

    if (isFull()) {
      rehash(); // increase capacity --> it is called automatically when the no of entry exceed its capacity
    }

    int index = getHashIndex(key);

    if ((hashTable[index] == null) || hashTable[index].isRemoved()) { // key not found, so insert new entry
      hashTable[index] = new TableEntry<K, V>(key, value);
      numberOfEntries++;
//	    locationsUsed++;
      oldValue = null;
    } else { // key found; get old value for return and then replace it
      oldValue = hashTable[index].getValue();
      hashTable[index].setValue(value);
    } // end if

    return oldValue;
  } // end add

  // 20.12
  public V remove(K key) {
    V removedValue = null;

    int index = getHashIndex(key);
    index = locate(index, key);

    if (index != -1) {
      // key found; flag entry as removed and return its value
      removedValue = hashTable[index].getValue();
      hashTable[index].setToRemoved();
      numberOfEntries--;
    } // end if
    // else not found; result is null

    return removedValue;
  } // end remove

  // 20.11
  public V getValue(K key) {
    V result = null;

    int index = getHashIndex(key);
    index = locate(index, key);

    if (index != -1) {
      result = hashTable[index].getValue(); // key found; get value
    }
		// else not found; result is null

    return result;
  } // end getValue

  // 20.13
  private int locate(int index, K key) {
    if (hashTable[index] == null || !key.equals(hashTable[index].getKey())) {
      return -1;
    } else {
      return index;
    }
  } // end locate

  public boolean contains(K key) {
    return getValue(key) != null;
  } // end contains

  public boolean isEmpty() {
    return numberOfEntries == 0;
  } // end isEmpty

  public boolean isFull() {
    return false;
  } // end isFull

  public int getSize() {
    return numberOfEntries;
  } // end getSize

  public final void clear() {
    for (int index = 0; index < hashTable.length; index++) {
      hashTable[index] = null;
      numberOfEntries--;
    }

    
    // locationsUsed = 0;
  } // end clear

  private int getHashIndex(K key) {
    int hashIndex = key.hashCode() % hashTable.length;
    if (hashIndex < 0) {
      hashIndex = hashIndex + hashTable.length;
    } 
    return hashIndex;
  } 

  /**
   * Task: Increases the size of the hash table to twice its old size.
   */
  private void rehash() {
    TableEntry<K, V>[] oldTable = hashTable;
    int oldSize = hashTable.length;
    int newSize = 2 * oldSize;
    hashTable = new TableEntry[newSize]; 
    for (int index = 0; index < oldSize; index++) {
      if ((oldTable[index] != null) && oldTable[index].isIn()) {
        put(oldTable[index].getKey(), oldTable[index].getValue());
      }
    } 
  } 

  private class TableEntry<S, T> {

    private S key;
    private T value;
    private boolean inTable; // true if entry is in table

    private TableEntry(S searchKey, T dataValue) {
      key = searchKey;
      value = dataValue;
      inTable = true;
    } // end constructor

    private S getKey() {
      return key;
    } // end getKey

    private T getValue() {
      return value;
    } // end getValue

    private void setValue(T newValue) {
      value = newValue;
    } // end setValue

    private boolean isIn() {
      return inTable;
    } // end isIn

    private boolean isRemoved() { // opposite of isIn
      return !inTable;
    } // end isRemoved

    // state = true means entry in use; false means entry not in use, ie deleted
    private void setToRemoved() {
      key = null;
      value = null;
      inTable = false;
    } // end setToRemoved

    private void setToIn() { // not used
      inTable = true;
    } // end setToIn
  } // end TableEntry
} // end HashedDictionary
