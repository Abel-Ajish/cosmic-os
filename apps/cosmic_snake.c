#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define WIDTH 40
#define HEIGHT 20

typedef struct {
    int x, y;
} Point;

Point snake[100];
int snake_len;
Point food;
int dir_x = 1, dir_y = 0;
int score = 0;

void set_nb_input() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void draw() {
    printf("\033[H");
    printf("\033[1;36m--- 🐍 Cosmic Snake | Score: %d ---\033[0m\n", score);
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (int y = 0; y < HEIGHT; y++) {
        printf("#");
        for (int x = 0; x < WIDTH; x++) {
            int is_snake = 0;
            for (int k = 0; k < snake_len; k++) {
                if (snake[k].x == x && snake[k].y == y) {
                    is_snake = 1;
                    break;
                }
            }
            if (is_snake) printf("\033[1;32mO\033[0m");
            else if (food.x == x && food.y == y) printf("\033[1;31m*\033[0m");
            else printf(" ");
        }
        printf("#\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n\033[1;33mW/A/S/D to move, Q to quit\033[0m\n");
}

int main() {
    srand(time(NULL));
    set_nb_input();
    printf("\033[2J");

    snake_len = 3;
    snake[0] = (Point){WIDTH / 2, HEIGHT / 2};
    snake[1] = (Point){WIDTH / 2 - 1, HEIGHT / 2};
    snake[2] = (Point){WIDTH / 2 - 2, HEIGHT / 2};

    food = (Point){rand() % WIDTH, rand() % HEIGHT};

    while (1) {
        char c;
        if (read(STDIN_FILENO, &c, 1) > 0) {
            if (c == 'w' && dir_y == 0) { dir_x = 0; dir_y = -1; }
            else if (c == 's' && dir_y == 0) { dir_x = 0; dir_y = 1; }
            else if (c == 'a' && dir_x == 0) { dir_x = -1; dir_y = 0; }
            else if (c == 'd' && dir_x == 0) { dir_x = 1; dir_y = 0; }
            else if (c == 'q') break;
        }

        Point next = {snake[0].x + dir_x, snake[0].y + dir_y};

        // Collision checking
        if (next.x < 0 || next.x >= WIDTH || next.y < 0 || next.y >= HEIGHT) break;
        for (int i = 0; i < snake_len; i++) {
            if (snake[i].x == next.x && snake[i].y == next.y) goto end_game;
        }

        // Move snake
        for (int i = snake_len - 1; i > 0; i--) snake[i] = snake[i - 1];
        snake[0] = next;

        // Eat food
        if (next.x == food.x && next.y == food.y) {
            score += 10;
            snake_len++;
            food = (Point){rand() % WIDTH, rand() % HEIGHT};
        }

        draw();
        usleep(150000);
    }

end_game:
    printf("\033[2J\033[H\033[1;31mGame Over! Score: %d\033[0m\n", score);
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    return 0;
}
