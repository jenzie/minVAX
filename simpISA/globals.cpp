// globals.C
//
// Original program:	Jim Heliotis, March 2000
// Updates:
//
//	2000/11/29:	wrc, restructured code
//	2001/12/10:	wrc, modified simulation control
//
// Global variables for the dummest little computer.

#include "includes.h"

//
// Constants
//

const unsigned int ADDR_BITS( 12 ); // 12-bit address => 4096 units of memory
const unsigned int DATA_BITS( 15 ); // 15-bit unit size

//
// Buses
//

Bus abus( "ADDRBUS", ADDR_BITS ); // bus to carry memory addresses
Bus dbus( "DATABUS", DATA_BITS ); // bus to carry data and instructions

//
// Registers
//

StorageObject ir( "IR", DATA_BITS );        // instruction register
Counter mdr( "MDR", DATA_BITS );      	    // memory data register
Clearable ac( "AC", DATA_BITS );            // accumulator
Counter pc( "PC", ADDR_BITS );              // program counter

// 
// Other components
//

Memory m( "Memory", ADDR_BITS, DATA_BITS ); // primary memory
BusALU alu( "Adder", DATA_BITS );           // arithmetic logic unit

//
// Runtime control variables
//

bool done ( false );		// is the simulation over?
