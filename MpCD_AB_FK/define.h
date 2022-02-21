#ifndef DEFINE_h

  #define DEFINE_h

  #include "Arduino.h"
  
  #define SET_PIN               12
  #define RX_CHANNEL            10
  #define TX_CHANNEL            11
  #define BAUDRATE              9600 
  #define TRANSFER_DALAY        500
  #define USE_CHECK_SUM         1

  #define INITIALIZATION_VALUE  '0'
  #define END_OF_STRING         '\0'
  #define ACKNOWLEDGE           "acknowledge_r"

  #define MESSAGE_STAND         "M_STAND"
  #define MESSAGE_SEILFREI      "M_SEILFREI"
  #define MESSAGE_SEILAUS       "M_SEILAUS"
  #define MESSAGE_NACHKOMMEN    "M_NACHKOMMEN"

  #define S_ARRAY_SIZE          20
  #define R_ARRAY_SIZE          18
  #define M_ARRAY_SIZE          13
  #define P_ARRAY_SIZE          4

  #define TASTER_STAND          12            //PIN des Tasters
  #define TASTER_SEILFREI       111           //PIN des Tasters
  #define TASTER_SEILAUS        10            //PIN des Tasters
  #define TASTER_NACHKOMMEN     9             //PIN des Tasters

  #define TASTER_PAIRING        2             //PIN des Pairing Tasters


  #define LED_STAND             A0            //PIN des Tasters
  #define LED_SEILFREI          A1            //PIN des Tasters
  #define LED_SEILAUS           A2            //PIN des Tasters
  #define LED_NACHKOMMEN        A3            //PIN des Tasters

  #define LED_PAIRING           11            //PIN des Pairing Tasters

#endif /* DEFINE_h */