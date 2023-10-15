-- 1. Crear más de 100 mil registros en datos

drop procedure if exists insertData;

DELIMITER //

CREATE PROCEDURE insertData()
    BEGIN
        DECLARE i INT DEFAULT 0;
        DECLARE previous_date DATETIME;

        WHILE i <= 100000 DO

            -- Calcula id_Micro e Id_Sen_Act de manera cíclica (1 a 5)

            SET @id_Micro_Sen_Act = (i % 5) + 1;

            -- Genera una fecha aleatoria que es mayor a la anterior

            SET @Fecha = IFNULL(
                DATE_ADD(previous_date, INTERVAL FLOOR(RAND() * 365) DAY),
                NOW() - INTERVAL FLOOR(RAND() * 365) DAY
            );
            
            -- Guarda la fecha actual como la previa para la próxima iteración

            SET previous_date = @Fecha;

            -- Genera Datos del valor 0 al 100

            SET @Datos = RAND() * 100;

            -- Determina Unidad con base en id_Micro e id_Sen_Act

            SET @Unidad = CASE @id_Micro_Sen_Act
                WHEN 1 THEN 'Celsius'
                WHEN 2 THEN 'Kilopascals'
                WHEN 3 THEN 'Voltios'
                WHEN 4 THEN 'Porcentaje'
                WHEN 5 THEN 'Lumenes'
            END;

            INSERT INTO datos (id_Micro, Id_Sen_Act, Fecha, Datos, Unidad)
            VALUES (@id_Micro_Sen_Act, @id_Micro_Sen_Act, @Fecha, @Datos, @Unidad);

            SET i = i + 1;
            
        END WHILE;
END;

//
DELIMITER ;

CALL insertData();

-- 2. Hacer un query a la tabla datos y registrar el tiempo.

SET @start_time = UNIX_TIMESTAMP();

SELECT *
FROM datos
WHERE YEAR(Fecha) BETWEEN 2023 AND 3000;

SET @end_time = UNIX_TIMESTAMP();
SET @query_time = @end_time - @start_time;

SELECT @query_time AS QueryTimeInSeconds;

SET @start_time = UNIX_TIMESTAMP();

SELECT *
FROM datos
WHERE id_Micro = 1;

SET @end_time = UNIX_TIMESTAMP();
SET @query_time = @end_time - @start_time;

SELECT @query_time AS QueryTimeInSeconds;

-- 3. Crear un índice a la tabla datos.

CREATE INDEX IF NOT EXISTS idx_Fecha ON datos (Fecha);
CREATE INDEX IF NOT EXISTS idx_id_Micro ON datos (id_Micro);

-- 4. Hacer un query a datos usando el índice y registrar tiempo.

SET @start_time = UNIX_TIMESTAMP();

SELECT *
FROM datos
FORCE INDEX (idx_Fecha)
WHERE YEAR(Fecha) BETWEEN 2023 AND 3000;

SET @end_time = UNIX_TIMESTAMP();
SET @query_time = @end_time - @start_time;

SELECT @query_time AS QueryTimeInSeconds;

SET @start_time = UNIX_TIMESTAMP();

SELECT *
FROM datos
FORCE INDEX (idx_id_Micro)
WHERE id_Micro = 1;

SET @end_time = UNIX_TIMESTAMP();
SET @query_time = @end_time - @start_time;

SELECT @query_time AS QueryTimeInSeconds;

-- 5. Hacer un query usando BETWEEN con la columna de fechas en la tabla datos.

SELECT *
FROM datos
WHERE YEAR(Fecha) BETWEEN 2050 AND 2051
ORDER BY Fecha;

-- 6. Hacer un query usando la cláusula IN.

SELECT *
FROM datos
WHERE id_Micro IN (2, 5);

-- 7. Consultar la tabla proyecto, microcontrolador sin usar la cláusula JOIN.

SELECT 
    P.Nombre AS Proyecto,
    M.Nombre AS Microcontrolador
FROM Proyectos P, Microcontroladores M
WHERE P.idProyectos IN (
    SELECT PM.id_Proyectos
    FROM Proyecto_Micro PM
    WHERE PM.Id_Micro = M.idMicrocontroladores
);