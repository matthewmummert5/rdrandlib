/*

Copyright (c) 2014 Matthew Mummert

Version: 0.2

Developer Contact Info:
matthewmummert5 <?/!_a_t_|!?> gmail <D _ 0 _ t> com


License Agreement:

This software may be used and distributed in accordance with the MIT open source license.
Use of this software constitutes and agreement to abide by the terms below.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include "rdrandlib.h"



//global variables
static int retry_limit = DEFAULT_RETRY_LIMIT;

//This is an assembly routine that invokes the CPUID instruction and
//checks bit 30 of the ECX register
int Check_RDRAND_Support()
{
	unsigned int ECX;
	//Here we use the CPUID assembly instruction to determine if rdrand is supported.
	//In order to check for RDRAND support using the CPUID instruction, we first need
	//to load the number "1" into the EAX register, and the number "0" in the ECX
	//register. a quick way to zero the ECX register is to Exclusive-Or (XOR) it
	//with itself. Hence the instruction "xorl %%ecx, %%ecx"
	asm volatile("							;\
					movl $1, %%eax			;\
					xorl %%ecx, %%ecx 		;\
					cpuid 					;\
					movl %%ecx, %0 			;\
				"
				:"=r" (ECX)
				);

	//Examine bit 30 of the ECX register
	if( 0x40000000 == (ECX & 0x40000000) )
	{
		return RDRAND_SUPPORTED;
	}

	return RDRAND_NOT_SUPPORTED;


}

//This function takes the number that is passed to it,
//and returns another number consisting of all 1's 
//with the same number of bits as the input argument
unsigned int convert_to_ones(unsigned int number)
{
	unsigned int converted_number = 1;

	while(converted_number <= number)
	{
		converted_number = (converted_number << 1) | 0x1;
	}

	return converted_number;

}

//retrieves an 8-bit random number. Returns 1 if successful, 0 if unsuccessful
static int _rdrand8(char *randomNumber)
{

	unsigned char success;
	short temp;
	short *temp_p = &temp;


	//assembly code that invokes rdrand instruction and stores the result in variable "temp_p"
	//checks carry flag to ensure operation was successful, and stores the result in variable "success"
	asm volatile("rdrand %0 ; setc %1"

	    : "=r" (*temp_p), "=qm" (success));

	//put the random number from temporary variable "temp" into permanent variable "randomNumber"
	*randomNumber = (char) temp;

	//returns "1" if successful and "0" if unsuccessful
	return (int) success;

}

//retrieves a 16-bit random number. Returns 1 if successful, 0 if unsuccessful
static int _rdrand16(short *randomNumber)
{

	unsigned char success;



	//assembly code that invokes rdrand instruction and stores the result in variable "randomNumber"
	//checks carry flag to ensure operation was successful, and stores the result in variable "success"
	asm volatile("rdrand %0 ; setc %1"

	    : "=r" (*randomNumber), "=qm" (success));


	//returns "1" if successful and "0" if unsuccessful
	return (int) success;

}

//retrieves a 32-bit random number. Returns 1 if successful, 0 if unsuccessful
static int _rdrand32(int *randomNumber)
{

	unsigned char success;


	//assembly code that invokes rdrand instruction and stores the result in variable "randomNumber"
	//checks carry flag to ensure operation was successful, and stores the result in variable "success"
	asm volatile("rdrand %0 ; setc %1"

	    : "=r" (*randomNumber), "=qm" (success));


	//returns "1" if successful and "0" if unsuccessful
	return (int) success;

}

//retrieves a 64-bit random number. Returns 1 if successful, 0 if unsuccessful
static int _rdrand64(long long int *randomNumber)
{

	unsigned char success;


	//assembly code that invokes rdrand instruction and stores the result in variable "randomNumber"
	//checks carry flag to ensure operation was successful, and stores the result in variable "success"
	asm volatile("rdrand %0 ; setc %1"

	    : "=r" (*randomNumber), "=qm" (success));


	//returns "1" if successful and "0" if unsuccessful
	return (int) success;

}


//retrieves an 8-bit random number, if operation fails, will retry "retry_limit" number of times. Returns 1 if successful, 0 if unsuccessful
int rdrand_getRandom8(char* randomNumber)
{
	int i; //index variable used in for loop
	int success = RDRAND_FAIL; //used to determine if getting a random number was successful
	char temp; //temporary variable to store the random number

	for( i = 0; i < retry_limit; i++ )
	{
		//check to make sure retrieving the random number was successful
		//stores the result in "randomNumber" if successful and breaks from the for loop
		if (RDRAND_SUCCESS == _rdrand8(&temp))
		{
			*randomNumber = temp;
			success = RDRAND_SUCCESS;
			break;
		}

	}

	return success;

}

//retrieves a 16-bit random number, if operation fails, will retry "retry_limit" number of times. Returns 1 if successful, 0 if unsuccessful
int rdrand_getRandom16(short* randomNumber)
{
	int i; //index variable used in for loop
	int success = RDRAND_FAIL; //used to determine if getting a random number was successful
	short temp; //temporary variable to store the random number

	for( i = 0; i < retry_limit; i++ )
	{
		//check to make sure retrieving the random number was successful
		//stores the result in "randomNumber" if successful and breaks from the for loop
		if (RDRAND_SUCCESS == _rdrand16(&temp))
		{
			*randomNumber = temp;
			success = RDRAND_SUCCESS;
			break;
		}

	}

	return success;

}

//retrieves a 32-bit random number, if operation fails, will retry "retry_limit" number of times. Returns 1 if successful, 0 if unsuccessful
int rdrand_getRandom32(int* randomNumber)
{
	int i; //index variable used in for loop
	int success = RDRAND_FAIL; //used to determine if getting a random number was successful
	int temp; //temporary variable to store the random number

	for( i = 0; i < retry_limit; i++ )
	{
		//check to make sure retrieving the random number was successful
		//stores the result in "randomNumber" if successful and breaks from the for loop
		if (RDRAND_SUCCESS == _rdrand32(&temp))
		{
			*randomNumber = temp;
			success = RDRAND_SUCCESS;
			break;
		}

	}

	return success;

}

//retrieves a 64-bit random number, if operation fails, will retry "retry_limit" number of times. Returns 1 if successful, 0 if unsuccessful
int rdrand_getRandom64(long long int* randomNumber)
{
	int i; //index variable used in for loop
	int success = RDRAND_FAIL; //used to determine if getting a random number was successful
	long long int temp; //temporary variable to store the random number

	for( i = 0; i < retry_limit; i++ )
	{
		//check to make sure retrieving the random number was successful
		//stores the result in "randomNumber" if successful and breaks from the for loop
		if (RDRAND_SUCCESS == _rdrand64(&temp))
		{
			*randomNumber = temp;
			success = RDRAND_SUCCESS;
			break;
		}

	}

	return success;

}

//This function retrieves a random number between min and max
//without introducing the statistical bias of the modulo (%)
//operator. It works by continuously summoning random numbers
//until one in the desired range is found
int rdrand_getRandom_range(int* randomNumber, int min, int max)
{
	int temp = 0;
	int range = max-min;

	//check to make sure the user did not mix up min and max
	if(0 == range)
	{
		*randomNumber = min;
		return RDRAND_SUCCESS;
	}

	//swap max and min if range < 0
	if (range < 0)
	{
		range = -1 * range;
		temp = max;
		max = min;
		min = temp;
		temp = 0;
	}

	//add 1 to range so that the top number in the 
	//desired range will not be excluded
	range++;
	
	do
	{
		//get the random number
		if(RDRAND_FAIL == rdrand_getRandom32(&temp))
		{
			return RDRAND_FAIL;
		}
		
		//Convert the bits of "range" to all 1's, and then
		//logical AND the random number into it. This will zero out all
		//the unnecessary bits in the random number. This will drastically 
		//reduce the number of necessary calls to getRandom32()
		//and increase efficiency without introducing a statistical
		//bias
		temp = temp & convert_to_ones(range);

	} while(temp >= range);
	
	*randomNumber = temp + min;

	return RDRAND_SUCCESS;

}

//Fills a char array of "numberOfElements" length. Returns 1 if successful, 0 if unsuccessful
int fill_buffer_char_rdrand(char* dest, int numberOfElements)
{
	int i;
	char temp8;
	
	for( i = 0; i < numberOfElements; i++ )
	{
		//retrieves the random number
		//If the operation was unsuccessful, returns from the function.
		if (RDRAND_FAIL == rdrand_getRandom8(&temp8))
		{
			//returns "0" indicating that filling the buffer with random numbers was unsuccessful
			return RDRAND_FAIL;
		}

		//If operation was successful, places random number into the next entry in the array
		else
		{
			dest[i] = temp8;
		}

	}

	//returns "1" to indicate that filling the buffer with random numbers was successful
	return RDRAND_SUCCESS;
}

//Fills a short array of "numberOfElements" length. Returns 1 if successful, 0 if unsuccessful
int fill_buffer_short_rdrand(short* dest, int numberOfElements)
{
	int i;
	short temp16;
	
	for( i = 0; i < numberOfElements; i++ )
	{
		//retrieves the random number
		//If the operation was unsuccessful, returns from the function.
		if (RDRAND_FAIL == rdrand_getRandom16(&temp16))
		{
			//returns "0" indicating that filling the buffer with random numbers was unsuccessful
			return RDRAND_FAIL;
		}

		//If operation was successful, places random number into the next entry in the array
		else
		{
			dest[i] = temp16;
		}

	}

	//returns "1" to indicate that filling the buffer with random numbers was successful
	return RDRAND_SUCCESS;
}

//Fills an int array of "numberOfElements" length. Returns 1 if successful, 0 if unsuccessful
int fill_buffer_int_rdrand(int* dest, int numberOfElements)
{
	int i;
	int temp32;
	
	for( i = 0; i < numberOfElements; i++ )
	{
		//retrieves the random number
		//If the operation was unsuccessful, returns from the function.
		if (RDRAND_FAIL == rdrand_getRandom32(&temp32))
		{
			//returns "0" indicating that filling the buffer with random numbers was unsuccessful
			return RDRAND_FAIL;
		}

		//If operation was successful, places random number into the next entry in the array
		else
		{
			dest[i] = temp32;
		}

	}

	//returns "1" to indicate that filling the buffer with random numbers was successful
	return RDRAND_SUCCESS;
}

//Fills a 64-bit long long int array of "numberOfElements" length. Returns 1 if successful, 0 if unsuccessful
int fill_buffer_qint_rdrand(long long int* dest, int numberOfElements)
{
	int i;
	long long int temp64;
	
	for( i = 0; i < numberOfElements; i++ )
	{
		//retrieves the random number
		//If the operation was unsuccessful, returns from the function.
		if (RDRAND_FAIL == rdrand_getRandom64(&temp64))
		{
			//returns "0" indicating that filling the buffer with random numbers was unsuccessful
			return RDRAND_FAIL;
		}

		//If operation was successful, places random number into the next entry in the array
		else
		{
			dest[i] = temp64;
		}

	}

	//returns "1" to indicate that filling the buffer with random numbers was successful
	return RDRAND_SUCCESS;
}




//This function efficiently fills a buffer with random data by calling the 64 bit functions
//whenever possible, and using the 8 bit functions for the remainder 
int rdrand_get_bytes(void* dest, int bytes)
{
	int calls_to_64_bit;
	int calls_to_8_bit;
	int memory_offset;
	long long int *ptr_64bit = dest;
	char *ptr_8bit = dest;

	calls_to_64_bit = bytes / 8;
	calls_to_8_bit = bytes % 8;

	memory_offset = bytes - calls_to_8_bit;

	if ( RDRAND_FAIL == fill_buffer_qint_rdrand( ptr_64bit, calls_to_64_bit) )
	{
		//return "0" to indicate RDRAND failed to generate a random number
		return RDRAND_FAIL;
	}

	if ( RDRAND_FAIL == fill_buffer_char_rdrand((ptr_8bit + memory_offset), calls_to_8_bit) )
	{
		//return "0" to indicate RDRAND failed to generate a random number
		return RDRAND_FAIL;
	}

	
	return RDRAND_SUCCESS;



}





//This function fills a buffer with random numbers between min and max
//without introducing the statistical bias of the modulo (%)
//operator. It works by continuously summoning random numbers
//until one in the desired range is found
int fill_buffer_range_rdrand(int* dest, int numberOfElements, int min, int max)
{
	int i;
	int temp;
	
	for( i = 0; i < numberOfElements; i++ )
	{
		//retrieves a random number between "min" and "max"
		//If the operation was unsuccessful, returns from the function.
		if (RDRAND_FAIL == rdrand_getRandom_range(&temp, min, max))
		{
			//returns "0" indicating that filling the buffer with random numbers was unsuccessful
			return RDRAND_FAIL;
		}

		//If operation was successful, places random number into the next entry in the array
		else
		{
			dest[i] = temp;
		}

	}

	//returns "1" to indicate that filling the buffer with random numbers was successful
	return RDRAND_SUCCESS;

}

int rdrand_get_seed(long long int* randomSeed)
{
	int i;
	int j;
	long long int temp;
	long long int* temp_ptr = &temp;
	unsigned char success = RDRAND_FAIL;

	//invoking the 64-bit rdrand 1022 consecutive times guarentees that the DRBG will be reseeded
	for (i = 0; i < 1022; i++)
		{
			for( j = 0; j < retry_limit; j++ )
			{
				

				//Assembly code that invokes rdrand instruction and stores the result in variable "temp"
				//Checks carry flag to ensure operation was successful, and stores the result in variable "success"
				//We need to use assembly here instead of calling _rdrand64() to guarentee this section will not be 
				//optimized out by the compiler
				asm volatile("rdrand %0 ; setc %1"

	    			: "=r" (*temp_ptr), "=qm" (success));



				if (RDRAND_SUCCESS == (int) success)
				{
					*randomSeed = temp;
					success = RDRAND_SUCCESS;
					break;
				}

			}
			
			
		}

	return success;
}

//This funciton also guarentees that the DRBG will be reseeded by the entropy source between giving you random numbers
//Use this function to seed a CSPRNG (Cryptographically Secure Pseudorandom Number Generator)
//You can also use this function to generate a random key for a block cipher
//Returns 1 if successful, 0 if unsuccessful
int rdrand_seed_CSPRNG(long long int* randomSeed, int number_of_64_bit_blocks)
{
	int i;
	long long int temp;
	for( i = 0; i < number_of_64_bit_blocks; i++ )
	{
		//retrieves the random number
		//If the operation was unsuccessful, returns from the function.
		if (RDRAND_FAIL == rdrand_get_seed(&temp))
		{
			//returns "0" indicating that filling the buffer with random numbers failed
			return RDRAND_FAIL;
		}

		//If operation was successful, places random number into the next entry in the array
		else
		{
			randomSeed[i] = temp;
		}
	}
	return RDRAND_SUCCESS;
}
