#ifndef __FSTREAM__
#define __FSTREAM__

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "readline.h"
#include "struct.h"

int read_from_file(FILE* file, Node*** nodes);
Node* read_node_from_file(FILE* file);
void write_to_file(FILE* file, Node** nodes, int cnt);
void write_node_to_file(FILE* file, Node* node);
int valid_id(char* id);
int valid_alloc(void** original, void* tmp, Node* node, int mode);
Node* read_node_from_bin(FILE* file);
void write_node_to_bin(FILE* file, Node* node);

#endif
