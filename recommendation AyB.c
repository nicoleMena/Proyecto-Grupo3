#include <stdio.h>
#include <string.h>

typedef struct {
    char title[100];
    char genre[50];
} Movie;

void recommend_movies(const char *selected_genres[], int num_genres) {
    Movie movies[] = {
        {"Movie 1", "Action"},
        {"Movie 2", "Comedy"},
        {"Movie 3", "Drama"},
        {"Movie 4", "Horror"},
        {"Movie 5", "Romance"},
        {"Movie 6", "Action"},
        {"Movie 7", "Comedy"},
        {"Movie 8", "Drama"},
        {"Movie 9", "Horror"},
        {"Movie 10", "Romance"},
        {"Movie 11", "Action"},
        {"Movie 12", "Comedy"},
        {"Movie 13", "Drama"},
        {"Movie 14", "Horror"},
        {"Movie 15", "Romance"},
        {"Movie 16", "Action"},
        {"Movie 17", "Comedy"},
        {"Movie 18", "Drama"},
        {"Movie 19", "Horror"},
        {"Movie 20", "Romance"},
        {"Movie 21", "Action"},
        {"Movie 22", "Comedy"},
        {"Movie 23", "Drama"},
        {"Movie 24", "Horror"},
        {"Movie 25", "Romance"}
        
    };
    int num_movies = sizeof(movies) / sizeof(Movie);

    printf("Recommended movies:\n");
    for (int i = 0; i < num_genres; i++) {
        printf("\nGenre: %s\n", selected_genres[i]);
        int count = 0;
        for (int j = 0; j < num_movies && count < 5; j++) {
            if (strstr(movies[j].genre, selected_genres[i])) {
                printf("%d. %s\n", count + 1, movies[j].title);
                count++;
            }
        }
        if (count < 5) {
            for (int k = count; k < 5; k++) {
                printf("%d. No movie available\n", k + 1);
            }
        }
    }
}

// fin del codigo
