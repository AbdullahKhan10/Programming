//Author: Abdullah Khan
//Date: 03/20/2019
//Description: This class is the node in the doubly linked list

public class DLNode<T> {
	
	private T dataItem; //is the generic data stored in the node
	private int value; //is the value stored in the node
	private DLNode<T> next; //reference to next node 
	private DLNode<T> previous; //reference to previous node
	
	/**
	 * Method create and initialize a DLNode object
	 * 
	 * @param dataItem, value
	 * data: set the data in the node to the given data
	 * value: is the value stored in node
	 * 
	 * @return n/a
	 * @throws n/a
	 *             
	 */
	public DLNode(T dataItem, int value)
	{
		this.dataItem = dataItem;
		this.value = value;
		next = null;
		previous = null;
	}
	
	/**
	 * Method to get the value
	 * 
	 * @param n/a
	 * 
	 * @return value associated with the node
	 * @throws n/a
	 *             
	 */
	public int getValue()
	{
		return value;
	}
	
	/**
	 * Method to get the data
	 * 
	 * @param n/a
	 * 
	 * @return data associated with the node
	 * @throws n/a
	 *             
	 */
	public T getData()
	{
		return dataItem;
	}
	
	/**
	 * Method to get the next node
	 * 
	 * @param n/a
	 * 
	 * @return next node after the current node
	 * @throws n/a
	 *             
	 */
	public DLNode<T> getNext()
	{
		return next;
	}
	
	/**
	 * Method to get the previous node
	 * 
	 * @param n/a
	 * 
	 * @return previous node after the current node
	 * @throws n/a
	 *             
	 */
	public DLNode<T> getPrevious()
	{
		return previous;
	}
	
	/**
	 * Method to set the data
	 * 
	 * @param dataItem
	 * dataItem: is the parameter data
	 * 
	 * @return n/a
	 * @throws n/a
	 *             
	 */
	public void setData(T dataItem)
	{
		this.dataItem = dataItem;
	}
	
	/**
	 * Method to set the value
	 * 
	 * @param value
	 * value: is the integer type of value
	 * 
	 * @return n/a
	 * @throws n/a
	 *             
	 */
	public void setValue(int value)
	{
		this.value = value;
	}
	
	/**
	 * Method to set next
	 * 
	 * @param next
	 * next: next node in list
	 * 
	 * @return n/a
	 * @throws n/a
	 *             
	 */
	public void setNext(DLNode<T> next)
	{
		this.next = next;
	}
	
	/**
	 * Method to set previous
	 * 
	 * @param previous
	 * previous: this is the previous node
	 * 
	 * @return n/a
	 * @throws n/a
	 *             
	 */
	public void setPrevious(DLNode<T> previous)
	{
		this.previous = previous;
	}	
}
