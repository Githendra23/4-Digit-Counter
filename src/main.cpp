#include <Arduino.h>

#define TOTAL_SEGMENTS 7
#define TOTAL_DIGITS 4

int segments[] = {12, 11, 10, 9, 8, 7, 6};
int digits[] = {A1, A2, A3, A4};

void displayDigit(int number);
void turnOffAllDigits();

void setup()
{
  for (int i = 0; i < TOTAL_SEGMENTS; i++)
  {
    pinMode(segments[i], OUTPUT);
  }

  for (int i = 0; i < TOTAL_DIGITS; i++)
  {
    pinMode(digits[i], OUTPUT);
  }
  Serial.begin(9600);
}

int count = 80;
void loop()
{
  static uint32_t previousSecond = millis();

  displayDigit(count);

  if (millis() - previousSecond >= 100)
  {
    previousSecond = millis();

    count = (count + 1) % 10000;
    // Serial.println(count); // Commented out for optimization
  }
}

void displayDigit(int number)
{
  const int digitSegments[][TOTAL_SEGMENTS] = {
      {1, 1, 1, 1, 1, 1, 0}, // Define segments for digits 0-9
      {0, 1, 1, 0, 0, 0, 0},
      {1, 1, 0, 1, 1, 0, 1},
      {1, 1, 1, 1, 0, 0, 1},
      {0, 1, 1, 0, 0, 1, 1},
      {1, 0, 1, 1, 0, 1, 1},
      {1, 0, 1, 1, 1, 1, 1},
      {1, 1, 1, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 0, 1, 1}};

  for (int i = TOTAL_DIGITS - 1; i >= 0; i--)
  {
    byte digitNumber = (number / int(pow(10, TOTAL_DIGITS - 1 - i))) % 10;

    turnOffAllDigits();

    for (int j = 0; j < TOTAL_SEGMENTS; j++)
    {
      digitalWrite(segments[j], digitSegments[digitNumber][j]);
    }

    digitalWrite(digits[i], i == TOTAL_DIGITS - 1 || number / int(pow(10, TOTAL_DIGITS - 1 - i)) > 0 ? LOW : HIGH);
  }
}

void turnOffAllDigits()
{
  for (int j = 0; j < TOTAL_DIGITS; j++)
  {
    digitalWrite(digits[j], HIGH);
  }
}
