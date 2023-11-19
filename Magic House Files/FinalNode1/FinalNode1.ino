// Programa para NodeMCU 1 (Protoboard Blanca)

/* Sensores - Actuadores
Gas - Buzzer
Temperatura - Ventilador / Display
 */

// Definiciones de pins de NodeMCU 

#define D1 5 // SCL para display
#define D2 4 // SDA para display
#define D3 0 // Buzzer
#define D4 2 // Ventilador
#define D5 14 // Sensor de temperatura

// Definiciones del sensor de temperatura DHT11

#include "DHT.h"
#define DHT_TYPE DHT11
DHT dht(D5, DHT_TYPE);

// Definiciones del sensor de gas ARD-352

const int GAS_SENSOR_PIN = A0;
int gasSensorVoltage = -1;

// Definiciones de ESP8266MQTT

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Tec-IoT";
const char* password = "spotless.magnetic.bridge";
const char* mqtt_server = "broker.mqtt-dashboard.com";

const char* topico_salida_1 = "TopicOutTemperature_Equipo2";
const char* topico_salida_2 = "TopicOutGas_Equipo2";

char sTopicoOutTemperature[50];
char sTopicoOutGas[50]; 

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;

#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

// Funcion que conecta al Wi-fi del Router

void setup_wifi() {

  delay(10);

  Serial.println(); 
  Serial.print("Connecting to "); 
  Serial.println(ssid);

  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 

  randomSeed(micros());

  Serial.println(); 
  Serial.println("Wi-Fi connected"); 
  Serial.print("IP address: "); 
  Serial.println(WiFi.localIP());
}

// Funcion que conecta a Broker MQTT

void setup_mqtt() {

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  if (!client.connected()) {
    reconnect();
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  
  Serial.print("Message arrived ["); 
  Serial.print(topic); 
  Serial.print("] ");
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
}

// Funcion que conecta o reconecta a Broker MQTT

void reconnect() {

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");

      client.subscribe(topico_salida_1);
      client.subscribe(topico_salida_2);
    } 
    else {
      Serial.print("failed, rc="); 
      Serial.print(client.state()); 
      Serial.println(" try again in 5 seconds");

      delay(5000);
    }
  }
}

void connectMQTT() {
  
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  unsigned long now = millis();

  if (now - lastMsg > 5000) {
    lastMsg = now;
    ++value;

    Serial.println(now); 
    Serial.print("Publish message: "); 

    Serial.println(sTopicoOutTemperature);
    client.publish(topico_salida_1, sTopicoOutTemperature);

    Serial.println(sTopicoOutGas);
    client.publish(topico_salida_2, sTopicoOutGas);
  }
}

// Funcion que lee temperatura y humedad con el sensor DHT11

void readTemperatureHumidity(float thresold) {
  
  delay(1000);

  float h = 0;
  float t = 0;

  h = dht.readHumidity();
  t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    return;
  }

  if(t > thresold) {
    digitalWrite(D4, HIGH);
  }
  else {
    digitalWrite(D4, LOW);
  }

/*   For debugging
  Serial.print("T: ");
  Serial.println(t); */
  
  snprintf (sTopicoOutTemperature, MSG_BUFFER_SIZE, "{\"t\":%5.2f,\"h\":%5.2f}", t, h);
}

//  Funcion detectora de gas con el sensor ARD-352

void readGas(float threshold) {

  delay(1000);
  
  gasSensorVoltage = 0;

  gasSensorVoltage = analogRead(GAS_SENSOR_PIN);

  if(gasSensorVoltage > threshold) {
    turnOnBuzzer(D3, 3, 4000, 150, 200);
  }

/*   For debugging
  Serial.print("G: ");
  Serial.println(gasSensorVoltage); */

  snprintf (sTopicoOutGas, MSG_BUFFER_SIZE, "{\"gV\":%d}", gasSensorVoltage);
}

void turnOnBuzzer(unsigned short int pin, unsigned short int beeps, unsigned short int frequency, unsigned short int duration, unsigned short int delayTime) {

  for(unsigned short int i = 0; i < beeps; i++) {
    tone(pin, frequency, duration);
    delay(delayTime);
    noTone(pin);
    delay(delayTime);
  }
}

void setup() {

  Serial.begin(9600);

  pinMode(D1, OUTPUT); // SCL para display
  pinMode(D2, OUTPUT); // SDA para display
  pinMode(D3, OUTPUT); // Buzzer
  pinMode(D4, OUTPUT); // Ventilador
  pinMode(D5, INPUT); // Sensor de temperatura

  setup_wifi();
  setup_mqtt();

  dht.begin();
}

void loop() {
  
  readTemperatureHumidity(25);
  readGas(310);

  connectMQTT();
}