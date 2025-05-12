#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

int main() {
    int n, i, value;
    Node* head = NULL;
    Node* tail = NULL;

    printf("데이터의 개수를 입력하시오 : ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        printf("노드 #%d의 데이터를 입력하시오: ", i);
        scanf("%d", &value);
        Node* new_node = create_node(value);

        if (head == NULL) {
            head = tail = new_node;
        }
        else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
    }

    printf("\n데이터를 역순으로 출력: ");
    Node* curr = tail;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->prev;
    }
    printf("\n");

    curr = head;
    while (curr != NULL) {
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }

    return 0;
}
