
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
/

#define PUBLISH_DELAY   5000
#define DHTPIN          3
#define DHTTYPE         DHT11
#define RELAY_PIN       6
#define IO_USERNAME  "xxxxxxxxxx"
#define IO_KEY       "aio_yyyyyyyyyyyyyyyyyyy"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
//**********************************************************************************

// Server details
const char server[] = "io.adafruit.com";
const char resource[] = "https://io.adafruit.com/api/v2/xxxxxxxxxx/feeds?x-aio-key=aio_yyyyyyyyyyyyyyyyy";

const char api[]= "https://io.adafruit.com/api/v2/xxxxxxxxxxxx/feeds/counter";
const char aiotemperature[]="xxxxxxxxx/feeds/temperature";
const char aiocounter[]="xxxxxxxxxxxxx/feeds/counter";

const char apn[]      = "ap"; // Your APN
const char gprsUser[] = ""; // User
const char gprsPass[] = ""; // Password
const char simPIN[]   = ""; // SIM card PIN code, if any
const char iousername[] = "xxxxxxxxxx";
const char iokey[]=     "aio_yyyyyyyyyyyyyy";
const char aioserver[]= "io.adafruit.com";
const int aioserverport=  1883;

const char* xcounter = "69";
//const char* password = "---";

const char* host = "io.adafruit.com";
const char* io_key = "aio_yyyyyyyyyyyyyyyyyy";
const char* path_with_username = "/api/v2/xxxxxxxxxxxx/dashboards";
