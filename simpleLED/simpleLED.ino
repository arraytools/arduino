int led = 13;
void setup() {
  // put your setup code here, to run once:
  // Serial.begin(115200);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println("Hello World!");
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}
