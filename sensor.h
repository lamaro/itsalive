#include "Arduino.h"
#include "pineDefinition.h"


void sensorSetup(){
  Serial.println("INICIO SENSOR");
	pinMode(sensorPin, INPUT);
	pinMode(sensorPinTrigger, OUTPUT);
	digitalWrite(sensorPinTrigger, LOW);
  delay(10000);
  Serial.println("FIN INICIO SENSOR");
}

int capturarMovimiento(){
	long duration;
	int distance;
	digitalWrite(sensorPinTrigger, HIGH);
	delayMicroseconds(10); //Quitar este delay!!!!!!!!!!!
	digitalWrite(sensorPinTrigger, LOW);
	// Reads the echoPin, returns the sound wave travel time in microseconds
	duration = pulseIn(sensorPin, HIGH);
	// Calculating the distance
	distance= duration*0.034/2;
	// Prints the distance on the Serial Monitor
	return distance;
}
