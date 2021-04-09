#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>

char charEntrada;
int vibPin = PB3;
int palPin = PB4;
int adePin = PA4;
int revPin = PA5;

DFRobotDFPlayerMini player;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600); // Pines A9 TX y A10 RX
  Serial2.begin(9600); // Pines A2 TX y A3 RX
  pinMode(vibPin, OUTPUT);
  pinMode(palPin, OUTPUT);
  pinMode(adePin, OUTPUT);
  pinMode(revPin, OUTPUT);
  if (player.begin(Serial2))
  {
    Serial1.println("OK");
    player.volume(30);
  } else {
    Serial1.println("Conexión a DFPLayer Mini fallo.");
  }
}

void loop()
{
  if (Serial1.available() > 0)
  {
    charEntrada = Serial1.read();
    switch (charEntrada)
    {
    case 'a':
    /* Comienza a sonar el archivo de sonido durante 1.5 segundos y luego se
    detiene */
      player.play(1);
      Serial.println("A");
      delay(1500);
      player.stop();
      break;

    case 'b':
    /* El motor gira durante 3 segundos para apretar la banda y dar una
    sensacion de abrazo, se mantiene apretado durante 3 segundos mas
    y luego gira en el sentido contrario para soltar a la persona */
      digitalWrite(adePin, HIGH);
      digitalWrite(revPin, LOW);
      delay(3000);

      digitalWrite(adePin, LOW);
      digitalWrite(revPin, LOW);
      delay(3000);

      digitalWrite(adePin, LOW);
      digitalWrite(revPin, HIGH);
      delay(3000);

      digitalWrite(adePin, LOW);
      digitalWrite(revPin, LOW);
      delay(500);
      Serial.println("B");
      break;

    case 'c':
    /* Los motores vibradores comienzan a actuar durante 2.5 segundos, se
    detienen durante 1 segundo y el proceso se repite una vez mas */
      digitalWrite(vibPin, HIGH);
      delay(2500);

      digitalWrite(vibPin, LOW);
      delay(1000);

      digitalWrite(vibPin, HIGH);
      delay(2500);

      digitalWrite(vibPin, LOW);
      Serial.println("C");
      break;

    case 'd':
      digitalWrite(palPin, HIGH);
      delay(500);
      digitalWrite(palPin, LOW);
      delay(500);
      digitalWrite(palPin, HIGH);
      delay(500);
      digitalWrite(palPin, LOW);
      delay(500);
      Serial.println("D");
    }
  }
  delay(1000);
}