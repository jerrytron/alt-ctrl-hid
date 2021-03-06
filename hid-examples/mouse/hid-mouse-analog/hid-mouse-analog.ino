/* PJRC Documention for mouse HID: https://www.pjrc.com/teensy/td_mouse.html */

// A potentiometer generally has three posts / connection points
// you want to use. One goes to ground, one goes to your voltage
// (3.3V for the Teensy LC or Teensy 3.2) and the final one (usually the middle post)
// that goes to your analog pin for reading.

// Debug logging enabled.
const bool kDebug = true;

// For testing. You can turn off movement for either axis.
const bool kAxisXOff = false;
const bool kAxisYOff = false;

// The analog pin to read from for the X axis.
const int kAnalogXPin = A0;

// The analog pin to read from for the Y axis.
const int kAnalogYPin = A1;

// The minimum increment to have the mouse move.
const int kMinMouseMove = 1;

// The maximum increment to have the mouse move.
const int kMaxMouseMove = 25;

// The low end of the movement 'dead zone'.
const int kMoveThresholdLow = -100;

// The high end of the movement 'dead zone'.
const int kMoveThresholdHigh = 100;

// The amount of milliseconds before updating the mouse.
const int kIntervalUpdateMillis = 25;

// The maximum value we will read from the analog pins.
const int kOffsetValue = 512; // About half of the max read value.

// The amount of milliseconds passed.
// It auto-increments so don't forget to set it to 0!
elapsedMillis _updateElapsed = 0;

// The last move on the X axis.
int _lastMoveX = 0;

// The last move on the Y axis.
int _lastMoveY = 0;

void setup() {
}

void loop() {
  // Only perform update logic every interval.
  if (_updateElapsed >= kIntervalUpdateMillis) {
    _updateElapsed = 0;

    int moveX = 0;
    int moveY = 0;

    // Read values from our analog pins. (0 - 1023 is the range).
    // To normalize the values (negative to positive range with around
    // zero being the resting, or dead zone), we will subtract half of
    // the maximum read value. Negative will map to negative movement,
    // positive to positive movement!
    int valueX = analogRead(kAnalogXPin) - kOffsetValue;
    int valueY = analogRead(kAnalogYPin) - kOffsetValue;

    if (valueX <= kMoveThresholdLow) {
      // Map our read value from one range to another. Our value range is about -100 to -512,
      // and we want the equivalent value in the range of our min and max mouse movement.
      // You can learn more about that function here: https://www.arduino.cc/en/Reference/Map
      moveX = map(valueX, kMoveThresholdLow, -kOffsetValue, -kMinMouseMove, -kMaxMouseMove);
      if (kDebug && !kAxisXOff) {
        Serial.print("Value ");
        Serial.print(valueX);
        Serial.print(" in ");
        Serial.print(kMoveThresholdLow);
        Serial.print(" -> ");
        Serial.print(-kOffsetValue);
        Serial.print(" maps to ");
        Serial.print(moveX);
        Serial.print(" in ");
        Serial.print(-kMinMouseMove);
        Serial.print(" -> ");
        Serial.println(-kMaxMouseMove);
      }
    } else if (valueX >= kMoveThresholdHigh) {
      // Map our read value from one range to another. Our value range is about 100 to 512,
      // and we want the equivalent value in the range of our min and max mouse movement.
      moveX = map(valueX, kMoveThresholdHigh, kOffsetValue, kMinMouseMove, kMaxMouseMove);
      if (kDebug && !kAxisXOff) {
        Serial.print("Value ");
        Serial.print(valueX);
        Serial.print(" in ");
        Serial.print(kMoveThresholdHigh);
        Serial.print(" -> ");
        Serial.print(kOffsetValue);
        Serial.print(" maps to ");
        Serial.print(moveX);
        Serial.print(" in ");
        Serial.print(kMinMouseMove);
        Serial.print(" -> ");
        Serial.println(kMaxMouseMove);
      }
    } else {
      moveX = 0;
    }

    if (valueY <= kMoveThresholdLow) {
      // Map our read value from one range to another. Our value range is about -100 to -512,
      // and we want the equivalent value in the range of our min and max mouse movement.
      moveY = map(valueY, kMoveThresholdLow, -kOffsetValue, -kMinMouseMove, -kMaxMouseMove);
      if (kDebug && !kAxisYOff) {
        Serial.print("Value ");
        Serial.print(valueY);
        Serial.print(" in ");
        Serial.print(kMoveThresholdLow);
        Serial.print(" -> ");
        Serial.print(-kOffsetValue);
        Serial.print(" maps to ");
        Serial.print(moveY);
        Serial.print(" in ");
        Serial.print(-kMinMouseMove);
        Serial.print(" -> ");
        Serial.println(-kMaxMouseMove);
      }
    } else if (valueY >= kMoveThresholdHigh) {
      // Map our read value from one range to another. Our value range is about 100 to 512,
      // and we want the equivalent value in the range of our min and max mouse movement.
      moveY = map(valueY, kMoveThresholdHigh, kOffsetValue, kMinMouseMove, kMaxMouseMove);
      if (kDebug && !kAxisYOff) {
        Serial.print("Value ");
        Serial.print(valueY);
        Serial.print(" in ");
        Serial.print(kMoveThresholdHigh);
        Serial.print(" -> ");
        Serial.print(kOffsetValue);
        Serial.print(" maps to ");
        Serial.print(moveY);
        Serial.print(" in ");
        Serial.print(kMinMouseMove);
        Serial.print(" -> ");
        Serial.println(kMaxMouseMove);
      }
    } else {
      moveY = 0;
    }

    // Reset movement values if an axis is off.
    if (kAxisXOff) { moveX = 0; }
    if (kAxisYOff) { moveY = 0; }

    _lastMoveX = moveX;
    _lastMoveY = moveY;

    Mouse.move(_lastMoveX, _lastMoveY);
  }
}
