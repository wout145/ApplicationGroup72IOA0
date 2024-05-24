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
int userSequence[maxSequenceLength];
int ledSequence[maxSequenceLength];
bool buttonPressed[4] = {false, false, false, false};
int currentPress = 0;
bool gameStarted = false;
int sequenceLength = 0;
int wrongLedSequence;

void setup() {
  
  // Setting up LEDs and buttons
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  }
  
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
}

void loop() {
  askForSequenceLength();
  getButtonSequence();
  showButtonSequence();
  createLedSequence();
  delay(500);
  showLedSequence();
  waitForUserResponse();
  
  
}

void askForSequenceLength() {
  
  Serial.println("Enter the length of your sequence (1-10):");
  while (Serial.available() == 0); // Wait for input
  sequenceLength = Serial.parseInt();
  Serial.print("You entered: ");
  Serial.println(sequenceLength);
  
}

void getButtonSequence() {
  Serial.println("Start pressing buttons to create your sequence...");
  while (currentPress < sequenceLength) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(buttonPins[i]) == HIGH && !buttonPressed[i]) {
        buttonPressed[i] = true;
        userSequence[currentPress] = i;
        currentPress++;
      } else if (digitalRead(buttonPins[i]) == LOW) {
        buttonPressed[i] = false;
      }
    }
  }
}

void showButtonSequence() {
  Serial.print("Your Sequence: ");
  for (int i = 0; i < sequenceLength; i++) {
    Serial.print(userSequence[i]);
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

    ledSequence[wrongLedNr] = wrongLedValue; 
  }
}

void showLedSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    digitalWrite(ledPins[ledSequence[i]], HIGH);
    delay(500);
    digitalWrite(ledPins[ledSequence[i]], LOW);
    delay(500);
  }
}

void blinkLeds(int times, int duration) {
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
    digitalWrite(ledPins[ledNr - 1], HIGH);
    delay(duration);
    digitalWrite(ledPins[ledNr - 1], LOW);
    delay(500);
  }
}

void waitForUserResponse() {
  Serial.println("Press the left button if you think the lights showed the correct sequence,");
  Serial.println("or press the right button if you think the lights showed the wrong sequence.");

  while (true) {
    if (digitalRead(BUTTON1) == HIGH) {
      if (wrongLedSequence == 0) {
        Serial.println("That was correct!");
        blinkLeds(3, 200);
      } else {
        Serial.println("That was wrong...");
        blinkLed(1, 1, 1000);
      }
      break;
    } else if (digitalRead(BUTTON4) == HIGH) {
      if (wrongLedSequence == 1) {
        Serial.println("That was correct!");
        blinkLeds(3, 200);
      } else {
        Serial.println("That was wrong...");
        blinkLed(1, 1, 1000);
      }
      break;
    }
  }

  Serial.println("Do you want to play another round? (y/n)");
  while (true) {
    if (Serial.available() > 0) {
      char response = Serial.read();
      if (response == 'y' || response == 'Y') {
        currentPress = 0;
        for (int i = 0; i < 4; i++) {
          buttonPressed[i] = false;
        }
        break;
      } else if (response == 'n' || response == 'N') {
        Serial.println("Game Over!");
        while (true); 
      }
    }
  }
}