/*
  Javino.cpp - Library communication for Arduino and Jason.
Version Stable 1.7
  Created by Lazarin, NM and Pantoja, CE - January 29, 2015.
	nilson.lazarin@cefet-rj.br
	carlos.pantoja@cefet-rj.br

  Updated in 2023-10-18
*/

#include "Arduino.h"
#include "Javino.h"

void Javino::start(int baudRate){
  _finalymsg.reserve(255);
  _sizeMSG = "";
  _finalymsg = "";
  _percepts = "";
  _msg = false;
  _size = 0;
  _round = 0;
  _time = 0;
  Serial.begin(baudRate);
}

void Javino::run(){
  if(availableMsg()){
    if(getMsg() == "getPercepts"){
      callback();
      sendMsg(_percepts);
      clearPercepts();
    }
    else{
      Javino::act[getMsg()]();
    } 
  }
}

void Javino::perceive(PerceiveCallback funcao){
  callback = funcao;
}

void Javino::addPercept(String newPercept){
  _percepts = _percepts+newPercept+";"; 
}

void Javino::clearPercepts(){
  _percepts = ""; 
}

void Javino::sendMsg(String m){
  char buffer[3];
  snprintf(buffer, sizeof(buffer), "%02X", m.length()); 
  String sizeofMSG = buffer; 
	Serial.print("fffe"+sizeofMSG+m);
}

String Javino::getMsg(){
  return _finalymsg;
}

boolean Javino::availableMsg(){
  boolean isMsg = _msg;
  _msg=false;
	return isMsg;
}

void Javino::readSerial() {
  while (Serial.available()){
    if(_round==0){
      _time = millis();
      _finalymsg = "";
    }else if((_round>0) && (_time+300<millis())){
      _sizeMSG = "";
      _round=0;
      _size = 0;
      _finalymsg = "";
      _msg = false;
      _time = millis();
    }
    
    char inChar = (char)Serial.read();
    _round++;
    
    if(((_round==1 | _round==2 | _round==3) && inChar!='f') | (_round==4 && inChar!='e')){
      _round=0;
      _size = 0;
      _finalymsg = "";
      _sizeMSG = "";
      _msg = false;
    }else if(_round==5 | _round==6 ){
      _msg = false;
      _sizeMSG += inChar;
      if(_round==6){
        _size = (strtol(_sizeMSG.c_str(), NULL, 16))+6;
        _sizeMSG = "";
      }
    }else if(_round>6){
      if(_round<_size){
        _msg = false;
        _finalymsg += inChar;
      }else if (_round=_size){
        _finalymsg += inChar;
        _round=0;
        _size = 0;
        _msg = true;
      }
    }
  }
}