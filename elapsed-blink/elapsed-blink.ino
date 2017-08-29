/*
  Blink
  
  This is a modified blink example that uses ElapsedTime library
  in order to demonstrate how to create non-blocking logic.

  Details: https://www.pjrc.com/teensy/td_timing_elaspedMillis.html
 */
 
// Pin 13 has the LED on Teensy LC, 3.1, 3.2
// give it a name:
const int kLedPin = 13;

const int kFrequencyMillis = 2000; // Blink on/off every 2 seconds.
const int kFrequencyMicros = 2000000; // Blink on/off every 2 seconds.

// How much time has passed in milliseconds.
// 1000 milliseconds = 1 second
elapsedMillis sinceBlinkMillis;

// How much time has passed in microseconds.
// 1000000 microseconds = 1000 milliseconds = 1 second
elapsedMillis sinceBlinkMicros;

bool ledState = LOW;

// The setup routine runs once when you press reset.
void setup() {                
  // Initialize the digital pin as an output.
  pinMode(kLedPin, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {

  if (sinceBlinkMillis >= kFrequencyMillis) {
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(kLedPin, ledState);
  }
  
  /*if (sinceBlinkMicros >= kFrequencyMicros) {
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(kLedPin, ledState);
  }*/
}
