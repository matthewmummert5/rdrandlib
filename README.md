Developer Contact Info:
matthewmummert5 <?/!_a_t_|!?> gmail <D _ 0 _ t> com



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


1)COMPILATION NOTES:

This program was successfully compiled with the GCC compiler on a 64-bit linux system. If you know that your machine supports the RDRAND instruction, then compile the "librdrand.c" file with the "main.c" file to test out getting random numbers



2)Testing for RDRAND support:

Please note that only Intel CPUs support the RDRAND instruction. Don't try use this software on an AMD or an ARM chip. If you email me asking why these libraries don't work on your Raspberry Pi, I'll just laugh. If you are unsure that your **INTEL** machine supports the RDRAND instruction, then compile main.c with rdrandlib.c (you can use the makefile), and that program will test for RDRAND support, as well as generate a few random numbers if your CPU DOES support it.

