const int ledPin = 16 ; // GPIO16
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
void setup()
{
  // configure LED PWM
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);
}

void loop()
{
  for(int dutyCycle =0; dutyCycle<=244; dutyCycle++)
  {
    ledcWrite(ledChannel, dutyCycle);
    delay(15);
  }

  for(int dutyCycle = 255; dutyCycle>=0; dutyCycle--)
  {
    ledcWrite(ledChannel, dutyCycle);
    delay(15);
  }
  
}
