#define LED_PIN 3
#define MODE_SWITCH 2
#define NUM_STATES 5   // 5 = random will be there, 4 = no random
#define FULL_PWM 255   // 255 full brightness
#define MAX_PWM 153    // 60% = 153/255 | this is basically brightness for the continuous on.
#define STROBE_HZ 11   // 10
#define SAW_HZ 5       //  5
#define RAND_HZ 30     // 30

int state = 0;
bool ModePressed = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(MODE_SWITCH, INPUT_PULLUP);
  randomSeed(analogRead(0));
}

void loop() {
  //handle the button
  if (!ModePressed && !digitalRead(MODE_SWITCH)) {
    ModePressed = true;
    state = (state + 1) % NUM_STATES;
    Serial.println(state);
  }

  // handle the states
  switch (state) {
    case 0: // off
      analogWrite(LED_PIN, 0);
    break;
    case 1: // on
      analogWrite(LED_PIN, MAX_PWM);
    break;
    case 2: // strobe
      analogWrite(LED_PIN, ((millis()*STROBE_HZ/500)%2)*FULL_PWM);
    break;
    case 3: // saw
      analogWrite(LED_PIN, FULL_PWM - ((millis()*SAW_HZ*FULL_PWM/1000)%(FULL_PWM+1)));
    break; 
    case 4: //random
    if ((millis()*RAND_HZ/500)%2)
       analogWrite(LED_PIN, FULL_PWM*random(2));
    break;
  }

  // delay for debouncing and button handling
  delay(5);
  if(digitalRead(MODE_SWITCH)) {
    ModePressed = false;
  }
}
