#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <ctype.h>  // Incluir ctype.h para usar tolower

// Funcion para recomendar peliculas basadas en uno o mas generos
void recomendar_peliculas(int argc, char *argv[]) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    
    // Construccion dinamica de la consulta SQL para manejar multiples generos
    char sql[1024] = "SELECT Pelicula.nombre, Pelicula.anio, Director.nombre, Estudio.nombre "
                     "FROM Pelicula "
                     "JOIN PeliculaGenero ON Pelicula.id = PeliculaGenero.pelicula_id "
                     "JOIN Genero ON PeliculaGenero.genero_id = Genero.id "
                     "JOIN Director ON Pelicula.director_id = Director.id "
                     "JOIN Estudio ON Pelicula.estudio_id = Estudio.id "
                     "WHERE LOWER(Genero.nombre) IN (";
    
    for (int i = 1; i < argc; i++) {
        strcat(sql, "?");
        if (i < argc - 1) {
            strcat(sql, ", ");
        }
    }
    strcat(sql, ");");

    // Abrir la base de datos
    int rc = sqlite3_open("peliculas.db", &db);
    if (rc) {
        fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Preparar la consulta SQL
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al preparar el SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Vincular los parametros de genero, insensible a mayusculas y minusculas
    for (int i = 1; i < argc; i++) {
        char lower_genre[100];
        for (int j = 0; argv[i][j]; j++) {
            lower_genre[j] = tolower(argv[i][j]);
        }
        lower_genre[strlen(argv[i])] = '\0';
        sqlite3_bind_text(stmt, i, lower_genre, -1, SQLITE_STATIC);
    }

    // Ejecutar la consulta y manejar los resultados
    int found = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        found = 1;
        const unsigned char *nombre = sqlite3_column_text(stmt, 0);
        int anio = sqlite3_column_int(stmt, 1);
        const unsigned char *director = sqlite3_column_text(stmt, 2);
        const unsigned char *estudio = sqlite3_column_text(stmt, 3);
        printf("Pelicula: %s, Ano: %d, Director: %s, Estudio: %s\n", nombre, anio, director, estudio);
    }

    if (!found) {
        printf("No se encontraron peliculas para los generos especificados.\n");
    }

    // Finalizar la declaracion y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <genero1> [<genero2> ... <generoN]\n", argv[0]);
        return 1;
    }

    recomendar_peliculas(argc, argv);

    return 0;
}
