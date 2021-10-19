const int ledChannel = 0;
const int resolution = 8;
const int buzPin = 23;
const int duty = 18;

char sVal, sDel;
const int nFrq[]={262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466,  494, 0, 523};
const int nDelay[]={2000, 1500, 1000, 750, 500, 375, 250};
String inptStr ="";
char toChar[1000];

void playNote(char note, int dur)
{
  int temp;
  if(note == 'c')
  {
    
    ledcSetup(ledChannel, 523, resolution);
    ledcWrite(ledChannel, duty);
    delay(dur);
    return;
  }
  else if(note == 'z')
  {
    ledcSetup(ledChannel, 0, resolution);
    delay(dur);
    return;
  }
  else temp = note-0x30;

  Serial.println(String(note) +" "+ String(dur));
  Serial.println("nFrq= " + String(nFrq[temp]) + ",Del= " + String(dur));
  ledcSetup(ledChannel, nFrq[temp], resolution);
  ledcWrite(ledChannel, duty);
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
    inptStr = Serial.readString();
    inptStr.toCharArray(toChar, inptStr.length());

    Serial.println(inptStr);
    for(int i=0; i<inptStr.length()-2; i+=2)
    {
      sVal = toChar[i];
      sDel = toChar[i+1];

      playNote(sVal, nDelay[sDel-'0']);
    }
    exit(0);
  }
}
