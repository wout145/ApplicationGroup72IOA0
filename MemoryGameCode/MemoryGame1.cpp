#define LED1 8
#define LED2 9
#define LED3 10
#define LED4 11
#define BUTTON1 4
#define BUTTON2 5
#define BUTTON3 6
#define BUTTON4 7

const int maxSequenceLength = 10;
int ledPins[4] = {LED1, LED2, LED3, LED4};
int buttonPins[4] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};
int randomSequence[maxSequenceLength];
int enteredSequence[maxSequenceLength];
bool buttonPressed[4] = {false, false, false, false};
int currentPress = 0;
bool gameStarted = false;
int sequenceLength = 0;

void setup() {
  
  // Setting up LEDs and buttons
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  }
  
  Serial.begin(9600);
  
  askForSequenceLength();
  
  
}

void loop() {
  
  if (Serial.available() > 0) {
    sequenceLength = Serial.parseInt();
    if (sequenceLength > 0 && sequenceLength <= maxSequenceLength) {
      Serial.print("You entered: ");
      Serial.println(sequenceLength);
      gameStarted = true;
    } else {
      Serial.println("Invalid Sequence Length");
      askForSequenceLength();
    }
    
    if (gameStarted) {
      generateRandomSequence();
      showSequence();
      
      while (currentPress < sequenceLength) {
        
        readButtons();
        
      }
      
      if (checkSequence()) {
        
        Serial.println("Correct");
        blinkAllLeds(3, 200);
        
      } else {
        Serial.println("False");
        blinkLed(LED1, 1, 1000);
      }
      
      askForAnotherRound();
      
    }
    
  }
  
  
  
}

void askForSequenceLength() {
 
  int response;
  
  delay(10);

  Serial.println("Please enter a sequence length (0-10)");
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
    delay(500);
    digitalWrite(ledPins[randomSequence[i]], LOW);
    delay(500);
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
    delay(duration);
  }
  
}

void blinkLed(int ledNr, int times, int duration) {
  
  delay(500);
  
  for (int k = 0; k < times; k++) {
    
    digitalWrite(ledNr, HIGH);
    delay(duration);
    digitalWrite(ledNr, LOW);
    delay(duration);
    
  }
}

void askForAnotherRound() {
  
  Serial.println("Do you want to play another round? (y/n): ");
  while (true) {
    if (Serial.available()> 0) {
      char response = Serial.read();
      if (response == 'y' || response == 'Y') {
        for (int i = 0; i < 4; i++) {
          buttonPressed[i] = false;
        }
        currentPress = 0;
        askForSequenceLength();
        break;
      } else if (response == 'n' || response == 'N') {
        Serial.println("Game Over");
        while(true);
      } 
    }
  }
  
}
