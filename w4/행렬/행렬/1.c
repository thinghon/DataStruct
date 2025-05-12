#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 행렬 구조체 정의
typedef struct Matrix {
	int m;       // 행(row) 수
	int n;       // 열(column) 수
	int** arr;   // 2차원 배열(행렬 데이터)
}Matrix;

// 행렬 동적 생성 함수
Matrix matrix_create(int m, int n) {
	Matrix mat;
	mat.m = m;
	mat.n = n;
	mat.arr = (int**)malloc(m * sizeof(int*)); // 행 포인터 배열 할당
	for (int i = 0; i < m; i++) {
		mat.arr[i] = (int*)malloc(n * sizeof(int)); // 각 행의 열 공간 할당
	}
	return mat;
}

// 행렬 입력 함수
void Input(char c, Matrix* mat) {
	for (int i = 0; i < mat->m; i++) {
		for (int j = 0; j < mat->n; j++) {
			printf("%c(%d, %d)? ", c, i + 1, j + 1); // 1부터 시작하는 좌표 출력
			scanf("%d", &mat->arr[i][j]);           // 사용자로부터 값 입력
		}
	}
}

// 행렬 메모리 해제 함수
void free_matrix(Matrix* mat) {
	for (int i = 0; i < mat->m; i++) {
		free(mat->arr[i]); // 각 행 해제
	}
	free(mat->arr);        // 행 포인터 배열 해제
}

// 행렬 덧셈 함수
Matrix sum(Matrix* A, Matrix* B) {
	if (A->m == B->m && A->n == B->n) { // 행과 열이 같아야 덧셈 가능
		Matrix C = matrix_create(A->m, A->n);
		for (int i = 0; i < A->m; i++) {
			for (int j = 0; j < A->n; j++) {
				C.arr[i][j] = A->arr[i][j] + B->arr[i][j];
			}
		}
		return C;
	}
	else {
		printf("A와 B행렬 덧셈이 불가능합니다.\n");
		return matrix_create(0, 0); // 크기가 0인 행렬 반환
	}
}

// 행렬 뺄셈 함수
Matrix sub(Matrix* A, Matrix* B) {
	if (A->m == B->m && A->n == B->n) { // 행과 열이 같아야 뺄셈 가능
		Matrix C = matrix_create(A->m, A->n);
		for (int i = 0; i < A->m; i++) {
			for (int j = 0; j < A->n; j++) {
				C.arr[i][j] = A->arr[i][j] - B->arr[i][j];
			}
		}
		return C;
	}
	else {
		printf("A와 B행렬 뺄셈이 불가능합니다.\n");
		return matrix_create(0, 0);
	}
}

// 행렬 곱셈 함수
Matrix mult(Matrix* A, Matrix* B) {
	if (A->n == B->m) { // A의 열 == B의 행이어야 곱셈 가능
		Matrix C = matrix_create(A->m, B->n);
		for (int i = 0; i < A->m; i++) {
			for (int j = 0; j < B->n; j++) {
				C.arr[i][j] = 0;
				for (int k = 0; k < A->n; k++) {
					C.arr[i][j] += A->arr[i][k] * B->arr[k][j]; // 내적 연산
				}
			}
		}
		return C;
	}
	else {
		printf("A와 B행렬 곱셈이 불가능합니다.\n");
		return matrix_create(0, 0);
	}
}

// 행렬 출력 함수
void print_mat(char ch, Matrix* mat) {
	printf("A %c B =\n", ch); // 연산 기호 출력
	for (int i = 0; i < mat->m; i++) {
		for (int j = 0; j < mat->n; j++) {
			printf("%d ", mat->arr[i][j]); // 행렬 요소 출력
		}
		printf("\n");
	}
	printf("\n");
}

// 메인 함수
int main() {
	int m, n;

	// A 행렬 입력
	printf("A의 행과 열을 입력하세요: ");
	scanf("%d %d", &m, &n);
	Matrix A = matrix_create(m, n);
	Input('A', &A);

	// B 행렬 입력
	printf("B의 행과 열을 입력하세요: ");
	scanf("%d %d", &m, &n);
	Matrix B = matrix_create(m, n);
	Input('B', &B);

	Matrix C;

	// 덧셈 결과 출력
	C = sum(&A, &B);
	if (C.m != 0 && C.n != 0) print_mat('+', &C);

	// 뺄셈 결과 출력
	C = sub(&A, &B);
	if (C.m != 0 && C.n != 0) print_mat('-', &C);

	// 곱셈 결과 출력
	C = mult(&A, &B);
	if (C.m != 0 && C.n != 0) print_mat('*', &C);

	// 메모리 해제
	free_matrix(&A);
	free_matrix(&B);
}
