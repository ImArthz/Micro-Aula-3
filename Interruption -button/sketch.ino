volatile int contador = 0;
volatile unsigned long ultimaInterrupcao = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), incrementarContador, RISING);
}

void loop() {
  Serial.print("Contador: ");
  Serial.println(contador);
  delay(500);
}

void incrementarContador() {
  unsigned long tempoAtual = millis();
  
  // Verifica se passou pelo menos 200ms desde a última interrupção
  if (tempoAtual - ultimaInterrupcao > 200) {
    contador++;
    ultimaInterrupcao = tempoAtual;
  }
}
