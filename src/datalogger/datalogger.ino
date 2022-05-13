// For Linux: sudo chmod a+rw /dev/ttyACM0

// Bibliotheken einbinden
#include <SPI.h>
#include <SD.h>
#include <Seeed_BME280.h> // Ermöglicht die Kommunikation mit dem BME
#include <Wire.h>  // Ermöglicht mit Geräten zu kommunizieren, welche das I²C Protokoll verwenden

// Instanziert den BME280
BME280 bme280;

// Zeit in Millisekunden zwischen den Aufrufen von flush(), also dem speichern auf der SD Karte
#define SYNC_INTERVAL 10000

// Zeit der letzten Synchronisierung
uint32_t syncTime = 0;

// Bestimmt, ob die Daten auch auf dem seriellen Monitor ausgegeben werden
#define ECHO_TO_SERIAL false

// Die digitalen Ports, an denen die LEDs für die Satusanzeige angeschlossen sind
#define redLED 7
#define yellowLED 6
#define greenLED 5

// Bestimmt, ob nur der Hall Sensor gemessen wird
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
  // Gibt (falls ECHO_TO_SERIAL wahr ist) den Fehler aus
  #if ECHO_TO_SERIAL
    Serial.println(message);
  #endif //ECHO_TO_SERIAL
}

// Diese Funktion wird immer aufgrufen, wenn die Ausgabe des Hall Sesnor von HIGH zu LOW wechselt (siehe setup)
void hallSensorTriggered() {
  // Falls das Programm am laufen ist
  if (_running) {
    // Setze die Zeit des letzten Aufrufs, auf die aktuelle Zeit
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

  // Falls eine der beiden Log-Dateien nicht erstellt wurde (weil z.B. alle Namen belegt waren), ... 
  if (!logfile) {
    error("Could not create a logfile"); // ... wird eine Fehlermeldung ausgegeben
    errorOccuredInSetup = true;
  } else if (!hall_trigger_logfile) {
    error("Could not create a logfile for the hall sensor triggers"); // ... wird eine Fehlermeldung ausgegeben
    errorOccuredInSetup = true;
  } else {
    // ... andernfalls wird der Name der erstellten Log-Datein ausgegeben
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

  delay(5000); // Wartet kurz

    // Falls noch keine Fehler aufgetreten ist, wird auf das Drücken des Start-Knopfs gewartet
  if (errorOccuredInSetup == false) {
    while (analogRead(onOffButton) < 1023) {
      delay(500);
    } 
  } else {
    while (1==1) { // ... andernfalls wird ein Fehler ausgegeben und lange gewartet
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
  _running = true;
  
  // Die Startzeit wird gespeichert
  runningSince = millis();
}

void loop(void)
{  
  // Falls der An-/Aus-Knopf gedrückt wird
  if (analogRead(onOffButton) >= 1023) {
    _running = false; // _running wird auf false gesetzt
    
    // Synchronisiert die gesammelten Daten, während die gelbe LED einmal blinkt
    digitalWrite(yellowLED, HIGH);
    logfile.flush();
    hall_trigger_logfile.flush();
    digitalWrite(yellowLED, LOW);
    
    digitalWrite(greenLED, LOW); // Schaltet die grüne LED aus
    digitalWrite(yellowLED, HIGH); // Schaltet die gelbe LED an
    digitalWrite(redLED, HIGH); // Schaltet die rote LED an
  }

  // Falls _running wahr ist
  if (_running == true) {

    // Falls lastLallSesnorTriggerTime nicht 0 ist
    if (lastLallSesnorTriggerTime != 0) {

      // Gibt (falls ECHO_TO_SERIAL wahr ist) "Hall sensor triggered!" auf dem seriellen Monitor aus
      #if ECHO_TO_SERIAL
        Serial.println("Hall sensor triggered!");
      #endif //ECHO_TO_SERIAL

      // Schreibt lastLallSesnorTriggerTime in die Log-Datei
      hall_trigger_logfile.println(lastLallSesnorTriggerTime);

      // Setzt lastLallSesnorTriggerTime wieder auf 0
      lastLallSesnorTriggerTime = 0;
    }

    // Falls nicht nur der Hall Sensor gemessen werden soll ...
    if (!onlyMeasureHallSesnor) {

      // Setzt _timestamp auf die aktuelle Zeit minus der Startzeit
      unsigned long _timestamp = millis() - runningSince;
      
      // Schreibt _timestamp in die Log-Datei
      logfile.print(_timestamp);
      // Gibt (falls ECHO_TO_SERIAL wahr ist) _timestamp am seriellen Monitor aus
      #if ECHO_TO_SERIAL
        Serial.print(_timestamp);
      #endif //ECHO_TO_SERIAL
  
      // Liest die Sensorwerte des UV-Sensors aus und rechnet sie in den UVI um
      float analogSignal = analogRead(UVSensor);
      float voltage = analogSignal/1023*5;
      float uvIndex = voltage / 0.1;
  
      // Schreibt die Sesnorwerte in die Log-Datei
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
      // Gibt (falls ECHO_TO_SERIAL wahr ist) die Sensorwerte am seriellen Monitor aus
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

      // Beginnt eine neue Zeile in der Log-Datei
      logfile.println();
      // Beginnt (falls ECHO_TO_SERIAL wahr ist) eine neue Zeile im Seriellen Monitor
      #if ECHO_TO_SERIAL
        Serial.println();
      #endif // ECHO_TO_SERIAL   
    }
  
    // Falls die letzte Synchronisierung länger als SYNC_INTERVAL Millisecunden her ist
    if ((millis() - syncTime) > SYNC_INTERVAL) {
      // Setzt syncTime auf die aktuelle Zeit
      syncTime = millis();
  
      // Die gesammelten Daten werden synchronisiert, während die gelbe LED einmal blinkt
      digitalWrite(yellowLED, HIGH);
      logfile.flush();
      hall_trigger_logfile.flush();
      digitalWrite(yellowLED, LOW);
    }
  }
}
