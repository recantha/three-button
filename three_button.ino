/*
   Purpose: To run the sequence for the Three-Button challenge in the Obstacle Course, Pi Wars 2019
   Authors: Michael Horne & Tim Richardson
*/
unsigned long max_time_for_sequence = 60000; //ms
unsigned long start_time = 0;

// Maintain state of buttons. (1 is 'has been pressed')
byte red_button_state = 0;
byte yellow_button_state = 0;
byte green_button_state = 0;

// relays (HIGH is OFF)
byte LED_PIN_red_button = 2;
byte LED_PIN_yellow_button = 7;
byte LED_PIN_green_button = 8;
// spare relay on 10;
byte relayPins[3] = {
  LED_PIN_red_button, LED_PIN_yellow_button, LED_PIN_green_button
};

// ordinary LEDs
byte LED_PIN_red_backup = 11;
byte LED_PIN_yellow_backup = 12;
byte LED_PIN_green_backup = 13;
byte ledPins[3] = {
  LED_PIN_red_backup, LED_PIN_yellow_backup, LED_PIN_green_backup
};

// Buzzer
byte BUZZER_PIN = 3;

// Button inputs
byte BUTTON_red = 4;
byte BUTTON_yellow = 5;
byte BUTTON_green = 6;
byte buttonPins[3] = {
  BUTTON_red, BUTTON_yellow, BUTTON_green
};

// Setup the Arduino interfaces
void setup() {
  // Set the LED pins to output, and turn them all off
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  // Set the Relay pins to output, and turn them all off
  for (int i = 0; i < 3; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);
  }

  pinMode(BUZZER_PIN, OUTPUT);

  // Set the Button pins to input
  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT);
    digitalWrite(buttonPins[i], HIGH); /* activate pull-up resistor */
  }
}

// What to do when all the buttons have been pressed within the allotted time
void success() {
  Serial.print("Success\n");
  for (int i = 0; i <= 5; i++) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    for (int i = 0; i < 3; i++) {
      digitalWrite(relayPins[i], LOW);
    }

    delay(500);
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    for (int i = 0; i < 3; i++) {
      digitalWrite(relayPins[i], HIGH);
    }

    delay(500);
  }
}

void reset() {
  // Set relative clock to 0
  // Turn on all button and backup LEDs.
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(relayPins[i], LOW);
  }

  red_button_state = 0;
  yellow_button_state = 0;
  green_button_state = 0;

  start_time = 0;
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  // 0 for a button is 'pressed'
  if ((digitalRead(BUTTON_red) == 0) || (red_button_state == 1)) {
    if (red_button_state == 0) {
      digitalWrite(LED_PIN_red_button, HIGH);
      digitalWrite(LED_PIN_red_backup, HIGH);
      red_button_state = 1;
      start_time = millis();
    }

    if ((digitalRead(BUTTON_yellow) == 0) || (yellow_button_state == 1)) {
      if (yellow_button_state == 0) {
        digitalWrite(LED_PIN_yellow_button, HIGH);
        digitalWrite(LED_PIN_yellow_backup, HIGH);
        yellow_button_state = 1;
      }

      if ((digitalRead(BUTTON_green) == 0) || (green_button_state == 1)) {
        if (green_button_state == 0) {
          digitalWrite(LED_PIN_green_button, HIGH);
          digitalWrite(LED_PIN_green_backup, HIGH);
          green_button_state = 1;

          // Success!
          success();
          reset();
        }
      }
    }
  }

  if (start_time != 0) {
    if ((millis() - start_time) >= max_time_for_sequence) {
      reset();
    }
  }
}
