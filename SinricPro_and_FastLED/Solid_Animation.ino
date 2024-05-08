void AllOn(int red, int green, int blue) {
  /* This function will turn ON all the LEDs to a solid color. */
  fill_solid(leds, NUM_LEDS, CRGB(red, green, blue));
  FastLED.show();
}

void AllOff() {
  /* This function will turn OFF all the LEDs. */
  FastLED.clear();
  FastLED.show();
}

void FadeOn(int red, int green, int blue) {
  /* This function will turn ON all LEDs with a fade animation. */
  float r, g, b;
  for(int i=0; i<=255; i++) {
    r = (i/256.0)*red;
    g = (i/256.0)*green;
    b = (i/256.0)*blue;
    fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
    FastLED.show();
    delay(2);
  }
}

void FadeOff(int red, int green, int blue) {
  /* This function will turn OFF all LEDs with a fade animation. NOTE: Color values must be provided as an initial starting point for the animation. */
  float r, g, b;
  for(int i=255; i>=0; i--) {
    r = (i/256.0)*red;
    g = (i/256.0)*green;
    b = (i/256.0)*blue;
    fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
    FastLED.show();
    delay(2);
  }
}

void SwipeOn(int red, int green, int blue) {
  /* This function will turn ON all LEDs with a line swipe animation. */
  for(int i=0; i<NUM_LEDS; i++) {
    leds[i].setRGB(red, green, blue);
    FastLED.show();
    delay(50);
  }
}

void SwipeOff(int red, int green, int blue) {
  /* This function will turn OFF all LEDs with a line swipe animation. NOTE: Try switching `NUM_LEDS` and `0` for i in the for loop for a different effect. */
  for(int i=0; i<NUM_LEDS; i++) {
    leds[i].setRGB(0, 0, 0);
    FastLED.show();
    delay(50);
  }
}
