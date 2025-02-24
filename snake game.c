#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // For getch()
#include <stdbool.h>

#define WIDTH 20
#define HEIGHT 20
#define MAX_SNAKE_SIZE 100
#define NUM_ACTIONS 4 // Up, Down, Left, Right

typedef struct {
    int x[MAX_SNAKE_SIZE];
    int y[MAX_SNAKE_SIZE];
    int size;
} Snake;

typedef struct {
    int x;
    int y;
} Food;

typedef struct {
    float q_table[WIDTH * HEIGHT][NUM_ACTIONS]; // Q-values
    float learning_rate;
    float discount_factor;
    float exploration_rate;
} QLearningAgent;

void init_game(Snake *snake, Food *food) {
    // Initialize snake position and size
    snake->size = 1;
    snake->x[0] = WIDTH / 2;
    snake->y[0] = HEIGHT / 2;

    // Place food randomly
    food->x = rand() % WIDTH;
    food->y = rand() % HEIGHT;
}

void draw(Snake *snake, Food *food) {
    // Clear console
    system("cls");
    
    // Draw game area
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            bool printed = false;

            // Draw snake
            for (int k = 0; k < snake->size; k++) {
                if (snake->x[k] == j && snake->y[k] == i) {
                    printf("O");
                    printed = true;
                    break;
                }
            }

            // Draw food
            if (!printed && food->x == j && food->y == i) {
                printf("F");
                printed = true;
            }

            if (!printed) {
                printf(".");
            }
        }
        printf("\n");
    }
}

bool is_collision(Snake *snake) {
    // Check for collision with walls or self
    if (snake->x[0] < 0 || snake->x[0] >= WIDTH || snake->y[0] < 0 || snake->y[0] >= HEIGHT) {
        return true;
    }
    for (int i = 1; i < snake->size; i++) {
        if (snake->x[0] == snake->x[i] && snake->y[0] == snake->y[i]) {
            return true;
        }
    }
    return false;
}

void update_snake(Snake *snake, int action) {
    // Update the snake's position based on action
    for (int i = snake->size - 1; i > 0; i--) {
        snake->x[i] = snake->x[i - 1];
        snake->y[i] = snake->y[i - 1];
    }

    switch (action) {
        case 0: // Up
            snake->y[0]--;
            break;
        case 1: // Down
            snake->y[0]++;
            break;
        case 2: // Left
            snake->x[0]--;
            break;
        case 3: // Right
            snake->x[0]++;
            break;
    }
}

void train_agent(QLearningAgent *agent, Snake *snake, Food *food) {
    // Placeholder for training logic
    // Update Q-table based on actions and rewards
}

int main() {
    srand(time(NULL));
    Snake snake;
    Food food;
    QLearningAgent agent = {{0}, 0.1f, 0.9f, 1.0f}; // Example values

    init_game(&snake, &food);

    while (true) {
        draw(&snake, &food);
        
        if (is_collision(&snake)) {
            printf("Game Over!\n");
            break;
        }

        // Example of a simple input method
        if (_kbhit()) {
            char ch = _getch();
            int action = -1;

            if (ch == 'w') action = 0; // Up
            if (ch == 's') action = 1; // Down
            if (ch == 'a') action = 2; // Left
            if (ch == 'd') action = 3; // Right
            
            if (action != -1) {
                update_snake(&snake, action);
                train_agent(&agent, &snake, &food);
            }
        }
        
        // Add delay for game speed
        _sleep(100);
    }

    return 0;
}
