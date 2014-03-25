// make_connections.C
//
// Original program:	Jim Heliotis, March 2000
// Updates:
//
//	2000/11/29:	wrc, restructured code
//
// Component connection function.  At execution time, this will
// connect all the CPU components according to the design of
// the architecture.

#include "includes.h"

void make_connections() {

	m.MAR().connectsTo( abus.OUT() );

	mdr.connectsTo( m.WRITE() );
	mdr.connectsTo( m.READ() );
	mdr.connectsTo( dbus.IN() );
	mdr.connectsTo( dbus.OUT() );
	mdr.connectsTo( alu.OP2() );

	ir.connectsTo( abus.IN() );
	ir.connectsTo( dbus.OUT() );

	ac.connectsTo( dbus.IN() );
	ac.connectsTo( dbus.OUT() );
	ac.connectsTo( alu.OP1() );
	ac.connectsTo( alu.OUT() );

	pc.connectsTo( abus.IN() );
	pc.connectsTo( abus.OUT() );
	pc.connectsTo( m.READ() );

}
