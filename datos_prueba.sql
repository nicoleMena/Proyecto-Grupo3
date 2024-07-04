-- Agregar directores
INSERT INTO Director (nombre) VALUES ('Quentin Tarantino');
INSERT INTO Director (nombre) VALUES ('Steven Spielberg');
INSERT INTO Director (nombre) VALUES ('Christopher Nolan');
INSERT INTO Director (nombre) VALUES ('Martin Scorsese');
INSERT INTO Director (nombre) VALUES ('Ridley Scott');
INSERT INTO Director (nombre) VALUES ('Tim Burton');  
INSERT INTO Director (nombre) VALUES ('James Cameron');
INSERT INTO Director (nombre) VALUES ('Hayao Miyazaki');
INSERT INTO Director (nombre) VALUES ('John Carpenter');

-- Agregar estudios cinematográficos
INSERT INTO Estudio (nombre) VALUES ('Miramax');
INSERT INTO Estudio (nombre) VALUES ('Universal Pictures');
INSERT INTO Estudio (nombre) VALUES ('Warner Bros');
INSERT INTO Estudio (nombre) VALUES ('Paramount Pictures');
INSERT INTO Estudio (nombre) VALUES ('20th Century Fox');
INSERT INTO Estudio (nombre) VALUES ('Disney'); 
INSERT INTO Estudio (nombre) VALUES ('Studio Ghibli');
INSERT INTO Estudio (nombre) VALUES ('20th Century Studios');

-- Agregar géneros
INSERT INTO Genero (nombre) VALUES ('Comedia');
INSERT INTO Genero (nombre) VALUES ('Drama');
INSERT INTO Genero (nombre) VALUES ('Accion');
INSERT INTO Genero (nombre) VALUES ('Ficcion');
INSERT INTO Genero (nombre) VALUES ('Thriller');
INSERT INTO Genero (nombre) VALUES ('Terror');
INSERT INTO Genero (nombre) VALUES ('Animada');

-- Agregar películas
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
('Django Unchained', 2012, 1, 1),
('The Nightmare Before Christmas', 1993, 6, 6), 
('Coraline', 2009, 6, 6), 
('Titanic', 1997, 7, 5),
('Spirited Away', 2001, 8, 7),
('The Thing', 1982, 9, 5),
('Avatar', 2009, 7, 5),
('My Neighbor Totoro', 1988, 8, 7),
('Halloween', 1978, 9, 3);

-- Asignar géneros a las películas
INSERT INTO PeliculaGenero (pelicula_id, genero_id) VALUES
(1, 5), -- Se le asigna uno o mas generos a cada pelicula
(2, 2),
(3, 2),
(4, 5),
(5, 3),
(6, 1),
(7, 4),
(8, 6),
(9, 4),
(10, 1),
(11, 7),  
(12, 7),  
(12, 6),  
(13, 2),  
(14, 7),  
(15, 6),  
(16, 4),  
(17, 7),  
(18, 6); 
