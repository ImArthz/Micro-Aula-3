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
