#define _GNU_SOURCE
<<<<<<< HEAD
//Define tren ko can giu, ghi de <time.h> khong bi loi tren linux
=======
#include "CTDL.h"
>>>>>>> e5aaaed (chinh sua lai 1 chut)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

<<<<<<< HEAD
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
=======
// Helper: hoan doi thong tin giua 2 khach hang (giu nguyen con tro next)
static void swap_customer_data(Customer* a, Customer* b) {
    Customer temp;
    memcpy(temp.id, a->id, sizeof(temp.id));
    memcpy(temp.name, a->name, sizeof(temp.name));
    memcpy(temp.room, a->room, sizeof(temp.room));
    temp.days = a->days;
    temp.price_per_day = a->price_per_day;
    temp.total_pay = a->total_pay;

    memcpy(a->id, b->id, sizeof(a->id));
    memcpy(a->name, b->name, sizeof(a->name));
    memcpy(a->room, b->room, sizeof(a->room));
    a->days = b->days;
    a->price_per_day = b->price_per_day;
    a->total_pay = b->total_pay;

    memcpy(b->id, temp.id, sizeof(b->id));
    memcpy(b->name, temp.name, sizeof(b->name));
    memcpy(b->room, temp.room, sizeof(b->room));
    b->days = temp.days;
    b->price_per_day = temp.price_per_day;
    b->total_pay = temp.total_pay;
}

// Khoi tao danh sach khach hang
void hotel_init(Customer** head) {
    *head = NULL;
}

