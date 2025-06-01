#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

void createAccount() {
    FILE *fp = fopen("accounts.txt", "a");
    struct Account a;

    printf("Enter Account Number: ");
    scanf("%d", &a.accNo);
    getchar();

    printf("Enter Account Holder Name: ");
    fgets(a.name, sizeof(a.name), stdin);
    a.name[strcspn(a.name, "\n")] = '\0';

    printf("Enter Initial Balance: ");
    scanf("%f", &a.balance);

    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);

    printf("Account created successfully!\n");
}

void viewAccounts() {
    FILE *fp = fopen("accounts.txt", "r");
    struct Account a;

    printf("\n--- All Bank Accounts ---\n");
    while (fread(&a, sizeof(a), 1, fp)) {
        printf("Account Number: %d\nName: %s\nBalance: %.2f\n\n", a.accNo, a.name, a.balance);
    }
    fclose(fp);
}

void searchAccount() {
    FILE *fp = fopen("accounts.txt", "r");
    struct Account a;
    int num, found = 0;

    printf("Enter Account Number to search: ");
    scanf("%d", &num);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == num) {
            printf("Account Found:\nAccount Number: %d\nName: %s\nBalance: %.2f\n", a.accNo, a.name, a.balance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("No account found with Account Number %d.\n", num);
    fclose(fp);
}

void deleteAccount() {
    FILE *fp = fopen("accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Account a;
    int num, found = 0;

    printf("Enter Account Number to delete: ");
    scanf("%d", &num);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo != num)
            fwrite(&a, sizeof(a), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found)
        printf("Account deleted successfully.\n");
    else
        printf("Account Number %d not found.\n", num);
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Bank Management System ---\n");
        printf("1. Create Account\n2. View Accounts\n3. Search Account\n4. Delete Account\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: createAccount(); break;
            case 2: viewAccounts(); break;
            case 3: searchAccount(); break;
            case 4: deleteAccount(); break;
            case 5: exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}