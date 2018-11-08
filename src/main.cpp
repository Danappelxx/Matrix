#include "application.h"
#include "color.h"
#include "matrix.h"
#include "neopixel.h"
#include "snake.h"
#include <vector>
#include "WebSocketsServer.h"

#define PIXEL_PIN D0
#define PIXEL_COUNT 420 // 14x30 (14 tall, 30 wide)
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
Matrix* matrix = new Matrix(14, 30);
Snake* snake = new Snake(false, 14, 30);
WebSocketsServer webSocket = WebSocketsServer(80);

void onEvent(uint8_t id, WStype_t type, uint8_t* payload, size_t length) {
    switch(type) {
        case WStype_CONNECTED:
            Serial.printlnf("[%u] Connected, url: %s", id, payload);
            break;
        case WStype_TEXT:
            Serial.printlnf("[%u] Got text: [%s]", id, payload);
            {
                String text = String((char *)payload);

                if (text.equals("UP") || text.equalsIgnoreCase("W")) {
                    snake->setDirection(UP);
                } else if (text.equals("DOWN") || text.equalsIgnoreCase("S")) {
                    snake->setDirection(DOWN);
                } else if (text.equals("LEFT") || text.equalsIgnoreCase("A")) {
                    snake->setDirection(LEFT);
                } else if (text.equals("RIGHT") || text.equalsIgnoreCase("D")) {
                    snake->setDirection(RIGHT);
                }
            }

            break;
        case WStype_DISCONNECTED:
            Serial.printlnf("[%u] Disconnected.", id);
            break;
        case WStype_ERROR:
        case WStype_FRAGMENT_TEXT_START:
        case WStype_FRAGMENT_BIN_START:
        case WStype_FRAGMENT:
        case WStype_FRAGMENT_FIN:
            break;
    }
}

void setup() {
    Serial.begin(9600);

    webSocket.begin();
    webSocket.onEvent(onEvent);

    strip.begin();
    strip.setBrightness(100);
    strip.show();
}

uint32_t hex(Color color) {
    return strip.Color(color.red, color.green, color.blue);
}

void draw(const std::vector<Color>& pixels) {
    for (auto i = 0; i < pixels.size(); i++) {
        strip.setPixelColor(i, hex(pixels[i]));
    }
    strip.show();
}

void loop() {
    webSocket.loop();

    snake->step();
    snake->draw(matrix);
    draw(matrix->getStrip());

    delay(max(10, 50 - 5 * snake->getLength()));
}
