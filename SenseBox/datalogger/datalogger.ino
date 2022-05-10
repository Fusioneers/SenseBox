// For Linux: sudo chmod a+rw /dev/ttyACM0

// Bibliotheken
#include <SPI.h>
#include <SD.h>
#include <Seeed_BME280.h> // Ermöglicht die Kommunikation mit dem BME
#include <Wire.h>  // Ermöglicht mit Geräten zu kommunizieren, welche das I²C Protokoll verwenden

BME280 bme280; // Instanziert den BME280

#define SYNC_INTERVAL 10000 // Zeit in Millisekunden zwischen den Aufrufen von flush(), also dem speichern auf der SD Karte
uint32_t syncTime = 0; // Zeit der letzten Synchronisierung

#define ECHO_TO_SERIAL false // Bestimmt, ob die Daten auch auf dem seriellen Monitor ausgegeben werden

// Die digitalen Ports, an denen die LEDs für die Satusanzeige angeschlossen sind
#define redLED 7
#define yellowLED 6
#define greenLED 5

# define onlyMeasureHallSesnor false

// Der digitale Port, an dem der Taster angeschlossen ist
#define onOffButton A2

// Der analoge Port, an dem der Hallsensor angeschlossen ist
#define hallSensor 2

// Der analoge Port, an dem der UV-Sensor angeschlossen ist
#define UVSensor A0

// Kontrolliert wann die Daten gesammelt werden -> kann über den Knopf an onOffButton kontrolliert werden
int _running = 0;

// Zeitpunkt, zu dem der Start-Konopf gedrückt wurde -> läuft nach ca. 50 Tagen über
unsigned long runningSince = 0; 

// Port des SD-Karten-Lesemoduls
#define chipSelect 10

// Speichert die letzten 10 Zeiten, zu denen der Hall-Sensor getriggert wurde
unsigned long lastLallSesnorTriggerTime = 0;

File logfile; // Instanziert das allgemeine Log-File
File hall_trigger_logfile; // Instanziert das Log-File für die Auslösungen des Hall-Sensors

// Falls ein Fehler auftritt, wird er von dieser Funktion gehandhabt
void error(String message) {
  digitalWrite(greenLED, LOW); // Schaltet die grüne LED aus
  digitalWrite(yellowLED, LOW); // Schaltet die gelbe LED aus
  digitalWrite(redLED, HIGH); // Schaltet die rote LED an
  #if ECHO_TO_SERIAL
    Serial.println(message); // Gibt den Fehler aus
  #endif //ECHO_TO_SERIAL
}


void hallSensorTriggered() {
  if (_running) {
    lastLallSesnorTriggerTime = millis();
  }
}

void setup(void)
{
  // Kontrolliert ob ein Fehler innerhalb des setup Teils aufgetreten ist
  bool errorOccuredInSetup = false;

  // Initialisiert den seriellen Monitor
  Serial.begin(9600);
  
  // Setzt den Pin-Mode der Status-LEDs auf OUTPUT
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  // Setzt den Pin-Mode des An- Ausschalters auf INPUT
  pinMode(onOffButton, INPUT);

  // Setzt den Pin-Mode des Hallsesnors auf INPUT
  pinMode(hallSensor, INPUT);
  
  // Attached die Funktion hallSensorTriggered, zu einem Ändern der Voltage am Port hallSensor von HIGH zu LOW
  attachInterrupt(digitalPinToInterrupt(hallSensor), hallSensorTriggered, FALLING);

  // Die gelbe LED wird für den restlichen setup-Teil angeschaltet
  digitalWrite(yellowLED, HIGH); 

  Serial.println("Initializing SD card...");
  // Setzt den SD-Karten Pin vorsichtshalber bereits auf OUTPUT
  pinMode(10, OUTPUT);

  // Initialisiert die SD-Karte, sofern vorhanden
  if (!SD.begin(chipSelect)) {
    error("Card failed, or not present");
    errorOccuredInSetup = true;
  }
  Serial.println("Card initialized.");

  // Erstellt ein neues Log-File mit dem Namen LOGGER + zweistellige noch nicht verwendete Zahl
  char filename[] = "LOGGER00.CSV";
  // Loopt duch alle möglichen Namen
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = i / 10 + '0';
    filename[7] = i % 10 + '0';
    if (! SD.exists(filename)) {
      // Falls der Name noch nicht belegt ist, wird das Log-File erstellt und der Loop unterbrochen
      logfile = SD.open(filename, FILE_WRITE);
      break;
    }
  }

  // Erstellt ein neues Log-File mit dem Namen HALLOG00 + zweistellige noch nicht verwendete Zahl
  char hall_trigger_filename[] = "HALLOG00.CSV";
  // Loopt duch alle möglichen Namen
  for (uint8_t i = 0; i < 100; i++) {
    hall_trigger_filename[6] = i / 10 + '0';
    hall_trigger_filename[7] = i % 10 + '0';
    if (! SD.exists(hall_trigger_filename)) {
      // Falls der Name noch nicht belegt ist, wird das Log-File erstellt und der Loop unterbrochen
      hall_trigger_logfile = SD.open(hall_trigger_filename, FILE_WRITE);
      break;
    }
  }

  // Falls keine Log-Datei erstellt wurde (weil z.B. alle Namen belegt waren), wird eine Fehlermeldung ausgegeben
  if (!logfile) {
    error("Could not create a logfile");
    errorOccuredInSetup = true;
  } else if (!hall_trigger_logfile) {
    error("Could not create a logfile for the hall sensor triggers");
    errorOccuredInSetup = true;
  } else {
    // Andernfalls wird der Name der erstellten Log-Datei ausgegeben
    Serial.print("Logging to: ");
    Serial.print(filename);
    Serial.print(" and ");
    Serial.println(hall_trigger_filename);
  }

  // Wenn keine Daten vom BME abgefragt werden können ...
  if (!bme280.init()) {
    error("Could not read data from BME"); // ... dann soll eine Fehlermeldung ausgegeben werden.
  }

  // Setzt die Spaltennamen für die CSV-Log-Dateien
  logfile.println("timestamp,temperature,pressure,humidity,altitude,uv");
  hall_trigger_logfile.println("timestamp");
  #if ECHO_TO_SERIAL
    // Gibt eine Warnung aus
    Serial.println("Note: The timestamp starts with the execution of the programm and will overflow after approx. 50 days.");
    // Setzt die Spaltennamen für die Ausgabe
    Serial.println("timestamp,temperature,pressure,humidity,altitude,uv"); 
  #endif //ECHO_TO_SERIAL

  delay(5000);

    // Falls noch keine Fehler aufgetreten ist, wird auf das Drücken des Start-Knopfs gewartet
  if (errorOccuredInSetup == false) {
    while (analogRead(onOffButton) < 1023) {
      delay(500);
    } 
  } else {
    while (1==1) { // Andernfalls wird eine Warnung ausgegeben und gewartet
      Serial.println("An error occured, see above");
      delay(900000); 
    }
  }

  // Schaltet die grüne LED an
  digitalWrite(greenLED, HIGH);

  delay(3000); // Wartet kurz

  // Die gelbe LED wird wieder ausgeschaltet
  digitalWrite(yellowLED, LOW);

  // Setzt _running auf wahr
  _running = 1;
  // Die Startzeit wird gespeichert
  runningSince = millis();
  int lastRotation = millis();
}

