#include <limits.h>
#include <stdio.h>
#include <time.h>

#include "libs/fstream.h"
#include "libs/gen.h"
#include "libs/sort.h"
#include "libs/struct.h"

int main()
{
    /*FILE* file_r = fopen("test.bin", "rb");
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
    dealloc_nodes(nodes, cnt);*/

    /*float time = 0;
    int cnt = 2, len = 100000;
    gen_arrays_nodes(&time, cnt, len, QSORT_MODE, NAME_MODE, REVERSE);
    printf("%f", time);*/
    return 0;
}
