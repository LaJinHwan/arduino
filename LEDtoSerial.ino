const int switchPin = 2;
const int ledPin = 13;
const int relay = 9;
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
  pinMode(relay,OUTPUT);
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
        pinlow();
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
    digitalWrite(relay,!digitalRead(relay));
  }
}

void seri()

{
if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input == "one") {
      interval = 1000;
    } else if (input == "two") {
      interval = 100;
    } else if (input == "three") {
      interval = 0;
    } else if (input == "zero") {
      digitalWrite(ledPin, LOW);
      pinlow();
    } else if (input == "sos") {
      
      sos();
    }
  }
}

void sos() {
  interval = 1000;
  unsigned long currentMillis = millis();

  for (int j = 1; j < 4; j++) {
    for (int i = 0; i < 6; i++) {
      if (i % 2 == 0) {
        digitalWrite(ledPin, HIGH);digitalWrite(relay, HIGH);
      } else {
        digitalWrite(ledPin, LOW);digitalWrite(relay, LOW);
      }
      
      if (j == 1 || j == 3) {
        if (i == 0 || i == 4) {
          
        } else if (i == 2) {
          
        }
      } else if (j == 2) {
        if (i == 0 || i == 4) {
          digitalWrite(relay, LOW);
        } else if (i == 2) {
          digitalWrite(relay, HIGH);
        }
      }
      
      if (j % 2 == 0) {
        interval = 200;
      } else {
        interval = 500;
      }
      
      while (millis() - currentMillis < interval / 2) { }
      currentMillis = millis();
     
    }
  }

 digitalWrite(ledPin,LOW);
 pinlow();
}

void pinlow(){
    while (1) {
        if (digitalRead(switchPin) == LOW) {
          isButtonPressed = false;
          isLongPressed = false;
          break;
        } else if (Serial.available() > 0) {
          String input = Serial.readStringUntil('\n');
          input.trim();
          if (input == "one") {
            interval = 1000;
            break;
          } else if (input == "two") {
            interval = 100;
            break;
          } else if (input == "three") {
            interval = 0;
            break;
          } else if (input == "sos"){
            sos();
          }
        }
      }
}


\

void loop() {
  swi();
  blink();
  seri();
  //relayto();
  
}
