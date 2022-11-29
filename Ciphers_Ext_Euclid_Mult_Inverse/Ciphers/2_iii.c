#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char mat[5][5];

void formPlayFairMat(char* key) {

    int isPres[26];
    for (int i = 0; i < 26; i++)
        isPres[i] = 0;
    isPres['j' - 'a'] = 1;
    
    int row = 0, col = 0;
    
    for (int i = 0; i < strlen(key); i++) {
        if (key[i] == 'j')
            key[i] = 'i';
        if (isPres[key[i] - 'a'] == 1)
            continue;
        isPres[key[i] - 'a'] = 1;
        mat[row][col] = key[i];
        col = (col + 1) % 5;
        if (col == 0)
            row += 1;
    }
    
    for (int i = 0; i < 26; i++) {
    
        if (isPres[i] == 0) {
            isPres[i] = 1;
            mat[row][col] = 'a' + i;
            col = (col + 1) % 5;
            if (col == 0)
                row += 1;
        }
    }
}

void getRowAndCol(char ch, int *x, int *y) {

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (mat[i][j] == ch) {
                *x = i;
                *y = j;
                return;
            }
        }
    }
}

char* encrypt(char* str) {

    int len = (int) strlen(str);
    char *res = malloc(len * sizeof(char));
    int ind = 0;
    for (int i = 0; i < len; i++)
        if (str[i] == 'j')
            str[i] = 'i';
    int i = 0;
    while (i < len) {
        char ch1 = 'x', ch2 = 'x';
        int j = i;
        ch1 = str[j++];
        if (j < len && ch1 != str[j])
            ch2 = str[j++];
        int x1, y1, x2, y2;
        getRowAndCol(ch1, &x1, &y1);
        getRowAndCol(ch2, &x2, &y2);
        if (x1 == x2) {
            y1 = (y1 + 1) % 5;
            y2 = (y2 + 1) % 5;
        }
        else if (y1 == y2) {
            x1 = (x1 + 1) % 5;
            x2 = (x2 + 1) % 5;
        }
        else {
            int t = y1;
            y1 = y2;
            y2 = t;
        }
        res[ind++] = mat[x1][y1];
        if (j - i == 2)
            res[ind++] = mat[x2][y2];
        i = j;
    }

    return res;
}

char* decrypt (char* str) {
    
    int len = (int) strlen(str);
    char *res = malloc(len * sizeof(char));
    
    for (int i = 0; i < len; i++) {
        if (str[i] == 'j')
            str[i] = 'i';
    }
    int ind = 0, i = 0;

    while (i < len) {
        char ch1 = 'x', ch2 = 'x';
        int j = i;
        ch1 = str[j++];
        if (j < len && ch1 != str[j])
            ch2 = str[j++];
        int x1, y1, x2, y2;
        getRowAndCol(ch1, &x1, &y1);
        getRowAndCol(ch2, &x2, &y2);
        if (x1 == x2) {
            y1 = (y1 + 4) % 5;
            y2 = (y2 + 4) % 5;
        }
        else if (y1 == y2) {
            x1 = (x1 + 4) % 5;
            x2 = (x2 + 4) % 5;
        }
        else {
            int t = y1;
            y1 = y2;
            y2 = t;
        }
        res[ind++] = mat[x1][y1];
        if (j - i == 2)
            res[ind++] = mat[x2][y2];
        i = j;
    }

    return res;
}



int main (int argc, char* argv[]) {

    char key[100];
    printf("Enter the key for playfair matrix: ");
    scanf("%[^\n]%*c", key);
    printf("%s\n", key);
    
    formPlayFairMat(key);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
    
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
            printf("Plain text: %s\n", res);
            break;
        }
        default: {
            printf("Invalid option\n");
        }
    }
    
    return 0;
}