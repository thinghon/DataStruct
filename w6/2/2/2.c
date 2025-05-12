#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ű���� ��� ����ü ����
typedef struct KeywordNode {
    char keyword[20];           // Ű���� ����
    int count;                  // �˻��� Ƚ�� ����
    int timestamp;              // �Է� ������ �����ϴ� ����
    struct KeywordNode* link;   // ���� ��带 ����Ű�� ������
} KeywordNode;

KeywordNode* head = NULL; // ���� ����Ʈ�� ���� ������ (��������)
int timestamp_counter = 0; // �Էµ� ������ �����ϴ� ī����

// �� ��带 �����ϴ� �Լ�
KeywordNode* create_node(const char* keyword) {
    KeywordNode* newNode = (KeywordNode*)malloc(sizeof(KeywordNode)); // �޸� �Ҵ�
    strcpy(newNode->keyword, keyword); // Ű���� ����
    newNode->count = 1;                // ó�� �߰��ǹǷ� �˻� Ƚ�� 1�� �ʱ�ȭ
    newNode->timestamp = timestamp_counter++; // ������� �����ϴ� Ÿ�ӽ�����
    newNode->link = NULL;              // ���� ���� ���� ����
    return newNode;
}

// ����Ʈ�� ����ϴ� �Լ� (�˻� Ƚ���� ���� ������ ���)
void print_list() {
    KeywordNode* p = head;
    while (p != NULL) {
        printf("%s - ", p->keyword); // Ű����� �˻� Ƚ�� ���
        p = p->link;                             // ���� ���� �̵�
    }
    printf("\n");
}

// Ű���带 �˻��ϴ� �Լ�
void search_keyword(const char* keyword) {
    KeywordNode* p = head;
    KeywordNode* prev = NULL;

    while (p != NULL) {
        if (strcmp(p->keyword, keyword) == 0) { // Ű���� �߰�
            p->count++; // �˻� �� ����
            return; // ��
        }
        prev = p;
        p = p->link;
    }
    // Ű���带 ã�� �������� �� ��带 ����Ʈ �� �տ� �߰�
    KeywordNode* newNode = create_node(keyword);

    // ���� �Էµ� Ű���尡 �� ���� �˻��� Ű���庸�� �տ� ������ ���� ��ġ�� ã��
    if (head == NULL || head->count < newNode->count) {
        // �� �տ� ����
        newNode->link = head;
        head = newNode;
    }
    else {
        // �˸��� ��ġ�� ����
        p = head;
        while (p->link != NULL && p->link->count >= newNode->count) {
            p = p->link;
        }
        newNode->link = p->link;
        p->link = newNode;
    }
}

// Ű���带 �����ϴ� �Լ�
void delete_keyword(const char* keyword) {
    KeywordNode* p = head;
    KeywordNode* prev = NULL;

    while (p != NULL) {
        if (strcmp(p->keyword, keyword) == 0) { // ������ Ű���� �߰�
            if (prev == NULL) { // ������ ��尡 head�� ���
                head = p->link;
            }
            else { // �߰��̳� ������ ����� ���
                prev->link = p->link;
            }
            free(p); // �޸� ����
            printf("'%s' ���� �Ϸ�!\n", keyword);
            return;
        }
        prev = p;
        p = p->link;
    }
    printf("'%s' ã�� �� �����ϴ�.\n", keyword);
}

int main() {
    int choice;
    char input[20];

    printf("*** �ǽð� �˻� �ý��� ***\n");

    while (1) {
        printf("\n�˻�<1> �˻�����<2> Ű���� ����<3> ����<4> : ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("�˻��� Ű���� �Է�: ");
            scanf("%s", input);
            search_keyword(input); // Ű���� �˻� �� ����Ʈ ��迭
        }
        else if (choice == 2) {
            printf("\n== ���� �˻� ���� ==\n");
            print_list(); // ����Ʈ ���
        }
        else if (choice == 3) {
            printf("������ Ű���� �Է�: ");
            scanf("%s", input);
            delete_keyword(input); // Ű���� ����
        }
        else if (choice == 4) {
            printf("���α׷� ����\n");
            break; // ���α׷� ����
        }
        else {
            printf("�߸��� �Է��Դϴ�.\n");
        }
    }

    // ���α׷� ���� �� �޸� ����
    KeywordNode* p = head;
    while (p != NULL) {
        KeywordNode* temp = p;
        p = p->link;
        free(temp);
    }

    return 0;
}
