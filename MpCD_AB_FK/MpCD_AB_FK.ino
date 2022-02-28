/**********************************************************************************************************
*
* @file     MpC_AB_FK.ino
* @brief    main
* @author   Alois Boesch, Florian Kalb
* 
* @details  The main of the program is listed here. It processes incoming commands and sends appropriate responses.
* @note     There are still debug functions stored.
*
**********************************************************************************************************/


#include "define.h"
#include "communication.h"

Communication MpCD_SR;

void interrupt_init(void);
void set_pairing_flag(void);

uint8_t flag = 0;
char message[M_ARRAY_SIZE + 1];
volatile uint8_t pairingAktiv = 0; 

void setup() 
{
  interrupt_init();

  Serial.begin(9600);             //Debug
  while ( !Serial ) {;}

  randomSeed(analogRead(3));   

  pinMode(SET_PIN, OUTPUT);
  digitalWrite(SET_PIN, HIGH);
}

void loop() 
{
  if ( pairingAktiv == 2 )
  {
    delay(1000);
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
