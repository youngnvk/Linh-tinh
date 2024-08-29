#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *previous;
};

typedef struct node node;

struct that {
    struct node *head;
    struct node *tail;
};

typedef struct that that;

node *create(int x) {
    node *newnode = (node*)malloc(sizeof(node));
    newnode->data = x;
    newnode->previous = NULL;
    newnode->next = NULL;
    return newnode;
}

void deleted(that *list, node *Q){
    if(list->tail == NULL){
        printf("Danh sach rong\n");
    }
    else{
        if(list->tail == list->head) {
            list->head = list->tail = NULL;
        }
        else {
            if (Q == list->head) { // Nút đầu bị loại
                list->head = list->head->next;
                list->head->previous = NULL;
            }
            else if (Q == list->tail) { // Nút cuối bị loại
                list->tail = list->tail->previous;
                list->tail->next = NULL;
            }
            else { // Nút giữa bị loại
                Q->previous->next = Q->next;
                Q->next->previous = Q->previous;
            }
            free(Q);
        }
    }
}
void add(that *list, node *Q, int x) {
    node *P = create(x);
    if (list->tail == NULL) {
        list->head = list->tail = P;
    } else {
        if (Q == list->head) {  //Them vao dau
            P->next = list->head;
            list->head->previous = P;
            list->head = P;
        } else if (Q == list->tail) { // Thêm vào cuối danh sách
            P->previous = list->tail;
            list->tail->next = P;
            list->tail = P;
        } else { // Thêm vào giữa danh sách
            P->previous = Q->previous;
            P->next = Q;
            Q->previous->next = P;
            Q->previous = P;
        }
    }
}
void print(that *list){
    node *temp = list->head;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
node* findnode(that *list, int value){
    node *current = list->head;
    while(current != NULL){
        if(current->data == value){
            return current;
        }
        current = current->next;
    }
    return NULL;
}
int main() {
    that list = {NULL, NULL};
    // Ví dụ để test
    node *node1 = create(10);
    node *node2 = create(18);
    list.head = node1; // Gán head với node1
    node1->next = node2;
    node2->previous = node1;
    list.tail = node2; // Gán tail với node2
    while(1){
        printf("---------------------Menu--------------------\n");
        printf("1.Add\n");
        printf("2.Delete\n");
        printf("3.Print\n");
        printf("4.Exit\n");
        int lc;
        scanf("%d", &lc);
        if(lc == 4){
            break;
        } else if(lc == 3){
            print(&list);
        }
        else if(lc == 1){
            int k;
            printf("Moi nhap so can them vao: ");
            scanf("%d", &k);
            while(1){
                printf("1.1 Nhap 1 de them vao dau danh sach\n");
                printf("1.2 Nhap 2 de them vao cuoi danh sach\n");
                printf("1.3 Nhap 3 de them vao giua danh sach\n");
                int lc2;
                scanf("%d", &lc2);
                if (lc2 == 1) {
                    add(&list, list.head, k);
                    break;
            } else if (lc2 == 2) {
                    add(&list, list.tail, k);
                    break;
            }
             else if (lc2 == 3) {
                int value;
                printf("Nhap gia tri cua so can them vao truoc: ");
                scanf("%d", &value);
                node *prevnode = findnode(&list, value);
                if (prevnode != NULL) {
                    add(&list, prevnode, k);
                    break;
                } else {
                    printf("khong tim thay.\n");
                    break;
                }
            }
            else{
                printf("Moi nhap lai!\n");

            }

            }

        }
        else if(lc == 2){
            while(1){
                int lc3;
                printf("----------------------MENU----------------------\n");
                printf("2.1 Nhap 1 de xoa dau danh sach\n");
                printf("2.2 Nhap 2 de xoa cuoi danh sach\n");
                printf("2.3 Nhap 3 xoa mot nut giua danh sach\n");
                scanf("%d", &lc3);
                if(lc3 == 1){
                    deleted(&list, list.head);
                    break;
                }
                else if(lc3 == 2){
                    deleted(&list, list.tail);
                    break;
                }
                else if(lc3 == 3){
                    int value;
                    printf("Nhap gia tri cua node can xoa\n");
                    scanf("%d", &value);
                    node *removed = findnode(&list, value);
                    if(removed != NULL){
                        deleted(&list, removed);
                        break;
                    }
                    else{
                        printf("Khong tim thay!\n");
                        break;
                    }
                }
            }
        }
        else{
            printf("Moi nhap lai!\n");
        }
    }
    free(node1);
    free(node2);
}
