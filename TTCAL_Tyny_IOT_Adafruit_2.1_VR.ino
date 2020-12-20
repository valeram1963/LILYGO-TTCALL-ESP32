/* **************************************************************
 *DOIT ESP32 DEVKIT V1 on port SLAB_USBtoUART
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space

// Default heartbeat interval for GSM is 60
// If you want override this value, uncomment and set this option:
// #define BLYNK_HEARTBEAT 30

#include"modem.h"
#include"adafruit_setup.h"
#include<Wire.h>
#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>

//#include <ESP8266HTTPClient.h>

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//*****************************************************************************************
// Configure TinyGSM library
#define TINY_GSM_MODEM_SIM800          // Modem is SIM800
#define TINY_GSM_RX_BUFFER      1024   // Set RX buffer to 1Kb
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10       /* Time ESP32 will go to sleep (in seconds) */

//***********************************SERIAL AT to MODEM*****************************************************
// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial
// Set serial for AT commands (to the module)
#define SerialAT  Serial1
TinyGsm modem(SerialAT);

void turnOffNetlight()
{
    SerialMon.println("Turning off SIM800 Red LED...");
    modem.sendAT("+CNETLIGHT=0");
}

void turnOnNetlight()
{
    SerialMon.println("Turning on SIM800 Red LED...");
    modem.sendAT("+CNETLIGHT=1");
}

TinyGsmClient client(modem);
const int  port = 1883;
//*****************************************************************************************



// setPowerBoostKeepOn
bool setupPMU()
{
    bool en = true;
    Wire.begin(I2C_SDA, I2C_SCL);
    Wire.beginTransmission(IP5306_ADDR);
    Wire.write(IP5306_REG_SYS_CTL0);
    if (en) {
        Wire.write(0x37); // Set bit1: 1 enable 0 disable boost keep on
    } else {
        Wire.write(0x35); // 0x37 is default reg value
    }
    return Wire.endTransmission() == 0;
}


// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

// Set serial for AT commands (to the module)
#define SerialAT  Serial1


//********************************************************************************************
//Adafruit Autentication

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, aioserver, aioserverport, iousername, iokey);

/****************************** Feeds *********************************************************/

// Setup a feed called 'count' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
#define COUNT_FEED "/feeds/counter"
Adafruit_MQTT_Publish count = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME COUNT_FEED);
//Adafruit_MQTT_Publish count = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/counter");
#define TEMP_FEED "/feeds/temperature"
Adafruit_MQTT_Publish temp = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME TEMP_FEED);

//********************************************************************************************
// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
//void MQTT_connect();

int x=0;//Counter value for test


//*****************************SETUP**********************************************************
//********************************************************************************************

void setup()
{
    // Set console baud rate
    SerialMon.begin(115200);
    Serial.println("TTCAL_Tyny_IOT_Adafruit_2.0_VR.ino");//.ino file name
    delay(300);

    // Start power management
    if (setupPMU() == false) {
        Serial.println("Setting power error");
    }

    // Some start operations
    setupModem();

    // Set GSM module baud rate and UART pins
    SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
    //SerialMon.println("Initializing setup modem...");
    //modem.restart();
}

//*************************************************************************************************
//*************************************************************************************************
//******************LOOP***************************************************************************
void loop()
{
    // Restart takes quite some time
    // To skip it, call init() instead of restart()
    SerialMon.println("Initializing modem...");
    //modem.restart();
    modem.init();

   // Turn off network status lights to reduce current consumption
   // turnOffNetlight();

   // The status light cannot be turned off, only physically removed
   // turnOnNetlight();

    // Or, use modem.init() if you don't need the complete restart
//    String modemInfo = modem.getModemInfo();
//    SerialMon.print("Modem: ");
//    SerialMon.println(modemInfo);
//    delay(5000);
//    // Unlock your SIM card with a PIN if needed
//    if (strlen(simPIN) && modem.getSimStatus() != 3 ) {
//        modem.simUnlock(simPIN);
//    }

    SerialMon.print("Waiting for network...");
    if (!modem.waitForNetwork(240000L)) {
        SerialMon.println(" fail");
        delay(10000);
        return;
    }


    if (modem.isNetworkConnected()) {
        SerialMon.print("Network connected ...->");
        SerialMon.println(" OK");

        // When the network connection is successful, turn on the indicator
        digitalWrite(LED_GPIO, LED_ON);
    }
//****************************************ACCESS to API *****************************************************
    SerialMon.print(F("Connecting to APN: "));
    SerialMon.print(apn);
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
        SerialMon.println(" fail");
        delay(10000);
        return;
    }
    SerialMon.println(" OK");
