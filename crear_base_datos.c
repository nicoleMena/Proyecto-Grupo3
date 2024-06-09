#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

void crear_tablas(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS Pelicula ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "nombre TEXT NOT NULL, "
                      "anio INTEGER, "
                      "director_id INTEGER, "
                      "estudio_id INTEGER, "
                      "FOREIGN KEY (director_id) REFERENCES Director(id), "
                      "FOREIGN KEY (estudio_id) REFERENCES Estudio(id));"
                      "CREATE TABLE IF NOT EXISTS Genero ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "nombre TEXT NOT NULL);"
                      "CREATE TABLE IF NOT EXISTS PeliculaGenero ("
                      "pelicula_id INTEGER, "
                      "genero_id INTEGER, "
                      "FOREIGN KEY (pelicula_id) REFERENCES Pelicula(id), "
                      "FOREIGN KEY (genero_id) REFERENCES Genero(id));"
                      "CREATE TABLE IF NOT EXISTS Director ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "nombre TEXT NOT NULL);"
                      "CREATE TABLE IF NOT EXISTS Estudio ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "nombre TEXT NOT NULL);";

    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        exit(1);
    }
}

int main(void) {
    sqlite3 *db;
    int rc = sqlite3_open("peliculas.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    crear_tablas(db);
    sqlite3_close(db);
    return 0;
}
