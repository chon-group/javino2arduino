#include <Javino.h>
Javino javino;

void setup() {
 pinMode(13,OUTPUT);

 /* Javino Acts and Percept description */
 javino.act["ledOn"]  = ledOn;
 javino.act["ledOff"] = ledOff;
 javino.perceive(getExogenousPerceptions);
 javino.start(9600);

}

void loop() {
  javino.run();
}

/*
 * The serialEvent() function handles interruptions coming from the serial port.
 * 
 * NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or other ATmega32U4 based boards. 
 * https://docs.arduino.cc/built-in-examples/communication/SerialEvent 
 * 
 */
void serialEvent(){
  javino.readSerial();
}

/* 
  It sends the exogenous environment's perceptions to the agent. 
*/
void getExogenousPerceptions(){ 
  if(digitalRead(13)==1)javino.addPercept("ledStatus(on)");
  else javino.addPercept("ledStatus(off)");
}

/* It implements the commands to be executed in the exogenous environment. 
*
* NOTE: Every command must reflect in a function. 
*
*/
void ledOn(){
  digitalWrite(13,HIGH); 
}

void ledOff(){
  digitalWrite(13,LOW); 
}
