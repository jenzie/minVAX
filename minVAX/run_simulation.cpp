// run_simulation.C
//
// Modified program: 	Jenny Zhen, March 2014
// Original program:	Jim Heliotis, March 2000
// Updates:
//
//	2000/11/29:	wrc, restructured code
//	2001/12/10:	wrc, modified simulation control
//
// Primary execution loop for the dummest little computer simulator.

#include "includes.h"

void run_simulation( char *objfile ) {

	// step 1:  load the object file

	m.load( objfile );

	// step 2:  set the entry point
	// get the address of entry point into pc
	
	aux.latchFrom( m.READ() );
	Clock::tick();
	
	abus.IN().pullFrom( aux );
	pc.latchFrom ( abus.OUT() );
	Clock::tick();

	// step 3:  continue fetching, decoding, and executing instructions
	// until we stop the simulation

	while( !done ) {

		// instruction fetch into ir
		// mdr is not needed anymore, since we can directly write into ir

		fetch_into( pc, abus, ir );

		// check for PC overflow
		
		if ( pc.value() >= 0x100 ) {
			cout << endl << "MACHINE HALTED due to PC overflow" << endl << endl;
			done = true;
			break;
		}

		// save the instruction's address (pc) and data (memory data register) 
		// values in hexadecimal
		
		savedPC = pc.value();
		savedIR = ir.value();

		// bump PC for next instruction
		
		pc.incr();
		Clock::tick();

		// decode and execute
		
		execute();
		printf("\n");
	}
}
