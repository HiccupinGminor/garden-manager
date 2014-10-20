/*************************************************** 
  This is an example for the Adafruit CC3000 Wifi Breakout & Shield

  Designed specifically to work with the Adafruit WiFi products:
  ----> https://www.adafruit.com/products/1469

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
 
 /*
This example does a test of the TCP client capability:
  * Initialization
  * Optional: SSID scan
  * AP connection
  * DHCP printout
  * DNS lookup
  * Optional: Ping
  * Connect to website and print out webpage contents
  * Disconnect
SmartConfig is still beta and kind of works but is not fully vetted!
It might not work on all networks!
*/
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"

// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIVIDER); // you can change this clock speed

#define WLAN_SSID "ATT992"
#define WLAN_PASS "0823031259"
#define WLAN_SECURITY WLAN_SEC_WPA2

#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data 
                                   // received before closing the connection.  If you know the server
                                   // you're accessing is quick to respond, you can reduce this value.

// What page to grab!
#define WEBSITE      "data.sparkfun.com"
//#define WEBPAGE      "/input/VGG3616pQEs9rG5VJj7r?private_key=9YYN1k1270h4zeK8oEPz&moisture="
//?private_key=9YYN1k1270h4zeK8oEPz"

/**************************************************************************/
/*!
    @brief  Sets up the HW and the CC3000 module (called automatically
            on startup)
*/
/**************************************************************************/

uint32_t ip;

int ping_pin = 2;
int ping_pin_2 = 4;
int reading_pin = A0;
int reading_pin_2 = A2;
int bad_status_pin = 6;
int good_status_pin = 9;
int emergency_status_pin = 13;
int moisture_reading;
int moisture_reading_2;
int n = 10;
//int reading_delay = 30000;
int reading_delay = 60000;
int broadcast_delay = 3600000;

void setup(void)
{
  pinMode(ping_pin, OUTPUT);
  pinMode(bad_status_pin, OUTPUT);
  pinMode(good_status_pin, OUTPUT);
  pinMode(emergency_status_pin, OUTPUT);
  
  Serial.begin(115200);
  Serial.print("Free RAM: "); Serial.println(getFreeRam(), DEC);
  
//  if (!cc3000.begin())
//  {
//    Serial.println(F("Couldn't begin()! Check your wiring?"));
//    while(1);
//  }
  
  // Optional SSID scan
  // listSSIDResults();
}

bool arrayCheckEqual(const int array[], int n)
{   
    for (int i = 0; i < n - 1; i++)      
    {         
        if (array[i] != array[i + 1])
            return false;
    }
    return true;
}

