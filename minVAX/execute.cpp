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
	
	// Get the value from AUX into RA.
	dbus.IN().pullFrom( aux );
	ra.latchFrom( dbus.OUT() );
	Clock::tick();
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
	
	// Get the value from AUX into RA.
	dbus.IN().pullFrom( aux );
	ra.latchFrom( dbus.OUT() );
	Clock::tick();
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
	
	// Get the value from AUX into RA.
	dbus.IN().pullFrom( aux );
	ra.latchFrom( dbus.OUT() );
	Clock::tick();
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
	
	// Get the value from AUX into RA.
	dbus.IN().pullFrom( aux );
	ra.latchFrom( dbus.OUT() );
	Clock::tick();
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
	Clock::tick();
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

bool jump() {
	// PC <- ADDR
	abus.IN().pullFrom( addr );
	pc.latchFrom( abus.OUT() );
	Clock::tick();
	
	// True for branch was taken.
	return true;
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

bool branch_if_ra_equals_zero( Counter &ra ) {
	// if RA == 0 then PC = EA
	if( ra.value() == 0 ) {
		jump();
		
		// True for branch was taken.
		return true;
	}
	
	// False for branch was not taken.
	return false;
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

bool branch_if_ra_less_than_zero( Counter &ra ) {
	// if RA < 0 then PC = EA
	if( ra( ADDR_BITS - 1 ) == 1 ) {
		jump();
		
		// True for branch was taken.
		return true;
	}
	
	// False for branch was not taken.
	return false;
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
	Clock::tick();
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
	
	// Get the value from AUX into RA.
	dbus.IN().pullFrom( aux );
	ra.latchFrom( dbus.OUT() );
	Clock::tick();
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
	Clock::tick();
}

//
// dump_ra() - dump (print) the value of register RA.
//
// RTL (Register Transfer Language)
// null
//
// Code 14
//

void dump_ra( Counter &ra, long ra_name, long am ) {
	printf("%02lx:  %02lx = ", savedPC, savedIR);
	printf( "DMP %01lx %01lx    R%lu=%02lx", ra_name, am, ra_name, ra.value() );
}

//
// dump_ra_short() - dump (print) the value of register RA.
//
// RTL (Register Transfer Language)
// null
//
// Code 14
//

void dump_ra_short( Counter &ra, long ra_name ) {
	printf( "R%lu=%02lx", ra_name, ra.value() );
}


//
// halt() - halt the computer.
//
// RTL (Register Transfer Language)
// null
//
// Code 15
//

void halt(long ra, long am) {
	printf("%02lx:  %02lx = ", savedPC, savedIR);
	printf("%3s %01lx %01lx   ", "HLT", ra, am);
	cout << endl << endl << "MACHINE HALTED due to halt instruction" << endl;
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
	
	Clock::tick();
}

//
// displacement_am() - Computes a memory address as a constant offset to reg.
//
// AM encoding: 010 and 011
// Address Mode: Displacement n
// Effective Address: EA = reg + imm
//

void displacement_am( Counter &reg, bool dataNeeded ) {
	// PC is pointing to the immediate value; get the imm value into addr.
	fetch_into( pc, abus, addr );
	pc.incr();
	
	// Save the immediate value for trace output.
	immediate = addr.value();
	
	// Compute EA = reg + imm; addr = reg + addr.
	alu.OP1().pullFrom( reg );
	alu.OP2().pullFrom( addr );
	alu.perform( BusALU::op_add );
	
	// Get the output from ALU into AUX.
	aux.latchFrom( alu.OUT() );
	Clock::tick();
	
	// Instead of moving the address into the address register, use the address 
	// to get the data.
	if( dataNeeded ) {
		fetch_into( aux, abus, addr );
	}
	// Otherwise, store the address.
	else {
		// Get the value from AUX into ADDR.
		dbus.IN().pullFrom( aux );
		addr.latchFrom( dbus.OUT() );
		Clock::tick();
	}
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
	
	// Save the immediate value for trace output.
	immediate = addr.value();
	
	pc.incr();
	Clock::tick();
}

//
// absolute_am() - The immediate byte contains the memory address.
//
// AM encoding: 101
// Address Mode: Absolute
// Effective Address: EA = imm
//

void absolute_am( bool dataNeeded ) {
	// PC is pointing to the immediate value; get the imm value into addr.
	fetch_into( pc, abus, addr );
	
	// Save the immediate value for trace output.
	immediate = addr.value();
	
	pc.incr();
	Clock::tick();
	
	// Instead of moving the address into the address register, use the address 
	// to get the data.
	if( dataNeeded ) {
		fetch_into( addr, abus, addr );
	}
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

void pc_relative_am( bool dataNeeded ) {
	// PC is pointing to the immediate value; get the imm value into addr.
	fetch_into( pc, abus, addr );
	
	// Save the immediate value for trace output.
	immediate = addr.value();
	
	pc.incr();
	Clock::tick();
	
	// Compute EA = PC + imm; addr = pc + addr
	alu.OP1().pullFrom( pc );
	alu.OP2().pullFrom( addr );
	alu.perform( BusALU::op_add );
	
	// Get the output from ALU into AUX.
	aux.latchFrom( alu.OUT() );
	Clock::tick();
	
	// Instead of moving the address into the address register, use the address 
	// to get the data.
	if( dataNeeded ) {
		fetch_into( pc, abus, addr );
	}
	// Otherwise, store the address.
	else {
		// Get the value from AUX into ADDR.
		dbus.IN().pullFrom( aux );
		addr.latchFrom( dbus.OUT() );
		Clock::tick();
	}
}

bool decode_am( long am, bool dataNeeded ) {
	switch( am ) {
		case 0:	register_am( r0 );						return true;
		case 1:	register_am( r1 );						return true;
		case 2:	displacement_am( r0, dataNeeded );		return false;
		case 3:	displacement_am( r1, dataNeeded );		return false;
		case 4:	immediate_am();							return true;
		case 5:	absolute_am( dataNeeded );				return false;
		case 6:	pc_relative_am( dataNeeded );			return false;
		default:
			cout << endl << 
				"MACHINE HALTED due to unknown address mode" << endl;
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
	long imm;
	bool branchTaken;
	
	// If true, instead of storing the EA for use later as an address, 
	// the EA is pointing to the data itself.
	bool dataNeeded;
	
	// Represents the operation performed by the instruction's opcode.
	const char* mnemonic;
	
	// Used to keep track of data vs. memory addresses stored in addr.
	// Since some instructions need a memory address in addr, an
	// invalid address mode could be used if addr contains data.
	// In that case, the machine should halt due to invalid address mode.
	bool data_in_addr;

	// In each case, note that the last set of operations aren't actually 
	// performed until we leave the switch statement.
	//
	// instr format: opcode = bits 7:4, address mode = bits 3:1, ra = bit 0

	opc = ir( DATA_BITS-1, DATA_BITS-4 );
	am = ir( DATA_BITS-5, DATA_BITS-7 );
	ra = ir( DATA_BITS-8 );
	
	// Check for invalid address modes.
	if( opc > 4 && opc < 11 && ( am == 0 || am == 1 || am == 4 ) ) {
		cout << endl << "MACHINE HALTED due to invalid address mode" << endl;
			done = true;
	}
	
	// Get the content of addr, if address mode matters for the instruction.
	// Ignore NOP, opc 0 and opc 10.
	if( opc > 0 && opc < 10 ) {
		if( opc > -1 && opc < 5 )
			dataNeeded = true;
		else
			dataNeeded = false;
		data_in_addr = decode_am( am, dataNeeded );
	}
		
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
		case 7: 	branchTaken = jump();					mnemonic = "JMP";
						break;
		case 8: 	branchTaken = 
					branch_if_ra_equals_zero( ra_reg );		mnemonic = "BEZ";
						break;
		case 9: 	branchTaken = 
					branch_if_ra_less_than_zero( ra_reg );	mnemonic = "BLT";
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
		case 14:	dump_ra( ra_reg, ra, am );				mnemonic = "DMP";
						break;
		case 15:	halt( ra, am );							mnemonic = "HLT";	
						break;

		default:
			cout << endl << "MACHINE HALTED due to unknown op code" 
				<< opc << endl;
			done = true;
	}
	
	if( opc != 15 && opc != 14 && !done ) {
		printf("%02lx:  %02lx = ", savedPC, savedIR);
		printf("%3s %01lx %01lx", mnemonic, ra, am);
		
		if( opc != 0 && opc != 10 ) {
			if( immediate == -1 )
				printf("    ");
			else
				printf(" %02lx ", immediate);
		
			immediate = -1;
			
			if( opc < 6 || opc > 10 )
				dump_ra_short( ra_reg, ra );
			else if( opc > 6 && opc < 10 ) {
				if( branchTaken )
					printf("BRANCH TAKEN");
				else
					printf("BRANCH NOT TAKEN");
				
				branchTaken = false;
			}
			else if( opc == 6 )
				printf("MEM[%01lx]=%02lx", addr.value(), aux.value());
		}
		else
			printf("   ");
	}
	
	Clock::tick();

}
