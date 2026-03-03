#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/cinema.h"

CINEMA* create_cinema_array(int size) {
    if (size < 12) {
        printf("Warning: Minimum 12 records required. Using %d.\n", size);
    }

    CINEMA* cinema = (CINEMA*)malloc(size * sizeof(CINEMA));
    if (cinema == NULL) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }

    printf("Enter data for %d movies:\n", size);
    for (int i = 0; i < size; i++) {
        printf("\n--- Movie %d ---\n", i + 1);

        printf("Title: ");
        fgets(cinema[i].movie_title, sizeof(cinema[i].movie_title), stdin);
        cinema[i].movie_title[strcspn(cinema[i].movie_title, "\n")] = 0;

        printf("Date (DD.MM.YYYY): ");
        fgets(cinema[i].session_date, sizeof(cinema[i].session_date), stdin);
        cinema[i].session_date[strcspn(cinema[i].session_date, "\n")] = 0;

        printf("Time (HH:MM): ");
        fgets(cinema[i].session_time, sizeof(cinema[i].session_time), stdin);
        cinema[i].session_time[strcspn(cinema[i].session_time, "\n")] = 0;

        printf("Duration (minutes): ");
        scanf("%d", &cinema[i].duration_minutes);
        getchar();

        printf("Genre: ");
        fgets(cinema[i].genre, sizeof(cinema[i].genre), stdin);
        cinema[i].genre[strcspn(cinema[i].genre, "\n")] = 0;

        printf("Budget (million $): ");
        scanf("%f", &cinema[i].budget);
        getchar();
    }
    return cinema;
}

void print_max_min_duration(const CINEMA* cinema, int size) {
    if (size <= 0) return;

    int max_idx = 0, min_idx = 0;
    for (int i = 1; i < size; i++) {
        if (cinema[i].duration_minutes > cinema[max_idx].duration_minutes)
            max_idx = i;
        if (cinema[i].duration_minutes < cinema[min_idx].duration_minutes)
            min_idx = i;
    }

    printf("\n=== MAX DURATION ===\n");
    printf("Title: %s\n", cinema[max_idx].movie_title);
    printf("Date: %s %s\n", cinema[max_idx].session_date, cinema[max_idx].session_time);
    printf("Duration: %d min\n", cinema[max_idx].duration_minutes);
    printf("Genre: %s\n", cinema[max_idx].genre);
    printf("Budget: %.2f $\n\n", cinema[max_idx].budget);

    printf("=== MIN DURATION ===\n");
    printf("Title: %s\n", cinema[min_idx].movie_title);
    printf("Date: %s %s\n", cinema[min_idx].session_date, cinema[min_idx].session_time);
    printf("Duration: %d min\n", cinema[min_idx].duration_minutes);
    printf("Genre: %s\n", cinema[min_idx].genre);
    printf("Budget: %.2f $\n", cinema[min_idx].budget);
}

void print_evening_short_movies(const CINEMA* cinema, int size) {
    int hour, found = 0;
    printf("\n=== EVENING SHORT MOVIES (after 18:00, <90min) ===\n");

    for (int i = 0; i < size; i++) {
        sscanf(cinema[i].session_time, "%d", &hour);
        if (hour >= 18 && cinema[i].duration_minutes < 90) {
            found = 1;
            printf("\n%s at %s, %d min, %s, %.2f $\n",
                   cinema[i].movie_title, cinema[i].session_time,
                   cinema[i].duration_minutes, cinema[i].genre, cinema[i].budget);
        }
    }
    if (!found) printf("No movies found.\n");
}

void print_comedy_max_budget(const CINEMA* cinema, int size) {
    int max_idx = -1;
    float max_budget = -1;

    for (int i = 0; i < size; i++) {
        if (strcasecmp(cinema[i].genre, "comedy") == 0 || 
            strcasecmp(cinema[i].genre, "комедия") == 0) {
            if (max_idx == -1 || cinema[i].budget > max_budget) {
                max_budget = cinema[i].budget;
                max_idx = i;
            }
        }
    }

    printf("\n=== COMEDY WITH MAX BUDGET ===\n");
    if (max_idx != -1) {
        for (int i = 0; i < size; i++) {
            if ((strcasecmp(cinema[i].genre, "comedy") == 0 || 
                 strcasecmp(cinema[i].genre, "комедия") == 0) && 
                cinema[i].budget == max_budget) {
                printf("%s - %.2f $ (%s %s)\n", cinema[i].movie_title,
                       cinema[i].budget, cinema[i].session_date, cinema[i].session_time);
            }
        }
    } else {
        printf("No comedy movies found.\n");
    }
}

int compare_by_genre_budget(const void* a, const void* b) {
    const CINEMA* ma = (const CINEMA*)a;
    const CINEMA* mb = (const CINEMA*)b;

    int genre_cmp = strcasecmp(ma->genre, mb->genre);
    if (genre_cmp != 0) return genre_cmp;
    return (mb->budget > ma->budget) ? 1 : -1;
}

void sort_and_print_by_genre_budget(CINEMA* cinema, int size) {
    qsort(cinema, size, sizeof(CINEMA), compare_by_genre_budget);

    printf("\n=== SORTED BY GENRE & BUDGET ===\n");
    char current_genre[50] = "";

    for (int i = 0; i < size; i++) {
        if (strcasecmp(cinema[i].genre, current_genre) != 0) {
            strcpy(current_genre, cinema[i].genre);
            printf("\n--- %s ---\n", current_genre);
        }
        printf("  %s - %.2f $\n", cinema[i].movie_title, cinema[i].budget);
    }
}

void free_cinema_array(CINEMA* cinema) {
    free(cinema);
}
