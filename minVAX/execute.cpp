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
//     (RA = RA + addr)
//
// Code 1
//

void add_to_ra( Counter &ra ) {
	alu.OP1().pullFrom( ra );
	alu.OP2().pullFrom( addr );
	alu.perform( BusALU::op_add );
	
	// Get the result from ALU into AUX.
	aux.latchFrom( alu.OUT() );
	Clock::tick();
	
	// Get the value from AUX into ADDR.
	dbus.IN().pullFrom( aux );
	addr.latchFrom( dbus.OUT() );
}

//
// and_to_ra() - bitwise AND data to register RA.
//
// RTL (Register Transfer Language)
// RA = RA & data(AM)
//     (RA = RA & addr)
//
// Code 2
//

void and_to_ra( Counter &ra ) {
	alu.OP1().pullFrom( ra );
	alu.OP2().pullFrom( addr );
	alu.perform( BusALU::op_and );
	
	// Get the result from ALU into AUX.
	aux.latchFrom( alu.OUT() );
	Clock::tick();
	
	// Get the value from AUX into ADDR.
	dbus.IN().pullFrom( aux );
	addr.latchFrom( dbus.OUT() );
}

//
// shift_right_arithmetic() - shift right arithmetic by number of bits 
//      specified by data.
//
// RTL (Register Transfer Language)
// RA = RA >>_a data(AM)
//     (RA = RA >>_a addr)
//
// Code 3
//

void shift_right_arithmetic( Counter &ra ) {
	alu.OP1().pullFrom( ra );
	alu.OP2().pullFrom( addr );
	alu.perform( BusALU::op_rashift );
	
	// Get the result from ALU into AUX.
	aux.latchFrom( alu.OUT() );
	Clock::tick();
	
	// Get the value from AUX into ADDR.
	dbus.IN().pullFrom( aux );
	addr.latchFrom( dbus.OUT() );
}

//
// shift_left_logical() - shift left logical by number of bits specified 
//      by data.
//
// RTL (Register Transfer Language)
// RA = RA << data(AM)
//     (RA = RA << addr)
//
// Code 4
//

void shift_left_logical( Counter &ra ) {
	alu.OP1().pullFrom( ra );
	alu.OP2().pullFrom( addr );
	alu.perform( BusALU::op_lshift );
	
	// Get the result from ALU into AUX.
	aux.latchFrom( alu.OUT() );
	Clock::tick();
	
	// Get the value from AUX into ADDR.
	dbus.IN().pullFrom( aux );
	addr.latchFrom( dbus.OUT() );
}

//
// load_to_ra() - load register RA from memory at the effective address 
//      specified by the address mode.
//
// RTL (Register Transfer Language)
// RA <- Mem[EA]
//     (AUX <- Mem[ADDR]
//     (RA <- AUX)
//
// Code 5
//

void load_to_ra( Counter &ra ) {
	// Get the value in memory specified by ADDR into AUX.
	// AUX <- Mem[ADDR]
	fetch_into( addr, abus, aux );
	
	// RA <- AUX
	dbus.IN().pullFrom( aux );
	ra.latchFrom( dbus.OUT() );
}

//
// store_to_mem() - store register RA to memory at the effective address 
//      specified by the address mode.
//
// RTL (Register Transfer Language)
// Mem[EA] <- RA
//     (MAR <- ADDR, AUX <- RA)
//     (Mem[MAR] <- AUX)
//
// Code 6
//

void store_to_mem( Counter &ra ) {
	// MAR <- ADDR, AUX <- RA
	abus.IN().pullFrom( addr );
	m.MAR().latchFrom( abus.OUT() );
	
	dbus.IN().pullFrom( ra );
	aux.latchFrom( dbus.OUT() );
	Clock::tick();
	
	// Mem[MAR] <- AUX
	m.WRITE().pullFrom( aux );
	m.write();
	Clock::tick();
}

//
// jump() - jump to memory location specified by the effective address.
//
// RTL (Register Transfer Language)
// PC = EA
//     (PC <- ADDR)
//
// Code 7
//

