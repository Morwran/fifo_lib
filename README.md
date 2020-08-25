## FIFO library
#### The library contains functions for working with FIFO (First In First Out). The library is designed to store arbitrary user-defined data structures in a memory structure such as a FIFO. This library has successfully tested on PC x86 and MCU boards such as STM32 (Cortex M3 and M7 core) and Xilinx Spartan6 (Microblaze core). To use this library in your project, you just need add fifo.c and fifo.h files to your project repository. As for testing how it works, you can build simple test file on your PC using makefile. To do this, you just need to run the following command in the project root directory: 
##### make all
#### After that, you can easily run the test using a command such as ./test on the bash command line.