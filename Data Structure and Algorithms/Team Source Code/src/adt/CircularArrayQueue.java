package adt;

public class CircularArrayQueue<T> implements QueueInterface<T> {

  private T[] array; // circular array of array entries and one unused location
  private int frontIndex;
  private int backIndex;
  private static final int DEFAULT_CAPACITY = 5;

  public CircularArrayQueue() {
    this(DEFAULT_CAPACITY);
  }

  public CircularArrayQueue(int initialCapacity) {
    array = (T[]) new Object[initialCapacity + 1];
    frontIndex = 0;
    backIndex = initialCapacity;
  }

  @Override
  public void enterQueue(T newEntry) {
    if (!isArrayFull()) {
      backIndex = (backIndex + 1) % array.length;
      array[backIndex] = newEntry;
    }
    else{
        doubleArray();
        backIndex = (backIndex + 1) % array.length;
        array[backIndex] = newEntry;
    }
  }
  
    public int initialQueueNum(){
        int initialQueueNum = 0;
        
        return initialQueueNum = backIndex - frontIndex +1;
    }

  @Override
  public T getFront() {
    T front = null;

    if (!isEmpty()) {
      front = array[frontIndex];
    }

    return front;
  }

  @Override
  public T removeQueue() {
    T front = null;

    if (!isEmpty()) {
      front = array[frontIndex];
      array[frontIndex] = null;
      frontIndex = (frontIndex + 1) % array.length;
    }

    return front;
  }

  @Override
  public boolean isEmpty() {
    return frontIndex == ((backIndex + 1) % array.length);
  }

  @Override
  public void clear() {
    if (!isEmpty()) {
      for (int index = frontIndex; index != backIndex; index = (index + 1) % array.length) {
        array[index] = null;
      }
      array[backIndex] = null;
    }

    frontIndex = 0;
    backIndex = array.length - 1;
  }

  private boolean isArrayFull() {
    return frontIndex == ((backIndex + 2) % array.length);
  }
  
  @Override
    public void displayAll() {
    /* Function to display status of Circular Queue */
    int i;
    if (isEmpty()) {
      System.out.println("Empty Queue");
    } else {
      for (i = frontIndex; i != backIndex; i = (i + 1) % array.length)
        System.out.println(array[i] + " ");
      System.out.println(array[i] + "\n");
    }
  }
    
    private void doubleArray() {
    T[] oldArray = array;
    array = (T[]) new Object[2 * oldArray.length];  
    
      for (int index = 0; index < oldArray.length; index++){ 
          array[index] = oldArray[index];
      }
  }

    public T printOneByOne(int position) {
        T printElement = null;
    
        if (!isEmpty()) {  
            printElement = array[position];
        }
        return printElement;
    }

}
