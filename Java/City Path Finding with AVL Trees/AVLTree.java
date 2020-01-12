//Author: Abdullah Khan
//Date: 30/03/2019
//Description: This class implements an avl tree

//the needed imports
import java.util.ArrayList;
import java.lang.*;


public class AVLTree implements AVLTreeADT {
	
	AVLTreeNode root; //the root of the tree
	int size; //the size of the tree
	
	/**
	 * Constructor
	 * @param n/a
	 */
	public AVLTree()
	{
		root = new AVLTreeNode(); //create new tree
		size = 0; //set initial size to 0
	}
	
	/**
	 * Set the root
	 * @param node - set the root
	 */
	public void setRoot(AVLTreeNode node)
	{
		root = node; //set root to parameter 
	}
	
	/**
	 * Normally we do not want to expose the root, but oh well.
	 * @return root
	 */
	public AVLTreeNode root()
	{
		return root; 
	}
	
	/**
	 * Is the provided node the root?
	 * @param node - some node of an AVLTree
	 * @return true if it is the root, false otherwise.
	 */
	public boolean isRoot(AVLTreeNode node)
	{
		return (root == node);
	}
	
	/**
	 * get number of elements stored in the tree.
	 * @return size
	 */
	public int getSize()
	{
		return size;
	}
	
	/**
	 * get operation: given a key, return the node with that key, return where it should be have been (a leaf) otherwise.
	 * @param node - root of a binary search tree.
	 * @param key
	 * @return node containing key k
	 */
	public AVLTreeNode get(AVLTreeNode node, int key)
	{
		if (node.isLeaf()) //if the node is a leaf 
		{
			return node; //then return the node
		}
		else
		{
			if (key == node.getKey()) //if the keys are equal
			{
				return node; //then return the node is found
			}
			else if (key < node.getKey())
			{
				return get(node.getLeft(), key); //recursively look for the key
			}
			else
			{
				return get(node.getRight(), key); //recursively look for the key 
			}
		}
	}

	/**
	 * Get the node with the smallest key, it is exists (null if it does not exist).
	 * @param node - when called, give a root of a tree.
	 * @return the internal node with the smallest key.
	 */
	public AVLTreeNode smallest(AVLTreeNode node)
	{
		if (node.isLeaf()) //if the node is a leaf
		{
			return null; //return null then 
		}
		else
		{
			AVLTreeNode temp = node; //create a temporary node that iterates over the tree
			
			while (temp.isInternal())
			{
				temp = temp.getLeft(); //keep going to the left to get the smallest
			}
			
			return temp.getParent(); //return the smallest 
		}
	}

