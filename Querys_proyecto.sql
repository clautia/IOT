
ALTER TABLE Proyectos
MODIFY COLUMN idProyectos INT AUTO_INCREMENT;

INSERT INTO Proyectos (Nombre, Descripcion, Dis_geografica)
VALUES
    ('Proyecto Innovacion Tech', 'Impulsando la innovacion tecnologica. Incluye desarrollo de software y hardware.', 'Sala de servidores 1, Edificio A'),
    ('Proyecto EcoSostenible', 'Desarrollo sostenible y conservacion ambiental. Enfoque en energias limpias y eficiencia energetica.', 'Edificio B, Piso 3, Oficina 302'),
    ('Proyecto SmartFactory', 'Fabrica inteligente para la produccion eficiente. Automatizacion y control en tiempo real.', 'Planta de produccion, Area de ensamblaje 1'),
    ('Proyecto Logistica 4.0', 'Optimizacion de la cadena de suministro con tecnologia de vanguardia. Seguimiento en tiempo real.', 'Sucursal central, Ciudad de Nueva York'),
    ('Proyecto SaludConectada', 'Transformacion de la atencion medica con dispositivos medicos inteligentes. Telemedicina y salud accesible.', 'Hospital General, Sala de Pacientes');

ALTER TABLE Microcontroladores
MODIFY COLUMN idMicrocontroladores INT AUTO_INCREMENT;

INSERT INTO Microcontroladores (Nombre, API_Hostname, Tipo_microcontrolador, Ubicacion_geografica, API_puerto)
VALUES
    ('NanoControl 2000', 'nanocontrol2000.local', 'Controlador de IoT', 'Sala de servidores 1, Edificio A', 8080),
    ('MegaSense Pro', 'megasensepro.local', 'Sensor de Ambiente', 'Edificio B, Laboratorio 302', 9090),
    ('SmartGate X', 'smartgatex.local', 'Controlador de Seguridad', 'Planta de producción, Área de acceso 1', 7070),
    ('EcoLink 5000', 'ecolink5000.local', 'Controlador de Energía', 'Sucursal central, Ciudad de Nueva York', 6060),
    ('HealthMonitor 300', 'healthmonitor300.local', 'Monitor de Salud', 'Hospital General, Sala de Pacientes', 5050);


SELECT * FROM Microcontroladores;

ALTER TABLE Proyecto_Micro
MODIFY COLUMN idProyecto_Micro INT AUTO_INCREMENT;

INSERT INTO Proyecto_Micro (id_Proyectos, Id_Micro)
VALUES
    (1, 1), -- Asociar Proyecto 1 con Microcontrolador 1
    (2, 2), -- Asociar Proyecto 2 con Microcontrolador 2
    (3, 3), -- Asociar Proyecto 3 con Microcontrolador 3
    (4, 4), -- Asociar Proyecto 4 con Microcontrolador 4
    (5, 5); -- Asociar Proyecto 5 con Microcontrolador 5

ALTER TABLE SenAct
MODIFY COLUMN IdSenAct INT AUTO_INCREMENT;

INSERT INTO SenAct (Nombre, Puerto_Pin, Ubicacion_geografica)
VALUES
    ('Sensor de Temperatura', 'T1', 'Sala de servidores 1'),
    ('Actuador de Iluminacion', 'A2', 'Edificio A, Piso 3, Oficina 302'),
    ('Sensor de Humedad', 'H1', 'Planta de produccion, Area de ensamblaje 1'),
    ('Actuador de Ventilacion', 'V2', 'Sucursal central, Ciudad de Nueva York'),
    ('Sensor de Presion', 'P1', 'Laboratorio de Investigacion, Laboratorio 101'),
    ('Actuador de Calefaccion', 'C3', 'Edificio B, Sala de Control');


ALTER TABLE Datos
MODIFY COLUMN idDatos INT AUTO_INCREMENT;

