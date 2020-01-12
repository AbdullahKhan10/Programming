//Author: Abdullah Khan
//Date: 19/02/2019
//Description: This class implements all the operations that the WordSearch class does 

import java.io.IOException;
import java.util.ArrayList; //for the array list
import java.io.BufferedReader; //used for file input
import java.io.FileReader; //used for file input

public class WordSearchOperations {

	private String[][] grid; //this is the grid of the wordy's search game storing each character
	private int gridSize; //size of the grid 
	
	private HashChainDictionary dict; //this hash table stores the dictionary
	private HashChainDictionary foundWords; //this hash table stores the current words that are found
	
	private int maxScore; //this stores the maximum score you can get in the game
	
	/**
	 * Method to initialize the whole game
	 * 
	 * @param fileName, wordTextFile
	 * fileName: the name of the document containing the game parameters
	 * wordTextFile: the name of the document containing the dictionary items
	 * 
	 * @return n/a
	 * @throws n/a
	 *             
	 */
	public WordSearchOperations(String fileName, String wordTextFile) throws IOException, DictionaryException
	{
		//these variables are created in order to get the dictionary from the wordTextFile
		FileReader file = new FileReader(wordTextFile);
		BufferedReader reader = new BufferedReader(file);
		String tempLine;
		
		//the dictionary will be the size of a prime number between 74000-75000
		dict = new HashChainDictionary(74017);
		
		while((tempLine = reader.readLine()) != null) //this iterates through each line of the dictionary storing a string key and a value
		{
			String[] tempLineSplit = tempLine.split(","); //splits the key and value by the ","
			
			Word addWord = new Word(tempLineSplit[0], Integer.parseInt(tempLineSplit[1])); //creating a word object using the split strings		
			dict.put(addWord); //put that word object into the dictionary
		}
		reader.close(); //close the file input object reader 
		
		//create another file input object for the fileName text file
		FileReader file2 = new FileReader(fileName);
		BufferedReader reader2 = new BufferedReader(file2);
		String tempLine2;
		
		gridSize = Integer.parseInt(reader2.readLine()); //set the first line of the fileName file to the grid size
		foundWords = new HashChainDictionary(71); //create a hash table storing all the found words in the game
		grid = new String[gridSize][gridSize]; //initialize the grid using the grid size 
		
		for (int i = 0; i < gridSize; i++)
		{
			tempLine2 = reader2.readLine(); //get each line
			for (int j = 0; j < gridSize; j++)
			{
				grid[i][j] = String.valueOf(tempLine2.charAt(j)); //use the lines of the fileName to initialize each element of the grid
			}	
		}
		
		maxScore = 0; //initially set the max score to 0
		
		while((tempLine2 = reader2.readLine()) != null)
		{
			maxScore = maxScore + dict.get(tempLine2).getValue(); //find the scores in the dictionary and find the corresponding max score
		}
		
		reader2.close(); //close the reader
	}
	
	/**
	 * Method to return the number of words currently found 
	 * 
	 * @param n/a
	 * 
	 * @return the size of the foundWords table
	 * @throws n/a
	 *             
	 */
	public int getNumWordsFound()
	{
		return foundWords.size(); //return the size of the foundWords hash table
	}
	
	/**
	 * Method to return the size of the grid
	 * 
	 * @param n/a
	 * 
	 * @return gridSize value
	 * @throws n/a
	 *             
	 */
	public int getSize()
	{
		return gridSize; //return the size of the grid
	}
	
	/**
	 * Method to return max score of the current game
	 * 
	 * @param n/a
	 * 
	 * @return maxScore value
	 * @throws n/a
	 *             
	 */
	public int getMaxScore()
	{
		return maxScore; //return the max score of the game
	}
	
	/**
	 * Method to return particular grid element string value
	 * 
	 * @param i, j
	 * i: the row
	 * j: the column
	 * 
	 * @return grid[i][j]
	 * @throws n/a
	 *             
	 */
	public String getLetter(int i, int j)
	{
		return grid[i][j]; //return the letter inside of the grid
	}
	
	/**
	 * Method to return the list of words found in the given string
	 * 
	 * @param string
	 * string: the string we are using to find substrings
	 * 
	 * @return the list of words found in the dictionary in the current string
	 * @throws n/a
	 *             
	 */
	public ArrayList<Word> checkWords(String string)
	{
		ArrayList<Word> words = new ArrayList<Word>(); //create a temporary array list of type words
		String temp; //going to the substrings
		
		for (int i = 0; i < string.length(); i++)
		{
			for (int j = i + 4; j < string.length() + 1; j++)
			{
				temp = string.substring(i, j); //the loop creates substring to get the particular instances of words
				
				if (dict.get(temp) != null) //if the substring is in the dictionary then add it to the array list
				{
					words.add(dict.get(temp)); //add the found word into the array list
				}
			}
		}
		return words; //return the array list
	}
	
	/**
	 * Method to return the list of words found in the given string using the checkWords function
	 * 
	 * @param line
	 * line: the string we are using to find substrings
	 * 
	 * @return the list of words found in the dictionary in the current string
	 * @throws n/a
	 *             
	 */
	public ArrayList<Word> findWords(String line)
	{
		ArrayList<Word> total = new ArrayList<Word>(); //create a temporary array list of type words
		
		String[] wordStrings = line.split("\\s+"); //splits the string between the spaces
		
		for (int i = 0; i < wordStrings.length; i++)
		{
			total.addAll(checkWords(wordStrings[i])); //using checkWords function add the array of words to the total
		}
		
		return total; //return the total found using the checkWords functions 
	}
	
	/**
	 * Method to return the list of words that were updated in the foundWords Dictionary
	 * 
	 * @param words
	 * words: list of words to update into the dictionary
	 * 
	 * @return the list of words that were just updated into the foundWords dictionary 
	 * @throws n/a
	 *             
	 */
	public ArrayList<Word> updateWordList(ArrayList<Word> words) throws DictionaryException
	{
		ArrayList<Word> added = new ArrayList<Word>(); //create a temporary array list of type words
		
		for (int i = 0; i < words.size(); i++) //iterates through the array list of words
		{
			if (foundWords.get(words.get(i).getKey()) == null) //if the words are not already in the dictionary then put them in the dictionary
			{
				foundWords.put(words.get(i)); //put the word into the dictionary 
				added.add(words.get(i)); //add the word to the added array list
			}
		}
		
		return added; //return the added array list containing all the newly updated words
	}	
}
