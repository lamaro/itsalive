//Proyecto Franky
//Autor: Leandro Amaro García y Universidad Maimonides

#include "pineDefinition.h"
#include "sensor.h"
#include "reles.h"
#include "mp3player.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//Sensor Ultrasonico
unsigned long previousMillisSensor = 0;
const long intervaloSensor = 3000; //Cada cuanto tiempo lee el sensor
const int thresholdSensorUsuario = 150; //Distancia del usuario. En centimetros
const long tiempoReaccionInicial = 8000; //Tiempo que tarda en activarse el sensor al ingresar a REPOSO
unsigned long previoustiempoReaccionInicial = 0; //En milisegundos

//Mecanismo movimiento
unsigned long previousMillisReleCorte = 0;
const long intervaloReleCorteSubida = 5000;
const long intervaloReleCorteBajada = 8000;
unsigned long previousMillisMantieneArriba = 0;
const long intervaloSeMantieneArriba = 20000;

//Sonido

void setup() {
  Serial.begin(115200);
  sensorSetup();
  releSetup();
  mp3PlayerSetup();
}

void loop() {
  
  switch (action)
    {
    case TEST:
    {
    //ESTADO DE PRUEBA
    Serial.println("TEST");
    reproducirAudio(1,40000);
    //FIN ESTADO DE PRUEBA
    break;
    }
    case REPOSO:
    {
    //Sonido laboratorio
    reproducirAudio(1,40000);
    unsigned long currentTiempoReaccionInicial = millis();
    if(currentTiempoReaccionInicial - previoustiempoReaccionInicial >= tiempoReaccionInicial) { //Sube por 3 segundos
  		unsigned long currentMillisSensor = millis();
  		if(currentMillisSensor - previousMillisSensor >= intervaloSensor) { //comienza temporizador
  			previousMillisSensor = currentMillisSensor;   
  			int distanciaUsuario = capturarMovimiento();
  		    Serial.print("Distance: ");
  			Serial.println(distanciaUsuario);
  			if (distanciaUsuario <= thresholdSensorUsuario){
          previousMillisReleCorte = millis();
          bool primeraRep = 1;
  				action = SUBE;
          ;
  			}	
  		}//termina temporizador	
    }
  	break;
    }
    case SUBE:
    {
    	// Franky sube, sonido terror, flash strobo on.
      //Sonido laboratorio
      myDFPlayer.volume(15);  //Set volume value. From 0 to 30
      reproducirAudio(2,4000); 
    	unsigned long currentMillisReleCorte = millis();
  		if(currentMillisReleCorte - previousMillisReleCorte < intervaloReleCorteSubida) { //Sube por 3 segundos
        Serial.println("SUBE");
        conectarStrobo();
        activarSubida();
        conectarMecanica();
  		}else{
        desconectarMecanica();
        previousMillisMantieneArriba = millis();
        action = MANTIENE;
  		}//termina temporizador	
    	break;
    }
    case MANTIENE:
    {
      reproducirAudio(2,4000);
      unsigned long currentMillisMantieneArriba = millis();
      if(currentMillisMantieneArriba - previousMillisMantieneArriba < intervaloSeMantieneArriba) { //Se mantiene por 10 segundos
        Serial.println("MANTIENE");
      }else{
        previousMillisReleCorte = millis();
        action = BAJA;
      }//termina temporizador 
      break;
    }
    case BAJA:
    {
      reproducirAudio(2,4000);
      unsigned long currentMillisReleCorte = millis();
      if(currentMillisReleCorte - previousMillisReleCorte < intervaloReleCorteBajada) { //Sube por 3 segundos
        //previousMillisReleCorte = currentMillisReleCorte;
        Serial.println("BAJA");
        activarBajada();
        conectarMecanica();
      }else{
        desconectarStrobo();
        desconectarMecanica();
        primeraRep = 1;
        previoustiempoReaccionInicial = millis();
        myDFPlayer.volume(5);  //Set volume value. From 0 to 30
        action = REPOSO;
      }//termina temporizador 
      break;
    }
  }
}


