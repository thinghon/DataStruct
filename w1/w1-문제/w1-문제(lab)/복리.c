#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>

#define MONEY 10000  // �ų� �߰��Ǵ� �⺻ �ݾ� 10,000��
#define YEAR 10      // ����� �Ⱓ(�� ��) 10��

int main()
{
    double total = 0;  // �� �ݾ��� ������ ����, �ʱⰪ�� 0
    double rate = 0;    // �������� ������ ����
    printf("������ �Է� : ");  // ����ڿ��� ������ �Է��� ��û
    scanf_s("%lf", &rate);  // ����ڷκ��� �������� �Ǽ������� �Է� ����
    rate = rate / 100;  // ������� �Էµ� �������� �Ǽ��� ��ȯ (��: 5% -> 0.05)

    // YEAR��ŭ �ݺ��ϸ鼭 �ų� MONEY�� �߰��ϰ� ���ڸ� ����
    for (int i = 0; i < YEAR; i++) {
        total = (total + MONEY) * (1 + rate);  // �ų� MONEY�� �߰��ϰ�, ����(rate)�� ����
    }
    printf("�Ѿ�: %f", total);  // ���� �Ѿ��� ���
}
