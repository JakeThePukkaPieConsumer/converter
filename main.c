#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

// Clear the console helper
void clear(void) {
    system("clear");
}

int read_double(const char *prompt, double *out) {
    char buf[256];

    for (;;) {
        printf("%s", prompt);
        if (fgets(buf, sizeof buf, stdin) == NULL)
            return 0; // EOF / read error

        errno = 0;
        char *end;
        double val = strtod(buf, &end);

        // Skip trailing whitespace/newline
        while (isspace((unsigned char)*end))
            end++;

        if (errno == ERANGE || end == buf || *end != '\0') {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        *out = val;
        return 1;
    }
}

// Celcius to Fahrenheit
double c_to_f(double celcius) {
    return (celcius * 1.8) + 32;
}

// Fahreineit to Celcius
double f_to_c(double fahrenheit) {
    return (fahrenheit - 32) / 1.8;
}

// Kelvin to Celcius
double k_to_c(double kelvin) {
    return kelvin - 273.15;
}

// Celcius to Kelvin
double c_to_k(double celcius) {
    return celcius + 273.15;
}

// Kelvin to Fahrenheit
double k_to_f(double kelvin) {
    return ((kelvin - 273.15) * 1.8) + 32;
}

// Fahrenheit to Kelvin
double f_to_k(double fahrenheit) {
    return ((fahrenheit - 32) / 1.8) + 273.15;
}

void handle_celcius_to_fahrenheit(void) {
    double celcius;
    printf("Celcius - Fahrenheit\n\n");

    if (!read_double("Enter celcius: ", &celcius))
        return;

    printf("Result: %.2f °Fahrenheit\n", c_to_f(celcius));
}

void handle_fahrenheit_to_celcius(void) {
    double fahrenheit;
    printf("Fahrenheit to Celcius\n\n");

    if (!read_double("Enter Fahrenheit: ", &fahrenheit))
        return;

    printf("Result: %.2f °Celcius\n", f_to_c(fahrenheit));
}

void handle_kelvin_to_celcius(void) {
    double kelvin;
    printf("Kelivn to Celcius\n\n");

    if (!read_double("Enter Kelvin: ", &kelvin))
        return;

    printf("Result: %.2f °Celcius\n", k_to_c(kelvin));
}

void handle_celcius_to_kelvin(void) {
    double celcius;
    printf("Celcius to Kelvin\n\n");

    if (!read_double("Enter Celcius: ", &celcius))
        return;

    printf("Result: %.2f Kelvin\n", c_to_k(celcius));
}

void load_options(void) {
    int name_width = 20;

    printf("%-*s\n", name_width, "1. Celcius to Fahrenheit");
    printf("%-*s\n", name_width, "2. Fahrenheit to Celcius");
    printf("%-*s\n", name_width, "3. Kelvin to Celcius");
    printf("%-*s\n", name_width, "4. Clecius to Kelvin");
    printf("%-*s\n", name_width, "5. Fahrenheit to Kelvin");
    printf("%-*s\n", name_width, "6. Kelvin to Fahrenheit");
}

int footer(void) {
    char buf[16];

    printf("\nq to Quit | r to Return: ");

    if (!fgets(buf, sizeof buf, stdin))
        return 0;

    switch (tolower((unsigned char)buf[0])) {
        case 'q':
            return 0;
        case 'r':
            return 1;
        default:
            return 1;
    }
}

void handle_scene(void (*content)(void)) {
    clear();
    content();
    if (!footer())
        return;
}

void load_menu(void) {
    char buf[32];
    int choice;

    for (;;) {
        clear();
        printf("Conversion utility\n\n");
        load_options();

        printf("\nChoice: ");
        fgets(buf, sizeof buf, stdin);
        choice = atoi(buf);

        switch (choice) {
            case 1:
                handle_scene(handle_celcius_to_fahrenheit);
                break;

            case 2:
                handle_scene(handle_fahrenheit_to_celcius);
                break;

            case 3:
                handle_scene(handle_kelvin_to_celcius);
                break;

            case 4:
                handle_scene(handle_celcius_to_kelvin);
                break;

            case 0:
                return;
        }
    }
}

int main(void) {
    load_menu();
    return 0;
}
