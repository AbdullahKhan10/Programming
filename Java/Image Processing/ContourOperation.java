//Author: Abdullah Khan
//Description: This operation takes an image and makes it look like a black and white drawing

import java.awt.Color;

public class ContourOperation implements ImageOperation{

	public Color[][] doOperation(Color[][] imageArray)
	{
		int numOfRows = imageArray.length; //set the imageArray's length to the number of rows
		int numOfColumns = imageArray[0].length; //set the imageArray's width to the number columns 
		
		Color[][] result = new Color[numOfRows][numOfColumns]; //this creates a color array with the number of rows and columns that we got from above
		
		for (int i = 0; i < numOfRows; i++) //this loop iterates through the rows
		{
			for (int j = 0; j < numOfColumns; j++) //this loop iterates through the columns
			{
				if (isBlack(imageArray, numOfRows, numOfColumns, i, j, i - 1, j - 1)) //this checks the array that is row -1 and column -1 to it; bounds are also checks to make sure array is in bound
				{
					result[i][j] = new Color(0,0,0); //sets the resulting array pixel to be black
				}
				else if (isBlack(imageArray, numOfRows, numOfColumns, i, j, i - 1, j)) //this checks the array that is row -1 and the same column to it; bounds are also checks to make sure array is in bound
				{
					result[i][j] = new Color(0,0,0); //sets the resulting array pixel to be black
				}
				else if (isBlack(imageArray, numOfRows, numOfColumns, i, j, i - 1, j + 1)) // this checks the array that is row -1 and column +1 to it; bounds are also checks to make sure array is in bound
				{
					result[i][j] = new Color(0,0,0); //sets the resulting array pixel to be black
				}
				else if (isBlack(imageArray, numOfRows, numOfColumns, i, j, i, j - 1)) //this checks the array that is the same row and column -1 to it; bounds are also checks to make sure array is in bound
				{
					result[i][j] = new Color(0,0,0); //sets the resulting array pixel to be black
				}
				else if (isBlack(imageArray, numOfRows, numOfColumns, i, j, i, j + 1)) //this checks the array that is the same row and column +1 to it; bounds are also checks to make sure array is in bound
				{
					result[i][j] = new Color(0,0,0); //sets the resulting array pixel to be black
				}
				else if (isBlack(imageArray, numOfRows, numOfColumns, i, j, i + 1, j - 1)) //this checks the array that is the row +1 and column -1 to it; bounds are also checks to make sure array is in bound
				{
					result[i][j] = new Color(0,0,0); //sets the resulting array pixel to be black
				}
				else if (isBlack(imageArray, numOfRows, numOfColumns, i, j, i + 1, j)) //this checks the array that is the row +1 and the same column to it; bounds are also checks to make sure array is in bound
				{
					result[i][j] = new Color(0,0,0); //sets the resulting array pixel to be black
				}
				else if (isBlack(imageArray, numOfRows, numOfColumns, i, j, i + 1, j + 1)) //this checks the array that is row +1 and column +1 to it; bounds are also checks to make sure array is in bound
				{
					result[i][j] = new Color(0,0,0); //sets the resulting array pixel to be black
				}
				else //if no neighbors of the array pixel is black then the pixel is set to be white
				{
					result[i][j] = new Color(255,255,255); //sets the resulting array pixel to be white
				}

			}
		}
		
		return result; //after setting the pixels to be either black or white the resulting array pixel image is returned by the function
	}
	
	private boolean isBlack(Color[][] image, int row, int col, int CR, int CC, int NR, int NC) //this is a private helper function to find the color distance of a particular point in the array to the specified neighboring point
	{
		if (NR < 0 || NR >= row || NC < 0 || NC >= col) //checks if the array is in bound 
		{
			return false; //returns false if out of bound
		}
		
		//using the formula in the notes the color distance is calculated without being square rooted to make it look cleaner
		double colorDistance = Math.sqrt(Math.pow(image[CR][CC].getRed() - image[NR][NC].getRed(), 2) 
							   + Math.pow(image[CR][CC].getGreen() - image[NR][NC].getGreen(), 2) 
							   + Math.pow(image[CR][CC].getBlue() - image[NR][NC].getBlue(), 2)); 
		
		if (colorDistance > 65) //if color distance is greater than 65 then pixel is black and returns true
		{
			return true;
		}
		
		return false; //otherwise false
	}
}