--este no va a ser necesario ya que cambie la configuracion en workbench
ALTER TABLE Datos
MODIFY COLUMN Datos INT;

--esta era una prueba para ver como se introducian los datos
INSERT INTO Datos (id_Micro, Id_Sen_Act, Fecha, Datos, Unidad)
VALUES
    (1, 1, '2023-10-01', 25.5, 'Celsius'),
    (2, 2, '2023-10-01', 100.2, 'Kilopascals'),
    (3, 3, '2023-10-01', 35.8, 'Voltios'),
    (4, 4, '2023-10-01', 50.1, 'Porcentaje'),
    (5, 5, '2023-10-01', 10.5, 'Lumenes');

--hice un codigo en c++ para que me generara los datos
INSERT INTO Datos (id_Micro, Id_Sen_Act, Fecha, Datos, Unidad)
VALUES
    (2, 2, '2023-03-12', 26.9, 'Kilopascals'),
    (3, 3, '2023-10-31', 28.1, 'Voltios'),
    (4, 4, '2023-04-26', 27.1, 'Porcentaje'),
    (5, 5, '2023-06-04', 64.2, 'Lumenes'),
    (1, 1, '2023-12-20', 62.9, 'Celsius'),
    (2, 2, '2023-09-01', 87.7, 'Kilopascals'),
    (3, 3, '2023-06-31', 13.5, 'Voltios'),
    (4, 4, '2023-08-14', 37.5, 'Porcentaje'),
    (5, 5, '2023-07-30', 56.5, 'Lumenes'),
    (1, 1, '2023-09-05', 55.0, 'Celsius'),
    (2, 2, '2023-11-24', 60.9, 'Kilopascals'),
    (3, 3, '2023-07-13', 18.4, 'Voltios'),
    (4, 4, '2023-12-04', 36.6, 'Porcentaje'),
    (5, 5, '2023-04-23', 40.0, 'Lumenes'),
    (1, 1, '2023-07-14', 68.4, 'Celsius'),
    (2, 2, '2023-08-20', 35.3, 'Kilopascals'),
    (3, 3, '2023-10-02', 45.3, 'Voltios'),
    (4, 4, '2023-03-11', 36.6, 'Porcentaje'),
    (5, 5, '2023-12-11', 69.2, 'Lumenes'),
    (1, 1, '2023-06-23', 66.8, 'Celsius'),
    (2, 2, '2023-05-18', 29.3, 'Kilopascals'),
    (3, 3, '2023-04-15', 91.9, 'Voltios'),
    (4, 4, '2023-04-08', 68.8, 'Porcentaje'),
    (5, 5, '2023-01-26', 56.3, 'Lumenes'),
    (1, 1, '2023-03-11', 22.9, 'Celsius'),
    (2, 2, '2023-03-10', 72.9, 'Kilopascals'),
    (3, 3, '2023-06-26', 22.0, 'Voltios'),
    (4, 4, '2023-03-03', 83.1, 'Porcentaje'),
    (5, 5, '2023-07-05', 37.1, 'Lumenes'),
    (1, 1, '2023-03-27', 88.5, 'Celsius'),
    (2, 2, '2023-11-18', 81.6, 'Kilopascals'),
    (3, 3, '2023-04-26', 33.5, 'Voltios'),
    (4, 4, '2023-09-17', 52.2, 'Porcentaje'),
    (5, 5, '2023-04-16', 64.7, 'Lumenes'),
    (1, 1, '2023-02-25', 35.3, 'Celsius'),
    (2, 2, '2023-11-02', 17.0, 'Kilopascals'),
    (3, 3, '2023-07-05', 87.4, 'Voltios'),
    (4, 4, '2023-08-07', 70.0, 'Porcentaje'),
    (5, 5, '2023-12-13', 82.3, 'Lumenes'),
    (1, 1, '2023-03-24', 80.9, 'Celsius'),
    (2, 2, '2023-05-13', 20.8, 'Kilopascals'),
    (3, 3, '2023-03-30', 42.8, 'Voltios'),
    (4, 4, '2023-03-24', 65.3, 'Porcentaje'),
    (5, 5, '2023-02-30', 24.9, 'Lumenes'),
    (1, 1, '2023-09-04', 41.6, 'Celsius'),
    (2, 2, '2023-08-23', 83.9, 'Kilopascals'),
    (3, 3, '2023-10-11', 86.9, 'Voltios'),
    (4, 4, '2023-07-29', 86.1, 'Porcentaje'),
    (5, 5, '2023-11-25', 18.0, 'Lumenes'),
    (1, 1, '2023-05-08', 31.9, 'Celsius'),
    (2, 2, '2023-05-31', 94.4, 'Kilopascals'),
    (3, 3, '2023-05-18', 44.9, 'Voltios'),
    (4, 4, '2023-12-11', 55.4, 'Porcentaje'),
    (5, 5, '2023-08-18', 94.7, 'Lumenes'),
    (1, 1, '2023-01-31', 29.0, 'Celsius'),
    (2, 2, '2023-03-31', 51.4, 'Kilopascals'),
    (3, 3, '2023-06-22', 44.5, 'Voltios'),
    (4, 4, '2023-05-31', 20.6, 'Porcentaje'),
    (5, 5, '2023-02-27', 52.5, 'Lumenes'),
    (1, 1, '2023-02-15', 77.3, 'Celsius'),
    (2, 2, '2023-01-15', 83.5, 'Kilopascals'),
    (3, 3, '2023-01-19', 52.8, 'Voltios'),
    (4, 4, '2023-08-16', 98.7, 'Porcentaje'),
    (5, 5, '2023-04-23', 83.3, 'Lumenes'),
    (1, 1, '2023-10-26', 61.3, 'Celsius'),
    (2, 2, '2023-05-15', 58.1, 'Kilopascals'),
    (3, 3, '2023-07-22', 80.6, 'Voltios'),
    (4, 4, '2023-07-19', 26.3, 'Porcentaje'),
    (5, 5, '2023-07-14', 45.1, 'Lumenes'),
    (1, 1, '2023-11-15', 29.4, 'Celsius'),
    (2, 2, '2023-09-15', 50.0, 'Kilopascals'),
    (3, 3, '2023-06-26', 27.9, 'Voltios'),
    (4, 4, '2023-04-15', 85.6, 'Porcentaje'),
    (5, 5, '2023-12-02', 98.6, 'Lumenes'),
    (1, 1, '2023-01-18', 81.8, 'Celsius'),
    (2, 2, '2023-02-02', 66.6, 'Kilopascals'),
    (3, 3, '2023-07-07', 37.1, 'Voltios'),
    (4, 4, '2023-09-10', 70.0, 'Porcentaje'),
    (5, 5, '2023-02-08', 61.6, 'Lumenes'),
    (1, 1, '2023-02-25', 19.8, 'Celsius'),
    (2, 2, '2023-03-05', 56.4, 'Kilopascals'),
    (3, 3, '2023-03-08', 75.9, 'Voltios'),
    (4, 4, '2023-02-22', 23.1, 'Porcentaje'),
    (5, 5, '2023-07-22', 33.5, 'Lumenes'),
    (1, 1, '2023-01-26', 11.8, 'Celsius'),
    (2, 2, '2023-01-30', 66.9, 'Kilopascals'),
    (3, 3, '2023-04-02', 60.2, 'Voltios'),
    (4, 4, '2023-12-23', 26.2, 'Porcentaje'),
    (5, 5, '2023-09-30', 65.6, 'Lumenes'),
    (1, 1, '2023-09-17', 40.8, 'Celsius'),
    (2, 2, '2023-01-31', 19.0, 'Kilopascals'),
    (3, 3, '2023-02-17', 73.9, 'Voltios'),
    (4, 4, '2023-07-30', 68.1, 'Porcentaje'),
    (5, 5, '2023-08-17', 90.5, 'Lumenes'),
    (1, 1, '2023-04-31', 34.3, 'Celsius');

