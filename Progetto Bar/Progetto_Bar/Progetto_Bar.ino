#include <Arduino_SensorKit.h>
#include <Arduino_SensorKit_BMP280.h>
#include <Arduino_SensorKit_LIS3DHTR.h>


#include <LiquidCrystal.h>
	
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int potPin = A0;  // Posizione del potenziometro che gestisce il Menu
int menuOption = 0;
const int numOptions = 6; // Numero di opzioni nel menu (6 opzioni)

//Per i senrori
float pressure;

int pulsante = 13;
bool statoLed = false;

//I sensori vanno fatti partire solo quando vengono chiamati nello switch

void setup() {
  lcd.begin(16, 2);
  pinMode(pulsante, INPUT);
}

void loop() {
  int sensorValue = analogRead(potPin);
  menuOption = map(sensorValue, 0, 1023, 0, numOptions - 1);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  
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
  
  // Gestione del pulsante per la selezione delle opzioni
  if (digitalRead(pulsante) == HIGH) {
    // Visualizza il messaggio del sensore selezionato
    lcd.setCursor(0, 0);
    lcd.clear();
    switch(menuOption) {
      case 0:
        Pressure.begin();
        lcd.print("Temp: ");
        lcd.print(Pressure.readTemperature());  // The unit for Celsius because original Arduino don't support special symbols
        lcd.print(" C");
        delay(3000);
        lcd.clear();
        lcd.print("Pressure: ");
        lcd.print(Pressure.readPressure());
        lcd.print(" Pa");
        delay(3000);
        lcd.clear();
        lcd.print("Altitude: ");
        lcd.print(Pressure.readAltitude());
        lcd.print(" m");
        delay(2500);
        lcd.clear();
        break;
      case 1:
        Accelerometer.begin();
        lcd.print("x:"); 
        lcd.print(Accelerometer.readX());
        delay(2000);
        lcd.clear();
        lcd.print("y:"); 
        lcd.print(Accelerometer.readY());
        delay(2000);
        lcd.clear();        
        lcd.print("z:"); 
        lcd.println(Accelerometer.readZ());
        delay(2000);
        lcd.clear();
        break;


      case 2:
        lcd.print("Light");
        break;
      case 3:
        lcd.print("Sound");
        break;
      case 4:
        lcd.print("Temperature");
        break;
      case 5:
        lcd.print("Humidity");
         break;
    }
    
    delay(2000); // Ritardo per la visualizzazione del messaggio
    
    // Ripristina il display principale
    lcd.clear();
    lcd.setCursor(0, 0);
  }
  

  delay(500); // Aggiungi un ritardo per una visualizzazione più stabile
}