//Author: Abdullah Khan
//Description: this takes and image and makes it twice the size in terms of number of pixels

import java.awt.Color;

public class MagnifyOperation implements ImageOperation{
	
	public Color[][] doOperation(Color[][] imageArray)
	{
		int numOfRows = imageArray.length; //set the imageArray's length to the number of rows 
		int numOfColumns = imageArray[0].length; //set the imageArray's length to the number of columns
		
		Color[][] result = new Color[numOfRows * 2][numOfColumns * 2]; //this creates a color array with the number of rows and columns that we got from above
		
		for (int i = 0, c1 = 0; i < numOfRows; i++, c1 += 2) //loops through the rows
		{			
			for (int j = 0, c2 = 0; j < numOfColumns; j++, c2 += 2) //loops through the columns
			{
				//all the colors of the imageArray pixel are set
				int red = imageArray[i][j].getRed();
				int green = imageArray[i][j].getGreen();
				int blue = imageArray[i][j].getBlue();
				
				result[c1][c2] = new Color(red, green, blue);
				result[c1 + 1][c2] = new Color(red, green, blue);
				result[c1][c2 + 1] = new Color(red, green, blue);
				result[c1 + 1][c2 + 1] = new Color(red, green, blue);
			}
		}
		
		return result; //return the resulting image
	}

}
