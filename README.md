minVAX
======

Simulation of a CISC (Complex Instruction Set Computer) CPU, using the C++ arch package.

execute.cpp  
	Added code to decode the address modes. Added code for the 8-instructions (load, store, isz, jump, halt, bzac, add, and swp).  

globals.cpp  
	Global variables for "minVAX." As per the lab requirements: the MDR and AC were removed; the AUX, ADDR, R0, R1 were added. Globals immediate, savedPC, and savedIR were added to aid the address mode immediates and trace output   
	printing.  
	  
make_connections.cpp  
	Component connection function. At execution time, this will connect all the CPU components according to the design of the architecture.  
	  
run_simulation.cpp  
	The primary execution loop for "minVAX." Added code to print the output.  
	  
minVAX.cpp  
	Contains the main() function for "minVAX." On line 24, debug mode was turned off.  
		  
globals.h  
	Extern declarations of global variables for "minVAX."  
	  
includes.h  
	Contains the system includes, arch library includes, and program specific includes. Added cstdio to use printf for the output.  
	  
prototypes.h  
	Function prototypes for "minVAX."  

