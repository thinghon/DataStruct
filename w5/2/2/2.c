#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 명함 정보를 저장하는 구조체
typedef struct {
	char* name;        // 이름
	char* phone_num;   // 전화번호
} Card;

// 명함을 생성하고 사용자로부터 정보를 입력받는 함수
Card create_card() {
	Card card;
	char temp[100];  // 임시 입력 버퍼

	printf("1>명함추가\n");

	// 이름 입력 및 동적 메모리 할당
	printf("이름: ");
	scanf("%s", temp);
	card.name = (char*)malloc(strlen(temp) + 1);  // 이름 저장 공간 동적 할당
	strcpy(card.name, temp);

	// 전화번호 입력 및 동적 메모리 할당
	printf("전화번호: ");
	scanf("%s", temp);
	card.phone_num = (char*)malloc(strlen(temp) + 1);  // 전화번호 저장 공간 동적 할당
	strcpy(card.phone_num, temp);

	printf("\n");
	return card;  // 명함 반환
}

// 이름으로 명함을 검색하는 함수
void search(Card* card, int n, char* c) {
	for (int i = 0; i < n; i++) {
		if (!strcmp(card[i].name, c)) {  // 이름이 일치하는 경우
			printf("-검색결과: \n");
			printf("이름: %s \n", card[i].name);
			printf("전화번호: %s \n\n", card[i].phone_num);
			return;
		}
	}
	// 일치하는 명함이 없을 경우
	printf("검색결과를 찾을 수 없습니다.\n\n");
}

// 이름으로 명함을 삭제하고 메모리를 재조정하는 함수
Card* remove_card(Card* card, int* n, char* c) {
	for (int i = 0; i < *n; i++) {
		if (!strcmp(card[i].name, c)) {  // 삭제할 명함을 찾은 경우
			// 메모리 해제
			free(card[i].name);
			free(card[i].phone_num);

			// 뒤의 명함들을 앞으로 한 칸씩 당김
			for (int j = i; j < *n - 1; j++) {
				card[j] = card[j + 1];
			}

			--(*n);  // 명함 개수 감소
			card = (Card*)realloc(card, (*n) * sizeof(Card));  // 메모리 재조정
			printf("삭제완료.\n\n");
			return card;
		}
	}
	// 일치하는 명함이 없는 경우
	printf("해당 이름은 없습니다.\n\n");
	return card;
}

// 모든 명함을 출력하는 함수
void print_card(Card* card, int n) {
	for (int i = 0; i < n; i++) {
		printf("이름: %s\n", card[i].name);
		printf("전화번호: %s\n", card[i].phone_num);
	}
	printf("\n");
}

// 메인 함수
int main() {
	int n = 0;               // 명함 개수
	int choice;              // 사용자 선택
	char name[30];           // 검색/삭제할 이름
	Card* card = NULL;       // 명함 배열 포인터

	while (1) {
		// 메뉴 출력
		printf("***명함 프로그램***\n");
		printf("추가<1> 검색<2> 삭제<3> 전체출력<4> 종료<5>: ");
		scanf("%d", &choice);

		if (choice == 1) {
			// 명함 추가
			++n;
			card = (Card*)realloc(card, n * sizeof(Card));  // 크기 증가
			card[n - 1] = create_card();  // 새 명함 추가
		}
		else if (choice == 2) {
			// 명함 검색
			printf("검색할 이름: ");
			scanf("%s", name);
			search(card, n, name);
		}
		else if (choice == 3) {
			// 명함 삭제
			printf("3>명함 삭제\n");
			printf("삭제할 이름: ");
			scanf("%s", name);
			card = remove_card(card, &n, name);
		}
		else if (choice == 4) {
			// 전체 출력
			print_card(card, n);
		}
		else if (choice == 5) {
			// 프로그램 종료
			break;
		}
		else {
			// 잘못된 메뉴 선택
			printf("해당 목록은 없습니다.\n");
		}
	}

	// 동적 메모리 해제
	for (int i = 0; i < n; i++) {
		free(card[i].name);
		free(card[i].phone_num);
	}
	free(card);

	return 0;
}
