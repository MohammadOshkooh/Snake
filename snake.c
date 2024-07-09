#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include  <conio.h>

/*
# 0 none
# 1 body
# 2 head
# 3 apple  length+=1
# 4 healthy
# 5 block healthy-=1  default = 4
# 6 prize  5s/1min
*/



typedef struct {
    int i;
    int j;
} Position;

typedef enum {
    NONE = 0,
    BODY=1,
    HEAD=2,
    APPLE=3,
    HEALTHY=4,
    BLOCK=5,
    PRIZE=6
} CellType;


int score = 0;
Position head= {0, 7};
Position tail = {0, 0};
int healthy = 5;
int length = 8;
int block_count = 4;
float speed = 1;
int mode = 2; // Modes: [1, 2, 3]
char direction = 'R'; // 'U', 'D', 'L', 'R'
#define HEIGHT 10
#define WIDTH 20

Position snake[100] = {
    {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}
};

int board[HEIGHT][WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void random_prize() {
    int r = rand() % 3;
    if (r == 0) {
        score += 2;
        score %= 99;
    } else if (r == 1) {
        healthy += 2;
    } else if (r == 2) {
        speed += 0.005*2;
    }
}

void display() {
    system("cls");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] == NONE) printf(".");
            else if (board[i][j] == BODY) printf("*");
            else if (board[i][j] == HEAD) printf("#");
            else if (board[i][j] == APPLE) printf("A");
            else if (board[i][j] == HEALTHY) printf("H");
            else if (board[i][j] == BLOCK) printf("B");
            else if (board[i][j] == PRIZE) printf("P");
        }
        printf("\n");
    }
    printf("Score: %d Healthy: %d\n", score, healthy);
}

int check_is_alive() {
    if (healthy <= 0) {
        display();
        printf("Game Over! You lost all health.\n");
        exit(0);
    }
    return 1;
}

Position get_new_head() {
    Position new_head = head;
    if (direction == 'U') new_head.i--;
    else if (direction == 'D') new_head.i++;
    else if (direction == 'L') new_head.j--;
    else if (direction == 'R') new_head.j++;
    return new_head;
}


void random_add_item(CellType item) {
    int i, j;
    do {
        i = rand() % HEIGHT;
        j = rand() % WIDTH;
    } while (board[i][j] != NONE);
    board[i][j] = item;
}


void action_validate(Position new_head) {
    int i = new_head.i;
    int j = new_head.j;

    if (board[i][j] == BLOCK || board[i][j] == BODY || board[i][j] == HEAD) {
        healthy--;
        check_is_alive();
    } else if (board[i][j] == APPLE) {
        length++;
        score++;
        score %= 99;
        random_add_item(APPLE);
        board[i][j] = NONE;
    } else if (board[i][j] == HEALTHY) {
        healthy++;
        random_add_item(HEALTHY);
        board[i][j] = NONE;
    } else if (board[i][j] == PRIZE) {
        random_prize();
    }
}


void turn_to_right(){
    direction = (direction == 'U') ? 'R' : (direction == 'D') ? 'L' : (direction == 'L') ? 'U' : 'D';
}

void move() {
    printf("i:%d j:%d  len:%d speed:%f\n", head.i, head.j, length, speed);
    Position new_head = get_new_head(head);

    if (mode == 1 || mode == 3) {
        new_head.i = new_head.i % HEIGHT;
        new_head.j = new_head.j % WIDTH;
    } else if (mode == 2) {
        if (!(0 <= new_head.i && new_head.i < HEIGHT && 0 <= new_head.j && new_head.j < WIDTH)) {
            healthy--;
            if (check_is_alive()) {
                turn_to_right();
                new_head = get_new_head();
            }
        }
    }

    if (mode == 3) {
        speed += 0.01;
    }

    action_validate(new_head);

    if (board[new_head.i][new_head.j] == BLOCK) {
        if (check_is_alive()) {
            turn_to_right();
            new_head = get_new_head();
        }
    }

    board[head.i][head.j] = BODY;
    if (board[new_head.i][new_head.j] != BODY) {
        board[new_head.i][new_head.j] = HEAD;
    }

    head = new_head;

    snake[length] = head;

        // pop tail
        tail = snake[0];
        for (int i = 0; i < length; i++) {
            snake[i] = snake[i + 1];
        }
        board[tail.i][tail.j] = NONE;
}

void get_input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'w' && direction != 'D') direction = 'U';
        else if (key == 's' && direction != 'U') direction = 'D';
        else if (key == 'a' && direction != 'R') direction = 'L';
        else if (key == 'd' && direction != 'L') direction = 'R';
    }
}


int main() {
    srand(time(NULL));

    for (int i = 0; i < 4; i++) random_add_item(BLOCK);
    random_add_item(APPLE);
    random_add_item(HEALTHY);

    while (1) {
        display();
        move();
        get_input();
        sleep(1.5/speed);
    }

    return 0;
}
