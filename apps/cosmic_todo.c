#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_FILE "/home/todo.txt"
#define MAX_TASK 256

void show_list() {
    FILE *f = fopen(TODO_FILE, "r");
    if (!f) {
        printf("\033[1;33mNo tasks found! Your cosmic journey is clear.\033[0m\n");
        return;
    }

    char task[MAX_TASK];
    int count = 1;
    printf("\033[1;36m--- 🌌 Cosmic Todo List ---\033[0m\n");
    while (fgets(task, sizeof(task), f)) {
        printf("%d. %s", count++, task);
    }
    fclose(f);
}

void add_task(char *task) {
    FILE *f = fopen(TODO_FILE, "a");
    if (!f) {
        perror("Could not open todo file");
        return;
    }
    fprintf(f, "%s\n", task);
    fclose(f);
    printf("\033[1;32mTask added to the stars!\033[0m\n");
}

void clear_tasks() {
    remove(TODO_FILE);
    printf("\033[1;31mTodo list cleared. A new galaxy awaits.\033[0m\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        show_list();
        printf("\nUsage: cosmic-todo [add <task> | clear]\n");
        return 0;
    }

    if (strcmp(argv[1], "add") == 0 && argc > 2) {
        char buffer[MAX_TASK] = "";
        for (int i = 2; i < argc; i++) {
            strcat(buffer, argv[i]);
            if (i < argc - 1) strcat(buffer, " ");
        }
        add_task(buffer);
    } else if (strcmp(argv[1], "clear") == 0) {
        clear_tasks();
    } else {
        printf("Unknown command. Usage: cosmic-todo [add <task> | clear]\n");
    }

    return 0;
}
