#include "sort.h"

void gnome_sort(Node** arr, int n, COMPARE compare, int flag)
{
    int index = 0;
    while (index < n) {
        if (index == 0)
            index++;
        if (((*compare)(*(arr + index), *(arr + index - 1)) > 0) ^ flag)
            index++;
        else {
            swap((arr + index), (arr + index - 1));
            index--;
        }
    }
}

void insertion_sort(Node** arr, int n, COMPARE compare, int flag)
{
    int i, j;
    Node* key;
    for (i = 1; i < n; i++) {
        key = *(arr + i);
        j = i - 1;
        while (j >= 0 && (((*compare)(*(arr + j), key)) > 0) ^ flag) {
            *(arr + j + 1) = *(arr + j);
            j = j - 1;
        }
        *(arr + j + 1) = key;
    }
}

void _qsort(Node** arr, int left, int right, COMPARE compare, int flag)
{
    int i, last;
    if (left >= right)
        return;
    swap(arr + left, arr + (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (((*compare)(arr[i], arr[left]) < 0) ^ flag)
            swap(arr + ++last, arr + i);
    swap(arr + left, arr + last);
    _qsort(arr, left, last - 1, compare, flag);
    _qsort(arr, last + 1, right, compare, flag);
}

int cmp_name(Node* node_1, Node* node_2)
{
    return strcmp(node_1->name, node_2->name);
}

int cmp_id(Node* node_1, Node* node_2)
{
    return strcmp(node_1->id, node_2->id);
}

int cmp_time(Node* node_1, Node* node_2)
{
    if (node_1->time > node_2->time) {
        return 1;
    } else if (node_1->time < node_2->time) {
        return -1;
    } else {
        return 0;
    }
}

void swap(Node** node_1, Node** node_2)
{
    Node* temp;
    temp = *node_1;
    *node_1 = *node_2;
    *node_2 = temp;
}
