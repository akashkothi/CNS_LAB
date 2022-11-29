#include <stdio.h>
#include <time.h>
#include <gmp.h>

int main (int argc, char* argv[]) {
	
	mpz_t primeNumber;
	mpz_init(primeNumber);
	
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	unsigned long seed;
	seed = time(NULL);
	gmp_randseed_ui(state, seed);
	
	int bits = 1024, result = 0;
	while (!result) {
		mpz_rrandomb(primeNumber, state, bits);
		result = mpz_probab_prime_p(primeNumber, 30);
	}
	gmp_printf("1024 bit prime number: %Zd \n", primeNumber);
	return 0;
}
