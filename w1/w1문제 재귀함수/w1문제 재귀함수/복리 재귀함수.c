#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

// ��� ����
#define MONEY 10000  // �ų� �߰��Ǵ� �⺻ �ݾ� 10,000��
#define YEAR 10      // ����� �Ⱓ(�� ��) 10��

// ��� �Լ��� ���� ���
void calculate(int y, double r, double t)
{
    if (y == 0) {
        // ��� ���� �� �Ѿ� ���
        printf("�Ѿ�: %f", t);
    }
    else {
        // �ų� MONEY�� �߰��ϰ�, ����(rate)�� ����
        t = (t + MONEY) * (1 + r);
        // ��� ȣ��� ���� �ط� �Ѿ
        calculate(y - 1, r, t);
    }
}

int main()
{
    double total = 0;  // �� �ݾ� (�ʱⰪ 0)
    double rate = 0;    // ������ (�ʱⰪ 0)

    // ������ �Է� �ޱ�
    printf("������ �Է� : ");
    scanf("%lf", &rate);  // ����ڷκ��� ������ �Է� �ޱ�

    // ������� �Էµ� �������� �Ǽ��� ��ȯ (��: 5% -> 0.05)
    rate = rate / 100;

    // ���� ����� ���� ��� �Լ� ȣ��
    calculate(YEAR, rate, total);  // YEAR(10��) ������ ���� ��� ����

    return 0;
}
