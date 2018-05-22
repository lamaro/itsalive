#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#ifndef _PIN_DEFS_
#define _PIN_DEFS_

//MAQUINA DE ESTADOS

#define TEST 10 // Estado de prueba
#define REPOSO 1 // Franky esta acostado, sensor espera persona, sonido resporacion, flash strobo off.
#define SUBE 2 // Franky sube, sonido terror, flash strobo on.
#define MANTIENE 4 // Franky se mantiene arriba, sonido terror, flash strobo on.
#define BAJA 8 // Franky baja, sonido terror u otro, flash strobo on.
int action = REPOSO; //Cambiar estado inicial REPOSO o TEST para pruebas

//PINES DE SENSOR
const int sensorPin = 2; //Sensor Ultrasonido - Echo
const int sensorPinTrigger = 3; //Sensor Ultrasonido - Trigger

//PINES DE 4 RELAY MODULE
const int releCorte = 4; //Rele 1 - Funcion de Corte Fuente 24V
const int releInversorA = 5; //Rele 1 - Funcion de Corte Fuente 24V
const int releInversorB = 6; //Rele 1 - Funcion de Corte Fuente 24V
const int releStrobo = 7; //Rele 1 - Funcion de Corte Fuente 24V

//PINES DE MP3 PLAYER

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

#endif
