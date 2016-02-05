/*
  MP3Flash16Pv2.h - Library for the MP3-Flash-16P module
  
  This version 2 forked version of MP3FLASH16P /u/Critters original library
  was created to remove the static port mappings in the original version.

  Released into the public domain
*/

#include "Arduino.h"
#include "MP3Flash16Pv2.h"

MP3Flash16Pv2::MP3Flash16Pv2()
  : _port(Serial)
{
  
}

MP3Flash16Pv2::MP3Flash16Pv2(Stream& port)
  : _port(port)
{
  
}

void MP3Flash16Pv2::init(int PIN_BUSY, int VOLUME)
{
    _PIN_BUSY = PIN_BUSY;
    _VOLUME = (uint8_t)VOLUME;
    pinMode(_PIN_BUSY, INPUT);
    digitalWrite(_PIN_BUSY, LOW);
}

void MP3Flash16Pv2::playFile(int FILE_NUMBER, int VOLUME)
{   
    if(VOLUME != -1)
    {
        _VOLUME = (uint8_t)VOLUME;
    }
    uint8_t filenumber = (uint8_t)FILE_NUMBER;
    uint8_t play1[8] = { 0X7E, 0XFF, 0X06, 0X22, 0X00, _VOLUME, filenumber, 0XEF };
    for (int i=0; i<8; i++) 
    {
        _port.write( play1[i] ); 
    }
}

void MP3Flash16Pv2::playFileAndWait(int FILE_NUMBER, int VOLUME)
{
    playFile(FILE_NUMBER, VOLUME);
    delay(100);
    while(isBusy()){
    }
    delay(250);
}

bool MP3Flash16Pv2::isBusy()
{
    return digitalRead(_PIN_BUSY) == LOW;
}

void MP3Flash16Pv2::setVolume(int VOLUME)
{
    _VOLUME = constrain(VOLUME, 0, 30);
}

void MP3Flash16Pv2::volumeUp()
{
    _VOLUME = min(_VOLUME+5, 30);
}

void MP3Flash16Pv2::volumeDown()
{
    _VOLUME = max(_VOLUME-5, 0);
}

void MP3Flash16Pv2::stopPlay()
{   
    uint8_t play1[8] = { 0X7E, 0XFF, 0X06, 0X16, 0X00, 0x00, 0x00, 0XEF };
    for (int i=0; i<8; i++) 
    {
        _port.write( play1[i] ); 
    }
}



