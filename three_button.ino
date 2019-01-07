/*
 * Purpose: To run the sequence for the Three-Button challenge in the Obstacle Course, Pi Wars 2019
 * Author: Michael Horne
 */
int max_time_for_sequence = 60000;
int iterate_time_since_start = 0;
int time_since_start = 0;

// Maintain state of buttons. (1 is 'has been pressed')
int red_button_state = 0;
int yellow_button_state = 0;
int green_button_state = 0;

// relays (HIGH is OFF)
int LED_PIN_red_button = 2;
int LED_PIN_yellow_button = 7;
int LED_PIN_green_button = 8;
// spare relay on 10;

// ordinary LEDs
int LED_PIN_red_backup = 11;
int LED_PIN_yellow_backup = 12;
int LED_PIN_green_backup = 13;
byte ledPins[6] = {
  LED_PIN_red_button, LED_PIN_yellow_button, LED_PIN_green_button,
  LED_PIN_red_backup, LED_PIN_yellow_backup, LED_PIN_green_backup
};

// Buzzer
int BUZZER_PIN = 3;

// Button inputs
int BUTTON_red = 4;
int BUTTON_yellow = 5;
int BUTTON_green = 6;
byte buttonPins[3] = {
  BUTTON_red, BUTTON_yellow, BUTTON_green
};

int button_read = 0;

void setup() {
  for(int i=0; i<6; i++)
    pinMode(ledPins[i], OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  for(int i=0; i<3; i++) {
    pinMode(buttonPins[i], INPUT);
    /* activate pull-up resistor */
    digitalWrite(buttonPins[i], HIGH);
  }
}

void reset() {
  // Turn on all button and backup LEDs.
  digitalWrite(LED_PIN_red_button, LOW);
  digitalWrite(LED_PIN_yellow_button, LOW);
  digitalWrite(LED_PIN_green_button, LOW);
  digitalWrite(LED_PIN_red_backup, HIGH);
  digitalWrite(LED_PIN_yellow_backup, HIGH);
  digitalWrite(LED_PIN_green_backup, HIGH);

  red_button_state = 0;
  yellow_button_state = 0;
  green_button_state = 0;

  iterate_time_since_start = 0;
  time_since_start = 0;

  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  // 0 for a button is 'pressed'
  button_read = digitalRead(BUTTON_red);
  if ((button_read == 0) || (red_button_state == 1)) {
    if (red_button_state == 1) {
      digitalWrite(LED_PIN_red_button, HIGH);
      digitalWrite(LED_PIN_red_backup, LOW);
      red_button_state = 1;
      iterate_time_since_start = 1;
    }

    button_read = digitalRead(BUTTON_yellow);
    if ((button_read == 0) || (yellow_button_state == 1)) {
      if (yellow_button_state == 1) {
        digitalWrite(LED_PIN_yellow_button, HIGH);
        digitalWrite(LED_PIN_yellow_backup, LOW);
        yellow_button_state = 1;
      }

      button_read = digitalRead(BUTTON_red);
      if ((button_read == 0) || (green_button_state == 1)) {
        if (green_button_state == 1) {
          digitalWrite(LED_PIN_green_button, HIGH);
          digitalWrite(LED_PIN_green_backup, LOW);
          green_button_state = 1;

          // sound buzzer for success!
          digitalWrite(BUZZER_PIN, HIGH);
          delay(2000);
          digitalWrite(BUZZER_PIN, LOW);
        }
      }
    }
  }

  if (iterate_time_since_start == 1) {
    time_since_start++;
  }

  if (time_since_start >= max_time_for_sequence) {
    reset();
  }
}
