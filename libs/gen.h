#ifndef __GEN__
#define __GEN__

#include <limits.h>

#include "fstream.h"
#include "struct.h"

Node* gen_node(void);
char* gen_name(void);
char* gen_id(void);
int gen_nodes(Node*** nodes, int cnt);
int gen_arrays_nodes(int cnt, int len);

#endif
