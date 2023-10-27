#include <Javino.h>
#include <LiquidCrystal.h>  //https://www.arduino.cc/reference/en/libraries/liquidcrystal/

#define PinD0 0
#define PinD1 1
#define PinD2 2
#define PinD3 3
#define PinLCDCtrl01 4
#define PinLCDCtrl02 5
#define PinLCDCtrl03 6
#define PinLCDCtrl04 7
#define PinLCDRS     8
#define PinLCDEN     9
#define PinLCDLight  10
#define PinD11 11
#define PinD12 12
#define PinD13 13

Javino javino;

LiquidCrystal lcd(PinLCDRS, PinLCDEN, PinLCDCtrl01, PinLCDCtrl02, PinLCDCtrl03, PinLCDCtrl04);
int lastBtnPressed = 1024;
String lastLCDMsg = "";

void serialEvent(){javino.readSerial();}

void setup() {
 startLCDWithKeyboard();
 javino.start(9600);
}
 
void loop() {
 readLCDKeyboard();
 if(javino.availableMsg()){
  if(javino.requestPercepts()) getExogenousPerceptions();
  else if(javino.requestAction("lcdOFF")) lcdOFF();
  else writeInLCD(javino.getMsg());
 }
}

void getExogenousPerceptions(){
    javino.addPercept("device(arduinoWithLCDKeypadShield)");
    
    if     (lastBtnPressed < 50){javino.addPercept("btnPressed(right)");}
    else if(lastBtnPressed < 150){javino.addPercept("btnPressed(up)");}
    else if(lastBtnPressed < 300){javino.addPercept("btnPressed(down)");}
    else if(lastBtnPressed < 500){javino.addPercept("btnPressed(left)");}
    else if(lastBtnPressed < 750){javino.addPercept("btnPressed(select)");}
    else {} 

    if(digitalRead(PinLCDLight)==1){javino.addPercept("lcdStatus(on)");}
    else{javino.addPercept("lcdStatus(off)");}

    javino.sendPercepts();
}

void startLCDWithKeyboard(){
  pinMode(PinLCDLight, OUTPUT);
  digitalWrite(PinLCDLight, LOW);
  lcd.begin(16, 2);
 }

void readLCDKeyboard(){ 
  int input = analogRead(A0);
  if(((input <= lastBtnPressed-50) || (input >= lastBtnPressed+50))
      & (input < 1000 )){
      lastBtnPressed = input;
  }
  delay(50);
}

void writeInLCD(String strL){
  if (strL.startsWith("\"") && strL.endsWith("\"")) {
    strL.remove(0, 1);
    strL.remove(strL.length() - 1); 
  }

  int lengthStr = strL.length();
  for (int startIndex = 0; startIndex < lengthStr; startIndex += 16) {
    int endIndex = startIndex + 15;
    if (endIndex >= lengthStr) {
      endIndex = lengthStr - 1;
    }
    String chunk = strL.substring(startIndex, endIndex + 1);
    digitalWrite(PinLCDLight, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(lastLCDMsg);
    lcd.setCursor(0,1);
    lcd.print(chunk);
    lastLCDMsg = chunk;
  }
}

void lcdOFF(){
  digitalWrite(PinLCDLight, LOW);
  lcd.clear();
}
