#include <stdio.h>
#include <string.h>
#include <math.h>

/*
	Alex Hromada
	anhromad
	M45218886
	Program 6: Unigram
	CS1142
	Spring 2020
	
	This program creates a language model by reading in a file of text and computing the probability 
	of occurence of each word.
*/

// We assue all words are no more than 63 characters long.
// This requires 64 characters in any array that holds a word since we need 1 for null.
// Instead of sprinkling the magic number 64 everywhere in your code, you should instead
// use the following constant:
#define WORD_ARRAY_SIZE 64

// Function prototypes, this allows the function implementations to appear in any order in the file
// You will be implementing these three functions.
unsigned int hashString(char* str);
double calcUnigramLogProb(unsigned int count, unsigned long total);
void stripUpper(char* str);

// Function prototypes for the test functions we have provided
void testHashString();
void testCalcUnigramLogProb();
void testStripUpper();

// Hash a null-terminated string to an unsigned int.
// Implement as in Java's hashCode for String s, calculates this equation:
//   s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]  (^ denotes exponentiation)
//
// You can follow the Java source code in this discussion: http://tinyurl.com/pqg2al5
//
// NOTE: While the above equation uses exponentiation, it is quite expensive and
// unnecessary to call the pow() function for each character. Also you will not get
// the same answer as us for long strings. You can do the calculation using only
// multiplication and addition. HINT: Can you reorder the calculation?
unsigned int hashString(char* str)
{
   int hash = 0;
   for(size_t i = 0; i < strlen(str); i++)
   {
	   hash = 31 * hash + str[i];
   }
   return hash;
}

// Calculate log probability of a word occurring count times in total words of data.
// Result is in log base 10.
double calcUnigramLogProb(unsigned int count, unsigned long total)
{
   return log10((double) count) - log10((double) total);
}

// Strip the null-terminated string str of characters that aren't letters or apostrophe.
// Converts all lowercase letters to uppercase.
// This operates in place on the string str.
void stripUpper(char* str)
{
	size_t len = strlen(str);
	if (len == 0)
		return;
	
	int i = 0;
	while(str[i] != '\0')
	{
		// While there is a sequence of characters that are not alphabetical, apostrophe, or
		// a null terminator
		while(!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') 
			|| str[i] == 39 || str[i] == '\0'))
		{
			int j = i;
			// Shift all characters 1 to the left 
			while(str[j] != '\0')
			{
				str[j] = str[j + 1];
				j++;
			}
			str[j] = '\0'; // Set the end character to a null terminator
		}
		
		// Set all lowercase characters to uppercase
		if(str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		i++;
	}
}

// Test function for the hashString function.
// Do NOT change this function.
void testHashString()
{
   char tests[][WORD_ARRAY_SIZE] = {"BAD", "DAB", "GOODFELLOWS", "WRITERSHIP", "a", "A", "abcdefghijklmnopqrstuvwxyz", "1234567890!@#$%^&*()", ""};

   int i = 0;
   while (strlen(tests[i]) > 0)
   {
      printf("\"%s\" -> %u\n", tests[i], hashString(tests[i]));
      i++;
   }
}

// Test function for the calcUnigramLogProb function.
// Do NOT change this function.
void testCalcUnigramLogProb()
{
   const int SIZE = 8;
   unsigned int  counts[] = { 5 ,  50 ,   1,    1,   1234,   0 , 100 , 1};
   unsigned long totals[] = {10 , 100 , 100, 2000, 567890, 123 , 100 , 1};
   
   for (int i = 0; i < SIZE; i++)
   {
      printf("%5u %7lu -> %9.6f\n", counts[i], totals[i], calcUnigramLogProb(counts[i], totals[i]));
   }
}

// Test function for the stripUpper function.
// Do NOT change this function.
void testStripUpper()
{
   char tests[][WORD_ARRAY_SIZE] = {"bad", "BAD", "BaD", "CAN'T", "well-done", "!L00K-", "1234567890", ""};
   
   int i = 0;
   while (strlen(tests[i]) > 0)
   {
      printf("\"%s\" -> ", tests[i]);
      stripUpper(tests[i]);
      printf("\"%s\" (len %zu)\n", tests[i], strlen(tests[i]));
      i++;
   }
}

int main(int argc, char** argv)
{
   // If no command line input we print out a help message and also run test functions
   if (argc <= 1)
   {
      printf("Usage: Unigram <hash table size> [debug]\n\n");
      testHashString();
      printf("\n");
      testCalcUnigramLogProb();
      printf("\n");
      testStripUpper();
      return 0;
   }

	const int TABLE_SIZE = atoi(argv[1]);
	int debug = 0;
	
	// Ends program if table size is not a positive value and prints an error message
	if(TABLE_SIZE < 1)
	{
		printf("Table size must be positive!\n");
		return 0;
	}
	
	// Sets the debug value to print debug info if specified in command line
	if(argc == 3)
	{
		debug = atoi(argv[2]);
	}
	
	char keys[TABLE_SIZE][WORD_ARRAY_SIZE]; // Array for hash table
	unsigned int count[TABLE_SIZE];			// Array for count of each word
	unsigned long total = 0;				// Total number of words in file
	
	// Fills hash table with empty strings
	for(int i = 0; i < TABLE_SIZE; i++)
	{
		strcpy(keys[i], "");
	}
	
	// Initialize all values in count array to 0
	for(int i = 0; i < TABLE_SIZE; i++)
	{
		count[i] = 0;
	}
	
	char buffer[WORD_ARRAY_SIZE];
	
	// Start reading from file and adding words to the hash table
	int tableSize = 0;
	while(scanf("%63s", buffer) != EOF)
	{
		// End program if the table fills before all words are inserted into hash table
		if(tableSize == TABLE_SIZE)
		{
			printf("ERROR: hash table is full!\n");
			
			// For debugging
			// for(unsigned int i = 0; i < TABLE_SIZE; i++)
			// {
			//		printf("%u %s\n", i, keys[i]);
			// }		
			
			return 0;
		}
		
		stripUpper(buffer);

		// As long as stripUpper method did not return an empty string, add to hash table
		if(strcmp(buffer, ""))
		{
			unsigned int hash = hashString(buffer);		// Get hashcode for the string
			unsigned int bucket = hash % TABLE_SIZE;	// Get the bucket to add string in hash table
			unsigned int index = bucket;				// Index to use if collision occurs
		
			do
			{
				// If the index is empty, add to table
				if(!strcmp(keys[index], ""))
				{
					strcpy(keys[index], buffer);
					count[index] = count[index] + 1;
					total++;
					tableSize++;
					break;
				}
				// If string already exists in table, increment the count
				else if(!strcmp(keys[index], buffer))
				{
					count[index] = count[index] + 1;
					total++;
					break;
				}
				// Increment index if index is not available
				else
				{
					index = (index + 1) % TABLE_SIZE;
				}
		
			} while(index != bucket);
		
			if(debug)
			{
				printf("%s -> hash %u, bucket %u, stored at %u, count %u\n", buffer, hash, bucket, index, count[index]);
			}
		}
		
	}
	
	// Print off all words from hash table with probability of occurence
	for(int i = 0; i < TABLE_SIZE; i++)
	{
		if(count[i] != 0 && strcmp(keys[i], ""))
		{
			double prob = calcUnigramLogProb(count[i], total);
			printf("%.6f %s\n", prob, keys[i]);
		}
	}
	
   return 0;
}