	/**
	 * put operation of a BST.
	 * @param node - node provided, assume the root is provided.
	 * @param key - key of new record
	 * @param data - data of new record.
	 * @return the node storing the new record.
	 */
	public AVLTreeNode put(AVLTreeNode node, int key, int data) throws TreeException
	{
		AVLTreeNode newNode = get(node, key); //find where to put the node
		
		if (newNode.isInternal()) //if the key is already in the tree 
		{
			throw new TreeException("Duplicate keys while trying to put!"); //throw an exception 
		}
		else
		{
			//set the key and data in the node
			newNode.setKey(key); 
			newNode.setData(data);
			
			//create 2 leaf children for the new node
			AVLTreeNode c1 = new AVLTreeNode();
			AVLTreeNode c2 = new AVLTreeNode();
			
			//set the node to the children
			newNode.setLeft(c1);
			newNode.setRight(c2);
			
			//set the children to the node 
			c1.setParent(newNode);
			c2.setParent(newNode);
			
			size++; //increment the size
			
			return newNode; //return the added node
		}
	}
	
  
	/**
	 * Remove a record with a given key in a tree rooted at a given node.
	 * @param node - the tree rooted at node.
	 * @param key - key of node we need to remove.
	 * @return the parent of the node.
	 */
	public AVLTreeNode remove(AVLTreeNode node, int key) throws TreeException
	{
		AVLTreeNode tempNode = get(node, key); //look for the node trying to remove
		
		if (tempNode.isLeaf()) //no node found if is leaf
		{
			throw new TreeException("Node not found while trying to remove"); //throw an exception if the node isn't found
		}
		else
		{
			if (tempNode.getLeft().isLeaf()) //Case one for the right child
			{
				AVLTreeNode p1 = tempNode.getParent(); //get a tempNode for the parent 
				AVLTreeNode c1 = tempNode.getRight(); //get a tempNode for the right child of the child
				
				if (tempNode.isRoot()) //if the node is a root
				{
					setRoot(c1); //then set child to root
				}
				else
				{
					//otherwise set the parent of tempNode to the child of the removed node
					p1.setRight(c1);
					c1.setParent(p1);
				}
				size--; //decrement the size counter
			}
			else if (tempNode.getRight().isLeaf()) //Case one for the left child
			{
				AVLTreeNode p2 = tempNode.getParent(); //get a tempNode for the parent
				AVLTreeNode c2 = tempNode.getLeft(); //get a tempNode for the left child of the child
				
				if (tempNode.isRoot()) //if the node is a root
				{
					setRoot(c2); //set child to root
				}
				else
				{
					//set the parent to the child and child to the parent
					p2.setLeft(c2);
					c2.setParent(p2);
				}
				size--; //decrement the counter
			}
			else //Case two of the remove operation
			{
				AVLTreeNode smallest = smallest(tempNode.getRight()); //get the inorderSuccessor
				tempNode.setKey(smallest.getKey()); //set the tempNode to the inorderSuccesor
				tempNode.setData(smallest.getData());
				remove(smallest, smallest.getKey()); //remove the smallest node afterwards
			}	
		}
		
		return tempNode.getParent(); //return the parent of tempNode
	}

		
	/**
	 * inorder traversal, gives a list.
	 * @param node - tree rooted at node.
	 * @return list containing nodes
	 */
	public ArrayList<AVLTreeNode> inorder(AVLTreeNode node)
	{
		ArrayList<AVLTreeNode> list = new ArrayList<AVLTreeNode>(); //create an ArrayList 
		
		inorderRec(node, list); //use the recursive inOrder function to iterate through the list and add to it
		
		return list;
	}

	/**
	 * inorder traversal.
	 * @param node - tree rooted at node.
	 * @return an ArrayList containing inorder traversal.
	 */
	public void inorderRec(AVLTreeNode node, ArrayList<AVLTreeNode> list)
	{
		if (!node.isInternal()) //stop recursion once you encounter a leaf
		{
			return;
		}
		
		inorderRec(node.getLeft(), list); //recursion left
		
		list.add(node); //add to the list
		
		inorderRec(node.getRight(), list); //recursion right
	}		

	/**
	 * Insert a record (key,data) into the tree, re-balance the tree as necessary.
	 * @param node - root of the tree
	 * @param key - a key
	 * @param data - a data item
	 * @throws TreeException - if a duplicate key is found.
	 */
	public void putAVL(AVLTreeNode node, int key, int data) throws TreeException
	{
		AVLTreeNode temp = put(node, key, data); //use the BST put function 
		rebalanceAVL(node, temp); //then use the re-balance function to re-balance the tree
    } 

	/**
	 * Remove a record with key k, re-balances if necessary.
	 * @param node - root of tree
	 * @param key - key meant to be removed.
	 * @throws TreeException - if the key does not exist in the tree.
	 */
	public void removeAVL(AVLTreeNode node, int key) throws TreeException
	{
		AVLTreeNode temp = remove(node, key); //use the BST remove function
		rebalanceAVL(node, temp); //then use the re-balance function to re-balance the tree
	}

