//Author: Abdullah Khan
//Date: 03/20/2019
//Description: This class contains the main which finds the shortest connections from the starting point which is the power to the customer

//import exceptions
import java.io.FileNotFoundException;
import java.io.IOException;


public class ShortestPath {
	
	/**
	 * This is the map instance which is uploaded
	 */
	Map cityMap;
	
	  /**  Constructor: This initializes map
	   *   @param filename
	   *   filename: this is the name of the file that contains all the map parameters
	   */
	public ShortestPath (String filename)
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
	public static void main (String[] args)
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

		ShortestPath shortPath = new ShortestPath(args[0]); //create a connection object that creates a map
		DLList<MapCell> mapCellList = new DLList<MapCell>();
		
		mapCellList.insert(shortPath.cityMap.getStart(), 0);
		shortPath.cityMap.getStart().markInList();
		
		
		while(!mapCellList.isEmpty()) //loops until the list is empty
		{
			MapCell smallest = mapCellList.getSmallest(); //returns and removes the smallest
			smallest.markOutList(); //marks the smallest out of the list
			
			if (smallest.isCustomer()) //when the smallest is the customer 
			{
				break; //break the loop
			}
			else //otherwise
			{
				for (int i = 0; i <= 3; i++) //loops through all the neighbors
				{
					MapCell next = shortPath.nextCell(smallest); //this is a neighbor of the smallest cell
					
					if (next != null) //if the neighbor is not null
					{
						int distance = 1 + smallest.getDistanceToStart(); //create a variable for distance of the neighbors
						
						if (next.getDistanceToStart() > distance) //if the neighbor distance is greater then make it the smaller distance
						{
							next.setDistanceToStart(distance); //set cell distance
							next.setPredecessor(smallest); //set cell as predecessor
						}
						
						int distance2 = next.getDistanceToStart(); //distance of the other cell
						
						if (next.isMarkedInList() && distance2 < mapCellList.getDataValue(next))
						{
							mapCellList.changeValue(next, distance2); //if distance is less and cell is marked then change value in list
						}
						
						if (!next.isMarkedInList()) //if the neighbor is not marked
						{
							mapCellList.insert(next, distance2); //insert it into the list
							next.markInList(); //mark it as in the list
						}

					}
				}
				
			}
		}
		
		if (mapCellList.isEmpty()) //if the stack is empty
		{
			System.out.println("You cannot reach your destination!"); //then this means we have not reached our destination
		}
		else //if not empty 
		{
			System.out.println("You have reached your destination!"); //then we have reached our destination
			System.out.println("Number of cells in the shortest path from the initial cell to the destination: " + (shortPath.cityMap.getDestination().getDistanceToStart() - 1)); //gives the size of the stack -2 because we don't count the customer and the power
		}
		
	}
	
	
	  /**  This function returns the best cell according to all the specifications
	   *   @param cell
	   *   cell: this is the current cell which is used to find the next best cell that is adjacent to it
	   *   @return this returns the found best cell; if none is found then returns null
	   */
	private MapCell nextCell(MapCell cell)
	{
		for (int i = 0; i < 4; i++) //this loops through all of the neighbors
		{
			if (cell.isPowerStation()) //if the current cell is a power station
			{	
				if (i == 0 || i == 2) //checks the north and south neighbors
				{
					if (cell.getNeighbour(i) != null && (cell.getNeighbour(i).isOmniSwitch() || cell.getNeighbour(i).isVerticalSwitch()) && !cell.getNeighbour(i).isMarked())
					{
						return cell.getNeighbour(i);
					}
				}
				
				if (i == 1 || i == 3) //checks the east and west neighbors
				{
					if (cell.getNeighbour(i) != null && (cell.getNeighbour(i).isOmniSwitch() || cell.getNeighbour(i).isHorizontalSwitch()) && !cell.getNeighbour(i).isMarked())
					{
						return cell.getNeighbour(i);
					}
				}
			}
			
			if (cell.isOmniSwitch()) //if the current cell is an Omni switch
			{
				if (i == 0 || i == 2) //checks the north and south cell
				{
					if (cell.getNeighbour(i) != null && (cell.getNeighbour(i).isOmniSwitch() || cell.getNeighbour(i).isCustomer() || cell.getNeighbour(i).isVerticalSwitch()) && !cell.getNeighbour(i).isMarked())
					{
						return cell.getNeighbour(i);
					}
				}
				
				if (i == 1 || i == 3) //checks the east and west cell
				{
					if (cell.getNeighbour(i) != null && (cell.getNeighbour(i).isOmniSwitch() || cell.getNeighbour(i).isCustomer() || cell.getNeighbour(i).isHorizontalSwitch()) && !cell.getNeighbour(i).isMarked())
					{
						return cell.getNeighbour(i);
					}
				}
			}
			
			if (cell.isVerticalSwitch()) //if the current cell is a vertical cell
			{
				if (i == 0 || i == 2) //these are the adjacent north and south
				{
					if (cell.getNeighbour(i) != null && (cell.getNeighbour(i).isOmniSwitch() || cell.getNeighbour(i).isCustomer() || cell.getNeighbour(i).isVerticalSwitch()) && !cell.getNeighbour(i).isMarked())
					{
						return cell.getNeighbour(i); //if found on the north or south then return cell
					}
				}
			}
			
			if (cell.isHorizontalSwitch()) //if the cell is a horizontal cell
			{
				if (i == 1 || i == 3) //these are the adjacent east and west
				{
					if (cell.getNeighbour(i) != null && (cell.getNeighbour(i).isOmniSwitch() || cell.getNeighbour(i).isCustomer() || cell.getNeighbour(i).isHorizontalSwitch()) && !cell.getNeighbour(i).isMarked())
					{
						return cell.getNeighbour(i); //if found on the east or west then return cell
					}
				}
			}
		}
			
		return null; //if none of the conditions above are met then return null
	}
	
}
