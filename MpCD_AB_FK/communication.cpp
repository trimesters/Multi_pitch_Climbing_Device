

#include "communication.h"

Communication::Communication(uint8_t txChannel_, uint8_t rxChannel_, uint8_t setPin_, uint32_t baudRate_, uint16_t transferDelay_): SerialIO(rxChannel_, txChannel_)
{

  SerialIO.begin(9600);
  
  for (uint8_t i = 0; i < R_ARRAY_SIZE; ++i) messageRead[i]  = INITIALIZATION_VALUE;
  messageRead[S_ARRAY_SIZE] = END_OF_STRING;
  
  for (uint8_t i = 0; i < S_ARRAY_SIZE; ++i) messageWrite[i] = INITIALIZATION_VALUE;
  messageWrite[R_ARRAY_SIZE] = END_OF_STRING;
  
  for (uint8_t i = 0; i < P_ARRAY_SIZE; ++i) pairingValue[i]  = INITIALIZATION_VALUE;
  pairingValue[P_ARRAY_SIZE] = END_OF_STRING;

  for (uint8_t i = 0; i < M_ARRAY_SIZE; ++i) messageValue[i]  = INITIALIZATION_VALUE;
  messageValue[M_ARRAY_SIZE] = END_OF_STRING;

  startChar     ='<';
  stopChar      ='>';
  checkBreak    =',';

  transferDelay = transferDelay_;
}

Communication::~Communication()
{

}

uint8_t Communication::message_write_to_paired_device(char* message)
{
  if (message_build(message) != S_ARRAY_SIZE)
  {
    return EXIT_FAILURE;
  }
  if (message_write() != S_ARRAY_SIZE)
  {
    return EXIT_FAILURE;
  }
  
  if (message_read() == EXIT_SUCCESS)
  {
    get_message_value_from_messageRead();

    if (strcmp(ACKNOWLEDGE, messageValue) == EXIT_SUCCESS)
    {
      return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
  }
}

uint8_t Communication::message_read_from_paired_device(char* message)
{
  if (message_read() == EXIT_SUCCESS)
  {
    if (strncmp(messageRead, pairingValue, 3) == EXIT_SUCCESS)
    {
      if (message_build(ACKNOWLEDGE) != S_ARRAY_SIZE)
      {
        return EXIT_FAILURE;
      }
      if (message_write() != S_ARRAY_SIZE)
      {
        return EXIT_FAILURE;
      }

      get_message_value_from_messageRead();
      strncpy(message, messageValue, M_ARRAY_SIZE);

      return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
  }
  return EXIT_FAILURE;
}

uint8_t Communication::set_message(char* message)
{
  int8_t rslt;

    rslt = snprintf(messageValue, M_ARRAY_SIZE, "%s", message); 

  return rslt;
}

uint8_t Communication::set_pairing_value(uint8_t uniqueNumber)
{
  int8_t rslt;

  rslt = snprintf(pairingValue, P_ARRAY_SIZE, "%003u", uniqueNumber);

  return rslt + 1;
}

void Communication::get_message_value_from_messageRead(void)
{
  for (uint8_t i = 0; i < M_ARRAY_SIZE; ++i)
  {
    messageValue[i] = messageRead[i + 4];
  }
}

uint8_t Communication::get_pairing_value_from_messageRead(void)
{
  uint8_t number = 0;

  for (uint8_t i = 0; i < P_ARRAY_SIZE - 1; ++i)
  {
    number = 10 * number + (messageRead[i] - '0');
  }

  return number; 
}

uint8_t Communication::message_build(char* message)
{
  int8_t rslt;

  rslt = snprintf(messageWrite, S_ARRAY_SIZE, "%c%s%c%s%c", startChar, pairingValue, checkBreak, message, stopChar); // 1C (<) + 3C (xxx) + 1C (,) + 13C (...) + 1C (>) + 1C (\0) = 20C

  return rslt + 1;
}

uint8_t Communication::message_write(void)
{
  int8_t rslt = 0;
  uint8_t count = 0;

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) // no interrupts allowed while writing to buffer
  {
    while (messageWrite[count] != '\0')
    {
      rslt = SerialIO.write(messageWrite[count]);
      count++;
    }
  }

  delay(transferDelay);

  return rslt + 19;
}

uint8_t Communication::message_read(void)
{
  char input;
  int8_t flag  = 0;
  int16_t count     = 0;

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) // no interrupts allowed while writing to buffer
  {
    while ( (SerialIO.available()) && (count < (R_ARRAY_SIZE + 1)) )
    {
      input = SerialIO.read();

      if (input == stopChar)
      {
        delay(transferDelay);
        return EXIT_SUCCESS;
      }

      if (flag == 1)
      {
        messageRead[count] = input;
        count++;
      }
      
      if (input == startChar)
      {
        flag = 1;
      }
    }
  }
  return EXIT_FAILURE;
}

uint8_t Communication::searchNewPairing(volatile uint8_t* pairingAktiv)
{
  uint8_t flag          = 0;
  uint8_t uniqueNumber  = 0;
  uint8_t randNumber    = (uint8_t)random(254);

  
  while(*pairingAktiv == 1)
  {
    if (flag == 0)
    {
      if (pairingPhaseOne(&flag, &uniqueNumber, &randNumber) != EXIT_SUCCESS)
      {
        return EXIT_FAILURE;
      }
    }
    else if(flag == 2)
    {
      if (pairingPhaseTwo(&flag, &uniqueNumber, &randNumber) != EXIT_SUCCESS)
      {
        return EXIT_FAILURE;
      }
    }
    else if( flag == 4)
    {
      if (pairingPhaseThree(&flag, &uniqueNumber, &randNumber) == EXIT_SUCCESS)
      {
        return EXIT_SUCCESS;
      }
    }

    if (flag == 1)
    {
      if (message_read() == EXIT_SUCCESS)
      {
        flag = 2;
      }
    }
    else if ( flag == 3)
    {
      if (message_read() == EXIT_SUCCESS)
      {
        flag = 4;
      }
    }
  }
}

uint8_t Communication::pairingPhaseOne(uint8_t* flag, uint8_t* randNumber, uint8_t* uniqueNumber)
{
  if (set_pairing_value(*randNumber) != P_ARRAY_SIZE)
  {
    return EXIT_FAILURE;
  }

  if (message_build(messageValue) != S_ARRAY_SIZE)
  {
    return EXIT_FAILURE;
  }

  if (message_write() != S_ARRAY_SIZE)
  {
    return EXIT_FAILURE;
  }

  *flag = 1;

  return EXIT_SUCCESS;
}

uint8_t Communication::pairingPhaseTwo(uint8_t* flag, uint8_t* randNumber, uint8_t* uniqueNumber)
{   
  *uniqueNumber = get_pairing_value_from_messageRead();
  *uniqueNumber = *uniqueNumber + *randNumber;

  if (set_pairing_value(*uniqueNumber) != P_ARRAY_SIZE)
  {
    return EXIT_FAILURE;
  }

  if (message_build(messageValue) != S_ARRAY_SIZE)
  {
    return EXIT_FAILURE;
  }

  if (message_write() != S_ARRAY_SIZE)
  {
    return EXIT_FAILURE;
  }

  *flag = 3;

  return EXIT_SUCCESS;
}

uint8_t Communication::pairingPhaseThree(uint8_t* flag, uint8_t* randNumber, uint8_t* uniqueNumber)
{
  if (*uniqueNumber == get_pairing_value_from_messageRead())
  {
    return EXIT_SUCCESS;
  }

  *flag = 0;

  return EXIT_FAILURE;
}
