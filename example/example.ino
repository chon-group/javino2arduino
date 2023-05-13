#include <Javino.h>
Javino javino;

void serialEvent(){
 /*
 * The serialEvent() function handles interruptions coming from the serial port.
 * 
 * NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or other ATmega32U4 based boards. 
 * https://docs.arduino.cc/built-in-examples/communication/SerialEvent 
 * 
 */
  javino.readSerial();
}

void setup() {
 javino.start(9600);
 pinMode(13,OUTPUT);
}

void loop() {
 if(javino.availableMsg()){
  if(javino.getMsg() == "getPercepts")javino.sendMsg(getPercepts());
  else if(javino.getMsg() == "ledOn") ledOn();
  else if(javino.getMsg() == "ledOff")ledOff();
 }
}

/* It sends the exogenous environment's perceptions to the agent. */
String getPercepts(){
  String beliefs = 
          "resourceName(myArduino);"
          "ledStatus("+String(digitalRead(13))+");"; 
          
  return beliefs;
}

/* It implements the command to be executed in the exogenous environment. 
*
* NOTE: Every command must reflect in a function. 
*
*/
void ledOn(){
  digitalWrite(13,HIGH); 
}

/* It implements the command to be executed in the exogenous environment. */
void ledOff(){
  digitalWrite(13,LOW); 
}
