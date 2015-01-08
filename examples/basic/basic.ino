#include <Ultrasonic_Anemometer.h>
#include <Wire.h>
#include <Adafruit_MCP9808.h>


#define TRIGGER_PIN 3
#define ECHO_PIN 2
#define SENSOR_SPACING_CM 76

UltrasonicAnemometer windSensor( TRIGGER_PIN, ECHO_PIN, SENSOR_SPACING_CM );

Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

void setup(){
  Serial.begin(9600);
  windSensor.begin();

  if (!tempsensor.begin(0x18)) {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }




}

void loop(){

  windSensor.setTemperatureC( tempsensor.readTempC() );
  windSensor.update();

  Serial.print(F("Wind Speed: "));
  Serial.print(windSensor.windSpeed());
  Serial.println(F(" m/s\n"));

  delay( 500 );



}
