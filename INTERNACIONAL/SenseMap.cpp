#include <Arduino.h>
#include "SenseMap.h"

SenseMap::SenseMap(){}

void SenseMap::setup()
{
  i2c_init(); 
  pinMode(trig_E, OUTPUT);
  pinMode(echo_E, INPUT);
  pinMode(trig_D, OUTPUT);
  pinMode(echo_D, INPUT);
  pinMode(trig_A, OUTPUT);
  pinMode(echo_A, INPUT);
  pinMode(trig_I, OUTPUT);
  pinMode(echo_I, INPUT);
  firstTemperature=(temperatureCelcius(mlxRight)+temperatureCelcius(mlxLeft))/2;
}

void SenseMap::beginTrig(const byte trig)
{
  digitalWrite(trig, HIGH);
  digitalWrite(trig, LOW);
}

float SenseMap::getDistanceOf(const byte echo, uint8_t num)
{
  if(num == 1)
    beginTrig(trig_I);
  else if(num == 2)
    beginTrig(trig_D);
  else if(num == 3)
    beginTrig(trig_E);
  else if(num == 4)
    beginTrig(trig_A);
  
  Time = pulseIn(echo, HIGH);
  distance = Time * 0.000001 * sound / 2.0;
  return distance;
}

float SenseMap::temperatureCelcius(int mlx) 
{
  int dev = mlx;
  int data_low = 0;
  int data_high = 0;
  int pec = 0;
  
  i2c_start_wait(dev+I2C_WRITE);
  i2c_write(0x07);
  
  i2c_rep_start(dev+I2C_READ);
  data_low = i2c_readAck();
  data_high = i2c_readAck();
  pec = i2c_readNak();
  i2c_stop();
  
  double tempFactor = 0.02;
  double tempData = 0x0000;
  int frac;
  
  tempData = (double)(((data_high & 0x007F) << 8) + data_low);
  tempData = (tempData * tempFactor)-0.01;
  float celcius = tempData - 273.15;
  
  return celcius;
}

void SenseMap::checkDistances()
{
  if(this -> getDistanceOf(echo_E, 3) >= 8 && this -> getDistanceOf(echo_E, 3) <= 13)
  {  
    motors.setBase(115);
    unsigned long tempoo = millis();
    
    while(this -> getDistanceOf(echo_E, 3) > 8)
    {
      motors.avanzar(motors.de,30,30,motors.bD);
      
      if(millis()>(tempoo+1000))
        break;
    }
    
  motors.detenerse();
  motors.setBase(150);
  }
  else if(this -> getDistanceOf(echo_E, 3) < 5 && this -> getDistanceOf(echo_E, 3) != 0)
  {
    unsigned long ter = millis();
    motors.setBase(95);
    
    while(this -> getDistanceOf(echo_E, 3) < 4)
    {
      motors.atrasPID(motors.de);
      if(millis()>(ter+300))
        break;
    }
    motors.detenerse();
    motors.setBase(150);
  }
  
  float disss = this -> getDistanceOf(echo_E, 3);
  
  if(disss >= 27 && disss <= 45) //36
  {
    motors.setBase(110);
    unsigned long terr = millis();
    
    if(disss >= 31 && disss <= 38)
    {}
    else if(disss > 38)
    {
      while(this -> getDistanceOf(echo_E, 3) > 36)
      {
        motors.avanzar(motors.de,30,30,motors.bD);
        if(millis() > (terr + 300))
          break;
      }
      
     motors.detenerse();
    }
    else if(disss < 31)
    {
      while(this -> getDistanceOf(echo_E, 3) < 31)
       {
          motors.atrasPID(motors.de);
          if(millis() > (terr+200))
           break;
       }
       
     motors.detenerse();
    }
    
     motors.setBase(150);
  }
}
