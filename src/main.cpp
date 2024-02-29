#include <Arduino.h>

int segments[] = {7, 6, 5, 11, 10, 8, 9, 4};

void displayDigit(int number);

void setup()
{
  for (int i = 4; i <= 11; i++)
  {
    digitalWrite(i, OUTPUT);
  }
}

int count = 0;
void loop()
{
  displayDigit(count);
  delay(1000);
  count = (count + 1) % 10;
}

void displayDigit(int number)
{
  const int digitSegments[][7] = {
      {1, 1, 1, 1, 1, 1, 0},
      {0, 1, 1, 0, 0, 0, 0},
      {1, 1, 0, 1, 1, 0, 1},
      {1, 1, 1, 1, 0, 0, 1},
      {0, 1, 1, 0, 0, 1, 1},
      {1, 0, 1, 1, 0, 1, 1},
      {1, 0, 1, 1, 1, 1, 1},
      {1, 1, 1, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 0, 1, 1}};

  for (int i = 0; i < 7; i++)
  {
    digitalWrite(segments[i], digitSegments[number][i]);
  }
}
