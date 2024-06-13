#include <sqlite3.h>
#include <stdio.h>   
#include <stdlib.h>  

// Funcion para crear las tablas necesarias en la base de datos
void crear_tablas(sqlite3 *db) {
    // Consulta SQL para crear las tablas
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

    char *err_msg = 0; // Almacenar mensajes de error
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg); // Ejecuta la consulta SQL

    // Verificar error
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg); 
        sqlite3_free(err_msg); // Libera la memoria del mensaje de error
        exit(1); // Terminar el programa con un codigo de error
    }
}

int main(void) {
    sqlite3 *db; 
    int rc = sqlite3_open("peliculas.db", &db); // Abrir base de datos

    // Verifica si hubo un error al abrir la base de datos
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db)); // Muestra el mensaje de error
        return 1; 
    }

    crear_tablas(db); // Llamar funcion para crear las tablas
    sqlite3_close(db); // Cerrar la base de datos
    return 0;
}
