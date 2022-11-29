#include <stdio.h>
#include <gmp.h>
#include <time.h>

gmp_randstate_t state;
unsigned long seed;

void randInit() {
    gmp_randinit_mt(state);
    seed = time(NULL);
    gmp_randseed_ui(state, seed);
}

int test(mpz_t n) {

    if (mpz_cmp_ui(n, 1) == 0)
        return -1;
    if (mpz_cmp_ui(n, 2) == 0 || mpz_cmp_ui(n, 3) == 0)
        return 1;

    mpz_t a, r, k, q;
    mpz_inits(a, r, k, q, NULL);

    mpz_set(q, n);
    mpz_set_ui(k, 0);
    
    mpz_mod_ui(r, q, 2);
    if (mpz_cmp_ui(r, 0) == 0)
        return 0;
    
    mpz_sub_ui(q, q, 1);
    mpz_set_ui(r, 0);
    while (mpz_cmp_ui(r, 0) == 0) {
        mpz_fdiv_qr_ui(q, r, q, 2);
        mpz_mod_ui(r, q, 2);
        mpz_add_ui(k, k, 1);
    }

    // gmp_printf("%Zd %Zd \n", k, q);

    mpz_sub_ui(n, n, 1);
    while (1) {
        mpz_urandomm(a, state, n);
        if (mpz_cmp_ui(a, 1) > 0 && mpz_cmp(a, n) < 0)
            break;
    }
    mpz_add_ui(n, n, 1);

    mpz_powm(r, a, q, n);


    if (mpz_cmp_ui(r, 1) == 0)
        return 1;

    for (int j = 0; mpz_cmp_ui(k, j) > 0; j++) {
        if (j != 0) {
            mpz_mul_ui(q, q, 2);
            mpz_powm(r, a, q, n);
        }
        mpz_add_ui(r, r, 1);
        if (mpz_cmp(r, n) == 0)
            return 1;
    }
    return 0;

} 

int main(int argc, char* argv[]) {

    randInit();

    mpz_t p;
    printf("Enter the number: ");
    gmp_scanf("%Zd", p);

    if (test(p) == 1) {
        gmp_printf("%Zd is prime number is inconclusive\n", p);
    }
    else {
        gmp_printf("%Zd is composite number\n", p);
    }

    return 0;
}