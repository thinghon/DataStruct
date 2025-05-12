#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���� ������ �����ϴ� ��� ����ü ����
typedef struct MusicNode {
    char title[50];              // ���� ����
    char artist[50];             // ��Ƽ��Ʈ �̸�
    struct MusicNode* next;      // ���� ��带 ����Ű�� ������
} MusicNode;

MusicNode* tail = NULL;  // ���� ���� ����Ʈ�� ������ ���(����)�� ����Ű�� ������

// ���ο� ��� ���� �Լ�
MusicNode* create_node(const char* title, const char* artist) {
    MusicNode* newNode = (MusicNode*)malloc(sizeof(MusicNode));
    strcpy(newNode->title, title);
    strcpy(newNode->artist, artist);
    newNode->next = newNode;  // �ڱ� �ڽ��� ����Ű���� �ʱ�ȭ (���� ����� ���)
    return newNode;
}

// ���� �߰� �Լ�
void add_music(const char* title, const char* artist) {
    MusicNode* newNode = create_node(title, artist);
    if (tail == NULL) {
        // ����Ʈ�� ������� ���
        tail = newNode;
    }
    else {
        // ���ο� ��带 ������ �����ϰ� ������ ����
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }
}

// ���� ���� �Լ�
void delete_music(const char* title) {
    if (tail == NULL) {
        printf("������ ������ �����ϴ�.\n");
        return;
    }

    MusicNode* curr = tail->next;
    MusicNode* prev = tail;

    do {
        if (strcmp(curr->title, title) == 0) {
            // ���� ����� �ϳ����� ���
            if (curr == tail && curr->next == tail) {
                free(curr);
                tail = NULL;
            }
            else {
                // ���� ����� ���� �� �� �ϳ��� ���
                prev->next = curr->next;
                if (curr == tail) tail = prev;
                free(curr);
            }
            return;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != tail->next);

    printf("���� '%s'��(��) ã�� �� �����ϴ�.\n", title);
}

// �ݺ� ��� �Լ�
void repeat_play(int times) {
    if (tail == NULL) {
        printf("����� ������ �����ϴ�.\n");
        return;
    }

    MusicNode* curr = tail->next;
    for (int i = 0; i < times; i++) {
        printf("%s(%s)", curr->title, curr->artist);
        if (i < times - 1) printf("-");
        curr = curr->next;
    }
    printf("\n");
}

// �ѹ� ��� �Լ� (��� ���� 1������ ���)
void play_once() {
    if (tail == NULL) {
        printf("����� ������ �����ϴ�.\n");
        return;
    }

    MusicNode* curr = tail->next;
    MusicNode* start = curr;
    do {
        printf("%s(%s)", curr->title, curr->artist);
        curr = curr->next;
        if (curr != start) printf("-");
    } while (curr != start);
    printf("\n");
}

// ���� ����Ʈ ��� �Լ�
void print_list() {
    if (tail == NULL) {
        printf("������ �����ϴ�.\n");
        return;
    }

    MusicNode* curr = tail->next;
    MusicNode* start = curr;
    do {
        printf("%s(%s)", curr->title, curr->artist);
        curr = curr->next;
        if (curr != start) printf("-");
    } while (curr != start);
    printf("\n");
}

int main() {
    int choice;
    char title[50], artist[50];
    int repeatCount;

    printf("***���� ��� ���α׷�***\n");

    while (1) {
        // ����� �޴� �Է� �ޱ�
        printf("�߰�<1> ����<2> �ݺ����<3> �ѹ����<4> ���Ǹ���Ʈ<5> ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            // ���� �߰�
            printf("%d> �߰�\n", choice);
            printf("����: ");
            scanf(" %[^\n]", title);       // ���� ���� �Է�
            printf("��Ƽ��Ʈ: ");
            scanf(" %[^\n]", artist);
            add_music(title, artist);
            break;

        case 2:
            // ���� ����
            printf("%d> ����\n", choice);
            printf("����: ");
            scanf(" %[^\n]", title);
            delete_music(title);
            break;

        case 3:
            // �ݺ� ���
            printf("%d> �ݺ����\n", choice);
            printf("����� ���� ��: ");
            scanf("%d", &repeatCount);
            repeat_play(repeatCount);
            break;

        case 4:
            // �ѹ� ��� (�Է¹��� ����ŭ ���, ��ü ������ ũ�� ��ü�� ���)
            printf("%d> �ѹ����\n", choice);
            printf("����� ���� ��: ");
            scanf("%d", &repeatCount);

            if (tail == NULL) {
                printf("����� ������ �����ϴ�.\n");
                break;
            }

            // ��ü ���� �� ���
            int total = 1;
            MusicNode* temp = tail->next;
            while (temp != tail) {
                total++;
                temp = temp->next;
            }

            // playCount = ����� �� (�Է°� �Ǵ� ��ü �� �� ���� ��)
            int playCount = (repeatCount < total) ? repeatCount : total;

            // �ִ� playCount ������ŭ ���
            temp = tail->next;
            for (int i = 0; i < playCount; i++) {
                printf("%s(%s)", temp->title, temp->artist);
                if (i < playCount - 1) printf("-");
                temp = temp->next;
            }
            printf("\n");
            break;

        case 5:
            // ���� ����Ʈ ���
            printf("%d> ���Ǹ���Ʈ\n", choice);
            print_list();
            break;

        default:
            printf("�߸��� �����Դϴ�.\n");
        }
    }

    return 0;
}
