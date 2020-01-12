//Author: Abdullah Khan
//Date: 02/22/2019
//Description: This class contains the main which finds the connections from the starting point which is the power to the customer

//import exceptions
import java.io.FileNotFoundException;
import java.io.IOException;

public class FindConnection {

	/**
	 * This is the map instance which is uploaded
	 */
	private Map cityMap;
	
	  /**  Constructor: This initializes map
	   *   @param filename
	   *   filename: this is the name of the file that contains all the map parameters
	   */
	public FindConnection (String filename) 
	{
		try 
		{
			cityMap = new Map(filename); //uses the map constructor to initialize a map
		} 
		catch (InvalidMapException e)  //catch the invalid map exception
		{
			e.printStackTrace();
		} 
		catch (FileNotFoundException e) //catch the file not found exception
		{
			e.printStackTrace();
		} 
		catch (IOException e) //catch the input / output error exception
		{
			e.printStackTrace();
		}
	}
	
	  /**  Main: contains the find path algorithm
	   *   @param args[0]
	   *   args[0]: the name of the file that we are getting the map from
	   */
	public static void main (String[] args) throws EmptyStackException
	{		
		if(args.length < 1) //if no arguments are given to the system
		{
			System.out.println("You must provide the name of the input file"); //give message and exit
			System.exit(0);
		}
		
		if (!(args[0].equals("map1.txt") ||  //check if the input is any of the map names
			args[0].equals("map2.txt") ||
			args[0].equals("map3.txt") ||
			args[0].equals("map4.txt") ||
			args[0].equals("map5.txt") ||
			args[0].equals("map6.txt") ||
			args[0].equals("map7.txt") ||
			args[0].equals("map8.txt")))
		{
			System.out.println("The name of file you have provided is invalid"); //give message and exit
			System.exit(0);
		}

		FindConnection connection = new FindConnection(args[0]); //create a connection object that creates a map
		ArrayStack<MapCell> mapCellStack = new ArrayStack<MapCell>(); //create a stack of type mapCell
		
		mapCellStack.push(connection.cityMap.getStart()); //push the start cell into the stack
		connection.cityMap.getStart().markInitial(); //mark the start cell as initial
		connection.cityMap.getStart().markInStack(); //mark the start cell as in stack
		
		while (!mapCellStack.isEmpty() && !mapCellStack.peek().isCustomer()) //keep looping until the stack is empty or till the customer is found
		{
			MapCell current = mapCellStack.peek(); //create a current mapCell variable to store the current mapCell we are working with
			
			if (current.isCustomer()) //if the current is the customer 
			{
				break; //then break the loop
			}
			
			if (connection.bestCell(current) != null) //if the best cell function does not return null 
			{
				mapCellStack.push(connection.bestCell(current)); //then push the best cell into the stack
				connection.bestCell(current).markInStack(); //the cell is also marked
			}
			else //if the bestcell from the current cell is null
			{
				MapCell unmark = mapCellStack.pop(); //pop the cell on top
				unmark.markOutStack(); //mark the cell out of the stack
			}
		}
		
		if (mapCellStack.isEmpty()) //if the stack is empty
		{
			System.out.println("You cannot reach your destination!"); //then this means we have not reached our destination
		}
		else //if not empty 
		{
			System.out.println("You have reached your destination!"); //then we have reached our destination
			System.out.println("Number of cells in the path from the initial cell to the destination: " + (mapCellStack.size() - 2)); //gives the size of the stack -2 because we don't count the customer and the power
		}
	}
	
