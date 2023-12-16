#include <limits.h>
#include <stdio.h>
#include <time.h>

#include "libs/fstream.h"
#include "libs/gen.h"
#include "libs/sort.h"
#include "libs/struct.h"

int main()
{
    const char* prompt_actions = "(a) in\n(b) out\n(c) sort\n(d) gen and test\n";
    const char* prompt_in = "(a) из стандартного потока ввода потока («с клавиатуры»);\n(b) из текстового файла (с возможностью указания имени файла);\n(c) из бинарного файла (с возможностью указания имени файла).\n";
    const char* prompt_out = "(a) в стандартный поток вывода («на экран»);\n(b) в текстовый файл (с возможностью указания имени файла);\n(c) в бинарный файл (с возможностью указания имени файла).\n";
    const char* prompt_sort = "(a) qsort\n(b) gnome_sort\n(c) insertion_sort\n";
    const char* prompt_cmp = "(a) name\n(b) id\n(c) time\n";
    const char* prompt_direction = "(a) direct\n(b) reverse\n";
    char state = 0, state_2 = 0, state_3 = 0;
    char* file_name = NULL;
    Node** nodes = NULL;
    float time = 0;
    FILE* file = NULL;
    int len = 0, dir = 0;
    fptr_compare compare = NULL;
    int sort = 0, cmp = 0, cnt = 0;
    printf("%s", prompt_actions);
    while (scanf("%c", &state) != EOF) {
        scanf("%*c");
        switch (state) {
        case 'a':
            printf("%s", prompt_in);
            dealloc_nodes(nodes, len);
            nodes = NULL;
            if (scanf("%c", &state) != EOF) {
                scanf("%*c");
                switch (state) {
                case 'a':
                    if ((len = read(stdin, &nodes, FILE_MODE)) == 0) {
                        return 0;
                    }
                    break;
                case 'b':
                    file_name = readline(stdin, "Введите название файла\n");
                    file = fopen(file_name, "r");
                    free(file_name);
                    if (file == NULL) {
                        fprintf(stderr, "Ошибка файла\n");
                        break;
                    }
                    if ((len = read(file, &nodes, FILE_MODE)) == 0) {
                        return 0;
                    }
                    break;
                case 'c':
                    file_name = readline(stdin, "Введите название файла\n");
                    file = fopen(file_name, "rb");
                    if (file == NULL) {
                        fprintf(stderr, "Ошибка файла\n");
                        break;
                    }
                    free(file_name);
                    if ((len = read(file, &nodes, BIN_MODE)) == 0) {
                        return 0;
                    }
                    break;
                }
            } else {
                return 0;
            }
            break;
        case 'b':
            printf("%s", prompt_out);
            if (scanf("%c", &state) != EOF) {
                scanf("%*c");
                switch (state) {
                case 'a':
                    write(stdout, nodes, len, FILE_MODE);
                    break;
                case 'b':
                    file_name = readline(stdin, "Введите название файла\n");
                    file = fopen(file_name, "w");
                    if (file == NULL) {
                        fprintf(stderr, "Ошибка файла\n");
                        break;
                    }
                    free(file_name);
                    write(file, nodes, len, FILE_MODE);
                    break;
                case 'c':
                    file_name = readline(stdin, "Введите название файла\n");
                    file = fopen(file_name, "wb");
                    if (file == NULL) {
                        fprintf(stderr, "Ошибка файла\n");
                        break;
                    }
                    free(file_name);
                    write(file, nodes, len, BIN_MODE);
                    break;
                }
            } else {
                return 0;
            }
            break;
        case 'c':
            printf("%s", prompt_sort);
            if (scanf("%c", &state) != EOF) {
                scanf("%*c");
                printf("%s", prompt_cmp);
                if (scanf("%c", &state_2) != EOF) {
                    scanf("%*c");
                    printf("%s", prompt_direction);
                    if (scanf("%c", &state_3) != EOF) {
                        scanf("%*c");
                        switch (state_2) {
                        case 'a':
                            compare = cmp_name;
                            break;
                        case 'b':
                            compare = cmp_id;
                            break;
                        case 'c':
                            compare = cmp_time;
                            break;
                        }
                        switch (state_3) {
                        case 'a':
                            dir = DIRECT;
                            break;
                        case 'b':
                            dir = REVERSE;
                            break;
                        }
                        switch (state) {
                        case 'a':
                            _qsort(nodes, 0, len - 1, compare, dir);
                            break;
                        case 'b':
                            gnome_sort(nodes, len, compare, dir);
                            break;
                        case 'c':
                            insertion_sort(nodes, len, compare, dir);
                            break;
                        }
                    }
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
            break;
        case 'd':
            printf("%s", prompt_sort);
            if (scanf("%c", &state) != EOF) {
                scanf("%*c");
                printf("%s", prompt_cmp);
                if (scanf("%c", &state_2) != EOF) {
                    scanf("%*c");
                    printf("%s", prompt_direction);
                    if (scanf("%c", &state_3) != EOF) {
                        scanf("%*c");
                        printf("количества элементов в генерируемых массивах: ");
                        if (scanf("%d", &len) != EOF) {
                            printf("количества генерируемых массивов: ");
                            if (scanf("%d", &cnt) != EOF) {
                                scanf("%*c");
                                switch (state_2) {
                                case 'a':
                                    cmp = NAME_MODE;
                                    break;
                                case 'b':
                                    cmp = ID_MODE;
                                    break;
                                case 'c':
                                    cmp = TIME_MODE;
                                    break;
                                }
                                switch (state_3) {
                                case 'a':
                                    dir = DIRECT;
                                    break;
                                case 'b':
                                    dir = REVERSE;
                                    break;
                                }
                                switch (state) {
                                case 'a':
                                    sort = QSORT_MODE;
                                    break;
                                case 'b':
                                    sort = GNOME_MODE;
                                    break;
                                case 'c':
                                    sort = INSERTION_MODE;
                                    break;
                                }
                                if (gen_arrays_nodes(&time, cnt, len, sort, cmp, dir) == 0) {
                                    return 0;
                                }
                                cnt = 0;
                                len = 0;
                                printf("avg time: %f\n", time);
                            } else {
                                return 0;
                            }
                        } else {
                            return 0;
                        }
                    }
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
            break;
        }
        printf("%s", prompt_actions);
    }
    dealloc_nodes(nodes, len);
    return 0;
}
