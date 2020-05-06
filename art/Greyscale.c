#include <stdio.h>
#include <stdlib.h>

/*
	Alex Hromada
	anhromad
	M45218886
	Program Final: Art
	CS1142
	Spring 2020
	
	This program reads in an rgb image file and converts the rgb to greyscale and outputs
*/

// Pixel Structure that contains the rgb values of the pixel
// as well as the computed greyscale value
typedef struct
{
	int rVal;   // Value of red
	int gVal;	// Value of green
	int bVal;	// Value of blue
	double grey;  // Greyscale value
	
} Pixel;

// Image Structure
// Contains 2D array of pixels
typedef struct
{
	int rows;
	int cols;
	Pixel** pixels;  // 2D Array of pixels
	
} Image;

// Funciton prototypes
void imageUninit(Image* image);

/*
	Deallocates image object and frees memeory
*/
void imageUninit(Image* image)
{
	for(int i = 0; i < image->rows; i++)
	{
		free(image->pixels[i]);
		image->pixels[i] = NULL;
	}
	
	free(image->pixels);
	image->pixels = NULL;
}

int main()
{

	int rows = 0;
	int cols = 0;
	
	scanf("%d %d", &rows, &cols);
	
	Image image;
	
	image.rows = rows;
	image.cols = cols;
	
	// Allocation of memory for the image
	image.pixels = malloc(sizeof(Pixel*) * image.rows);
	for(int i = 0; i < image.rows; i++)
	{
		image.pixels[i] = malloc(sizeof(Pixel) * image.cols);
		for(int j = 0; j < image.cols; j++)
		{
			Pixel pixel;
			pixel.rVal = 0;
			pixel.gVal = 0;
			pixel.bVal = 0;
			pixel.grey = 0.0;
			image.pixels[i][j] = pixel;
		}
		
	}
	
	// Buffer array to hold rgb values
	int buff[3];
	
	// Reading in the pixel data from the rgb file
	for(int i = 0; i < image.rows; i++)
	{
		int j = 0;
		int buffIndex = 0;
		while(scanf("%d", &buff[buffIndex]) != EOF)
		{
			Pixel* curr = &image.pixels[i][j];
			
			switch(buffIndex)
			{
				case 0:
					curr->rVal = buff[buffIndex];
					buffIndex += 1;
					break;
				case 1:
					curr->gVal = buff[buffIndex];
					buffIndex += 1;
					break;
				case 2:
					curr->bVal = buff[buffIndex];
					buffIndex = 0;
					j++;
					break;
			}
			
			if(j == cols)
				break;
		}
		
	}
	
	// Conversion of rgb values to greyscale
	for(int i = 0; i < image.rows; i++)
	{
		for(int j = 0; j < image.cols; j++)
		{
			Pixel* curr = &image.pixels[i][j];
			double rFrac = (double) curr->rVal / 255;
			double gFrac = (double) curr->gVal / 255;
			double bFrac = (double) curr->bVal / 255;
			curr->grey = (0.299 * rFrac) + (0.587 * gFrac) + (0.114 * bFrac);
		
		}
	}

	// Display of the greyscale values
	printf("%d %d\n", image.rows, image.cols);
	for(int i = 0; i < image.rows; i++)
	{
		for(int j = 0; j < image.cols; j++)
		{
			Pixel* curr = &image.pixels[i][j];
			printf("%.6f ", curr->grey);
			
		}
		printf("\n");
	}

	
	imageUninit(&image);

	return 0;

}