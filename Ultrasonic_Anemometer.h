#pragma once


class UltrasonicAnemometer {



public:

  UltrasonicAnemometer( float distanceCM );

  void
    update( void ); // Refresh all variables;


private:

  typedef struct {

    float
      tempC ,
      pressure ,
      humidity ;

  } correction_data_t ;

  float
    _speedOfSound ,
    _windSpeed ; // m/s

  float const
    _sensorDistanceCM ;





};
