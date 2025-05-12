#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 키워드 노드 구조체 정의
typedef struct KeywordNode {
    char keyword[20];           // 키워드 저장
    int count;                  // 검색된 횟수 저장
    int timestamp;              // 입력 순서를 저장하는 변수
    struct KeywordNode* link;   // 다음 노드를 가리키는 포인터
} KeywordNode;

KeywordNode* head = NULL; // 연결 리스트의 시작 포인터 (전역변수)
int timestamp_counter = 0; // 입력된 순서를 관리하는 카운터

// 새 노드를 생성하는 함수
KeywordNode* create_node(const char* keyword) {
    KeywordNode* newNode = (KeywordNode*)malloc(sizeof(KeywordNode)); // 메모리 할당
    strcpy(newNode->keyword, keyword); // 키워드 복사
    newNode->count = 1;                // 처음 추가되므로 검색 횟수 1로 초기화
    newNode->timestamp = timestamp_counter++; // 순서대로 증가하는 타임스탬프
    newNode->link = NULL;              // 다음 노드는 아직 없음
    return newNode;
}

// 리스트를 출력하는 함수 (검색 횟수가 많은 순으로 출력)
void print_list() {
    KeywordNode* p = head;
    while (p != NULL) {
        printf("%s - ", p->keyword); // 키워드와 검색 횟수 출력
        p = p->link;                             // 다음 노드로 이동
    }
    printf("\n");
}

// 키워드를 검색하는 함수
void search_keyword(const char* keyword) {
    KeywordNode* p = head;
    KeywordNode* prev = NULL;

    while (p != NULL) {
        if (strcmp(p->keyword, keyword) == 0) { // 키워드 발견
            p->count++; // 검색 수 증가
            return; // 끝
        }
        prev = p;
        p = p->link;
    }
    // 키워드를 찾지 못했으면 새 노드를 리스트 맨 앞에 추가
    KeywordNode* newNode = create_node(keyword);

    // 새로 입력된 키워드가 더 자주 검색된 키워드보다 앞에 오도록 삽입 위치를 찾음
    if (head == NULL || head->count < newNode->count) {
        // 맨 앞에 삽입
        newNode->link = head;
        head = newNode;
    }
    else {
        // 알맞은 위치에 삽입
        p = head;
        while (p->link != NULL && p->link->count >= newNode->count) {
            p = p->link;
        }
        newNode->link = p->link;
        p->link = newNode;
    }
}

// 키워드를 삭제하는 함수
void delete_keyword(const char* keyword) {
    KeywordNode* p = head;
    KeywordNode* prev = NULL;

    while (p != NULL) {
        if (strcmp(p->keyword, keyword) == 0) { // 삭제할 키워드 발견
            if (prev == NULL) { // 삭제할 노드가 head인 경우
                head = p->link;
            }
            else { // 중간이나 마지막 노드인 경우
                prev->link = p->link;
            }
            free(p); // 메모리 해제
            printf("'%s' 삭제 완료!\n", keyword);
            return;
        }
        prev = p;
        p = p->link;
    }
    printf("'%s' 찾을 수 없습니다.\n", keyword);
}

int main() {
    int choice;
    char input[20];

    printf("*** 실시간 검색 시스템 ***\n");

    while (1) {
        printf("\n검색<1> 검색순위<2> 키워드 삭제<3> 종료<4> : ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("검색할 키워드 입력: ");
            scanf("%s", input);
            search_keyword(input); // 키워드 검색 및 리스트 재배열
        }
        else if (choice == 2) {
            printf("\n== 현재 검색 순위 ==\n");
            print_list(); // 리스트 출력
        }
        else if (choice == 3) {
            printf("삭제할 키워드 입력: ");
            scanf("%s", input);
            delete_keyword(input); // 키워드 삭제
        }
        else if (choice == 4) {
            printf("프로그램 종료\n");
            break; // 프로그램 종료
        }
        else {
            printf("잘못된 입력입니다.\n");
        }
    }

    // 프로그램 종료 전 메모리 정리
    KeywordNode* p = head;
    while (p != NULL) {
        KeywordNode* temp = p;
        p = p->link;
        free(temp);
    }

    return 0;
}
