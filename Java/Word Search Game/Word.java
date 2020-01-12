//Author: Abdullah Khan
//Date: 19/02/2019
//Description: This class is the data that the node will store 

public class Word {
	
	private String word; //store a word key of type string
	private int score; //stores the associated score for that word
	
	/**
	 * Method create and initialize a word object
	 * 
	 * @param word, score
	 * word: set word to given word
	 * score: set score to given score
	 * 
	 * @return n/a
	 * @throws n/a
	 *             
	 */
	public Word(String word, int score)
	{
		//initialize the word components to the given amounts
		this.word = word;
		this.score = score;
	}
	
	/**
	 * Method to return key
	 * 
	 * @param n/a
	 * 
	 * @return the key word 
	 * @throws n/a
	 *             
	 */
	public String getKey()
	{
		return word; //return the key
	}
	
	/**
	 * Method to return value
	 * 
	 * @param n/a
	 * 
	 * @return the associated value
	 * @throws n/a
	 *             
	 */
	public int getValue()
	{
		return score; //return the score
	}
}
