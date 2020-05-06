#include <stdio.h>
#include <stdlib.h>

/*
	Alex Hromada
	Program 4: Random
	CS1142
	Spring 2020
	
	Generates random sentences based on words passed in, a probability of continuation, and a
	seed for which we seed the random number generator
*/

int main(int argc, char** argv){
	
	if(argc < 5){
		printf("SentenceInventor <number> <probability> <seed> <word1> [word2] ...\n");
		return 0;
	}
	
	const int NUM_SENT = atoi(argv[1]);
	const float PROB_SENT = atof(argv[2]);
	
	srand(atoi(argv[3]));
	
	char* words[argc - 3];
	
	
	// Copies the strings from argv into a new array
	int nextIndex = 0;
	int size = 0;
	for(int i = 4; i < argc; i++){
		char* word = argv[i];
		words[nextIndex] = word;
		nextIndex++;
		size++;
	}
	words[nextIndex] = 0;
	
	int randIndex = 0;
	double randProb = 0;
	int numWords = 0;
	
	// Loop through for the amount of sentences specified
	for(int i = 0; i < NUM_SENT; i++){
				
		// Get a random number for index of array
		randIndex = rand() % (size);
		printf("%s", words[randIndex]);
		numWords++;
	
		// Generates a new probability for continuation
		randProb = (double) (rand() % 100) / 100;
		
		// Loop as long as the generated probability is less than the input probability
		while(randProb < PROB_SENT){
			
			// Grabs a random index from the array
			randIndex = rand() % (size);
			printf(" %s", words[randIndex]);
			numWords++;
		
			// Generate new random probability
			randProb = (double) (rand() % 100) / 100;
		
		}
		printf(".\n");
		
	}
	
	// Calculate the average
	double avgWords = (double) numWords / NUM_SENT;

	printf("Total sentences = %d \n", NUM_SENT);
	printf("Average words per sentence = %.2f\n", avgWords);
	
	return 0;
	
}