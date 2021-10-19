const int touchPin =4;
const int buttonPin = 15; // the number of the pushbutton pin
const int ledPin = 16; // the number of the LED pin
int readBtnState;
int readPinState;
int NOWledState=LOW;//현재의 LED 켜짐 상태 확인. 초기상태는 꺼짐상태.
int PREVIOUSledState=LOW;//바로 직전의 LED 켜짐 상태 확인. 초기상태는 꺼짐상태.
int TEMPledState=LOW;//터치핀을 활용한 임시 LED상태 변경.

long tempTime = 0;//버튼이 눌린 시간 저장
long releaseThreshold = 400;//100ms이하의 버튼 눌림을 인지함. 
long touchPinThreshold = 30;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  readBtnState = digitalRead(buttonPin);
  readPinState = touchRead(touchPin);
  Serial.println(readPinState);
  
  if(readBtnState == HIGH && PREVIOUSledState == LOW && millis()-tempTime > releaseThreshold)
  {
    NOWledState = !NOWledState;//현재 led상태 반대로 바꾸기
   // Serial.println(NOWledState);
    tempTime = millis();
  }

  if(readPinState<touchPinThreshold)
  {
    TEMPledState = !NOWledState;//누르는 순간 잠시 led상태를 반대로 바꾼다.
    digitalWrite(ledPin, TEMPledState);   
  }
  else digitalWrite(ledPin, NOWledState);
  

  PREVIOUSledState = readBtnState;
}
 
