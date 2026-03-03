#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/cinema.h"

/*
 * Function: create_cinema_array
 */
CINEMA* create_cinema_array(int size) {
    if (size < 12) {
        printf("Warning: Minimum 12 records required. Using %d.\n", size);
    }
    
    /* Динамическое выделение памяти для массива структур [citation:4] */
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
        getchar(); /* очистка буфера */
        
        printf("Genre: ");
        fgets(cinema[i].genre, sizeof(cinema[i].genre), stdin);
        cinema[i].genre[strcspn(cinema[i].genre, "\n")] = 0;
        
        printf("Budget (million $): ");
        scanf("%f", &cinema[i].budget);
        getchar(); /* очистка буфера */
    }
    
    return cinema;
}

/*
 * Function: print_max_min_duration
 */
void print_max_min_duration(const CINEMA* cinema, int size) {
    if (size <= 0) return;
    
    int max_idx = 0, min_idx = 0;
    
    for (int i = 1; i < size; i++) {
        if (cinema[i].duration_minutes > cinema[max_idx].duration_minutes) {
            max_idx = i;
        }
        if (cinema[i].duration_minutes < cinema[min_idx].duration_minutes) {
            min_idx = i;
        }
    }
    
    printf("\n=== MOVIE WITH MAXIMUM DURATION ===\n");
    printf("Title: %s\n", cinema[max_idx].movie_title);
    printf("Date: %s, Time: %s\n", cinema[max_idx].session_date, cinema[max_idx].session_time);
    printf("Duration: %d min\n", cinema[max_idx].duration_minutes);
    printf("Genre: %s, Budget: %.2f million $\n", cinema[max_idx].genre, cinema[max_idx].budget);
    
    printf("\n=== MOVIE WITH MINIMUM DURATION ===\n");
    printf("Title: %s\n", cinema[min_idx].movie_title);
    printf("Date: %s, Time: %s\n", cinema[min_idx].session_date, cinema[min_idx].session_time);
    printf("Duration: %d min\n", cinema[min_idx].duration_minutes);
    printf("Genre: %s, Budget: %.2f million $\n", cinema[min_idx].genre, cinema[min_idx].budget);
}

/*
 * Function: print_evening_short_movies
 */
void print_evening_short_movies(const CINEMA* cinema, int size) {
    int hour;
    int found = 0;
    
    printf("\n=== MOVIES AFTER 18:00 WITH DURATION < 90 MIN ===\n");
    
    for (int i = 0; i < size; i++) {
        sscanf(cinema[i].session_time, "%d", &hour);
        
        if (hour >= 18 && cinema[i].duration_minutes < 90) {
            found = 1;
            printf("\nTitle: %s\n", cinema[i].movie_title);
            printf("Time: %s, Duration: %d min\n", cinema[i].session_time, cinema[i].duration_minutes);
            printf("Genre: %s, Budget: %.2f million $\n", cinema[i].genre, cinema[i].budget);
        }
    }
/*
 * Function: print_comedy_max_budget
void print_comedy_max_budget(const CINEMA* cinema, int size) {
    float max_budget = -1;
    /* Поиск комедии с максимальным бюджетом */
    for (int i = 0; i < size; i++) {
        if (strcasecmp(cinema[i].genre, "comedy") == 0 || 
                max_budget = cinema[i].budget;
                max_budget_idx = i;
            }
        }
    }
    printf("\n=== COMEDY MOVIES WITH MAXIMUM BUDGET ===\n");
    if (max_budget_idx != -1) {
        for (int i = 0; i < size; i++) {
            if ((strcasecmp(cinema[i].genre, "comedy") == 0 || 
                 strcasecmp(cinema[i].genre, "комедия") == 0) && 
                cinema[i].budget == max_budget) {
                printf("\nTitle: %s\n", cinema[i].movie_title);
                printf("Budget: %.2f million $\n", cinema[i].budget);
                printf("Date: %s, Time: %s\n", cinema[i].session_date, cinema[i].session_time);
            }
    } else {
        printf("No comedy movies found.\n");
    }
}

/*
 * Helper function: сравнение по жанру и бюджету
 */
int compare_by_genre_budget(const void* a, const void* b) {
    const CINEMA* movie_a = (const CINEMA*)a;
    const CINEMA* movie_b = (const CINEMA*)b;
    
    /* Сначала по жанру */
    int genre_cmp = strcasecmp(movie_a->genre, movie_b->genre);
    if (genre_cmp != 0) {
        return genre_cmp;
    }
    
    /* Затем по бюджету (по убыванию) */
    if (movie_a->budget > movie_b->budget) return -1;
    if (movie_a->budget < movie_b->budget) return 1;
    return 0;
}

/*
 * Function: sort_and_print_by_genre_budget
 */
void sort_and_print_by_genre_budget(CINEMA* cinema, int size) {
    /* Сортировка массива структур */
    qsort(cinema, size, sizeof(CINEMA), compare_by_genre_budget);
    
    printf("\n=== MOVIES SORTED BY GENRE AND BUDGET ===\n");
    char current_genre[50] = "";
    
    for (int i = 0; i < size; i++) {
        if (strcasecmp(cinema[i].genre, current_genre) != 0) {
            strcpy(current_genre, cinema[i].genre);
            printf("\n--- Genre: %s ---\n", current_genre);
        }
        
        printf("  %s - %.2f million $\n", cinema[i].movie_title, cinema[i].budget);
    }
}

/*
 * Function: free_cinema_array
 */
void free_cinema_array(CINEMA* cinema) {
    free(cinema);
}        }
    
            if (max_budget_idx == -1 || cinema[i].budget > max_budget) {
            strcasecmp(cinema[i].genre, "комедия") == 0) {
    
    int max_budget_idx = -1;
 */

}
    }
    
        printf("No movies found.\n");

