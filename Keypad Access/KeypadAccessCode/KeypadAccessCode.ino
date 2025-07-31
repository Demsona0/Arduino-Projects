#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define Password_Length 10
#define SUBMIT_KEY '#'

char Data[Password_Length];
char Master[Password_Length] = "12345";
int RedLED = 13;
int GreenLED = 12;
byte data_count = 0;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();
  pinMode(GreenLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  digitalWrite(RedLED, HIGH);
  digitalWrite(GreenLED, LOW);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  
  customKey = customKeypad.getKey();
  if (customKey) {
    if (customKey == SUBMIT_KEY) {
      checkPassword();
    } 
    else if (data_count < Password_Length - 1) {
      Data[data_count] = customKey;
      lcd.setCursor(data_count, 1);
      lcd.print('*');
      data_count++;
    }
  }
}

void checkPassword() {
  lcd.clear();
  Data[data_count] = '\0';
  
  if (!strcmp(Data, Master)) {
    lcd.print("Correct");
    digitalWrite(RedLED, LOW);
    digitalWrite(GreenLED, HIGH);
    delay(5000);
    digitalWrite(RedLED, HIGH);
    digitalWrite(GreenLED, LOW);
  } else {
    lcd.print("Incorrect");
    digitalWrite(RedLED, HIGH);
    delay(3000);
  }
  
  lcd.clear();
  clearData();
}

void clearData() {
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
}