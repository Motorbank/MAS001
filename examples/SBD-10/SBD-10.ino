#define EN_PIN  6
#define DIR_PIN 5
#define STP_PIN 9

#define BUTTON_1  13
#define BUTTON_2  12

void setup() {
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(EN_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  digitalWrite(DIR_PIN, LOW);
  digitalWrite(EN_PIN, LOW);

  // Init Timer 1
  pinMode(STP_PIN, OUTPUT);
  TCCR1A = 0B01000000;  // Toggle OC1A on compare match / CTC Mode
  TCCR1B = 0B00001001; // CTC Mode / timer_clock = (16/64)MHz = 250kHz
  TCNT1 = 0;
  OCR1A = 0;
  TCCR1C = 0B10000000; // Force Output Compare for Channel A
}

uint16_t val;
void loop() {
  if(digitalRead(BUTTON_1) == HIGH) digitalWrite(EN_PIN, HIGH);
  else digitalWrite(EN_PIN, LOW);

  if(digitalRead(BUTTON_2) == HIGH) digitalWrite(DIR_PIN, HIGH);
  else digitalWrite(DIR_PIN, LOW);

  val = (uint16_t)analogRead(A0) * 10 + 1000;
  OCR1AL = (uint8_t)val;
  OCR1AH = (uint8_t)(val >> 8);
  delay(50);
}
