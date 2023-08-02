#include <Arduino_FreeRTOS.h>
#include <DHT.h>

#define dht_apin A0//analog pin sensor is connected
DHT dht(dht_apin,DHT11);
float hum;
float tem;

#define LIGHT 2 // define pint 2 for sensor
#define RELAY 9 // define pin 9 as for relay
boolean digital = 0;// set true to use digital and control the sensitiviety with potentiometer on the module
                  // set to false to control with a5 value on Arduino
unsigned int LightValue = 700;// LightValue to determine
                      // at what value the realy should be ON
#define dht_a5pin A5//analog pin sensor is connected


//define two tasks for Blink & AnalogRead
void TaskTem( void *pvParameters ); 
void TaskHum( void *pvParameters ); 
void TaskLight( void *pvParameters ); 

//the setup function runs once when you press reset or power the board
void setup()
{
//initialize serial communication at 9600 bits per second
Serial.begin(9600);

dht.begin();
delay(100);

//now set up two tasks to run independently.
xTaskCreate(
  TaskTem
  ,  "Temp"  //a name just for humans
  ,  128  //this stack size can be checked and adjusted by reading the Stack Highwater
  ,  NULL
  ,  1  //priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
  ,  NULL );

xTaskCreate(
  TaskTem
  ,  "Hum"  
  ,  128  // stack size
  ,  NULL
  ,  1  // Priority
  ,  NULL );

xTaskCreate(
  TaskLight
  ,  "Lit"  
  ,  128  // stack size
  ,  NULL
  ,  1  // Priority
  ,  NULL );

// Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started

Serial.println("humidity------temperature------light\n\n");

}


void loop()
{
  // Empty. Things are done in Tasks.
}

/*-----------------------------------------------------*/
/*----------------------- Tasks -----------------------*/
/*-----------------------------------------------------*/

void TaskHum(void*pvParameters)  // This is a task.
{
  (void) pvParameters;

  pinMode(dht_apin,INPUT);

  for  (;;)
  {
    float hum=dht.readHumidity();
    Serial.print("current humidity = ");
    Serial.print(hum);
    Serial.print("%\t");
    delay(1000);
  }
}


void TaskTem(void*pvParameters)  // This is a task.
{
  (void) pvParameters;

  //initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(dht_apin,INPUT);

  for  (;;)  // A Task shall never return or exit.
  {
    float hum=dht.readTemperature();
    Serial.print("Temperature = ");
    Serial.print(tem);
    Serial.print("C\n");
    delay(1000);


  }
}


void TaskLight(void*pvParameters)  // This is a task.
{
  pinMode(dht_a5pin,INPUT);

  for  (;;)
  {
      if(digital == true)
   {
  // Light LDR Sensor Code
  int L =digitalRead(LIGHT);// read the sensor 

      if(L == 1){
        Serial.println(" light is Off");
        digitalWrite(RELAY,LOW);// turn the relay ON
      }else{
         Serial.println("  === light is On");
         digitalWrite(RELAY,HIGH);// turn the relay OFF
      } // if
   }// if digital end
  
   else
   {
    int a5Value = analogRead(A5);// read A0 value

      if( a5Value >= LightValue){
        Serial.print(analogRead(A5));
        Serial.println(" Light is Off");
        digitalWrite(RELAY,LOW);// turn the relay ON
      }else{
         Serial.print(analogRead(A5));
         Serial.println("  === light On");
         digitalWrite(RELAY,HIGH);// turn the relay OFF
      } // if
   }
   delay(1000);
  }
}