// Kiem tra ma khach hang da ton tai hay chua
int check_id_exists(Customer* head, const char* id) {
    Customer* cur = head;
    while (cur != NULL) {
        if (strcmp(cur->id, id) == 0) {
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

// Them khach hang vao cuoi danh sach
void add_customer(Customer** head, Customer new_cust) {
    Customer* newNode = (Customer*)malloc(sizeof(Customer));
    if (!newNode) return;
    *newNode = new_cust;
    newNode->next = NULL;
    
    if (*head == NULL) {
        *head = newNode;
    } else {
        Customer* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Xoa khach hang theo ma hoac ten
int delete_customer(Customer** head, const char* search_term) {
    if (*head == NULL) return 0;
    Customer* temp = *head;
    Customer* prev = NULL;
    
    // Truong hop xoa nut dau tien
    if (strcmp(temp->id, search_term) == 0 || strcasecmp(temp->name, search_term) == 0) {
        *head = temp->next;
        free(temp);
        return 1;
    }
    
    // Tim nut can xoa
    while (temp != NULL && strcmp(temp->id, search_term) != 0 && strcasecmp(temp->name, search_term) != 0) {
        prev = temp;
        temp = temp->next;
    }
    
    // Khong tim thay
    if (temp == NULL) return 0;
    
    prev->next = temp->next;
    free(temp);
    return 1;
}

// Tim kiem khach hang theo ID
Customer* find_customer_by_id(Customer* head, const char* id) {
    Customer* cur = head;
    while (cur != NULL) {
        if (strcmp(cur->id, id) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// Tim kiem khach hang theo ten
Customer* find_customer_by_name(Customer* head, const char* name) {
    Customer* cur = head;
    while (cur != NULL) {
        if (strcasecmp(cur->name, name) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// Tim kiem khach hang theo phong
Customer* find_customer_by_room(Customer* head, const char* room) {
    Customer* cur = head;
    while (cur != NULL) {
        if (strcmp(cur->room, room) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// Cap nhat thong tin khach hang
void update_customer(Customer* head, const char* id, const char* name, const char* room, int days, double price_per_day) {
    Customer* cur = find_customer_by_id(head, id);
    if (cur) {
        strncpy(cur->name, name, sizeof(cur->name) - 1);
        cur->name[sizeof(cur->name) - 1] = '\0';
        strncpy(cur->room, room, sizeof(cur->room) - 1);
        cur->room[sizeof(cur->room) - 1] = '\0';
        cur->days = days;
        cur->price_per_day = price_per_day;
        cur->total_pay = days * price_per_day;
    }
}

// Giai phong toan bo danh sach khach hang
void free_customer_list(Customer** head) {
    if (!head) return;
    Customer* cur = *head;
    while (cur != NULL) {
        Customer* nextNode = cur->next;
        free(cur);
        cur = nextNode;
    }
    *head = NULL;
}

// Sap xep theo so ngay o con lai
void sort_by_remaining_days(Customer** head, int ascending) {
    if (!head || !*head) return;
    int swapped;
    Customer* ptr1;
    Customer* lptr = NULL;
    do {
        swapped = 0;
        ptr1 = *head;
        while (ptr1->next != lptr) {
            int condition = ascending ? (ptr1->days > ptr1->next->days) : (ptr1->days < ptr1->next->days);
            if (condition) {
                swap_customer_data(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Sap xep theo ten chu cai
void sort_by_name(Customer** head, int ascending) {
    if (!head || !*head) return;
    int swapped;
    Customer* ptr1;
    Customer* lptr = NULL;
    do {
        swapped = 0;
        ptr1 = *head;
        while (ptr1->next != lptr) {
            int cmp = strcasecmp(ptr1->name, ptr1->next->name);
            int condition = ascending ? (cmp > 0) : (cmp < 0);
            if (condition) {
                swap_customer_data(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Sap xep theo tong so tien phai tra
void sort_by_total_pay(Customer** head, int ascending) {
    if (!head || !*head) return;
    int swapped;
    Customer* ptr1;
    Customer* lptr = NULL;
    do {
        swapped = 0;
        ptr1 = *head;
        while (ptr1->next != lptr) {
            int condition = ascending ? (ptr1->total_pay > ptr1->next->total_pay) : (ptr1->total_pay < ptr1->next->total_pay);
            if (condition) {
                swap_customer_data(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Doc du lieu tu file customer.txt (id:ten:phong;songay;tongtien)
int read_customers_from_file(Customer** head, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return 0;
    
    free_customer_list(head);
    
    char line[512];
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) == 0) continue;
        
        Customer c;
        memset(&c, 0, sizeof(Customer));
        
        char* token_id = strtok(line, ":");
        char* token_name = strtok(NULL, ":");
        char* token_room = strtok(NULL, ";");
        char* token_days = strtok(NULL, ":");
        char* token_total = strtok(NULL, "");
        
        if (token_id && token_name && token_room && token_days && token_total) {
            strncpy(c.id, token_id, sizeof(c.id) - 1);
            strncpy(c.name, token_name, sizeof(c.name) - 1);
            strncpy(c.room, token_room, sizeof(c.room) - 1);
            c.days = atoi(token_days);
            c.total_pay = atof(token_total);
            if (c.days > 0) {
                c.price_per_day = c.total_pay / c.days;
            } else {
                c.price_per_day = 0;
            }
            add_customer(head, c);
        }
    }
    fclose(f);
    return 1;
}

// Ghi du lieu ra file customer.txt (id:ten:phong;songay;tongtien)
int write_customers_to_file(Customer* head, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) return 0;
    Customer* cur = head;
    while (cur != NULL) {
        fprintf(f, "%s:%s:%s;%d:%.2f\n", cur->id, cur->name, cur->room, cur->days, cur->total_pay);
        cur = cur->next;
    }
    fclose(f);
    return 1;
}

// Khoi tao ngan xep Stack de undo
>>>>>>> e5aaaed (chinh sua lai 1 chut)
void undo_init(UndoList* list, int max_limit) {
    list->top = NULL;
    list->count = 0;
    list->max_limit = max_limit;
}

<<<<<<< HEAD
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
=======
// Luu mot trang thai du lieu vao Stack
void undo_save(UndoList* list, const char* state) {
    if (!list) return;
    
    UndoNode* newNode = (UndoNode*)malloc(sizeof(UndoNode));
    if (!newNode) return;
    
    strncpy(newNode->state, state, MAX_LEN - 1);
    newNode->state[MAX_LEN - 1] = '\0';
    newNode->next = list->top;
    list->top = newNode;
    list->count++;
    
    // Neu qua han, xoa trang thai cu nhat o cuoi Stack
    if (list->count > list->max_limit) {
        UndoNode* cur = list->top;
        if (cur) {
            while (cur->next && cur->next->next) {
                cur = cur->next;
            }
            if (cur->next) {
                free(cur->next);
                cur->next = NULL;
            }
            list->count--;
        }
    }
}

// Khoi phuc mot trang thai gan nhat tu Stack
int undo_pop(UndoList* list, char* restoredState) {
    if (!list || !list->top) return 0;
    UndoNode* temp = list->top;
    strncpy(restoredState, temp->state, MAX_LEN - 1);
    restoredState[MAX_LEN - 1] = '\0';
    list->top = temp->next;
    free(temp);
    list->count--;
    return 1;
}

// Giai phong Stack undo
void undo_free(UndoList* list) {
    if (!list) return;
    UndoNode* cur = list->top;
    while (cur != NULL) {
        UndoNode* nextNode = cur->next;
        free(cur);
        cur = nextNode;
>>>>>>> e5aaaed (chinh sua lai 1 chut)
    }
    list->top = NULL;
    list->count = 0;
}
<<<<<<< HEAD
=======

// Tu dong hoa danh sach thanh dang chuoi phuc vu serialize
void serialize_list(Customer* head, char* buffer) {
    buffer[0] = '\0';
    Customer* cur = head;
    int offset = 0;
    while (cur != NULL) {
        int written = snprintf(buffer + offset, MAX_LEN - offset, "%s:%s:%s;%d:%.2f\n",
                               cur->id, cur->name, cur->room, cur->days, cur->total_pay);
        if (written < 0 || offset + written >= MAX_LEN) {
            break;
        }
        offset += written;
        cur = cur->next;
    }
}

// Chuyen chuoi da serialize ve lai danh sach lien ket
void deserialize_list(Customer** head, const char* buffer) {
    free_customer_list(head);
    if (!buffer || strlen(buffer) == 0) return;
    
    char* buf_copy = strdup(buffer);
    if (!buf_copy) return;
    
    char* saveptr;
    char* line = strtok_r(buf_copy, "\n", &saveptr);
    while (line != NULL) {
        Customer c;
        memset(&c, 0, sizeof(Customer));
        
        char* sub_saveptr;
        char* token_id = strtok_r(line, ":", &sub_saveptr);
        char* token_name = strtok_r(NULL, ":", &sub_saveptr);
        char* token_room = strtok_r(NULL, ";", &sub_saveptr);
        char* token_days = strtok_r(NULL, ":", &sub_saveptr);
        char* token_total = strtok_r(NULL, "", &sub_saveptr);
        
        if (token_id && token_name && token_room && token_days && token_total) {
            strncpy(c.id, token_id, sizeof(c.id) - 1);
            strncpy(c.name, token_name, sizeof(c.name) - 1);
            strncpy(c.room, token_room, sizeof(c.room) - 1);
            c.days = atoi(token_days);
            c.total_pay = atof(token_total);
            if (c.days > 0) {
                c.price_per_day = c.total_pay / c.days;
            } else {
                c.price_per_day = 0;
            }
            add_customer(head, c);
        }
        line = strtok_r(NULL, "\n", &saveptr);
    }
    free(buf_copy);
}

// Sao luu trang thai hien tai cua danh sach phuc vu undo
void save_undo_state(UndoList* list, Customer* head) {
    char state[MAX_LEN];
    serialize_list(head, state);
    undo_save(list, state);
}

// Khoi tao hang doi yeu cau
void queue_init(RequestQueue* q) {
    if (!q) return;
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
}

// Them yeu cau dat phong vao hang doi (Queue)
void enqueue_request(RequestQueue* q, const char* name, const char* room, int days, double price_per_day) {
    if (!q) return;
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newNode) return;
    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0';
    strncpy(newNode->room, room, sizeof(newNode->room) - 1);
    newNode->room[sizeof(newNode->room) - 1] = '\0';
    newNode->days = days;
    newNode->price_per_day = price_per_day;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
}

// Lay yeu cau dat phong khoi hang doi (Queue)
int dequeue_request(RequestQueue* q, char* name, char* room, int* days, double* price_per_day) {
    if (!q || !q->front) return 0;
    QueueNode* temp = q->front;
    if (name) strcpy(name, temp->name);
    if (room) strcpy(room, temp->room);
    if (days) *days = temp->days;
    if (price_per_day) *price_per_day = temp->price_per_day;
    
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    q->count--;
    return 1;
}

// Giai phong hang doi yeu cau
void free_queue(RequestQueue* q) {
    if (!q) return;
    QueueNode* cur = q->front;
    while (cur != NULL) {
        QueueNode* nextNode = cur->next;
        free(cur);
        cur = nextNode;
    }
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
}

// Chen mot khach hang vao cay nhi phan tim kiem (BST)
TreeNode* bst_insert(TreeNode* root, Customer cust) {
    if (root == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        if (!newNode) return NULL;
        newNode->data = cust;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    
    int cmp = strcmp(cust.id, root->data.id);
    if (cmp < 0) {
        root->left = bst_insert(root->left, cust);
    } else {
        root->right = bst_insert(root->right, cust);
    }
    return root;
}

// Dung cay nhi phan tu danh sach lien ket khach hang
TreeNode* build_bst_from_list(Customer* head) {
    TreeNode* root = NULL;
    Customer* cur = head;
    while (cur != NULL) {
        root = bst_insert(root, *cur);
        cur = cur->next;
    }
    return root;
}

// Tim kiem nhanh bang cay nhi phan tim kiem (BST)
TreeNode* bst_search_by_id(TreeNode* root, const char* id) {
    if (root == NULL) return NULL;
    int cmp = strcmp(id, root->data.id);
    if (cmp == 0) return root;
    if (cmp < 0) return bst_search_by_id(root->left, id);
    return bst_search_by_id(root->right, id);
}

// Giai phong cay nhi phan tim kiem
void bst_free(TreeNode* root) {
    if (root == NULL) return;
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}

// Thong ke cac so lieu du lieu khach san??? khong dong vao da test co
void get_statistics(Customer* head, int* total_cust, int* total_days, int* total_rooms, double* total_revenue) {
    *total_cust = 0;
    *total_days = 0;
    *total_rooms = 0;
    *total_revenue = 0.0;
    
    char room_list[1000][10];
    int room_count = 0;
    
    Customer* cur = head;
    while (cur != NULL) {
        (*total_cust)++;
        *total_days += cur->days;
        *total_revenue += cur->total_pay;
        
        int exists = 0;
        for (int i = 0; i < room_count; i++) {
            if (strcmp(room_list[i], cur->room) == 0) {
                exists = 1;
                break;
            }
        }
        if (!exists && room_count < 1000) {
            strcpy(room_list[room_count], cur->room);
            room_count++;
        }
        
        cur = cur->next;
    }
    *total_rooms = room_count;
}
>>>>>>> e5aaaed (chinh sua lai 1 chut)
void log_history(const char* action) {
    FILE* f = fopen("history.txt", "a");
    if (!f) return;
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    char time_str[10];
    strftime(time_str, sizeof(time_str), "%H:%M", tm_info);
    fprintf(f, "[%s] %s\n", time_str, action);
    fclose(f);
<<<<<<< HEAD
}
//Dung cau code duoi khoi tao 1 action 
 //char log_msg[150];
                    //snprintf(log_msg, sizeof(log_msg), "Them Khach {%s}{%s}{%d}h", c.name, c.room, c.days * 24);
                    //log_history(log_msg);
=======
};
>>>>>>> e5aaaed (chinh sua lai 1 chut)
