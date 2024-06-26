package adt;

/**
 * QueueInterface.java An interface for the ADT queue with an additional
 * method that returns an iterator to the queue.
 * 
 * @param <T>
 * @author: Yong Yue
 **/

  public interface QueueInterface<T> {

  public void enterQueue(T newEntry);

  public T removeQueue();

  public T getFront();

  public boolean isEmpty();

  public void clear();
  
  public void displayAll();
  
  public int initialQueueNum();
  
}

