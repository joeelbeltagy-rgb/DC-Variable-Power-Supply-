#include <Wire.h>
#include <DFRobot_LCD.h>           // DFRobot's I²C LCD library

// change this to 0x3F if your module is at that address
#define LCD_ADDR   0x27
#define LCD_COLS   16
#define LCD_ROWS   2

// instantiate the LCD object
DFRobot_LCD lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

#define pwmPin   9    // OC1A
#define potPin   A0   // voltage-set pot

void setup() {
  Wire.begin();               // init I2C
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.backlight();            // turn on backlight (DFRobot API)
  lcd.setCursor(0,0);
  lcd.print("Duty Cycle:");

  // ——— PWM init (Timer1, 8-bit Fast PWM @31.25kHz) ———
  pinMode(pwmPin, OUTPUT);
  pinMode(potPin, INPUT);
  TCCR1A = (1 << COM1A1) | (1 << WGM10);  // non-invert OC1A, fast-PWM 8-bit
  TCCR1B = (1 << WGM12)    | (1 << CS10); // no prescaler
}

void loop() {
  // 1) read pot, map to 0–255, feed into OCR1A
  int potValue = analogRead(potPin);
  int pwmValue = map(potValue, 0, 1023, 0, 255);
  OCR1A = pwmValue;

  // 2) compute percent (0.0–100.0)
  float pct = (pwmValue / 255.0) * 100.0;
  pct = constrain(pct, 0.0, 100.0);

  // 3) display on LCD, line 2
  lcd.setCursor(0,1);
  lcd.print(pct, 1);      // one decimal place
  lcd.print("%   ");      // pad extra spaces to clear old digits

  delay(100);
}
