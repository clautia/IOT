// Programa para NodeMCU, detector de iluminacion mediante un fotorresitor, de temperatura y de distancia

// Definiciones de pins de NodeMCU 

#define D0 16 // Pin del LED del fotorresistor
#define D1 5 // Pin del LED de sensor de temperatura
#define D2 4 // Pin del LED de sensor de distancia
#define D3 0 // Pin del LED de aviso de mensaje recibido
#define D4 2 // Pin del LED de aviso de primer cáracter es 1
#define D5 14 // Pin de sensor de temperatura
#define D6 12 // Pin Trigger
#define D7 13 // Pin Echo

// Definiciones del sensor de temperatura DHT11

#include "DHT.h"
#define DHT_TYPE DHT11
DHT dht(D5, DHT_TYPE);

// Definiciones del fotorresistor

const int PHOTO_PIN = A0;
int photorresistorVoltage = -1; // 0 ... 1023

// Definiciones del sensor de distancia

float v = 331.5 + 0.6 * 20; // m/s

// Definiciones de ESP8266MQTT

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Tec-IoT";
const char* password = "spotless.magnetic.bridge";
const char* mqtt_server = "broker.mqtt-dashboard.com";

/* const char* topico_entrada_1 = "TopicInPhotorresitor_Equipo2";
const char* topico_entrada_2 = "TopicInTemperature_Equipo2";
const char* topico_entrada_3 = "TopicInDistance_Equipo2"; */

const char* topico_salida_1 = "TopicOutPhotorresistor_Equipo2";
const char* topico_salida_2 = "TopicOutTemperature_Equipo2";
const char* topico_salida_3 = "TopicOutDistance_Equipo2";

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

/*    client.subscribe(topico_entrada_1);
      client.subscribe(topico_entrada_2);
      client.subscribe(topico_entrada_3); */

      client.subscribe(topico_salida_1);
      client.subscribe(topico_salida_2);
      client.subscribe(topico_salida_3);
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

    Serial.println(sTopicoOutPhotorresistor);
    client.publish(topico_salida_1, sTopicoOutPhotorresistor);

    Serial.println(sTopicoOutTemperature);
    client.publish(topico_salida_2, sTopicoOutTemperature);

    Serial.println(sTopicoOutDistance);
    client.publish(topico_salida_3, sTopicoOutDistance);
  }
}

//  Funcion detectora de iluminacion mediante un fotorresitor

void medirLuz() {
  
  photorresistorVoltage = analogRead(PHOTO_PIN);

  Serial.print("Valor de voltaje (Iluminacion): \n");
  Serial.println(photorresistorVoltage);

  if (photorresistorVoltage > 500)
    digitalWrite(D0, HIGH);
  else
    digitalWrite(D0, LOW);

  snprintf (sTopicoOutPhotorresistor, MSG_BUFFER_SIZE, "{\"pV\":%d}", photorresistorVoltage);
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

  if (t > 25)
    digitalWrite(D1, HIGH);
  else
    digitalWrite(D1, LOW);

  snprintf (sTopicoOutTemperature, MSG_BUFFER_SIZE, "{\"t\":%5.2f,\"h\":%5.2f}", t, h);
}

// Funcion que lee distancia mediante sensor ultrasónico

void medirDistancia() {
  digitalWrite(D6, LOW);
  delayMicroseconds(3);
  digitalWrite(D6, HIGH);
  delayMicroseconds(5);
  digitalWrite(D6, LOW);

  float tUs = pulseIn(D7, HIGH);
  float t = tUs / 1000.0 / 1000.0 / 2.0;
  float d = t * v;
  float dCm = d * 100; 

  Serial.print("Distancia (cm): \n");
  Serial.println(dCm);

  delay(200);

  if(dCm < 10) {
    digitalWrite(D2, HIGH);
  }
  else {
    digitalWrite(D2, LOW);
  }

  snprintf (sTopicoOutDistance, MSG_BUFFER_SIZE, "{\"dCm\":%5.2f}", dCm);
}

void setup() {

  Serial.begin(9600);

  pinMode(D0, OUTPUT); // Pin del LED del fotorresistor
  pinMode(D1, OUTPUT); // Pin del LED de sensor de temperatura
  pinMode(D2, OUTPUT); // Pin del LED de sensor de distancia
  pinMode(D3, OUTPUT); // Pin del LED de aviso de mensaje recibido
  pinMode(D4, OUTPUT); // Pin del LED de aviso de primer cáracter es 1
  pinMode(D5, INPUT); // Pin de sensor de temperatura
  pinMode(D6, OUTPUT); // Pin Trigger
  pinMode(D7, INPUT); // Pin Echo

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