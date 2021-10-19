const int trigPin = 22;
const int echoPin = 23;

const int ledChannel = 0;
const int resolution = 8;
const int buzPin = 18;
const int duty = 18;

char sVal, sDel;
const int nFrq[]={262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466,  494, 0, 523};
const int nDelay[]={2000, 1500, 1000, 750, 500, 375, 250};

void setup()
{
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  ledcAttachPin(buzPin, ledChannel);
}

void playNote(int note, int dur)
{
  ledcSetup(ledChannel, note, resolution);
  ledcWrite(ledChannel, duty);
  delay(dur);
}

void loop()
{
  long duration, distance;
  //Triggering by 10us pulse
  digitalWrite(trigPin, LOW); // trig low for 2us
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // trig high for 10us
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //getting duration for echo pulse
  duration = pulseIn(echoPin, HIGH);
  //sound speed = 340 m/s = 34/1000 cm/us
  //distance = duration * 34/1000 * 1/2
  distance = duration * 17 / 1000;
  Serial.print(distance);
  Serial.print("cm");

  if(distance<100)
  {
    playNote(1000-(distance*10), distance*70);
    Serial.print("\nNote: " + String(1000-(distance*10)));
    Serial.println();
  }
  else
  {
    playNote(200, 500);
  }
  delay(500);
}
