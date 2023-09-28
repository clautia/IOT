--Query
insert into ENROLLED (STUDENT, COURSE, GPA) SELECT idStudents, idCourses, (RAND()*(5-0) +0) FROM COURSES, students;

--Maximo
SELECT 
    Students.name, Courses.name, MAX(enrolled.gpa)
FROM 
    Enrolled
LEFT JOIN students ON Students.idStudents=Enrolled.student
LEFT JOIN courses ON courses.idCourses=Enrolled.course;

--Minimo
SELECT 
    Students.name, Courses.name, MIN(enrolled.gpa)
FROM 
    Enrolled
LEFT JOIN students ON Students.idStudents=Enrolled.student
LEFT JOIN courses ON courses.idCourses=Enrolled.course;

--Select with a gpa over 3
SELECT
    Courses.name, Students.name, Enrolled.gpa
FROM
Enrolled
LEFT JOIN Courses ON Courses.idCourses =Enrolled.course
LEFT JOIN Students ON Students.idStudents = Enrolled.student
WHERE 
enrolled.gpa > 3
GROUP BY Courses.name, Students.name; 

-- Agrupar por el valor maximo de todas las materias
SELECT
Courses.name, Students.name,MAX(enrolled.gpa)
FROM
Enrolled
    LEFT JOIN Courses ON Courses.idCourses =Enrolled.course
    LEFT JOIN Students ON Students.idStudents = Enrolled.student
GROUP BY Courses.name;

--Te marca error cuanto intenntas cmabiar algo que no esta por orden

--Cambiar el nombre del encabezado de las tablas
SELECT
Courses.name AS Curso, Students.name AS Student, MAX(enrolled.gpa)
FROM
Enrolled
    LEFT JOIN Courses ON Courses.idCourses =Enrolled.course
    LEFT JOIN Students ON Students.idStudents = Enrolled.student
GROUP BY Courses.name;


--Buscar a los que se llaman Tony en el LIKE se usa % en WHERE name = 'Tony'
SELECT * FROM students WHERE name LIKE '%Tony%';

SELECT * FROM enrolled WHERE student = 1;

--Ordenar los datos por cierto campo por jemeplo la edad
SELECT * FROM students ORDER BY age ;
SELECT * FROM students ORDER BY age ASC;  --para orden ascendente
SELECT * FROM students ORDER BY age DESC; --para orden descendente

--EStudinate y sus respectivas caliifcaciones
SELECT 
    student,course, gpa
FROM 
enrolled
GROUP BY student, course;

--Un sub query es sacar una seleccion o proyeccion de otro query, se puede visualizar ocmo si fuera otra tabla.
--SE PUEDE ENCAPUSALR UN QUERY
------------------PASO 1-------------------------------
SELECT
*
FROM 
(SELECT
    student, course, gpa
FROM
    Enrolled
GROUP BY student, course) AS table2;

--------------------PASO 2------------------------------

SELECT
*
FROM 
(SELECT
    student, course, gpa
FROM
    Enrolled
GROUP BY student, course) AS grouped
WHERE 
student=1;

---------------------PASO 3-------------------------

SELECT
student, avg(gpa)
FROM 
(SELECT
    student, course, gpa
FROM
    Enrolled
GROUP BY student, course) AS grouped
GROUP BY student;

--Contar el registro
SELECT COUNT(*) FROM enrolled;
SELECT COUNT(*) AS conteo FROM enrolled;--Cambiar nombre a la tabla

--Cambair el ultimo registro de enrolled
DELETE FROM Enrolled WHERE idEnrolled = '20';