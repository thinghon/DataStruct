#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���� ������ �����ϴ� ����ü
typedef struct {
	char* name;        // �̸�
	char* phone_num;   // ��ȭ��ȣ
} Card;

// ������ �����ϰ� ����ڷκ��� ������ �Է¹޴� �Լ�
Card create_card() {
	Card card;
	char temp[100];  // �ӽ� �Է� ����

	printf("1>�����߰�\n");

	// �̸� �Է� �� ���� �޸� �Ҵ�
	printf("�̸�: ");
	scanf("%s", temp);
	card.name = (char*)malloc(strlen(temp) + 1);  // �̸� ���� ���� ���� �Ҵ�
	strcpy(card.name, temp);

	// ��ȭ��ȣ �Է� �� ���� �޸� �Ҵ�
	printf("��ȭ��ȣ: ");
	scanf("%s", temp);
	card.phone_num = (char*)malloc(strlen(temp) + 1);  // ��ȭ��ȣ ���� ���� ���� �Ҵ�
	strcpy(card.phone_num, temp);

	printf("\n");
	return card;  // ���� ��ȯ
}

// �̸����� ������ �˻��ϴ� �Լ�
void search(Card* card, int n, char* c) {
	for (int i = 0; i < n; i++) {
		if (!strcmp(card[i].name, c)) {  // �̸��� ��ġ�ϴ� ���
			printf("-�˻����: \n");
			printf("�̸�: %s \n", card[i].name);
			printf("��ȭ��ȣ: %s \n\n", card[i].phone_num);
			return;
		}
	}
	// ��ġ�ϴ� ������ ���� ���
	printf("�˻������ ã�� �� �����ϴ�.\n\n");
}

// �̸����� ������ �����ϰ� �޸𸮸� �������ϴ� �Լ�
Card* remove_card(Card* card, int* n, char* c) {
	for (int i = 0; i < *n; i++) {
		if (!strcmp(card[i].name, c)) {  // ������ ������ ã�� ���
			// �޸� ����
			free(card[i].name);
			free(card[i].phone_num);

			// ���� ���Ե��� ������ �� ĭ�� ���
			for (int j = i; j < *n - 1; j++) {
				card[j] = card[j + 1];
			}

			--(*n);  // ���� ���� ����
			card = (Card*)realloc(card, (*n) * sizeof(Card));  // �޸� ������
			printf("�����Ϸ�.\n\n");
			return card;
		}
	}
	// ��ġ�ϴ� ������ ���� ���
	printf("�ش� �̸��� �����ϴ�.\n\n");
	return card;
}

// ��� ������ ����ϴ� �Լ�
void print_card(Card* card, int n) {
	for (int i = 0; i < n; i++) {
		printf("�̸�: %s\n", card[i].name);
		printf("��ȭ��ȣ: %s\n", card[i].phone_num);
	}
	printf("\n");
}

// ���� �Լ�
int main() {
	int n = 0;               // ���� ����
	int choice;              // ����� ����
	char name[30];           // �˻�/������ �̸�
	Card* card = NULL;       // ���� �迭 ������

	while (1) {
		// �޴� ���
		printf("***���� ���α׷�***\n");
		printf("�߰�<1> �˻�<2> ����<3> ��ü���<4> ����<5>: ");
		scanf("%d", &choice);

		if (choice == 1) {
			// ���� �߰�
			++n;
			card = (Card*)realloc(card, n * sizeof(Card));  // ũ�� ����
			card[n - 1] = create_card();  // �� ���� �߰�
		}
		else if (choice == 2) {
			// ���� �˻�
			printf("�˻��� �̸�: ");
			scanf("%s", name);
			search(card, n, name);
		}
		else if (choice == 3) {
			// ���� ����
			printf("3>���� ����\n");
			printf("������ �̸�: ");
			scanf("%s", name);
			card = remove_card(card, &n, name);
		}
		else if (choice == 4) {
			// ��ü ���
			print_card(card, n);
		}
		else if (choice == 5) {
			// ���α׷� ����
			break;
		}
		else {
			// �߸��� �޴� ����
			printf("�ش� ����� �����ϴ�.\n");
		}
	}

	// ���� �޸� ����
	for (int i = 0; i < n; i++) {
		free(card[i].name);
		free(card[i].phone_num);
	}
	free(card);

	return 0;
}
