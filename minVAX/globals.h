// globals.h
//
// Original version:	Warren Carithers, November 2000
// Updates:
//
//	2001/12/10:	wrc, modified simulation control
//
// Extern declarations of global variables for the dummest little computer.

#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "includes.h"

extern const unsigned int ADDR_BITS; // 12-bit address => 4096 units of memory
extern const unsigned int DATA_BITS; // 15-bit unit size

extern Bus abus; // bus to carry memory addresses
extern Bus dbus; // bus to carry data and instructions

extern StorageObject aux;   // auxiliary register
extern StorageObject ir;    // instruction register
extern StorageObject addr;  // address register
extern StorageObject r0;    // R0 register
extern StorageObject r1;    // R1 register
extern Counter pc;          // program counter
extern Memory m;            // primary memory
extern BusALU alu;          // arithmetic logic unit

extern bool done;	        // is the simulation over?

#endif
