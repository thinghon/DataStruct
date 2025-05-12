#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>

#define MONEY 10000  // 매년 추가되는 기본 금액 10,000원
#define YEAR 10      // 계산할 기간(년 수) 10년

int main()
{
    double total = 0;  // 총 금액을 저장할 변수, 초기값은 0
    double rate = 0;    // 연이율을 저장할 변수
    printf("연이율 입력 : ");  // 사용자에게 연이율 입력을 요청
    scanf_s("%lf", &rate);  // 사용자로부터 연이율을 실수형으로 입력 받음
    rate = rate / 100;  // 백분율로 입력된 연이율을 실수로 변환 (예: 5% -> 0.05)

    // YEAR만큼 반복하면서 매년 MONEY를 추가하고 이자를 적용
    for (int i = 0; i < YEAR; i++) {
        total = (total + MONEY) * (1 + rate);  // 매년 MONEY를 추가하고, 이자(rate)를 적용
    }
    printf("총액: %f", total);  // 계산된 총액을 출력
}
