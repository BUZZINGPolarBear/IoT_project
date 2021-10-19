const int joyPinX = 34;
const int joyPinY= 39;
const int joySW = 36;
const int cdsPin = 35;

int xVal = 0, yVal=0, sVal=0, cVal=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(joySW, INPUT);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  xVal = analogRead(joyPinX);
  yVal = analogRead(joyPinY);
  cVal = analogRead(cdsPin);
  sVal = analogRead(joySW);

  String str = "(X, Y) = (" + String(xVal) + ", " + String(yVal) + ")\n";
  Serial.print("JOYCON status: " + str);
  Serial.println(sVal?"OFF":"ON");
  Serial.println("Cds Value = " + String(cVal));
  delay(500);
}
