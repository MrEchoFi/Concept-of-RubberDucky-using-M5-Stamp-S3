
#include <Keyboard.h>  // Requires native USB HID support

// ----- Customize Your Command Script Here -----
const char* commandScript[] = {
  "echo Troubleshooting initiated...",
  "ipconfig /release",
  "ipconfig /renew",
  "echo Please wait...",
  "timeout /t 5",
  "exit"
};
const int numCommands = sizeof(commandScript) / sizeof(commandScript[0]);

// Keystroke delay (in milliseconds)
const int keystrokeDelay = 50;

// Send text character by character
void sendString(const char* text) {
  for (int i = 0; text[i] != '\0'; i++) {
    Keyboard.write(text[i]);
    delay(keystrokeDelay);
  }
}

void setup() {
  Keyboard.begin();
  
  // Give the host time to recognize the USB device.
  delay(2000);

  // ----- Opening the Command Terminal (Windows Example) -----
  // Press Windows + R to open the Run dialog.
  Keyboard.press(KEY_LEFT_GUI);
  delay(100);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();
  delay(500);

  // Type "cmd" to open the Command Prompt.
  sendString("cmd");
  delay(100);
  Keyboard.write(KEY_RETURN);
  delay(1000);

  // ----- Inject the Command Script -----
  for (int i = 0; i < numCommands; i++) {
    sendString(commandScript[i]);
    Keyboard.write(KEY_RETURN);
    delay(500);
  }

  // Finish the session.
  delay(1000);
  Keyboard.end();
}

void loop() {
  // Script injected once; nothing to do in loop.
}
