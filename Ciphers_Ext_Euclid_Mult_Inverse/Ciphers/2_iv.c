#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char cipherKey[100];

char* encrypt(char* str){
    int len = strlen(str), length = 0;
    for (int i = 0; i < 100; i++) {
        if (cipherKey[i] != '\0')
            length++;
    }
    char* res = malloc(len * sizeof(char));
    int j = -1;
    for (int i = 0; i < len; i++) {
        res[i] = str[i];
        if (isalpha(res[i])) {
            int v1 = res[i] - 'a', v2 = cipherKey[(j + 1) % length] - 'a';
            res[i] = 'a' + (v1 + v2) % 26;
        }
    }

    return res;
}

char* decrypt(char* str){
    int len = strlen(str), length = 0;
    for (int i = 0; i < 100; i++) {
        if (cipherKey[i] != '\0')
            length++;
    }
    char* res = malloc(len * sizeof(char));
    int j = -1;
    for (int i = 0; i < len; i++) {
        res[i] = str[i];
        if (isalpha(res[i])) {
            int v1 = res[i] - 'a', v2 = cipherKey[(j + 1) % length] - 'a';
            res[i] = 'a' + (v1 - v2 + 26) % 26;
        }
    }

    return res;
}



int main (int argc, char* argv[]) {

    printf("Enter the key for polyalphabetic Cipher: ");
    scanf("%[^\n]%*c", cipherKey);
    printf("%s\n", cipherKey);

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
            char* res = encrypt(str);
            printf("Plain text: %s\n", str);
            printf("Cipher text: %s\n", res);
            break;
        }
        case 2: {
            char str[100];
            printf("Enter the Cipher text: ");
            getchar();
            scanf("%[^\n]%*c", str);
            char* res = decrypt(str);
            printf("Cipher text: %s\n", str);
            printf("Plain text: %s\n", res);
            break;
        }
        default: {
            printf("Invalid option\n");
        }
    }

    return 0;
}