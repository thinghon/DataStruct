#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 소수 판별 함수 (재귀)
// a가 b로 나누어 떨어지면 소수가 아님 (0 반환)
// b가 1이면 check_1(a)를 호출하여 마지막 숫자가 1인지 확인
int prime_check(int a, int b)
{
    if (b == 1) return check_1(a);  // 소수 판별 완료 후 1로 끝나는지 확인
    else if (a % b == 0) return 0;   // 나누어 떨어지면 소수가 아님
    return prime_check(a, b - 1);    // b를 줄여가며 재귀 호출
}

// 1로 끝나는 숫자인지 확인하는 함수
// 1로 끝나면 해당 숫자를 반환, 아니면 0 반환
int check_1(int num)
{
    if (num % 10 == 1) return num;
    return 0;
}

// 1부터 n까지의 1로 끝나는 소수들의 합을 구하는 재귀 함수
int calculate(int n, int t)
{
    if (n >= 2)
        t = t + prime_check(n, n - 1); // 현재 n이 소수이면서 1로 끝나면 더하기
    else
        return t; // n이 1 이하가 되면 결과 반환

    return calculate(n - 1, t); // n을 줄여가며 재귀 호출
}

int main()
{
    int n, t = 0;
    int total = 0;
    printf("입력 (2 < n < 10000): ");
    scanf("%d", &n);

    // 입력값 검증: 2보다 크고 10000보다 작은 값만 허용
    if (n <= 2 || n >= 10000) {
        printf("(2 < n < 10000)조건에 맞지 않음.\n");
        return 1;
    }

    // n부터 시작해서 1까지 재귀적으로 검사
    total = calculate(n, t);

    // 결과 출력
    printf("%d", total);
    return 0;
}
