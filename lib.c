#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[100];
    char author[50];
    int quantity;
};

void addBook() {
    FILE *fp = fopen("library.txt", "a");
    struct Book b;

    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    getchar();

    printf("Enter Book Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = '\0';

    printf("Enter Author Name: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = '\0';

    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
    printf("Book added successfully.\n");
}

void viewBooks() {
    FILE *fp = fopen("library.txt", "r");
    struct Book b;

    printf("\n--- Library Books ---\n");
    while (fread(&b, sizeof(b), 1, fp)) {
        printf("ID: %d\nTitle: %s\nAuthor: %s\nQuantity: %d\n\n", b.id, b.title, b.author, b.quantity);
    }
    fclose(fp);
}

void searchBook() {
    FILE *fp = fopen("library.txt", "r");
    struct Book b;
    int id, found = 0;

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            printf("Book Found:\nID: %d\nTitle: %s\nAuthor: %s\nQuantity: %d\n", b.id, b.title, b.author, b.quantity);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("No book found with ID %d.\n", id);
    fclose(fp);
}

void deleteBook() {
    FILE *fp = fopen("library.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Book b;
    int id, found = 0;

    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id != id)
            fwrite(&b, sizeof(b), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);
    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (found)
        printf("Book deleted successfully.\n");
    else
        printf("Book with ID %d not found.\n", id);
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Library Management System ---\n");
        printf("1. Add Book\n2. View Books\n3. Search Book\n4. Delete Book\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}