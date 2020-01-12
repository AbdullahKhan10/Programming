//Author: Abdullah Khan
//Date: 02/22/2019
//Description: This class implements an array stack of generic type with methods push, pop, peek

public class ArrayStack<T> implements ArrayStackADT<T>{
	
	/**
	 * This is the array that contains all the elements
	 */
	private T[] stack;
	
	/**
	 * This is the variable that contains the size of array stack
	 */
	private int top;
	
	  /**  Constructor: This initializes the array stack to default capacity
	   *   @param n/a
	   */
	public ArrayStack()
	{
		stack = (T[]) (new Object[20]); //set stack to size 20
		top = -1; //default set to -1
	}
	
	  /**  Constructor: This initializes the array stack to given capacity
	   *   @param initialCapacity
	   *   initialCapacity: is the size of the array stack
	   */
	public ArrayStack(int initialCapacity)
	{
		stack = (T[]) (new Object[initialCapacity]); //set stack to initialCapacity
		top = -1; //default set to -1 
	}
	
	  /**  Adds one element to the top of this stack. 
	   *   @param dataItem data item to be pushed onto stack
	   */
	public void push(T dataItem)
	{
		if (top == stack.length - 1) //if stack is a certain size 
		{
			expandCapacity(); //then expand the size of the stack depending
		}
		
		top++; //increase the stack size
		stack[top] = dataItem; //set the top of the stack to dataItem
	}
	
	  /**  Removes and returns the top element from this stack. 
	   *   @return T data item removed from the top of the stack
	   *   @exception throws EmptyStackException if the stack is empty
	   */
	public T pop() throws EmptyStackException
	{
		if (isEmpty()) //if the stack is empty
		{
			throw new EmptyStackException("pop"); //throw this exception
		}
		
		T result = stack[top]; //this result variable is going to be returned at the end
		stack[top] = null; //top of the stack is set to null
		top--; //decrease size of stack
		
		if (size() < stack.length / 3 && stack.length > 20) //resize the stack 
		{
			int smallerSize = stack.length / 2; //make a smaller size variable 
			T[] smaller = (T[]) (new Object[smallerSize]); //create smaller stack
			
			for (int index = 0; index < smallerSize; index++)
			{
				smaller[index] = stack[index]; //initialize the smaller stack to the current stack
			}
			stack = smaller; //make smaller stack equal to the actual stack
		}
		
		return result; //return the removed value
	}
	
	 /**  Returns without removing the top element of this stack. 
	   *   @return T data item on top of the stack
	   *   @Exception if the stack is empty EmptyStackException is thrown
	   */
	public T peek() throws EmptyStackException
	{
		if (isEmpty()) //if stack is empty 
		{
			throw new EmptyStackException("peek"); //then throw an EmptyStackException
		}
		
		return stack[top]; //return the item on top of the stack
	}
	
	  /**  Tells if the array stack is empty or not 
	   *   @return returns true if stack is empty and false otherwise
	   */
	public boolean isEmpty()
	{
		return (top == -1); //returns if stack is empty
	}
	
	  /**  Tells the size of the stack  
	   *   @return is the number of items in the stack
	   */
	public int size()
	{
		return top + 1; //returns number of items in stack
	}
	
	  /**  Tells the capacity of the stack
	   *   @return is the capacity of the stack 
	   */
	public int length()
	{
		return stack.length; //return capacity of stack
	}
	
	  /**  Gives a string of the stack in order
	   *   @return is the string containing all the data in the stack separated by a comma 
	   */
	public String toString()
	{
		String result = "Stack: "; //create a string variable
		
		for (int index = 0; index < size(); index++)
		{
			result = result + stack[index]; //add the stack variable to the string
			
			if (index < top) //if the end is reached 
			{
				result = result + ", "; //then add a comma and space to the string
			}
		}
		
		return result; //return the string
	}
	
	  /**  Increases the capacity of the stack depending on the current stack of the array
	   *  
	   */
	private void expandCapacity()
	{
		T[] larger; //a variable for the larger array is created
		
		if (stack.length < 100) //if the stack is smaller than 100 
		{
			larger = (T[]) (new Object[stack.length * 2]); //then double the size of the larger stack
		}
		else
		{
			larger = (T[]) (new Object[stack.length + 50]); //otherwise add 50 to the current size of stack
		}
		
		for (int index = 0; index < stack.length; index++)
		{
			larger[index] = stack[index]; //make the larger stack equal to the smaller stack
		}
		
		stack = larger; //set the actual stack to larger
	}
}
