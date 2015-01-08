#include "Ultrasonic_Anemometer.h"


UltrasonicAnemometer::UltrasonicAnemometer( int triggerPin, int echoPin, float distanceCM, unsigned long updateInterval ) :
_triggerPin( triggerPin ), _echoPin(echoPin), _sensorDistanceCM( distanceCM ), _updateInterval( updateInterval ){

  _ambient.tempC = 0 ;
  _ambient.pressure = 0 ;
  _ambient.humidity = 0 ;
  _ambient.updateFlag = 0;

  _lastUpdateTime = 0;
  _newDataFlag = 0;
}

void UltrasonicAnemometer::begin( void ){

  pinMode(_triggerPin, OUTPUT);
  digitalWrite(_triggerPin, LOW);
  pinMode(_echoPin, INPUT);

}

void UltrasonicAnemometer::update( void ){

  if( _ambient.updateFlag ){
    _setSpeedOfSound();
    _ambient.updateFlag = 0;
  }
if(millis() - _lastUpdateTime >= _updateInterval){
  _lastUpdateTime = millis();
  _setPingSpeed( _ping() );
  _setWindSpeed();
  }
}

void UltrasonicAnemometer::setTemperatureC( float temp ){
  _ambient.updateFlag = 1;
  _ambient.tempC = temp;

}

void UltrasonicAnemometer::setHumidity( float humidity ){
  _ambient.updateFlag = 1;
  _ambient.humidity = humidity;

}

void UltrasonicAnemometer::setPressure( float pressure ){
  _ambient.updateFlag = 1;
  _ambient.pressure = pressure;

}

float UltrasonicAnemometer::sensorSpacing( void ) const{
  return _sensorDistanceCM ;
}

float UltrasonicAnemometer::speedOfSound( void ) const{
  return _speedOfSound ;
}

float UltrasonicAnemometer::windSpeed( void ){
  _newDataFlag = 0;
  return _windSpeed ;
}

bool UltrasonicAnemometer::ready() const{
  return _newDataFlag;

}



/********************PRIVATE****************************/


void UltrasonicAnemometer::_setSpeedOfSound( void ){
  _speedOfSound = 331.5 + 0.606 * _ambient.tempC;
}

void UltrasonicAnemometer::_setPingSpeed( unsigned long pingTime ){
  //Serial.println(pingTime);
  _pingSpeed = _sensorDistanceCM * 10000;
  _pingSpeed /= pingTime;
}

void UltrasonicAnemometer::_setWindSpeed( void ){
  _newDataFlag = 1;
  _windSpeed = _pingSpeed - _speedOfSound;
}

unsigned long UltrasonicAnemometer::_ping( void ){

  digitalWrite(_triggerPin, HIGH);
  delayMicroseconds(12);
  digitalWrite(_triggerPin, LOW);
  unsigned long pulseTime = pulseIn(_echoPin, HIGH);

  return pulseTime;
}
