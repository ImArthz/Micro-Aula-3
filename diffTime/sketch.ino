volatile float time_pri = 0;
volatile float time_sec = 0;

unsigned long lastInterruptTime1 = 0;
unsigned long lastInterruptTime2 = 0;
const unsigned long debounceDelay = 200; // 200ms de debounce

void setup() {
  Serial.begin(9600);
  Serial.flush();
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), firstTime, RISING);
  attachInterrupt(digitalPinToInterrupt(3), lastTime, RISING);
}

void loop() {
  // Nada aqui por enquanto
}

void firstTime () {
  unsigned long currentTime = millis();

  if (currentTime - lastInterruptTime1 > debounceDelay) {
    time_pri = currentTime;
    Serial.println("Clicou botão 1");
    lastInterruptTime1 = currentTime;
  }
}

void lastTime () {
  unsigned long currentTime = millis();

  if (currentTime - lastInterruptTime2 > debounceDelay) {
    time_sec = currentTime;
    float diffTime = (time_sec - time_pri) / 1000.0;

    Serial.println("Clicou botão 2");
    Serial.print("Diferença de tempo : ");
    Serial.println(diffTime, 3); // 3 casas decimais

    lastInterruptTime2 = currentTime;
  }
}
