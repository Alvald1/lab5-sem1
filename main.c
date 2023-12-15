#include <stdio.h>

#include "libs/fstream.h"
#include "libs/readline.h"
#include "libs/sort.h"
#include "libs/struct.h"

int main()
{
    /*node->name = strdup("qwer  djs");
    node->id = strdup("asdf-1232");
    node->time = 98;
    FILE* file_w = fopen("test.bin", "wb");
    write_to_bin(file_w, node);
    fclose(file_w);
    FILE* file_r = fopen("test.bin", "rb");
    node = read_from_bin(file_r);
    fclose(file_r);*/
    FILE* file_r = fopen("test.txt", "r");
    int cnt = 0;
    Node** nodes = NULL;
    if ((cnt = read_from_file(file_r, &nodes)) == 0) {
        return 0;
    }
    write_to_file(stdout, nodes, cnt);
    printf("\n\n");
    insertion_sort(nodes, cnt, cmp_name, DIRECT);
    write_to_file(stdout, nodes, cnt);
    printf("\n\n");
    gnome_sort(nodes, cnt, cmp_id, REVERSE);
    write_to_file(stdout, nodes, cnt);
    printf("\n\n");
    _qsort(nodes, 0, cnt - 1, cmp_time, 0);
    write_to_file(stdout, nodes, cnt);
    dealloc_nodes(nodes, cnt);
    return 0;
}
