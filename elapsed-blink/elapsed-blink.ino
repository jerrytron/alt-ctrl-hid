/*
  Blink
  
  This is a modified blink example that uses ElapsedTime library
  in order to demonstrate how to create non-blocking logic.

  Details: https://www.pjrc.com/teensy/td_timing_elaspedMillis.html
 */
 
// Pin 13 has the LED on Teensy LC, 3.1, 3.2
// give it a name:
const int kLedPin = 13;

const int kFrequencyMillis = 1000; // Blink on/off every 1 seconds.
const int kFrequencyMicros = 1000000; // Blink on/off every 1 seconds.

// How much time has passed in milliseconds.
// 1000 milliseconds = 1 second
elapsedMillis sinceBlinkMillis;

// How much time has passed in microseconds.
// 1000000 microseconds = 1000 milliseconds = 1 second
// The example below is commented out, so just uncomment
// it and comment out the current code in loop to try it.
elapsedMicros sinceBlinkMicros;

bool ledState = LOW;

// The setup routine runs once when you press reset.
void setup() {
  // The following lines of code are to check to make
  // sure you are setup to emulate devices like the keyboard
  // and mouse!
  //while (!Serial.available()) {}
  Mouse.screenSize(1920, 1080);
  Keyboard.set_modifier(0);
  
  // Initialize the digital pin as an output.
  pinMode(kLedPin, OUTPUT);

  delay(2000);
  // This code will simply print to the serial monitor
  // (the magnifying glass button in the top right)
  // which Teensy board you are using, in case you aren't sure!
#if defined(__MK20DX256__) // Using Teensy 3.1/3.2
  Serial.println("You are using a Teensy 3.1 or 3.2!");
#elif defined(__MKL26Z64__) // Using Teensy LC
  Serial.println("You are using a Teensy LC!");
#endif
}

// the loop routine runs over and over again forever:
void loop() {

  if (sinceBlinkMillis >= kFrequencyMillis) {
    sinceBlinkMillis = 0;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(kLedPin, ledState);
  }
  
  /*if (sinceBlinkMicros >= kFrequencyMicros) {
    sinceBlinkMicros = 0;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(kLedPin, ledState);
  }*/
}
