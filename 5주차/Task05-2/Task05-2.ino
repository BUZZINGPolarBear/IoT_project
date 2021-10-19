const int ledPin = 16 ; // the number of the LED pin
int ledState = LOW; // ledState used to set the LED

unsigned long previousMillis = 0; 
const long interval = 1000; 

void setup() {
pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) 
  {
    //save the last time you blinked the LED
    previousMillis = currentMillis;
    if (ledState == LOW) ledState = HIGH;
    else ledState = LOW;
  }
  // set the LED with the ledState of the variable:
  digitalWrite(ledPin, ledState);
}
