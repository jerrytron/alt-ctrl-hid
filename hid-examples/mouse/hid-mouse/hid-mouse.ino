/* PJRC Documention for mouse HID: https://www.pjrc.com/teensy/td_mouse.html */

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

#include <Bounce.h>

Bounce button4 = Bounce(4, 10);
Bounce button5 = Bounce(5, 10);

void setup() {
  Mouse.screenSize(1920, 1080);  // configure screen size
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
}

void loop() {
  button4.update();
  button5.update();
  if (button4.fallingEdge()) {
    Mouse.moveTo(25, 100);       // point to pixel at 25, 100
  }
  if (button5.fallingEdge()) {
    Mouse.moveTo(1580, 14);      // point to pixel at 1580, 14
  }
}
