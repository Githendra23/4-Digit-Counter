#include <Arduino.h>

#define BITSIZE 14
#define TOTAL_DIGITS 4
#define TOTAL_SEGMENTS 7
#define MAX_COUNT (int)pow(10, TOTAL_DIGITS)

int segments[] = {12, 11, 10, 9, 8, 7, 6};
int digits[] = {A1, A2, A3, A4};

void displayDigit(int number);
byte getDigit(int number, int position);
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

int count = 0;
void loop()
{
  static uint32_t previousSecond = millis();

  displayDigit(count);

  if (millis() - previousSecond >= 100)
  {
    previousSecond = millis();

    count = (count + 1) % MAX_COUNT;
    Serial.println(count);
  }
}

void displayDigit(int number)
{
  const int digitSegments[][7] = {
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
    byte digitNumber = getDigit(number, i);

    turnOffAllDigits();

    for (int j = 0; j < TOTAL_SEGMENTS; j++)
    {
      digitalWrite(segments[j], digitSegments[digitNumber][j]);
    }

    digitalWrite(digits[i], i == 3 || number / (int)pow(10, 3 - i) > 0 ? LOW : HIGH);
  }
}

byte getDigit(int number, int position)
{
  String binaryString = String(number);

  while (binaryString.length() != 4)
  {
    binaryString = "0" + binaryString;
  }

  char digitChar = binaryString[position];
  byte digitValue = digitChar - '0';

  return digitValue;
}

void turnOffAllDigits()
{
  for (unsigned int j = 0; j < TOTAL_DIGITS; j++)
  {
    digitalWrite(digits[j], HIGH);
  }
}