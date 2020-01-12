//Author: Abdullah Khan
//Description: This operation takes and image and take its brightness score to change pixel colors 

import java.awt.Color;

public class ThresholdingOperation implements ImageOperation{
	
	public Color[][] doOperation(Color[][] imageArray)
	{
		int numOfRows = imageArray.length; //set the imageArray's length to the number of rows
		int numOfColumns = imageArray[0].length; //set the imageArray's length to the number of columns
		
		Color[][] result = new Color[numOfRows][numOfColumns]; //this creates a color array with the number of rows and columns that we got from above
		
		double brightnessScore; //according to the notes, we need to calculate brightness score in order to alter the image
		
		for (int i = 0; i < numOfRows; i++) //loop is for the rows
		{
			for (int j = 0; j < numOfColumns; j++) //loop is for the columns
			{
				brightnessScore = 0.21 * imageArray[i][j].getRed() + 0.71 * imageArray[i][j].getGreen() + 0.07 * imageArray[i][j].getBlue(); //this formula, as in the notes, calculates the brightness score of the pixel
				
				if (brightnessScore > 100) //if the score is higher than 100 the pixel is turned white
				{
					result[i][j] = new Color(255, 255, 255); //sets pixel to be white
				}
				else
				{
					result[i][j] = new Color(0, 0, 0); //otherwise set the pixel to be black
				}
			}
		}
		
		return result; //returns the new array of pixels
	}
}
