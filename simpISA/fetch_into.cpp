// fetch_into.C
//
// Original program:	Jim Heliotis, March 2000
// Updates:
//
//	2000/11/29:	wrc, restructured code
//
// Move a word from the specified location in memory to the
// indicated destination via a particular bus.

#include "includes.h"

void fetch_into( StorageObject &addr, Bus &bus, StorageObject &dest ) {

	// move address into MAR

	bus.IN().pullFrom( addr );
	m.MAR().latchFrom( bus.OUT() );
	Clock::tick();

	// read word from memory into destination

	m.read();
	dest.latchFrom( m.READ() );

	// Note that we don't ahve to do the clock tick here; we could,
	// instead, just return, and have the next clock tick issued in
	// the program do the read.  This would cause us to do the read
	// operation and the next operation we set up as parallel
	// actions.  This requires that the next tick be done before we
	// try to use the contents of 'dest'.

	Clock::tick();

}
