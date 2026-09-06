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

// celsius to Fahrenheit
double c_to_f(double celsius) {
    return (celsius * 1.8) + 32;
}

// Fahreineit to celsius
double f_to_c(double fahrenheit) {
    return (fahrenheit - 32) / 1.8;
}

// Kelvin to celsius
double k_to_c(double kelvin) {
    return kelvin - 273.15;
}

// celsius to Kelvin
double c_to_k(double celsius) {
    return celsius + 273.15;
}

// Kelvin to Fahrenheit
double k_to_f(double kelvin) {
    return ((kelvin - 273.15) * 1.8) + 32;
}

// Fahrenheit to Kelvin
double f_to_k(double fahrenheit) {
    return ((fahrenheit - 32) / 1.8) + 273.15;
}

void handle_celsius_to_fahrenheit(void) {
    double celsius;
    printf("Celsius - Fahrenheit\n\n");

    if (!read_double("Enter Celsius: ", &celsius))
        return;

    printf("Result: %.2f °fahrenheit\n", c_to_f(celsius));
}

void handle_fahrenheit_to_celsius(void) {
    double fahrenheit;
    printf("Fahrenheit to Celsius\n\n");

    if (!read_double("Enter Fahrenheit: ", &fahrenheit))
        return;

    printf("Result: %.2f °celsius\n", f_to_c(fahrenheit));
}

void handle_kelvin_to_celsius(void) {
    double kelvin;
    printf("Kelivn to Celsius\n\n");

    if (!read_double("Enter Kelvin: ", &kelvin))
        return;

    printf("Result: %.2f °celsius\n", k_to_c(kelvin));
}

void handle_celsius_to_kelvin(void) {
    double celsius;
    printf("Celsius to Kelvin\n\n");

    if (!read_double("Enter Celsius: ", &celsius))
        return;

    printf("Result: %.2f kelvin\n", c_to_k(celsius));
}

void load_options(void) {
    int name_width = 20;

    printf("%-*s\n", name_width, "1. celsius to Fahrenheit");
    printf("%-*s\n", name_width, "2. Fahrenheit to celsius");
    printf("%-*s\n", name_width, "3. Kelvin to Celsius");
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
                handle_scene(handle_celsius_to_fahrenheit);
                break;

            case 2:
                handle_scene(handle_fahrenheit_to_celsius);
                break;

            case 3:
                handle_scene(handle_kelvin_to_celsius);
                break;

            case 4:
                handle_scene(handle_celsius_to_kelvin);
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
