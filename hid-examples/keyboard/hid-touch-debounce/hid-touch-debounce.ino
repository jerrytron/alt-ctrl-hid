/* PJRC Documention for keyboard HID: https://www.pjrc.com/teensy/td_keyboard.html */

const bool kDebug = true;

// Touch sensing pin (Teensy LC or Teensy 3.x)
const int kTouchPin = A1;

// Value touch sense must exceed to trigger a touched event.
const int kThreshold = 1500;

// The number of milliseconds to debounce buttons presses.
const int kDebounceMillis = 10;

// How long a temporary character should display until automatically removed.
const int kDebugInterval = 1000;

// How much time elapsed for debouncing the potentiometer.
elapsedMillis _debounceElapsed = 0;

// How much time elapsed before printing debug.
elapsedMillis _debugElapsed = 0;

// Are we currently debouncing?
bool _debouncing = false;

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
    // Didn't finish debouncing, so assume state didn't change.
    if (_debouncing) {
      _debouncing = false;
    } else {
      // A new state change, start debouncing.
      _debouncing = true;
      _debounceElapsed = 0;
    }
  } else {
    // Finished debouncing, we have a new event!
    if (_debouncing && (_debounceElapsed >= kDebounceMillis)) {
      _debouncing = false;

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
  }

  // Save the last touch state.
  _lastIsTouched = isTouched;
}
