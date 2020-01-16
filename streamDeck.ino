#include <Keyboard.h>

int keypadPins[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
int keypadStatus;  // Used to monitor which buttons are pressed.
int timeout;  // timeout variable used in loop

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  for (int i=0; i<9; i++)
  {
    pinMode(keypadPins[i], INPUT);  // Set all keypad pins as inputs
    digitalWrite(keypadPins[i], HIGH);  // pull all keypad pins high
  }
  Keyboard.begin();
}

void loop()
{
  keypadStatus = getKeypadStatus();  // read which buttons are pressed
  if (keypadStatus != 0)  // If a button is pressed go into here
  {
    sendKeyPress(keypadStatus);  // send the button over USB
    timeout = 500;  // top of the repeat delay
    while ((getKeypadStatus() == keypadStatus) && (--timeout))  // Decrement timeout and check if key is being held down
      delay(1);
    while (getKeypadStatus() == keypadStatus)  // while the same button is held down
    {
      sendKeyPress(keypadStatus);  // continue to send the button over USB
      digitalWrite(LED_BUILTIN, HIGH);
      delay(50);  // 50ms repeat rate
    }
    digitalWrite(LED_BUILTIN, LOW);
  }
}

/* sendKeyPress(int key): This function sends a single key over USB
   It requires an int, of which the 12 LSbs are used. Each bit in
   key represents a single button on the keypad.
   This function will only send a key press if a single button
   is being pressed */
void sendKeyPress(int key)
{
  switch(key)
  {
    case 2:  // 0x001
      Keyboard.write('1');  // Sends a keyboard '1'
      break;
    case 3:  // 0x002
      Keyboard.write('2');
      break;
    case 4:  // 0x004
      Keyboard.write('3');
      break;
    case 5:  // 0x008
      Keyboard.write('4');
      break;
    case 6:  // 0x010
      Keyboard.write('5');
      break;
    case 7:  // 0x020
      Keyboard.write('6');
      break;
    case 8:  // 0x040
      Keyboard.write('7');
      break;
    case 9:  // 0x080
      Keyboard.write('8');
      break;
    case 10:  // 0x100
      Keyboard.write('9');
      break;
  }
}

/* getKeypadStatus(): This function returns an int that represents
the status of the 12-button keypad. Only the 12 LSb's of the return
value hold any significange. Each bit represents the status of a single
key on the button pad. '1' is bit 0, '2' is bit 1, '3' is bit 2, ..., 
'#' is bit 11.

This function doesn't work for multitouch.
*/
int getKeypadStatus()
{

  for (int i=0; i<9; i++)
  {
    if (digitalRead(keypadPins[i]) == LOW) {
      return keypadPins[i];
    }
  }
  
  return 0;
}
