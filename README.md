

LED.ino -  스위치를 누르는 것을 카운팅
           1회 => 1초 주기로 on/off
           2회 => 0.1초 주기로 on/off
           3회 => 영구 on
           
           2초 이상 누를 시 => 영구 off  스위치를 다시 누르면 반복
           스위치 누르는 것을 확실히 하기 위해 딜레이 함수 


LEDtoSerial.ino - LED.ino에 기능 추가
                  입력을 하면 동작을 1회,2회,3회,2초 이상 누르는 기능을 수행
                  one => 1초 주기로 on/off
                  two => 0.1초 주기로 on/off
                  three => 영구 on
                  zero => 영구 off
                 
relay.ino - LEDtoSerial.ino에 기능 추가
            sos 입력 시 모스부호로 릴레이 모듈에서 소리가 나며 LED로도 빛을 낸다.
