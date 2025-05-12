#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100  

typedef struct {
    char data[MAX_STACK_SIZE];
    int top;
} StackType;
void init_stack(StackType* s) {
    s->top = -1;
}
int is_empty(StackType* s) {
    return (s->top == -1);
}
int is_full(StackType* s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}
void push(StackType* s, char item) {
    if (is_full(s)) {
        fprintf(stderr, "���� ��ȭ ����\n");
        return;
    }
    s->data[++(s->top)] = item;
}
char pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    return s->data[(s->top)--];
}
char peek(StackType* s) {
    if (is_empty(s)) {
        return '\0';
    }
    return s->data[s->top];
}

// ��ȣ ¦�� �´��� Ȯ���ϴ� �Լ�
int match(char open, char close) {
    if (open == '(' && close == ')') return 1;
    if (open == '[' && close == ']') return 1;
    if (open == '{' && close == '}') return 1;
    return 0;
}

// �Էµ� ���ڿ��� �ùٸ� ��ȣ �������� �˻��ϴ� �Լ�
int check(const char* exp) {
    StackType s;
    init_stack(&s);

    char ch;
    int len = strlen(exp);

    for (int i = 0; i < len; i++) {
        ch = exp[i];

        if (ch == '(' || ch == '[' || ch == '{') {
            // ��ȣ ��ø ��Ģ Ȯ��
            // �߰�ȣ '{' �ȿ��� ���ȣ '['�� �� �� ����,
            // �Ұ�ȣ '(' �ȿ��� �߰�ȣ '{'�� ���ȣ '['�� �� �� ����.
            if ((ch == '{' && peek(&s) == '(') || (ch == '[' && peek(&s) == '{')) {
                return 0; // ���� 4 ����
            }
            push(&s, ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}') {
            // �ݴ� ��ȣ�� �������� ��, ������ ����ִٸ� ����
            if (is_empty(&s)) {
                return 0;
            }
            char top = pop(&s);
            // ���� ��ȣ�� ���� ��ȣ�� ¦�� ���� ������ ����
            if (!match(top, ch)) {
                return 0;
            }
        }
    }
    // ��� �˻簡 ���� �� ������ ����ִٸ� ����, �׷��� ������ ����
    return is_empty(&s);
}

int main(void) {
    char exp[MAX_STACK_SIZE];
    printf("�Է�: ");
    scanf("%s", exp);

    // ��ȣ �˻� ��� ���
    if (check(exp)) {
        printf("����\n");
    }
    else {
        printf("����\n");
    }

    return 0;
}
