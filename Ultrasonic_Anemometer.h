#pragma once


#include "Arduino.h"

class UltrasonicAnemometer {



public:

  UltrasonicAnemometer( int triggerPin, int echoPin, float distanceCM, unsigned long updateInterval = 1000 );

  void
    begin( void ) ,
    update( void ) , // Refresh all variables;
    setUpdateInterval( unsigned long interval ),
    setTemperatureC( float temp ) ,
    setHumidity( float humidity ) ,
    setPressure( float pressure ) ;


  float
    sensorSpacing( void ) const ,
    speedOfSound( void ) const ,
    windSpeed( void ) const ;


  int
    pingTravelTime( void ) const ;


private:

  typedef struct {

    float
      tempC ,
      pressure ,
      humidity ;

    bool
      updateFlag ;

  } correction_data_t ;

  /**************************VARIABLES********************************/
  float
    _speedOfSound ,
    _windSpeed , // m/s
    _pingSpeed ; // m/s

  float const
    _sensorDistanceCM ;

  int const
    _triggerPin,
    _echoPin ;

  unsigned long
    _updateInterval,
    _lastUpdateTime ;

  correction_data_t
    _ambient ;



/**************************METHODS********************************/

  void
    _setSpeedOfSound( void ),
    _setPingSpeed( unsigned long pingTime ),
    _setWindSpeed( void ) ;

  unsigned long
    _ping( void ) ;


};
