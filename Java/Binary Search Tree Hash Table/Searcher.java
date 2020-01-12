//Author: Abdullah Khan
//Date: 04/01/2019
//Description: This class implements a searcher that will find all the words and also insert all the words into the tree

import java.util.*;
import java.io.*;

public class Searcher {
	
	  /**  
	   *   This is the table which has big array of BST nodes
	   */
	private HashTable table;
	
	  /**  
	   *   The string name of the text file
	   */
	private String inputFile;
	
	  /**  Constructor: This initializes the table and inputFile to the given parameters
	   *   @param table, inputFile
	   *   table - is the table variable
	   *   input - name of the given inputFile
	   */
	public Searcher(HashTable table, String inputFile)
	{
		this.table = table; //set this table to given
		this.inputFile = inputFile; //set this inputFile to given
	}
	
	/**
	 * Method that finds all the words in the BST using the findWord function
	 * 
	 * @param n/a
	 * @return n/a
	 *             
	 */
	public void findAllWords() 
	{	
		try
		{
			BufferedReader in = new BufferedReader(new FileReader(inputFile)); //create a reader to get the input file
			String line = in.readLine(); //set the line to be in a String variable 
			in.close(); //close the file
			
			String[] words = line.split("\\s+"); //split the string where there is a space and store into string array
			
			for (int i = 0; i < words.length; i++) //iterate through the array of strings
			{
				findWord(words[i]); //call the findWord function on all the strings in the array
			}	
		}
		catch (Exception e) //throw this message if there is an error reading or opening the file
		{
			System.out.println("Find all words cannot compute because there is no input file");
		}
	}
	
	/**
	 * Method that looks for a word in the lexicon data structure then prints appropriate message to output file
	 * 
	 * @param n/a
	 * @return n/a
	 *             
	 */
	public void findWord(String searchWord)
	{
		int index = table.computeIndex(searchWord); //find the index of the searchWord in the table 
		
		BinSearchTree[] tab = table.getTable(); //create a temporary BST array to get the table
		
		BinSearchTreeNode search = tab[index].getWord(searchWord); //make search equal the node found while putting searchWord into the getWord function
		
		if (search == null) //if not found in the tree 
		{
			CustomPrinter.wordNotFound(searchWord, inputFile); //use this static function to print and output that word is not found
		}
		else //otherwise 
		{
			CustomPrinter.wordFound(searchWord, inputFile); //use the static function to print and output that the word is found
			
			Iterator<FileNode> list = search.getFiles().iterator(); //make variable list to be an iterator for the list in the BST node
			
			while (list.hasNext()) //iterate through the list 
			{
				FileNode current = list.next(); //a sort of counter to move to the next node 
				CustomPrinter.printPositionsPerFileFound(current.getFilename(), current.getPositions(), inputFile); //print required information using the static function
			}	
		}
	}
	
}
