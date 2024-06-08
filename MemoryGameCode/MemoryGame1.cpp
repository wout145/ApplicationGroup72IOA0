// Code for memory game 1
// Make sure you have the LiquidCrystal I2C library installed (via your arduino IDE)

#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); 


#define LED1 A0
#define LED2 A1
#define LED3 A2
#define LED4 A3
#define BUTTON1 5
#define BUTTON2 4
#define BUTTON3 3
#define BUTTON4 2

const int maxSequenceLength = 10;
int ledPins[4] = {LED1, LED2, LED3, LED4};
int buttonPins[4] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};
int randomSequence[maxSequenceLength];
int enteredSequence[maxSequenceLength];
bool buttonPressed[4] = {false, false, false, false};
int currentPress = 0;
bool gameStarted = false;

//BLOCKS TO BE BUILD:
int sequenceLength = 3;
int TimeBetweenLights = 500;

//Reward if correct
int WhichLightShouldBlinkCorrect = 5;
int AmountOfBlinksCorrect = 5;
int HowLongEachBlinkCorrect = 300;

//Reward if wrong
int WhichLightShouldBlinkWrong = 2;
int AmountOfBlinksWrong = 10;
int HowLongEachBlinkWrong = 400;

void setup() {
  // Initialize LCD and turn on the backlight:
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
    // Setting up LEDs and buttons
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  }

    lcd.setCursor(0, 0); // Set cursor to the first column of the first row
    lcd.print("Welcome to");
    lcd.setCursor(0, 1); // Set cursor to the first column of the second row
    lcd.print("Memory game 1!");
    Serial.begin(9600);
    randomSeed(analogRead(0));
	delay(2000); // Wait for 2 seconds
  
      //askForSequenceLength();
  

}

void loop() {
  
  if (sequenceLength > 0) {
    sequenceLength = sequenceLength;
    if (sequenceLength > 0 && sequenceLength <= maxSequenceLength) {
      lcd.clear();
	  lcd.print("Chosen sequence-");
	  lcd.setCursor(0, 1);
	  lcd.print("length = ");
      lcd.print(sequenceLength);
      gameStarted = true;
    } else {
      lcd.clear();
      lcd.print("Invalid Sequence Length");
      //askForSequenceLength();
    }
    
    if (gameStarted) {
      generateRandomSequence();
      SequenceCountDown();
      showSequence();
      
      lcd.print("Enter your");
      lcd.setCursor(0,1);
      lcd.print("answer now!");
      
      while (currentPress < sequenceLength) {
        
        readButtons();
        
      }
      
      if (checkSequence()) {
        
        lcd.clear();
        delay(500);
        lcd.print("That was");
        lcd.setCursor(0,1);
        lcd.print("correct!");
        blinkAllLeds(AmountOfBlinksCorrect, HowLongEachBlinkCorrect);
        
        askForAnotherRound();
        
        
      } else {
        
        lcd.clear();
        delay(500);
        lcd.print("That was");
        lcd.setCursor(0,1);
        lcd.print("wrong...");
        
        if (WhichLightShouldBlinkWrong == 1){
          blinkLed(LED1, AmountOfBlinksWrong, HowLongEachBlinkWrong);
          }
        else if (WhichLightShouldBlinkWrong == 2){
          blinkLed(LED2, AmountOfBlinksWrong, HowLongEachBlinkWrong);
          }
        
        else if (WhichLightShouldBlinkWrong == 3){
          blinkLed(LED3, AmountOfBlinksWrong, HowLongEachBlinkWrong);
          }
        
        else if (WhichLightShouldBlinkWrong == 4){
          blinkLed(LED4, AmountOfBlinksWrong, HowLongEachBlinkWrong);
          }        
        else {
          blinkAllLeds(AmountOfBlinksWrong, HowLongEachBlinkCorrect);       
      	  }
        
        askForAnotherRound();
      	        
      }
      
    } 

  }  

}

void SequenceCountDown() {
  delay(3000); //Delay while showing text "you entered"
  lcd.clear();
  lcd.print("Showing sequence");
  lcd.setCursor(0, 1); // Set cursor to the first column of the second row
  lcd.print("in...");
  delay(1500);
  lcd.clear();
  lcd.print("3...");
  delay(1000);
  lcd.clear();
  lcd.print("2...");
  delay(1000);
  lcd.clear();
  lcd.print("1...");
  delay(1000);
  lcd.clear();
  delay(1000);
}
  
  

void askForSequenceLength() {//NOT USED IN THE CURRENT GAME
 
  int response;
  
  delay(1000);
  lcd.clear();
  

  lcd.setCursor(0, 0); // Set cursor to the first column of the first row
  lcd.print("Enter sequence");
  lcd.setCursor(0, 1); // Set cursor to the first column of the second row
  lcd.print("length 0-10");
  Serial.begin(9600);
  randomSeed(analogRead(0)); 
  
  

  while(Serial.available() > 0) {
    Serial.read();
  }
  
  gameStarted = false;
  
  
}

void generateRandomSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    randomSequence[i] = random(0, 4);
  }  
}

void showSequence() {
    
  for (int i = 0; i < sequenceLength; i++) {
    digitalWrite(ledPins[randomSequence[i]], HIGH);
    delay(TimeBetweenLights);
    digitalWrite(ledPins[randomSequence[i]], LOW);
    delay(TimeBetweenLights);
  }
  
  currentPress = 0;
  
}

void readButtons() {
  
  for (int i = 0; i < 4; i++) {
    
    if (digitalRead(buttonPins[i]) == HIGH && !buttonPressed[i]) {      
      buttonPressed[i] = true;
      enteredSequence[currentPress] = i;
      currentPress++;      
    } else if (digitalRead(buttonPins[i]) == LOW) {      
      buttonPressed[i] = false;      
    }  
    
  }  
}

bool checkSequence() {
  
  for (int i = 0; i < sequenceLength; i++) {
    if (enteredSequence[i] != randomSequence[i]) {
      return false;
    }
  }
  
  return true;
}

void blinkAllLeds(int times, int duration) {
  
  delay(500);
  
  for (int k = 0; k < times; k++) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    delay(duration);
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    delay(500);
  }
  
}

void blinkLed(int ledNr, int times, int duration) {
  
  delay(500);
  
  for (int k = 0; k < times; k++) {
    
    digitalWrite(ledNr, HIGH);
    delay(duration);
    digitalWrite(ledNr, LOW);
    delay(500);
    
  }
}

void askForAnotherRound() {
  
  lcd.clear();
  lcd.print("Play again?");
  lcd.setCursor(0,1);
  delay(1500);
  lcd.print("left=y right=n");
  
  

  while (true) {
    if (digitalRead(BUTTON1) == HIGH) { // Left button for "yes"
      for (int i = 0; i < 4; i++) {
        buttonPressed[i] = false;
      }
      currentPress = 0;
      //askForSequenceLength();
      break;
    } else if (digitalRead(BUTTON4) == HIGH) { // Right button for "no"
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Game Over");
      while (true); // Infinite loop to end the game
    }
    delay(50); // Debounce delay
  }
}