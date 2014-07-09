#include <Adafruit_NeoPixel.h>
#include <Process.h>

#define LED_COUNT 50
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

	_server.begin("/usr/bin/rgam/pngled-server.py");
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
			_pixels.setPixelColor(row, _pixels.Color(red, green, blue));
		}
		_pixels.show();
	}
}
