#include <stdio.h>

double convert(int celcius) {
    return (celcius * 1.8) + 32;
}

int main(void) {
    int celcius;
    printf("Please enter celcius: ");
    if (scanf("%d", &celcius) != 1) {
        return 1;
    };
    printf("Fahrenheit: %0.1f\n", convert(celcius));
    return 0;
}
