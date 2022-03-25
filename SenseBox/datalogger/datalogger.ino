#include <SPI.h>
#include <SD.h>
#include "RTClib.h"
#include <Seeed_BME280.h> // Ermöglicht die Kommunikation mit dem BME
#include <Wire.h>  // Ermöglicht mit Geräten zu kommunizieren, welche das I²C Protokoll verwenden

// For Linux: sudo chmod a+rw /dev/ttyACM0

BME280 bme280; // Instanziert den BME280

// how many milliseconds between grabbing data and logging it. 1000 ms is once a second
#define LOG_INTERVAL  1000 // mills between entries (reduce to take more/faster data)

// how many milliseconds before writing the logged data permanently to disk
// set it to the LOG_INTERVAL to write each time (safest)
// set it to 10*LOG_INTERVAL to write all data every 10 datareads, you  lose up to
// the last 10 reads if power is lost but it uses less power and is much faster!
#define SYNC_INTERVAL 1000 // mills between calls to flush() - to write data to the card
uint32_t syncTime = 0; // time of last sync()

#define ECHO_TO_SERIAL   1 // Bestimmt, ob die Daten auch auf dem seriellen Monitor ausgegeben werden

// Die digitalen Pins, an denen die LEDs für die Satusanzeige angeschlossen sind
#define redLED 7
#define yellowLED 6
#define greenLED 5

// Der digitale Pin, an dem der Taster angeschlossen ist
#define onOffButton A3

RTC_DS1307 RTC; // Instanziert eine Real Time Clock

// Kontrolliert wann die Daten gesammelt werden -> kann über den Knopf an onOffButton kontrolliert werden
int _running = 0;
// for the data logging shield, we use digital pin 10 for the SD cs line
const int chipSelect = 10;

File logfile; // Instanziert das Log-File

// Falls ein Fehler auftritt, wird er von dieser Funktion gehandhabt
void error(String message) {
  digitalWrite(greenLED, LOW); // Schaltet die grüne LED aus
  digitalWrite(redLED, HIGH); // Schaltet die rote LED an
  
  #if ECHO_TO_SERIAL
    Serial.println(message); // Gibt den Fehler aus
  #endif //ECHO_TO_SERIAL
}

void setup(void)
{
  Serial.begin(9600); // Initialisiert den seriellen Monitor

  // Setzt den Pin-Mode der Status-LEDs auf OUTPUT
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  // Setzt den Pin-Mode des An- Ausschalters auf INPUT
  pinMode(onOffButton, INPUT);

  digitalWrite(yellowLED, HIGH); // Die gelbe LED wird für den restlichen setup-Teil angeschaltet

  Serial.println("Initializing SD card...");
  pinMode(10, OUTPUT); // Setzt den SD-Karten Pin vorsichtshalber bereits auf OUTPUT

  // Initialisiert die SD-Karte, sofern vorhanden
  if (!SD.begin(chipSelect)) {
    error("Card failed, or not present");
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
    error("Couldnt create a logfile");
  }

  // Gibt den Namen der erstellten Log-Datei aus
  Serial.print("Logging to: ");
  Serial.println(filename);

  // Verbindet sich mit der Real Time Clock
  Wire.begin();
  if (!RTC.begin()) {
    error("RTC failed");
  }

  // Wenn keine Daten vom BME abgefragt werden können...
  if (!bme280.init()) {
    error("Couldn't read data from BME"); // ...dann soll eine Fehlermeldung ausgegeben werden.
  }

  logfile.println("time,temperature,pressure,humidity,altitude"); // Setzt die Spaltennamen für die CSV-Log-Datei
  #if ECHO_TO_SERIAL
    Serial.println("time,temperature,pressure,humidity,altitude"); // Setzt die Spaltennamen für die Ausgabe
  #endif //ECHO_TO_SERIAL
  
  digitalWrite(yellowLED, LOW); // Die gelbe LED wird wieder ausgeschaltet
  digitalWrite(greenLED, HIGH); // Schaltet die grüne LED an
}

void loop(void)
{
  digitalWrite(yellowLED, LOW); // Schaltet die gelbe LED aus
  if (analogRead(onOffButton) > 1000) {
    _running = !_running;
  }
  if (_running == 1) {
    DateTime now; // Initialisiert die Zeit-variable now

    delay((LOG_INTERVAL - 1) - (millis() % LOG_INTERVAL)); // Wartet kurze Zeit ab
    
    now = RTC.now(); // Setzt now auf die aktuelle Zeit
    // Schreibt die Zeit im yyyy/mm/dd hh:mm:ss Format in die Log-Datei
    logfile.print('"');
    logfile.print(now.year(), DEC);
    logfile.print("/");
    logfile.print(now.month(), DEC);
    logfile.print("/");
    logfile.print(now.day(), DEC);
    logfile.print(" ");
    logfile.print(now.hour(), DEC);
    logfile.print(":");
    logfile.print(now.minute(), DEC);
    logfile.print(":");
    logfile.print(now.second(), DEC);
    logfile.print('"');
    #if ECHO_TO_SERIAL
      // Gibt die Zeit im yyyy/mm/dd hh:mm:ss Format aus
      Serial.print('"');
      Serial.print(now.year(), DEC);
      Serial.print("/");
      Serial.print(now.month(), DEC);
      Serial.print("/");
      Serial.print(now.day(), DEC);
      Serial.print(" ");
      Serial.print(now.hour(), DEC);
      Serial.print(":");
      Serial.print(now.minute(), DEC);
      Serial.print(":");
      Serial.print(now.second(), DEC);
      Serial.print('"');
    #endif //ECHO_TO_SERIAL
  
    // Liest die Sensorwerte vom BME aus und schreibt sie in Vaiablen
    double temp = bme280.getTemperature();
    double pres = bme280.getPressure(); // Druck in Pascal
    double hum = bme280.getHumidity();
    double alt = bme280.calcAltitude(pres);
  
    // Schreibt die Werte in die Log-Datei
    logfile.print(", ");
    logfile.print(temp);
    logfile.print(", ");
    logfile.print(pres / 100000);  // Umrechnung in Bar
    logfile.print(", ");
    logfile.print(hum);
    logfile.print(", ");
    logfile.print(alt);
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
  } else {
    digitalWrite(yellowLED, HIGH); // Schaltet die gelbe LED an
  }
  delay(500);
}
