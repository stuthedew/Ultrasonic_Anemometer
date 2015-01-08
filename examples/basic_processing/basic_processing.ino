#include <Ultrasonic_Anemometer.h>
#include <Wire.h>
#include <Adafruit_MCP9808.h>

#define SAMPLE_SIZE 10

#define TRIGGER_PIN 3
#define ECHO_PIN 2
#define SENSOR_SPACING_CM 76

int itr = 0;

float rollAvgAry[SAMPLE_SIZE];

UltrasonicAnemometer windSensor( TRIGGER_PIN, ECHO_PIN, SENSOR_SPACING_CM );

Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

void setup(){
  Serial.begin(9600);
  windSensor.begin();

  if (!tempsensor.begin(0x18)) {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }
  windSensor.setTemperatureC( tempsensor.readTempC() );

  for(int i = 0; i < SAMPLE_SIZE;){

    if(windSensor.ready()){

      rollAvgAry[i] = windSensor.windSpeed();
      i++;

    }
    windSensor.setTemperatureC( tempsensor.readTempC() );
    windSensor.update();
    delay(50);
  }

}

void loop(){

  windSensor.setTemperatureC( tempsensor.readTempC() );
  windSensor.update();
  if(windSensor.ready()){
    rollAvgAry[itr] = windSensor.windSpeed();
    int tmpInt = round(rollAverage() * 1000);

    tmpInt = map(tmpInt, -6500, 6500, 0, 1023);
    Serial.println(tmpInt);
    itr++;
    itr %= SAMPLE_SIZE;

}

  delay( 50 );
}

float rollAverage(){
  float tmp = 0;
  for(int i = 0; i < SAMPLE_SIZE; i++){
    tmp += rollAvgAry[i] ;
  }
  return tmp / SAMPLE_SIZE;
}
