#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��� ����ü ����
typedef struct Node {
    char keyword[20];          // Ű���带 ������ ���ڿ�
    int count;                 // (������ ��� ��������) �˻� Ƚ���� ������ ����
    struct KeywordNode* link;  // ���� ��带 ����Ű�� ������
} KeywordNode;

// ����Ʈ �� �տ� �� Ű���带 �߰��ϴ� �Լ�
void insert_first(KeywordNode** head, char* keyword) {
    KeywordNode* new_node = (KeywordNode*)malloc(sizeof(KeywordNode)); // �� ��� ����
    strcpy(new_node->keyword, keyword); // Ű���� ����
    new_node->count = 1;                // count �⺻�� 1�� ���� (��� �� ������ �ʱ�ȭ)
    new_node->link = *head;              // �� ��尡 ���� head�� ����Ŵ
    *head = new_node;                    // head�� �� ���� ����
}

void print_list(KeywordNode* node) {
    if (node == NULL) return; // ������ ������ ����

    print_list(node->link); // ���� ��带 ���� ��� ȣ��

    if (node->link != NULL)    // ������ ��尡 �ƴϸ� '-' ���
        printf(" - ");
    printf("%s", node->keyword); // Ű���� ���
}

// Ư�� Ű���带 ���ο� Ű����� �����ϴ� �Լ�
void update_keyword(KeywordNode* head, char* old_keyword, char* new_keyword) {
    for (KeywordNode* p = head; p != NULL; p = p->link) { // ����Ʈ ��ȸ
        if (strcmp(p->keyword, old_keyword) == 0) {       // old_keyword ã����
            strcpy(p->keyword, new_keyword);              // ���ο� Ű����� ��ü
            return;
        }
    }
    printf("�ش� Ű���带 ã�� �� �����ϴ�.\n"); // �� ã���� ���
}

// Ư�� Ű���带 ����Ʈ���� �����ϴ� �Լ�
void delete_keyword(KeywordNode** head, char* keyword) {
    KeywordNode* current = *head;
    KeywordNode* prev = NULL;

    while (current != NULL) { // ����Ʈ ��ȸ
        if (strcmp(current->keyword, keyword) == 0) { // ������ Ű���� ã��
            if (prev == NULL) { // ������ ��尡 ù ��° ����� ���
                *head = current->link;
            }
            else { // �߰��̳� ������ ����� ���
                prev->link = current->link;
            }
            free(current); // �޸� ����
            printf("���� �Ϸ�\n");
            return;
        }
        prev = current; // ���� ��带 ���� ���� �̵�
        current = current->link; // ���� ��带 �������� �̵�
    }
    printf("�ش� Ű���带 ã�� �� �����ϴ�.\n"); // �� ã���� ���
}

void print_reverse_list(KeywordNode* head) {
    KeywordNode* p = head;
    if (p == NULL) return; // ����Ʈ�� ��������� �ƹ��͵� ���� ����

    printf("%s", p->keyword); // ù ��° ���� '-' ���� ���
    p = p->link;
    while (p != NULL) {       // �������� '-' �ٿ��� ���
        printf("-");
        printf("%s", p->keyword);
        p = p->link;
    }
    printf("\n");
}

int main() {
    KeywordNode* head = NULL;
    int choice;
    char keyword[20];
    char new_keyword[20];

    while (1) {
        printf("�߰� <1> ���<2> �������<3> ����<4> Ű�������<5> ����<6>: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            printf("1> �߰�: ");
            scanf("%s", keyword);
            insert_first(&head, keyword);
        }
        else if (choice == 2) {
            printf("2> ���\n");
            print_list(head);
            printf("\n");
        }
        else if (choice == 3) {
            printf("3> �������\n");
            print_reverse_list(head);
        }
        else if (choice == 4) {
            printf("4> ����\n");
            printf("������: ");
            scanf("%s", keyword);
            printf("������: ");
            scanf("%s", new_keyword);
            update_keyword(head, keyword, new_keyword);
        }
        else if (choice == 5) {
            printf("5> Ű���� ����\n");
            printf("������ Ű����: ");
            scanf("%s", keyword);
            delete_keyword(&head, keyword);
        }
        else if (choice == 6) {
            break;
        }
        else {
            printf("�߸� �Է��߽��ϴ�.\n");
        }
    }

    while (head != NULL) {
        KeywordNode* temp = head;
        head = head->link;
        free(temp);
    }

    return 0;
}
