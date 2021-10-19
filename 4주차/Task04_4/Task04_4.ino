const int ledChannel = 0;
const int resolution = 8;
const int buzPin = 23;
const int duty = 18;

int sVal;
int nFrq[]={262, 277, 294, 311, 330, 349, 370, 392, 415,440, 466,  494};

void playNote(int note, int dur)
{
  ledcSetup(ledChannel, nFrq[note], resolution);
  ledcWrite(ledChannel, duty);
  Serial.println(note);
  delay(dur);
}

void setup()
{
  Serial.begin(115200);
  ledcAttachPin(buzPin, ledChannel);
}

void loop()
{
  if(Serial.available()>0)
  {
    sVal = Serial.read();
    playNote(sVal-0x30, 250);
  }
}
