#include <bits/stdc++.h>
#include <gmp.h>

using namespace std;

gmp_randstate_t state;
unsigned long seed;

void rand_init(){
	gmp_randinit_mt(state);
	seed = time(NULL);
	gmp_randseed_ui(state, seed);
}

void get_p_alpha(mpz_t p, mpz_t alpha) {
	int bits = 1024, flag = 0;
	mpz_t t1, t2, t3, q, r;
	mpz_inits(t1, t2, t3, q, r, NULL);
	while (!flag) {
		int f = 0;
		while (!f) {
			mpz_rrandomb(p, state, bits);
			f = mpz_probab_prime_p(p, 30);
		}
		mpz_sub_ui(t1, p, 1);
		mpz_fdiv_q_ui(t1, t1, 2);
		flag = mpz_probab_prime_p(t1, 30);
	}
	mpz_set_ui(q, 2);
	mpz_set(r, t1);
	
	flag = 0;
	while (!flag) {
		mpz_urandomm(t1, state, p);
		while (mpz_cmp_ui(t1, 1) <= 0 || mpz_cmp(t1, p) >= 0) {
			mpz_urandomm(t1, state, p);
		}
		mpz_powm(t2, t1, q, p);
		mpz_powm(t3, t1, r, p);
		if (mpz_cmp_ui(t2, 1) != 0 && mpz_cmp_ui(t3, 1) != 0) {
			mpz_set(alpha, t1);
			flag = 1;
		}
	}
}

int main() {
	
	rand_init();
	
	mpz_t p, g, x1, y1, k, m, c1, c2, temp;
	
	mpz_inits(p, g, x1, y1, k, m, c1, c2, temp, NULL);
	
	get_p_alpha(p, g);

	gmp_printf("prime Number: %Zd\n\nalpha: %Zd\n\n", p, g);
	
	mpz_urandomm(x1, state, p);
	mpz_sub_ui(temp, p, 1);
	
	while (mpz_cmp_ui(k, 1) <= 0 || mpz_cmp(k, temp) >= 0) {
		mpz_urandomm(k, state, p);
	}
	
	
	// private key
	while (mpz_cmp_ui(x1, 1) <= 0 || mpz_cmp(x1, temp) >= 0) {
		mpz_urandomm(x1, state, p);
	}
	// public key
	mpz_powm(y1, g, x1, p);
	

	printf("Enter message: ");
	gmp_scanf("%Zd", m);
	
	// C1 and C2
	mpz_powm(c1, g, k, p);
	mpz_powm(c2, y1, k, p);
	mpz_mul(c2, c2, m);
	mpz_mod(c2, c2, p);
	
	gmp_printf("C1: %Zd\n\nC2: %Zd\n\n", c1, c2);
	
	
	mpz_powm(c1, c1, x1, p);
	mpz_invert(c1, c1, p);
	mpz_mul(c2, c2, c1);
	mpz_mod(c2, c2, p);
	
	gmp_printf("decrypted text: %Zd\n\n", c2);
	
	if (mpz_cmp(m, c2) == 0) {
		printf("decryption successful\n");
	}
	else {
		printf("decryption failed\n");
	}
	
	
	return 0;
}
