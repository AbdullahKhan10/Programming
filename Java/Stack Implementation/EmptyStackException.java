//Author: Abdullah Khan
//Date: 02/22/2019
//Description: This class creates exceptions for when a stack is empty and an operation cannot be performed

public class EmptyStackException extends Exception {
	
	  /**
	   * Sets up this exception with an appropriate message.
	   * @param message explains the error that threw the exception
	   */
	public EmptyStackException(String message)
	{
		super("Error! You cannot " + message + " an empty stack!");
	}

}
