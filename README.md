# Relatório de Atividades - Laboratório de Microcontroladores e Microprocessadores  
**Aula 03 — Interrupções e Timers no Arduino**  

---

## 👥 Nome da Dupla  

<div align="center">

### 👥 Equipe do Projeto

| **Alunos** | **Professor** |
|:----------:|:-------------:|
| <a href="https://github.com/ImArthz"><img src="https://github.com/ImArthz.png" width="100" style="border-radius: 50%; box-shadow: 0 0 8px #239A3B; border: 2px solid #239A3B"></a><br>**Arthur Mendonça**<br>[![GitHub](https://img.shields.io/badge/Ver_Repositórios-239A3B?style=flat-square&logo=github)](https://github.com/ImArthz) | <a href="https://github.com/DiegoAscanio"><img src="https://github.com/DiegoAscanio.png" width="100" style="border-radius: 50%; box-shadow: 0 0 8px #00599C; border: 2px solid #00599C"></a><br>**Prof. Diego Ascanio**<br>[![GitHub](https://img.shields.io/badge/Ver_Repositórios-00599C?style=flat-square&logo=github)](https://github.com/DiegoAscanio) |
| <a href="https://github.com/alvaroajs"><img src="https://github.com/alvaroajs.png" width="100" style="border-radius: 50%; box-shadow: 0 0 8px #239A3B; border: 2px solid #239A3B"></a><br>**Álvaro Silva**<br>[![GitHub](https://img.shields.io/badge/Ver_Repositórios-239A3B?style=flat-square&logo=github)](https://github.com/alvaroajs) | |

</div>


## Exercício 1: Contador de Interrupções Externas:

### Objetivo:  

Neste exercício, desenvolveu-se um circuito utilizando o Arduino para contabilizar quantas vezes o push button foi pressionado, exibindo esse valor no Monitor Serial.

### Componentes Principais:

- 1 Arduino UNO.
- 1 Push Button
- 1 Resistor de 10 kΩ.


### Código:  
```cpp
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


```
### Funcionamento:  

Após o push button ser pressionado, o Serial Print exibe quantas vezes ele foi acionado.


### Demonstração Visual:  

<div align="center">
  <img src="docs/imgs/projeto 1 img.png" 
       alt="circuito Contado De Interrupções externa" 
       width="600">
  <br>
  <em>Circuito Circuito para conta interropções externas em arduino.</em>
</div>

### Link para o Projeto no Wokwi:  
[![Projeto 1 - Contador de interrupções](https://img.shields.io/badge/Wokwi-Projeto_1-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://wokwi.com/projects/431569904349137921)

----------------------------------------

## Exercício 2: Medidor de Tempo de Interrupção:

### Objetivo:  

Criação de um projeto com Arduino que tem como objetivo medir e contabilizar, em milissegundos, o tempo decorrido entre o acionamento de dois push buttons.

### Componentes Principais:  

- 1 Arduino Uno.
- 2 Push Button.
- 2 Resistores de 10 kΩ.

### Código:  
```cpp
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
    Serial.println("Clicked Button 1");
    lastInterruptTime1 = currentTime;
  }
}

void lastTime () {
  unsigned long currentTime = millis();

  if (currentTime - lastInterruptTime2 > debounceDelay) {
    time_sec = currentTime;
    float diffTime = (time_sec - time_pri) / 1000.0;

    Serial.println("Clicked Button 2");
    Serial.print("Diff Time: ");
    Serial.println(diffTime, 3); // 3 casas decimais

    lastInterruptTime2 = currentTime;
  }
}

```
### Funcionamento:  

O programa utiliza interrupções externas para detectar os eventos de pressão dos botões: o primeiro botão inicia a contagem de tempo e o segundo botão encerra a contagem, permitindo assim calcular com precisão o intervalo entre os dois eventos.

### Demonstração Visual:  

### Demonstração Visual:  
<div align="center">
  <img src="docs/imgs/projeto 2 img.png" 
       alt="Circuito Medidor de tempo de interrupção" 
       width="600">
  <br>
  <em> Circuito: que mede o tempo relativo entre interrupção externa de dois botões.</em>
</div>

### Link para o Projeto no Wokwi:  
[![Projeto 2 - Medidor de tempor de interrupção](https://img.shields.io/badge/Wokwi-Projeto_2-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://wokwi.com/projects/431569895044073473)

----------------------------------------

# Exercício 3: Alarme de Interrupção com Cancelamento:




### Objetivo:  
Desenvolver um sistema de alarme com Arduino que utilize interrupção externa para detectar movimento (via push button no pino 2). Quando o botão é pressionado, um LED acende e um buzzer emite som, mantendo o alarme ativado. Um segundo botão, conectado a outro pino (sem interrupção), serve para desligar o alarme.

---

### Componentes Principais:  

- 1 Arduino UNO.
- 2 Push Button.
- 1 Ded.
- 1 Buzzer.

---

### Código:  
```cpp
int Sensorpin = 2;
int Cancelpin = 3;
int Ledpin = 13;

bool pressed = false;

void press()
{
  pressed = true;
  digitalWrite(Ledpin, HIGH);
}

void pause()
{
  digitalWrite(Ledpin, LOW);
  pressed = false;
}

void setup()
{
  Serial.begin(9600);

  pinMode(Sensorpin,INPUT);
  pinMode(Cancelpin,INPUT);
  pinMode(Ledpin,INPUT);

  attachInterrupt(digitalPinToInterrupt(Sensorpin),press,RISING);
  attachInterrupt(digitalPinToInterrupt(Cancelpin),pause,RISING);
}

void loop()
{
  if(pressed == true)
  {
    tone(12, 301, 250);
  }
  delay(200);
}


```
### Funcionamento:  

Após pressionar o primeiro botão, o buzzer imitira um som até ser desativado pressionando o outro push button.

---

### Demonstração Visual:  

<div align="center">
  <img src="docs/imgs/projeto 3 img.png" 
       alt="Alarme " 
       width="400">
  <br>
  <em>Circuito com Alarme.</em>
</div>

---

### Link para o Projeto no Wokwi:  
[![Projeto 3 - Alarme](https://img.shields.io/badge/Wokwi-Projeto_3-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://wokwi.com/projects/431572574259127297)

---
# Exercício 4:  



### Objetivo:  
Desenvolver um sistema de alarme com Arduino que, ao ser ativado, emite um som contínuo. Caso o botão de soneca seja pressionado, o alarme silencia temporariamente (por um período predeterminado), e volta a tocar automaticamente após esse tempo.

---

### Componentes Principais:  

- 1 Arduino UNO
- 1 Buzzer
- 2 Push Button

---

### Código:  
```cpp
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


```
### Funcionamento:  

O sistema consiste em um alarme controlado por Arduino, que é ativado por um botão. Quando o botão de alarme é pressionado, o sistema dispara um sinal sonoro contínuo por meio de um buzzer. O alarme permanecerá ativo até que o usuário pressione o botão de soneca, o qual silencia temporariamente o alarme.

---  
### Demonstração Visual:  
<div align="center">
  <img src="docs/imgs/projeto 4 img.png" 
       alt="Alarme com soneca" 
       width="400">
  <br>
  <em>Circuito Alarme com funcionalidade de soneca.</em>
</div>  

---  

### Link para o Projeto no Wokwi:  
[![Projeto 4 - Alarme com soneca](https://img.shields.io/badge/Wokwi-Projeto_4-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://wokwi.com/projects/431583804083174401)  

---  


