
//*******************************************************************************************
//ADAFRUIT IO WEB portal
//Arduino
//Name
//Temperature
//Maximum length: 128 characters. Used: 11
//
//Key
//temperature
//Changing the key will change API URLs and MQTT subscription topics. The only characters we permit are lower case english letters ("a" to "z"), numbers, and dash ("-").
//
//See our guide to naming things in Adafruit IO for more information about how we handle the formatting of names and keys.
//
//Current Endpoints
//Web  https://io.adafruit.com/valeram1919/feeds/temperature
//API https://io.adafruit.com/api/v2/valeram1919/feeds/temperature
//MQTT
//by Key  valeram1919/feeds/temperature

#define PUBLISH_DELAY   5000
#define DHTPIN          3
#define DHTTYPE         DHT11
#define RELAY_PIN       6
#define IO_USERNAME  "valeram1919"
#define IO_KEY       "aio_wJAn65hF9N9JxxCDbFI6V0fVLa4L"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
//**********************************************************************************

// Server details
const char server[] = "io.adafruit.com";
const char resource[] = "https://io.adafruit.com/api/v2/valeram1919/feeds?x-aio-key=aio_wJAn65hF9N9JxxCDbFI6V0fVLa4L";

const char api[]= "https://io.adafruit.com/api/v2/valeram1919/feeds/counter";
const char aiotemperature[]="valeram1919/feeds/temperature";
const char aiocounter[]="valeram1919/feeds/counter";
//const char temperature[]="value=42 -H X-AIO-Key:aio_wJAn65hF9N9JxxCDbFI6V0fVLa4L https://io.adafruit.com/api/v2/valeram1919/feeds/temperature/data";
//const char temperature[]=" value=42 https://io.adafruit.com/api/v2/valeram1919/feeds/temperature/data/";
// Your GPRS credentials (leave empty, if missing)
const char apn[]      = "ibox.tim.it"; // Your APN
const char gprsUser[] = ""; // User
const char gprsPass[] = ""; // Password
const char simPIN[]   = ""; // SIM card PIN code, if any
const char iousername[] = "valeram1919";
const char iokey[]=     "aio_wJAn65hF9N9JxxCDbFI6V0fVLa4L";
const char aioserver[]= "io.adafruit.com";
const int aioserverport=  1883;
//const char temperature[] PROGMEM = iousername "/feeds/temperature";
//
const char* xcounter = "69";
//const char* password = "---";

const char* host = "io.adafruit.com";
const char* io_key = "aio_wJAn65hF9N9JxxCDbFI6V0fVLa4L";
const char* path_with_username = "/api/v2/valeram1919/dashboards";
