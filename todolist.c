#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LENGTH 100

struct Task {
    char description[MAX_LENGTH];
};

int main() {
    struct Task tasks[MAX_TASKS];
    int taskCount = 0;
    int choice, i, del;

    while (1) {
        printf("\n--- To-Do List Menu ---\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Delete Task\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline character

        switch (choice) {
            case 1:
                if (taskCount < MAX_TASKS) {
                    printf("Enter task description: ");
                    fgets(tasks[taskCount].description, MAX_LENGTH, stdin);
                    tasks[taskCount].description[strcspn(tasks[taskCount].description, "\n")] = 0;
                    taskCount++;
                    printf("Task added successfully!\n");
                } else {
                    printf("Task list is full!\n");
                }
                break;

            case 2:
                if (taskCount == 0) {
                    printf("No tasks available.\n");
                } else {
                    printf("\nYour Tasks:\n");
                    for (i = 0; i < taskCount; i++) {
                        printf("%d. %s\n", i + 1, tasks[i].description);
                    }
                }
                break;

            case 3:
                if (taskCount == 0) {
                    printf("No tasks to delete.\n");
                } else {
                    printf("Enter task number to delete: ");
                    scanf("%d", &del);
                    if (del < 1 || del > taskCount) {
                        printf("Invalid task number!\n");
                    } else {
                        for (i = del - 1; i < taskCount - 1; i++) {
                            tasks[i] = tasks[i + 1];
                        }
                        taskCount--;
                        printf("Task deleted successfully!\n");
                    }
                }
                break;

            case 4:
                printf("Exiting To-Do List. Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}