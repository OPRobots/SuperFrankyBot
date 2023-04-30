int RGBColor[] = {255, 0, 0};
int decColor = 0;
int incColor = 1;
long lastRGBmillis = 0;

void setBatteryColor() {
  byte batteryCharge = 0, r = 0, g = 0;
  batteryCharge = map(map(analogRead(BATTERY_PIN), 0, 1023, 0, 840), 740, 840, 0, 100);
  if (batteryCharge > 50) {
    r = map(batteryCharge, 51, 100, 255, 0);
    g = 255;

  } else if (batteryCharge < 50) {
    r = 255;
    g = map(batteryCharge, 49, 0, 255, 0);

  } else if (batteryCharge == 50) {
    r = 255;
    g = 255;
  }
  if (batteryCharge <= 10 || batteryCharge >= 90) {
    long tiempo = millis();
    do {
      setRGBColor(r, g, 0);
      delay(200);
      setRGBColor(0, 0, 0);
    } while ((millis() - tiempo) < 2000);
  } else {
    setRGBColor(r, g, 0);
    delay(2000);
    setRGBColor(0, 0, 0);
  }
}

void setRainbowColor() {
  if(millis()-lastRGBmillis > 10){
  RGBColor[decColor] -= 3;
  RGBColor[incColor] += 3;
  setRGBColor(RGBColor[0], RGBColor[1], RGBColor[2]);
  if (RGBColor[decColor] <= 0 || RGBColor[incColor] >= 255) {
    RGBColor[decColor] = 0;
    RGBColor[incColor] = 255;
    setRGBColor(RGBColor[0], RGBColor[1], RGBColor[2]);
    decColor++;
    if (decColor > 2) {
      decColor = 0;
    }
    incColor = decColor == 2 ? 0 : decColor + 1;
  }
  lastRGBmillis = millis();
  }
}

void setRGBColor(int r, int g, int b) {
  analogWrite(LED_DERECHO[0], 255 - r);
  analogWrite(LED_DERECHO[1], 255 - g);
  analogWrite(LED_DERECHO[2], 255 - b);
  analogWrite(LED_IZQUIERDO[0], 255 - r);
  analogWrite(LED_IZQUIERDO[1], 255 - g);
  analogWrite(LED_IZQUIERDO[2], 255 - b);
}
