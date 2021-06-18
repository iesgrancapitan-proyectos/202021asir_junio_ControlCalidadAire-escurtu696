#include <DHT.h>
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#include <MHZ19.h>
#include <Arduino.h>
#include <SoftwareSerial.h> 

#define MH_Z19_RX TX
#define MH_Z19_TX RX
#define DHTPin D2
#define DHTTYPE DHT22
DHT dht(DHTPin, DHTTYPE);

#define WLAN_SSID       "iesgc112" 
#define WLAN_PASS       "1234567890" 

#define MQTT_SERVER      "ec2-54-88-159-111.compute-1.amazonaws.com" 
#define MQTT_SERVERPORT  1883
#define MQTT_USERNAME    ""
#define MQTT_KEY         ""
#define MQTT_FEED_TEMP   "iesgrancapitan/aula1/temperature" 
#define MQTT_FEED_HUMI   "iesgrancapitan/aula1/humidity"
#define MQTT_FEED_CO2   "iesgrancapitan/aula1/co2" 

MHZ19 myMHZ19;
SoftwareSerial mySerial(MH_Z19_RX, MH_Z19_TX); 

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_USERNAME, MQTT_KEY);

Adafruit_MQTT_Publish temperatureFeed = Adafruit_MQTT_Publish(&mqtt, MQTT_FEED_TEMP);

Adafruit_MQTT_Publish humidityFeed = Adafruit_MQTT_Publish(&mqtt, MQTT_FEED_HUMI);

// Feed to publish CO2
Adafruit_MQTT_Publish co2Feed = Adafruit_MQTT_Publish(&mqtt, MQTT_FEED_CO2);

//----------------------------------------------

void connectWiFi();

//----------------------------------------------

void setup() {
  Serial.begin(115200);
  Serial.println("IoT demo");
  dht.begin();
  connectWiFi();
  connectMQTT();

  Serial.println("");
  Serial.println("Init...");

  // Init MH-Z19
  mySerial.begin(9600);          
  myMHZ19.begin(mySerial);

  // Show firmware
  char myVersion[4];          
  myMHZ19.getVersion(myVersion);

  Serial.print("Firmware Version: ");
  for(byte i = 0; i < 4; i++)
  {
    Serial.print(myVersion[i]);
    if(i == 1)
      Serial.print(".");    
  }
  Serial.println("");

  Serial.printf("Max range: %d ppm\n", myMHZ19.getRange());
  Serial.printf("ABC status: ");
  Serial.println(myMHZ19.getABC()?"ON":"OFF");
  Serial.println("Setup done.");
}

//----------------------------------------------

void loop() {
  delay(600);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Fallo en la lectura");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");

  Serial.printf("CO2: %d ppm\n", myMHZ19.getBackgroundCO2());
  delay(5000);

  temperatureFeed.publish(t);
  humidityFeed.publish(h);
  co2Feed.publish(myMHZ19.getBackgroundCO2());
}

//----------------------------------------------

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
