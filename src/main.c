#include <stdio.h>
#include <stdlib.h>
#include "../include/cinema.h"

int main() {
    int size;
    CINEMA* cinema = NULL;

    printf("=== CINEMA MANAGEMENT SYSTEM ===\n");
    printf("Variant 35: CINEMA structure\n\n");

    printf("Enter number of movies (minimum 12): ");
    scanf("%d", &size);
    getchar();

    if (size < 12) {
        printf("Error: At least 12 movies required.\n");
        return 1;
    }

    cinema = create_cinema_array(size);
    if (cinema == NULL) {
        printf("Error: Failed to create cinema array.\n");
        return 1;
    }

    printf("\n========================================\n");
    printf("DEMONSTRATION OF ALL FUNCTIONS\n");
    printf("========================================\n");

    print_max_min_duration(cinema, size);
    print_evening_short_movies(cinema, size);
    print_comedy_max_budget(cinema, size);
    sort_and_print_by_genre_budget(cinema, size);

    free_cinema_array(cinema);
    printf("\nProgram completed successfully.\n");
    return 0;
}
