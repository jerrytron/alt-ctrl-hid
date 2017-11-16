/* PJRC Documention for keyboard HID: https://www.pjrc.com/teensy/td_keyboard.html */

const bool kDebug = true;

// Touch sensing pin (Teensy LC or Teensy 3.x)
const int kTouchPin = A1;

// Value touch sense must exceed to trigger a touched event.
const int kThreshold = 1500;

// How long a temporary character should display until automatically removed.
const int kDebugInterval = 1000;

// How much time elapsed before printing debug.
elapsedMillis _debugElapsed = 0;

// Last state of the touch sense input.
bool _lastIsTouched = false;

void setup() {
}

void loop() {
  // Read values from our touch sensing pin.
  int value = touchRead(kTouchPin);

  if (kDebug) {
    if (_debugElapsed >= kDebugInterval) {
      _debugElapsed = 0;
      Serial.print("Touch Value: ");
      Serial.println(value);
    }
  }

  bool isTouched = false;
  // If value greater than threshold, it is touched.
  if (value >= kThreshold) {
    isTouched = true;
  }
  
  if (isTouched != _lastIsTouched) {
    // A new touched event.
    if (isTouched) {
      if (kDebug) {
        Serial.println("Touch press!");
      }
      Keyboard.press(KEY_T); // <-- Press whatever keyboard key you want!
    } else { // A new touch released event.
      if (kDebug) {
        Serial.println("Touch release!");
      }
      Keyboard.release(KEY_T); // <-- Make sure you release the same key!
    }
  }

  // Save the last touch state.
  _lastIsTouched = isTouched;
}
