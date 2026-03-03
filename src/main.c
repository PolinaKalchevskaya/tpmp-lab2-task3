#include <stdio.h>
#include <stdlib.h>
#include "../include/cinema.h"

int main() {
    int size;
    CINEMA* cinema = NULL;
    
    printf("=== CINEMA MANAGEMENT SYSTEM ===\n");
    printf("Variant 35: CINEMA structure\n\n");
    
    /* Ввод количества записей (минимум 12) */
    printf("Enter number of movies (minimum 12): ");
    scanf("%d", &size);
    getchar(); /* очистка буфера */
    
    if (size < 12) {
        printf("Error: At least 12 movies required.\n");
        return 1;
    }
    
    /* Создание массива структур */
    cinema = create_cinema_array(size);
    if (cinema == NULL) {
        printf("Error: Failed to create cinema array.\n");
        return 1;
    }
    
    /* Демонстрация всех функций */
    printf("\n" + "="*50 + "\n");
    printf("DEMONSTRATION OF ALL FUNCTIONS\n");
    printf("="*50 + "\n");
    
    /* 1. Фильмы с макс и мин продолжительностью */
    print_max_min_duration(cinema, size);
    
    /* 2. Фильмы после 18:00 с продолжительностью < 90 мин */
    print_evening_short_movies(cinema, size);
    
    /* 3. Комедии с максимальным бюджетом */
    print_comedy_max_budget(cinema, size);
    
    /* 4. Сортировка по жанру и бюджету */
    sort_and_print_by_genre_budget(cinema, size);
    
    /* Освобождение памяти */
    free_cinema_array(cinema);
    
    printf("\nProgram completed successfully.\n");
    return 0;
}
