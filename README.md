# Sistema de Recomendación de Películas

## Descripción del Proyecto
Este proyecto es un sistema de recomendación de películas desarrollado en C, utilizando bibliotecas open source compatibles. El usuario puede seleccionar entre uno y tres géneros de películas en una interfaz gráfica. El sistema utiliza un algoritmo de recomendación que consulta una base de datos SQLite para sugerir películas basadas en los géneros seleccionados.

### Archivos del Proyecto
- `algoritmo_recomendacion.c`: Implementa el algoritmo de recomendación que filtra películas por género.
- `crear_base_datos.c`: Crea las tablas necesarias en la base de datos `peliculas.db`.
- `datos_prueba.sql`: Contiene datos de prueba para poblar la base de datos.
- `funciones_bd.c` y `funciones_bd.h`: Contienen funciones para manejar la base de datos, como insertar y actualizar películas.
- `funciones_ig.c` y `funciones_ig.h`: Contienen funciones para manejar la interfaz gráfica con GTK+.
- `interfaz.c`: Implementa la interfaz gráfica donde el usuario selecciona los géneros de películas.
- `Makefile`: Archivo de make que compila todos los componentes del proyecto.
- `peliculas.db`: Base de datos SQLite que almacena información sobre las películas.
- `pruebas_bd.c`: Contiene pruebas para verificar el correcto funcionamiento de las funciones de la base de datos.
- `contribucion.md`: Describe las convenciones de código y los mensajes de commit para el proyecto.

## Dependencias e Instalación
### Requisitos
- Compilador GCC
- Biblioteca GLib
- Biblioteca SQLite
- Biblioteca GTK+

### Instalación en Linux
1. **Instalar dependencias**:
   ```sh
   sudo apt-get update
   sudo apt-get install build-essential libglib2.0-dev libsqlite3-dev libgtk-3-dev
   ```
2. Clonar el repositorio:
    ```sh
    git clone https://github.com/nicoleMena/Proyecto-Grupo3.git
    cd Proyecto-Grupo3
    ```
3. Compilar el proyecto:
    ```sh
    make
    ```

### Pasos para Ejecución
1. Ejecutar la interfaz gráfica:
    ```sh
    ./interfaz
    ```
