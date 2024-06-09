#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <glib.h>

void recomendar_peliculas(const char *genero) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = 
        "SELECT Pelicula.nombre, Pelicula.anio, Director.nombre, Estudio.nombre "
        "FROM Pelicula "
        "JOIN PeliculaGenero ON Pelicula.id = PeliculaGenero.pelicula_id "
        "JOIN Genero ON PeliculaGenero.genero_id = Genero.id "
        "JOIN Director ON Pelicula.director_id = Director.id "
        "JOIN Estudio ON Pelicula.estudio_id = Estudio.id "
        "WHERE Genero.nombre = ?";

    int rc = sqlite3_open("peliculas.db", &db);
    if (rc) {
        fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al preparar el SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, genero, -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *nombre = sqlite3_column_text(stmt, 0);
        int anio = sqlite3_column_int(stmt, 1);
        const unsigned char *director = sqlite3_column_text(stmt, 2);
        const unsigned char *estudio = sqlite3_column_text(stmt, 3);

        printf("Pelicula: %s, Año: %d, Director: %s, Estudio: %s\n", nombre, anio, director, estudio);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <genero>\n", argv[0]);
        return 1;
    }

    recomendar_peliculas(argv[1]);

    return 0;
}
