#include "Arduino.h"
#include "pineDefinition.h"


void releSetup(){ 
  Serial.println();
  Serial.println("INICIO RELES");
	pinMode(releCorte, OUTPUT);
	digitalWrite(releCorte, LOW);

	pinMode(releInversorA, OUTPUT);
	digitalWrite(releInversorA, LOW);

	pinMode(releInversorB, OUTPUT);
	digitalWrite(releInversorB, LOW);

	pinMode(releStrobo, OUTPUT);
	digitalWrite(releStrobo, LOW);
  delay(5000);
  Serial.println("FIN INICIO RELES");
}

void conectarMecanica(){
	digitalWrite(releCorte, HIGH);
}

void desconectarMecanica(){
	digitalWrite(releCorte, LOW);
}

void conectarStrobo(){
  digitalWrite(releStrobo, HIGH);
}

void desconectarStrobo(){
  digitalWrite(releStrobo, LOW);
}

void activarSubida(){
  
	  digitalWrite(releInversorA, HIGH);
	  digitalWrite(releInversorB, HIGH);
  
}

void activarBajada(){
  
	  digitalWrite(releInversorA, LOW);
	  digitalWrite(releInversorB, LOW);
  
}
