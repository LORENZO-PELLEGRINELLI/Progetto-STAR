	
#include "Arduino_SensorKit.h"
#include <Arduino_SensorKit_BMP280.h>
#include <Arduino_SensorKit_LIS3DHTR.h>

#define Environment Environment_I2C


//Buzzer
#define BUZZER 5

#include <LiquidCrystal.h>
	
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int potPin = A0;  // Posizione del potenziometro che gestisce il Menu
int menuOption = 0;
const int numOptions = 6; // Numero di opzioni nel menu (6 opzioni)

//Per i senrori
float pressure;

int pulsante = 13;
bool statoLed = false;

//Led che si illumina per le misurazioni
#define LED 6

//Led che si illumina quando non c'è la misurazione
#define LEDStan 10

//Per il sensore della luce
int light_sensor = A3; 

//Sensore del suono
int sound_sensor = A2; //assign to pin A2

//I sensori vanno fatti partire solo quando vengono chiamati nello switch
void setup() {
  lcd.begin(16, 2);
  pinMode(pulsante, INPUT);
  pinMode(LED,OUTPUT);    //Sets the pinMode to Output
  pinMode(LEDStan, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(potPin);
  menuOption = map(sensorValue, 0, 1023, 0, numOptions - 1);

  
  lcd.clear();
  lcd.setCursor(0, 0);

  digitalWrite(LEDStan, HIGH);
  
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

  //Gestione selezione opzioni

  if(digitalRead(pulsante) == HIGH){
    lcd.setCursor(0, 0);
    lcd.clear();

    switch(menuOption){
      case 0:{
          Pressure.begin();
          digitalWrite(LED, HIGH);  //Led si attiva per la misurazione
          digitalWrite(LEDStan, LOW);
          tone(BUZZER, 300); //Set the voltage to high and makes a noise
          lcd.print("Temp: ");
          lcd.print(Pressure.readTemperature());  // The unit for Celsius because original Arduino don't support special symbols

          Serial.print("Temperatura: ");  //Pressione comunicata al Rasperry
          Serial.println(Pressure.readTemperature()); 
          Serial.print("C");

          lcd.print(" C");
          delay(3000);
          lcd.clear();
          lcd.print("Pressure: ");
          lcd.print(Pressure.readPressure());

          Serial.print("Pressure:");
          Serial.println(Pressure.readPressure());
          Serial.print("Pa");

          lcd.print(" Pa");
          delay(3000);
          lcd.clear();
          lcd.print("Altitude:");
          lcd.print(Pressure.readAltitude());

          Serial.print("Altitudine:");  
          Serial.println(Pressure.readAltitude());  //Altitudine comunicata al Rasperry
          Serial.print("m");

          lcd.print(" m");   	
          delay(2500);
          digitalWrite(LED, LOW);  //led si spegne appena finita la misurazione
          noTone(BUZZER);//Sets the voltage to low and makes no noise
          lcd.clear();
          break;
      }

      case 1:{
          Accelerometer.begin();
          digitalWrite(LED, HIGH);  //Led si attiva per la misurazione
          digitalWrite(LEDStan, LOW);
          tone(BUZZER, 300); //Set the voltage to high and makes a noise
          lcd.print("x:"); 
          lcd.print(Accelerometer.readX());
          
          Serial.print("X:");  
          Serial.println(Accelerometer.readX());  

          delay(2000);
          lcd.clear();
          lcd.print("y:"); 
          lcd.print(Accelerometer.readY());

          Serial.print("Y:");  
          Serial.println(Accelerometer.readY()); 

          delay(2000);
          lcd.clear();        
          lcd.print("z:"); 
          lcd.println(Accelerometer.readZ());

          Serial.print("Z:");  
          Serial.println(Accelerometer.readZ()); 

          delay(2000);
          digitalWrite(LED, LOW);  //led si spegne appena finita la misurazione
          noTone(BUZZER);//Sets the voltage to low and makes no noise
          lcd.clear();
          break;

      }

      case 2:{
        digitalWrite(LED, HIGH);  //Led si attiva per la misurazione
        digitalWrite(LEDStan, LOW);
        tone(BUZZER, 300); //Set the voltage to high and makes a noise
        int raw_light = analogRead(light_sensor); // read the raw value from light_sensor pin (A3)
        int light = map(raw_light, 0, 1023, 0, 100); // map the value from 0, 1023 to 0, 100

        lcd.print("Light level: "); 
        lcd.println(light); // print the light value in Serial Monitor

        Serial.print("Light level:");  
        Serial.println(light); 

        delay(2000); // add a delay to only read and print every 2 seconds

        digitalWrite(LED, LOW);  //led si spegne appena finita la misurazione
        noTone(BUZZER);//Sets the voltage to low and makes no noise
        lcd.clear();
        break;
      }

      case 3:{
        digitalWrite(LED, HIGH);  //Led si attiva per la misurazione
        digitalWrite(LEDStan, LOW);
        tone(BUZZER, 300); //Set the voltage to high and makes a noise
        int soundValue = 0; //create variable to store many different readings
        for (int i = 0; i < 32; i++) //create a for loop to read 
        { soundValue += analogRead(sound_sensor);  } //read the sound sensor
      
        soundValue >>= 5; //bitshift operation 

        lcd.println(soundValue); //print the value of sound sensor

        Serial.print("Sound value:");  
        Serial.println(soundValue); 

        delay(3000);
        digitalWrite(LED, LOW);  //led si spegne appena finita la misurazione
        noTone(BUZZER);//Sets the voltage to low and makes no noise
        lcd.clear();
        break;
      }

     
    }
  }
  
  

  delay(500); // Aggiungi un ritardo per una visualizzazione più stabile
}
