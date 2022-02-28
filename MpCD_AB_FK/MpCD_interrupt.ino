/**********************************************************************************************************
*
* @file     MpC_interrupt.ino
* @brief    interrupt
* @author   Alois Boesch, Florian Kalb
* 
* @details  In this file the interrupt routines are written.
* @note     It is assumed that there is only one interrupt for all functions. 
            This terminates the deep sleep and then the corresponding key is queried. 
            It must only be determined whether the controller wakes up fast enough. 
*
**********************************************************************************************************/


volatile uint32_t lastInterruptTimePairing = 0;

//The x-axis is referenced in this interrupt routine.
void set_pairing_flag(void)
{ 
  uint32_t interruptTime = millis();
  
  if (((interruptTime - lastInterruptTimePairing) > 1000))
  {
    pairingAktiv = 1;
  }

  lastInterruptTimePairing = interruptTime;
}

////Initialization of the Interrupt
void interrupt_init(void) 
{
  attachInterrupt(digitalPinToInterrupt(TASTER_PAIRING), set_pairing_flag, CHANGE);
}
