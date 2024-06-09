INSERT INTO Director (nombre) VALUES ('Steven Spielberg'), ('Christopher Nolan');
INSERT INTO Estudio (nombre) VALUES ('Warner Bros'), ('Universal Pictures');
INSERT INTO Genero (nombre) VALUES ('Accion'), ('Drama'), ('Comedia');

INSERT INTO Pelicula (nombre, anio, director_id, estudio_id) VALUES 
('Jurassic Park', 1993, 1, 2),
('Inception', 2010, 2, 1);

INSERT INTO PeliculaGenero (pelicula_id, genero_id) VALUES
(1, 1), (1, 2),
(2, 1), (2, 2);
