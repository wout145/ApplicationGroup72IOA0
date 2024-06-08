// Code for memory game 2
// Make sure you have the LiquidCrystal I2C Library installed (preferably via your Arduino IDE)

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


//BLOCKS TO BUILD
const int sequenceLength = 5; // Default sequence length
int TimeBetweenLights = 300;


//Reward if correct
int WhichLightShouldBlinkCorrect = 5;
int AmountOfBlinksCorrect = 5;
int HowLongEachBlinkCorrect = 300;

//Reward if wrong
int WhichLightShouldBlinkWrong = 2;
int AmountOfBlinksWrong = 10;
int HowLongEachBlinkWrong = 400;





int ledPins[4] = {LED1, LED2, LED3, LED4};
int buttonPins[4] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};
int userSequence[sequenceLength];
int ledSequence[sequenceLength];
bool buttonPressed[4] = {false, false, false, false};
int currentPress = 0;
bool gameStarted = false;
int wrongLedSequence;

void setup() {
  // Setting up LEDs and buttons
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  }
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Welcome to");
  lcd.setCursor(0, 1); // Set cursor to the first column of the second row
  lcd.print("Memory game 2!");
  delay(3000);
  lcd.clear();
  
  lcd.print("Chosen sequence-");
  lcd.setCursor(0, 1);
  lcd.print("length = ");
  lcd.print(sequenceLength);
  
  delay(3000);
  lcd.clear();
  
  lcd.print("Press left");
  lcd.setCursor(0, 1);
  lcd.print("button to start!");
  Serial.begin(9600);
  randomSeed(analogRead(0));
 
  
  
}

void loop() {
  if (!gameStarted && digitalRead(BUTTON1) == HIGH) {
    delay(200); // Debounce delay
    while (digitalRead(BUTTON1) == HIGH); // Wait for button release
    gameStarted = true;
    
    
    lcd.clear();
    lcd.print("Enter your ");
    lcd.setCursor(0, 1);
    lcd.print("sequence now!");
     
    
    getButtonSequence();
    createLedSequence();
    delay(500);
    showLedSequence();
    waitForUserResponse();
  }
}

void getButtonSequence() {
  delay(10);
  currentPress = 0;
  while (currentPress < sequenceLength) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(buttonPins[i]) == HIGH && !buttonPressed[i]) {
        buttonPressed[i] = true;
        userSequence[currentPress] = i;
        currentPress++;
        delay(200); // Debounce delay
      } else if (digitalRead(buttonPins[i]) == LOW) {
        buttonPressed[i] = false;
      }
    }
  }
}

void createLedSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    ledSequence[i] = userSequence[i];
  }
  
  wrongLedSequence = random(0, 2);
  
  if (wrongLedSequence == 1) {
    int wrongLedNr = random(0, sequenceLength);
    int wrongLedValue = random(0, 4);
    if (userSequence[wrongLedNr] == wrongLedValue) {
      wrongLedValue = (wrongLedValue + 1) % 4;
    }

    ledSequence[wrongLedNr] = wrongLedValue; 
  }
}

void showLedSequence() {
  
  
  lcd.clear();
  lcd.print("Got it!");
  delay(2000);
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

  
  for (int i = 0; i < sequenceLength; i++) {
    digitalWrite(ledPins[ledSequence[i]], HIGH);
    delay(TimeBetweenLights);
    digitalWrite(ledPins[ledSequence[i]], LOW);
    delay(500);
  }
  delay(TimeBetweenLights);
}

void blinkAllLeds(int times, int duration) {
  for (int i = 0; i < times; i++) {
    for (int k = 0; k < 4; k++) {
      digitalWrite(ledPins[k], HIGH);
    }
    delay(duration);
    for (int k = 0; k < 4; k++) {
      digitalWrite(ledPins[k], LOW);
    }
    delay(500);
  }
}

void blinkLed(int ledNr, int times, int duration) {
  for (int i = 0; i < times; i++) {
    digitalWrite(ledPins[ledNr], HIGH);
    delay(duration);
    digitalWrite(ledPins[ledNr], LOW);
    if (i < times - 1) {
      delay(500);
    }
  }
}

void waitForUserResponse() {
  lcd.clear();
  lcd.print("Left if correct");
  lcd.setCursor(0, 1);
  lcd.print("Right if wrong");

  while (true) {
    if (digitalRead(BUTTON1) == HIGH) {
      if (wrongLedSequence == 0) {
        lcd.clear();
        delay(500);
        lcd.print("That was");
        lcd.setCursor(0,1);
        lcd.print("correct!");
        blinkAllLeds(AmountOfBlinksCorrect, HowLongEachBlinkCorrect);
      } else {
        lcd.clear();
        delay(500);
        lcd.print("That was");
        lcd.setCursor(0,1);
        lcd.print("wrong...");
        blinkLed(1, 1, 1000);
      }
      break;
    } else if (digitalRead(BUTTON4) == HIGH) {
      if (wrongLedSequence == 1) {
        lcd.clear();
        lcd.print("That was");
        lcd.setCursor(0,1);
        lcd.print("correct!");
        blinkAllLeds(AmountOfBlinksCorrect, HowLongEachBlinkCorrect);
      } else {
        lcd.clear();
        lcd.print("That was");
        lcd.setCursor(0,1);
        lcd.print("wrong...");
        blinkLed(1, 1, 1000);
      }
      break;
    }
  }

  lcd.clear();
  lcd.print("Play again?");
  lcd.setCursor(0, 1);
  lcd.print("left=y, right=n");

  while (true) {
    if (digitalRead(BUTTON1) == HIGH) {
      delay(200); // Debounce delay
      while (digitalRead(BUTTON1) == HIGH); // Wait for button release
      currentPress = 0;
      for (int i = 0; i < 4; i++) {
        buttonPressed[i] = false;
      }
      gameStarted = false;
      lcd.clear();
      lcd.print("Press left btn");
      lcd.setCursor(0, 1);
      lcd.print("to start");
      break;
    } else if (digitalRead(BUTTON4) == HIGH) {
      lcd.clear();
      lcd.print("Game Over!");
      while (true); 
    }
  }
}


