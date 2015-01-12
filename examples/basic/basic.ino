#include <Ultrasonic_Anemometer.h>
#include <Wire.h>
#include <Adafruit_MCP9808.h>


#define TRIGGER_PIN 2
#define ECHO_PIN 3
#define SENSOR_SPACING_CM 76

UltrasonicAnemometer windSensor( TRIGGER_PIN, ECHO_PIN, SENSOR_SPACING_CM );

//Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

void setup(){
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  windSensor.begin();

  //if (!tempsensor.begin(0x18)) {
    //Serial.println("Couldn't find MCP9808!");
    //while (1);
  //}




}

void loop(){

  //windSensor.setTemperatureC( tempsensor.readTempC() );
  windSensor.update();

  Serial.print(F("Wind Speed: "));
  Serial.print(windSensor.windSpeed());
  Serial.println(F(" m/s\n"));

  delay( 500 );



}
