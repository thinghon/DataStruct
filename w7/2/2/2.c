#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �ܾ� ������ ��� ���� ���� ����Ʈ ��� ����
typedef struct wordNode {
    char english[30];            // ���� �ܾ�
    char korean[30];             // ��
    struct wordNode* prev;       // ���� ��� ������
    struct wordNode* next;       // ���� ��� ������
} wordNode;

wordNode* head = NULL;           // �ܾ����� ���� ���

// ���ο� �ܾ� ��带 �����ϴ� �Լ�
wordNode* create_node(const char* eng, const char* kor) {
    wordNode* newNode = (wordNode*)malloc(sizeof(wordNode)); // �޸� ���� �Ҵ�
    strcpy(newNode->english, eng);    // ���� �ܾ� ����
    strcpy(newNode->korean, kor);     // �� ����
    newNode->prev = newNode->next = NULL; // ����, ���� ������ �ʱ�ȭ
    return newNode;
}

// �ܾ ���ĺ� ������ �����ϴ� �Լ�
void add_word(const char* eng, const char* kor) {
    wordNode* newNode = create_node(eng, kor);

    // ����Ʈ�� ����ִ� ���, �� ��尡 head�� ��
    if (head == NULL) {
        head = newNode;
        return;
    }

    wordNode* curr = head;

    // ���ĺ� ������ ��ġ ã��
    while (curr != NULL && strcmp(curr->english, eng) < 0) {
        curr = curr->next;
    }

    if (curr == head) {
        // �� �ܾ ���� �տ� �� ���
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else if (curr == NULL) {
        // �� �ܾ ���� �ڿ� �� ���
        wordNode* tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        tail->next = newNode;
        newNode->prev = tail;
    }
    else {
        // �߰��� ������ ���
        wordNode* prevNode = curr->prev;
        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next = curr;
        curr->prev = newNode;
    }
}

// �ܾ �����ϴ� �Լ�
void delete_word(const char* eng) {
    wordNode* curr = head;

    // ������ �ܾ ã��
    while (curr != NULL) {
        if (strcmp(curr->english, eng) == 0) {
            if (curr == head) {
                // ù ����� ��� head�� ���� ���� �ű�
                head = curr->next;
                if (head != NULL) head->prev = NULL;
            }
            else {
                // �߰� �Ǵ� ������ ��� ����
                curr->prev->next = curr->next;
                if (curr->next != NULL) {
                    curr->next->prev = curr->prev;
                }
            }
            free(curr); // �޸� ����
            printf("'%s' ���� �Ϸ�\n", eng);
            return;
        }
        curr = curr->next;
    }
    printf("'%s' �ܾ ã�� �� �����ϴ�.\n", eng);
}

// �ܾ �˻��ϴ� �Լ�
void search_word(const char* eng) {
    wordNode* curr = head;
    while (curr != NULL) {
        if (strcmp(curr->english, eng) == 0) {
            printf("%s ���� %s�Դϴ�.\n", eng, curr->korean);
            return;
        }
        curr = curr->next;
    }
    printf("'%s' �ܾ ã�� �� �����ϴ�.\n", eng);
}

// �ܾ��忡 �ִ� ��� �ܾ ����ϴ� �Լ�
void print_all() {
    if (head == NULL) {
        printf("�ܾ����� ��� �ֽ��ϴ�.\n");
        return;
    }

    wordNode* curr = head;
    while (curr != NULL) {
        printf("%s(%s)", curr->english, curr->korean);
        if (curr->next != NULL)
            printf(" - "); // �߰� ������
        curr = curr->next;
    }
    printf("\n");
}

// ���� ���: ���� �ܾ ���� ���� �Է¹ް� ä��
void quiz() {
    if (head == NULL) {
        printf("�ܾ����� ��� �־� ������ �� �� �����ϴ�.\n");
        return;
    }

    int correct = 0, wrong = 0;
    char answer[30];
    wordNode* curr = head;

    while (curr != NULL) {
        printf("%s: ", curr->english);     // ���� �ܾ� ���
        scanf(" %[^\n]", answer);          // �� �Է�

        if (strcmp(curr->korean, answer) == 0)
            correct++;                     // ������ ���
        else
            wrong++;                       // ������ ���

        curr = curr->next;
    }
    printf("%d�� ����, %d�� �����Դϴ�.\n", correct, wrong);
}

// ���� �Լ�: ����� �������̽�
int main() {
    int choice;
    char eng[30], kor[30];

    printf("*** ���� �ܾ��� ���α׷� ***\n");

    while (1) {
        printf("�߰�<1> ����<2> �˻�<3> ��κ���<4> ����<5> ����<0> ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("%d> �߰�\n", choice);
            printf("����: ");
            scanf(" %[^\n]", eng);
            printf("��: ");
            scanf(" %[^\n]", kor);
            add_word(eng, kor);
            break;

        case 2:
            printf("%d> ����\n", choice);
            printf("�ܾ�: ");
            scanf(" %[^\n]", eng);
            delete_word(eng);
            break;

        case 3:
            printf("%d> �˻�\n", choice);
            printf("�ܾ�: ");
            scanf(" %[^\n]", eng);
            search_word(eng);
            break;

        case 4:
            printf("%d> ��κ���\n", choice);
            print_all();
            break;

        case 5:
            printf("%d> ����\n", choice);
            quiz();
            break;

        case 0:
            printf("���α׷��� �����մϴ�.\n");
            return 0;

        default:
            printf("�߸��� �����Դϴ�.\n");
        }
    }

    return 0;
}