SELECT Nombre, Dis_geografica AS Localizacion
FROM Proyectos;

ALTER TABLE Datos
MODIFY COLUMN Datos FLOAT;
--Mostrar los microcontroladores y actuadores relacionados

SELECT Distinct
	Microcontroladores.nombre AS Microcontrolador,
    SenAct.nombre AS Sensor_actuador
FROM microcontroladores
JOIN Datos ON datos.id_Micro = microcontroladores.idMicrocontroladores
JOIN SenAct ON SenAct.idSenAct =datos.id_Sen_Act;

--4.-Mostrar nombres de proyecto, microcontrolador, actuador/sensor y dato.
------------------------------------------
SELECT
    P.Nombre AS NombreProyecto,
    M.Nombre AS NombreMicrocontrolador,
    SA.Nombre AS NombreSensorActuador,
    GROUP_CONCAT(D.Datos ORDER BY D.Fecha ASC SEPARATOR ', ') AS DatosRegistrados
FROM
    Proyectos P
JOIN
    Proyecto_Micro PM ON P.idProyectos = PM.id_Proyectos
JOIN
    Microcontroladores M ON PM.Id_Micro = M.idMicrocontroladores
JOIN
    Datos D ON M.idMicrocontroladores = D.id_Micro
JOIN
    SenAct SA ON D.Id_Sen_Act = SA.idSenAct
