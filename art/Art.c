#include <stdio.h>
#include <stdlib.h>

/*
	Alex Hromada
	anhromad
	M45218886
	Program Final: Art
	CS1142
	Spring 2020
	
	This program reads in a greyscale file from standard input and outputs the image in 
	ascii form
*/


// Pixel Structure that contains the greyscale value of the pixel
// Used in Image
typedef struct
{
	double grey;  // Greyscale value
	
} Pixel;


//  Image Structure
//  Contains 2D array of pixels
typedef struct
{
	int rows;
	int cols;
	Pixel** pixels;  // 2D Array of pixels
	
} Image;

// Funciton prototypes
void imageUninit(Image* image);
void drawLine(int rowLen);
void printArt(Image* image);
char greyToChar(double greyVal);
void addDelta(double delta, Image* image);

/*
	Prints a line border; used for the top and bottom borders of the output
*/
void drawLine(int rowLen)
{
	printf("+");
	for(int i = 0; i < rowLen; i++)
	{
		printf("-");
	}
	printf("+\n");
}

/*
	Prints the image in ascii form
*/
void printArt(Image* image)
{
	drawLine(image->cols);
	for(int i = 0; i < image->rows; i++)
	{
		printf("|");
		for(int j = 0; j < image->cols; j++)
		{
			Pixel* curr = &image->pixels[i][j];
			char pix = greyToChar(curr->grey);
			printf("%c", pix);
		}
		printf("|\n");
		
	}
	drawLine(image->cols);
	
}

/*
	Returns a character based on a given greyscale value
*/
char greyToChar(double greyVal)
{
	if(greyVal < 0.2)
		return ' ';
	else if(greyVal < 0.4)
		return '.';
	else if(greyVal < 0.6)
		return 'o';
	else if(greyVal < 0.8)
		return 'O';
	else
		return '@';
	
}

/*
	Adds a delta to all of the greyscale values in an image
*/
void addDelta(double delta, Image* image)
{
	for(int i = 0; i < image->rows; i++)
	{
		for(int j = 0; j < image->cols; j++)
		{
			Pixel* curr = &image->pixels[i][j];
			curr->grey = curr->grey + delta;
		}
	}
}

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

int main(int argc, char** argv)
{

	double delta = 0.0;
	
	// Check if a delta was given in command line
	if(argc == 2)
	{
		delta = atof(argv[1]);
	}
	
	int rows = 0;
	int cols = 0;
	
	scanf("%d %d", &rows, &cols);
	
	Image image;
	
	image.rows = rows;
	image.cols = cols;
	
	// Allocate memory for image
	image.pixels = malloc(sizeof(Pixel*) * image.rows);
	for(int i = 0; i < image.rows; i++)
	{
		image.pixels[i] = malloc(sizeof(Pixel) * image.cols);
		for(int j = 0; j < image.cols; j++)
		{
			Pixel pixel;
			pixel.grey = 0.0;
			image.pixels[i][j] = pixel;
		}
		
	}
		
	// Fill image with data from greyscale file
	for(int i = 0; i < image.rows; i++)
	{
		int j = 0;
		double greyVal = 0;
		while(scanf("%lf", &greyVal) != EOF)
		{
			Pixel* curr = &image.pixels[i][j];
			curr->grey = greyVal;
			j++;
			
			if(j == cols)
				break;
		
		}
		
	}
	
	// Checks if a delta was given with a value not 0, save on runtime
	if(delta != 0)
		addDelta(delta, &image);

	// Print the image in ascii form
	printArt(&image);

	imageUninit(&image);

	return 0;

}