	  /**  This function returns the best cell according to all the specifications
	   *   @param cell
	   *   cell: this is the current cell which is used to find the next best cell that is adjacent to it
	   *   @return this returns the found best cell; if none is found then returns null
	   */
	private MapCell bestCell(MapCell cell)
	{
		for (int i = 0; i < 4; i++) //this loop tries to find the customer loop
		{
			if (cell.isOmniSwitch()) //if the current cell is an Omni switch
			{
				if (cell.getNeighbour(i) != null && cell.getNeighbour(i).isCustomer() && !cell.getNeighbour(i).isMarked()) //then look at all the adjacent valid cells
				{
					return cell.getNeighbour(i); //if found then return the cell
				}
			}
			
			if (cell.isVerticalSwitch()) //if the current cell is a vertical cell
			{
				if (i == 0 || i == 2) //these are the adjacent north and south
				{
					if (cell.getNeighbour(i) != null && cell.getNeighbour(i).isCustomer() && !cell.getNeighbour(i).isMarked())
					{
						return cell.getNeighbour(i); //if found on the north or south then return cell
					}
				}
			}
			
			if (cell.isHorizontalSwitch()) //if the cell is a horizontal cell
			{
				if (i == 1 || i == 3) //these are the adjacent east and west
				{
					if (cell.getNeighbour(i) != null && cell.getNeighbour(i).isCustomer() && !cell.getNeighbour(i).isMarked())
					{
						return cell.getNeighbour(i); //if found on the east or west then return cell
					}
				}
			}
		}
		
		
		if (cell.isOmniSwitch() || cell.isPowerStation()) //if the current cell is a omni switch or a power station
		{
			for (int i = 0; i < 4; i++) //then look at all adjacent cells
			{
				if (cell.getNeighbour(i) != null && cell.getNeighbour(i).isOmniSwitch() && !cell.getNeighbour(i).isMarked())
				{
					return cell.getNeighbour(i); //look for the adjacent omni switch cell
				}
			}

		}

		if (cell.isOmniSwitch()) //if the current cell is a omni switch
		{
			for (int i = 0; i < 4; i++) //look for the corresponding vertical or horizontal switch
			{
				if (i == 0) //if the north switch is vertical
				{
					if (cell.getNeighbour(i) != null && cell.getNeighbour(i).isVerticalSwitch() && !cell.getNeighbour(i).isMarked())
					{
						return cell.getNeighbour(i);
					}
				}
				else if (i == 1) //if the east switch is horizontal
				{
					if (cell.getNeighbour(i) != null && cell.getNeighbour(i).isHorizontalSwitch() && !cell.getNeighbour(i).isMarked())
					{
						return cell.getNeighbour(i);
					}
				}
				else if (i == 2) //if the south cell is vertical
				{
					if (cell.getNeighbour(i) != null && cell.getNeighbour(i).isVerticalSwitch() && !cell.getNeighbour(i).isMarked())
					{
						return cell.getNeighbour(i);
					}
				}
				else if (i == 3) //if the west cell is horizontal
				{
					if (cell.getNeighbour(i) != null && cell.getNeighbour(i).isHorizontalSwitch() && !cell.getNeighbour(i).isMarked())
					{
						return cell.getNeighbour(i);
					}
				}		
			}
		}
		
		if (cell.isVerticalSwitch()) //if the current cell is a vertical switch
		{
			for (int i = 0; i < 4; i = i + 2) //look at the north and south cells and see if you find another vertical cell or omni switch
			{
				if (cell.getNeighbour(i) != null && (cell.getNeighbour(i).isVerticalSwitch() || cell.getNeighbour(i).isOmniSwitch()) && !cell.getNeighbour(i).isMarked())
				{
					return cell.getNeighbour(i);
				}
			}
		}
		
		if (cell.isHorizontalSwitch()) //if the current cell is a horizontal switch
		{
			for (int i = 1; i < 4; i = i + 2) //look at the north and south cells and see if you find another vertical cell or omni switch
			{
				if (cell.getNeighbour(i) != null && (cell.getNeighbour(i).isHorizontalSwitch() || cell.getNeighbour(i).isOmniSwitch()) && !cell.getNeighbour(i).isMarked())
				{
					return cell.getNeighbour(i);
				}
			}
		}
			
		return null; //if none of the conditions above are met then return null
	}
}
