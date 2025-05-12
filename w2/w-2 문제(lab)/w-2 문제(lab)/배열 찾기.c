#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 탐색 횟수를 기록할 변수
int count = 0;

// 이진 탐색 함수 (재귀적 구현)
int find_num(int arr[], int i, int n, int m)
{
    // 중간 인덱스 계산
    int mid = (i + n) / 2;

    // 찾는 값이 중간값과 일치하면 종료
    if (arr[mid] == m) {
        return 0;
    }
    // 찾는 값이 중간값보다 클 경우 (오른쪽 탐색)
    else if (arr[mid] < m) {
        count++;  // 탐색 횟수 증가
        find_num(arr, mid, n, m);  // 오른쪽 부분 탐색
    }
    // 찾는 값이 중간값보다 작을 경우 (왼쪽 탐색)
    else {
        count++;  // 탐색 횟수 증가
        find_num(arr, i, mid, m);  // 왼쪽 부분 탐색
    }
}

int main()
{
    int n, m;  // 배열 크기(n)와 찾고자 하는 값(m)
    // 배열 크기 입력 받기
    printf("자연수 입력:");
    scanf("%d", &n);

    // 배열 동적 할당 및 초기화
    int* arr = (int*)calloc(n, sizeof(int));

    // 배열 값 초기화 (1부터 n까지)
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // 찾고자 하는 값 입력 받기
    printf("찾고자하는 수 입력:");
    scanf("%d", &m);

    // 이진 탐색 수행
    find_num(arr, 0, n, m);
    // 탐색 횟수 출력
    printf("반복횟수:%d", count);

    // 할당된 메모리 해제
    free(arr);
}