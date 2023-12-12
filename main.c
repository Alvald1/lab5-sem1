#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    char* name;
    char* id;
    int time;
} Node;

void init_node(Node* node);
Node* read_from_file(FILE* file);
char* readline(FILE* file, const char* prompt);
void dealloc_node(Node* node);
int valid_id(char id[9]);
void display_node(Node* node);

int main()
{
    FILE* file = fopen("test.txt", "r");
    for (int i = 0; i < 2; ++i) {
        Node* node = read_from_file(file);
        if (node != NULL) {
            display_node(node);
            dealloc_node(node);
        }
    }
    return 0;
}

void init_node(Node* node)
{
    node->name = NULL;
    node->id = NULL;
    node->time = 0;
}
void display_node(Node* node)
{
    printf("Name: %s\nID: %s\nTime: %d\n", node->name, node->id, node->time);
}

Node* read_from_file(FILE* file)
{
    Node* node = (Node*)malloc(sizeof(Node));
    init_node(node);
    char *prompt_name = "", *prompt_id = "", *prompt_time = "", *tmp = NULL, *id = NULL;
    if (file == stdin) {
        prompt_name = "Введите ФИО: ";
        prompt_id = "Введите ID: ";
        prompt_time = "Введите время: ";
    }
    char* str = readline(file, prompt_name);
    if (str != NULL) {
        node->name = str;
    } else {
        dealloc_node(node);
        return NULL;
    }
    int id_len = 9;
    tmp = (char*)malloc(id_len);
    if (tmp != NULL) {
        id = tmp;
    } else {
        fprintf(stderr, "Ошибка памяти\n");
        dealloc_node(node);
        return NULL;
    }
    fprintf(stdout, "%s", prompt_id);
    if (fscanf(file, "%9[^\n]", id) != EOF) {
        int flag = valid_id(id);
        if (flag) {
            node->id = id;
        } else {
            fprintf(stderr, "Ошибка ввода ID\n");
            tmp = calloc(1, 1);
            if (tmp != NULL) {
                node->id = tmp;
            } else {
                fprintf(stderr, "Ошибка памяти\n");
                dealloc_node(node);
                return NULL;
            }
        }
    } else {
        free(id);
        dealloc_node(node);
        return NULL;
    }
    int time = 0;
    fprintf(stdout, prompt_time);
    if (fscanf(file, "%d", &time) != EOF) {
        if (time > 0) {
            node->time = time;
        } else {
            fprintf(stderr, "Ошибка ввода time\n");
            fscanf(file, "%*[^\n]");
        }
    } else {
        dealloc_node(node);
        return NULL;
    }
    return node;
}

int valid_id(char id[9])
{
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

char* readline(FILE* file, const char* prompt)
{
    fprintf(stdout, "%s", prompt);
    fscanf(file, "%*[\n]");
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

void dealloc_node(Node* node)
{
    free(node->name);
    free(node->id);
    free(node);
}