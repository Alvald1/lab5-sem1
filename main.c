#include <stdio.h>

#include "libs/fstream.h"
#include "libs/readline.h"
#include "libs/sort.h"
#include "libs/struct.h"

int main()
{
    FILE* file_r = fopen("test.bin", "rb");
    int cnt = 0;
    Node** nodes = NULL;
    if ((cnt = read(stdin, &nodes, FILE_MODE)) == 0) {
        return 0;
    }
    FILE* file_w = fopen("test.txt", "w");
    write(file_w, nodes, cnt, FILE_MODE);
    write(stdout, nodes, cnt, FILE_MODE);
    fclose(file_w);
    fclose(file_r);
    dealloc_nodes(nodes, cnt);
    return 0;
}
