// Programa para NodeMCU

/* Sensores - Actuadores
Gas - Buzzer
Temperatura - Ventilador / Display
 */

// Definiciones de pins de NodeMCU 

#define D0 16 // Sensor de temperatura
#define D1 5 // Buzzer
#define D2 4 // Ventilador
#define D3 0 // SCL para display
#define D4 2 // SDA para display

// Definiciones del sensor de temperatura DHT11

#include "DHT.h"
#define DHT_TYPE DHT11
DHT dht(D0, DHT_TYPE);

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

char sTopicoOutPhotorresistor[50];
char sTopicoOutTemperature[50];
char sTopicoOutDistance[50]; 

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

  digitalWrite(D3, HIGH); 
  delay(100); 
  digitalWrite(D3, LOW); // Aviso LED mensaje recibido

  if ((char)payload[0] == '1') { // Aviso LED primer cáracter es 1
    digitalWrite(D4, HIGH);
  } 
  else {
    digitalWrite(D4, LOW); 
  }
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

void conectarMQTT() {
  
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

//  Funcion detectora de gas con el sensor ARD-352

void medirGas() {
  
  gasSensorVoltage = analogRead(GAS_SENSOR_PIN);

  Serial.print("Valor de voltaje (Gas): \n");
  Serial.println(gasSensorVoltage);

  if (gasSensorVoltage > 500)
    encenderBuzzer();

  snprintf (sTopicoOutGas, MSG_BUFFER_SIZE, "{\"gV\":%d}", gasSensorVoltage);
}

// Funcion que lee temperatura y humedad con el sensor DHT11

void medirTemperatura() {
  
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.print("Falló al leer el sensor DHT\n");
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humedad: "); Serial.print(h);
  Serial.print(", Temperatura: "); Serial.print(t);
  Serial.print("(C) "); Serial.print(f);
  Serial.print("(F), Indice de calor: "); Serial.print(hic);
  Serial.print("(C) "); Serial.print(hif);
  Serial.print("(F)\n\n");

  digitalWrite(D3, (int) t);

  snprintf (sTopicoOutTemperature, MSG_BUFFER_SIZE, "{\"t\":%5.2f,\"h\":%5.2f}", t, h);
}

void encenderBuzzer() {

    tone(D4, 1000);
    delay(1000);
    noTone(D4);
    delay(1000);
}

void setup() {

  Serial.begin(9600);

  pinMode(D0, INPUT); // Pin del sensor de temperatura
  pinMode(D1, OUTPUT); // Pin SCL para display
  pinMode(D2, OUTPUT); // Pin SDA para display
  pinMode(D3, OUTPUT); // Ventilador
  pinMode(D4, OUTPUT); // Buzzer

  setup_wifi();
  setup_mqtt();

  dht.begin();
}

void loop() {
  
  medirTemperatura();
  medirLuz();
  medirDistancia();
  conectarMQTT();
}