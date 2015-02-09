/*

Copyright (c) 2014 Matthew Mummert

Version: 0.1

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

#ifndef RDRANDLIB_H
#define RDRANDLIB_H


//Some Definitions
#define RDRAND_SUPPORTED 3
#define RDRAND_NOT_SUPPORTED 2
#define RDRAND_SUCCESS 1
#define RDRAND_FAIL 0

//Intel recommends the maximum number of retries should be 10
//If the rdrand instruction fails 10 consecutive times then that
//indicates there is a larger problem with the processor
#define DEFAULT_RETRY_LIMIT 10

//This is an assembly routine that invokes the CPUID instruction and
//checks bit 30 of the ECX register
int Check_RDRAND_Support();

//This function takes the number that is passed to it,
//and returns another number consisting of all 1's 
//with the same number of bits as the input argument
unsigned int convert_to_ones(unsigned int number);


/*DO NOT CALL THESE FOUR FUNCTIONS DIRECTLY TO GENERATE RANDOM NUMBERS*/
/*Instead, use the "rdrand_getRandom()" functions as those functions automatically retry if the operation was unsuccessful*/

static int _rdrand8(char* randomNumber); //retrieves an 8-bit random number. Returns 1 if successful, 0 if unsuccessful
static int _rdrand16(short *randomNumber); //retrieves a 16-bit random number. Returns 1 if successful, 0 if unsuccessful
static int _rdrand32(int* randomNumber); //retrieves a 32-bit random number. Returns 1 if successful, 0 if unsuccessful
static int _rdrand64(long long int* randomNumber); //retrieves a 64-bit random number. Returns 1 if successful, 0 if unsuccessful




/*USE THESE FUNCTIONS BELOW TO GENERATE RANDOM NUMBERS*/

//retrieves an 8-bit random number, if operation fails, will retry a specified number of times. Returns 1 if successful, 0 if unsuccessful
int rdrand_getRandom8(char* randomNumber);

//retrieves a 16-bit random number, if operation fails, will retry a specified number of times. Returns 1 if successful, 0 if unsuccessful
int rdrand_getRandom16(short* randomNumber);

//retrieves a 32-bit random number, if operation fails, will retry a specified number of times. Returns 1 if successful, 0 if unsuccessful
int rdrand_getRandom32(int* randomNumber);

//retrieves a 64-bit random number, if operation fails, will retry a specified number of times. Returns 1 if successful, 0 if unsuccessful
int rdrand_getRandom64(long long int* randomNumber);

//This function retrieves a random number between min and max
//without introducing the statistical bias of the modulo (%)
//operator. It works by continuously requesting random numbers
//until one in the desired range is found
int rdrand_getRandom_range(int* randomNumber, int min, int max);





//Fills a char array of "numberOfElements" length. Returns 1 if successful, 0 if unsuccessful
int fill_buffer_char_rdrand(char* dest, int numberOfElements);

//Fills a short array of "numberOfElements" length. Returns 1 if successful, 0 if unsuccessful
int fill_buffer_short_rdrand(short* dest, int numberOfElements);

//Fills an int array of "numberOfElements" length. Returns 1 if successful, 0 if unsuccessful
int fill_buffer_int_rdrand(int* dest, int numberOfElements);

//Fills a 64-bit long long int array of "numberOfElements" length. Returns 1 if successful, 0 if unsuccessful
int fill_buffer_qint_rdrand(long long int* dest, int numberOfElements);

//This function efficiently fills a buffer with random data by calling the 64 bit functions
//whenever possible, and using the 8 bit functions for the remainder
int rdrand_get_bytes(void* dest, int bytes);

//This function fills a buffer with random numbers between min and max
//without introducing the statistical bias of the modulo (%)
//operator. It works by continuously requesting random numbers
//until one in the desired range is found
int fill_buffer_range_rdrand(int* dest, int numberOfElements, int min, int max);



/*Use the following functions for getting random seeds*/


//This funciton guarentees that the DRBG will be reseeded by the entropy source between giving you random numbers
//It works by calling the 64 bit rdrand instruction repeatedly until the entropy source reseeds the DRBG (1022 times)
//Returns 1 if successful, 0 if unsuccessful
int rdrand_get_seed(long long int* randomSeed);

//This funciton also guarentees that the DRBG will be reseeded by the entropy source between giving you random numbers
//Use this function to seed a CSPRNG (Cryptographically Secure Pseudorandom Number Generator)
//You can also use this function to generate a random key for a block cipher
//Returns 1 if successful, 0 if unsuccessful
int rdrand_seed_CSPRNG(long long int* randomSeed, int number_of_64_bit_blocks);

#endif

