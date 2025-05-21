volatile bool alarmeAtivo = false;
volatile bool modoSoneca = false;
volatile bool botaoToggle = false;
volatile uint16_t contadorTempo = 0;

void acionarToggle() {
  botaoToggle = true;
}

void ativarSoneca() {
  if (alarmeAtivo) {
    alarmeAtivo = false;
    modoSoneca = true;

    contadorTempo = 0;
    TCNT1 = 0;

    Serial.println("Soneca Iniciada");
  }
}

ISR(TIMER1_COMPA_vect) {
  contadorTempo++;
  TCNT1 = 0;
}

void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);   // LED ou Buzzer
  pinMode(2, INPUT);     // Botão Toggle
  pinMode(3, INPUT);     // Botão Soneca

  attachInterrupt(digitalPinToInterrupt(2), acionarToggle, RISING);
  attachInterrupt(digitalPinToInterrupt(3), ativarSoneca, RISING);

  cli();  // Desabilita interrupções globais temporariamente

  TCCR1A = 0b00000000;   // Timer em modo normal
  TCCR1B = 0b00001000;   // CTC (Clear Timer on Compare Match)
  TCCR1B = 0b00000101;   // Prescaler em 1024

  OCR1A = 15625;         // Valor para 1 segundo
  TIMSK1 |= 0b00000010;  // Habilita interrupção por comparação A

  sei();  // Reabilita interrupções globais
}

void loop() {
  if (modoSoneca) {
    if (contadorTempo >= 5) {
      Serial.println("Soneca Finalizada");
      alarmeAtivo = true;
      modoSoneca = false;

      contadorTempo = 0;
      TCNT1 = 0;
    }
  }

  if (alarmeAtivo) {
    tone(13, 262, 20);
    if (contadorTempo >= 30) {
      alarmeAtivo = false;
    }
  }

  if (botaoToggle) {
    alarmeAtivo = !alarmeAtivo;
    botaoToggle = false;

    contadorTempo = 0;
    TCNT1 = 0;
  }
}
