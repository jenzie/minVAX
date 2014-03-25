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
// add_to_ra() - add data to register RA.
//
// RTL (Register Transfer Language)
// RA = RA + data(AM)
//
// Code 1
//

void add_to_ra() {
}

//
// and_to_ra() - bitwise AND data to register RA.
//
// RTL (Register Transfer Language)
// RA = RA & data(AM)
//
// Code 2
//

void and_to_ra() {
}

//
// shift_right_arithmetic() - shift right arithmetic by number of bits 
//      specified by data.
//
// RTL (Register Transfer Language)
// RA = RA >>_a data(AM)
//
// Code 3
//

void shift_right_arithmetic() {
}

//
// shift_left_logical() - shift left logical by number of bits specified 
//      by data.
//
// RTL (Register Transfer Language)
// RA = RA << data(AM)
//
// Code 4
//

void shift_left_logical() {
}

//
// load_to_ra() - load register RA from memory at the effective address 
//      specified by the address mode.
//
// RTL (Register Transfer Language)
// RA <- Mem[ EA ]
//
// Code 5
//

void load_to_ra() {
}

//
// store_to_mem() - store register RA to memory at the effective address 
//      specified by the address mode.
//
// RTL (Register Transfer Language)
// Mem[ EA ] <- RA
//
// Code 6
//

void store_to_mem() {
}

//
// jump() - jump to memory location specified by the effective address.
//
// RTL (Register Transfer Language)
// PC = EA
//
// Code 7
//

void jump() {
}

//
// branch_if_ra_equals_zero() - branch to location at the effective address 
//      if RA is zero.
//
// RTL (Register Transfer Language)
// if RA == 0 then PC = EA
//
// Code 8
//

void branch_if_ra_equals_zero() {
}

//
// branch_if_ra_less_than_zero() - branch to location at the effective address 
//      if RA is less than zero.
//
// RTL (Register Transfer Language)
// if RA < 0 then PC = EA
//
// Code 9
//

void branch_if_ra_less_than_zero() {
}

//
// clear_ra() - clear register RA.
//
// RTL (Register Transfer Language)
// RA = 0
//
// Code 11
//

void clear_ra() {
}

//
// complement_ra() - complement register RA.
//
// RTL (Register Transfer Language)
// RA = !(RA)
//
// Code 12
//

void complement_ra() {
}

//
// increment_ra() - increment register RA.
//
// RTL (Register Transfer Language)
// RA = RA + 1
//
// Code 13
//

void increment_ra() {
}

//
// dump_ra() - dump (print) the value of register RA.
//
// RTL (Register Transfer Language)
// null
//
// Code 14
//

void dump_ra() {
}

//
// halt() - halt the computer.
//
// RTL (Register Transfer Language)
// null
//
// Code 15
//

void halt() {
	printf("%5s %03x\n", "HALT", ir(DATA_BITS - 4, 0));
	cout << endl << "MACHINE HALTED due to halt instruction" << endl;
	done = true;
}

// Functions for decoding effective address, based on address modes (am).

//
// register_am() - The 2nd operand is in reg.
// This can only be used for ALU operations.
//
// AM encoding: 000 and 001
// Address Mode: Register n
// Effective Address: data in Rn
//

void register_am( StorageObject reg ) {
	dbus.IN().pullFrom( reg );
	addr.latchFrom( dbus.OUT() );
}

//
// displacement_am() - Computes a memory address as a constant offset to reg.
//
// AM encoding: 010 and 011
// Address Mode: Displacement n
// Effective Address: EA = reg + imm
//

void displacement_am( StorageObject reg ) {
	// PC is pointing to the immediate value; get the imm value into addr.
	fetch_into( pc, abus, addr );
	pc.incr();
	
	// Compute EA = reg + imm; addr = reg + addr
	alu.OP1().pullFrom( reg );
	alu.OP2().pullFrom( addr );
	alu.perform( BusALU::op_add );
	
	// Get the EA into addr.
	addr.latchFrom( alu.OUT() );
}

//
// immediate_am() - The 2nd operand is in the imm byte.
// This can only be used for ALU operations.
//
// AM encoding: 100
// Address Mode: Immediate
// Effective Address: data in imm
//

void immediate_am() {
	// PC is pointing to the immediate value; get the imm value into addr.
	fetch_into( pc, abus, addr );
	pc.incr();
}

