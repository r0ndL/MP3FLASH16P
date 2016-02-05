/*
  MP3Flash16Pv2.h - Library for the MP3-Flash-16P module
  
  This version 2 forked version of MP3FLASH16P /u/Critters original library
  was created to remove the static port mappings in the original version.

  Released into the public domain
*/

#ifndef MP3Flash16Pv2_h
#define MP3Flash16Pv2_h
#include "Arduino.h"

class MP3Flash16Pv2
{
	public:
  		MP3Flash16Pv2();
  		MP3Flash16Pv2(Stream& port);
    public:
        void init(int PIN_BUSY, int VOLUME = 30);
        void playFile(int FILE_NUMBER, int VOLUME = -1);
        void playFileAndWait(int FILE_NUMBER, int VOLUME = -1);
        void setVolume(int VOLUME);
        void volumeUp();
        void volumeDown();
        void stopPlay();
        bool isBusy();
    private:
        int _PIN_BUSY;
        uint8_t _VOLUME;
        bool isPlaying;
        Stream& _port;
};

#endif
