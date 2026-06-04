#include <LiquidCrystal_I2C.h>

// ── LCD: I²C address 0x27, 16 columns, 2 rows ──────────────────────────────
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ── Pin definitions ─────────────────────────────────────────────────────────
#define POT_PIN   A0   // potentiometer → voltage setpoint
#define PWM_PIN    9   // PWM output → MOSFET gate driver

void setup() {
  pinMode(POT_PIN, INPUT);
  pinMode(PWM_PIN, OUTPUT);

  // ── LCD init ──────────────────────────────────────────────────────────────
  lcd.init();
  lcd.backlight();

  // ── Timer1: 8-bit Fast PWM, no prescaler → ~31.25 kHz ────────────────────
  // Eliminates audible switching noise compared to default 490 Hz analogWrite
  TCCR1A = (1 << COM1A1) | (1 << WGM10);  // non-inverting OC1A, fast-PWM 8-bit
  TCCR1B = (1 << WGM12)  | (1 << CS10);   // no prescaler
}

void loop() {
  // 1) Read potentiometer and map to PWM range (0–255)
  int pwmValue = map(analogRead(POT_PIN), 0, 1023, 0, 255);
  OCR1A = pwmValue;   // write directly to Timer1 compare register

  // 2) Calculate duty cycle percentage (0–100%)
  int duty = map(pwmValue, 0, 255, 0, 100);
  duty = constrain(duty, 0, 100);

  // 3) Calculate output voltage
  //    At 100% duty → ~24V output (transformer secondary peak after filtering)
  //    Scale factor: 24.0 / 100 = 0.24 V per percent
  float voltage = duty * 0.24;

  // 4) Update LCD
  //    Line 1: "Duty: 99%  "
  //    Line 2: "Volt: 23.76V"
  lcd.setCursor(0, 0);
  lcd.print("Duty: ");
  lcd.print(duty);
  lcd.print("%   ");      // trailing spaces clear leftover digits

  lcd.setCursor(0, 1);
  lcd.print("Volt: ");
  lcd.print(voltage, 2);  // 2 decimal places → matches display (23.76V)
  lcd.print("V   ");

  delay(100);
}
