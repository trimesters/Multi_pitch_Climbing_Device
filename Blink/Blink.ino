#define Sensor_1 21


volatile uint32_t last_interrupt_time_x = 0;
volatile uint8_t plotter_aktiv_x = 0; //The value for the X-axis sensor


void interrupt_init();
void sensor_left();

int Counter = 0;


void setup() 
{
	Serial.begin(9600);    //PC-Monitoring
	Serial1.begin(9600);   //Serielle Verbindung zu 1. Funkmodul 
	Serial2.begin(9600);   //Serielle Verbindung zu 2. Funkmodul

	interrupt_init(); //Initialization of the Interrupt routine

}


void loop() 
{
	if (Serial2.available()) 
	{          
		Serial.write(Serial2.read());  	//Wenn Funkmodul 2 etwas empfang wird es in den Monitor geschrieben
	} 
	
	/*
	if (Serial.available())   			//Wenn am Monitor etwas geschrieben wird, wird es an Funkmodul 1 geschickt
	{          
		Serial1.write(Serial.read());
	}
	*/

	delay(10);

	/*
	
	Counter += 1;

	if (Counter > 1000)  //Immer wenn der Counter 1000 erreicht, wird "Hello World" an Funkmodul 1 geschickt, eine neue Zeile eingefügt und der Counter zurückgesetzt
	{                
		Serial1.write("Hello World");
		Serial.println();
		Counter = 0;
	}

	*/
}



void interrupt_init() 
{
	// Initialize the Interrupt Pins:
	attachInterrupt(digitalPinToInterrupt(Sensor_1), sensor_left, CHANGE);

}

//The x-axis is referenced in this interrupt routine.
void sensor_left() //Serial.println("Pin11");
{ 

	uint32_t interrupt_time = millis();

	if ((interrupt_time - last_interrupt_time_x) > 50) 
	{
		Serial1.write("Hello \n");
	}
	last_interrupt_time_x = interrupt_time;
}



