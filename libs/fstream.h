#ifndef __FSTREAM__
#define __FSTREAM__

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "readline.h"
#include "struct.h"

enum { BIN_MODE,
    FILE_MODE };

typedef Node* (*fptr_read_mode)(FILE* file);
typedef void (*fptr_write_mode)(FILE* file, Node* node);

int read(FILE* file, Node*** nodes, int mode);
void write(FILE* file, Node** nodes, int cnt, int mode);
Node* read_node_from_file(FILE* file);
void write_node_to_file(FILE* file, Node* node);
Node* read_node_from_bin(FILE* file);
void write_node_to_bin(FILE* file, Node* node);
int valid_id(char* id);
int valid_alloc(void** original, void* tmp, Node* node, int mode);

#endif
