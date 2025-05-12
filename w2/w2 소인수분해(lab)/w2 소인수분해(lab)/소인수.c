#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 정수를 소인수로 분해하는 함수
void integer(int n, int factors)
{
    // 종료 조건: 인수가 1일 경우
    if (factors == 1) printf("%d %d", factors, n);
    // n이 현재 인수로 나누어 떨어지는 경우
    else if ((n % factors) == 0) {
        printf("%d ", (n / factors));  // 몫 출력

        // 현재 인수가 소수인지 확인
        if (check_prime(factors, factors / 2)) {
            printf("%d ", factors);  // 소수인 경우 출력
            return 0;  // 종료
        }
        else integer(factors, factors / 2);  // 소수가 아니면 계속 탐색
    }
    else integer(n, --factors);  // 인수를 감소시키며 재귀 호출

    return 0;
}

// 소수 판별 함수 (재귀적 구현)
int check_prime(int prime, int i)
{
    if (i == 1) return 1;            // 1까지 도달하면 소수
    else if ((prime % i) == 0) return 0;  // 나누어 떨어지면 소수 아님
    return check_prime(prime, --i);  // 계속 탐색
}

int main()
{
    int n;
    printf("n을 입력하시오:");
    scanf("%d", &n);

    // 소인수 분해 시작
    integer(n, n / 2);
}