void jump() {
	// PC <- ADDR
	abus.IN().pullFrom( addr );
	pc.latchFrom( abus.OUT() );
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

void branch_if_ra_equals_zero( Counter &ra ) {
	// if RA == 0 then PC = EA
	if( ra.value() == 0 )
		jump();
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

void branch_if_ra_less_than_zero( Counter &ra ) {
	// if RA < 0 then PC = EA
	if( ra.value() < 0 )
		jump();
}

//
// clear_ra() - clear register RA.
//
// RTL (Register Transfer Language)
// RA = 0
//
// Code 11
//

void clear_ra( Counter &ra ) {
	ra.clear();
}

//
// complement_ra() - complement register RA.
//
// RTL (Register Transfer Language)
// RA = !(RA)
//
// Code 12
//

void complement_ra( Counter &ra ) {
	alu.OP1().pullFrom( ra );
	alu.OP2().pullFrom( addr );
	alu.perform( BusALU::op_not );
	
	// Get the result from ALU into AUX.
	aux.latchFrom( alu.OUT() );
	Clock::tick();
	
	// Get the value from AUX into ADDR.
	dbus.IN().pullFrom( aux );
	addr.latchFrom( dbus.OUT() );
}

//
// increment_ra() - increment register RA.
//
// RTL (Register Transfer Language)
// RA = RA + 1
//     (RA <- RA + 1)
//
// Code 13
//

void increment_ra( Counter &ra ) {
	// RA <- RA + 1
	ra.incr();
}

//
// dump_ra() - dump (print) the value of register RA.
//
// RTL (Register Transfer Language)
// null
//
// Code 14
//

void dump_ra( Counter &ra, long ra_name ) {
	printf( "R%lu=%02x", ra_name, ra.value() );
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

void register_am( Counter &reg ) {
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

void displacement_am( Counter &reg ) {
	// PC is pointing to the immediate value; get the imm value into addr.
	fetch_into( pc, abus, addr );
	pc.incr();
	
	// Compute EA = reg + imm; addr = reg + addr.
	alu.OP1().pullFrom( reg );
	alu.OP2().pullFrom( addr );
	alu.perform( BusALU::op_add );
	
	// Get the output from ALU into AUX.
	aux.latchFrom( alu.OUT() );
	Clock::tick();
	
	// Get the value from AUX into ADDR.
	dbus.IN().pullFrom( aux );
	addr.latchFrom( dbus.OUT() );
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
	
	// Get the output from ALU into AUX.
	aux.latchFrom( alu.OUT() );
	Clock::tick();
	
	// Get the value from AUX into ADDR.
	dbus.IN().pullFrom( aux );
	addr.latchFrom( dbus.OUT() );
}

bool decode_am( long am ) {
	switch( am ) {
		case 0:	register_am( r0 );			return true;
		case 1:	register_am( r1 );			return true;
		case 2:	displacement_am( r0 );		return false;
		case 3:	displacement_am( r1 );		return false;
		case 4:	immediate_am();				return true;
		case 5:	absolute_am();				return false;
		case 6:	pc_relative_am();			return false;
		default:
			cout << endl << 
				"MACHINE HALTED due to unknown address mode" << 
				am << endl;
			done = true;
			return false;
	}
}

//
// execute() - decode and execute the instruction
//

void execute() {
	long opc;
	long am;
	long ra;
	
	// Represents the operation performed by the instruction's opcode.
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
		data_in_addr = decode_am( am );
		
	// Get the register represented by ra as RA.
	Counter &ra_reg = (( ra == 0 ) ? r0 : r1 );
	
	// Opcode represents instructions supported by the minVAX CPU.
	switch( opc ) {
		// Instructions that use the address mode to get the data.
		case 0:												mnemonic = "NOP";
						break;
		case 1: 	add_to_ra( ra_reg );					mnemonic = "ADD";
						break;
		case 2: 	and_to_ra( ra_reg );					mnemonic = "AND";
						break;
		case 3: 	shift_right_arithmetic( ra_reg );		mnemonic = "SRA";
						break;
		case 4: 	shift_left_logical( ra_reg );			mnemonic = "SLL";
						break;
		
		// Instructions that use the address mode to get an effective address.
		case 5: 	load_to_ra( ra_reg );					mnemonic = "LDR";
						break;
		case 6: 	store_to_mem( ra_reg );					mnemonic = "STR";
						break;
		case 7: 	jump();									mnemonic = "JMP";
						break;
		case 8: 	branch_if_ra_equals_zero( ra_reg );		mnemonic = "BEZ";
						break;
		case 9: 	branch_if_ra_less_than_zero( ra_reg );	mnemonic = "BLT";
						break;
		case 10: 											mnemonic = "NOP";
						break;
		
		// Instructions that ignore the address mode.
		case 11:	clear_ra( ra_reg );						mnemonic = "CLR";
						break;
		case 12:	complement_ra( ra_reg );				mnemonic = "CMP";
						break;
		case 13:	increment_ra( ra_reg );					mnemonic = "INC";
						break;
		case 14:	dump_ra( ra_reg, ra );					mnemonic = "DMP";
						break;
		case 15:	halt();									mnemonic = "HLT";	
						break;

		default:
			cout << endl << "MACHINE HALTED due to unknown op code" << opc << endl;
			done = true;
	}

	//if (opc != 4 && opc != 7)
		//printf("%5s %03x   AC=%04x", mnemonic, ir(DATA_BITS - 4, 0), ac.value());

	Clock::tick();

}
