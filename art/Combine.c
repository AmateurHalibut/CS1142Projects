#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
	Alex Hromada
	anhromad
	M45218886
	Program Final: Art
	CS1142
	Spring 2020
	
	This program reads in a mask file, an output file, and one or many greyscale input files and
	uses the mask file to combine the greyscale files into one output file
*/


// Pixel Structure that contains the greyscale value of the pixel
// Used in Image
typedef struct
{
	double grey;  // Greyscale value
	
} Pixel;

// Mask pixel struct that contains the integer value of the pixel in the mask
typedef struct
{
	int pixelVal;  // Greyscale value
	
} MaskPixel;

// Mask struct that contins a 2D array of mask pixels
typedef struct
{
	int rows;
	int cols;
	MaskPixel** maskPixels;  // 2D Array of pixels
	
} Mask;

// Image Structure
// Contains 2D array of pixels
typedef struct
{
	int rows;
	int cols;
	Pixel** pixels;  // 2D Array of pixels
	
} Image;

 // Stats struct that contains the statistics of the output made by the main program
 // Includes pixel count, mean of the greyscale values, min greyscale value, and max greyscale value
typedef struct
{
	int count;
	double mean;
	double min;
	double max;
	
} Stats;



// Funciton prototypes
bool maskInit(Mask* mask, const char* filename);
bool imageInit(Image* image, const char* filename);
void imageEmptyInit(Image* image, int rows, int cols);
void maskUninit(Mask* mask);
void imageUninit(Image* image);
bool writeDouble2DArrayToFile(Image* outImg, const char* filename);
void computeStatsFromDouble2D(Image* image, Stats* stats);
void printStats(Stats* stats);

/*
	Initializes and allocates memory for a mask
	Allocates the 2D array of mask pixels and fills from a file
*/
bool maskInit(Mask* mask, const char* filename)
{
	FILE* in = fopen(filename, "r");
	
	if(in == NULL)
		return false;
	
	fscanf(in, "%d %d", &mask->rows, &mask->cols);		// Read in rows and cols of mask
	
	// Allocation of memory for mask
	mask->maskPixels = malloc(sizeof(MaskPixel*) * mask->rows);
	for(int i = 0; i < mask->rows; i++)
	{
		mask->maskPixels[i] = malloc(sizeof(MaskPixel) * mask->cols);
		for(int j = 0; j < mask->cols; j++)
		{
			MaskPixel pixel;
			pixel.pixelVal = 0;
			mask->maskPixels[i][j] = pixel;
		}
	}
	
	int maxNum = 0;
	int totalNums = 0;
	// Read in mask data
	for(int i = 0; i < mask->rows; i++)
	{
		int j = 0;
		int pixelNum = 0;
		while(fscanf(in, "%d", &pixelNum) != EOF)
		{
			if(pixelNum > maxNum)
				maxNum = pixelNum;
			
			MaskPixel* curr = &mask->maskPixels[i][j];
			curr->pixelVal = pixelNum;
			totalNums += 1;
			j++;
			
			if(j == mask->cols)
				break;

		}
	}
	
	// Calculating the percentages of each integer in the mask file
	int maskStats[maxNum + 1];
	double maskPercents[maxNum + 1];
	for(int i = 0; i <= maxNum; i++)
	{
		maskStats[i] = 0;
		for(int j = 0; j < mask->rows; j++)
		{
			for(int k = 0; k < mask->cols; k++)
			{
				MaskPixel* curr = &mask->maskPixels[j][k];
				if(curr->pixelVal == i)
				{
					maskStats[i] += 1;
				}
			}
		}
	}
	
	// Converting each count of integers to percentages
	for(int i = 0; i <= maxNum; i++)
	{
		maskPercents[i] = 100.0 * ( (double) maskStats[i] / totalNums);
	}
	
	printf("Mask size: %d x %d\n", mask->rows, mask->cols);
	
	for(int i = 0; i <= maxNum; i++)
	{
		printf("Mask %d: %.2lf%%\n", i, maskPercents[i]);
	}

	fclose(in);
	in = NULL;
	
	return true;
	
}

/*
	Initializes and allocates memory for a greyscale image
	Allocates the 2D array of pixels and fills from a file
*/
bool imageInit(Image* image, const char* filename)
{
	
	FILE* in = fopen(filename, "r");
	
	if(in == NULL)
		return false;
	
	fscanf(in, "%d %d", &image->rows, &image->cols);		// Read in rows and cols of image
	
	// Allocation of memory for image
	image->pixels = malloc(sizeof(Pixel*) * image->rows);
	for(int i = 0; i < image->rows; i++)
	{
		image->pixels[i] = malloc(sizeof(Pixel) * image->cols);
		for(int j = 0; j < image->cols; j++)
		{
			Pixel pixel;
			pixel.grey = 0.0;
			image->pixels[i][j] = pixel;
		}
	}
	
	// Read in image data from greyscale file
	for(int i = 0; i < image->rows; i++)
	{
		int j = 0;
		double greyVal = 0;
		while(fscanf(in, "%lf", &greyVal) != EOF)
		{
			Pixel* curr = &image->pixels[i][j];
			curr->grey = greyVal;
			j++;
			
			if(j == image->cols)
				break;

		}
	}

	fclose(in);
	in = NULL;
	
	return true;
	
	
}

