//Author: Abdullah Khan
//Date: 30/03/2019
//Description: This class implements a depth first search of the map

import java.util.*;

public class DepthFirstSearch {
	
	RouteGraph inputGraph; //this is the variable for the graph
	Stack<Intersection> stack; //the stack variable
	
	/**
	 * Constructor
	 * @param graph: uses the graph given from the main function
	 *
	 */
	public DepthFirstSearch(RouteGraph graph)
	{
		inputGraph = graph; //initialize to the graph given
		stack = new Stack<Intersection>(); //create a new stack
	} 
	
	/**
	 * DFS of the path
	 * @param 
	 * startVertex - is the vertex in the graph you start at
	 * endVertex - is the vertex in the graph you want to go to
	 * @return a stack containing the path
	 */
	public Stack<Intersection> path(Intersection startVertex, Intersection endVertex) throws GraphException
	{
		stack.clear(); //start with a clean stack
		pathRec(startVertex, endVertex); //use the recursive function to input into the stack
		return stack; //return the stack
	}
	
	/**
	 * DFS of the path recursive
	 * @param 
	 * startVertex - is the vertex in the graph you start at
	 * endVertex - is the vertex in the graph you want to go to
	 * @return true or false whether a particular vertex is marked or not
	 */
	public boolean pathRec (Intersection startVertex, Intersection endVertex) throws GraphException
	{
		startVertex.setMark(true); //mark the start as true
		
		stack.push(startVertex); //push the start to the stack 
		
		if (startVertex == endVertex)
		{
			return true; //if the end vertex is found return true
		}
		else
		{
			Iterator<Road> it = inputGraph.incidentRoads(startVertex); //this is the list of incident roads
			
			while (it.hasNext()) //for each incident road 
			{
				Intersection x = it.next().getSecondEndpoint(); //variable for the road
				
				if (x.getMark() == false) //check to see if the mark is false
				{
					if (pathRec(x, endVertex) == true) //if the recursive call is true
					{
						return true; //then return true 
					}
				}
			}
			
			stack.pop(); //pop the stack 
			return false; //return false
		}
	}
}
