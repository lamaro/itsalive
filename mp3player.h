#include "Arduino.h"
#include "pineDefinition.h"

static unsigned long timer = 0;
bool primeraRep = 1;
void mp3PlayerSetup(){
	mySoftwareSerial.begin(9600);
  
  Serial.println();
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(5);  //Set volume value. From 0 to 30
}

void reproducirAudio(int nroAudio, unsigned long duracionAudio){
  static unsigned long timer = millis();
    if (millis() - timer > duracionAudio || primeraRep) {
      primeraRep = 0;
      timer = millis();
      myDFPlayer.play(nroAudio);
    }
}