/*
	Allocates memory for an empty image object
*/
void imageEmptyInit(Image* image, int rows, int cols)
{
	
	image->rows = rows;
	image->cols = cols;
	
	// Allocation of memory for image
	image->pixels = malloc(sizeof(Pixel*) * image->rows);
	for(int i = 0; i < image->rows; i++)
	{
		image->pixels[i] = malloc(sizeof(Pixel) * image->cols);
		for(int j = 0; j < image->cols; j++)
		{
			Pixel pixel;
			pixel.grey = 0.0;
			image->pixels[i][j] = pixel;
		}
	}
	
	
}

/*
	Writes the data from the output object to a file
*/
bool writeDouble2DArrayToFile(Image* outImg, const char* filename)
{
	FILE* out = fopen(filename, "w");
	
	if(out == NULL)
		return false;
	
	// Loop through to write all elements to the output file
	fprintf(out, "%d %d\n", outImg->rows, outImg->cols);
	for(int i = 0; i < outImg->rows; i++)
	{
		for(int j = 0; j < outImg->cols; j++)
		{
			Pixel* curr = &outImg->pixels[i][j];
			fprintf(out, "%.6f ", curr->grey);
			
		}
		fprintf(out, "\n");
	}
	
	fclose(out);
	out = NULL;
	
	return true;
}

/*
	Computes the statistics of the final output
*/
void computeStatsFromDouble2D(Image* image, Stats* stats)
{
	stats->count = 0;
	stats->mean = 0.0;
	stats->min = 1.0;
	stats->max = 0.0;
	
	stats->count = image->rows * image->cols;  // Total pixels is rows x columes
	
	double totalVal = 0.0;
	for(int i = 0; i < image->rows; i++)
	{
		for(int j = 0; j < image->cols; j++)
		{
			Pixel* curr = &image->pixels[i][j];
			totalVal += curr->grey;  // Update total value for mean calculation
			
			// Update min
			if(curr->grey < stats->min) 
				stats->min = curr->grey;
			
			// Update max
			if(curr->grey > stats->max)
				stats->max = curr->grey;
			
		}
	}
	
	stats->mean = totalVal / (double) stats->count;
}

/*
	Prints all of the data from a stats object
*/
void printStats(Stats* stats)
{
	printf("count = %d, mean = %.6lf, min = %.6lf, max = %.6lf\n", stats->count, 
		stats->mean, stats->min, stats->max);
	
}

/*
	Deallocates and frees memory from a mask object
*/
void maskUninit(Mask* mask)
{
	for(int i = 0; i < mask->rows; i++)
	{
		free(mask->maskPixels[i]);
		mask->maskPixels[i] = NULL;
	}
	
	free(mask->maskPixels);
	mask->maskPixels = NULL;
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
	int inFile = 3;
	int fileNum = 0;
	
    if (argc < 4)
    {
        printf("Combine <mask file> <output file> <grey file0> [grey file1] ...\n");
        return 0;
    }   
	
	const int maxInputFile = argc;
	const int maskFile = 1;
	const int outFile = 2;
	
	Mask mask;
	Image image;
	Image out;
	Stats stats;
	
	
	printf("Opening '%s' for input\n", argv[maskFile]);
	if(!maskInit(&mask, argv[maskFile]))
	{
		printf("ERROR: Can't open '%s' for input!\n", argv[maskFile]);
		return 1;
	}
	
	imageEmptyInit(&out, mask.rows, mask.cols);
	
	// Outer loop to handle each greyscale input
	do{
		
		printf("Opening '%s' for input\n", argv[inFile]);
		if(!imageInit(&image, argv[inFile]))
		{
			printf("ERROR: Can't open '%s' for input!\n", argv[inFile]);
			maskUninit(&mask);
			imageUninit(&out);
			return 1;
		}
		
		if(image.rows != mask.rows || image.cols != mask.cols)
		{
			printf("ERROR: Input file '%s' size %d x %d invalid!\n", argv[inFile], image.rows, image.cols);
			maskUninit(&mask);
			imageUninit(&out);
			return 1;
		}

		// Loop to move the data from each greyscale file to the output file based on the values
		// at the index in the mask file
		for(int i = 0; i < image.rows; i++)
		{
			for(int j = 0; j < image.cols; j++)
			{
				Pixel* curr = &image.pixels[i][j];
				Pixel* currOut = &out.pixels[i][j];
				MaskPixel* currMask = &mask.maskPixels[i][j];
				
				if(currMask->pixelVal == fileNum)
					currOut->grey = curr->grey;
			}
		}
		
		// Free up memory from this image
		imageUninit(&image);			
		inFile += 1;
		fileNum += 1;
		
	} while (inFile < maxInputFile);
	
	
	printf("Opening '%s' for output\n", argv[outFile]);
	if(!writeDouble2DArrayToFile(&out, argv[outFile]))
	{
		printf("Failed to open '%s' for output!\n", argv[outFile]);
		return 1;
	}
	
	computeStatsFromDouble2D(&out, &stats);
	printStats(&stats);
	
	maskUninit(&mask);
	imageUninit(&out);

	return 0;

}