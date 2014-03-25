// dummest.C
//
// Original program:	Jim Heliotis, March 2000
// Updates:
//
//	2000/11/29:	wrc, restructured code
//

// This is an implementation of a class example known as
// "The Dummest Little Computer".  It shows how to use
// some of the features of the "arch" kit.

// The two instructions shown involve the accumulator.
//   op code 0 = clear accumulator
//   op code 1 = add memory to accumulator

#include "includes.h"

int main ( int argc, char *argv[] ) {

	// turn on data flow tracing and memory dump after load
	// |= performs an "or" on the value and saves it

	// CPUObject::debug |= CPUObject::trace | CPUObject::memload;

	// make sure we've been given an object file name

	if( argc != 2 ) {
		cerr << "Usage:  " << argv[0] << " object-file-name\n\n";
		exit( 1 );
	}

	cout << hex; // change base for future printing

	try {

		make_connections();

		run_simulation( argv[1] );

	}

	catch( ArchLibError &err ) {

		cout << endl
		     << "Simulation aborted - ArchLib runtime error"
		     << endl
		     << "Cause:  " << err.what() << endl;
		return( 1 );
	
	}

	return( 0 );
}
