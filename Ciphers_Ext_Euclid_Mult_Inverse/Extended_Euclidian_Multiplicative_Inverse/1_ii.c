#include <stdio.h>
#include <gmp.h>

void EEA(mpz_t g, mpz_t A, mpz_t B, mpz_t X, mpz_t Y) {
    mpz_t a, b, q, r, x0, y0, x1, y1, t1, t2;
    mpz_inits(a, b, q, r, x0, y0, x1, y1, t1, t2, NULL);
    
    mpz_set_ui(x0, 1);
    mpz_set_ui(y0, 0);
    mpz_set_ui(x1, 0);
    mpz_set_ui(y1, 1);
    mpz_set(a, A);
    mpz_set(b, B);
    
    mpz_mod(a, a, b);
    while (1) {
        mpz_fdiv_qr(q, r, a, b);
        mpz_set(a, b);
        mpz_set(b, r);
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
    }
    mpz_set(g, a);
    mpz_set(X, x1);
}

int main (int argc,char* argv[]) {
    
    mpz_t a, b, g, X, Y, x;
    mpz_inits(a, b, g, X, Y, x, NULL);
    
    printf("Enter the value of a: ");
    gmp_scanf("%Zd", a);
    printf("Enter the value of b: ");
    gmp_scanf("%Zd", b);
    
    gmp_printf("Value of a: %Zd\nValue of b: %Zd\n", a, b);
    
    EEA(g, a, b, X, Y);    
    
    mpz_mod(X, X, b);
    mpz_set(x, X);
    
    // checking whether found inverse is true or not    
    mpz_mul(X, X, a);
    mpz_mod(X, X, b);
    if (mpz_cmp_ui(X, 1) == 0){
        gmp_printf("\nMultiplicative inverse found is: %Zd\n", x);
    }
    else
        printf("Doesn't exists\n");
    
    return 0;
}