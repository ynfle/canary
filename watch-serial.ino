#include <LiquidCrystal.h>

int pwm = 255;
int level = 100;
int sensor = A0;
int blink_rate = 400;

#define AIN1 7
#define AIN2 8
#define PWMA 10
#define STBY 6

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(sensor, INPUT); 
  lcd.setCursor(0, 0);
  lcd.print("Ethanol level:");
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // set the cursor to (0,0):
  
  int inputData = analogRead(sensor);
  lcd.clear(); 
  lcd.setCursor(0, 1);
  lcd.print(inputData);
  lcd.setCursor(0, 0);
  lcd.print("Ethanol level:");
  if (inputData >= level) {
    vibrate(); 
    lcd.setCursor(8, 1);
    lcd.print("Warning!");
    
    lcd.noDisplay();
    delay(blink_rate);
    lcd.display();
    delay(blink_rate - 100);
  } else {
    stop();
    lcd.setCursor(0, 1);
    lcd.print(inputData);
    digitalWrite(STBY, LOW);
  }
  Serial.println(inputData);
  delay(100);
}

void vibrate(){
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, pwm);
}
void stop() {
  digitalWrite(STBY, LOW);
}


