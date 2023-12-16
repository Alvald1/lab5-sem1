#ifndef __GEN__
#define __GEN__

#include <limits.h>
#include <time.h>

#include "fstream.h"
#include "sort.h"
#include "struct.h"

enum { QSORT_MODE,
    GNOME_MODE,
    INSERTION_MODE,
    NAME_MODE,
    ID_MODE,
    TIME_MODE };

Node* gen_node(void);
char* gen_name(void);
char* gen_id(void);
int gen_nodes(Node*** nodes, int cnt);
int gen_arrays_nodes(float* time, int cnt, int len, int sort_mode, int cmp_mode, int direction_mode);
int measuring_time(Node** nodes, int len, float* time, int sort_mode, int cmp_mode, int direction_mode);

#endif
