//Author: Abdullah Khan
//Date: 03/20/2019
//Description: This class is a generic doubly linked list that implements DLListADT

public class DLList<T> implements DLListADT<T>{
	
	private DLNode<T> front; //this is the front of the list
	private DLNode<T> rear; //this is the rear of the list
	private int count; //number of elements in the list
	
	/**
	 * Method create and initialize an empty DLList 
	 * 
	 * @param n/a
	 * 
	 * @return n/a
	 * @throws n/a
	 *             
	 */
	public DLList()
	{
		//sets front and back to null and count to 0
		front = null;
		rear = null;
		count = 0;
	}
	/**
	 * Adds one node storing the given dataItem and value to the rear of the 
	 * doubly linked list
	 * 
	 * @param  dataItem, value to be added to the doubly linked list
	 */
	public void insert(T dataItem, int value)
	{
		DLNode<T> newNode = new DLNode<T>(dataItem, value); //create a new node with the parameters 
		
		//the case if the list is empty
		if (front == null)
		{
			front = newNode;
			rear = newNode;
		}
		else //the case if the list is not empty
		{
			DLNode<T> current = front; //make a temporary variable
			while (current != null)
			{
				current = current.getNext(); //iterate through the list
			}
			
			//add the node to the specified spot
			rear.setNext(newNode);
			newNode.setPrevious(rear);
			rear = newNode;
		}
		count++; //increment the count
	}

	/**
	 * Removes and returns the data item stored in the linked list with smallest
	 * associated value. Throws an EmptyListException if the list is empty.
	 * 
	 * @return T data item in the list with smallest associated value
	 */
	public T getSmallest() throws EmptyListException
	{
		if (isEmpty()) //throw exception if list is empty
		{
			throw new EmptyListException("Cannot get smallest value in list because the list is empty!");
		}
		
		//create temporary variable and a variable for the smallest node
		DLNode<T> current = front;
		DLNode<T> min = current; 
		
		//iterate through the list and find the smallest variable
		while(current != null)
		{
			if (min.getValue() > current.getValue())
			{
				min = current; //if a smaller value is found make it equal to minimum
			}
			current = current.getNext(); //iterate through the list
		}
		
		if (min == front) //in case the minimum is on the front
		{
			front = front.getNext(); //remove the node
			if (front != null)
			{
				front.setPrevious(null);
			}
		}
		else //in case the minimum is not on the front
		{
			min.getPrevious().setNext(min.getNext());
			
			if (min == rear) //check is the minimum is on the back
			{
				rear = min.getPrevious(); 
				if (rear != null)
				{
					rear.setNext(null);
				}
			}
			else
			{
				min.getNext().setPrevious(min.getPrevious());
			}
		}
		count--; //decrement the counter
		return min.getData(); //return the removed node
	}

	/**
	 * Changes the value associated to the given dataItem to the new value. Throws an  
	 * InvalidDataItemException if no node of the list stores the given dataItem.
	 * 
	 * @param dataItem whose value is to be changed
	 * @param newValue new value for this dataItem
	 */
	public void changeValue(T dataItem, int newValue) throws InvalidDataItemException
	{
		DLNode<T> current = front;
		
		while(current != null && !dataItem.equals(current.getData()))
		{
			current = current.getNext(); //iterate through the list
		}
		
		if (current == null) //if node not found throw an exception
		{
			throw new InvalidDataItemException("The data item you are trying to change does not exist!");
		}
		
		current.setValue(newValue); //change the value if the node is found
	}

	/**
	 * Returns the value of the given dataItem. Throws an InvalidDataItemException if
	 * no node of the list stores the given dataItem.
	 * 
	 * @param dataItem whose value is being sought
	 * @return value of this dataItem
	 */
	public int getDataValue(T dataItem) throws InvalidDataItemException
	{
		DLNode<T> current = front; //create temporary variable
		
		while(current != null && !dataItem.equals(current.getData()))
		{
			current = current.getNext(); //iterate through the list until either null or node is found
		}
		
		if (current == null) //throw exception if value not found
		{
			throw new InvalidDataItemException("You are searching for a data item that does not exist in the list!");
		}
		
		return current.getValue(); //return the value that is searched for
	}
	
	/**
	 * Returns true if this list is empty.
	 * 
	 * @return true if this list is empty, false otherwise
	 */
	public boolean isEmpty()
	{
		return (count == 0); //if count is 0 - is empty
	}

	/**
	 * Returns the number of dataItems in this list.
	 * 
	 * @return int number of dataItems in this list
	 */
	public int size()
	{
		return count; //return the size 
	}

	/**
	 * Returns a string representation of this list.
	 * 
	 * @return String representation of this list
	 */
	public String toString()
	{
		String result = "List: "; //create a string variable 
		
		DLNode<T> current = front; //create a temporary variable
		
		while (current != null)
		{
			result = result + current.getData().toString() + "," + current.getValue() + ";"; //iterate through the list and add the nodes to the string in the provided format
			current = current.getNext();
		}
		
		return result; //return the resulting string
	}
}
