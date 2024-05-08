void fadeAnimation(int red, int green, int blue){
  float r, g, b;

  // FADE IN
  for(int i = 0; i <= 255; i++) {
    r = (i/256.0)*red;
    g = (i/256.0)*green;
    b = (i/256.0)*blue;
    fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
    FastLED.show();
    delay(2);
  }

  // FADE OUT
  for(int i = 255; i >= 0; i--) {
    r = (i/256.0)*red;
    g = (i/256.0)*green;
    b = (i/256.0)*blue;
    fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
    FastLED.show();
    delay(2);
  }
}
