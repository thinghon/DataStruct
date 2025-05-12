#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define MAZE_WIDTH 10
#define MAZE_HEIGHT 10

typedef struct {
    short y; // �� (row)
    short x; // �� (column)
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
        fprintf(stderr, "���� ��ȭ ����\n");
        return;
    }
    s->data[++(s->top)] = item;
}
element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

// �̷� �迭 (3: �Ա�, 4: �ⱸ, 9: �湮 ǥ��)
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

// ���� ��ġ�� �Ա� ��ġ
element here = { 1, 1 };
element entry = { 1, 1 };

// ��ȿ�� ��ġ�� ���ÿ� push
void push_loc(StackType* s, int y, int x) {
    if (y < 0 || x < 0 || y >= MAZE_HEIGHT || x >= MAZE_WIDTH) return;
    if (maze[y][x] == 0 || maze[y][x] == 4) {
        element tmp = { y, x };
        push(s, tmp);
    }
}

// �̷� ��� �Լ�
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

        // �湮�ߴ� ��ġ�� 9�� �ٲ��� (3�̾��� ���� ��ġ �����)
        if (maze[y][x] != 3) {
            maze[y][x] = 9;
        }

        // ���� ��ġ�� 3���� ǥ��
        maze[here.y][here.x] = 3;

        maze_print(maze); // �̷� ���

        // 4���� Ž��
        push_loc(&s, y - 1, x);  // ��
        push_loc(&s, y + 1, x);  // �Ʒ�
        push_loc(&s, y, x - 1);  // ����
        push_loc(&s, y, x + 1);  // ������

        if (is_empty(&s)) {
            printf("��~ ������\n");
            return 0;
        }
        else {
            // ���� ��ġ�� �湮 ǥ�� 9�� ���� (������ ����� ����)
            maze[here.y][here.x] = 9;
            here = pop(&s);
        }
    }

    // �ⱸ(4)�� �������� �� 3���� ǥ�� �� ���
    maze[here.y][here.x] = 3;
    maze_print(maze);
    printf("���~\n");
    return 0;
}