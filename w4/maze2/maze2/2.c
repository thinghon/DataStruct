#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define MAZE_WIDTH 10
#define MAZE_HEIGHT 3

typedef struct {
    short y;
    short x;
} element;
typedef struct {
    element data[MAX_SIZE];
    int top;
} StackType;
void init_stack(StackType* s) { s->top = -1; }
int is_empty(StackType* s) { return (s->top == -1); }
int is_full(StackType* s) { return (s->top == MAX_SIZE - 1); }
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

int maze[MAZE_HEIGHT][MAZE_WIDTH] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 3, 0, 0, 0, 0, 0, 4, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

element here = { 1, 1 }; // 입구
element out = { 1, 7 }; // 출구

void push_loc(StackType* s, int y, int x, int from) {
    if (y < 0 || x < 0 || y >= MAZE_HEIGHT || x >= MAZE_WIDTH) return;

    if (from == 1 && (maze[y][x] == 0 || maze[y][x] == 4)) {
        element tmp = { y, x };
        push(s, tmp);
    }
    else if (from == 2 && (maze[y][x] == 0 || maze[y][x] == 3)) {
        element tmp = { y, x };
        push(s, tmp);
    }
}

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
    StackType s1, s2;
    init_stack(&s1);
    init_stack(&s2);

    element prev_here = here;
    element prev_out = out;

    while (1) {
        int y1 = here.y, x1 = here.x;
        int y2 = out.y, x2 = out.x;

        // 방문 표시
        if (maze[y1][x1] != 3) maze[y1][x1] = 9;
        if (maze[y2][x2] != 4) maze[y2][x2] = 9;

        // 현재 위치 표시
        maze[here.y][here.x] = 3;
        maze[out.y][out.x] = 4;

        maze_print(maze);

        // 입구 방향 4방향 push
        push_loc(&s1, y1 - 1, x1, 1);
        push_loc(&s1, y1 + 1, x1, 1);
        push_loc(&s1, y1, x1 - 1, 1);
        push_loc(&s1, y1, x1 + 1, 1);

        // 출구 방향 4방향 push
        push_loc(&s2, y2 - 1, x2, 2);
        push_loc(&s2, y2 + 1, x2, 2);
        push_loc(&s2, y2, x2 - 1, 2);
        push_loc(&s2, y2, x2 + 1, 2);

        if (is_empty(&s1) || is_empty(&s2)) {
            printf("헐~ 지못미\n");
            return 0;
        }

        prev_here = here;
        prev_out = out;
        here = pop(&s1);
        out = pop(&s2);

        // 서로 만났는지 검사 (같은 위치 or 교차 위치)
        if ((here.y == out.y && here.x == out.x) ||
            (here.y == prev_out.y && here.x == prev_out.x &&
                out.y == prev_here.y && out.x == prev_here.x)) {
            break;
        }

        // 방문 표시 (다음에 덮어쓰기 전용)
        maze[prev_here.y][prev_here.x] = 9;
        maze[prev_out.y][prev_out.x] = 9;
    }

    maze_print(maze);
    printf("대박~\n");

    return 0;
}
