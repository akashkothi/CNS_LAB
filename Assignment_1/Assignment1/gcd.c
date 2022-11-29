#include <stdio.h>
#include <gmp.h>

int main(int argc, char* argv[]) {
	mpz_t a, b;
	mpz_inits(a, b, NULL);
	mpz_t t;
	
	printf("Enter the value of a: ");
	gmp_scanf("%Zd", a);
	printf("Enter the value of b: ");
	gmp_scanf("%Zd", b);
	
	while (mpz_cmp_ui(b, 0) != 0) {
		mpz_set(t, b);
		mpz_mod(b, a, b);
		mpz_set(a, t);
	}
	
	gmp_printf("GCD is: %Zd\n", a);
	return 0;
}
