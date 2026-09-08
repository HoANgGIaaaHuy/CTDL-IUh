#ifndef CTDL_H
#define CTDL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 16384

#ifdef __cplusplus
extern "C" {
#endif

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

// Struct quan ly hang doi yeu cau dat phong
typedef struct QueueNode {
    char name[50];
    char room[10];
    int days;
    double price_per_day;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int count;
} RequestQueue;

// Struct Node cho Cay Nhi Phan Tim Kiem
typedef struct TreeNode {
    Customer data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Struct cho Stack Undo (
typedef struct UndoNode {
    char state[MAX_LEN];
    struct UndoNode* next;
} UndoNode;

typedef struct {
    UndoNode* top;
    int count;
    int max_limit;
} UndoList;
void hotel_init(Customer** head);
int check_id_exists(Customer* head, const char* id);
void add_customer(Customer** head, Customer new_cust);
int delete_customer(Customer** head, const char* search_term);
Customer* find_customer_by_id(Customer* head, const char* id);
Customer* find_customer_by_name(Customer* head, const char* name);
Customer* find_customer_by_room(Customer* head, const char* room);
void update_customer(Customer* head, const char* id, const char* name, const char* room, int days, double price_per_day);
void free_customer_list(Customer** head);

// Sap xep
void sort_by_remaining_days(Customer** head, int ascending);
void sort_by_name(Customer** head, int ascending);
void sort_by_total_pay(Customer** head, int ascending);

// Doc/Ghi file text
int read_customers_from_file(Customer** head, const char* filename);
int write_customers_to_file(Customer* head, const char* filename);
//Nang cao

// 1. Stack (Undo)
void undo_init(UndoList* list, int max_limit);
void undo_save(UndoList* list, const char* state);
int undo_pop(UndoList* list, char* restoredState);
void undo_free(UndoList* list);
void serialize_list(Customer* head, char* buffer);
void deserialize_list(Customer** head, const char* buffer);
void save_undo_state(UndoList* list, Customer* head);

// 2. Queue
void queue_init(RequestQueue* q);
void enqueue_request(RequestQueue* q, const char* name, const char* room, int days, double price_per_day);
int dequeue_request(RequestQueue* q, char* name, char* room, int* days, double* price_per_day);
void free_queue(RequestQueue* q);

// 3. Tree
TreeNode* bst_insert(TreeNode* root, Customer cust);
TreeNode* build_bst_from_list(Customer* head);
TreeNode* bst_search_by_id(TreeNode* root, const char* id);
void bst_free(TreeNode* root);

// 4. Thong ke
void get_statistics(Customer* head, int* total_cust, int* total_days, int* total_rooms, double* total_revenue);

// 5. Lich su thao tac
void log_history(const char* action);

#ifdef __cplusplus
}
#endif

#endif // CTDL_H
