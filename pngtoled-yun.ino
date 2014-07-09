#include <Adafruit_NeoPixel.h>
#include <Process.h>

#define LED_COUNT 50 // should equal RGAM_DATA_ROWS
#define LED_DATA_PIN 3
#define LED_DEFAULT_BRIGHTNESS 10

const char go = 0xf005ba11;
const char command = 0x00;

Adafruit_NeoPixel _pixels = Adafruit_NeoPixel(LED_COUNT, LED_DATA_PIN, NEO_GRB + NEO_KHZ800);
Process _server;

void setup() {
  Serial.begin(9600);
  
  _pixels.begin();
  _pixels.setBrightness(LED_DEFAULT_BRIGHTNESS);

  Bridge.begin();

	_server.begin("/usr/bin/rgam/pngtoled-server.py");
	_server.runAsynchronously();
}

void loop() {
	if (!_server.running()) {
		setup();
	}

	while(_server.available() < 3);
	
	uint8_t c = _server.read();
	if (c != go) continue;
	
	c = _server.read();
	if (c == command) {
		uint8_t rowCount = (uint8_t)_server.read();

		uint8_t r, g, b;
		for (uint8_t i = 0; i < rowCount; i++) {
			if (i >= LED_COUNT) break;
			
			while (_server.available() < 3);
			
			red = _server.read();
			green = _server.read();
			blue = _server.read();
			uint32_t color = _pixels.Color(red, green, blue);
			_pixels.setPixelColor(row, color);
		}
		_pixels.show();
	}
	  // 
	  // 	
	  // Serial.print("frm "); Serial.println(_frame);
	  // 
	  // for (int32_t row = 0; row < RGAM_DATA_ROWS; row++) {
	  //   if (row >= LED_COUNT) break;
	  // 
	  // 		// We are counting LEDs "bottom up" starting from the bottom of the strip, 
	  // 		// while the  animation is listing pixels "top down" starting from the
	  // 		// top of the image. So reverse here.
	  // 		uint32_t rowReversed = LED_COUNT - 1 - row;
	  // 
	  //   const byte *pixel = data[_frame][rowReversed];
	  // 
	  //   uint16_t red   = (int) pgm_read_byte(pixel);
	  //   uint16_t green = (int) pgm_read_byte(&(pixel[1]));
	  //   uint16_t blue  = (int) pgm_read_byte(&(pixel[2]));
	  //   
	  //   uint32_t color = _pixels.Color(red, green, blue);
	  // 
	  //   _pixels.setPixelColor(row, color);
	  // }
	  // _pixels.show();
	  // 
	  // if (++_frame == RGAM_DATA_COLUMNS) _frame = 0;
	  // 
	  // delay(DELAY);
	  // Serial.println();
}
