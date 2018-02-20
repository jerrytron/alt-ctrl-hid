// See this link for a comprehensive guide:
// https://www.pjrc.com/teensy/td_keyboard.html
// Scroll down to All Keys Codes

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

#include <Bounce2.h>
#include "BPLib.h"

// Setting a debug bool to true means it will print
// useful data to serial to help debug and configure.
const bool kDebugTouchEvents  = true; // Prints touch sense down and release events.
const bool kDebugTouchVals    = false; // Prints all touch pin values at an interval.
// FYI: To use kDebugTouchValPlot, kDebugTouchVals must be true, kDebugTouchEvents & kDebugBtnEvents must be false.
const bool kDebugTouchValPlot = false; // Instead of text, prints values for graph plotting.
const bool kDebugBtnEvents    = true; // Prints button down and release events.

// If true, we are using touch sense pins as intended.
// If false, they will be configured as buttons.
const bool kTouchActive = true;

//vvvvvvvvvvvvv TEENSY 3.1/3.2 ONLY - TOUCH SENSING vvvvvvvvvvvvv//
#if defined(__MK20DX256__) // Using Teensy 3.1/3.2
// Total count of touch sense pins we are managing.
const uint8_t kTouchPinCount = 9;
// All Touch Sense Pins: 0, 1, 15 - 19, 22, 23, (not using underside pad ->) 25, 32, 33
// The list of Teensy touch sense pin numbers.
const uint8_t kTouchPins[] = { 0, 1, 15, 16, 17, 18, 19, 22, 23 };
// Which touch pins are being used for your controller? Associated with the pins just above.
const bool kTouchPinsActive[] = { false, false, false, false, false, false, false, false, false };
// By default, a button is 'pressed' when a connection is made / it is shorted to ground. You can reverse that behavior for each pin.
const bool kTouchPinsReverse[] = { false, false, false, false, false, false, false, false, false };
// Threshold values relating to each of the touch pins.
const uint16_t kTouchThresholds[] = { 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500 };
// List which keyboard keys are associated with each touch pin.
const uint16_t kTouchKeys[] = { BP_KEY_W, BP_KEY_A, BP_KEY_S, BP_KEY_D, BP_KEY_UP, BP_KEY_LEFT, BP_KEY_DOWN, BP_KEY_RIGHT, BP_KEY_SPACE };
// List which modifier keys are to be used with the above key.
// Four mod keys available: MODIFIERKEY_CTRL, MODIFIERKEY_SHIFT, MODIFIERKEY_ALT, MODIFIERKEY_GUI
// Use one or more, separating with the logic OR operator. For example: MODIFIERKEY_CTRL | MODIFIERKEY_ALT
const uint16_t kTouchMods[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//^^^^^^^^^^^^^ TEENSY 3.1/3.2 ONLY - TOUCH SENSING ^^^^^^^^^^^^^//

//vvvvvvvvvvvvv TEENSY LC ONLY - TOUCH SENSING vvvvvvvvvvvvv//
#elif defined(__MKL26Z64__) // Using Teensy LC
// Total count of touch sense pins we are managing.
const uint8_t kTouchPinCount = 11;
// All Touch Sense Pins: 0, 1, 3, 4, 15 - 19, 22, 23
// The list of Teensy touch sense pin numbers.
const uint8_t kTouchPins[] = { 0, 1, 3, 4, 15, 16, 17, 18, 19, 22, 23 };
// Which touch pins are being used for your controller? Associated with the pins just above.z
const bool kTouchPinsActive[] = { false, false, false, false, false, false, false, false, false, false, false };
// By default, a button is 'pressed' when a connection is made / it is shorted to ground. You can reverse that behavior for each pin.
const bool kTouchPinsReverse[] = { false, false, false, false, false, false, false, false, false, false, false };
// Threshold values relating to each of the touch pins.
const uint16_t kTouchThresholds[] = { 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500 };
// List which keyboard keys are associated with each touch pin.
const uint16_t kTouchKeys[] = { BP_KEY_W, BP_KEY_A, BP_KEY_S, BP_KEY_D, BP_KEY_Z, BP_KEY_X, BP_KEY_UP, BP_KEY_LEFT, BP_KEY_DOWN, BP_KEY_RIGHT, BP_KEY_SPACE };
// List which modifier keys are to be used with the above key.
// Four mod keys available: MODIFIERKEY_CTRL, MODIFIERKEY_SHIFT, MODIFIERKEY_ALT, MODIFIERKEY_GUI
// Use one or more, separating with the logic OR operator. For example: MODIFIERKEY_CTRL | MODIFIERKEY_ALT
const uint16_t kTouchMods[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
#endif
//^^^^^^^^^^^^^ TEENSY LC ONLY - TOUCH SENSING ^^^^^^^^^^^^^//

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
// Store the total number of active touch pins.
uint8_t _activeTouchPins = 0;

//vvvvvvvvvvvvv TEENSY 3.1/3.2 ONLY - BUTTONS vvvvvvvvvvvvv//
#if defined(__MK20DX256__) // Using Teensy 3.1/3.2
// Total count of pins used for buttons.
const uint8_t kButtonPinCount = 15;
// All Digital Pins (excluding touch pins): 2 - 14, 20, 21, (not using underside pad ->) 24, 26 - 28, 29 - 31
// The list of digital pins for buttons.
// Pin 6 might need a 1k resistor pullup.
const uint8_t kButtonPins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 20, 21 };
// By default, a button is 'pressed' when a connection is made / it is shorted to ground. You can reverse that behavior for each pin.
const bool kButtonPinsReverse[] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
// List which keyboard keys are associated with each digital pin.
const uint16_t kButtonKeys[] = { BP_KEY_W, BP_KEY_A, BP_KEY_S, BP_KEY_D, BP_KEY_Z, BP_KEY_X, BP_KEY_UP, BP_KEY_LEFT, BP_KEY_DOWN, BP_KEY_RIGHT, BP_KEY_SPACE, BP_KEY_ENTER, BP_KEY_ESC, BP_KEYPAD_0, BP_KEYPAD_1 };
// List which modifier keys are to be used with the above key.
// Four mod keys available: MODIFIERKEY_CTRL, MODIFIERKEY_SHIFT, MODIFIERKEY_ALT, MODIFIERKEY_GUI
// Use one or more, separating with the logic OR operator. For example: MODIFIER_CTRL | MODIFIER_ALT
const uint16_t kButtonMods[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//^^^^^^^^^^^^^ TEENSY 3.1/3.2 ONLY - BUTTONS ^^^^^^^^^^^^^//

//vvvvvvvvvvvvv TEENSY LC ONLY - BUTTONS vvvvvvvvvvvvv//
#elif defined(__MKL26Z64__) // Using Teensy LC
// Total count of pins used for buttons.
const uint8_t kButtonPinCount = 13;
// All Digital Pins (excluding touch pins): 2, 5 - 14, 20, 21
// The list of digital pins for buttons.
const uint8_t kButtonPins[] = { 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 20, 21 };
// By default, a button is 'pressed' when a connection is made / it is shorted to ground. You can reverse that behavior for each pin.
const bool kButtonPinsReverse[] = { false, false, false, false, false, false, false, false, false, false, false, false, false };
// List which keyboard keys are associated with each digital pin.
const uint16_t kButtonKeys[] = { BP_KEY_W, BP_KEY_A, BP_KEY_S, BP_KEY_D, BP_KEY_Z, BP_KEY_X, BP_KEY_UP, BP_KEY_LEFT, BP_KEY_DOWN, BP_KEY_RIGHT, BP_KEY_SPACE, BP_KEY_ENTER, BP_KEY_ESC };
// List which modifier keys are to be used with the above key.
// Four mod keys available: MODIFIERKEY_CTRL, MODIFIERKEY_SHIFT, MODIFIERKEY_ALT, MODIFIERKEY_GUI
// Use one or more, separating with the logic OR operator. For example: MODIFIER_CTRL | MODIFIER_ALT
const uint16_t kButtonMods[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
#endif
//^^^^^^^^^^^^^ TEENSY LC ONLY - BUTTONS ^^^^^^^^^^^^^//

// Store debouncing objects for buttons.
Bounce* _buttons[kButtonPinCount];

// The number of milliseconds to debounce touch sensing.
const uint16_t kTchDebounceMillis = 10;

// The number of milliseconds to debounce buttons presses.
const uint16_t kBtnDebounceMillis = 10;

// The millis to delay after each logic loop.
const uint16_t kLoopDelay = 0;

BPLib _btMod;

void setup() {
  Serial1.begin(115200);
  
  for (uint8_t i = 0; i < kButtonPinCount; ++i) {
    _buttons[i] = new Bounce();
    _buttons[i].attach(kButtonPins[i], INPUT_PULLUP);
    _buttons[i].interval(kBtnDebounceMillis);
  }

  // If you don't want to use touch at all, set them up as buttons.
  if (kTouchActive == false) {
    for (uint8_t i = 0; i < kTouchPinCount; ++i) {
      _touchButtons[i] = new Bounce();
      _touchButtons[i].attach(kTouchPins[i], INPUT_PULLUP);
      _touchButtons[i].interval(kBtnDebounceMillis);
    }
  } else {
    // Count how many touch pins are active (set true).
    for (uint8_t i = 0; i < kTouchPinCount; ++i) {
      if (kTouchPinsActive[i]) {
        _activeTouchPins++;
      }
    }
  }

  delay(500);
}

void loop() {
  for (uint8_t i = 0; i < kButtonPinCount; ++i) {
    _buttons[i]->update();

    // Determine which event occurred for debugging.
    bool pressed = false;
    bool released = false;

    if (_buttons[i]->fell()) {
      if (kButtonPinsReverse[i]) {
        //Keyboard.release(kButtonKeys[i]);
        _btMod.keyboardRelease(kButtonKeys[i]);
        released = true;
      } else {
        /*Keyboard.set_modifier(kButtonMods[i]);
        Keyboard.press(kButtonKeys[i]);
        Keyboard.set_modifier(0);*/
        _btMod.keyboardPress(kButtonKeys[i], kButtonMods[i]);
        pressed = true;
      }
    } else if (_buttons[i]->rose()) {
      if (kButtonPinsReverse[i]) {
        /*Keyboard.set_modifier(kButtonMods[i]);
        Keyboard.press(kButtonKeys[i]);
        Keyboard.set_modifier(0);*/
        _btMod.keyboardPress(kButtonKeys[i], kButtonMods[i]);
        pressed = true;
      } else {
        //Keyboard.release(kButtonKeys[i]);
        _btMod.keyboardRelease(kButtonKeys[i]);
        released = true;
      }
    }
    if (kDebugBtnEvents && pressed) {
      Serial.print("Btn Press - Pin: ");
      Serial.print(kButtonPins[i]);
      Serial.print(", Key Code: ");
      Serial.println(kButtonKeys[i]);
    } else if (kDebugBtnEvents && released) {
      Serial.print("Btn Release - Pin: ");
      Serial.print(kButtonPins[i]);
      Serial.print(", Key Code: ");
      Serial.println(kButtonKeys[i]);
    }
  }

  // If you don't want to use touch at all, set them up as buttons.
  if (kTouchActive == false) {
    for (uint8_t i = 0; i < kTouchPinCount; ++i) {
      _touchButtons[i]->update();

      // Determine which event occurred for debugging.
      bool pressed = false;
      bool released = false;

      if (_touchButtons[i]->fell()) {
        if (kTouchPinsReverse[i]) {
          //Keyboard.release(kTouchKeys[i]);
          _btMod.keyboardRelease(kTouchKeys[i]);
          released = true;
        } else {
          /*Keyboard.set_modifier(kTouchMods[i]);
          Keyboard.press(kTouchKeys[i]);
          Keyboard.set_modifier(0);*/
          _btMod.keyboardPress(kTouchKeys[i], kTouchMods[i]);
          pressed = true;
        }
      } else if (_touchButtons[i]->rose()) {
        if (kTouchPinsReverse[i]) {
         /* Keyboard.set_modifier(kTouchMods[i]);
          Keyboard.press(kTouchKeys[i]);
          Keyboard.set_modifier(0);*/
          _btMod.keyboardPress(kTouchKeys[i], kTouchMods[i]);
          pressed = true;
        } else {
          //Keyboard.release(kTouchKeys[i]);
          _btMod.keyboardRelease(kTouchKeys[i]);
          released = true;
        }
      }
      if (kDebugBtnEvents && pressed) {
        Serial.print("TBtn Press - Pin: ");
        Serial.print(kTouchPins[i]);
        Serial.print(", Key Code: ");
        Serial.println(kTouchKeys[i]);
      } else if (kDebugBtnEvents && released) {
        Serial.print("TBtn Release - Pin: ");
        Serial.print(kTouchPins[i]);
        Serial.print(", Key Code: ");
        Serial.println(kTouchKeys[i]);
      }
    }
  } else {
    // Store if the interval passed for outputting values.
    bool debugOutput = false;
    // Check if the frequency time has passed.
    if ((millis() - _touchDebugTime) > kTouchDebugMillis) {
      debugOutput = true;
      _touchDebugTime = millis();
    }
    
    // Track the active pin index so we know if we are at the end of the loop.
    uint8_t activePinIndex = 0;

    // Using touch sense pins.
    for (uint8_t i = 0; i < kTouchPinCount; i++) {
      // Check to see if we are using this touch sense pin.
      // If not, skip it.
      if (!kTouchPinsActive[i]) {
        continue;
      }
      
      // Get the current analogue value of the touch sense pin.
      uint16_t touchVal = touchRead(kTouchPins[i]);

      // For printing debug text or values continuously.
      if (kDebugTouchVals) {
        if (debugOutput) {
          activePinIndex++;
          if (kDebugTouchValPlot) {
            Serial.print("index: ");
            Serial.print(i);
            if (activePinIndex >= _activeTouchPins) {
              Serial.println(touchVal);
            } else {
              Serial.print(touchVal);
              Serial.print("\t");
            }
          } else {
            Serial.print("Touch Value - Pin: ");
            Serial.print(kTouchPins[i]);
            Serial.print(", Read Val: ");
            Serial.println(touchVal);
          }
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

      // Determine which event occurred for debugging.
      bool pressed = false;
      bool released = false;

      // If the time since the last state change is greater than
      // the debounce delay value we have set, we have a valid state change.
      if ((millis() - _touchLastDebounce[i]) > kTchDebounceMillis) {
        if (touchState != _touchState[i]) {
          _touchState[i] = touchState;

          if (_touchState[i]) {
            if (kTouchPinsReverse[i]) {
              //Keyboard.release(kTouchKeys[i]);
              _btMod.keyboardRelease(kTouchKeys[i]);
              released = true;
            } else {
              /*Keyboard.set_modifier(kTouchMods[i]);
              Keyboard.press(kTouchKeys[i]);
              Keyboard.set_modifier(0);*/
              _btMod.keyboardPress(kTouchKeys[i], kTouchMods[i]);
              pressed = true;
            }
          } else {
            if (kTouchPinsReverse[i]) {
              /*Keyboard.set_modifier(kTouchMods[i]);
              Keyboard.press(kTouchKeys[i]);
              Keyboard.set_modifier(0);*/
              _btMod.keyboardPress(kTouchKeys[i], kTouchMods[i]);
              pressed = true;
            } else {
              //Keyboard.release(kTouchKeys[i]);
              _btMod.keyboardRelease(kTouchKeys[i]);
              released = true;
            }
          }
        }
      }

      if (kDebugTouchEvents && pressed) {
        Serial.print("Touch Press - Pin: ");
        Serial.print(kTouchPins[i]);
        Serial.print(", Read Val: ");
        Serial.print(touchVal);
        Serial.print(", Key Code: ");
        Serial.println(kTouchKeys[i]);
      } else if (kDebugTouchEvents && released) {
        Serial.print("Touch Release - Pin: ");
        Serial.print(kTouchPins[i]);
        Serial.print(", Read Val: ");
        Serial.print(touchVal);
        Serial.print(", Key Code: ");
        Serial.println(kTouchKeys[i]);
      }
      
      _touchLastVal[i] = touchVal;
      _touchLastState[i] = touchState;
    }
  }

  delay(kLoopDelay);
}
