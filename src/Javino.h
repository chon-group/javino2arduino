/*
  Javino.h - Library communication for Arduino and Jason.
Version Stable 1.7
  Created by Lazarin, NM and Pantoja, CE - January 29, 2015.
  nilson.lazarin@cefet-rj.br
	carlos.pantoja@cefet-rj.br

  Updated in 2023-10-18
*/

#ifndef Javino_h
#define Javino_h

#include "Arduino.h"
#include "../lib/StdCpp/map"

class Javino
{
  public:
    void start(int baudRate);
    void sendMsg(String msg);
    String getMsg();
    boolean availableMsg();
    boolean requestPercepts();
    boolean requestAction(String strCommand);
    void readSerial();
    void addPercept(String newPercept);
    void clearPercepts();
    void sendPercepts();
    std::map<String, void(*)()> act;
    void run();
    typedef void (*PerceiveCallback)();
    void perceive(PerceiveCallback callback);
  private:
    unsigned int _round;
    unsigned int _size;
    boolean  _msg;
    String _finalymsg;
    String _sizeMSG;
    String _percepts;
    unsigned long _time;
    PerceiveCallback callback;
};

#endif