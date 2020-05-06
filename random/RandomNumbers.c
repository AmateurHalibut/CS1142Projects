#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h> 

/*
	Alex Hromada
	Program 4: Random
	CS1142
	Spring 2020
	
	This program generates random numbers based on a number of bits, a seed, and a tap bit
	from which to shift and modify the number
*/

unsigned int toDecimal(bool *bitArray, int b);

int main(int argc, char** argv){
	
	if(argc < 5){
		printf("RandomNumbers <bits> <seed> <tap bit> <numbers>\n");
		return 0;
	}
	
	const int BITS 		= atoi(argv[1]);
	unsigned int seed 	= atoi(argv[2]);
	const int TAP_BIT 	= atoi(argv[3]);
	const int NUMS		= atoi(argv[4]);
	
	unsigned int maxNum = 2;
	for(int i = 0; i < BITS - 1; i++){
		maxNum = maxNum * 2;
	}
	
	if(BITS > 31 || BITS < 0){
		printf("Invalid input!\n");
		return 0;
	}
	
	if(seed < 0 || seed > maxNum - 1){
		printf("Invalid input!\n");
		return 0;
	}

	if(TAP_BIT < 0 || TAP_BIT >= BITS){
		printf("Invalid input!\n");
		return 0;
	}
	
	bool bits[BITS];
	
	// Fills an array with boolean values representing bit values
	// Fille so that least significant bit is at index 0
	unsigned int divisor = maxNum / 2;
	int j = BITS - 1;
	while(divisor > 0){
		if(seed >= divisor){
			bits[j] = true;
			j--;
			seed -= divisor;
		} else{
			bits[j] = false;
			j--;
		}
		divisor = divisor / 2;
	}
	
	unsigned int decimalVal = toDecimal(bits, BITS);
	
	// Prints off binary value
	for(int i = BITS - 1; i >= 0; i--){
		if(bits[i]){
			printf("1");
		}
		else {
			printf("0");
		}
	}
	printf(" = %d\n", decimalVal);

	// Generating the random number using left shift and XOR
	int tapBit = 0;
	int mSB = 0;
	int newBit = 0;
	bool newBool = false;
	
	// Iterates through each number generation
	for(int i = 0; i < NUMS - 1; i++){
		
		tapBit = 	(int) bits[TAP_BIT];
		mSB = 		(int) bits[BITS - 1];
		newBit = 	tapBit ^ mSB;		// XORs tapbit with MSB
		newBool = 	(bool) newBit;
		
		for(int k = BITS - 1; k > 0; k--){
			bits[k] = bits[k - 1];
		}
		bits[0] = newBool;
		
		// Converts binary back to decimal
		decimalVal = toDecimal(bits, BITS);
	
		// Prints off binary value
		for(int i = BITS - 1; i >= 0; i--){
			if(bits[i]){
				printf("1");
			}
			else {
				printf("0");
			}
		}
		printf(" = %d\n", decimalVal);

	}

	return 0;
	
}

/*
	Computes a power of 2
*/
int powerOf2(int n){
	
	// Base Case that returns 1 when power is 0, 2 if power is 1
	if(n == 0){
		return 1;
	}
	if(n == 1){
		return 2;
	}
	
	int half = powerOf2(n / 2);
	
	if(n % 2 == 0){
		return half * half;
	}
	else{
		return half * half * 2;
	}
}

/*
	Converts binary value back to decimal value
*/
unsigned int toDecimal(bool *bitArray, int b){
	unsigned int num = 0;
	for(int i = 0; i < b; i++){
		if(bitArray[i]){
			num = num + powerOf2(i);
		}
	}
	return num;
}

