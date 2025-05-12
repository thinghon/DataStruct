#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 음악 정보를 저장하는 노드 구조체 정의
typedef struct MusicNode {
    char title[50];              // 음악 제목
    char artist[50];             // 아티스트 이름
    struct MusicNode* next;      // 다음 노드를 가리키는 포인터
} MusicNode;

MusicNode* tail = NULL;  // 원형 연결 리스트의 마지막 노드(꼬리)를 가리키는 포인터

// 새로운 노드 생성 함수
MusicNode* create_node(const char* title, const char* artist) {
    MusicNode* newNode = (MusicNode*)malloc(sizeof(MusicNode));
    strcpy(newNode->title, title);
    strcpy(newNode->artist, artist);
    newNode->next = newNode;  // 자기 자신을 가리키도록 초기화 (단일 노드인 경우)
    return newNode;
}

// 음악 추가 함수
void add_music(const char* title, const char* artist) {
    MusicNode* newNode = create_node(title, artist);
    if (tail == NULL) {
        // 리스트가 비어있을 경우
        tail = newNode;
    }
    else {
        // 새로운 노드를 꼬리에 연결하고 꼬리를 갱신
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }
}

// 음악 삭제 함수
void delete_music(const char* title) {
    if (tail == NULL) {
        printf("삭제할 음악이 없습니다.\n");
        return;
    }

    MusicNode* curr = tail->next;
    MusicNode* prev = tail;

    do {
        if (strcmp(curr->title, title) == 0) {
            // 삭제 대상이 하나뿐인 경우
            if (curr == tail && curr->next == tail) {
                free(curr);
                tail = NULL;
            }
            else {
                // 삭제 대상이 여러 개 중 하나인 경우
                prev->next = curr->next;
                if (curr == tail) tail = prev;
                free(curr);
            }
            return;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != tail->next);

    printf("음악 '%s'을(를) 찾을 수 없습니다.\n", title);
}

// 반복 재생 함수
void repeat_play(int times) {
    if (tail == NULL) {
        printf("재생할 음악이 없습니다.\n");
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

// 한번 재생 함수 (모든 곡을 1번씩만 재생)
void play_once() {
    if (tail == NULL) {
        printf("재생할 음악이 없습니다.\n");
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

// 음악 리스트 출력 함수
void print_list() {
    if (tail == NULL) {
        printf("음악이 없습니다.\n");
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

    printf("***음악 재생 프로그램***\n");

    while (1) {
        // 사용자 메뉴 입력 받기
        printf("추가<1> 삭제<2> 반복재생<3> 한번재생<4> 음악리스트<5> ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            // 음악 추가
            printf("%d> 추가\n", choice);
            printf("제목: ");
            scanf(" %[^\n]", title);       // 공백 포함 입력
            printf("아티스트: ");
            scanf(" %[^\n]", artist);
            add_music(title, artist);
            break;

        case 2:
            // 음악 삭제
            printf("%d> 삭제\n", choice);
            printf("제목: ");
            scanf(" %[^\n]", title);
            delete_music(title);
            break;

        case 3:
            // 반복 재생
            printf("%d> 반복재생\n", choice);
            printf("재생할 음악 수: ");
            scanf("%d", &repeatCount);
            repeat_play(repeatCount);
            break;

        case 4:
            // 한번 재생 (입력받은 수만큼 재생, 전체 수보다 크면 전체만 재생)
            printf("%d> 한번재생\n", choice);
            printf("재생할 음악 수: ");
            scanf("%d", &repeatCount);

            if (tail == NULL) {
                printf("재생할 음악이 없습니다.\n");
                break;
            }

            // 전체 음악 수 계산
            int total = 1;
            MusicNode* temp = tail->next;
            while (temp != tail) {
                total++;
                temp = temp->next;
            }

            // playCount = 재생할 수 (입력값 또는 전체 수 중 작은 값)
            int playCount = (repeatCount < total) ? repeatCount : total;

            // 최대 playCount 개수만큼 재생
            temp = tail->next;
            for (int i = 0; i < playCount; i++) {
                printf("%s(%s)", temp->title, temp->artist);
                if (i < playCount - 1) printf("-");
                temp = temp->next;
            }
            printf("\n");
            break;

        case 5:
            // 음악 리스트 출력
            printf("%d> 음악리스트\n", choice);
            print_list();
            break;

        default:
            printf("잘못된 선택입니다.\n");
        }
    }

    return 0;
}
