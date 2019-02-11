/*
 * Bounce2
 *
 * This is a basic button example showing how to use the Bounce2 library.
 * 
 * Details: https://github.com/thomasfredericks/Bounce2
 * 
 * Teensy HID keyboard docs: https://www.pjrc.com/teensy/td_keyboard.html
 * Teensy HID mouse docs: https://www.pjrc.com/teensy/td_mouse.html
 */

#include <Bounce2.h>

// The digital pin we will connect the button to.
const int kBtnPin = 2;

// The number of milliseconds to debounce buttons presses.
const int kDebounceMillis = 10;

// Create a button we can use.
Bounce _button = Bounce();

// The setup routine runs once when you press reset
// or open the serial monitor.
void setup() {
  // Set the pin our button is using.
  // We want to use INPUT_PULLUP and not just INPUT
  // because this tells the pin to stay at high voltage
  // when not being pressed (when it is normally open).
  _button.attach(kBtnPin, INPUT_PULLUP);

  // Set the debounce interval in milliseconds.
  // This indicates how many milliseconds a signal
  // change must be stable before the event occurs.
  _button.interval(kDebounceMillis);
}

// the loop routine runs over and over again forever:
void loop() {
  // Update the state of our button.
  _button.update();

  // Check the state of our button.
  if (_button.fell()) { // The button was pressed!
    // Commit the currently selected character index.
    Keyboard.press(KEY_A);
  } else if (_button.rose()) { // The button was released!
    Keyboard.release(KEY_A);
  }
}
