// Programa para NodeMCU 2 (Protoboard roja)

/* Sensores - Actuadores
Ultrasonico - Servo
Fotorresistencia - LED
 */

#include <NewPing.h>

// Definiciones de pins de NodeMCU 

#define D0 16 // Trigger de ultrasonico
#define D1 5 // Servo
#define D2 4 // Echo de ultrasonico
#define D3 0 // LED

// Definición de ultrasónico

#define MAX_DISTANCE 40

NewPing sonar(DO, D2, MAX_DISTANCE);

// Definiciones de fotorresistencia

const int PHOTORRESISTANCE_PIN = A0;
int photorresistanceVoltage = -1;

// Definiciones de ESP8266MQTT

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Tec-IoT";
const char* password = "spotless.magnetic.bridge";
const char* mqtt_server = "broker.mqtt-dashboard.com";

const char* topico_salida_1 = "TopicOutDistance_Equipo2";
const char* topico_salida_2 = "TopicOutLigth_Equipo2";

char sTopicoOutDistance[50];
char sTopicoOutLigth[50];

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

    Serial.println(sTopicoOutDistance);
    client.publish(topico_salida_1, sTopicoOutDistance);

    Serial.println(sTopicoOutLigth);
    client.publish(topico_salida_2, sTopicoOutLigth);
  }
}

// Función medidora de distancia con ultrasónico

void readDistance(unsigned short int thresold) {

  delay(50);

  float distance = sonar.ping_cm();

  if(distance > thresold) {
    digitalWrite(D1, 100);
  }

  snprintf (sTopicoOutDistance, MSG_BUFFER_SIZE, "{\"d\":%5.2f}", distance);

}

//  Funcion detectora de luz con fotorresistencia

void readLigth(float threshold) {
  
  photorresistanceVoltage = analogRead(PHOTORRESISTANCE_PIN);

  Serial.print("Valor de voltaje (Gas): \n");
  Serial.println(photorresistanceVoltage);

  if (photorresistanceVoltage > threshold)
    digitalWrite(D3, HIGH);

  snprintf (sTopicoOutLigth, MSG_BUFFER_SIZE, "{\"lV\":%5.2f}", photorresistanceVoltage);
}

// Funcion que lee temperatura y humedad con el sensor DHT11

void setup() {

  Serial.begin(115200);

  pinMode(D0, OUTPUT); // Trigger de ultrasonico
  pinMode(D1, OUTPUT); // Servo
  pinMode(D2, INPUT); // Echo de ultrasonico
  pinMode(D3, OUTPUT); // LED

  setup_wifi();
  setup_mqtt();

  dht.begin();
}

void loop() {
  
  readDistance(100);
  readLigth(100);

  connectMQTT();
}