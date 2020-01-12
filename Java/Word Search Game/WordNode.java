//Author: Abdullah Khan
//Date: 19/02/2019
//Description: This class is the node of each list in the hash table

public class WordNode {
	
	private Word data; //the data part of the node
	private WordNode next; //the WordNode pointing to the nextNode
	
	/**
	 * Method create and initialize a WordNode object
	 * 
	 * @param data
	 * data: set the data in the node to the given data
	 * 
	 * @return n/a
	 * @throws n/a
	 *             
	 */
	public WordNode(Word data)
	{
		this.data = data; //initialize the data of the node 
		this.next = null; //set the next node to null by default
	}
	
	/**
	 * Method to the data
	 * 
	 * @param n/a
	 * 
	 * @return data associated with the node
	 * @throws n/a
	 *             
	 */
	public Word getData()
	{
		return data; //return the data of the node
	}
	
	/**
	 * Method to return next node
	 * 
	 * @param n/a
	 * 
	 * @return the next node
	 * @throws n/a
	 *             
	 */
	public WordNode getNext()
	{
		return next; //return the next node
	}
	
	/**
	 * Method to set the next node
	 * 
	 * @param set
	 * set: the next node that is being set to
	 * 
	 * @return n/a
	 * @throws n/a
	 *             
	 */
	public void setNext(WordNode set)
	{
		next = set; //set the next node
	}
}
