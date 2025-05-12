#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Ž�� Ƚ���� ����� ����
int count = 0;

// ���� Ž�� �Լ� (����� ����)
int find_num(int arr[], int i, int n, int m)
{
    // �߰� �ε��� ���
    int mid = (i + n) / 2;

    // ã�� ���� �߰����� ��ġ�ϸ� ����
    if (arr[mid] == m) {
        return 0;
    }
    // ã�� ���� �߰������� Ŭ ��� (������ Ž��)
    else if (arr[mid] < m) {
        count++;  // Ž�� Ƚ�� ����
        find_num(arr, mid, n, m);  // ������ �κ� Ž��
    }
    // ã�� ���� �߰������� ���� ��� (���� Ž��)
    else {
        count++;  // Ž�� Ƚ�� ����
        find_num(arr, i, mid, m);  // ���� �κ� Ž��
    }
}

int main()
{
    int n, m;  // �迭 ũ��(n)�� ã���� �ϴ� ��(m)
    // �迭 ũ�� �Է� �ޱ�
    printf("�ڿ��� �Է�:");
    scanf("%d", &n);

    // �迭 ���� �Ҵ� �� �ʱ�ȭ
    int* arr = (int*)calloc(n, sizeof(int));

    // �迭 �� �ʱ�ȭ (1���� n����)
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // ã���� �ϴ� �� �Է� �ޱ�
    printf("ã�����ϴ� �� �Է�:");
    scanf("%d", &m);

    // ���� Ž�� ����
    find_num(arr, 0, n, m);
    // Ž�� Ƚ�� ���
    printf("�ݺ�Ƚ��:%d", count);

    // �Ҵ�� �޸� ����
    free(arr);
}