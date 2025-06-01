#include <stdio.h>
#include <string.h>

int main() {
    char str[100], rev[100];
    int i, len, flag = 0;

    printf("Enter a string: ");
    scanf("%s", str);

    len = strlen(str);

    // Reverse the string manually
    for(i = 0; i < len; i++) {
        rev[i] = str[len - i - 1];
    }
    rev[i] = '\0';  // Null terminate the reversed string

    // Compare original and reversed
    if(strcmp(str, rev) == 0) {
        printf("'%s' is a palindrome.\n", str);
    } else {
        printf("'%s' is not a palindrome.\n", str);
    }

    return 0;
}