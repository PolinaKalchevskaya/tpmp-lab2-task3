#ifndef CINEMA_H
#define CINEMA_H

/* Structure CINEMA for variant 35 */
typedef struct {
    char movie_title[100];
    char session_date[11];    /* DD.MM.YYYY */
    char session_time[6];      /* HH:MM */
    int duration_minutes;
    char genre[50];
    float budget;              /* million $ */
} CINEMA;

/* Function prototypes */
CINEMA* create_cinema_array(int size);
void print_max_min_duration(const CINEMA* cinema, int size);
void print_evening_short_movies(const CINEMA* cinema, int size);
void print_comedy_max_budget(const CINEMA* cinema, int size);
void sort_and_print_by_genre_budget(CINEMA* cinema, int size);
void free_cinema_array(CINEMA* cinema);

#endif
