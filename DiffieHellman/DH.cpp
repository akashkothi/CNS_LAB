#include <bits/stdc++.h>
#include <gmp.h>

using namespace std;

gmp_randstate_t state;
unsigned long seed;

void rand_init() {
    gmp_randinit_mt(state);
    seed = time(NULL);
    gmp_randseed_ui(state, seed);
}

void get_p_q_r_alpha(mpz_t p, mpz_t alpha, int bits) {
    mpz_t temp, q, r, t1, t2;
    int result = 0;
    mpz_inits(temp, q, r, t1, t2, NULL);
    while (!result) {
        int res1 = 0;
        while (!res1) {
            mpz_rrandomb(p, state, bits);
            res1 = mpz_probab_prime_p(p, 30);
        }
        mpz_sub_ui(temp, p, 1);
        mpz_fdiv_q_ui(temp, temp, 2);
        result = mpz_probab_prime_p(temp, 30);
        if (!result) {
            mpz_set_ui(q, 2);
            mpz_set(r, temp);
        }
    }


    int flag = 0;
    while (!flag) {
        mpz_urandomm(temp, state, p);
        while (mpz_cmp_ui(temp, 1) <= 0 || mpz_cmp(temp, p) >= 0) {
            mpz_urandomm(temp, state, p);
        }
        mpz_powm(t1, temp, q, p);
        mpz_powm(t2, temp, r, p);
        if (mpz_cmp_ui(t1, 1) != 0 && mpz_cmp_ui(t2, 1) != 0) {
            flag = 1;
        }
    }
    mpz_set(alpha, temp);
}

void secret_key_generation(mpz_t k, mpz_t y, mpz_t x, mpz_t q) {
    mpz_powm(k, y, x, q);
}



int main() {

    rand_init();

    int bits = 1024;

    mpz_t p, q, r, alpha, xa, xb, ya, yb, ka, kb;
    mpz_inits(p, q, r, alpha, xa, xb, ya, yb, ka, kb, NULL);

    get_p_q_r_alpha(p, alpha, bits);

    gmp_printf("Prime Number\n%Zd\ngenertor is\n%Zd\n", p, alpha);

    // user A key generation
    mpz_urandomm(xa, state, p);
    while (mpz_cmp_ui(xa, 1) <= 0 || mpz_cmp(xa, p) >= 0) {
        mpz_urandomm(xa, state, p);
    }

    mpz_set_ui(xa, 97);
    mpz_powm(ya, alpha, xa, p);

    //user B key generation
    mpz_urandomm(xb, state, p);
    while (mpz_cmp_ui(xb, 1) <= 0 || mpz_cmp(xb, p) >= 0) {
        mpz_urandomm(xb, state, p);
    }

    mpz_powm(yb, alpha, xb, p);

    gmp_printf("User A public key\n%Zd\nUser B public key\n%Zd\n", ya, yb);


    // generation of secret key by user A
    mpz_powm(ka, yb, xa, p);

    // generation of secret key by user B
    mpz_powm(kb, ya, xb, p);
    
    if (mpz_cmp(ka, kb))
        printf("Secret keys generated does not match.\n");
    else
        printf("Secret keys generated are matched\n");

    return 0;
}