//Door survey bot w/ LCD screen
//by Ethan Palosh

//To change each day:
///////////////////////////////
///////////////////////////////
///////////////////////////////

//Questions are asked in a "this or that" format
String choiceOne = "Sunset";
String choiceTwo = "Stargazing";
String bottomText = "           ...assuming perfect weather!";

///////////////////////////////
///////////////////////////////
///////////////////////////////


// includes the library code:
#include <LiquidCrystal.h> //LCD
#include <EEPROM.h> //permenant memory

// initializes the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//buttons
const int choiceOnePin = 12;
const int choiceTwoPin = 11;

int numChoiceOne;
int numChoiceTwo;

void setup() {

  //counters - read the integer from EEPROM
  numChoiceOne = EEPROMReadInt(0);
  numChoiceTwo = EEPROMReadInt(10);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("setup");

  pinMode(choiceOnePin, INPUT);
  pinMode(choiceTwoPin, INPUT);
}

//main loop
void loop() {

  //LCD setup and delay for scroll
  lcd.scrollDisplayLeft();
  lcd.setCursor(0, 0);
  delay(150);
  

  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  //idle message
  lcd.print(choiceOne + " or " + choiceTwo + "?" + "       Vote!!");
  //additional info if added
  lcd.setCursor(0, 1);
  lcd.print(bottomText);

  //stores state of buttons
  int one = digitalRead(choiceOnePin);
  int two = digitalRead(choiceTwoPin);

  if(one == 1){
    delay(200);
    if(two == 1){
      lcd.clear();
      delay(100);
      lcd.setCursor(0, 0);
      lcd.print(choiceOne + " " + numChoiceOne);
      lcd.setCursor(0, 1);
      lcd.print(choiceTwo + " " + numChoiceTwo);
      delay(5000);
      one = digitalRead(choiceOnePin);
      two = digitalRead(choiceTwoPin);
      if(two == 1 && one == 1){
        lcd.clear();
        lcd.print("Clearing memory");
        delay(2000);
        EEPROMWriteInt(0, 0);
        EEPROMWriteInt(10, 0);
        numChoiceOne = 0;
        numChoiceTwo = 0;
      }
      lcd.clear();
      return;
    }
    lcd.clear();
    delay(300);
    lcd.print("You chose:");
    delay(300);
    lcd.setCursor(0, 1);
    lcd.print(choiceOne);
    delay(1000);
    lcd.clear();
    delay(300);
    lcd.print("Calculating");
    lcd.setCursor(0, 1);
    lcd.print("results...");
    delay(700);

    EEPROMWriteInt(0, ++numChoiceOne);

    lcd.clear();
    delay(300);
    lcd.setCursor(0, 0);
    lcd.print(choiceOne + " " + numChoiceOne);
    lcd.setCursor(0, 1);
    lcd.print(choiceTwo + " " + numChoiceTwo);
    delay(5000);
    lcd.clear();
  }

  if(two == 1){
    delay(200);
    if(one == 1){
      lcd.clear();
      delay(100);
      lcd.setCursor(0, 0);
      lcd.print(choiceOne + " " + numChoiceOne);
      lcd.setCursor(0, 1);
      lcd.print(choiceTwo + " " + numChoiceTwo);
      delay(5000);
      one = digitalRead(choiceOnePin);
      two = digitalRead(choiceTwoPin);
      if(two == 1 && one == 1){
        lcd.clear();
        lcd.print("Clearing memory");
        delay(2000);
        EEPROMWriteInt(0, 0);
        EEPROMWriteInt(10, 0);
        numChoiceOne = 0;
        numChoiceTwo = 0;
      }
      lcd.clear();
      return;
    }
    lcd.clear();
    delay(300);
    lcd.print("You chose:");
    delay(300);
    lcd.setCursor(0, 1);
    lcd.print(choiceTwo);
    delay(1000);
    lcd.clear();
    delay(300);
    lcd.print("Calculating");
    lcd.setCursor(0, 1);
    lcd.print("results...");
    delay(700);

    EEPROMWriteInt(10, ++numChoiceTwo);

    lcd.clear();
    delay(300);
    lcd.setCursor(0, 0);
    lcd.print(choiceOne + " " + numChoiceOne);
    lcd.setCursor(0, 1);
    lcd.print(choiceTwo + " " + numChoiceTwo);
    delay(5000);
    lcd.clear();
  }

}

// Function to write an integer to EEPROM
void EEPROMWriteInt(int address, int value) {
  EEPROM.write(address, lowByte(value));       // Write low byte
  EEPROM.write(address + 1, highByte(value));  // Write high byte
  //EEPROM.commit();  // This line is essential for some Arduino boards like the ESP8266
}

// Function to read an integer from EEPROM
int EEPROMReadInt(int address) {
  byte lowByteValue = EEPROM.read(address);       // Read low byte
  byte highByteValue = EEPROM.read(address + 1);  // Read high byte
  return (lowByteValue | (highByteValue << 8));  // Combine bytes into an integer
}


//extra

// print the number of seconds since reset: millis() / 1000
