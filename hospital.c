#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
};

void addPatient() {
    FILE *fp = fopen("patients.txt", "a");
    struct Patient p;

    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    getchar(); // consume newline

    printf("Enter Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = '\0';

    printf("Enter Age: ");
    scanf("%d", &p.age);
    getchar();

    printf("Enter Disease: ");
    fgets(p.disease, sizeof(p.disease), stdin);
    p.disease[strcspn(p.disease, "\n")] = '\0';

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    printf("Patient record added successfully.\n");
}

void viewPatients() {
    FILE *fp = fopen("patients.txt", "r");
    struct Patient p;

    printf("\n--- All Patient Records ---\n");
    while (fread(&p, sizeof(p), 1, fp)) {
        printf("ID: %d\nName: %s\nAge: %d\nDisease: %s\n\n", p.id, p.name, p.age, p.disease);
    }
    fclose(fp);
}

void searchPatient() {
    FILE *fp = fopen("patients.txt", "r");
    struct Patient p;
    int id, found = 0;

    printf("Enter Patient ID to search: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("Record Found:\nID: %d\nName: %s\nAge: %d\nDisease: %s\n", p.id, p.name, p.age, p.disease);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("No record found for ID %d.\n", id);
    fclose(fp);
}

void deletePatient() {
    FILE *fp = fopen("patients.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Patient p;
    int id, found = 0;

    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id != id)
            fwrite(&p, sizeof(p), 1, temp);
        else
            found = 1;
    }
    fclose(fp);
    fclose(temp);
    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (found)
        printf("Record deleted successfully.\n");
    else
        printf("No record found with ID %d.\n", id);
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Hospital Management System ---\n");
        printf("1. Add Patient\n2. View Patients\n3. Search Patient\n4. Delete Patient\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}