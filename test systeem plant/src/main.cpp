// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLQf1ywiaq"
#define BLYNK_DEVICE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "zycYQ3ZSEkmhrzC8rgpiOYlLXJttoZKh"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Simons1";
char pass[] = "Simons2804";

BlynkTimer timer;

#include "switchKaKu.h"
#define TRANSMITTERID1 29012000 //Dit ID nog controleren met wat is geprogrammeerd
#define rfPin 25
#define ledPin 2

const int ldrPin = 39;

int pumpPin = 33;
int moistSensPin = 36;
int moistValue = 0;

int lightInitial;
int lightValue;

BLYNK_WRITE(V0)

{
  if (param.asInt() == 1)
  {
    digitalWrite(ledPin, HIGH);
    {
      // led aan
    }
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
}

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, moistValue);
  Blynk.virtualWrite(V3, lightValue);
}

//setup code only runs once at startup
void setup()
{

  Serial.begin(9600); //start a serial connection with a baud rate of 9600

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L, myTimerEvent);
  // Serial.println(F("DHT11"));

  //dht.begin();

  pinMode(ldrPin, INPUT); //define ldrPin as INPUT since we want to read it
  pinMode(ledPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  lightInitial = analogRead(ldrPin);

  // switchKaku(rfPin, TRANSMITTERID1, 1, 1, true, 3);
}

//loop runs all the time over and over again

void loop()
{

  Blynk.run();
  timer.run();
  // delay(100);
  //switchKaku(rfPin, TRANSMITTERID1, 1, 1, true, 3);

  moistValue = analogRead(moistSensPin);
  Serial.println(moistValue);

  if (moistValue <= 1550) //waarde moet nog precies gedefineerd worden
  {
    Serial.println("Pump is now on");
    digitalWrite(pumpPin, HIGH);
    delay(500);
  }

  else
  {
    Serial.println("Pump is now off");
    digitalWrite(pumpPin, LOW);
    delay(500); //delay kan eventueel worden weg gelaten
  }

  //Ledlamp gaat aan onder een bepaalde waarde

  lightValue = analogRead(ldrPin);
  Serial.println(lightValue);
  if (lightValue <= 2350)
  {
    digitalWrite(ledPin, HIGH);                       //turn on light
    switchKaku(rfPin, TRANSMITTERID1, 1, 1, true, 3); //turn on klikaanklikuit
    Serial.println("klikaan");
  }
  else
  {
    digitalWrite(ledPin, LOW);                         //turn off light
    switchKaku(rfPin, TRANSMITTERID1, 1, 1, false, 3); //turn off klikaanklikuit
    Serial.println("klikuit");
  }

  delay(200); //wait 200ms
}