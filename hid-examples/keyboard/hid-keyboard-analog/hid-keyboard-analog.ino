/* PJRC Documention for keyboard HID: https://www.pjrc.com/teensy/td_keyboard.html */

// A potentiometer generally has three posts / connection points
// you want to use. One goes to ground, one goes to your voltage
// (3.3V for the Teensy LC or Teensy 3.2) and the final one (usually the middle post)
// that goes to your analog pin for reading.

// This example will show how you can use a potentiometer and a button to make full
// alphabet keyboard! You will turn the pot to select a letter which will briefly print
// as text and delete itself, and press the button to keep the selected letter.

#include <Bounce2.h>

// Size of our keys array.
const int kKeyCount = 26;

// Our array of keys we want the potentiometer to cycle through.
const int kKeys[] = { KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G,
                      KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N,
                      KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U,
                      KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z };

// The analog pin to read from to control a mouse axis.
const int kAnalogPin = A0;

// The minimum analog pin value we can read.
const int kMinReadValue = 0;

// The maximum analog pin value we can read.
const int kMaxReadValue = 1023;

// The digital pin to use for the button.
const int kDigitalPin = 15;

// The number of milliseconds to debounce buttons presses.
const int kDebounceMillis = 10;

// How long a temporary character should display until automatically removed.
const int kTimeoutMillis = 1000;

// Defining our button - first argument is the digital pin, the second is
// how many milliseconds to debounce. That means how long to wait before we
// are sure the signal change isn't noise, but an ACTUAL press.
Bounce _button = Bounce();

// The last index read by the potentiometer.
int _lastIndex = 0;

// How much time elapsed for debouncing the potentiometer.
elapsedMillis _debounceElapsed = 0;

// Are we currently debouncing?
bool _debouncing = false;

// How many temporary characters are we displaying?
int _chars = 0;

// How much time has passed to check for a timeout?
elapsedMillis _timeoutElapsed = 0;

void setup() {
  // Setup the digital pin our button is connected to.
  // We want to use INPUT_PULLUP and not just INPUT
  // because this tells the pin to stay at high voltage,
  // so when the button is pressed (and connected to ground)
  // it has a clean change from high voltage (3.3V here) and
  // ground (0V).
  _button.attach(kDigitalPin,INPUT_PULLUP)
  _button.interval(kDebounceMillis)
}

void loop() {
  // Update the state of our button.
  _button.update();
  
  // Read values from our analog pins. (0 - 1023 is the range).
  int value = analogRead(kAnalogPin);

  // Map the read value to one of our key indexes.
  int index = map(value, kMinReadValue, kMaxReadValue, 0, kKeyCount - 1);

  if (index != _lastIndex) {
    if (_debouncing) {
      _debouncing = false;
    } else {
      _debouncing = true;
      _debounceElapsed = 0;
    }
  } else {
    if (_debouncing && (_debounceElapsed >= kDebounceMillis)) {
      _debouncing = false;

      // If we are selecting a new character,
      // remove any temporary characters.
      while (_chars > 0) {
        Keyboard.press(KEY_BACKSPACE);
        Keyboard.release(KEY_BACKSPACE);
        _chars--;
      }
      
      Keyboard.press(kKeys[index]);
      Keyboard.release(kKeys[index]);
      _chars++;
      _timeoutElapsed = 0;
    }
  }

  // Save the latest index from our read.
  _lastIndex = index;

  // If the user just waits, eventually the temp character
  // will be deleted.
  if ((_chars > 0) && (_timeoutElapsed >= kTimeoutMillis)) {
    while (_chars > 0) {
      Keyboard.press(KEY_BACKSPACE);
      Keyboard.release(KEY_BACKSPACE);
      _chars--;
    }
  }

  // Check the state of our button.
  if (_button.fell()) { // The button was pressed!
    // Commit the currently selected character index.
    Keyboard.press(kKeys[index]);
    // Reset the timeout so a temp character will still display.
    _timeoutElapsed = 0;
  } else if (_button.rose()) { // The button was released!
    Keyboard.release(kKeys[index]);
  }
}
