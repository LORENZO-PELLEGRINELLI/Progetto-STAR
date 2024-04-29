#include <Arduino_SensorKit_LIS3DHTR.h>

#define Environment Environment_I2C

// Definizione del pin del buzzer
#define BUZZER 5

// Inclusione della libreria LiquidCrystal
#include <LiquidCrystal.h>
	
// Definizione delle connessioni dei pin per il display LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Definizione del pin per il potenziometro
const int potPin = A0;

// Variabile per tenere traccia dell'opzione del menu
int menuOption = 0;
const int numOptions = 6;

// Definizione del pin per il pulsante
int pulsante = 13;

// Definizione del pin per il sensore di luce
int light_sensor = A3;

// Definizione del pin per il sensore del suono
int sound_sensor = A2;

void setup() {
  // Inizializzazione del display LCD
  lcd.begin(16, 2);
  
  // Configurazione del pin del pulsante come input
  pinMode(pulsante, INPUT);
  
  // Configurazione del pin LED come output
  pinMode(LED, OUTPUT);
  
  // Configurazione del pin del buzzer come output
  pinMode(BUZZER, OUTPUT);
  
  // Inizializzazione della comunicazione seriale a 9600 baud
  Serial.begin(9600);
}

void loop() {
  // Lettura del valore del potenziometro per selezionare l'opzione del menu
  int sensorValue = analogRead(potPin);
  menuOption = map(sensorValue, 0, 1023, 0, numOptions - 1);
  
  // Pulizia del display LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  
  // Visualizzazione delle opzioni del menu
  switch(menuOption) {
    case 0:
      lcd.print("1 - Air");
      break;
    case 1:
      lcd.print("2 - Acceleration");
      break;
    case 2:
      lcd.print("3 - Light");
      break;
    case 3:
      lcd.print("4 - Sound");
      break;
    case 4:
      lcd.print("5 - Temperature");
      break;
    case 5:
      lcd.print("6 - Humidity");
      break;
  }

  // Gestione selezione opzioni
  if(digitalRead(pulsante) == HIGH) {
    lcd.setCursor(0, 0);
    lcd.clear();

    switch(menuOption) {
      case 0:
        Pressure.begin();
        // Invia i dati del sensore di pressione attraverso la porta seriale
        Serial.print("Pressure: ");
        Serial.print(Pressure.readPressure());
        Serial.println(" Pa");
        break;
      case 1:
        Accelerometer.begin();
        // Invia i dati dell'accelerometro attraverso la porta seriale
        Serial.print("Acceleration - X: ");
        Serial.print(Accelerometer.readX());
        Serial.print(", Y: ");
        Serial.print(Accelerometer.readY());
        Serial.print(", Z: ");
        Serial.println(Accelerometer.readZ());
        break;
      case 2:
        // Leggi il valore del sensore di luce
        int raw_light = analogRead(light_sensor);
        int light = map(raw_light, 0, 1023, 0, 100);
        // Invia i dati del sensore di luce attraverso la porta seriale
        Serial.print("Light level: ");
        Serial.println(light);
        break;
      case 3:
        // Leggi il valore del sensore del suono
        int soundValue = 0;
        for (int i = 0; i < 32; i++) {
          soundValue += analogRead(sound_sensor);
        }
        soundValue >>= 5;
        // Invia i dati del sensore del suono attraverso la porta seriale
        Serial.print("Sound level: ");
        Serial.println(soundValue);
        break;
    }
  }
  
  // Aggiungi un ritardo per una visualizzazione più stabile
  delay(500);
}

