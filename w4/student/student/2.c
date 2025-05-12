#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 학생 정보를 저장할 구조체 정의
typedef struct Student {
	int st_num;             // 학번
	char name[20];          // 이름
	char phone_num1[15];    // 전화번호1
	char phone_num2[15];    // 전화번호2
	int* course_num;        // 수강 과목 번호 배열 (동적 할당)
} Student;

// 학번 입력 함수
int input_st_num() {
	int num;
	printf("학번을 입력하세요: ");
	scanf("%d", &num);
	return num;
}

// 이름 입력 함수
void input_name(char name[]) {
	printf("이름을 입력하세요: ");
	scanf("%s", name);
}

// 전화번호 입력 함수
void input_phone(int i, char phone_num[]) {
	printf("전화번호%d 입력하세요: ", i);
	scanf("%s", phone_num);
}

// 수강 과목 수 및 과목 번호 입력 함수
int input_course(Student* temp) {
	int num;
	printf("수강듣는 과목의 수를 입력하세요: ");
	scanf("%d", &num);

	// 수강 과목 수만큼 동적 할당
	temp->course_num = (int*)malloc(num * sizeof(int));

	// 과목 번호 입력
	for (int i = 0; i < num; i++) {
		printf("%d번 수강과목번호를 입력하세요: ", i + 1);
		scanf("%d", &temp->course_num[i]);
	}
	return num;
}

// 한 명의 학생 정보를 입력받아 Student 구조체 반환
Student student_create(int* ct) {
	Student st;
	st.st_num = input_st_num();             // 학번 입력
	input_name(st.name);                    // 이름 입력
	input_phone(1, st.phone_num1);          // 전화번호1 입력
	input_phone(2, st.phone_num2);          // 전화번호2 입력
	*ct = input_course(&st);                // 수강 과목 입력 후 과목 수 반환

	return st;
}

// 전체 학생 정보 출력 함수
void print_data(Student* data, int* count, int n) {
	int width = 74; // 테두리 너비 설정

	// 상단 테두리
	for (int i = 0; i < width; i++) printf("*");
	printf("\n");

	// 헤더 출력
	printf("* %-10s %-10s %-15s %-15s %-16s *\n",
		"학번", "이름", "전화번호1", "전화번호2", "과목");

	// 헤더 아래 테두리
	for (int i = 0; i < width; i++) printf("*");
	printf("\n");

	// 학생별 정보 출력
	for (int i = 0; i < n; i++) {
		// 기본 정보 출력
		printf("* %-10d %-10s %-15s %-15s ",
			data[i].st_num,
			data[i].name,
			data[i].phone_num1,
			data[i].phone_num2);

		// 과목 번호 출력
		for (int j = 0; j < count[i]; j++) {
			printf("%04d ", data[i].course_num[j]); // 4자리 수로 출력
		}

		// 과목이 4개 미만일 경우 빈 칸 채우기
		for (int j = count[i]; j < 4; j++) {
			printf("    ");
		}

		printf("*\n");
	}

	// 하단 테두리
	for (int i = 0; i < width; i++) printf("*");
	printf("\n");
}

// 동적 할당한 메모리 해제 함수
void free_memory(Student* data, int n) {
	for (int i = 0; i < n; i++) {
		free(data[i].course_num); // 과목 번호 배열 해제
	}
	free(data); // 학생 배열 해제
}

// 메인 함수
int main() {
	int n;
	int* count; // 학생별 수강 과목 수를 저장할 배열

	printf("입력받을 학생의 수를 입력하세요: ");
	scanf("%d", &n);

	// 동적 메모리 할당
	Student* data = (Student*)malloc(n * sizeof(Student));
	count = (int*)malloc(n * sizeof(int));

	// 각 학생 정보 입력
	for (int i = 0; i < n; i++) {
		data[i] = student_create(&count[i]);
	}

	// 학생 정보 출력
	print_data(data, count, n);

	// 메모리 해제
	free_memory(data, n);
	free(count);
	return 0;
}
