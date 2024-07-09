# Snake Game

A simple Snake game implemented in Python. The game features different items that affect the snake's health, score, and speed. It includes three different modes of gameplay.

## Game Rules

- **Snake**: The player controls a snake that moves around the board. The snake can grow in length and collect various items to increase the score and health.
- **Board**: The board is a grid where the snake moves and interacts with items.
- **Items**:
  - `0`: Empty space.
  - `1`: Snake body.
  - `2`: Snake head.
  - `3`: Apple (increases score and length).
  - `4`: Health item (increases health).
  - `5`: Block (decreases health if collided).
  - `6`: Prize (random effect: increase score, health, or speed).

## Gameplay

- **Score**: Increases when the snake eats apples or receives a random prize. The maximum score is 99.
- **Health**: Decreases upon collision with blocks or the snake's own body. Increases by collecting health items.
- **Speed**: Increases gradually in mode 3 or when a random prize increases it.

## Controls

- `W`: Move up
- `S`: Move down
- `A`: Move left
- `D`: Move right

## Modes

- `1`: The snake can pass through the edges and appear on the opposite side.
- `2`: The snake cannot pass through the edges and will lose health upon hitting the border.
- `3`: Combination of mode 1 and gradual increase in speed.

## How to Run

1. Ensure you have Python installed on your system.
2. Save the game code in a file, e.g., `snake_game.py`.
3. Run the script using Python:
    ```sh
    python snake_game.py
    ```

## Code Explanation

### Initial Setup
The game initializes with a predefined snake body, board, and other parameters such as score, health, length, speed, and mode.

### Functions

- `random_prize()`: Adds random prize effects to score, health, or speed.
- `check_is_alive()`: Checks if the snake is still alive based on its health.
- `find_item(item)`: Finds all coordinates of a specific item on the board.
- `random_remove_item(item)`: Removes a random occurrence of a specific item.
- `random_add_item(item)`: Adds a specific item to a random empty spot on the board.
- `display()`: Clears the console and displays the current state of the board.
- `action_validate(new_head)`: Validates the action taken by the snake's new head position.
- `turn_to_right()`: Changes the snake's direction to the right.
- `get_new_head(head)`: Calculates the new head position based on the current direction.
- `move()`: Moves the snake to the new position and handles the game logic.
- `get_input()`: Captures user input for controlling the snake.

### Main Game Loop

The game runs in a loop where it continuously updates the display, moves the snake, and processes user input until the game ends.

---

Enjoy playing the Snake game!
