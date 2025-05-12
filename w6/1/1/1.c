#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 노드 구조체 정의
typedef struct Node {
    char keyword[20];          // 키워드를 저장할 문자열
    int count;                 // (지금은 사용 안하지만) 검색 횟수를 저장할 정수
    struct KeywordNode* link;  // 다음 노드를 가리키는 포인터
} KeywordNode;

// 리스트 맨 앞에 새 키워드를 추가하는 함수
void insert_first(KeywordNode** head, char* keyword) {
    KeywordNode* new_node = (KeywordNode*)malloc(sizeof(KeywordNode)); // 새 노드 생성
    strcpy(new_node->keyword, keyword); // 키워드 복사
    new_node->count = 1;                // count 기본값 1로 설정 (사용 안 하지만 초기화)
    new_node->link = *head;              // 새 노드가 현재 head를 가리킴
    *head = new_node;                    // head를 새 노드로 갱신
}

void print_list(KeywordNode* node) {
    if (node == NULL) return; // 끝까지 갔으면 종료

    print_list(node->link); // 다음 노드를 먼저 재귀 호출

    if (node->link != NULL)    // 마지막 노드가 아니면 '-' 출력
        printf(" - ");
    printf("%s", node->keyword); // 키워드 출력
}

// 특정 키워드를 새로운 키워드로 수정하는 함수
void update_keyword(KeywordNode* head, char* old_keyword, char* new_keyword) {
    for (KeywordNode* p = head; p != NULL; p = p->link) { // 리스트 순회
        if (strcmp(p->keyword, old_keyword) == 0) {       // old_keyword 찾으면
            strcpy(p->keyword, new_keyword);              // 새로운 키워드로 교체
            return;
        }
    }
    printf("해당 키워드를 찾을 수 없습니다.\n"); // 못 찾으면 출력
}

// 특정 키워드를 리스트에서 삭제하는 함수
void delete_keyword(KeywordNode** head, char* keyword) {
    KeywordNode* current = *head;
    KeywordNode* prev = NULL;

    while (current != NULL) { // 리스트 순회
        if (strcmp(current->keyword, keyword) == 0) { // 삭제할 키워드 찾음
            if (prev == NULL) { // 삭제할 노드가 첫 번째 노드인 경우
                *head = current->link;
            }
            else { // 중간이나 마지막 노드인 경우
                prev->link = current->link;
            }
            free(current); // 메모리 해제
            printf("삭제 완료\n");
            return;
        }
        prev = current; // 이전 노드를 현재 노드로 이동
        current = current->link; // 현재 노드를 다음으로 이동
    }
    printf("해당 키워드를 찾을 수 없습니다.\n"); // 못 찾으면 출력
}

void print_reverse_list(KeywordNode* head) {
    KeywordNode* p = head;
    if (p == NULL) return; // 리스트가 비어있으면 아무것도 하지 않음

    printf("%s", p->keyword); // 첫 번째 노드는 '-' 없이 출력
    p = p->link;
    while (p != NULL) {       // 나머지는 '-' 붙여서 출력
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
        printf("추가 <1> 출력<2> 역순출력<3> 변경<4> 키워드삭제<5> 종료<6>: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            printf("1> 추가: ");
            scanf("%s", keyword);
            insert_first(&head, keyword);
        }
        else if (choice == 2) {
            printf("2> 출력\n");
            print_list(head);
            printf("\n");
        }
        else if (choice == 3) {
            printf("3> 역순출력\n");
            print_reverse_list(head);
        }
        else if (choice == 4) {
            printf("4> 변경\n");
            printf("변경전: ");
            scanf("%s", keyword);
            printf("변경후: ");
            scanf("%s", new_keyword);
            update_keyword(head, keyword, new_keyword);
        }
        else if (choice == 5) {
            printf("5> 키워드 삭제\n");
            printf("삭제할 키워드: ");
            scanf("%s", keyword);
            delete_keyword(&head, keyword);
        }
        else if (choice == 6) {
            break;
        }
        else {
            printf("잘못 입력했습니다.\n");
        }
    }

    while (head != NULL) {
        KeywordNode* temp = head;
        head = head->link;
        free(temp);
    }

    return 0;
}
