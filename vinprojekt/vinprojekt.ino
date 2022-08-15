#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

#include <Wire.h>

#define joyY A0


LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {12, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 




int redpin = 9; 
int greenpin =10;
int bluepin = 11; 
int val;
int redval = 0;
int greenval = 0;
int blueval = 0;
char color = 'A';


int buzzer = 10;

void clearColor () {
    analogWrite(redpin, 0);
    analogWrite(bluepin, 0);
    analogWrite(greenpin, 0);
    redval=0;
    greenval=0;
    blueval=0;
    updateSinglelcd('A');
    updateSinglelcd('C');
    updateSinglelcd('B');
    redval=0;
    greenval=0;
    blueval=0;
    updateSinglelcd('A');
    updateSinglelcd('C');
    updateSinglelcd('B');
  }

void setColor(char c, int val) {
        if (c=='A') {
        analogWrite(redpin, val);
        redval=val;
      }
      else if (c=='B') {
        analogWrite(greenpin, val);
        greenval=val;
      }
      else if (c=='C') {
        analogWrite(bluepin, val);
        blueval=val;
      }
      updateSinglelcd(c);
  }

void setMaxColor(char c) {
      if (c=='A') {
        analogWrite(redpin, 255);
        redval=255;
      }
      else if (c=='B') {
        analogWrite(greenpin, 255);
        greenval=255;
      }
      else if (c=='C') {
        analogWrite(bluepin, 255);
        blueval=255;
      }
      updateSinglelcd(c);
  }
  
void raiseColor(char c){
      if (c=='A') {
        if (redval<255) {
            redval++;
            analogWrite(redpin, redval);
          }

      }
      else if (c=='B') {
        if (greenval<255) {
            greenval++;
            analogWrite(greenpin, greenval);
          }
      }
      else if (c=='C') {
        if (blueval<255) {
            blueval++;
            analogWrite(bluepin, blueval);
          }
      }
      updateSinglelcd(c);
  }

  void lowerColor(char c){
      if (c=='A') {
        if (redval>0) {
            redval--;
            analogWrite(redpin, redval);
          }

      }
      else if (c=='B') {
        if (greenval>0) {
            greenval--;
            analogWrite(greenpin, greenval);
          }
      }
      else if (c=='C') {
        if (blueval>0) {
            blueval--;
            analogWrite(bluepin, blueval);
          }
      }
      updateSinglelcd(c);
  }

void updateSinglelcd(char c) {
    if(c=='A') {
        if(redval<100) {
          lcd.setCursor(3,0);
          lcd.print("0");
          lcd.print(redval);
          }
        else if(redval<10) {
          lcd.setCursor(3,0);
          lcd.print("00");
          lcd.print(redval);
          }
        else if(redval==0) {
          lcd.setCursor(3,0);
          lcd.print("000");
          lcd.setCursor(5,0);
          lcd.print("0");
          }
        else {
          lcd.setCursor(3,0);
          lcd.print(redval);
          } 
      }
      else if(c=='B') {
        if(greenval<100) {
          lcd.setCursor(10,0);
          lcd.print("0");
          lcd.print(greenval);
          }
        else if(greenval<10) {
          lcd.setCursor(10,0);
          lcd.print("00");
          lcd.print(greenval);
          }
        else if(greenval==0) {
          lcd.setCursor(10,0);
          lcd.print("000");
          lcd.setCursor(12,0);
          lcd.print("0");
          }
        else {
          lcd.setCursor(10,0);
          lcd.print(greenval);
          } 
      }
      else if(c=='C') {
        if(blueval<100) {
          lcd.setCursor(3,1);
          lcd.print("0");
          lcd.print(blueval);
          }
        else if(blueval<10) {
          lcd.setCursor(3,1);
          lcd.print("00");
          lcd.print(blueval);
          }
        else if(blueval==0) {
          lcd.setCursor(3,1);
          lcd.print("000");
          lcd.setCursor(5,1);
          lcd.print("0");
          }
        else {
          lcd.setCursor(3,1);
          lcd.print(blueval);
          } 
      }
  }

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print("R: 025 ");
  lcd.print("G: 025 ");
  lcd.setCursor(0,1);
  lcd.print("B: 025");
  analogWrite(redpin, 25);
  analogWrite(greenpin, 25);
  analogWrite(bluepin, 25);
  
}
void loop() {
  char customKey = customKeypad.getKey();
  int yValue = analogRead(joyY);
  Serial.println(yValue);
  //tone(buzzer,2000);
  //delay(1500);
  //noTone(buzzer);
  //delay(500);
  if (yValue>600) {
    raiseColor(color);
    }

  if (yValue<400) {
    lowerColor(color);
    }
  
  if (customKey=='A' || customKey=='B' || customKey=='C'){
    Serial.println(customKey);
    color=customKey;
  }
  else if (customKey=='D') {
    Serial.println("Setting all colors to 0");
    clearColor();
    lcd.setCursor(5,0);
    lcd.print("0");
    lcd.setCursor(5,1);
    lcd.print("0");
    lcd.setCursor(12,0);
    lcd.print("0");
   }
  else if (customKey=='#' || customKey=='*') {
    Serial.println("Setting color to 0");
    setColor(color,0);
    if (color=='A') {
        lcd.setCursor(5,0);
        lcd.print("0");
      }
    else if (color=='B') {
        lcd.setCursor(12,0);
        lcd.print("0");
      }
    else if (color=='C') {
        lcd.setCursor(5,1);
        lcd.print("0");
      }
  }
  else if (customKey=='0') {
    Serial.println("Setting color to max");
    setMaxColor(color);  
  }
  else if (customKey=='1' || customKey=='2' || customKey=='3' || customKey=='4' || customKey=='5' || customKey=='6' || customKey=='7' || customKey=='8' || customKey=='9' ) {
    Serial.println("Setting color to 25*button clicked");
    int someInt = customKey - '0';
    val=someInt*25;
    setColor(color,val);  
  }
  delay(10);
}
