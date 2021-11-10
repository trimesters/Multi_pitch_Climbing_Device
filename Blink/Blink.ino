
 int inPin = 7;
 int Counter = 0;
 uint8_t flag = 0; 
 //int16_t uint16_t
 
 void setup() {
 Serial.begin(9600);    //PC-Monitoring
 Serial1.begin(9600);   //Serielle Verbindung zu 1. Funkmodul 
 Serial2.begin(9600);   //Serielle Verbindung zu 2. Funkmodul
 Serial.println("Let's start!");


 pinMode(inPin, INPUT_PULLUP);
 }


 
 void loop() 
 {

  flag = digitalRead(inPin);

if (flag != 0)
{
  Serial1.write("Taster gedrueckt");
}
 if (Serial2.available()) 
 {           //Wenn Funkmodul 2 etwas empfang wird es in den Monitor geschrieben
  Serial.write(Serial2.read());
 }
 if (Serial.available()) 
 {           //Wenn am Monitor etwas geschrieben wird, wird es an Funkmodul 1 geschickt
    Serial1.write(Serial.read());
 }

delay(5);
Counter += 1;

 if (Counter > 1000) 
 {                //Immer wenn der Counter 1000 erreicht, wird "Hello World" an Funkmodul 1 geschickt, eine neue Zeile eingefügt und der Counter zurückgesetzt
  Serial1.write("Hello World");
  Serial.println();
  Counter = 0;
  }
 }

 
