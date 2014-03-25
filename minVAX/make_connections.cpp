// make_connections.C
//
// Modified program: 	Jenny Zhen, March 2014
// Original program:	Jim Heliotis, March 2000
// Updates:
//
//	2000/11/29:	wrc, restructured code
//
// Component connection function.  At execution time, this will
// connect all the CPU components according to the design of
// the architecture.

#include "includes.h"

//
// make_connections() - define connections for registers/StorageObjects.
// Connections for buses are not defined: ABus, DBus, ALU.
// Connections for special components are not defined: Memory.
// Special components do not directly read/write from anything.
//
void make_connections() {

	ir.connectsTo( dbus.OUT() );
	ir.connectsTo( m.READ() );
	
	aux.connectsTo( abus.IN() );
	aux.connectsTo( abus.OUT() );
	aux.connectsTo( dbus.IN() );
	aux.connectsTo( dbus.OUT() );
	aux.connectsTo( m.READ() );
	aux.connectsTo( m.WRITE() );
	
	pc.connectsTo( abus.IN() );
	pc.connectsTo( abus.OUT() );
	pc.connectsTo( alu.OP1() );
	
	addr.connectsTo( alu.OP2() );
	addr.connectsTo( m.READ() );
	addr.connectsTo( dbus.IN() );
	addr.connectsTo( dbus.OUT() );
	
	r0.connectsTo( alu.OP1() );
	r0.connectsTo( alu.OP2() );
	r0.connectsTo( dbus.IN() );
	r0.connectsTo( dbus.OUT() );

	r1.connectsTo( alu.OP1() );
	r1.connectsTo( alu.OP2() );
	r1.connectsTo( dbus.IN() );
	r1.connectsTo( dbus.OUT() );
	
	m.MAR().connectsTo( abus.OUT() );
}
