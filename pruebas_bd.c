#include <stdio.h>
#include <assert.h>
#include <sqlite3.h>
#include "funciones_bd.h"



void prueba_insertar() {
    // Inserta una película de prueba
    insertar_pelicula("Prueba", 2024, 1, 1);

    // Verifica que la película ha sido insertada
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM Pelicula WHERE nombre = 'Prueba'";

    if (sqlite3_open("peliculas.db", &db) != SQLITE_OK) {
        fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Error al preparar el SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        assert(count == 1);
    } else {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    prueba_insertar();
    printf("Todas las pruebas pasaron correctamente\n");
    return 0;
}
