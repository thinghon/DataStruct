#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>

// å�� ��ġ ������ ��� ����ü
typedef struct {
	char floor;  // ����
	char room;   // ������ ��ȣ
	char shelf;  // å�� ��ȣ
} BookLoc;

// å ������ ��� ����ü
typedef struct {
	char title[30];     // ����
	char author[30];    // ����
	char ISBN[20];      // ISBN �ڵ�
	short page;         // ������ ��
	BookLoc loc;        // å ��ġ ����
} Book;

// å ������ �Է¹޴� �Լ�
void input(Book* books, int n) {
	char st[30];  // �ӽ� �Է� ����

	// ����, ����, ISBN �Է�
	printf("%d�� å�� ������ �Է��Ͻÿ�? ", n + 1);
	gets(books[n].title);
	printf("%d�� å�� ���ڸ� �Է��Ͻÿ�? ", n + 1);
	gets(books[n].author);
	printf("%d�� å�� ISBN�ڵ带 �Է��Ͻÿ�? ", n + 1);
	gets(books[n].ISBN);

	// ������ �� �Է�
	printf("%d�� å�� ������ ���� �Է��Ͻÿ�? ", n + 1);
	scanf("%d", &books[n].page);

	// ��ġ ���� �Է�
	printf("å�� ��ġ�� �Է��Ͻÿ�\n");
	printf("������ �Է��Ͻÿ�? ");
	scanf("%s", &books[n].loc.floor);
	printf("�����ǹ�ȣ�� �Է��Ͻÿ�? ");
	scanf("%s", &books[n].loc.room);
	printf("å���ȣ�� �Է��Ͻÿ�? ");
	scanf("%s", &books[n].loc.shelf);

	getchar();  // �Է� ���ۿ� ���� �ִ� ���� ���� ����
}

// å ������ ����ϴ� �Լ�
void output(Book* books, int n) {
	// ��� ���
	printf("********************************************************************************\n");
	printf("%-16s %-16s %-16s %-9s %-5s %-8s %-5s\n",
		"����", "����", "ISBN", "��������", "����", "������", "å��");
	printf("********************************************************************************\n");

	// �� å�� ���� ���
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
	Book* book;  // Book ����ü ������
	int n;       // å�� ��

	// å�� �� �Է�
	printf("�Է� ���� å�� ���� �Է��Ͻÿ�? ");
	scanf("%d", &n);
	getchar();  // ���� ����

	// ���� �޸� �Ҵ�
	book = (Book*)malloc(n * sizeof(Book));

	// �� å ���� �Է�
	for (int i = 0; i < n; i++) {
		input(book, i);
	}

	// ��ü å ���� ���
	output(book, n);

	// �޸� ����
	free(book);
}
