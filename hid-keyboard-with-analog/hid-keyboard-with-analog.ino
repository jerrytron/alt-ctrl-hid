// See this link for a comprehensive guide:
// https://www.pjrc.com/teensy/td_keyboard.html

// MOUSE MOVEMENT
//
// You can move the mouse easily, providing the X and X amount
// the cursor should be moved with a given action. Keep in mind,
// for smooth movement, many small motions should occur.
// Mouse.move(X, Y) allows for each value a range of: -127 to 127
// CODE -> Mouse.move(4, -2);
//
// Simple Click
// CODE -> Mouse.click();
//
// Advanced Click
// You can click left, middle, and right buttons. Here you can set
// which of those buttons are pressed. Remember to unpress by setting to 0!
// Mouse.set_buttons(LEFT, MIDDLE, RIGHT)
// CODE -> Mouse.set_buttons(0, 0, 1); // Right click.
// CODE -> Mouse.set_buttons(0, 0, 0); // Right release.
//
// Scrolling
// You can use the scroll wheel, positive values scroll up,
// negative values scroll down.
// CODE -> Mouse.scroll(-3);

// EASY KEYBOARD PRESSES
//
// You can send keyboard commands by using:
// CODE -> Keyboard.print("Hello");
// CODE -> Keyboard.println(" World");
// This will print on your computer: "Hello World" then hit enter.
// All of the text are sent as keyboard events in order.

// INTERMEDIATE KEYBOARD PRESSES
//
// You can manually set key press and release events.
// It will take care of setting up the presses and
// sending the command.
// CODE -> Keyboard.press(KEY_A);
// CODE -> Keyboard.release(KEY_A); 

// ADVANCED KEYBOARD PRESSES
//
// There are four modifier keys:
// MODIFIERKEY_CTRL (Ctrl Key)
// MODIFIERKEY_SHIFT (Shift Key)
// MODIFIERKEY_ALT (Alt Key)
// MODIFIERKEY_GUI (Windows (PC) or Clover (Mac))
//
// If you want no modifier keys pressed, use a zero.
// CODE-> Keyboard.set_modifier(0);
//
// To press just one modifier is simple.
// CODE-> Keyboard.set_modifier(MODIFIERKEY_SHIFT);
//
// To press more than one modifier, use the logic OR operator. For example:
// CODE-> Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_ALT);
//
// Six keys are always transmitted by a keyboard, but usually all
// but the first are just 0.
// CODE-> Keyboard.set_key1(KEY_A);
// CODE-> Keyboard.set_key2(KEY_B);
// CODE-> Keyboard.set_key3(KEY_C);
// CODE-> Keyboard.set_key4(KEY_D);
// CODE-> Keyboard.set_key5(KEY_E);
// CODE-> Keyboard.set_key6(KEY_F);
//
// To send your keyboard event:
// CODE-> Keyboard.send_now();
//
// You MUST set_key# and set_modifier to 0 to clear them,
// or they will stay pressed even after Keyboard.send_now();

#include <Bounce.h>

// Setting a debug bool to true means it will print
// useful data to serial to help debug and configure.
const bool kDebugTouchEvents = true;
const bool kDebugTouchVals   = false;
const bool kDebugBtnEvents   = true;

// If true, we are using touch sense pins as intended.
// If false, they will be configured as buttons.
const bool kTouchActive = true;