void loop(void)
{
  digitalWrite(ping_pin, HIGH);
  digitalWrite(ping_pin_2, HIGH);
  //Delay before taking measurements
  delay(500);
  
  //Read in on analog A0 the moisture reading
  Serial.println("Sensor reading moisture:");

  //Read in on analog pin the moisture reading
  int readings[n];
  for(int i = 0; i < n; i ++){
    if(i % 2 == 0) {
      readings[i] = analogRead(reading_pin);
      Serial.println("Pin 1"); 
    }
    else {
      readings[i] = analogRead(reading_pin_2);
      Serial.println("Pin 2");
    }
    
    delay(150);
  }
  moisture_reading = arrayAverage(readings, n);
  
  Serial.println(moisture_reading);
  //Turn off ping pins
  digitalWrite(ping_pin, LOW);
  digitalWrite(ping_pin_2, LOW);  
  
  if(moisture_reading <= 150)
  {
    digitalWrite(good_status_pin, LOW);    
    digitalWrite(bad_status_pin, HIGH);
    digitalWrite(emergency_status_pin, LOW);
    
    if(moisture_reading <= 50){
    //Light up "needs watering" LED
      digitalWrite(emergency_status_pin, HIGH);
    }
  }
  else
  {
    digitalWrite(good_status_pin, HIGH);
    digitalWrite(emergency_status_pin, LOW);
    digitalWrite(bad_status_pin, LOW); 
  }
  
//  Serial.print(F("\nAttempting to connect to ")); Serial.println(WLAN_SSID);
//  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
//    Serial.println(F("Failed!"));
//    while(1);
//  }
//   
//  Serial.println(F("Connected!"));
//  
//  /* Wait for DHCP to complete */
//  Serial.println(F("Request DHCP"));
//  while (!cc3000.checkDHCP())
//  {
//    delay(100);
//  }  

//  ip = 0;
  // Try looking up the website's IP address
//  Serial.print(WEBSITE); Serial.print(F(" -> "));
//  int resolve_attempts = 0;
//  while (ip == 0) {
//    if(resolve_attempts > 5) {
//      return; 
//    }
//    if (! cc3000.getHostByName(WEBSITE, &ip)) {
//      Serial.println(F("Couldn't resolve!"));
//      resolve_attempts++;
//    }
//    delay(500);
//  }

  /* Try connecting to the website.
     Note: HTTP/1.1 protocol is used to keep the server from closing the connection before all data is read.
  */
 
//  char uri[77] = "/input/VGG3616pQEs9rG5VJj7r?private_key=9YYN1k1270h4zeK8oEPz&moisture=";
//  char char_moisture_reading[20];
//  
//  strcat(uri, itoa(moisture_reading, char_moisture_reading, 10));
//  
//  Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 80);
//  if (www.connected()) {
//    www.fastrprint(F("GET "));
//    www.fastrprint(uri);
//    www.fastrprint(F(" HTTP/1.1\r\n"));
//    www.fastrprint(F("Host: ")); www.fastrprint(WEBSITE); www.fastrprint(F("\r\n"));
//    www.fastrprint(F("\r\n"));
//    www.println();
//  } else {
//    Serial.println(F("Connection failed"));    
//    return;
//  }
//
//  Serial.println(F("-------------------------------------"));
  
  /* Read data until either the connection is closed, or the idle timeout is reached. */ 
//  unsigned long lastRead = millis();
//  while (www.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
//    while (www.available()) {
//      char c = www.read();
//      Serial.print(c);
//      lastRead = millis();
//    }
//  }
//  www.close();
//  Serial.println(F("-------------------------------------"));
//  
  /* You need to make sure to clean up after yourself or the CC3000 can freak out */
  /* the next time your try to connect ... */
//  Serial.println(F("\n\nDisconnecting"));
//  cc3000.disconnect();
//  
  delay(reading_delay);
}

///**************************************************************************/
///*!
//    @brief  Begins an SSID scan and prints out all the visible networks
//*/
///**************************************************************************/

//void listSSIDResults(void)
//{
//  uint32_t index;
//  uint8_t valid, rssi, sec;
//  char ssidname[33]; 
//
//  if (!cc3000.startSSIDscan(&index)) {
//    Serial.println(F("SSID scan failed!"));
//    return;
//  }
//
//  Serial.print(F("Networks found: ")); Serial.println(index);
//  Serial.println(F("================================================"));
//
//  while (index) {
//    index--;
//
//    valid = cc3000.getNextSSID(&rssi, &sec, ssidname);
//    
//    Serial.print(F("SSID Name    : ")); Serial.print(ssidname);
//    Serial.println();
//    Serial.print(F("RSSI         : "));
//    Serial.println(rssi);
//    Serial.print(F("Security Mode: "));
//    Serial.println(sec);
//    Serial.println();
//  }
//  Serial.println(F("================================================"));
//
//  cc3000.stopSSIDscan();
//}

///**************************************************************************/
///*!
//    @brief  Tries to read the IP address and other connection details
//*/
///**************************************************************************/
//bool displayConnectionDetails(void)
//{
//  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
//  
//  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
//  {
//    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
//    return false;
//  }
//  else
//  {
//    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
//    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
//    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
//    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
//    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
//    Serial.println();
//    return true;
//  }
//}

int arrayAverage(const int array[], int n)
{
  int sum;
  for (int i = 0; i < n; i++)
  {
      sum = sum + array[i];
  }
  return sum / n;
}
