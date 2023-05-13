/*
  Javino.h - Library communication for Arduino and Jason.
Version Stable 1.6
  Created by Lazarin, NM and Pantoja, CE - January 29, 2015.
    nilson.lazarin@cefet-rj.br
	carlos.pantoja@cefet-rj.br

  Updated in 2023-05-12
*/

#ifndef Javino_h
#define Javino_h

#include "Arduino.h"

class Javino
{
  public:
    void start(int baudRate);
    void sendMsg(String msg);
    String getMsg();
    boolean availableMsg();
    void readSerial();
  private:
    unsigned int _round;
    unsigned int _size;
    boolean  _msg;
    String _finalymsg;
    String _sizeMSG;
    unsigned long _time;
};

#endif