-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema Proyecto
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema Proyecto
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `Proyecto` DEFAULT CHARACTER SET utf8 ;
USE `Proyecto` ;

-- -----------------------------------------------------
-- Table `Proyectos`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Proyectos` (
  `idProyectos` INT NOT NULL,
  `Nombre` VARCHAR(45) NOT NULL,
  `Descripcion` VARCHAR(45) NOT NULL,
  `Dis_geografica` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idProyectos`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Proyecto_Micro`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Proyecto_Micro` (
  `idProyecto_Micro` INT NOT NULL,
  `id_Proyectos` INT NOT NULL,
  `Id_Micro` INT NOT NULL,
  PRIMARY KEY (`idProyecto_Micro`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Microcontroladores`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Microcontroladores` (
  `idMicrocontroladores` INT NOT NULL,
  `Nombre` VARCHAR(45) NOT NULL,
  `API` VARCHAR(45) NOT NULL,
  `Tipo_microcontrolador` VARCHAR(45) NOT NULL,
  `Ubicacion_geografica` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idMicrocontroladores`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Datos`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Datos` (
  `idDatos` INT NOT NULL,
  `id_Micro` INT NOT NULL,
  `Id_Sen_Act` INT NOT NULL,
  PRIMARY KEY (`idDatos`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `SenAct`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `SenAct` (
  `idSenAct` INT NOT NULL,
  `Dato` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idSenAct`))
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
