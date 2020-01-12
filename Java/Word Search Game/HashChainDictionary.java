//Author: Abdullah Khan
//Date: 19/02/2019
//Description: This class creates a hash table with the dictionary methods put, get, and remove

public class HashChainDictionary implements DictionaryADT{

	private WordNode[] hTable; //array for the hash table
	private int hTableSize; //full size of the hash table array
	private int size = 0; //number of word values in the hash table; initially zero
	
	/**
	 * Method create and initialize a hash dictionary of specified size
	 * 
	 * @param size
	 * size: is the size of the array which is the dictionary's index
	 * 
	 * @return n/a
	 * @throws n/a
	 *             
	 */
	public HashChainDictionary(int size)
	{
		hTable = new WordNode[size]; //create a new hash table of size given
		hTableSize = size; //set the size of the table to given size
	}
	
	/**
	 * Method to put a word object into the dictionary
	 * 
	 * @param word
	 * word: this word is being inserted into the dictionary
	 * 
	 * @return an integer value indication 1 for collision or 0 for no collision
	 * @throws DictionaryException when the given word is already in the dictionary
	 *             
	 */
	public int put(Word word) throws DictionaryException
	{
		WordNode p = hTable[hashFunction(word.getKey())]; //use hash function to find position
		
		if (p == null)
		{
			hTable[hashFunction(word.getKey())] = new WordNode(word); //if the particular section of the table is empty create a new word there
			size++; //increment the size of the current size
			return 0; //return 0 for no collisions
		}
		else
		{
			while (p.getNext() != null && !p.getData().getKey().equals(word.getKey()))
			{
				p = p.getNext(); //keep moving to the next element in the list until you are at the end or you are at the same key
			}
			
			if (p.getData().getKey().equals(word.getKey())) //having the same key will cause an error and exception to be thrown
			{
				throw new DictionaryException(word.getKey()); //throw the exception
			}
			else
			{
				p.setNext(new WordNode(word)); //set the new word into the list by adding it to the last element in the list
				size++; //increment the size of the current size
				return 1; //return 1 for a collision
			}
		}
	}
	
	/**
	 * Method to get a word object from the dictionary
	 * 
	 * @param inputWord
	 * inputWord: this word is being searched for in the dictionary
	 * 
	 * @return null if the key is not found in the dictionary and the associated word in the dictionary if found in the dictionary
	 * @throws n/a
	 *             
	 */
	public Word get(String inputWord)
	{
		WordNode p = hTable[hashFunction(inputWord)]; //use hash function to find the particular element in array and set it to p
		
		while (p != null && !p.getData().getKey().equals(inputWord))
		{
			p = p.getNext(); //keep moving through the list until the end or until a key equals the input word
		}
		
		if (p == null)
		{
			return null; //if no matching key was found return null
		}
		else
		{
			return p.getData(); //if key is found return the data associated
		}
	}
	
	/**
	 * Method to remove a word object from the dictionary
	 * 
	 * @param inputWord
	 * inputWord: this key word is going to removed from the dictionary 
	 * 
	 * @return the data that was removed from the dictionary
	 * @throws NoKeyException if the key is not found 
	 *             
	 */
	public Word remove(String inputWord) throws NoKeyException
	{
		WordNode p = hTable[hashFunction(inputWord)]; //use the hash function to find the particular array element of the table
		WordNode prev = null; //initially set the previous node to equal null
		
		while (p != null)
		{
			if (p.getData().getKey().equals(inputWord))
			{
				if (prev != null)
				{
					prev.setNext(p.getNext()); //if the list has more than 1 item then set previous
				}
				else
				{
					hTable[hashFunction(inputWord)] = p.getNext(); //remove the key from the list
					size--; //decrease the size by 1 after removal of the element
					return p.getData(); //return the data that was removed
				}
			}
			else
			{
				prev = p; //set the previous
				p = p.getNext(); //set the current
			}
		}
		
		throw new NoKeyException(inputWord); //throw an exception if no key was found
	}
	
	/**
	 * Method to calculate the hash value of the given key
	 * 
	 * @param key
	 * key: this key is broken up and a hash value is calculated
	 * 
	 * @return the associated hash value of the string key as an integer
	 * @throws n/a
	 *             
	 */
	private int hashFunction(String key)
	{
		//polynomial hash function
		int val = (int) key.charAt(key.length() - 1); //initially set val to the key.lenth() - 1 
		
		for (int i = key.length() - 2; i >= 0; i--) //iterate through each character of the given string
		{
			val = ((val * 33) + (int)key.charAt(i)) % hTableSize; //hash each character by using x = 33 and M = hTableSize
		}
		
		return val; //return the hashed value
	}
	
	
	/**
	 * Method to return the size of the current table
	 * 
	 * @param n/a
	 * 
	 * @return return the number of elements in the hash table
	 * @throws n/a
	 *             
	 */
	public int size()
	{
		return size; //return the current number of elements in the hash table
	}	
}
