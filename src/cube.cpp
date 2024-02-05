#include "cube.h"

typedef void (Cube::*ModePtr)(int); 
#define DATA_PIN 3

ModePtr modes[] = { 
  &Cube::randomColors,
  &Cube::colorStrips, 
  &Cube::allColors, 
  &Cube::starry, 
  &Cube::colorPlanes, 
  &Cube::expandingSquaresInward, 
  &Cube::expandingSquaresOutward,
};

Cube::Cube(int width, int depth, int height) {
  this->width = width;
  this->depth = depth;
  this->height = height;
  pixelCount = width * depth * height;
  pixelsPerPlane = width * depth;
  leds = new RGBPIXEL[pixelCount];
#ifdef NEO_FASTLED
  strip = new FastLEDReference(FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, pixelCount));
#else
  strip = new NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod>(pixelCount);
#endif
}

Cube::~Cube() {
  if (leds!=NULL) {
    STRIP->clearLedData();
    delete[] leds;
    leds = NULL;
  }
}

void Cube::set_pixel_color(int i, RGBPIXEL pixel) {
#ifdef NEO_FASTLED
  leds[i] = pixel;
#else
  strip->SetPixelColor(i, pixel);
#endif
}

void Cube::setup() {
  if (strip!=NULL) {
    for (int led = 0; led <pixelCount;led++) {
      leds[led] = RGBPIXEL::Black;
    }
    show();
  }

}

void Cube::loop(int loopNumber) {
  if (strip==NULL) {
    return;
  }

  int modeCount = sizeof(modes) / sizeof(ModePtr);

  int iMode = (loopNumber / 40) % modeCount;
  ModePtr mode = modes[iMode];
  (this->*mode)(loopNumber);
  show();
}

void Cube::show() {
  STRIP->showLeds();
}

#define SHIFT 5

void Cube::randomColors(int loopNumber) {
  for (int i=0; i<pixelCount;i++) {
    set_pixel_color(i, RGBPIXEL(random(256),random(256),random(256)));
  }
}

void Cube::colorStrips(int loopNumber) {
  for (int i=0; i<pixelCount;i++) {
    set_pixel_color(i, colors[(i%width+loopNumber)%numColors]);
  }
}

void Cube::colorPlanes(int loopNumber) {
  for (int i=0; i<pixelCount;i++) {
    set_pixel_color(i, colors[((i/25)+loopNumber/3)%numColors]);
  }
}

void Cube::allColors(int loopNumber) {
  for (int i=0; i<pixelCount;i++) {
    int n = (i+loopNumber) % pixelCount;
    int plane = n / pixelsPerPlane;
    int rank = n % pixelsPerPlane;

    float sat = 0.5 + 0.5 * ((float) plane / height);
    float hue = ((float) rank) / pixelsPerPlane;
    HUEPIXEL hsl(hue, sat, 0.25);
    set_pixel_color(i, hsl);
  }
}

void Cube::expandingSquares(int loopNumber, int dir) {
  int n = loopNumber / 1;
  for (int i=0; i<pixelCount;i++) {
    RGBPIXEL col1 = colors[n % numColors];
    RGBPIXEL col2 = colors[(n+1*dir) % numColors];
    RGBPIXEL col3 = colors[(n+2*dir) % numColors];

    RGBPIXEL color;
    int col = i % 5;
    int line = (i / 5) % 5;
    if (col==2 && line==2) {
      color = col1;
    }
    else if (col>0 && col<4 && line>0 && line<4) {
      color = col2;
    }
    else {
      color = col3;
    }
    set_pixel_color(i, color);

  }
}

void Cube::expandingSquaresInward(int loopNumber) {
  expandingSquares(loopNumber, 1);
}

void Cube::expandingSquaresOutward(int loopNumber) {
  expandingSquares(loopNumber, -1);
}

void Cube::starry(int loopNumber) {
  for (int i=0; i<pixelCount;i++) {
    RGBPIXEL color = black;
    if (random(256) > 200) {
      color = RGBPIXEL(random(256),random(256),random(256));
    }
    set_pixel_color(i, color);
  }
}

