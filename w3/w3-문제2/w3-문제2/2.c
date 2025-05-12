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
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    s->data[++(s->top)] = item;
}
char pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
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

// 괄호 짝이 맞는지 확인하는 함수
int match(char open, char close) {
    if (open == '(' && close == ')') return 1;
    if (open == '[' && close == ']') return 1;
    if (open == '{' && close == '}') return 1;
    return 0;
}

// 입력된 문자열이 올바른 괄호 구조인지 검사하는 함수
int check(const char* exp) {
    StackType s;
    init_stack(&s);

    char ch;
    int len = strlen(exp);

    for (int i = 0; i < len; i++) {
        ch = exp[i];

        if (ch == '(' || ch == '[' || ch == '{') {
            // 괄호 중첩 규칙 확인
            // 중괄호 '{' 안에는 대괄호 '['가 올 수 없고,
            // 소괄호 '(' 안에는 중괄호 '{'나 대괄호 '['가 올 수 없다.
            if ((ch == '{' && peek(&s) == '(') || (ch == '[' && peek(&s) == '{')) {
                return 0; // 조건 4 위반
            }
            push(&s, ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}') {
            // 닫는 괄호가 등장했을 때, 스택이 비어있다면 실패
            if (is_empty(&s)) {
                return 0;
            }
            char top = pop(&s);
            // 열린 괄호와 닫힌 괄호가 짝이 맞지 않으면 실패
            if (!match(top, ch)) {
                return 0;
            }
        }
    }
    // 모든 검사가 끝난 후 스택이 비어있다면 성공, 그렇지 않으면 실패
    return is_empty(&s);
}

int main(void) {
    char exp[MAX_STACK_SIZE];
    printf("입력: ");
    scanf("%s", exp);

    // 괄호 검사 결과 출력
    if (check(exp)) {
        printf("성공\n");
    }
    else {
        printf("실패\n");
    }

    return 0;
}
