#include "struct.h"

void init_node(Node* node)
{
    node->name = NULL;
    node->id = NULL;
    node->time = 0;
}

void dealloc_nodes(Node** nodes, int cnt)
{
    if (nodes == NULL) {
        return;
    }
    for (int i = 0; i < cnt; ++i) {
        dealloc_node(*(nodes + i));
    }
    free(nodes);
}

void dealloc_node(Node* node)
{
    if (node != NULL) {
        free(node->name);
        free(node->id);
        free(node);
    }
}
