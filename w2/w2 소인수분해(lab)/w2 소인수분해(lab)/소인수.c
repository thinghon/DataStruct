#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// ������ ���μ��� �����ϴ� �Լ�
void integer(int n, int factors)
{
    // ���� ����: �μ��� 1�� ���
    if (factors == 1) printf("%d %d", factors, n);
    // n�� ���� �μ��� ������ �������� ���
    else if ((n % factors) == 0) {
        printf("%d ", (n / factors));  // �� ���

        // ���� �μ��� �Ҽ����� Ȯ��
        if (check_prime(factors, factors / 2)) {
            printf("%d ", factors);  // �Ҽ��� ��� ���
            return 0;  // ����
        }
        else integer(factors, factors / 2);  // �Ҽ��� �ƴϸ� ��� Ž��
    }
    else integer(n, --factors);  // �μ��� ���ҽ�Ű�� ��� ȣ��

    return 0;
}

// �Ҽ� �Ǻ� �Լ� (����� ����)
int check_prime(int prime, int i)
{
    if (i == 1) return 1;            // 1���� �����ϸ� �Ҽ�
    else if ((prime % i) == 0) return 0;  // ������ �������� �Ҽ� �ƴ�
    return check_prime(prime, --i);  // ��� Ž��
}

int main()
{
    int n;
    printf("n�� �Է��Ͻÿ�:");
    scanf("%d", &n);

    // ���μ� ���� ����
    integer(n, n / 2);
}