#ifndef __SORT__
#define __SORT__

#include <string.h>

#include "struct.h"

enum { DIRECT,
    REVERSE };

typedef int (*fptr_compare)(Node* node_1, Node* node_2);

void swap(Node** node_1, Node** node_2);
void gnome_sort(Node** arr, int n, fptr_compare compare, int flag);
void insertion_sort(Node** arr, int n, fptr_compare compare, int flag);
void _qsort(Node** arr, int left, int right, fptr_compare compare, int flag);
int cmp_name(Node* node_1, Node* node_2);
int cmp_id(Node* node_1, Node* node_2);
int cmp_time(Node* node_1, Node* node_2);

#endif
