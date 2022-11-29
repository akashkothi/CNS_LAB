#include <stdio.h>
#include <gmp.h>

void CRT(mpz_t X, mpz_t a[], mpz_t m[], int n) {

    mpz_set_ui(X, 0);

    mpz_t M, x[n], Mi[n], Minv[n], temp;
    mpz_init(temp);

    // finding M
    mpz_inits(M, NULL);
    mpz_set_ui(M, 1);
    for (int i = 0; i < n; i++) {
        mpz_mul(M, M, m[i]);
    }

    // finding Mi's
    for (int i = 0; i < n; i++) {
        mpz_init(Mi[i]);
        mpz_divexact(Mi[i], M, m[i]);
    }

    // finding inverses of Mi's w.r.to mi's
    for (int i = 0; i < n; i++) {
        mpz_init(Minv[i]);
        // EEAinv(Minv[i], Mi[i], m[i]);
        mpz_invert(Minv[i], Mi[i], m[i]);
    }

    for (int i = 0; i < n; i++) {
        mpz_set_ui(temp, 1);
        mpz_mul(temp, temp, Mi[i]);
        mpz_mul(temp, temp, Minv[i]);
        mpz_mul(temp, temp, a[i]);
        mpz_add(X, X, temp);
    }
    mpz_mod(X, X, M);
}

int main (int argc, char* argv[]) {

    int n;
    printf("Enter number of congruences: ");
    scanf("%d", &n);

    mpz_t a[n], m[n], ans;
    mpz_init(ans);
    printf("Enter the values of ai and mi in order\n");
    for (int i = 0; i < n; i++) {
        mpz_inits(a[i], m[i], NULL);
        gmp_scanf("%Zd", a[i]);
        gmp_scanf("%Zd", m[i]);
    }
    mpz_t X;
    mpz_init(X);

    CRT(X, a, m, n);
    gmp_printf("X value is: %Zd\n", X);


    return 0;
}