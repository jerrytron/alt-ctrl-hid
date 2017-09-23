/* PJRC Documention for mouse HID: https://www.pjrc.com/teensy/td_mouse.html */

// A potentiometer generally has three posts / connection points
// you want to use. One goes to ground, one goes to your voltage
// (3.3V for the Teensy LC or Teensy 3.2) and the final one (usually the middle post)
// that goes to your analog pin for reading.

// The analog pin to read from to control a mouse axis.
const int kAnalogPin = A0;

// The minimum analog pin value we can read.
const int kMinReadValue = 0;

// The maximum analog pin value we can read.
const int kMaxReadValue = 1023;

// The minimum increment to have the mouse move.
const int kMinMouseMove = -127;

// The maximum increment to have the mouse move.
const int kMaxMouseMove = 127;

// The amount of milliseconds before updating the mouse.
const int kIntervalUpdateMillis = 25;

// The amount of milliseconds passed.
// It auto-increments so don't forget to set it to 0!
elapsedMillis _updateElapsed = 0;

void setup() {
}

void loop() {
  // Only perform read logic every interval.
  if (_updateElapsed >= kIntervalUpdateMillis) {
    _updateElapsed = 0;

    int8_t movePixels = 0;

    // Read values from our analog pins. (0 - 1023 is the range).
    int16_t value = analogRead(kAnalogPin);

    // The maximum you can move the mouse for every update is -127 to 127.
    // Since we are working with -512 to 511, we are going to use a special
    // function called "map" that allows us to map one set of values onto another.
    // You can learn more about that function here: https://www.arduino.cc/en/Reference/Map
    movePixels = map(value, kMinReadValue, kMaxReadValue, kMinMouseMove, kMaxMouseMove);

    Serial.print("Value ");
    Serial.print(value);
    Serial.print(" moving mouse ");
    Serial.print(movePixels);
    Serial.println(" pixels.");

    // To change what axis you are moving the mouse pointer,
    // change which argument you provide movePixels to.
    // (x, y) so (movePixels, 0) moves along the X axis,
    // and (0, movePixels) move along the Y axis,
    // or (movePixels, movePixels) will move diagonally!
    Mouse.move(movePixels, 0);
  }
}
