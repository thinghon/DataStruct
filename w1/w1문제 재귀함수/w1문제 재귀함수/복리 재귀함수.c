#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

// 상수 정의
#define MONEY 10000  // 매년 추가되는 기본 금액 10,000원
#define YEAR 10      // 계산할 기간(년 수) 10년

// 재귀 함수로 복리 계산
void calculate(int y, double r, double t)
{
    if (y == 0) {
        // 재귀 종료 시 총액 출력
        printf("총액: %f", t);
    }
    else {
        // 매년 MONEY를 추가하고, 이자(rate)를 적용
        t = (t + MONEY) * (1 + r);
        // 재귀 호출로 다음 해로 넘어감
        calculate(y - 1, r, t);
    }
}

int main()
{
    double total = 0;  // 총 금액 (초기값 0)
    double rate = 0;    // 연이율 (초기값 0)

    // 연이율 입력 받기
    printf("연이율 입력 : ");
    scanf("%lf", &rate);  // 사용자로부터 연이율 입력 받기

    // 백분율로 입력된 연이율을 실수로 변환 (예: 5% -> 0.05)
    rate = rate / 100;

    // 복리 계산을 위한 재귀 함수 호출
    calculate(YEAR, rate, total);  // YEAR(10년) 동안의 복리 계산 시작

    return 0;
}
