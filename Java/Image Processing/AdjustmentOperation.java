//Author: Abdullah Khan
//Description: This operation sets the pixels relative to the array's top left index

import java.awt.Color;

public class AdjustmentOperation implements ImageOperation{

	public Color[][] doOperation(Color[][] imageArray)
	{
		int numOfRows = imageArray.length; //set the imageArray's length to the number of rows
		int numOfColumns = imageArray[0].length; //set the imageArray's length to the number of columns
		
		Color[][] result = new Color[numOfRows][numOfColumns]; //this creates a color array with the number of rows and columns that we got from above
		
		double M = Math.sqrt(Math.pow(numOfRows, 2) + Math.pow(numOfColumns, 2)); //the maximum distance from any pixel to the upper left corner of the image is calculated first using the image size
		
		for (int i = 0; i < numOfRows; i++) //loops through the rows
		{
			for (int j = 0; j < numOfColumns; j++) //loops through the columns
			{
				double D = Math.sqrt(Math.pow(i, 2) + Math.pow(j, 2)); //the current distance from the upper left corner is calculated 
				double adjustBrightness = D / M; //this formula calculates the how much the color of the current image shall change
				
				double r = imageArray[i][j].getRed() * adjustBrightness; //this calculates the alteration of the red
				double g = imageArray[i][j].getGreen() * adjustBrightness; //this calculates the alteration of the green
				double b = imageArray[i][j].getBlue() * adjustBrightness; //this calculates the alteration of the blue
				
				//all the altered color changes are set in double and now we need to convert them to int type
				int red = (int)Math.round(r);
				int green = (int)Math.round(g);
				int blue = (int)Math.round(b);
				
				//the resulting pixel is set using the above calculations
				result[i][j] = new Color(red, green, blue);
			}
		}
		
		return result; //the final pixel array is returned
	}
}
