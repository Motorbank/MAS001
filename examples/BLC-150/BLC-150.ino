#define EN_PIN  6
#define DIR_PIN 5

#define BUTTON_1  13
#define BUTTON_2  12

void setup() {
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(EN_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  digitalWrite(DIR_PIN, LOW);
  digitalWrite(EN_PIN, LOW);

}

uint16_t val;
void loop() {
  if(digitalRead(BUTTON_1) == HIGH) digitalWrite(EN_PIN, HIGH);
  else digitalWrite(EN_PIN, LOW);

  if(digitalRead(BUTTON_2) == HIGH) digitalWrite(DIR_PIN, HIGH);
  else digitalWrite(DIR_PIN, LOW);

  delay(50);
}
