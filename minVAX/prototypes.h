// prototypes.h
//
// Original version:	Warren Carithers, Novermber 2000
// Updates:
//
//	2001/12/10:	wrc, expanded execute() implementation
//
// Function prototypes for the dummest little computer.

#ifndef _PROTOTYPES_H
#define _PROTOTYPES_H

void clear_ac();
void add_to_ac();
void execute();
void fetch_into( StorageObject &, Bus &, StorageObject & );
void make_connections();
void run_simulation( char * );

#endif
