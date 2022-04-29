// For Linux: sudo chmod a+rw /dev/ttyACM0

// Bibliotheken
#include <SPI.h>
#include <SD.h>
#include <Seeed_BME280.h> // Ermöglicht die Kommunikation mit dem BME
#include <Wire.h>  // Ermöglicht mit Geräten zu kommunizieren, welche das I²C Protokoll verwenden

BME280 bme280; // Instanziert den BME280

#define SYNC_INTERVAL 10000 // Zeit in Millisekunden zwischen den Aufrufen von flush(), also dem speichern auf der SD Karte
uint32_t syncTime = 0; // Zeit der letzten Synchronisierung

#define ECHO_TO_SERIAL   1 // Bestimmt, ob die Daten auch auf dem seriellen Monitor ausgegeben werden

// Die digitalen Ports, an denen die LEDs für die Satusanzeige angeschlossen sind
#define redLED 7
#define yellowLED 6
#define greenLED 5

// Der digitale Port, an dem der Taster angeschlossen ist
#define onOffButton A2

// Der analoge Port, an dem der Hallsensor angeschlossen ist
#define hallSensor A3

// Der analoge Port, an dem der UV-Sensor angeschlossen ist
#define UVSensor A0

// Kontrolliert wann die Daten gesammelt werden -> kann über den Knopf an onOffButton kontrolliert werden
int _running = 0;

// Speichert wann der Hall-Sensor des Anemometers das letzte Mal ausgelöst wurde
int lastRotation = 0;

// Speichert wie lange das Anemometer für die letzte Umdrehug gebraucht hat
int rotationTime = 0;

// Zeitpunkt, zu dem der Start-Konopf gedrückt wurde -> läuft nach ca. 50 Tagen über
unsigned long runningSince = 0; 

// Port des SD-Karten-Lesemoduls
const int chipSelect = 10;

File logfile; // Instanziert das Log-File

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
  int _now = millis();
  rotationTime = _now - lastRotation;
  lastRotation = _now;
}

void setup(void)
{
  // Kontrolliert ob ein Fehler innerhalb des setup Teils aufgetreten ist
  bool errorOccuredInSetup = false;

  // Attached die Funktion hallSensorTriggered, zu einem Ändern der Voltage am Port hallSensor von HIGH zu LOW
  attachInterrupt(digitalPinToInterrupt(hallSensor), hallSensorTriggered, FALLING);
  
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

  // Die gelbe LED wird für den restlichen setup-Teil angeschaltet
  digitalWrite(yellowLED, HIGH); 

  delay(1000); // Warte kurz

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

  // Falls keine Log-Datei erstellt wurde (weil z.B. alle Namen belegt waren), wird eine Fehlermeldung ausgegeben
  if (! logfile) {
    error("Could not create a logfile");
    errorOccuredInSetup = true;
  } else {
    // Andernfalls wird der Name der erstellten Log-Datei ausgegeben
    Serial.print("Logging to: ");
    Serial.println(filename);
  }

  // Wenn keine Daten vom BME abgefragt werden können ...
  if (!bme280.init()) {
    error("Could not read data from BME"); // ... dann soll eine Fehlermeldung ausgegeben werden.
  }

  // Setzt die Spaltennamen für die CSV-Log-Datei
  logfile.println("timestamp,temperature,pressure,humidity,altitude,hallsensor,uv"); 
  #if ECHO_TO_SERIAL
    // Gibt eine Warnung aus
    Serial.println("Note: The timestamp starts with the execution of the programm and will overflow after approx. 50 days.");
    // Setzt die Spaltennamen für die Ausgabe
    Serial.println("timestamp,temperature,pressure,humidity,altitude,hallsensor,uv"); 
  #endif //ECHO_TO_SERIAL

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
    digitalWrite(greenLED, LOW); // Schaltet die grüne LED aus
    digitalWrite(yellowLED, HIGH); // Schaltet die gelbe LED an
    digitalWrite(redLED, HIGH); // Schaltet die rote LED an
  }
  
  if (_running == 1) {    
    unsigned long _timestamp = millis() - runningSince; // Setzt now auf die aktuelle Zeit minus der Startzeit
    // Schreibt die Zeit seit Start des Programmes (in Millisekunden) in die Log-Datei
    logfile.print(_timestamp);
    #if ECHO_TO_SERIAL
      // Gibt die Zeit seit Start des Programmes (in Millisekunden) aus
      Serial.print(_timestamp);
    #endif //ECHO_TO_SERIAL

    // Liest die Sensorwerte vom BME aus und schreibt sie in Vaiablen
    double temp = bme280.getTemperature(); // Temperatur in Grad Celsius
    double pres = bme280.getPressure(); // Druck in Pascal
    int hum = bme280.getHumidity(); // Luftfeuchtigkeit
    double alt = bme280.calcAltitude(pres); // Berechnete Höhe

    // Liest die Sensorwerte des Hall-Sensors aus
    int hall = analogRead(hallSensor);

    // Liest die Sensorwerte des UV-Sensors aus
    float analogSignal = analogRead(UVSensor);
    float voltage = analogSignal/1023*5;
    float uvIndex = voltage / 0.1;

    // Schreibt die Werte in die Log-Datei
    logfile.print(", ");
    logfile.print(temp);
    logfile.print(", ");
    logfile.print(pres / 100000);  // Umrechnung in Bar
    logfile.print(", ");
    logfile.print(hum);
    logfile.print(", ");
    logfile.print(alt);
    logfile.print(", ");
    logfile.print(hall);
    logfile.print(", ");
    logfile.print(uvIndex);
    #if ECHO_TO_SERIAL
      Serial.print(", ");
      Serial.print(temp);
      Serial.print("C");
      Serial.print(", ");
      Serial.print(pres / 100000);  // Umrechnung in Bar
      Serial.print("Bar");
      Serial.print(", ");
      Serial.print(hum);
      Serial.print(", ");
      Serial.print(alt);
      Serial.print("m");
      Serial.print(", ");
      Serial.print(hall);
      Serial.print(", ");
      Serial.print(uvIndex);
    #endif //ECHO_TO_SERIAL

    logfile.println(); // Beginnt eine neue Zeile in der Log-Datei 
    #if ECHO_TO_SERIAL
      Serial.println(); // Beginnt eine neue Zeile im Seriellen Monitor
    #endif // ECHO_TO_SERIAL
  
    // Stellt sicher, dass nicht zu oft auf die SD-Karte zugegriffen wird
    if ((millis() - syncTime) < SYNC_INTERVAL) return;
    syncTime = millis();
  
    // Lässt die gelbe LED blinken, um zu signalisieren, dass synchronisiert wird
    digitalWrite(yellowLED, HIGH);
    logfile.flush();
    digitalWrite(yellowLED, LOW);
  }
}
