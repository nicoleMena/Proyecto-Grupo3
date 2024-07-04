#include <stdio.h>
#include <sqlite3.h>

// Función para insertar una película en la base de datos
void insertar_pelicula(const char *nombre, int anio, int director_id, int estudio_id) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO Pelicula (nombre, anio, director_id, estudio_id) VALUES (?, ?, ?, ?)";

    if (sqlite3_open("peliculas.db", &db) != SQLITE_OK) {
        fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Error al preparar el SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, anio);
    sqlite3_bind_int(stmt, 3, director_id);
    sqlite3_bind_int(stmt, 4, estudio_id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Error al insertar datos: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Película insertada correctamente\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

// Función para actualizar una película en la base de datos
void actualizar_pelicula(int id, const char *nombre, int anio, int director_id, int estudio_id) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE Pelicula SET nombre = ?, anio = ?, director_id = ?, estudio_id = ? WHERE id = ?";

    if (sqlite3_open("peliculas.db", &db) != SQLITE_OK) {
        fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Error al preparar el SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, anio);
    sqlite3_bind_int(stmt, 3, director_id);
    sqlite3_bind_int(stmt, 4, estudio_id);
    sqlite3_bind_int(stmt, 5, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Error al actualizar datos: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Película actualizada correctamente\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

// Función para eliminar una película de la base de datos
void eliminar_pelicula(int id) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM Pelicula WHERE id = ?";

    if (sqlite3_open("peliculas.db", &db) != SQLITE_OK) {
        fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Error al preparar el SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Error al eliminar datos: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Película eliminada correctamente\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

