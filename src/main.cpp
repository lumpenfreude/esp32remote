#import <Arduino.h>
#import "Adafruit_keypad.h"
#define IR_SEND_PIN 0
#define IR_FEEDBACK_LED_PIN 2
#define IR_INPUT_PIN 23
#define EXCLUDE_UNIVERSAL_PROTOCOLS
#define EXCLUDE_EXOTIC_PROTOCOLS
#import <IRremote.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3c
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
      {'0', '1', '2'},
      {'4', '5', '6'},
      {'7', '8', '9'},
      {'a', 'b', 'c'}
};
byte rowPins[ROWS] = {17, 16, 32, 2};
byte colPins[COLS] = {25, 23, 5};
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

static const unsigned char PROGMEM logo_bmp[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00,
   0x00, 0x04, 0x03, 0x00, 0x00, 0x02, 0x06, 0x00, 0x00, 0x01, 0x08, 0x00,
   0x00, 0x01, 0x08, 0x00, 0x00, 0xc3, 0x0b, 0x00, 0xc0, 0x65, 0x0c, 0x00,
   0xc0, 0x6d, 0x0c, 0x00, 0x00, 0xc7, 0x0b, 0x00, 0x00, 0x0d, 0x08, 0x00,
   0x00, 0x01, 0x08, 0x00, 0x00, 0x5f, 0x08, 0x30, 0x00, 0x01, 0x08, 0x28,
   0x00, 0xc1, 0x7b, 0x24, 0x00, 0x41, 0x7a, 0x24, 0x00, 0x41, 0x8b, 0x13,
   0x00, 0x41, 0xe3, 0x18, 0x00, 0x21, 0x04, 0x13, 0x00, 0x62, 0x07, 0x0c,
   0x00, 0xc2, 0x03, 0x06, 0x00, 0x04, 0x00, 0x06, 0x00, 0x04, 0x00, 0x03,
   0x00, 0xf8, 0xe3, 0x00, 0x00, 0x28, 0x14, 0x00, 0x00, 0x28, 0x14, 0x00,
   0x00, 0x28, 0x14, 0x00, 0x00, 0x2c, 0x16, 0x00, 0x00, 0x22, 0x11, 0x00,
   0x00, 0x1c, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00 };

void setup() {
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        for(;;); // Don't proceed, loop forever          
    }
    IrSender.begin();
    display.display();
    testdrawbitmap();   
}

void testdrawbitmap(void) {
    display.clearDisplay();
    display.drawBitmap(
        (display.width()  - LOGO_WIDTH ) / 2,
        (display.height() - LOGO_HEIGHT) / 2,
        logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1
        );
    display.display();
    delay(1000);
}

void loop() {
customKeypad.tick();
while (customKeypad.available()) {
	keypadEvent e = customKeypad.read();
	if (e.bit.EVENT == KEY_JUST_PRESSED) {
		if ((char)e.bit.KEY == '0') 
		IrSender.sendSony(0x490, 12); // volume up
		delay(50);
		}
		else if ((char)e.bit.KEY == '1') {
		IrSender.sendSony(0xA50, 12); // source 
		delay(50);
		}
		else if ((char)e.bit.KEY == '2') {
		IrSender.sendSony(0xA90, 12); // power
		delay(50);
		}
		else if ((char)e.bit.KEY == '3') {
		IrSender.sendSony(0xA90, 12); // volume down
		delay(50);
		}
		else if ((char)e.bit.KEY == '4') {
		IrSender.sendSony(0xA50, 12); // up
		delay(50);
		}
		else if ((char)e.bit.KEY == '5') {
		IrSender.sendSony(0x070, 15); // menu
		delay(50);
		}
		else if ((char)e.bit.KEY == '6') {
		IrSender.sendSony(0x2D0, 12); // left 
		delay(50);
		}
		else if ((char)e.bit.KEY == '7') {
		IRSender.sendSony(0xA07, 12); // enter
		delay(50);
		}
		else if ((char)e.bit.KEY == '8') {
		IRSender.sendSony(0xCD0, 12); // right
		delay(50);
		}
		else if ((char)e.bit.KEY == '9') {
		display.clearDisplay(); // disappear dickbutt
		delay(50);
		}
		else if ((char)e.bit.KEY == 'a') {
		IRSender.sendSony(0xAF0, 12); //down
		delay(50);
		}
		else if ((char)e.bit.KEY == 'b') {
		testdrawbitmap(); //reappear dickbutt
		delay(50);
		}
	}
}