//**************************************CONNECTED TO IO SEVER*******************************************************
    SerialMon.print("Connecting to ");
    SerialMon.print(aioserver);
    client.connect(aioserver,aioserverport);
    
    if (!client.connect(aioserver,aioserverport)) {
        SerialMon.println(" fail");
        delay(10000);
        return;
    }
    SerialMon.println(" OK");

//*******************************************************MQTT Connected*****************************************
 connect();
  
  Adafruit_MQTT_Subscribe *subscription;

  Adafruit_MQTT_Publish count = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME COUNT_FEED);

 
 // Now we can publish stuff!
  Serial.print(F("\nSending count val "));
  x=x+10;

 Serial.print("x=");
 Serial.println(x); 
 
  if (! count.publish((int)x)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("Counter Data sent ->OK!"));
  }

connect();


  Adafruit_MQTT_Publish temp = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME TEMP_FEED);

  if (! temp.publish((int)x)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("Temperature Data sent ->OK!"));
  }

//****************************************Timer for Modem Restart************************************************


    // Shutdown
    client.stop();
    SerialMon.println(F("Server disconnected"));

    modem.gprsDisconnect();
    SerialMon.println(F("GPRS disconnected"));


    // DTR is used to wake up the sleeping Modem
#ifdef MODEM_DTR
    bool res;

    modem.sleepEnable();

    delay(100);

    // test modem response , res == 0 , modem is sleep
    res = modem.testAT();
    Serial.print("SIM800 Test AT result 0 , modem is sleep-> ");
    Serial.println(res);

    delay(1000);

    Serial.println("Use DTR Pin Wakeup");
    pinMode(MODEM_DTR, OUTPUT);
    //Set DTR Pin low , wakeup modem .
    digitalWrite(MODEM_DTR, LOW);


    // test modem response , res == 1 , modem is wakeup
    res = modem.testAT();
    Serial.print("SIM800 Test AT result res == 1 , modem is wakeup-> ");
    Serial.println(res);

#endif



    // Make the BLUELED blink three times before going to sleep
    int i = 3;
    while (i--) {
        digitalWrite(LED_GPIO, LED_ON);
        modem.sendAT("+SPWM=0,1000,80");
        delay(500);
        digitalWrite(LED_GPIO, LED_OFF);
        modem.sendAT("+SPWM=0,1000,0");
        delay(500);
    }
//*********************************POWER SLEEP ********************************************
    //After all off - uncomment if you need to go for deepsleep and reset at wakeup
//    modem.poweroff();
//
//   SerialMon.println(F("Poweroff"));
//
//    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
//
//    esp_deep_sleep_start();

    /*
    The sleep current using AXP192 power management is about 500uA,
    and the IP5306 consumes about 1mA
    */
}

void connect() {
Serial.print("Connecting to Adafruit IO... ");
int8_t ret;
while ((ret = mqtt.connect()) != 0) {
  switch (ret) {
    case 1: Serial.println("Wrong protocol"); break;
    case 2: Serial.println("ID rejected"); break;
    case 3: Serial.println("Server unavail"); break;
    case 4: Serial.println("Bad user/pass"); break;
    case 5: Serial.println("Not authed"); break;
    case 6: Serial.println("Failed to subscribe"); break;
    default: Serial.println("Connection failed"); break;
  }
  if (ret >= 0) {
    mqtt.disconnect();
  }
  Serial.println("Retrying connection...");
  delay(5000);
}
Serial.println("Adafruit IO Connected!");
}
