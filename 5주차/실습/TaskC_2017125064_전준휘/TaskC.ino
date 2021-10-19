const int ledPin = 16;
const int ledPin2 = 17;
const int ledPin3 = 5;
const int motionSensor = 36;

unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;

const int ledPinARR[3] = {16, 17, 5};
int ledCnt=0;
int ledARR[5] = {0, 0, 0};
const int time_threshold = 15000;

void IRAM_ATTR detectsMovement() 
{
  startTimer = true;
  ledCnt++;

  if(ledCnt%3==1)
  {
    Serial.println ("1st MOTION DETECTED!");
    digitalWrite(ledPin, HIGH);
    ledARR[0] = millis();
  }

  else if(ledCnt%3==2)
  {
    Serial.println ("2nd MOTION DETECTED!");
    digitalWrite(ledPin2, HIGH);
    ledARR[1] = millis();
  }

  else if(ledCnt%3==0)
  {
    Serial.println ("3rd MOTION DETECTED!");
    digitalWrite(ledPin3, HIGH);
    ledARR[2] = millis();
  }
  lastTrigger = millis();
}


void setup()
{
  Serial.begin(115200);
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop()
{
  now = millis();

  for(int i=0; i<3; i++)
  {
    if(ledARR[i]==0) continue;
    else if((now-ledARR[i] > time_threshold))
    {
      digitalWrite(ledPinARR[i], LOW);
      ledARR[i]=0;
      Serial.println("Pin" + String(i+1) + "OFF");
      startTimer = false; 
    }
  }
}
