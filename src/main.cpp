#include "application.h"
#include "color.h"
#include "matrix.h"
#include "neopixel.h"
#include "snake.h"
#include <vector>

#define PIXEL_PIN D0
#define PIXEL_COUNT 420 // 14x30 (14 tall, 30 wide)
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
Matrix* matrix = new Matrix(14, 30);
Snake* snake = new Snake(14, 30);

void setup() {
    strip.begin();
    strip.setBrightness(100);
    strip.show();

    for (int i = 0; i < 14; i++)
        matrix->set(Point { i, i }, Color { 255, 255, 255 });

    for (int i = 0; i < 14; i++)
        matrix->set(Point { 27 - i, i }, Color { 255, 255, 255 });

    for (int i = 0; i < 27; i++)
        matrix->set(Point { i, 0 }, Color { 255, 255, 255 });
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
    snake->step();
    snake->draw(matrix);
    draw(matrix->getStrip());
    delay(max(10, 50 - 5 * snake->getLength()));
}
