#include <stdio.h>

int main() {
    int pin = 1234;
    int balance = 1000;
    int choice, enteredPin, withdrawAmount, depositAmount;
    
    printf("Enter your PIN: ");
    scanf("%d", &enteredPin);

    if (enteredPin != pin) {
        printf("Invalid PIN.\n");
        return 1;
    }

    while (1) {
        printf("\nATM Menu:\n");
        printf("1. Check Balance\n");
        printf("2. Withdraw Cash\n");
        printf("3. Deposit Cash\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Your balance is: %d\n", balance);
                break;
            case 2:
                printf("Enter amount to withdraw: ");
                scanf("%d", &withdrawAmount);
                if (withdrawAmount > balance) {
                    printf("Insufficient balance.\n");
                } else {
                    balance -= withdrawAmount;
                    printf("Withdrawal successful. New balance: %d\n", balance);
                }
                break;
            case 3:
                printf("Enter amount to deposit: ");
                scanf("%d", &depositAmount);
                balance += depositAmount;
                printf("Deposit successful. New balance: %d\n", balance);
                break;
            case 4:
                printf("Thank you for using the ATM.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}