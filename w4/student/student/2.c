#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// �л� ������ ������ ����ü ����
typedef struct Student {
	int st_num;             // �й�
	char name[20];          // �̸�
	char phone_num1[15];    // ��ȭ��ȣ1
	char phone_num2[15];    // ��ȭ��ȣ2
	int* course_num;        // ���� ���� ��ȣ �迭 (���� �Ҵ�)
} Student;

// �й� �Է� �Լ�
int input_st_num() {
	int num;
	printf("�й��� �Է��ϼ���: ");
	scanf("%d", &num);
	return num;
}

// �̸� �Է� �Լ�
void input_name(char name[]) {
	printf("�̸��� �Է��ϼ���: ");
	scanf("%s", name);
}

// ��ȭ��ȣ �Է� �Լ�
void input_phone(int i, char phone_num[]) {
	printf("��ȭ��ȣ%d �Է��ϼ���: ", i);
	scanf("%s", phone_num);
}

// ���� ���� �� �� ���� ��ȣ �Է� �Լ�
int input_course(Student* temp) {
	int num;
	printf("������� ������ ���� �Է��ϼ���: ");
	scanf("%d", &num);

	// ���� ���� ����ŭ ���� �Ҵ�
	temp->course_num = (int*)malloc(num * sizeof(int));

	// ���� ��ȣ �Է�
	for (int i = 0; i < num; i++) {
		printf("%d�� ���������ȣ�� �Է��ϼ���: ", i + 1);
		scanf("%d", &temp->course_num[i]);
	}
	return num;
}

// �� ���� �л� ������ �Է¹޾� Student ����ü ��ȯ
Student student_create(int* ct) {
	Student st;
	st.st_num = input_st_num();             // �й� �Է�
	input_name(st.name);                    // �̸� �Է�
	input_phone(1, st.phone_num1);          // ��ȭ��ȣ1 �Է�
	input_phone(2, st.phone_num2);          // ��ȭ��ȣ2 �Է�
	*ct = input_course(&st);                // ���� ���� �Է� �� ���� �� ��ȯ

	return st;
}

// ��ü �л� ���� ��� �Լ�
void print_data(Student* data, int* count, int n) {
	int width = 74; // �׵θ� �ʺ� ����

	// ��� �׵θ�
	for (int i = 0; i < width; i++) printf("*");
	printf("\n");

	// ��� ���
	printf("* %-10s %-10s %-15s %-15s %-16s *\n",
		"�й�", "�̸�", "��ȭ��ȣ1", "��ȭ��ȣ2", "����");

	// ��� �Ʒ� �׵θ�
	for (int i = 0; i < width; i++) printf("*");
	printf("\n");

	// �л��� ���� ���
	for (int i = 0; i < n; i++) {
		// �⺻ ���� ���
		printf("* %-10d %-10s %-15s %-15s ",
			data[i].st_num,
			data[i].name,
			data[i].phone_num1,
			data[i].phone_num2);

		// ���� ��ȣ ���
		for (int j = 0; j < count[i]; j++) {
			printf("%04d ", data[i].course_num[j]); // 4�ڸ� ���� ���
		}

		// ������ 4�� �̸��� ��� �� ĭ ä���
		for (int j = count[i]; j < 4; j++) {
			printf("    ");
		}

		printf("*\n");
	}

	// �ϴ� �׵θ�
	for (int i = 0; i < width; i++) printf("*");
	printf("\n");
}

// ���� �Ҵ��� �޸� ���� �Լ�
void free_memory(Student* data, int n) {
	for (int i = 0; i < n; i++) {
		free(data[i].course_num); // ���� ��ȣ �迭 ����
	}
	free(data); // �л� �迭 ����
}

// ���� �Լ�
int main() {
	int n;
	int* count; // �л��� ���� ���� ���� ������ �迭

	printf("�Է¹��� �л��� ���� �Է��ϼ���: ");
	scanf("%d", &n);

	// ���� �޸� �Ҵ�
	Student* data = (Student*)malloc(n * sizeof(Student));
	count = (int*)malloc(n * sizeof(int));

	// �� �л� ���� �Է�
	for (int i = 0; i < n; i++) {
		data[i] = student_create(&count[i]);
	}

	// �л� ���� ���
	print_data(data, count, n);

	// �޸� ����
	free_memory(data, n);
	free(count);
	return 0;
}
