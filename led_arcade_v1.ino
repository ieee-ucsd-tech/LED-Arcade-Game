// LED Arcade Game v1

int ledPins[11] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int buttonPin = 13;
int speedPin = A0;

int ledIndex = 0; // index of current led on
int change = 1; // increment/decrement for leds
int buttonState; // button pressed (HIGH/LOW)
int gameSp; // game speed from potentiometer
int gameCount = 0; // number of games played

void setup() {
  Serial.begin(9600);

  for (int i : ledPins) {
    pinMode(i, OUTPUT);
  }

  pinMode(buttonPin, INPUT);
}

void loop() {
  // set game speed from potentiometer
  gameSp = map(analogRead(speedPin), 0, 1023, 25, 100);
  
  runLed();
  checkButton();
}

// control LED running back and forth
void runLed() {
  digitalWrite(ledPins[ledIndex], HIGH);
  delay(gameSp);
  digitalWrite(ledPins[ledIndex], LOW);
  
  ledIndex += change;
  if (ledIndex == 10) {
    change = -1;
  }
  else if (ledIndex == 0) {
    change = 1;
  }
}

// check button pressed
void checkButton() {
  buttonState = digitalRead(buttonPin); // read button
  
  if (buttonState == HIGH) {
    gameCount++;
    Serial.print("Attempt #");
    Serial.print(gameCount);
    Serial.print(": ");

    // player wins if button pressed when middle LED on
    if (ledIndex == 5) {
      win();
    }
    else {
      lose();
    }

    // reset game
    ledIndex = 0;
    change = 1;
    delay(1000);
  }
}

// LED pattern when player wins
void win() {
  Serial.println("You win!");
  
  digitalWrite(ledPins[5], HIGH);
  for (int j = 0; j < 3; j++) {
    for (int i = 1; i <= 5; i++) {
      digitalWrite(ledPins[5+i], HIGH);
      digitalWrite(ledPins[5-i], HIGH);
      delay(50);
      digitalWrite(ledPins[5+i], LOW);
      digitalWrite(ledPins[5-i], LOW);
    }
    for (int i = 4; i > 1; i--) {
      digitalWrite(ledPins[5+i], HIGH);
      digitalWrite(ledPins[5-i], HIGH);
      delay(50);
      digitalWrite(ledPins[5+i], LOW);
      digitalWrite(ledPins[5-i], LOW);
    }
  }
  digitalWrite(ledPins[5], LOW);
}

// blink LED when player loses
void lose() {
  Serial.println("You lose!");
  
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[ledIndex], HIGH);
    delay(100);
    digitalWrite(ledPins[ledIndex], LOW);
    delay(100);
  }
}
