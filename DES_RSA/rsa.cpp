#include <bits/stdc++.h>
#include <gmp.h>

using namespace std;


gmp_randstate_t state;
unsigned int seed;
void Rand_init() {
	gmp_randinit_mt(state);
	seed = time(NULL);
	gmp_randseed_ui(state, seed);
}



int main () {

	Rand_init();

	mpz_t p, q, n, count, totient, e, d, pt, ct, dt, temp;
	mpz_inits(p, q, n, count, totient, e, d, pt, ct, dt, temp, NULL);
	
	int bits = 16, result = 0;
	while (!result) {
		mpz_rrandomb(p, state, bits);
		result = mpz_probab_prime_p(p, 1000);
	}
	result = 0;
	while (!result) {
		mpz_rrandomb(q, state, bits);
		result = mpz_probab_prime_p(q, 1000);
	}
	gmp_printf("p: %Zd\nq: %Zd\n", p, q);
	
	mpz_mul(n, p, q);
	
	mpz_sub_ui(p, p, 1);
	mpz_sub_ui(q, q, 1);
	mpz_mul(totient, p, q);
	mpz_add_ui(p, p, 1);
	mpz_add_ui(q, q, 1);
	
	
	gmp_printf("n: %Zd\ntotient: %Zd\n", n, totient);
	
	while (mpz_cmp_ui(e, 1) <= 0 || mpz_cmp_ui(temp, 1) != 0) {
		mpz_urandomm(e, state, totient);
		mpz_gcd(temp, e, totient);
	}
	
	gmp_printf("e: %Zd\n", e);
	
	mpz_invert(d, e, totient);
	gmp_printf("d: %Zd\n", d);
	mpz_mul(temp, e, d);
	mpz_mod(temp, temp, totient);
	
	printf("Enter the Message: ");
	gmp_scanf("%Zd", pt);
	
	mpz_powm(ct, pt, e, n);
	
	gmp_printf("CipherText: %Zd\n", ct);
	
	mpz_powm(dt, ct, d, n);
	gmp_printf("Decrypted Text: %Zd\n", dt);
	
	if (mpz_cmp(pt, dt) == 0) {
		printf("Decryption successful\n");
	}
	else {
		printf("Decryption failed\n");
	}
	
	return 0;
}
