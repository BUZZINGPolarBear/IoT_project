#define timeSeconds 20
// Set GPIOs for LED and PIR Motion Sensor
const int led1 = 5;
const int led2 = 16;
const int led3 = 17;

const int motionSensor = 36;

int led[3] = {5,16,17};
int now[3];
int last[3];
int startTimer[3];
int lastTrigger[3];
int i = 0;
// Timer: Auxiliary variables

int cnt = 0;
int current;
void IRAM_ATTR detectsMovement() {
  
  lastTrigger[cnt] = millis();
  Serial.print("MOTION DETECTED!!!-");
  Serial.println(cnt);
  digitalWrite(led[cnt], HIGH);
  startTimer[cnt] = true;
  
  cnt++;
  if (cnt == 3) {
    cnt = 0;
  }
  
  
}


void setup() { // Serial port for debugging purposes
Serial.begin(115200); // PIR Motion Sensor mode INPUT_PULLUP
pinMode(motionSensor, INPUT_PULLUP); // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING); // Set LED to LOW

pinMode(led1, OUTPUT);
digitalWrite(led1, LOW);
pinMode(led2, OUTPUT);
digitalWrite(led2, LOW);
pinMode(led3, OUTPUT);
digitalWrite(led3, LOW);

}


void loop() {// Current time
   current = millis();
   // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if (startTimer[i] ){
    if ((current - lastTrigger[i] > (timeSeconds*1000))) {
    Serial.print("Motion stopped...");
    Serial.println(i);
    digitalWrite(led[i], LOW);
    startTimer[i] = false;
    i++;
    if (i >= 3) {
      i = 0;
      cnt = 0;
      }
    }
  }
 
}