void loop(void)
{  
  // Überprüft, ob der An-/Aus-Knopf gedrückt wird, falls ja, wird das Data-Logging beendet
  if (analogRead(onOffButton) >= 1023) {
    _running = 0;
    // Lässt die gelbe LED blinken, um zu signalisieren, dass synchronisiert wird
    digitalWrite(yellowLED, HIGH);
    logfile.flush();
    hall_trigger_logfile.flush();
    digitalWrite(yellowLED, LOW);
    
    digitalWrite(greenLED, LOW); // Schaltet die grüne LED aus
    digitalWrite(yellowLED, HIGH); // Schaltet die gelbe LED an
    digitalWrite(redLED, HIGH); // Schaltet die rote LED an
  }
  
  if (_running == 1) {
    if (lastLallSesnorTriggerTime != 0) {

      #if ECHO_TO_SERIAL
        Serial.println("Hall sensor triggered!");
      #endif //ECHO_TO_SERIAL
      
      
      hall_trigger_logfile.println(lastLallSesnorTriggerTime);
      lastLallSesnorTriggerTime = 0;
    }
    
    if (!onlyMeasureHallSesnor) {
      unsigned long _timestamp = millis() - runningSince; // Setzt now auf die aktuelle Zeit minus der Startzeit
      // Schreibt die Zeit seit Start des Programmes (in Millisekunden) in die Log-Datei
      logfile.print(_timestamp);
      #if ECHO_TO_SERIAL
        // Gibt die Zeit seit Start des Programmes (in Millisekunden) aus
        Serial.print(_timestamp);
      #endif //ECHO_TO_SERIAL
  
      // Liest die Sensorwerte vom BME aus und schreibt sie in Vaiablen
      // double temp = ; // Temperatur in Grad Celsius
      // int hum = ; // Luftfeuchtigkeit
      // double alt = ; // Berechnete Höhe
  
      // Liest die Sensorwerte des UV-Sensors aus
      float analogSignal = analogRead(UVSensor);
      float voltage = analogSignal/1023*5;
      float uvIndex = voltage / 0.1;
  
      // Schreibt die Werte in die Log-Datei
      logfile.print(", ");
      logfile.print(bme280.getTemperature());
      logfile.print(", ");
      logfile.print(bme280.getPressure());
      logfile.print(", ");
      logfile.print(bme280.getHumidity());
      logfile.print(", ");
      logfile.print(bme280.calcAltitude(bme280.getPressure()));
      logfile.print(", ");
      logfile.print(uvIndex);
      #if ECHO_TO_SERIAL
        Serial.print(", ");
        Serial.print(bme280.getTemperature());
        Serial.print(" °C");
        Serial.print(", ");
        Serial.print(bme280.getPressure());
        Serial.print(" Pascal");
        Serial.print(", ");
        Serial.print(bme280.getHumidity());
        Serial.print(", ");
        Serial.print(bme280.calcAltitude(bme280.getPressure()));
        Serial.print(" m");
        Serial.print(", ");
        Serial.print(uvIndex);
      #endif //ECHO_TO_SERIAL
  
      logfile.println(); // Beginnt eine neue Zeile in der Log-Datei 
      #if ECHO_TO_SERIAL
        Serial.println(); // Beginnt eine neue Zeile im Seriellen Monitor
      #endif // ECHO_TO_SERIAL   
    }
  
    // Stellt sicher, dass nicht zu oft auf die SD-Karte zugegriffen wird
    if ((millis() - syncTime) < SYNC_INTERVAL) return;
    syncTime = millis();
  
    // Lässt die gelbe LED blinken, um zu signalisieren, dass synchronisiert wird
    digitalWrite(yellowLED, HIGH);
    logfile.flush();
    hall_trigger_logfile.flush();
    digitalWrite(yellowLED, LOW);
  }
}
