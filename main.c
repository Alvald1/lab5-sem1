#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
    char* name;
    char* id;
    int time;
} Node;

typedef int (*COMPARE)(Node* node_1, Node* node_2);

void init_node(Node* node);
void dealloc_nodes(Node** nodes, int cnt);
void dealloc_node(Node* node);
int read_from_file(FILE* file, Node*** nodes);
Node* read_node_from_file(FILE* file);
void write_node_to_file(FILE* file, Node* node);
int valid_id(char* id);
int valid_alloc(void** original, void* tmp, Node* node, int mode);
Node* read_node_from_bin(FILE* file);
void write_node_to_bin(FILE* file, Node* node);
char* readline(FILE* file, const char* prompt);
void swap(Node** node_1, Node** node_2);
void gnome_sort(Node** arr, int n, COMPARE compare, int flag);
void insertion_sort(Node** arr, int n, COMPARE compare, int flag);
void _qsort(Node** arr, int left, int right, COMPARE compare, int flag);
int cmp_name(Node* node_1, Node* node_2);
int cmp_id(Node* node_1, Node* node_2);
int cmp_time(Node* node_1, Node* node_2);

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
    for (int i = 0; i < cnt; ++i) {
        write_node_to_file(stdout, *(nodes + i));
    }
    dealloc_nodes(nodes, cnt);
    return 0;
}

int read_from_file(FILE* file, Node*** nodes)
{
    int cnt = 0;
    fscanf(file, "%d", &cnt);
    fscanf(file, "%*c");
    void* tmp = malloc(cnt * sizeof(Node*));
    if (valid_alloc((void*)nodes, tmp, NULL, 1) == 0) {
        return 0;
    }
    for (int i = 0; i < cnt; ++i) {
        tmp = read_node_from_file(file);
        if (tmp != NULL) {
            (*(*nodes + i)) = tmp;
        } else {
            dealloc_nodes(*nodes, i - 1);
            return 0;
        }
    }
    return cnt;
}

Node* read_node_from_file(FILE* file)
{
    Node* node = NULL;
    char *prompt_name = "", *prompt_id = "", *prompt_time = "";
    void* tmp = malloc(sizeof(Node));
    if (valid_alloc((void*)&node, tmp, NULL, 1) == 0) {
        return NULL;
    }
    init_node(node);
    if (file == stdin) {
        prompt_name = "Введите ФИО: ";
        prompt_id = "Введите ID: ";
        prompt_time = "Введите время: ";
    }
    tmp = readline(file, prompt_name);
    if (valid_alloc((void*)&(node->name), tmp, node, 0) == 0) {
        return NULL;
    }
    tmp = readline(file, prompt_id);
    if (valid_alloc((void*)&(node->id), tmp, node, 0) == 0) {
        return NULL;
    }
    if (valid_id(node->id) == 0) {
        fprintf(stderr, "Ошибка ввода ID\n");
        free(node->id);
        tmp = calloc(1, 1);
        if (valid_alloc((void*)&(node->id), tmp, node, 1) == 0) {
            return NULL;
        }
    }
    fprintf(stdout, "%s", prompt_time);
    if (fscanf(file, "%d", &(node->time)) != EOF) {
        if (node->time <= 0) {
            node->time = 0;
            fprintf(stderr, "Ошибка ввода time\n");
            fscanf(file, "%*[^\n]");
        }
        fscanf(file, "%*c");
    } else {
        dealloc_node(node);
        return NULL;
    }
    return node;
}

void write_node_to_file(FILE* file, Node* node)
{
    char *prompt_name = "", *prompt_id = "", *prompt_time = "";
    if (file == stdout) {
        prompt_name = "Name: ";
        prompt_id = "ID: ";
        prompt_time = "Time: ";
    }
    fprintf(file, "%s%s\n%s%s\n%s%d\n", prompt_name, node->name, prompt_id, node->id, prompt_time, node->time);
}

int valid_id(char* id)
{
    if (strlen(id) != 9) {
        return 0;
    }
    int flag = (id[4] == '-');
    for (int i = 0; i < 4; ++i) {
        if (isalpha(id[i])) {
            ++flag;
        }
    }
    for (int i = 5; i < 9; ++i) {
        if (isdigit(id[i])) {
            ++flag;
        }
    }
    return flag == 9;
}

int valid_alloc(void** original, void* tmp, Node* node, int mode)
{
    if (tmp != NULL) {
        *original = tmp;
        return 1;
    }
    dealloc_node(node);
    if (mode) {
        fprintf(stderr, "Ошибка памяти\n");
    }
    return 0;
}

void init_node(Node* node)
{
    node->name = NULL;
    node->id = NULL;
    node->time = 0;
}

void dealloc_nodes(Node** nodes, int cnt)
{
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

Node* read_node_from_bin(FILE* file)
{
    Node* node = NULL;
    int str_len = 0;
    void* tmp = malloc(sizeof(Node));
    if (valid_alloc((void*)&node, tmp, NULL, 1) == 0) {
        return NULL;
    }
    init_node(node);
    fread(&str_len, sizeof(int), 1, file);
    tmp = malloc(str_len + 1);
    if (valid_alloc((void*)&(node->name), tmp, node, 1) == 0) {
        return NULL;
    }
    fread(node->name, sizeof(char), str_len + 1, file);
    fread(&str_len, sizeof(int), 1, file);
    tmp = malloc(str_len + 1);
    if (valid_alloc((void*)&(node->id), tmp, node, 1) == 0) {
        return NULL;
    }
    fread(node->id, sizeof(char), str_len + 1, file);
    fread(&(node->time), sizeof(int), 1, file);
    return node;
}

void write_node_to_bin(FILE* file, Node* node)
{
    int str_len = strlen(node->name);
    fwrite(&str_len, sizeof(int), 1, file);
    fwrite(node->name, str_len + 1, 1, file);
    str_len = strlen(node->id);
    fwrite(&str_len, sizeof(int), 1, file);
    fwrite(node->id, sizeof(char), str_len + 1, file);
    fwrite(&(node->time), sizeof(int), 1, file);
}

char* readline(FILE* file, const char* prompt)
{
    fprintf(stdout, "%s", prompt);
    int size_inc = 10;
    int len = 0, cnt, max_len = size_inc + 1;
    char* new_buffer = NULL;
    char* buffer = (char*)malloc(max_len);
    char* cur_pos = buffer;
    while (1) {
        cnt = 0;
        if (fscanf(file, "%10[^\n]%n", cur_pos, &cnt) == EOF) {
            free(buffer);
            return NULL;
        }
        len += cnt;
        cur_pos += cnt;
        if (cnt == size_inc) {
            new_buffer = (char*)realloc(buffer, max_len += size_inc);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            cur_pos = new_buffer + len;
            buffer = new_buffer;
        } else {
            new_buffer = (char*)realloc(buffer, len + 1);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
            cur_pos = new_buffer + len;
            *cur_pos = '\0';
            break;
        }
    }
    fscanf(file, "%*c");
    return buffer;
}

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
