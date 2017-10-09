/* PJRC Documention for keyboard HID: https://www.pjrc.com/teensy/td_keyboard.html */

// A potentiometer generally has three posts / connection points
// you want to use. One goes to ground, one goes to your voltage
// (3.3V for the Teensy LC or Teensy 3.2) and the final one (usually the middle post)
// that goes to your analog pin for reading.

// This example will show how you can press a keyboard button at different speeds using
// a potentiometer. We are using the right arrow as a simple way to see the effects.

// The analog pin to read from to control a mouse axis.
const int kAnalogPin = A0;

// The minimum analog pin value we can read.
const int kMinReadValue = 0;

// The maximum analog pin value we can read.
const int kMaxReadValue = 1023;

// The minimum interval speed for pressing keys.
const int kMinPressInterval = 500;

// The maximum interval speed for pressing keys.
const int kMaxPressInterval = 10;

// The interval in milliseconds for how quickly the keys will be pressed.
elapsedMillis _keyPressElapsed = 0;

// The current key press interval.
int _keyPressInterval = 0;

void setup() {
}

void loop() {
  // Read values from our analog pins. (0 - 1023 is the range).
  int value = analogRead(kAnalogPin);

  // You can learn more about that function here: https://www.arduino.cc/en/Reference/Map
  _keyPressInterval = map(value, kMinReadValue, kMaxReadValue, kMinPressInterval, kMaxPressInterval);
  
  // Only perform read logic every interval.
  if (_keyPressElapsed >= _keyPressInterval) {
    _keyPressElapsed = 0;

    Keyboard.press(KEY_RIGHT);
    Keyboard.release(KEY_RIGHT);
  }
}
