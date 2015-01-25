//This program demonstrates proper use of generating random numbers with the rdrandlib functions

#include <stdio.h>
#include "rdrandlib.h"


int main(void)
{
	int success;
	int rdrand_support;
	int i;
	unsigned char randomChar;
	int randomInt;
	int randomInts[500];

	//First, we check to see if rdrand is available on the processor
	rdrand_support = Check_RDRAND_Support();

	if (RDRAND_SUPPORTED == rdrand_support)
	{
		printf("RDRAND instruction IS supported on this processor\n");
	}

	if(RDRAND_NOT_SUPPORTED == rdrand_support)
	{
		printf("RDRAND instruction IS NOT supported on this processor\n");
		printf("Exiting Program\n");
		return 0;
	}





	printf("This purpose of this program is to test the RDRAND library\n");

	printf("\nGenerating a single random byte...\n");


	//always check to make sure rdrand instruction didn't fail
	//it can occasionally happen when maxing it out on multiple threads
	//although this is extremely unlikely since these functions will
	//automatically retry 10 times
	if( RDRAND_FAIL == rdrand_getRandom8(&randomChar))
	{
		printf("RDRAND failed to generate a random char\n");
	}

	else
	{
		printf("Random Char: %hhx\n", randomChar);
	}

	
	printf("\nGenerating a single random integer...\n");

	if( RDRAND_FAIL == rdrand_getRandom32(&randomInt))
	{
		printf("RDRAND failed to generate a random integer\n");
	}

	else
	{
		printf("Random Integer: %x\n", randomInt);
	}

	printf("Generating an array of 10 random integers...\n");

	if( RDRAND_FAIL == fill_buffer_int_rdrand(randomInts, 10))
	{
		printf("RDRAND failed to generate an array of random integers\n");
	}

	else
	{
		for(i = 0; i < 10; i++)
		{
			printf("%x\n", randomInts[i]);
		}

	}

	printf("\n");

	//you would use this function to simulate rolling dice, for instance
	//it generates a random number within the programmer's specified range
	if( RDRAND_FAIL == rdrand_getRandom_range(&randomInt,1,6))
	{
		printf("RDRAND failed to generate a random integer\n");
	}
	else
	{
		printf("Fetching a random number between 1 and 6: %d\n", randomInt);
	}
	

	return 0;

}
