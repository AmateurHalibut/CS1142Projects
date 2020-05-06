#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

/*
	Alex Hromada
	anhromad
	M45218886
	Program 5: Tunnel
	CS1142
	Spring 2020
	
	This program reads in a file of a row and column value along with a 2D grid of integer values
	and reads them into a 2D array and uses a greedy algorithm to 
*/

void printTunnel(int row, int col, int a[row][col]);
void checkEast(int row, int col, int a[row][col], int *min, int *dir, int x, int y);
void checkSouth(int row, int col, int a[row][col], int *min, int *dir, int x, int y);
void checkNorth(int row, int col, int a[row][col], int *min, int *dir, int x, int y);
void checkWest(int row, int col, int a[row][col], int *min, int *dir, int x, int y);
int checkSur(int row, int col, int a[row][col], int dir, int x, int y);
void dig(int row, int col, int a[row][col], int startRow, int *l, int *c, int verbose);

/*
	Prints the current 2D array
*/
void printTunnel(int row, int col, int a[row][col])
{
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			if(a[i][j] == 0)
				printf(".");		
			else
				printf("%d", a[i][j]);
			
			if(j == col - 1)
				printf("\n");
			
		}
		
	}
	
	printf("\n");
}

/*
	Checks the value for easterly travel
*/
void checkEast(int row, int col, int a[row][col], int *min, int *dir, int x, int y)
{
	// Backtracking check
	if(a[y][x + 1] == 0)
		return;
	
	if(a[y][x + 1] < *min)
	{	
		*min = a[y][x + 1];
		*dir = 0;
	}
}

/*
	Checks the value for eoutherly travel
*/
void checkSouth(int row, int col, int a[row][col], int *min, int *dir, int x, int y)
{
	// Bounds check
	if(y + 1 >= row)
		return;
	
	// Backtracking check
	if(a[y + 1][x] == 0)
		return;
	
	if(a[y + 1][x] < *min)
	{
		*min = a[y + 1][x];
		*dir = 1;
	}
}

/*
	Checks the value for northerly travel
*/
void checkNorth(int row, int col, int a[row][col], int *min, int *dir, int x, int y)
{
	// Bounds check
	if(y - 1 < 0)
		return;
	
	// Backtracking check
	if(a[y - 1][x] == 0)
		return;
	
	if(a[y - 1][x] < *min)
	{
		*min = a[y - 1][x];
		*dir = 2;
	}
}

/*
	Checks the value for westerly travel
*/
void checkWest(int row, int col, int a[row][col], int *min, int *dir, int x, int y)
{
	// Bounds check
	if(x - 1 < 0)
		return;
	
	// Backtracking check
	if(a[y][x - 1] == 0)
		return;
	
	if(a[y][x - 1] < *min)
	{
		*min = a[y][x - 1];
		*dir = 3;
	}
}


/*
	Checks surrounding elements and returns an int value for which direction to dig
*/
int checkSur(int row, int col, int a[row][col], int dir, int x, int y)
{
	// Start min from a value greater than 9
	int min = 10;
	
	// Directional checks
	checkEast(row, col, a, &min, &dir, x, y);
	checkSouth(row, col, a, &min, &dir, x, y);
	checkNorth(row, col, a, &min, &dir, x, y);
	checkWest(row, col, a, &min, &dir, x, y);
	
	return dir;	
}

/*
	Digging algorithm
	Loops through points until you reach the right end of the grid or hits a deadend
*/
void dig(int row, int col, int a[row][col], int startRow, int *l, int *c, int verbose)
{
	int x = 0;
	int y = startRow;
	
	*l = *l + 1;
	*c = *c + a[y][x];
		
	a[y][x] = 0;
	
	// Loop until the program hits the right most side of the grid
	while(x < col - 1)
	{
		// Set direction for movement
		// End = -1
		// East = 0
		// South = 1
		// North = 2
		// West = 3
		int direction = -1;
		
		direction = checkSur(row, col, a, direction, x, y);
		
		// Breaks out of the loop if no direction can be traversed
		if(direction == -1)
			break;
		
		// Prints the grid each iteration as long as verbose is a non-zero value
		if(verbose != 0)
			printTunnel(row, col, a);
		
		// Checks the value of direction and increments x or y accordingly
		if(direction == 0)
			x++;
		else if(direction == 1)
			y++;
		else if(direction == 2)
			y--;
		else if(direction == 3)
			x--;
		
		// Update length and cost values
		*l = *l + 1;
		*c = *c + a[y][x];
		
		// Set current pos to 0
		a[y][x] = 0;
	}
}


int main(int argc, char** argv){
	
	if(argc < 2)
	{
		printf("Tunnel <start row> [verbose]\n");
		return 0;
	}
	
	int startRow = atoi(argv[1]);
	int verbose = 0;
	
	if(argc == 3)
	{
		verbose = atoi(argv[2]);
	}
		
	int row 		= 0;
	int col 		= 0;
	int maxDif 		= 1;
	int minDif 		= 9;
	
	scanf("%d %d", &row, &col);
	
	if(startRow > row)
	{
		printf("Invalid starting row!\n");
		return 0;
	}
	
	int cave[row][col];
	int dataPoints = row * col;
	int totalDif = 0;
	double aveDif = 0.0;

	// Read through all the data points to get the total number of points and
	// average value of the points
	int currData = 0;
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			scanf("%d", &currData);
			
			if(currData < minDif)
				minDif = currData;
			else if(currData > maxDif)
				maxDif = currData;
			
			totalDif += currData;
			cave[i][j] = currData;
			
		}
		
	}
	
	aveDif = (double) totalDif / dataPoints;
	
	printf("Data points: %d\n", dataPoints);
	printf("Avg difficulty: %.3f\n", aveDif);
	printf("Min difficulty: %d\n", minDif);
	printf("Max difficulty: %d\n", maxDif);
	printf("\n");
	
	int length = 0;
	int cost = 0;

	// Run digging algorithm
	dig(row, col, cave, startRow, &length, &cost, verbose);
	
	printTunnel(row, col, cave);
	
	printf("Length = %d\n", length);
	printf("Cost = %d\n\n", cost);
	
}