#define _GNU_SOURCE
//Define tren ko can giu, ghi de <time.h> khong bi loi tren linux
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#define MAX_LEN 16384
// Struct quan ly thong tin khach hang
typedef struct Customer {
    char id[15];
    char name[50];
    char room[10];
    int days;
    double price_per_day;
    double total_pay;
    struct Customer* next;
} Customer;
void undo_init(UndoList* list, int max_limit) {
    list->top = NULL;
    list->count = 0;
    list->max_limit = max_limit;
}

void undo_save(UndoList* list, const char* state) {
    if (list == NULL) return;

    // Tao Node moi
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return; 
    strncpy(newNode->state, state, MAX_LEN - 1);
    newNode->state[MAX_LEN - 1] = '\0'; 
    // Push vao stack
    newNode->next = list->top;
    list->top = newNode;
    list->count++;

    //Neu vuot gioi han, xoa node cu nhat o duoi
    if (list->count > list->max_limit) {
        Node* temp = list->top;
        // Duyet toi node ke cuoi
        while (temp->next != NULL && temp->next->next != NULL) {
            temp = temp->next;
        }
        free(temp->next); 
        temp->next = NULL;
        list->count--;
    }
}

int undo_pop(UndoList* list, char* restoredState) {
    if (list == NULL || list->top == NULL) {
        return 0;
    }
    
    Node* temp = list->top;
    list->top = list->top->next;
    
    strncpy(restoredState, temp->state, MAX_LEN - 1);
    restoredState[MAX_LEN - 1] = '\0';

    free(temp);
    list->count--;
    return 1; 
}
void undo_free(UndoList* list) {
    if (list == NULL) return;
    
    Node* current = list->top;
    Node* nextNode = NULL;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    list->top = NULL;
    list->count = 0;
}
void log_history(const char* action) {
    FILE* f = fopen("history.txt", "a");
    if (!f) return;
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    char time_str[10];
    strftime(time_str, sizeof(time_str), "%H:%M", tm_info);
    fprintf(f, "[%s] %s\n", time_str, action);
    fclose(f);
}
//Dung cau code duoi khoi tao 1 action 
 //char log_msg[150];
                    //snprintf(log_msg, sizeof(log_msg), "Them Khach {%s}{%s}{%d}h", c.name, c.room, c.days * 24);
                    //log_history(log_msg);