#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX_BUFFER 64

// Hardcoded users for now (Educational simplicity)
typedef struct {
    char *username;
    char *password;
} User;

User users[] = {
    {"cosmic", "space"},
    {"root", "admin"}
};

void set_echo(int enable) {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    if (enable) t.c_lflag |= ECHO;
    else t.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int main() {
    char username[MAX_BUFFER];
    char password[MAX_BUFFER];

    printf("\n\033[1;36m🌠 Welcome to Cosmic OS Pro Edition\033[0m\n");

    while (1) {
        printf("Login: ");
        if (!fgets(username, MAX_BUFFER, stdin)) return 1;
        username[strcspn(username, "\n")] = 0;

        printf("Password: ");
        set_echo(0);
        if (!fgets(password, MAX_BUFFER, stdin)) return 1;
        password[strcspn(password, "\n")] = 0;
        set_echo(1);
        printf("\n");

        int found = 0;
        for (int i = 0; i < sizeof(users)/sizeof(users[0]); i++) {
            if (strcmp(username, users[i].username) == 0 && 
                strcmp(password, users[i].password) == 0) {
                found = 1;
                break;
            }
        }

        if (found) {
            printf("\033[1;32mAccess Granted. Initializing Cosmic Shell...\033[0m\n\n");
            // Set environment variable for shell to know the user
            setenv("USER", username, 1);
            return 0; // Success
        } else {
            printf("\033[1;31mInvalid credentials. The cosmos is silent.\033[0m\n");
        }
    }
}
