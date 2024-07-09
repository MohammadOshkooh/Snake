import os
import time
import random

# 0 none
# 1 body
# 2 head
# 3 apple  length+=1
# 4 healthy
# 5 block healthy-=1  default = 4
# 6 prize  5s/1min

score = 0
head = (0, 7)
tail = (0, 0)
direction = 'RIGHT'
healthy = 5
length = 8
block_count = 4
speed = 2
mode = 3 # [1, 2, 3]

snake = [(0, 0), (0, 1), (0, 2), (0, 3), (0, 4), (0, 5), (0, 6), (0, 7)]  # initial snake body

board = [
    [1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
]

width, height = 20, 10


def random_prize():
    global score, healthy, length, speed
    random_prize = random.choice([1, 2, 3])
    if random_prize == 1:
        score += 2
        score %= 99
    elif random_prize == 2:
        healthy += 2
    elif random_prize == 3:
        speed += 0.5


def check_is_alive():
    if healthy <= 0:
        print("Game Over! You lost all health.")
        exit()
    return True


def find_item(item):
    res = []
    for i in range(height):
        for j in range(width):
            if board[i][j] == item:
                res.append((i, j))
    return res


def random_remove_item(item):
    item_array = find_item(item)
    i, j = random.choice(item_array)
    board[i][j] = 0


def random_add_item(item):
    while True:
        i = random.randint(0, height - 1)
        j = random.randint(0, width - 1)
        if board[i][j] == 0:
            board[i][j] = item
            break


def display():
    os.system('cls' if os.name == 'nt' else 'clear')
    for i in range(height):
        for j in range(width):
            if board[i][j] == 0:
                print('.', end='')
            elif board[i][j] == 1:
                print('*', end='')
            elif board[i][j] == 2:
                print('#', end='')
            elif board[i][j] == 3:
                print('A', end='')
            elif board[i][j] == 4:
                print('H', end='')
            elif board[i][j] == 5:
                print('B', end='')
            elif board[i][j] == 6:
                print('P', end='')
            else:
                print(' ', end='')
        print()
    print(f'Score: {score} Healthy: {healthy}')


def action_validate(new_head):
    global healthy, length, score, head, direction
    i, j = new_head

    if board[i][j] == 5 or board[i][j] == 1 or board[i][j] == 2:
        healthy -= 1
        check_is_alive()


    elif board[i][j] == 3:
        length += 1
        score += 1
        score %= 99
        random_add_item(3)
        board[i][j] = 0

    elif board[i][j] == 4:
        healthy += 1
        random_add_item(4)
        board[i][j] = 0

    elif board[i][j] == 6:
        random_prize()


def turn_to_right():
    global direction
    if direction == 'UP':
        direction = 'RIGHT'
    elif direction == 'DOWN':
        direction = 'LEFT'
    elif direction == 'LEFT':
        direction = 'UP'
    elif direction == 'RIGHT':
        direction = 'DOWN'


def get_new_head(head):
    i, j = head

    if direction == 'UP':
        new_head = (i - 1, j)
    elif direction == 'DOWN':
        new_head = (i + 1, j)
    elif direction == 'LEFT':
        new_head = (i, j - 1)
    elif direction == 'RIGHT':
        new_head = (i, j + 1)

    return new_head


def move():
    global head, direction, length, snake, healthy, speed
    print(head)
    new_head = get_new_head(head)

    if mode in [1, 3]:
        new_head = (new_head[0] % height, new_head[1] % width)

    if mode == 2:
        if not (0 <= new_head[0] < height and 0 <= new_head[1] < width):
            healthy -= 1
            if check_is_alive():
                turn_to_right()
                new_head = get_new_head(head)

    if mode == 3:
        speed += 0.1

    action_validate(new_head)

    if board[new_head[0]][new_head[1]] == 5:  # block
        if check_is_alive():
            turn_to_right()
            new_head = get_new_head(head)

    board[head[0]][head[1]] = 1
    if board[new_head[0]][new_head[1]] != 1:
        board[new_head[0]][new_head[1]] = 2

    head = new_head

    snake.append(head)
    if len(snake) > length:
        tail = snake.pop(0)
        board[tail[0]][tail[1]] = 0

    return True


def get_input():
    global direction
    import msvcrt
    if msvcrt.kbhit():
        key = msvcrt.getch().decode('utf-8').upper()
        if key == 'W' and direction != 'DOWN':
            direction = 'UP'
        elif key == 'S' and direction != 'UP':
            direction = 'DOWN'
        elif key == 'A' and direction != 'RIGHT':
            direction = 'LEFT'
        elif key == 'D' and direction != 'LEFT':
            direction = 'RIGHT'


if __name__ == '__main__':
    for _ in range(4):
        random_add_item(5)

    random_add_item('3')
    random_add_item('4')

    while True:
        display()
        if not move():
            break
        get_input()
        time.sleep(1 / speed)

    print("Game Over!")
