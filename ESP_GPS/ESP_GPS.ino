#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <Adafruit_GPS.h>

#define GPSSerial Serial1
#define RADIO 6371
#define TO_RAD (3.1415926536 / 180)

// Distancia a calcular
double distancia, plaza_lat = 10.5060384, plaza_lon = -66.9146525, limite = 100.0;
char buff_output[100];
// Connect to the GPS on the hardware port
Adafruit_GPS GPS(&GPSSerial);

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
#define GPSECHO false

uint32_t timer = millis();

void setup()
{
  Serial.begin(115200);
  
  char buff_test[100];
  double d = dist(36.12, -86.67, 33.94, -118.4); // should return aprox 2887 Km

  sprintf(buff_test, "Distancia obtenida de prueba: %5.3f", d);
  Serial.println(buff_test);

  Serial.println("Adafruit GPS library basic parsing test!");

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  // Turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  delay(1000);

  // Ask for firmware version
  GPSSerial.println(PMTK_Q_RELEASE);
}

void loop() // run over and over again
{
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived())
  {
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return;                       // we can fail to parse a sentence in which case we should just wait for another
  }

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000)
  {
    timer = millis(); // reset the timer

    if (GPS.fix)
    {
      distancia = dist(GPS.latitude, GPS.longitude, plaza_lat, plaza_lon) * 1000;

      if (distancia <= limite)
      {
        sprintf(buff_output, "Usted se encuentra en el radio de búsqueda por %5.3f m.", distancia);
        Serial.println(buff_output);
      }
    }
  }
}

double dist(double lat1, double lon1, double lat2, double lon2)
{
  double dx, dy, dz;
  lon1 -= lon2;
  lon1 *= TO_RAD, lat1 *= TO_RAD, lat2 *= TO_RAD;

  dz = sin(lat1) - sin(lat2);
  dx = cos(lon1) * cos(lat1) - cos(lat2);
  dy = sin(lon1) * cos(lat1);
  return asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * RADIO;
}
