#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// �Ҽ� �Ǻ� �Լ� (���)
// a�� b�� ������ �������� �Ҽ��� �ƴ� (0 ��ȯ)
// b�� 1�̸� check_1(a)�� ȣ���Ͽ� ������ ���ڰ� 1���� Ȯ��
int prime_check(int a, int b)
{
    if (b == 1) return check_1(a);  // �Ҽ� �Ǻ� �Ϸ� �� 1�� �������� Ȯ��
    else if (a % b == 0) return 0;   // ������ �������� �Ҽ��� �ƴ�
    return prime_check(a, b - 1);    // b�� �ٿ����� ��� ȣ��
}

// 1�� ������ �������� Ȯ���ϴ� �Լ�
// 1�� ������ �ش� ���ڸ� ��ȯ, �ƴϸ� 0 ��ȯ
int check_1(int num)
{
    if (num % 10 == 1) return num;
    return 0;
}

// 1���� n������ 1�� ������ �Ҽ����� ���� ���ϴ� ��� �Լ�
int calculate(int n, int t)
{
    if (n >= 2)
        t = t + prime_check(n, n - 1); // ���� n�� �Ҽ��̸鼭 1�� ������ ���ϱ�
    else
        return t; // n�� 1 ���ϰ� �Ǹ� ��� ��ȯ

    return calculate(n - 1, t); // n�� �ٿ����� ��� ȣ��
}

int main()
{
    int n, t = 0;
    int total = 0;
    printf("�Է� (2 < n < 10000): ");
    scanf("%d", &n);

    // �Է°� ����: 2���� ũ�� 10000���� ���� ���� ���
    if (n <= 2 || n >= 10000) {
        printf("(2 < n < 10000)���ǿ� ���� ����.\n");
        return 1;
    }

    // n���� �����ؼ� 1���� ��������� �˻�
    total = calculate(n, t);

    // ��� ���
    printf("%d", total);
    return 0;
}
