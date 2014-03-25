// execute.C
//
// Modified program: 	Jenny Zhen, March 2014
// Original program:	Jim Heliotis, March 2000
// Updates:
//
//	2000/11/29:	wrc, restructured code
//	2001/12/10:	wrc, split execute() into separate routines
//
// Instruction execution routine for the dummest little computer.

#include "includes.h"

//
// store_to_mem() - store accumulator to memory address given.
//
// RTL (Register Transfer Language)
// MAR <- IR[11-0], MDR <- AC
// Mem[MAR] <- MDR
//
// Code 1
//

// void store_to_mem() {

	// // MAR <- IR[11-0], MDR <- AC
	// // The parallelization is simulated by the Clock::tick() for this CPU.
	// abus.IN().pullFrom(ir);
	// m.MAR().latchFrom(abus.OUT());

	// dbus.IN().pullFrom(ac);
	// mdr.latchFrom(dbus.OUT());

	// Clock::tick();

	// // Mem[MAR] <- MDR
	// m.WRITE().pullFrom(mdr);
	// m.write();

// }

//
// execute() - decode and execute the instruction
//

void execute() {
	long opc;
	const char* mnemonic;

	// In each case, note that the last set of operations aren't actually performed 
	// until we leave the switch statement.
	//
	// instr format:  opcode = bits 14:12, address = bits 11:0

	opc = ir( DATA_BITS-1, DATA_BITS-3 );

	switch( opc ) {

		// case 8: clear_ac();								 mnemonic = "CLEAR";	break;

		default:
			cout << endl << "MACHINE HALTED due to unknown op code" << opc << endl;
			done = true;
	}

	//if (opc != 4 && opc != 7)
		//printf("%5s %03x   AC=%04x", mnemonic, ir(DATA_BITS - 4, 0), ac.value());

	Clock::tick();

}