// Total count of touch sense pins we are managing.
const uint8_t kTouchPinCount = 12;
// All Touch Sense Pins: 0, 1, 15 - 19, 22, 23, (underside pad ->) 25, 32, 33
// The list of Teensy touch sense pin numbers.
const uint8_t kTouchPins[] = { 0, 1, 15, 16, 17, 18, 19, 22, 23, 25, 32, 33 };
// Which touch pins are being used for your controller? Associated with the pins just above.
const bool kTouchPinsActive[] = { false, false, false, false, false, false, false, false, false, false, false, false };
// By default, a button is 'pressed' when a connection is made / it is shorted to ground. You can reverse that behavior for each pin.
const bool kTouchPinsReverse[] = { false, false, false, false, false, false, false, false, false, false, false, false };
// Threshold values relating to each of the touch pins.
const uint16_t kTouchThresholds[] = { 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500 };
// List which keyboard keys are associated with each touch pin.
const uint16_t kTouchKeys[] = { KEY_W, KEY_A, KEY_S, KEY_D, KEY_Z, KEY_X, KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_SPACE, KEY_ENTER };
// List which modifier keys are to be used with the above key.
// Four mod keys available: MODIFIERKEY_CTRL, MODIFIERKEY_SHIFT, MODIFIERKEY_ALT, MODIFIERKEY_GUI
// Use one or more, separating with the logic OR operator. For example: MODIFIER_CTRL | MODIFIER_ALT
const uint16_t kTouchMods[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// How often in millis the debug print should print.
uint16_t kTouchDebugMillis = 500;

// Store the last values read from touch sense pins.
uint16_t _touchLastVal[kTouchPinCount] = {0};
// Store the last calculated state of our virtual touch buttons.
uint8_t _touchLastState[kTouchPinCount] = {0};
// Store the current state of our touch buttons.
uint8_t _touchState[kTouchPinCount] = {0};
// Store time in millis when the pin was last toggled.
uint32_t _touchLastDebounce[kTouchPinCount] = {0};
// Store time in millis for last debug touch print.
uint32_t _touchDebugTime = 0;

// If we don't use touch, we need to store debouncing objects.
Bounce* _touchButtons[kTouchPinCount];


// Total count of pins used for buttons.
const uint8_t kButtonPinCount = 13;
// All Digital Pins (excluding touch pins): 2 - 14, 20, 21, (underside pad ->) 24, 26 - 28, 29 - 31
// The list of digital pins for buttons.
// Pin 6 might need a 1k resistor pullup.
const uint8_t kButtonPins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
// Which button pins are being used for your controller? Associated with the pins just above.
const bool kButtonPinsActive[] = { false, false, false, false, false, false, false, false, false, false, false, false };
// By default, a button is 'pressed' when a connection is made / it is shorted to ground. You can reverse that behavior for each pin.
const bool kButtonPinsReverse[] = { false, false, false, false, false, false, false, false, false, false, false, false, false };
// List which keyboard keys are associated with each digital pin.
const uint16_t kButtonKeys[] = { KEY_W, KEY_A, KEY_S, KEY_D, KEY_Z, KEY_X, KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_SPACE, KEY_ENTER, KEY_ESC };
// List which modifier keys are to be used with the above key.
// Four mod keys available: MODIFIERKEY_CTRL, MODIFIERKEY_SHIFT, MODIFIERKEY_ALT, MODIFIERKEY_GUI
// Use one or more, separating with the logic OR operator. For example: MODIFIER_CTRL | MODIFIER_ALT
const uint16_t kButtonMods[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// Store debouncing objects for buttons.
Bounce* _buttons[kButtonPinCount];


// Total count of pins used for buttons.
const uint8_t kAnalogPinCount = 11;
// The list of Teensy analog pin numbers (that have easy access).
const uint8_t kAnalogPins[] = { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A14 };
// Which pins are being used for your controller? Associated with the pins just above.
const bool kAnalogPinsActive[] = { false, false, false, false, false, false, false, false, false, false, false };
// List which keyboard keys are associated with each digital pin.
const uint16_t kAnalogKeys[] = { KEY_W, KEY_A, KEY_S, KEY_D, KEY_Z, KEY_X, KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_SPACE };
// List which modifier keys are to be used with the above key.
// Four mod keys available: MODIFIERKEY_CTRL, MODIFIERKEY_SHIFT, MODIFIERKEY_ALT, MODIFIERKEY_GUI
// Use one or more, separating with the logic OR operator. For example: MODIFIER_CTRL | MODIFIER_ALT
const uint16_t kAnalogMods[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// Store debouncing objects for buttons.
Bounce* _analogPots[kAnalogPinCount];


// The number of milliseconds to debounce touch sensing.
const uint16_t kTchDebounceMillis = 10;

// The number of milliseconds to debounce buttons presses.
const uint16_t kBtnDebounceMillis = 10;

// The millis to delay after each logic loop.
const uint16_t kLoopDelay = 10;

void setup() {
  Serial.begin(9600);
  
  for (uint8_t i = 0; i < kButtonPinCount; ++i) {
    if (
    pinMode(kButtonPins[i], INPUT_PULLUP);
    _buttons[i] = new Bounce(kButtonPins[i], kBtnDebounceMillis);
  }

  // If you don't want to use touch at all, set them up as buttons.
  if (kTouchActive == false) {
    for (uint8_t i = 0; i < kTouchPinCount; ++i) {
      pinMode(kTouchPins[i], INPUT_PULLUP);
      _touchButtons[i] = new Bounce(kTouchPins[i], kBtnDebounceMillis);
    }
  }

  delay(500);
}

void loop() {
  for (uint8_t i = 0; i < kButtonPinCount; ++i) {
    _buttons[i]->update();

    if (_buttons[i]->fallingEdge()) {
      if (kDebugBtnEvents) {
        Serial.print("Btn Press - Pin: ");
        Serial.print(kButtonPins[i]);
        Serial.print(", Key Val: ");
        Serial.println(kButtonKeys[i]);
      }
      if (kButtonPinsReverse[i]) {
        Keyboard.release(kButtonKeys[i]);
      } else {
        Keyboard.set_modifier(kButtonMods[i]);
        Keyboard.press(kButtonKeys[i]);
        Keyboard.set_modifier(0);
      }
    } else if (_buttons[i]->risingEdge()) {
      if (kDebugBtnEvents) {
        Serial.print("Btn Release - Pin: ");
        Serial.print(kButtonPins[i]);
        Serial.print(", Key Val: ");
        Serial.println(kButtonKeys[i]);
      }
      if (kButtonPinsReverse[i]) {
        Keyboard.set_modifier(kButtonMods[i]);
        Keyboard.press(kButtonKeys[i]);
        Keyboard.set_modifier(0);
      } else {
        Keyboard.release(kButtonKeys[i]);
      }
    }

    /*if ((kRisingEdge && _buttons[i]->risingEdge()) ||
        !kRisingEdge && _buttons[i]->fallingEdge()) {
      
    }*/
  }

  // If you don't want to use touch at all, set them up as buttons.
  if (kTouchActive == false) {
    for (uint8_t i = 0; i < kTouchPinCount; ++i) {
      _touchButtons[i]->update();

      if (_touchButtons[i]->fallingEdge()) {
        if (kDebugBtnEvents) {
          Serial.print("TBtn Press - Pin: ");
          Serial.print(kTouchPins[i]);
          Serial.print(", Key Val: ");
          Serial.println(kTouchKeys[i]);
        }
        if (kTouchPinsReverse[i]) {
          Keyboard.release(kTouchKeys[i]);
        } else {
          Keyboard.set_modifier(kTouchMods[i]);
          Keyboard.press(kTouchKeys[i]);
          Keyboard.set_modifier(0);
        }
      } else if (_touchButtons[i]->risingEdge()) {
        if (kDebugBtnEvents) {
          Serial.print("TBtn Release - Pin: ");
          Serial.print(kTouchPins[i]);
          Serial.print(", Key Val: ");
          Serial.println(kTouchKeys[i]);
        }
        if (kTouchPinsReverse[i]) {
          Keyboard.set_modifier(kTouchMods[i]);
          Keyboard.press(kTouchKeys[i]);
          Keyboard.set_modifier(0);
        } else {
          Keyboard.set_modifier(0);
        }
      }
    }
  } else {
    // Using touch sense pins.
    for (uint8_t i = 0; i < kTouchPinCount; ++i) {
      // Check to see if we are using this touch sense pin.
      // If not, skip it.
      if (!kTouchPinsActive[i]) {
        //continue;
      }
      
      // Get the current analogue value of the touch sense pin.
      uint16_t touchVal = touchRead(kTouchPins[i]);
      
      if (kDebugTouchVals) {
        if ((millis() - _touchDebugTime) > kTouchDebugMillis) {
          _touchDebugTime = millis();
          Serial.print("Touch Value - Pin: ");
          Serial.print(kTouchPins[i]);
          Serial.print(", Read Val: ");
          Serial.println(touchVal);
        }
      }
      
      // We are treating it like a button, default state to not pressed / active.
      uint8_t touchState = 0;

      // If the current value equals or exceeds the threshold, it is pressed / active.
      if (touchVal >= kTouchThresholds[i]) {
        touchState = 1;
      }

      // If the state changes, we need to reset our debounce timestamp.
      if (touchState != _touchLastState[i]) {
        _touchLastDebounce[i] = millis();
      }

      // If the time since the last state change is greater than
      // the debounce delay value we have set, we have a valid state change.
      if ((millis() - _touchLastDebounce[i]) > kTchDebounceMillis) {
        if (touchState != _touchState[i]) {
          _touchState[i] = touchState;

          if (_touchState[i]) {
            if (kDebugTouchEvents) {
              Serial.print("Touch Press - Pin: ");
              Serial.print(kTouchPins[i]);
              Serial.print(", Key Val: ");
              Serial.println(kTouchKeys[i]);
            }
            Keyboard.set_modifier(kTouchMods[i]);
            Keyboard.press(kTouchKeys[i]);
            Keyboard.set_modifier(0);
          } else {
            if (kDebugTouchEvents) {
              Serial.print("Touch Release - Pin: ");
              Serial.print(kTouchPins[i]);
              Serial.print(", Key Val: ");
              Serial.println(kTouchKeys[i]);
            }
            Keyboard.release(kTouchKeys[i]);
          }
        }
      }
      
      _touchLastVal[i] = touchVal;
      _touchLastState[i] = touchState;
    }
  }

  delay(kLoopDelay);
}
