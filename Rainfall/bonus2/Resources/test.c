#include <stdio.h>

int main() {
	printf("sizeof(\"%s\") = %zu\n", "Hyvää päivää ", sizeof("Hyvää päivää "));
	printf("sizeof(\"%s\") = %zu\n", "Goedemiddag! ", sizeof("Goedemiddag! "));
	printf("sizeof(\"%s\") = %zu\n", "Hello ", sizeof("Hello "));
}
