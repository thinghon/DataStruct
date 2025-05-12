#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 단어 정보를 담는 이중 연결 리스트 노드 정의
typedef struct wordNode {
    char english[30];            // 영어 단어
    char korean[30];             // 뜻
    struct wordNode* prev;       // 이전 노드 포인터
    struct wordNode* next;       // 다음 노드 포인터
} wordNode;

wordNode* head = NULL;           // 단어장의 시작 노드

// 새로운 단어 노드를 생성하는 함수
wordNode* create_node(const char* eng, const char* kor) {
    wordNode* newNode = (wordNode*)malloc(sizeof(wordNode)); // 메모리 동적 할당
    strcpy(newNode->english, eng);    // 영어 단어 복사
    strcpy(newNode->korean, kor);     // 뜻 복사
    newNode->prev = newNode->next = NULL; // 이전, 다음 포인터 초기화
    return newNode;
}

// 단어를 알파벳 순으로 삽입하는 함수
void add_word(const char* eng, const char* kor) {
    wordNode* newNode = create_node(eng, kor);

    // 리스트가 비어있는 경우, 새 노드가 head가 됨
    if (head == NULL) {
        head = newNode;
        return;
    }

    wordNode* curr = head;

    // 알파벳 순으로 위치 찾기
    while (curr != NULL && strcmp(curr->english, eng) < 0) {
        curr = curr->next;
    }

    if (curr == head) {
        // 새 단어가 가장 앞에 올 경우
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else if (curr == NULL) {
        // 새 단어가 가장 뒤에 올 경우
        wordNode* tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        tail->next = newNode;
        newNode->prev = tail;
    }
    else {
        // 중간에 삽입할 경우
        wordNode* prevNode = curr->prev;
        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next = curr;
        curr->prev = newNode;
    }
}

// 단어를 삭제하는 함수
void delete_word(const char* eng) {
    wordNode* curr = head;

    // 삭제할 단어를 찾음
    while (curr != NULL) {
        if (strcmp(curr->english, eng) == 0) {
            if (curr == head) {
                // 첫 노드인 경우 head를 다음 노드로 옮김
                head = curr->next;
                if (head != NULL) head->prev = NULL;
            }
            else {
                // 중간 또는 마지막 노드 삭제
                curr->prev->next = curr->next;
                if (curr->next != NULL) {
                    curr->next->prev = curr->prev;
                }
            }
            free(curr); // 메모리 해제
            printf("'%s' 삭제 완료\n", eng);
            return;
        }
        curr = curr->next;
    }
    printf("'%s' 단어를 찾을 수 없습니다.\n", eng);
}

// 단어를 검색하는 함수
void search_word(const char* eng) {
    wordNode* curr = head;
    while (curr != NULL) {
        if (strcmp(curr->english, eng) == 0) {
            printf("%s 뜻은 %s입니다.\n", eng, curr->korean);
            return;
        }
        curr = curr->next;
    }
    printf("'%s' 단어를 찾을 수 없습니다.\n", eng);
}

// 단어장에 있는 모든 단어를 출력하는 함수
void print_all() {
    if (head == NULL) {
        printf("단어장이 비어 있습니다.\n");
        return;
    }

    wordNode* curr = head;
    while (curr != NULL) {
        printf("%s(%s)", curr->english, curr->korean);
        if (curr->next != NULL)
            printf(" - "); // 중간 구분자
        curr = curr->next;
    }
    printf("\n");
}

// 시험 기능: 영어 단어를 보고 뜻을 입력받고 채점
void quiz() {
    if (head == NULL) {
        printf("단어장이 비어 있어 시험을 볼 수 없습니다.\n");
        return;
    }

    int correct = 0, wrong = 0;
    char answer[30];
    wordNode* curr = head;

    while (curr != NULL) {
        printf("%s: ", curr->english);     // 영어 단어 출력
        scanf(" %[^\n]", answer);          // 뜻 입력

        if (strcmp(curr->korean, answer) == 0)
            correct++;                     // 정답일 경우
        else
            wrong++;                       // 오답일 경우

        curr = curr->next;
    }
    printf("%d개 정답, %d개 오답입니다.\n", correct, wrong);
}

// 메인 함수: 사용자 인터페이스
int main() {
    int choice;
    char eng[30], kor[30];

    printf("*** 영어 단어장 프로그램 ***\n");

    while (1) {
        printf("추가<1> 삭제<2> 검색<3> 모두보기<4> 시험<5> 종료<0> ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("%d> 추가\n", choice);
            printf("영어: ");
            scanf(" %[^\n]", eng);
            printf("뜻: ");
            scanf(" %[^\n]", kor);
            add_word(eng, kor);
            break;

        case 2:
            printf("%d> 삭제\n", choice);
            printf("단어: ");
            scanf(" %[^\n]", eng);
            delete_word(eng);
            break;

        case 3:
            printf("%d> 검색\n", choice);
            printf("단어: ");
            scanf(" %[^\n]", eng);
            search_word(eng);
            break;

        case 4:
            printf("%d> 모두보기\n", choice);
            print_all();
            break;

        case 5:
            printf("%d> 시험\n", choice);
            quiz();
            break;

        case 0:
            printf("프로그램을 종료합니다.\n");
            return 0;

        default:
            printf("잘못된 선택입니다.\n");
        }
    }

    return 0;
}