//
// absolute_am() - The immediate byte contains the memory address.
//
// AM encoding: 101
// Address Mode: Absolute
// Effective Address: EA = imm
//

void absolute_am() {
	// PC is pointing to the immediate value; get the imm value into addr.
	fetch_into( pc, abus, addr );
	pc.incr();
}

//
// pc_relative_am() - Computes a memory address as a constant offset to PC 
// register. Note that the PC should be pointing to the address after the 
// imm byte.
//
// AM encoding: 110
// Address Mode: PC Relative
// Effective Address: EA = PC + imm
//

void pc_relative_am() {
	// PC is pointing to the immediate value; get the imm value into addr.
	fetch_into( pc, abus, addr );
	pc.incr();
	
	// Compute EA = PC + imm; addr = pc + addr
	alu.OP1().pullFrom( pc );
	alu.OP2().pullFrom( addr );
	alu.perform( BusALU::op_add );
	
	// Get the EA into addr.
	addr.latchFrom( alu.OUT() );
}

void decode_am( long am, bool &data_in_addr ) {
	switch( am ) {
		case 0:	register_am( r0 );			data_in_addr = true;	break;
		case 1:	register_am( r1 );			data_in_addr = true;	break;
		case 2:	displacement_am( r0 );		data_in_addr = false;	break;
		case 3:	displacement_am( r1 );		data_in_addr = false;	break;
		case 4:	immediate_am();				data_in_addr = true;	break;
		case 5:	absolute_am();				data_in_addr = false;	break;
		case 6:	pc_relative_am();			data_in_addr = false;	break;
		default:
			cout << endl << 
				"MACHINE HALTED due to unknown address mode" << 
				am << endl;
			done = true;
	}
}

//
// execute() - decode and execute the instruction
//

void execute() {
	long opc;
	long am;
	long ra;
	const char* mnemonic;
	
	// Used to keep track of data vs. memory addresses stored in addr.
	// Since some instructions need a memory address in addr, an
	// invalid address mode could be used if addr contains data.
	// In that case, the machine should halt due to invalid address mode.
	bool data_in_addr;

	// In each case, note that the last set of operations aren't actually performed 
	// until we leave the switch statement.
	//
	// instr format: opcode = bits 7:4, address mode = bits 3:1, ra = bit 0

	opc = ir( DATA_BITS-1, DATA_BITS-4 );
	am = ir( DATA_BITS-5, DATA_BITS-7 );
	ra = ir( DATA_BITS-8 );
	
	// Get the content of addr, if address mode matters for the instruction.
	if( opc > -1 && opc < 11 )
		decode_am( am, &data_in_addr );
	
	// Opcode represents instructions supported by the minVAX CPU.
	switch( opc ) {
		// Instructions that use the address mode to get the data.
		case 0:										mnemonic = "NOP";	break;
		case 1: 	add_to_ra();					mnemonic = "ADD";	break;
		case 2: 	and_to_ra();					mnemonic = "AND";	break;
		case 3: 	shift_right_arithmetic();		mnemonic = "SRA";	break;
		case 4: 	shift_left_logical();			mnemonic = "SLL";	break;
		
		// Instructions that use the address mode to get an effective address.
		case 5: 	load_to_ra();					mnemonic = "LDR";	break;
		case 6: 	store_to_mem();					mnemonic = "STR";	break;
		case 7: 	jump();							mnemonic = "JMP";	break;
		case 8: 	branch_if_ra_equals_zero();		mnemonic = "BEZ";	break;
		case 9: 	branch_if_ra_less_than_zero();	mnemonic = "BLT";	break;
		case 10: 									mnemonic = "NOP";	break;
		
		// Instructions that ignore the address mode.
		case 11:	clear_ra();						mnemonic = "CLR";	break;
		case 12:	complement_ra();				mnemonic = "CMP";	break;
		case 13:	increment_ra();					mnemonic = "INC";	break;
		case 14:	dump_ra();						mnemonic = "DMP";	break;
		case 15:	halt();							mnemonic = "HLT";	break;

		default:
			cout << endl << "MACHINE HALTED due to unknown op code" << opc << endl;
			done = true;
	}

	//if (opc != 4 && opc != 7)
		//printf("%5s %03x   AC=%04x", mnemonic, ir(DATA_BITS - 4, 0), ac.value());

	Clock::tick();

}
