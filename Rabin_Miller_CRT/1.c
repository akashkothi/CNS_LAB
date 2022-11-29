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

int fermatPrimalityTest(mpz_t p) {

    if (mpz_cmp_ui(p, 1) == 0)
        return -1;

    if (mpz_cmp_ui(p, 2) == 0)
        return 1;

    mpz_t a, r;
    mpz_inits(a, r, NULL);

    while (mpz_cmp_ui(a, 0) == 0 || mpz_cmp_ui(a, 1) == 0)
        mpz_urandomm(a, state, p);
    
    mpz_sub_ui(r, p, 1);
    mpz_powm(a, a, r, p);
    mpz_mod(a, a, p);

    if (mpz_cmp_ui(a, 1) == 0)
        return 1;
    return 0;
}

int main (int argc, char* argv[]) {

    randInit();

    mpz_t p, a, r;
    mpz_inits(p, a, r, NULL);
    printf("Enter the number: ");
    gmp_scanf("%Zd", p);
    
    int ans = fermatPrimalityTest(p);
    if (ans == -1) {
        gmp_printf("%Zd is neither prime nor composite\n", p);
    }
    else if (ans == 1) {
        gmp_printf("%Zd is probably prime\n", p);
    }
    else {
        gmp_printf("%Zd is composite number\n", p);
    }
    return 0;
}