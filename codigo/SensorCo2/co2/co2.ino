#include <MHZ.h>
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <SoftwareSerial.h>

// WiFi configuration
#define WLAN_SSID       "iesgc112" 
#define WLAN_PASS       "0123456789" 

// MQTT configuration
#define MQTT_SERVER      "192.168.112.156" 
#define MQTT_SERVERPORT  1883
#define MQTT_USERNAME    ""
#define MQTT_KEY         ""
#define MQTT_FEED_CO2   "iesgrancapitan/aula1/co2" 
#define MQTT_FEED_TVOC  "iesgrancapitan/aula1/tvoc" 

// WiFi connection
WiFiClient client;

// MQTT connection
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_USERNAME, MQTT_KEY);

// Feed to publish CO2
Adafruit_MQTT_Publish co2Feed = Adafruit_MQTT_Publish(&mqtt, MQTT_FEED_CO2);

// Feed to publish TVOC
Adafruit_MQTT_Publish tvocFeed = Adafruit_MQTT_Publish(&mqtt, MQTT_FEED_TVOC);

//CO2 Sensor
#define CO2_IN 10
#define MH_Z19_RX RX  // D7
#define MH_Z19_TX TX  // D6

MHZ co2(MH_Z19_RX, MH_Z19_TX, CO2_IN, MHZ19B);

//----------------------------------------------

void connectWiFi();
void connectMQTT();
//void initSensor();

//----------------------------------------------

void setup() {
  Serial.begin(9600);
  pinMode(CO2_IN, INPUT);
  delay(100);
  Serial.println("CO2 IES Gran Capitan");
  if (co2.isPreHeating()) {
    Serial.print("Preheating");
    while (co2.isPreHeating()) {
      Serial.print(".");
      delay(5000);
    }
    Serial.println();
  }
  connectWiFi();
  connectMQTT();
//  initSensor();
}

//----------------------------------------------

void loop() {
  Serial.print("\n----- Time from start: ");
  Serial.print(millis() / 1000);
  Serial.println(" s");
  // Wait a few seconds between measurements.
  delay(1000);

//  if(sensor.checkDataReady() == false){
  //  Serial.println("Data is not ready!");
    //return;
  //}

  int ppm_uart = co2.readCO2UART();
  Serial.print("PPMuart: ");

  if (ppm_uart > 0) {
    Serial.print(ppm_uart);
  } else {
    Serial.print("n/a");
  }

  int ppm_pwm = co2.readCO2PWM();
  Serial.print(", PPMpwm: ");
  Serial.print(ppm_pwm);

  int temperature = co2.getLastTemperature();
  Serial.print(", Temperature: ");

  if (temperature > 0) {
    Serial.println(temperature);
  } else {
    Serial.println("n/a");
  }

  Serial.println("\n------------------------------");
  delay(5000);
  
  //co2Feed.publish(co2);
  //tvocFeed.publish(tvoc);
}



void connectWiFi() {
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//----------------------------------------------

void connectMQTT() {
  if (mqtt.connected())
    return;

  Serial.print("Connecting to MQTT... ");
  while (mqtt.connect() != 0) {
       Serial.println("Error. Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);
  }
}