GROUP BY
    P.Nombre, M.Nombre, SA.Nombre
ORDER BY
    NombreProyecto, NombreMicrocontrolador, NombreSensorActuador;

------AGRUPAR SENSOR CON PROYECTO
SELECT 
    P.Nombre AS NombreProyecto,
    GROUP_CONCAT(SA.Nombre ORDER BY SA.Nombre ASC SEPARATOR ', ') AS Sensores
FROM
    Proyectos P
JOIN
    Proyecto_Micro PM ON P.idProyectos = PM.id_Proyectos
JOIN
    Microcontroladores M ON PM.Id_Micro = M.idMicrocontroladores
JOIN
    Datos D ON M.idMicrocontroladores = D.id_Micro
JOIN
    SenAct SA ON D.Id_Sen_Act = SA.idSenAct
GROUP BY
    P.Nombre
ORDER BY
    NombreProyecto;

    ----Valor Maximo, minimo y promedio de el sensor de humedad
    SELECT
    P.Nombre AS NombreProyecto,
    SA.Nombre AS NombreSensor,
    MAX(D.Datos) AS ValorMaximo,
    MIN(D.Datos) AS ValorMinimo,
    AVG(D.Datos) AS ValorPromedio
FROM
    Proyectos P
JOIN
    Proyecto_Micro PM ON P.idProyectos = PM.id_Proyectos
JOIN
    Microcontroladores M ON PM.Id_Micro = M.idMicrocontroladores
JOIN
    Datos D ON M.idMicrocontroladores = D.id_Micro
JOIN
    SenAct SA ON D.Id_Sen_Act = SA.idSenAct
WHERE
    SA.Nombre = 'Sensor de Humedad'
GROUP BY
    P.Nombre, SA.Nombre
ORDER BY
    NombreProyecto, NombreSensor;

SELECT
    P.Nombre AS NombreProyecto,
    SA.Nombre AS NombreSensor,
    MAX(D.Datos) AS ValorMaximo,
    MIN(D.Datos) AS ValorMinimo,
    AVG(D.Datos) AS ValorPromedio
FROM
    Proyectos P
JOIN
    Proyecto_Micro PM ON P.idProyectos = PM.id_Proyectos
JOIN
    Microcontroladores M ON PM.Id_Micro = M.idMicrocontroladores
JOIN
    Datos D ON M.idMicrocontroladores = D.id_Micro
JOIN
    SenAct SA ON D.Id_Sen_Act = SA.idSenAct
