#include "gen.h"

int measuring_time(Node** nodes, int len, float* time, int sort_mode, int cmp_mode, int direction_mode)
{
    int direction = 0;
    clock_t start = 0, end = 0;
    fptr_compare compare = NULL;
    *time = 0;
    switch (cmp_mode) {
    case NAME_MODE:
        compare = cmp_name;
        break;
    case ID_MODE:
        compare = cmp_id;
        break;
    case TIME_MODE:
        compare = cmp_time;
        break;
    default:
        dealloc_nodes(nodes, len);
        return 0;
    }
    switch (direction_mode) {
    case DIRECT:
        direction = DIRECT;
        break;
    case REVERSE:
        direction = REVERSE;
        break;
    default:
        dealloc_nodes(nodes, len);
        return 0;
    }
    switch (sort_mode) {
    case QSORT_MODE:
        start = clock();
        _qsort(nodes, 0, len - 1, compare, direction);
        end = clock();
        *time += (float)(end - start) / CLOCKS_PER_SEC;
        break;
    case GNOME_MODE:
        start = clock();
        gnome_sort(nodes, len, compare, direction);
        end = clock();
        *time += (float)(end - start) / CLOCKS_PER_SEC;
        break;
    case INSERTION_MODE:
        start = clock();
        insertion_sort(nodes, len, compare, direction);
        end = clock();
        *time += (float)(end - start) / CLOCKS_PER_SEC;
        break;
    default:
        dealloc_nodes(nodes, len);
        return 0;
    }
    return 1;
}

int gen_arrays_nodes(float* time, int cnt, int len, int sort_mode, int cmp_mode, int direction_mode)
{
    FILE* file_save = NULL;
    const int size = 10;
    char* file_name = NULL;
    *time = 0;
    for (int i = 0; i < cnt; ++i) {
        void* tmp = calloc(size + strlen(".txt") + strlen("test_") + 1, 1);
        if (valid_alloc((void*)&file_name, tmp, NULL, 1) == 0) {
            return 0;
        }
        sprintf(file_name, "%s%d%s", "test_", i, ".txt");
        Node** nodes = NULL;
        if (gen_nodes(&nodes, len) == 0) {
            free(file_name);
            return 0;
        }
        if (measuring_time(nodes, len, time, sort_mode, cmp_mode, direction_mode) == 0) {
            free(file_name);
            return 0;
        }
        file_save = fopen(file_name, "w");
        write(file_save, nodes, len, FILE_MODE);
        dealloc_nodes(nodes, len);
        fclose(file_save);
        free(file_name);
    }
    *time /= cnt;
    return 1;
}

int gen_nodes(Node*** nodes, int cnt)
{
    void* tmp = malloc(cnt * sizeof(Node*));
    if (valid_alloc((void*)nodes, tmp, NULL, 1) == 0) {
        return 0;
    }
    for (int i = 0; i < cnt; ++i) {
        tmp = gen_node();
        if (tmp != NULL) {
            (*(*nodes + i)) = tmp;
        } else {
            dealloc_nodes(*nodes, i - 1);
            return 0;
        }
    }
    return 1;
}

Node* gen_node(void)
{
    void* tmp = malloc(sizeof(Node));
    Node* node = NULL;
    if (valid_alloc((void*)&node, tmp, node, 0) == 0) {
        return NULL;
    }
    init_node(node);
    char* name = gen_name();
    char* id = gen_id();
    if (name == NULL || id == NULL) {
        return NULL;
    }
    int time = rand() % INT_MAX;
    node->name = name;
    node->id = id;
    node->time = time;
    return node;
}

char* gen_name(void)
{
    int len = rand() % 100;
    int size = 'a' - 'z';
    void* tmp = malloc(len + 1);
    char* name = NULL;
    if (valid_alloc((void*)&name, tmp, NULL, 1) == 0) {
        return NULL;
    }
    for (int i = 0; i < len; ++i) {
        *(name + i) = rand() % size + 1 + 'a';
    }
    *(name + len) = '\0';
    return name;
}

char* gen_id(void)
{
    int size_1 = 'a' - 'z', size_2 = 10;
    int len = 9;
    void* tmp = malloc(len + 1);
    char* id = NULL;
    if (valid_alloc((void*)&id, tmp, NULL, 1) == 0) {
        return NULL;
    }
    for (int i = 0; i < 4; ++i) {
        *(id + i) = rand() % size_1 + 1 + 'a';
    }
    *(id + 4) = '-';
    for (int i = 5; i < len; ++i) {
        *(id + i) = rand() % size_2 + '0';
    }
    *(id + len) = '\0';
    return id;
}