	/**
	 * Updates the height of a node (i.e. its height is maintained when it is changed, 1+max(height of left child, height of right child)).
	 * @param node
	 */
	public void recomputeHeight(AVLTreeNode node)
	{
		int maxHeight; //create a max height variable
		
		if (node.getLeft().getHeight() > node.getRight().getHeight()) //check the left to be bigger
		{
			maxHeight = node.getLeft().getHeight(); //if the left is bigger then maxHeight is on left
		}
		else if (node.getLeft().getHeight() == node.getRight().getHeight()) //checks if heights are equal
		{
			maxHeight = node.getLeft().getHeight(); //if equal then maxHeight can be either
		}
		else
		{
			maxHeight = node.getRight().getHeight(); //otherwise the right is bigger
		}
		
		node.setHeight(1 + maxHeight); //set the recomputed Height
	}

	/**
	 * This method rebalances the tree, and updates the heights of nodes as subtrees are rotated (moving upwards in the tree).
	 * @param r - root of AVL Tree
	 * @param v - where we first consider
	 */
	public void rebalanceAVL(AVLTreeNode r, AVLTreeNode v)
	{
		if (!v.isLeaf()) //if the subtree is an internal node
		{
			recomputeHeight(v); //compute the height of the node
		}
		
		while (v != r) //while the subtree is not equal to the root
		{
			v = v.getParent(); //make the subtree equal to its parent 
			if ((Math.abs(v.getLeft().getHeight() - v.getRight().getHeight())) > 1) //check if the height difference is more than 1
			{ 
				AVLTreeNode y = taller(v, true); //get the next node after the non-balance
				boolean onLeft = onLeft(y); //check if the node is on the left
				AVLTreeNode x = taller(y, onLeft); //then get the next node after that node
				
				if (v.getRight() == y && y.getRight() == x) //this is the right right case causing a left rotation
				{
					if (v.isRoot()) //if there are only 3 nodes in the tree and those require balance
					{
						//code to do a left rotation on the node
						v.setRight(y.getLeft());
						y.getLeft().setParent(v);
						
						y.setLeft(v);
						v.setParent(y);
						y.setParent(null);
						
						
						root = y; // make the middle man the root in this case
						
						//recompute the heights after
						recomputeHeight(v);
						recomputeHeight(y);
						
						r = y;
						v = y;
					}
					else //Case where it a left rotation on a subtree rather than the root
					{
						AVLTreeNode p = v.getParent();
						
						if (onLeft(v))
						{
							p.setLeft(y);						
						}
						else
						{
							p.setRight(y);
						}
						
						//code to do a left rotation on the subtree taking into account the parent
						y.setParent(p);
						
						v.setRight(y.getLeft());
						y.getLeft().setParent(v);
						
						y.setLeft(v);
						v.setParent(y);
						
						//recompute the heights afterwards
						recomputeHeight(p);
						recomputeHeight(v);
						recomputeHeight(y);
						
						v = y;
					}
				}
				else if (v.getLeft() == y && y.getLeft() == x) //this is the left left case where we do a right rotation
				{
					if (v.isRoot()) //Case where there are 3 nodes and the root is changed during the rotation
					{
						//code to do a right rotation on the tree
						v.setLeft(y.getRight());
						y.getRight().setParent(v);
						
						y.setRight(v);
						v.setParent(y);
						y.setParent(null);
						
						root = y; //this becomes the new root 
						
						//recompute the heights afterwards
						recomputeHeight(v);
						recomputeHeight(y);
						
						v = y;
						r = y;
					}
					else //Case where the subtree is where the imbalance occurs and not the root
					{
						AVLTreeNode p = v.getParent();
						
						//account for the parent of the subtree not lose the subtree 
						if (onLeft(v))
						{
							p.setLeft(y);						
						}
						else
						{
							p.setRight(y);
						}
						
						//do the right rotation on the tree
						y.setParent(p);
						
						v.setLeft(y.getRight());
						y.getRight().setParent(v);
						
						y.setRight(v);
						v.setParent(y);
						
						//recompute the heights afterwards
						recomputeHeight(p);
						recomputeHeight(v);
						recomputeHeight(y);
						
						v = y;
					}
				}
				else if (v.getRight() == y && y.getLeft() == x) //Case where we have to do a right left rotation on the tree
				{
					if (v.isRoot()) //if we have to change the root during the rotation
					{
						//code to perform the rotation
						v.setRight(x.getLeft());
						x.getLeft().setParent(v);
						
						y.setLeft(x.getRight());
						x.getRight().setParent(y);
						
						x.setParent(null);
						
						x.setLeft(v);
						v.setParent(x);
						
						x.setRight(y);
						y.setParent(x);
						
						root = x; //in this case x becomes the new root of the tree
						
						//recompute the heights afterwards
						recomputeHeight(v);
						recomputeHeight(y);
						recomputeHeight(x);
						
						v = x;
						r = x;
					}
					else //if the imbalance is not in the root and is in the subtree
					{
						AVLTreeNode p = v.getParent();
						
						if (onLeft(v))
						{
							p.setLeft(x);						
						}
						else
						{
							p.setRight(x);
						}
						
						//same as the rotations above but now we consider a different rotation
						x.setParent(p);
						
						v.setRight(x.getLeft());
						x.getLeft().setParent(v);
						
						y.setLeft(x.getRight());
						x.getRight().setParent(y);
						
						x.setLeft(v);
						v.setParent(x);
						
						x.setRight(y);
						y.setParent(x);
						
						//recompute the heights afterwards
						recomputeHeight(p);
						recomputeHeight(v);
						recomputeHeight(y);
						recomputeHeight(x);
						
						v = x;
					}
				}
				else if (v.getLeft() == y && y.getRight() == x) //case where we have to do a left right rotation
				{
					if (v.isRoot()) //if the root is where the imbalance is and that is where we are performing the left right rotation
					{
						//this is the code to do the rotation
						v.setLeft(x.getLeft());
						x.getRight().setParent(v);
						
						y.setRight(x.getLeft());
						x.getLeft().setParent(y);
						
						x.setParent(null);
						
						x.setLeft(y); 
						y.setParent(x);
						
						x.setRight(v);
						v.setParent(x);
						
						root = x; //in the double rotations the lowest node becomes the root
						
						//recompute the heights afterwards
						recomputeHeight(v);
						recomputeHeight(y);
						recomputeHeight(x);
						
						v = x;
						r = x;
					}
					else //in case the imbalance is in the subtrees
					{
						AVLTreeNode p = v.getParent();
						
						if (onLeft(v))
						{
							p.setLeft(x);						
						}
						else
						{
							p.setRight(x);
						}
						
						//makes sure to not lose information and keep the parent of the focus node
						x.setParent(p);
						
						//code to do the rotation
						v.setLeft(x.getRight());
						x.getRight().setParent(v);
						
						y.setRight(x.getLeft()); 
						x.getLeft().setParent(y); 
						
						x.setLeft(y); 
						y.setParent(x);
						
						x.setRight(v); 
						v.setParent(x);
						
						//recompute the heights afterwards
						recomputeHeight(p);
						recomputeHeight(v);
						recomputeHeight(y);
						recomputeHeight(x);
						
						v = x;
					}
				}
			}
			recomputeHeight(v);
		}	
	}
	
	
	/**
	 * Function to check if a node is on its parent's left
	 *  
	 * @param node - this is the node being checked
	 * @return true or false based on if the node is on the left
	 */
	private boolean onLeft(AVLTreeNode node)
	{
		return (node.getParent().getLeft() == node);
	}
	
	/**
	 * Find the taller child of a node
	 *  
	 * @param node - this is the node being checked
	 * onLeft - this tells if the node is on the left
	 * @return returns the taller node 
	 */
	public AVLTreeNode taller(AVLTreeNode node, boolean onLeft)
	{
		if (node.getLeft().getHeight() > node.getRight().getHeight()) 
		{
			return node.getLeft(); //if the node on the left is taller
		}
		else if (node.getLeft().getHeight() == node.getRight().getHeight())
		{
			//if both nodes are the same height give the one depending on if its on the left
			if (onLeft)
			{
				return node.getLeft();
			}
			else
			{
				return node.getRight();
			}
		}
		else
		{
			return node.getRight(); //otherwise return the right node
		}
	}
}
