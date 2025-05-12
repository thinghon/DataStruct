#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_STACK_SIZE 100

// 스택 구조체 정의
typedef char element;
typedef struct {
    element data[MAX_STACK_SIZE];
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
void push(StackType* s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    s->data[++(s->top)] = item;
}
element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    return s->data[(s->top)--];
}
element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    return s->data[s->top];
}

// 연산자의 우선순위를 반환하는 함수
int prec(char op) {
    switch (op) {
    case '(': case ')':
    case '{': case '}':
    case '[': case ']': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    }
    return -1;
}

// 스택에서 숫자를 조합하여 정수로 변환하는 함수
int num_combine(StackType* s) {
    int value, num = 0;
    char num_buffer[MAX_STACK_SIZE];
    int k = 0;
    if (peek(s) == ' ') {
        pop(s);
    }
    while (!is_empty(s) && peek(s) != ' ') {
        num_buffer[k++] = pop(s);
    }
    num_buffer[k] = '\0';
    int digit = strlen(num_buffer) - 1;
    for (int i = strlen(num_buffer); i > 0; i--) {
        value = num_buffer[i - 1] - '0';
        num = (pow(10, digit--) * value) + num;
    }
    return num;
}

// 후위표기법 수식을 계산하는 함수
int cal(char arr[]) {
    StackType s;
    init_stack(&s);

    char ch;
    char result_str[MAX_STACK_SIZE];
    int op1, op2;
    int len = strlen(arr);

    for (int i = 0; i < len; i++) {
        ch = arr[i];
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
            if (ch != ' ') {
                push(&s, ch);
            }
            else {
                push(&s, ch);
            }
        }
        else {
            op2 = num_combine(&s);
            op1 = num_combine(&s);

            int result;
            switch (ch) {
            case '+': result = op1 + op2; break;
            case '-': result = op1 - op2; break;
            case '*': result = op1 * op2; break;
            case '/': result = op1 / op2; break;
            }

            sprintf(result_str, "%d", result);
            for (int j = 0; result_str[j] != '\0'; j++) {
                push(&s, result_str[j]);
            }
        }
    }
    return num_combine(&s);
}

// 중위표기법을 후위표기법으로 변환하는 함수
void postfix_notation(char exp[], char postfix[]) {
    StackType s;
    init_stack(&s);
    char ch;
    int len = strlen(exp);
    int idx = 0;
    char num_buffer[MAX_STACK_SIZE];
    int num_idx = 0;

    for (int i = 0; i < len; i++) {
        ch = exp[i];

        if (ch >= '0' && ch <= '9') {
            num_buffer[num_idx++] = ch;
        }
        else {
            if (num_idx > 0) {
                num_buffer[num_idx] = '\0';
                for (int j = 0; num_buffer[j] != '\0'; j++) {
                    postfix[idx++] = num_buffer[j];
                }
                postfix[idx++] = ' ';
                num_idx = 0;
            }

            switch (ch) {
            case '+': case '-': case '*': case '/':
                while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) {
                    postfix[idx++] = pop(&s);
                    postfix[idx++] = ' ';
                }
                push(&s, ch);
                break;
            case '(': case '{': case '[':
                push(&s, ch);
                break;
            case ')': case '}': case ']':
                while (!is_empty(&s)) {
                    char top_op = pop(&s);
                    if ((ch == ')' && top_op == '(') ||
                        (ch == '}' && top_op == '{') ||
                        (ch == ']' && top_op == '[')) {
                        break;
                    }
                    postfix[idx++] = top_op;
                    postfix[idx++] = ' ';
                }
                break;
            }
        }
    }

    if (num_idx > 0) {
        num_buffer[num_idx] = '\0';
        for (int j = 0; num_buffer[j] != '\0'; j++) {
            postfix[idx++] = num_buffer[j];
        }
        postfix[idx++] = ' ';
    }

    while (!is_empty(&s)) {
        postfix[idx++] = pop(&s);
        postfix[idx++] = ' ';
    }

    postfix[idx] = '\0';
}

int main(void) {
    char s[MAX_STACK_SIZE];
    printf("입력: ");
    scanf("%s", s);
    char postfix[MAX_STACK_SIZE];
    printf("중위표시수식: %s \n", s);
    postfix_notation(s, postfix);
    int result = cal(postfix);
    printf("후위표시수식: %s\n", postfix);
    printf("결과: %d\n", result);
    return 0;
}