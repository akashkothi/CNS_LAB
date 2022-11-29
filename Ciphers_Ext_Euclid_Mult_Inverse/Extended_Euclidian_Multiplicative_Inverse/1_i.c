#include <stdio.h>
#include <gmp.h>

void EEA(mpz_t g, mpz_t A, mpz_t B, mpz_t X, mpz_t Y, int *i) {
    mpz_t a, b, q, r, x0, y0, x1, y1, t1, t2;
    mpz_inits(a, b, q, r, x0, y0, x1, y1, t1, t2, NULL);
    
    mpz_set_ui(x0, 1);
    mpz_set_ui(y0, 0);
    mpz_set_ui(x1, 0);
    mpz_set_ui(y1, 1);
    mpz_set(a, A);
    mpz_set(b, B);
    
    mpz_mod(a, a, b);
    printf("bezout coefficients at each iteration \n");
    while (1) {
        // gmp_printf("%Zd %Zd ", a, b);
        mpz_fdiv_qr(q, r, a, b);
        mpz_set(a, b);
        mpz_set(b, r);
        // gmp_printf("%Zd %Zd ", q, r);
        if (mpz_cmp_ui(b, 0) == 0)
            break;
        
        mpz_mul(t1, x1, q);
        mpz_set(t2, x1);
        mpz_sub(x1, x0, t1);
        mpz_set(x0, t2);
        
        mpz_mul(t1, y1, q);
        mpz_set(t2, y1);
        mpz_sub(y1, y0, t1);
        mpz_set(y0, t2);
        gmp_printf("%d: %Zd %Zd \n", (*i)++, x1, y1);
    }
    mpz_set(g, a);
    mpz_set(X, x1);
    mpz_set(Y, y1);
}

int main (int argc,char* argv[]) {
    
    mpz_t a, b, g, X, Y, x;
    mpz_inits(a, b, g, X, Y, x, NULL);
    
    printf("Enter the value of a: ");
    gmp_scanf("%Zd", a);
    printf("Enter the value of b: ");
    gmp_scanf("%Zd", b);
    
    gmp_printf("Value of a: %Zd\nValue of b: %Zd\n", a, b);
    
    int i = 1;
    EEA(g, a, b, X, Y, &i);
    
    gmp_printf("GCD is: %Zd\n", g);
    
    return 0;
}