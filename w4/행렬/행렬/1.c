#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ��� ����ü ����
typedef struct Matrix {
	int m;       // ��(row) ��
	int n;       // ��(column) ��
	int** arr;   // 2���� �迭(��� ������)
}Matrix;

// ��� ���� ���� �Լ�
Matrix matrix_create(int m, int n) {
	Matrix mat;
	mat.m = m;
	mat.n = n;
	mat.arr = (int**)malloc(m * sizeof(int*)); // �� ������ �迭 �Ҵ�
	for (int i = 0; i < m; i++) {
		mat.arr[i] = (int*)malloc(n * sizeof(int)); // �� ���� �� ���� �Ҵ�
	}
	return mat;
}

// ��� �Է� �Լ�
void Input(char c, Matrix* mat) {
	for (int i = 0; i < mat->m; i++) {
		for (int j = 0; j < mat->n; j++) {
			printf("%c(%d, %d)? ", c, i + 1, j + 1); // 1���� �����ϴ� ��ǥ ���
			scanf("%d", &mat->arr[i][j]);           // ����ڷκ��� �� �Է�
		}
	}
}

// ��� �޸� ���� �Լ�
void free_matrix(Matrix* mat) {
	for (int i = 0; i < mat->m; i++) {
		free(mat->arr[i]); // �� �� ����
	}
	free(mat->arr);        // �� ������ �迭 ����
}

// ��� ���� �Լ�
Matrix sum(Matrix* A, Matrix* B) {
	if (A->m == B->m && A->n == B->n) { // ��� ���� ���ƾ� ���� ����
		Matrix C = matrix_create(A->m, A->n);
		for (int i = 0; i < A->m; i++) {
			for (int j = 0; j < A->n; j++) {
				C.arr[i][j] = A->arr[i][j] + B->arr[i][j];
			}
		}
		return C;
	}
	else {
		printf("A�� B��� ������ �Ұ����մϴ�.\n");
		return matrix_create(0, 0); // ũ�Ⱑ 0�� ��� ��ȯ
	}
}

// ��� ���� �Լ�
Matrix sub(Matrix* A, Matrix* B) {
	if (A->m == B->m && A->n == B->n) { // ��� ���� ���ƾ� ���� ����
		Matrix C = matrix_create(A->m, A->n);
		for (int i = 0; i < A->m; i++) {
			for (int j = 0; j < A->n; j++) {
				C.arr[i][j] = A->arr[i][j] - B->arr[i][j];
			}
		}
		return C;
	}
	else {
		printf("A�� B��� ������ �Ұ����մϴ�.\n");
		return matrix_create(0, 0);
	}
}

// ��� ���� �Լ�
Matrix mult(Matrix* A, Matrix* B) {
	if (A->n == B->m) { // A�� �� == B�� ���̾�� ���� ����
		Matrix C = matrix_create(A->m, B->n);
		for (int i = 0; i < A->m; i++) {
			for (int j = 0; j < B->n; j++) {
				C.arr[i][j] = 0;
				for (int k = 0; k < A->n; k++) {
					C.arr[i][j] += A->arr[i][k] * B->arr[k][j]; // ���� ����
				}
			}
		}
		return C;
	}
	else {
		printf("A�� B��� ������ �Ұ����մϴ�.\n");
		return matrix_create(0, 0);
	}
}

// ��� ��� �Լ�
void print_mat(char ch, Matrix* mat) {
	printf("A %c B =\n", ch); // ���� ��ȣ ���
	for (int i = 0; i < mat->m; i++) {
		for (int j = 0; j < mat->n; j++) {
			printf("%d ", mat->arr[i][j]); // ��� ��� ���
		}
		printf("\n");
	}
	printf("\n");
}

// ���� �Լ�
int main() {
	int m, n;

	// A ��� �Է�
	printf("A�� ��� ���� �Է��ϼ���: ");
	scanf("%d %d", &m, &n);
	Matrix A = matrix_create(m, n);
	Input('A', &A);

	// B ��� �Է�
	printf("B�� ��� ���� �Է��ϼ���: ");
	scanf("%d %d", &m, &n);
	Matrix B = matrix_create(m, n);
	Input('B', &B);

	Matrix C;

	// ���� ��� ���
	C = sum(&A, &B);
	if (C.m != 0 && C.n != 0) print_mat('+', &C);

	// ���� ��� ���
	C = sub(&A, &B);
	if (C.m != 0 && C.n != 0) print_mat('-', &C);

	// ���� ��� ���
	C = mult(&A, &B);
	if (C.m != 0 && C.n != 0) print_mat('*', &C);

	// �޸� ����
	free_matrix(&A);
	free_matrix(&B);
}
