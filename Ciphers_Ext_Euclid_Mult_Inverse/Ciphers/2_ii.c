#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char cipherKey[26], decryptKey[26];

void formDecryptKey() {

    for (int i = 0; i < 26; i++) {
        decryptKey[cipherKey[i] - 'a'] = 'a' + i;
    }
}

char* encrypt(char* str) {

    int len = (int) strlen(str);
    char *res = malloc(len * sizeof(char));
    
    for (int i = 0; i < len; i++) {
        
        if (isalpha(str[i])) {
            res[i] = cipherKey[str[i] - 'a'];
        }
    }
    return res;
}


char* decrypt (char* str) {
    
    int len = (int) strlen(str);
    char *res = malloc(len * sizeof(char));
    
    for (int i = 0; i < len; i++) {
        
        if (isalpha(str[i])) {
            res[i] = decryptKey[str[i] - 'a'];
        }
    }
    return res;
}


int main (int argc, char* argv[]) {
    
    printf("Enter the cipherKey: ");
    for (int i = 0; i < 26; i++) {
        scanf("%c", cipherKey + i);
    }
    formDecryptKey();
    
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