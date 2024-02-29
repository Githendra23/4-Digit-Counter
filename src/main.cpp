#include <Arduino.h>

#define BITSIZE 14
#define TOTAL_DIGITS 4
#define TOTAL_SEGMENTS 7
#define MAX_COUNT 10000

int segments[] = {12, 11, 10, 9, 8, 7, 6};
int digits[] = {A1, A2, A3, A4};

void displayDigit(int number);
void disableDisplay();
int power(int base, int exponent);

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

int count = 1090;
void loop()
{
  static uint32_t previousSecond = millis();

  displayDigit(count);

  if (millis() - previousSecond >= 100)
  {
    previousSecond = millis();

    count = (count + 1) % MAX_COUNT;
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
    byte digitNumber = (number / power(10, TOTAL_DIGITS - 1 - i)) % 10;

    disableDisplay();

    digitalWrite(digits[i], i == TOTAL_DIGITS - 1 || number / int(power(10, TOTAL_DIGITS - 1 - i)) > 0 ? LOW : HIGH);

    for (int j = 0; j < TOTAL_SEGMENTS; j++)
    {
      digitalWrite(segments[j], digitSegments[digitNumber][j]);
    }
  }
}

void disableDisplay()
{
  for (unsigned int i = 0; i < TOTAL_DIGITS; i++)
  {
    digitalWrite(digits[i], HIGH);
  }

  for (unsigned int i = 0; i < TOTAL_SEGMENTS; i++)
  {
    digitalWrite(segments[i], LOW);
  }
}

int power(int base, int exponent)
{
  int result = 1;

  for (int i = 0; i < exponent; i++)
  {
    result *= base;
  }

  return result;
}