WHERE
    SA.Nombre = 'Sensor de Presion'
GROUP BY
    P.Nombre, SA.Nombre
ORDER BY
    NombreProyecto, NombreSensor;

----Ordenar por Nombre de proyecto, sensor, ubicacion del sensor y datos leidos del sensor

SELECT
    P.Nombre AS NombreProyecto,
    SA.Nombre AS NombreSensor,
    SA.Ubicacion_geografica AS UbicacionGeografica,
    GROUP_CONCAT(D.Datos ORDER BY D.Fecha ASC SEPARATOR ', ') AS Datos
FROM
    Proyectos P
JOIN
    Proyecto_Micro PM ON P.idProyectos = PM.id_Proyectos
JOIN
    Microcontroladores M ON PM.Id_Micro = M.idMicrocontroladores
JOIN
    Datos D ON M.idMicrocontroladores = D.id_Micro
JOIN
    SenAct SA ON D.Id_Sen_Act = SA.idSenAct
GROUP BY
    NombreProyecto, NombreSensor, UbicacionGeografica
ORDER BY
    NombreProyecto, NombreSensor, UbicacionGeografica;

--Insertar un dato nulo
INSERT INTO Datos (id_Micro, Id_Sen_Act, Fecha, Datos, Unidad)
VALUES
    (2, 2, '2023-03-12', NULL , 'Kilopascals');
--Crear una vista
CREATE OR REPLACE VIEW ProyectoMicroActSenDato AS
SELECT
    P.Nombre AS NombreProyecto,
    M.Nombre AS NombreMicrocontrolador,
    SA.Nombre AS NombreSensorActuador,
    GROUP_CONCAT(D.Datos ORDER BY D.Fecha ASC SEPARATOR ', ') AS DatosRegistrados
FROM
    Proyectos P
JOIN
    Proyecto_Micro PM ON P.idProyectos = PM.id_Proyectos
JOIN
    Microcontroladores M ON PM.Id_Micro = M.idMicrocontroladores
JOIN
    Datos D ON M.idMicrocontroladores = D.id_Micro
JOIN
    SenAct SA ON D.Id_Sen_Act = SA.idSenAct
GROUP BY
    P.Nombre
ORDER BY
    NombreProyecto, NombreMicrocontrolador, NombreSensorActuador;
--Ver los datos de la vista
SELECT * FROM ProyectoMicroActSenDato;

-- 2.Contar la cantidad de datos por sensor usando la vista de 1 (ESTE ESTA BIEN, PERO NO ES LO QUE PIDE)

SELECT NombreSensorActuador,
       (CHAR_LENGTH(DatosRegistrados) - CHAR_LENGTH(REPLACE(DatosRegistrados, ',', '')) + 1) AS CantidadDatos
FROM ProyectoMicroActSenDato;

--Agregar un microcontrolador nuevo
INSERT INTO Microcontroladores (Nombre, API_Hostname, Tipo_microcontrolador, Ubicacion_geografica, API_puerto)
VALUES
    ('ABT 800', 'nanocontrol.local', 'Controlador', 'Sala de servidores 10, Edificio b', 8070);

--Insertar microcontroladores que no se relacionen con un sensor
INSERT INTO Datos (id_Micro, Fecha, Datos, Unidad)
VALUES
    (6, '2023-06-11', 26.9, 'Kilopascals');
--Contar los registros de microcontroladores sin sensor
SELECT COUNT(*) AS Microcontroladores_sin_sensores
FROM Datos
WHERE Id_Sen_Act = 0;

--creamos SENSOR SIN DATOS
--Creamos una fila donde los datos del sensor sean nulos
INSERT INTO Datos (id_Micro, Id_Sen_Act, Datos)
VALUES
    (1,1, NULL);
--Contamos el numero de registros donde los datos sean nulos
SELECT COUNT(*) AS Registors_sin_datos
FROM DATOS
WHERE Datos IS NULL;
