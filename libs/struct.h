#ifndef __STRUCT__
#define __STRUCT__

#include <stdlib.h>

typedef struct _node {
    char* name;
    char* id;
    int time;
} Node;

void init_node(Node* node);
void dealloc_nodes(Node** nodes, int cnt);
void dealloc_node(Node* node);

#endif
