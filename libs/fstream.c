#include "fstream.h"

int read(FILE* file, Node*** nodes, int mode)
{
    int cnt = 0;
    fptr_read_mode read_mode = NULL;
    if (mode == BIN_MODE) {
        fread(&cnt, sizeof(int), 1, file);
        read_mode = read_node_from_bin;
    } else if (mode == FILE_MODE) {
        if (file == stdin) {
            fprintf(stdout, "Количетво структур: ");
        }
        if (fscanf(file, "%d", &cnt) == EOF) {
            return 0;
        }
        fscanf(file, "%*c");
        read_mode = read_node_from_file;
    }
    void* tmp = malloc(cnt * sizeof(Node*));
    if (valid_alloc((void*)nodes, tmp, NULL, 1) == 0) {
        return 0;
    }
    for (int i = 0; i < cnt; ++i) {
        tmp = (*read_mode)(file);
        if (tmp != NULL) {
            (*(*nodes + i)) = tmp;
        } else {
            dealloc_nodes(*nodes, i - 1);
            return 0;
        }
    }
    return cnt;
}

void write(FILE* file, Node** nodes, int cnt, int mode)
{
    fptr_write_mode write_mode = NULL;
    if (mode == BIN_MODE) {
        fwrite(&cnt, sizeof(int), 1, file);
        write_mode = write_node_to_bin;
    } else if (mode == FILE_MODE) {
        if (file != stdout) {
            fprintf(file, "%d\n", cnt);
        }
        write_mode = write_node_to_file;
    }
    for (int i = 0; i < cnt; ++i) {
        (*write_mode)(file, *(nodes + i));
    }
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
