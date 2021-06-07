const int sensorPin = A0, prototypePin = A1, thPin = A2, hrPin = A3, tPin = A4, oPin = A5;
int sensorValue = 0, prototypeValue = 0, preSensorValue = 0, quantity = 0, buttonState = 0;
int quantityDigit[4];
void setup()
{
  for (int i = 1; i < 13; i++)
  {
    pinMode(i, OUTPUT);
  }
}
void singleDisplay(int number)
{
  if (number == 0)
  {
    digitalWrite(1, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
  if (number == 1)
  {
    digitalWrite(1, LOW);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
  if (number == 2)
  {
    digitalWrite(1, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
  }
  if (number == 3)
  {
    digitalWrite(1, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
  }
  if (number == 4)
  {
    digitalWrite(1, LOW);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
  }
  if (number == 5)
  {
    digitalWrite(1, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
  }
  if (number == 6)
  {
    digitalWrite(1, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
  }
  if (number == 7)
  {
    digitalWrite(1, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
  if (number == 8)
  {
    digitalWrite(1, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
  }
  if (number == 9)
  {
    digitalWrite(1, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
  }
}
void quantityToDigitArray()
{
  int num = quantity;
  for (int i = 0; i < 4; ++i, num /= 10)
    quantityDigit[3 - i] = num % 10;
}
void turnOnAtIndex(int index)
{
  index += 8;
  for (int i = 8; i < 12; i++)
  {
    if (i == index)
    {
      digitalWrite(i, LOW);
    }
    else
    {
      digitalWrite(i, HIGH);
    }
  }
}
void displayNumber()
{
  for (int i = 0; i < 4; i++)
  {
    singleDisplay(quantityDigit[i]);
    turnOnAtIndex(i);
    delay(10);
  }
}
void checkPreset()
{
  quantityToDigitArray();
  if (analogRead(thPin) == 0 && analogRead(hrPin) == 0 && analogRead(tPin) == 0 && analogRead(oPin) == 0)
  {
    buttonState = 0;
  }
  if (buttonState == 0)
  {
    if (analogRead(thPin) > 0)
    {
      if (quantityDigit[0] == 9)
      {
        quantity -= 9000;
      }
      else
      {
        quantity += 1000;
      }
      buttonState = 1;
    }
    if (analogRead(hrPin) > 0)
    {
      if (quantityDigit[1] == 9)
      {
        quantity -= 900;
      }
      else
      {
        quantity += 100;
      }
      buttonState = 1;
    }
    if (analogRead(tPin) > 0)
    {
      if (quantityDigit[2] == 9)
      {
        quantity -= 90;
      }
      else
      {
        quantity += 10;
      }
      buttonState = 1;
    }
    if (analogRead(oPin) > 0)
    {
      if (quantityDigit[3] == 9)
      {
        quantity -= 9;
      }
      else
      {
        quantity += 1;
      }
      buttonState = 1;
    }
  }
}
void loop()
{
  preSensorValue = sensorValue;
  sensorValue = analogRead(sensorPin);
  prototypeValue = analogRead(prototypePin);
  if (sensorValue != preSensorValue && prototypeValue == sensorValue)
  {
    quantity++;
  }
  checkPreset();
  displayNumber();
}
