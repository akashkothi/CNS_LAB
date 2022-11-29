#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


char* encrypt(char* str, int n) {

    int len = (int) strlen(str);
    char *res = malloc(len * sizeof(char));
    
    for (int i = 0; i < len; i++) {
        
        if (isalpha(str[i])) {
            if (isupper(str[i])) {
                res[i] = (char)('A' + (str[i] - 'A' + n) % 26);
            }
            else {
                res[i] = (char)('a' + (str[i] - 'a' + n) % 26);
            }
        }
    }
    return res;
}


char* decrypt (char* str, int n) {
    
    int len = (int) strlen(str);
    char *res = malloc(len * sizeof(char));
    
    for (int i = 0; i < len; i++) {
        
        if (isalpha(str[i])) {
            if (isupper(str[i])) {
                res[i] = (char)('A' + (str[i] - 'A' - n + 26) % 26);
            }
            else {
                res[i] = (char)('a' + (str[i] - 'a' - n + 26) % 26);
            }
        }
    }
    return res;
}

int main (int argc, char* argv[]) {
    
    int n;
    printf("Enter the shift value of the caeser cipher: ");
    scanf("%d", &n);
    printf("1. To encrypt\n");
    printf("2. To decrypt\n");
    int val;
    printf("Enter the operation to be done: ");
    scanf("%d", &val);
    switch (val) {
        case 1: {
            char str[100];
            printf("Enter the plain text: ");
            getchar();
            scanf("%[^\n]%*c", str);
            char* res = encrypt(str, n);
            printf("%s\n", str);
            printf("Cipher text: %s\n", res);
            break;
        }
        case 2: {
            char str[100];
            printf("Enter the Cipher text: ");
            getchar();
            scanf("%[^\n]%*c", str);
            char* res = decrypt(str, n);
            printf("Plain text: %s\n", res);
            break;
        }
        default: {
            printf("Invalid option\n");
        }
    }
    return 0;
}