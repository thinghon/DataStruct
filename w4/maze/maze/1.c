#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define MAZE_WIDTH 10
#define MAZE_HEIGHT 10

typedef struct {
    short y; // 행 (row)
    short x; // 열 (column)
} element;
typedef struct {
    element data[MAX_SIZE];
    int top;
} StackType;
void init_stack(StackType* s) {
    s->top = -1;
}
int is_empty(StackType* s) {
    return (s->top == -1);
}
int is_full(StackType* s) {
    return (s->top == MAX_SIZE - 1);
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

// 미로 배열 (3: 입구, 4: 출구, 9: 방문 표시)
int maze[MAZE_HEIGHT][MAZE_WIDTH] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 3, 1, 1, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 1, 0, 0, 1, 0, 1, 0, 1 },
    { 1, 0, 0, 1, 0, 1, 1, 1, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 0, 1, 1, 1, 0, 1, 0, 1 },
    { 1, 0, 0, 1, 4, 1, 1, 1, 0, 1 },
    { 1, 0, 1, 1, 0, 0, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 1, 1, 0, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

// 현재 위치와 입구 위치
element here = { 1, 1 };
element entry = { 1, 1 };

// 유효한 위치면 스택에 push
void push_loc(StackType* s, int y, int x) {
    if (y < 0 || x < 0 || y >= MAZE_HEIGHT || x >= MAZE_WIDTH) return;
    if (maze[y][x] == 0 || maze[y][x] == 4) {
        element tmp = { y, x };
        push(s, tmp);
    }
}

// 미로 출력 함수
void maze_print(int maze[MAZE_HEIGHT][MAZE_WIDTH]) {
    printf("\n");
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            printf("%d ", maze[y][x]);
        }
        printf("\n");
    }
}

int main(void) {
    int y, x;
    StackType s;
    init_stack(&s);
    here = entry;

    while (maze[here.y][here.x] != 4) {
        y = here.y;
        x = here.x;

        // 방문했던 위치는 9로 바꿔줌 (3이었던 이전 위치 지우기)
        if (maze[y][x] != 3) {
            maze[y][x] = 9;
        }

        // 현재 위치를 3으로 표시
        maze[here.y][here.x] = 3;

        maze_print(maze); // 미로 출력

        // 4방향 탐색
        push_loc(&s, y - 1, x);  // 위
        push_loc(&s, y + 1, x);  // 아래
        push_loc(&s, y, x - 1);  // 왼쪽
        push_loc(&s, y, x + 1);  // 오른쪽

        if (is_empty(&s)) {
            printf("헐~ 지못미\n");
            return 0;
        }
        else {
            // 현재 위치는 방문 표시 9로 변경 (다음에 덮어쓰기 전용)
            maze[here.y][here.x] = 9;
            here = pop(&s);
        }
    }

    // 출구(4)에 도달했을 때 3으로 표시 후 출력
    maze[here.y][here.x] = 3;
    maze_print(maze);
    printf("대박~\n");
    return 0;
}