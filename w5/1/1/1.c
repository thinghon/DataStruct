#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>

// 책의 위치 정보를 담는 구조체
typedef struct {
	char floor;  // 층수
	char room;   // 열람실 번호
	char shelf;  // 책장 번호
} BookLoc;

// 책 정보를 담는 구조체
typedef struct {
	char title[30];     // 제목
	char author[30];    // 저자
	char ISBN[20];      // ISBN 코드
	short page;         // 페이지 수
	BookLoc loc;        // 책 위치 정보
} Book;

// 책 정보를 입력받는 함수
void input(Book* books, int n) {
	char st[30];  // 임시 입력 버퍼

	// 제목, 저자, ISBN 입력
	printf("%d번 책의 제목을 입력하시오? ", n + 1);
	gets(books[n].title);
	printf("%d번 책의 저자를 입력하시오? ", n + 1);
	gets(books[n].author);
	printf("%d번 책의 ISBN코드를 입력하시오? ", n + 1);
	gets(books[n].ISBN);

	// 페이지 수 입력
	printf("%d번 책의 페이지 수를 입력하시오? ", n + 1);
	scanf("%d", &books[n].page);

	// 위치 정보 입력
	printf("책의 위치를 입력하시오\n");
	printf("층수를 입력하시오? ");
	scanf("%s", &books[n].loc.floor);
	printf("열람실번호를 입력하시오? ");
	scanf("%s", &books[n].loc.room);
	printf("책장번호를 입력하시오? ");
	scanf("%s", &books[n].loc.shelf);

	getchar();  // 입력 버퍼에 남아 있는 개행 문자 제거
}

// 책 정보를 출력하는 함수
void output(Book* books, int n) {
	// 헤더 출력
	printf("********************************************************************************\n");
	printf("%-16s %-16s %-16s %-9s %-5s %-8s %-5s\n",
		"제목", "저자", "ISBN", "페이지수", "층수", "열람실", "책장");
	printf("********************************************************************************\n");

	// 각 책의 정보 출력
	for (int i = 0; i < n; i++) {
		printf("%-16s %-16s %-16s %-10d %-5d %-8d %-5d\n",
			books[i].title,
			books[i].author,
			books[i].ISBN,
			books[i].page,
			books[i].loc.floor,
			books[i].loc.room,
			books[i].loc.shelf
		);
	}
}

int main() {
	Book* book;  // Book 구조체 포인터
	int n;       // 책의 수

	// 책의 수 입력
	printf("입력 받을 책의 수를 입력하시오? ");
	scanf("%d", &n);
	getchar();  // 버퍼 비우기

	// 동적 메모리 할당
	book = (Book*)malloc(n * sizeof(Book));

	// 각 책 정보 입력
	for (int i = 0; i < n; i++) {
		input(book, i);
	}

	// 전체 책 정보 출력
	output(book, n);

	// 메모리 해제
	free(book);
}
