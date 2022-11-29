#include <stdio.h>
#include <gmp.h>

int main() {
	
	mpz_t a, b;
	mpz_inits(a, b, NULL);
	printf("Enter the value of a: ");
	gmp_scanf("%Zd", a);
	printf("Enter the value of b: ");
	gmp_scanf("%Zd", b);
	gmp_printf("Value of a is %Zd and b is %Zd\n", a, b);
	if (mpz_cmp(a, b) > 0) {
		printf("a is greater than b\n");
	}
	else {
		printf("b is greater than a\n");
	}
	return 0;
}
