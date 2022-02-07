## 8080 Assembly Emulator & System Call Handler

### Description
This repository provides an emulator of Intel 8080 architecture with a system call handler. I do not have the ownership of the emulator ([8080emu.cpp](8080emu.cpp), [8080emuCPP.h](8080emuCPP.h)), yet I am sharing here as it is free to do so. The repository also comes with example assembly functions:

* Collatz.asm: Computes the numbers of Collatz conjecture from 1 to 25.
* Facrorize.asm: Calculates the factors of the number given in *input.txt*
* Palindrome.asm: Checks whether given number in *input.txt* is palindrome or not.
* ShowPrimes.asm: Calculates the prime numbers from 0 to 1000.

***

* In order to compile the program you only need a *g++* compiler. 
* To run the program without an error, create two files in the same directory: *input.txt* and *output.txt*. 
	* As explained above, Factorize.asm and Palindrome.asm functions take the required value from the *input.txt*, and all the output is written into *output.txt*
* Convert the *.asm* files into .com files using the following web site: http://sensi.org/~svo/i8080/
	* Paste the content of *.asm* file into this site
	* Click on the "make beatufil code" button
	* Download, and place the file ending with .com into the same directory.

### Example
After a successfull compilation, run for ShowPrimes:

	 $ ./main ShowPrimes.com 0
	 $ cat output.txt
	 	0
		1
		2 prime
		3 prime
		4
		5 prime
		6
		7 prime
		...
	
Run for Factorization. Change the content of input.txt as you wish, and after executing check the output.txt!

	 $ cat input.txt
	 	16
	 $ ./main Factorize.com 0
	 $ cat output.txt
		1
		2
		4
		8
		16
	
***

#### ToDo:
* Add Microkernel handling multiprogramming, interrupt handling and a bit of memory management.