-- Agregar directores
INSERT INTO Director (nombre) VALUES ('Quentin Tarantino');
INSERT INTO Director (nombre) VALUES ('Steven Spielberg');
INSERT INTO Director (nombre) VALUES ('Christopher Nolan');
INSERT INTO Director (nombre) VALUES ('Martin Scorsese');
INSERT INTO Director (nombre) VALUES ('Ridley Scott');

-- Agregar estudios cinematograficos
INSERT INTO Estudio (nombre) VALUES ('Miramax');
INSERT INTO Estudio (nombre) VALUES ('Universal Pictures');
INSERT INTO Estudio (nombre) VALUES ('Warner Bros');
INSERT INTO Estudio (nombre) VALUES ('Paramount Pictures');
INSERT INTO Estudio (nombre) VALUES ('20th Century Fox');

-- Agregar generos
INSERT INTO Genero (nombre) VALUES ('Comedia');
INSERT INTO Genero (nombre) VALUES ('Drama');
INSERT INTO Genero (nombre) VALUES ('Accion');
INSERT INTO Genero (nombre) VALUES ('Ciencia Ficcion');
INSERT INTO Genero (nombre) VALUES ('Thriller');

-- Agregar peliculas
INSERT INTO Pelicula (nombre, anio, director_id, estudio_id) VALUES 
('Pulp Fiction', 1994, 1, 1),
('Jurassic Park', 1993, 2, 2),
('Schindlers List', 1993, 2, 2),
('Inglourious Basterds', 2009, 1, 1),
('The Dark Knight', 2008, 3, 3),
('The Wolf of Wall Street', 2013, 4, 4),
('Gladiator', 2000, 5, 5),
('Alien', 1979, 5, 5),
('Inception', 2010, 3, 3),
('Django Unchained', 2012, 1, 1);

-- Asignar generos a las películas
INSERT INTO PeliculaGenero (pelicula_id, genero_id) VALUES
(3, 3), -- Se le asigna uno o mas generos a cada pelicula
(4, 1),  
(4, 2), 
(5, 2), 
(6, 1),  
(6, 2), 
(7, 1),  
(7, 4),  
(8, 2),  
(8, 5),  
(9, 1),  
(9, 2),  
(10, 1), 
(10, 4), 
(11, 1), 
(11, 4),
(12, 1), 
(12, 2); 
