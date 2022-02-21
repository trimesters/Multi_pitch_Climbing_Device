#include "define.h"
#include "communication.h"

Communication MpCD_SR;

void interrupt_init(void);
void set_pairing_flag(void);

uint8_t flag = 0;
char message[M_ARRAY_SIZE + 1];
volatile uint8_t pairingAktiv = 0; //Dieses Flag dient zum erkennen wenn das Gerät in den Pairing Modus kommt.

void setup() 
{
  interrupt_init();

  Serial.begin(9600);             //Debug
  while ( !Serial ) {;}

  randomSeed(analogRead(3));      //Initialisiert den Pseudozufallszahlengenerator

  pinMode(SET_PIN, OUTPUT);
  digitalWrite(SET_PIN, HIGH);
}

void loop() 
{
  if ( pairingAktiv == 2 )
  {

  }
  else if ( pairingAktiv == 1 )
  {
    if ( MpCD_SR.searchNewPairing(&pairingAktiv) == EXIT_SUCCESS )
    {
      pairingAktiv = 2;
      Serial.println((String)"Ende: " + pairingAktiv);
    }
  }
}
