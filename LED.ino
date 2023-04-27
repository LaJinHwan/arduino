const int switchPin = 2;
const int ledPin = 13;
bool isButtonPressed = false; // 버튼이 눌렸는지 여부를 저장할 변수
unsigned long previousMillis = 0;
unsigned long interval = 0; // LED 깜빡이는 간격을 저장할 변수
int buttonPressCount = 0;
bool isLongPressed = false; // 버튼이 오랫동안 눌렸는지 여부를 저장할 변수
unsigned long buttonPressStartTime = 0; // 버튼이 눌린 시간을 저장할 변수

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int switchState = digitalRead(switchPin);

  // 버튼이 눌렸을 때
  if (switchState == LOW) {
    // 버튼이 이전에 눌렸었는지 확인하여 LED 깜빡이는 간격을 변경
    if (!isButtonPressed) {
      isButtonPressed = true; // 버튼이 눌렸음을 저장
      buttonPressStartTime = millis(); // 버튼이 눌린 시간 저장
      digitalWrite(ledPin, HIGH); // LED 켜기
    }

    // 버튼이 2초 이상 눌린 경우
    if (millis() - buttonPressStartTime > 2000) {
      isLongPressed = true;
    }

    // 딜레이를 추가하여 버튼이 한 번만 인식되도록 함
    delay(50);
  } else {
    // 버튼이 떨어졌을 때
    if (isButtonPressed) {
      if (isLongPressed) {
        // 버튼이 오랫동안 눌린 경우 LED 끄기
        digitalWrite(ledPin, LOW);
        while(1){
         delay(1);
          if(digitalRead(switchPin) == LOW) {
            isButtonPressed = false; // 버튼이 떨어졌음을 저장
            isLongPressed = false; // 버튼이 오랫동안 눌린 상태 초기화
            break;
          }
        }
      } else {
        buttonPressCount++;

        if (buttonPressCount == 1) {
          interval = 1000;
        } else if (buttonPressCount == 2) {
          interval = 100;
        } else if (buttonPressCount == 3) {
          interval = 0;
        } else if (buttonPressCount == 4) {
          buttonPressCount = 0; // 버튼 누른 횟수 초기화
          interval = 1000; // 다시 1회 누름: 1초로 설정
        }
      }

      isButtonPressed = false; // 버튼이 떨어졌음을 저장
      isLongPressed = false; // 버튼이 오랫동안 눌린 상태 초기화
    }
  }

  // LED 깜빡이는 간격에 따라 LED 켜고 끄기
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();
    digitalWrite(ledPin, !digitalRead(ledPin));
  }
}
