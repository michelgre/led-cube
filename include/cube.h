#pragma once

#ifdef NEO_FASTLED
#include <FastLED.h>
#else
#include <NeoPixelBus.h>
#endif


#ifdef NEO_FASTLED
#define RGBPIXEL CRGB
#define HUEPIXEL CHSV
#define STRIP (*strip)
#else
#define RGBPIXEL RgbColor
#define HUEPIXEL HueColor
#define STRIP strip
#endif

// ========================
// FIXME
#define cs 128
static RGBPIXEL  black(0,0,0);
static RGBPIXEL  colors[] = { 
  RGBPIXEL (cs,  0,  0), 
  RGBPIXEL (cs, cs,  0),
  RGBPIXEL ( 0, cs,  0), 
  RGBPIXEL ( 0, cs, cs), 
  RGBPIXEL ( 0,  0, cs), 
  RGBPIXEL (cs,  0, cs),
};
static int numColors = sizeof(colors) / sizeof(RGBPIXEL);
// ========================

#ifdef NEO_FASTLED
class FastLEDReference {
public:
  FastLEDReference(CLEDController &controler) : _controler(controler){}
  //CLEDController &operator *() { return controler; }
  CLEDController *operator->() { return &_controler; }
protected:
  CLEDController &_controler;
};
#endif

class Cube {
public:
  Cube(int width, int depth, int height);
  ~Cube();
  void setup();
  void loop(int loopNumber);
  void show();

  void randomColors(int loopNumber);
  void colorStrips(int loopNumber);
  void colorPlanes(int loopNumber);
  void allColors(int loopNumber);
  void expandingSquares(int loopNumber, int dir);
  void expandingSquaresInward(int loopNumber);
  void expandingSquaresOutward(int loopNumber);
  void starry(int loopNumber);

  void set_pixel_color(int i, RGBPIXEL pixel);
  
  // typedef void (Cube::*ModePtr)(int);
protected:
  int width;
  int depth;
  int height;
  int pixelCount;
  int pixelsPerPlane;
  RGBPIXEL *leds = NULL;
#ifdef NEO_FASTLED
  FastLEDReference *strip = NULL;
#else
  NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> *strip = NULL;
#endif
};

