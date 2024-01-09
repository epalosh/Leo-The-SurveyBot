//Door survey bot w/ LCD screen
//by Ethan Palosh

//To change each day:
///////////////////////////////
///////////////////////////////
///////////////////////////////

//Questions are asked in a "this or that" format
String choiceOne = "Spotify";
String choiceTwo = "Apple Music";
String bottomText = "----------------------------------------";
//LCD lines are 40 characters long
///////////////////////////////
///////////////////////////////
///////////////////////////////

/* List of functions:

void clearMemorySequence(int &numchoiceOne, const int addressOne, int &numchoiceTwo, const int addressTwo)
void selectionSequence(const String choice, const int memoryAddress, int &count)
void displayCalculating(int msDelay)
void EEPROMWriteInt(int address, int value)
int EEPROMReadInt(int address)

*/

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

const int ledPin = 10;

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

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
}

//main loop
void loop() {

  //LCD setup and delay for scroll
  lcd.scrollDisplayLeft();
  lcd.setCursor(0, 0);
  delay(200);
  
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  //idle message
  lcd.print(choiceOne + " or " + choiceTwo + "?" + "      Vote!!");
  //additional info if added
  lcd.setCursor(0, 1);
  lcd.print(bottomText);

  //checks and stores state of buttons each iteration of the loop
  int one = digitalRead(choiceOnePin);
  int two = digitalRead(choiceTwoPin);

  //conditionals:


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

      //rechecks the buttons' state
      one = digitalRead(choiceOnePin);
      two = digitalRead(choiceTwoPin);
      //if they are still depressed, clear memory
      if(two == 1 && one == 1){
        clearMemorySequence(numChoiceOne, 0, numChoiceTwo, 10);
      }
      return;
    }

    selectionSequence(choiceOne, 0, numChoiceOne);

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
        clearMemorySequence(numChoiceOne, 0, numChoiceTwo, 10);
      }
      return;
    }

    selectionSequence(choiceTwo, 10, numChoiceTwo);

    delay(300);
    lcd.setCursor(0, 0);
    lcd.print(choiceOne + " " + numChoiceOne);
    lcd.setCursor(0, 1);
    lcd.print(choiceTwo + " " + numChoiceTwo);
    delay(5000);
    lcd.clear();
  }
}







//functions!!

//clears system memory
void clearMemorySequence(int &numchoiceOne, const int addressOne, int &numchoiceTwo, const int addressTwo) {
  lcd.clear();
  lcd.print("Clearing memory");
  delay(2000);
  EEPROMWriteInt(addressOne, 0);
  EEPROMWriteInt(addressTwo, 0);
  numChoiceOne = 0;
  numChoiceTwo = 0;
  lcd.clear();
}

//Registers the selection and shows the user. Then increments the selection count in memory
void selectionSequence(const String choice, const int memoryAddress, int &count) {
  lcd.clear();
  delay(300);
  lcd.print("You chose:");
  delay(300);
  lcd.setCursor(0, 1);
  lcd.print(choice);
  delay(1000);
  lcd.clear();

  displayCalculating(700);

  EEPROMWriteInt(memoryAddress, ++count);

  lcd.clear();
}

/*
//displays the current results
void displayResults(const String choiceOne, const int numChoiceOne, const String choiceTwo, const int numChoiceTwo, int msTime) {
  lcd.setCursor(0, 0);
  lcd.print(choiceOne + " " + numChoiceOne);
  lcd.setCursor(0, 1);
  lcd.print(choiceTwo + " " + numChoiceTwo);
  delay(msTime);
}
*/

//Displays "Calculating..." on the screen for a determined amount of time
void displayCalculating(int msDelay) {
  lcd.setCursor(0, 0);
  lcd.print("Calculating...");
  delay(msDelay);
  lcd.clear();
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
