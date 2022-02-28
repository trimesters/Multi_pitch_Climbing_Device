/**********************************************************************************************************
*
* @file     communication.h
* @brief    communication
* @author   Alois Boesch, Florian Kalb
* 
* @details  In this file the communication between the devices is defined and executed.
* @note     The pairing function still needs to be revised. Since errors can still occur.
            The length of the message must still be made variable. 
*
**********************************************************************************************************/

#ifndef COMMUNICATION_h

  #define COMMUNICATION_h

  #include "define.h"
  #include <Arduino.h>
  #include <util/atomic.h>
  #include <SoftwareSerial.h>  
  
  class Communication 
  {
    public:

      Communication(uint8_t txChannel_ = TX_CHANNEL, uint8_t rxChannel_ = RX_CHANNEL, uint8_t setPin_ = SET_PIN, uint32_t baudRate_ = BAUDRATE, uint16_t transferDelay_ = TRANSFER_DALAY);
      ~Communication();

      uint8_t searchNewPairing(volatile uint8_t*);
      uint8_t message_write_to_paired_device(char*);
      uint8_t message_read_from_paired_device(char* message);

      uint8_t set_message(char*);
    
    private:

      uint8_t message_build(char*);

      uint8_t message_write(void);
      uint8_t message_read(void);

      void get_message_value_from_messageRead(void);

      uint8_t get_pairing_value_from_messageRead(void);
      uint8_t set_pairing_value(uint8_t);

      uint8_t pairingPhaseOne(uint8_t*, uint8_t*, uint8_t*);
      uint8_t pairingPhaseTwo(uint8_t*, uint8_t*, uint8_t*);
      uint8_t pairingPhaseThree(uint8_t*, uint8_t*, uint8_t*);

      

      SoftwareSerial SerialIO;
      
      char messageRead[R_ARRAY_SIZE   + 1];                 
      char messageWrite[S_ARRAY_SIZE  + 1];             
      char pairingValue[P_ARRAY_SIZE  + 1];
      char messageValue[M_ARRAY_SIZE  + 1];

      char startChar;
      char stopChar;
      char checkBreak;

      uint16_t transferDelay;

  };

#endif /* COMMUNICATION_h */
