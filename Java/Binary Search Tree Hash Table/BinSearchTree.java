//Author: Abdullah Khan
//Date: 04/01/2019
//Description: This class implements a binary search tree with a get and insert function

public class BinSearchTree {

	  /**  
	   *   The root of the BST
	   */
	private BinSearchTreeNode root; 
	
	  /**  Constructor: This initializes the binary search tree by setting root to null
	   *   @param n/a
	   */
	public BinSearchTree()
	{
		root = new BinSearchTreeNode("", "", 0); //set to a null default value
	}
	
	/**
	 * Method that finds the word in the BST
	 * 
	 * @param searchWord is the String that is being searched for
	 * @return the node containing the word
	 *             
	 */
	public BinSearchTreeNode getWord(String searchWord)
	{
		return getWordHelper(root, searchWord); //calls the recursive helper function
	}
	
	/**
	 * Helper method that finds the word in the BST which is called in the above function
	 * 
	 * @param r, searchWord
	 * r: is the root of the BST
	 * searchWord: is the word being searched for
	 * 
	 * @return the node containing the word
	 *             
	 */
	private BinSearchTreeNode getWordHelper(BinSearchTreeNode r, String searchWord)
	{
		if (r == null) //this is the case if the tree/subtree is empty
		{
			return null; //then returns null
		}
		else if (searchWord.compareTo(r.getWord()) == 0) //search to see if the same word is found
		{
			return r; //then return the root
		}
		else if (searchWord.compareTo(r.getWord()) < 0) //comparison on the left side recursive
		{
			return getWordHelper(r.getLeft(), searchWord); //left side recursion
		}
		else //comparisons on the right side recursive
		{
			return getWordHelper(r.getRight(), searchWord); //right side recursion
		}
	}
	
	/**
	 * Method that inserts the word in the BST
	 * 
	 * @param theWord, Filename, thePosition 
	 * theWord - this is the word found
	 * theFileName - this is the name of the file the word is contained in
	 * thePosition - this is the location of the word 
	 * 
	 * @return n/a
	 *             
	 */
	public void insertWord(String theWord, String theFileName, int thePosition)
	{
		BinSearchTreeNode find = getWord(theWord); //look for the word in this tree 
		
		if (find != null) //if the word is found 
		{
			find.getFiles().insertWord(theFileName, thePosition); //then add to the linked list in the node
		}
		else //if the tree is empty
		{
			insertWord(root, theWord, theFileName, thePosition); //insert it into the tree using the helper function
		}
	}
	
	/**
	 * Method that inserts the word in the BST
	 * 
	 * @param r, theWord, Filename, thePosition 
	 * r - is the root of the tree
	 * theWord - this is the word found
	 * theFileName - this is the name of the file the word is contained in
	 * thePosition - this is the location of the word 
	 * 
	 * @return n/a
	 *             
	 */
	private void insertWord(BinSearchTreeNode r, String theWord, String theFileName, int thePosition)
	{
		if (r == null) //if the tree is empty then create a newNode and add it to the tree
		{
			BinSearchTreeNode newNode = new BinSearchTreeNode(theWord, theFileName, thePosition);
			r = newNode;
		}
		else if (theWord.compareTo(r.getWord()) < 0) //if the word is the word in the treeNode
		{
			if (r.getLeft() == null) //if the left node is null then create a new Node and set it to left
			{
				BinSearchTreeNode newNode = new BinSearchTreeNode(theWord, theFileName, thePosition);
				r.setLeft(newNode);
			}
			else
			{
				insertWord(r.getLeft(), theWord, theFileName, thePosition); //otherwise put the current r's left child into a recursive function
			}
		}
		else if (r.getRight() == null) //if the right side is null then there is space to insert and thus newNode is made and put into the tree
		{
			BinSearchTreeNode newNode = new BinSearchTreeNode(theWord, theFileName, thePosition);
			r.setRight(newNode);
		}
		else
		{
			insertWord(r.getRight(), theWord, theFileName, thePosition); //now put r's right child into the recursive function
		}	
	}
}
