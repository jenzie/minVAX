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

const unsigned int ADDR_BITS( 8 ); // 8-bit address => 256 units of memory
const unsigned int DATA_BITS( 8 ); // 8-bit unit size (00-FF)

//
// Buses
//

Bus abus( "ADDRBUS", ADDR_BITS ); // bus to carry memory addresses
Bus dbus( "DATABUS", DATA_BITS ); // bus to carry data and instructions

//
// Registers
//

StorageObject aux( "AUX", DATA_BITS );		// auxiliary register
StorageObject ir( "IR", DATA_BITS );        // instruction register
StorageObject addr( "ADDR", ADDR_BITS );	// address register
Counter r0( "R0", DATA_BITS );				// R0 register
Counter r1( "R1", DATA_BITS );				// R1 register
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
long immediate ( -1 );		// immediate value for address modes that use it
long savedPC;				// used for printing trace output
long savedIR;				// used for printing trace output