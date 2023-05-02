const int switchPin = 2;
const int ledPin = 13;
bool isButtonPressed = false;
unsigned long previousMillis = 0;
unsigned long interval = 0;
int buttonPressCount = 0;
bool isLongPressed = false;
unsigned long buttonPressStartTime = 0;

void setup()
{
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}
void swi()
{
  int switchState = digitalRead(switchPin);

  if (switchState == LOW)
  {
    if (!isButtonPressed)
    {
      isButtonPressed = true;
      buttonPressStartTime = millis();
      digitalWrite(ledPin, HIGH);
    }

    if (millis() - buttonPressStartTime > 2000)
    {
      isLongPressed = true;
    }

    delay(50);
  }
  else
  {
    if (isButtonPressed)
    {
      if (isLongPressed)
      {
        digitalWrite(ledPin, LOW);
        while (1)
        {

          if (digitalRead(switchPin) == LOW)
          {
            isButtonPressed = false;
            isLongPressed = false;
            break;
          }
          else if (Serial.available() > 0)
          {
            String input = Serial.readStringUntil('\n');
            input.trim();

            if (input == "one")
            {
              interval = 1000;
              break;
            }
            else if (input == "two")
            {
              interval = 100;
              break;
            }
            else if (input == "three")
            {
              interval = 0;
              break;
            }
          }
        }
      }
      else
      {
        buttonPressCount++;

        if (buttonPressCount == 1)
        {
          interval = 1000;
        }
        else if (buttonPressCount == 2)
        {
          interval = 100;
        }
        else if (buttonPressCount == 3)
        {
          interval = 0;
        }
        else if (buttonPressCount == 4)
        {
          buttonPressCount = 0;
          interval = 1000;
        }
      }

      isButtonPressed = false;
      isLongPressed = false;
    }
  }
}

void blink()
{
  if (millis() - previousMillis >= interval)
  {
    previousMillis = millis();
    digitalWrite(ledPin, !digitalRead(ledPin));
  }
}

void seri()
{
  if (Serial.available() > 0)
  {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input == "one")
    {
      interval = 1000;
    }
    else if (input == "two")
    {
      interval = 100;
    }
    else if (input == "three")
    {
      interval = 0;
    }
    else if (input == "zero")
    {
      digitalWrite(ledPin, LOW);
      while (1)
      {

        if (digitalRead(switchPin) == LOW)
        {
          isButtonPressed = false;
          isLongPressed = false;
          break;
        }
        else if (Serial.available() > 0)
        {
          String input = Serial.readStringUntil('\n');
          input.trim();

          if (input == "one")
          {
            interval = 1000;
            break;
          }
          else if (input == "two")
          {
            interval = 100;
            break;
          }
          else if (input == "three")
          {
            interval = 0;
            break;
          }
        }
      }
    }
  }
}
void loop()
{
  swi();
  blink();
  seri();
}
