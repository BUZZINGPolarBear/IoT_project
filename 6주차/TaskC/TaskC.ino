#include <EEPROM.h>
// define the number of bytes you want to access
#define EEPROM_SIZE 80

const int ledChannel = 0;
const int resolution = 8;
const int buzPin = 23;
const int buttonPin = 15;
const int duty = 18;

byte sVal, sDel;
const int nFrq[]={262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466,  494, 0, 523};
const int nDelay[]={2000, 1500, 1000, 750, 500, 375, 250};
String inptStr ="";
int str_len;
char toChar[1000];

int buttonState; 
int lastButtonState = LOW; 
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50; 

int music_cnt=0;
int music_pair_index = 3;
int is_music_saved=false;
bool is_music_played=false;



void setup()
{
  Serial.begin(115200);
  ledcAttachPin(buzPin, ledChannel);
  pinMode(buttonPin, INPUT);  
  // initialize EEPROM with predefined size
  EEPROM.begin(EEPROM_SIZE);
  pinMode(buttonPin, INPUT);
  if(EEPROM.read(0) == 0xAC) is_music_saved = true;
  EEPROM.commit();
  
}

void loop()
{
  
  if(Serial.available()>0)
  {
    inptStr = Serial.readString();
    str_len = inptStr.length();
    inptStr.toCharArray(toChar, str_len);
    
    if(toChar[0]=='<' || toChar[str_len-1] == '>')
    {
      Serial.println("Saving Notes.....");
      for(int i=1; i<inptStr.length()-2; i+=2)
      {
        EEPROM.write(music_pair_index++, byte(toChar[i]-'0'));
        Serial.println("Saved At: " + String(music_pair_index) + " Which is: " + EEPROM.read(music_pair_index-1));
        EEPROM.write(music_pair_index++, byte(toChar[i+1]-'0'));
        Serial.println("Saved At: " + String(music_pair_index) + " Which is: " + EEPROM.read(music_pair_index-1));
        EEPROM.commit();
      }
      EEPROM.write(2, str_len-2);
      Serial.println("문자열 길이: " + str_len-2); 
      EEPROM.write(0, 0xAC);
      EEPROM.commit();
      Serial.println("Music Saved.");
    }

    else
    {
      Serial.println(inptStr);
      for(int i=0; i<inptStr.length()-2; i+=2)
      {
        sVal = toChar[i];
        sDel = toChar[i+1];
        
        playNote(sVal, nDelay[sDel-'0']);
       }
       playNote('z', 2000);
    }
  }
  
  if(is_music_saved && !is_music_played )
  {
    Serial.println("#######Saved Note is Playing.....#######");
    music_cnt = 40;
    
    for(int i=3; i<EEPROM.read(2); i += 2)
    {
      sVal = EEPROM.read(i);
      sDel = EEPROM.read(i+1);
      Serial.println("-----------");
      Serial.println("Got " + String(sVal+'0'-0x30) + " AND " + String(sDel+'0'-0x30));
      playNote(sVal+'0', nDelay[sDel+'0'-0x30]);
    }
    playNote('z', 20000);
    EEPROM.write(0,0xAB);
    EEPROM.commit();
    is_music_played=true;
  }
}

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
