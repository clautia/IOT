// Programa para NodeMCU 2 (Protoboard roja)

/* Sensores - Actuadores
Ultrasonico - Servo
Fotorresistencia - LED
 */

// Definiciones de pins de NodeMCU 

#define D1 5 // Servo
#define D2 4 // Echo de ultrasonico
#define D3 0 // LED
#define D4 2 // Trigger de ultrasonico

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
  
  delay(2000);

  float distance = 0; 
  float duration = 0;

  digitalWrite(D4, LOW);
  delayMicroseconds(2);

  digitalWrite(D4, HIGH);
  delayMicroseconds(10);
  digitalWrite(D4, LOW);

  duration = pulseIn(D2, HIGH);

  distance = duration * 0.034 / 2;

  if(distance > thresold) {
    digitalWrite(D4, HIGH);
  }
  else {
    digitalWrite(D4, LOW);
  }

  snprintf (sTopicoOutDistance, MSG_BUFFER_SIZE, "{\"d\":%5.2f}", distance);
}

//  Funcion detectora de luz con fotorresistencia

void readLigth(float threshold) {

  photorresistanceVoltage = 0;
  
  photorresistanceVoltage = analogRead(PHOTORRESISTANCE_PIN);

  Serial.print("Valor de voltaje (Luz): \n");
  Serial.println(photorresistanceVoltage);

  if (photorresistanceVoltage > threshold) {
    digitalWrite(D3, HIGH);
  }
  else {
    digitalWrite(D3, LOW);
  }

  snprintf (sTopicoOutLigth, MSG_BUFFER_SIZE, "{\"lV\":%d}", photorresistanceVoltage);
}

// Funcion que lee temperatura y humedad con el sensor DHT11

void setup() {

  Serial.begin(9600);

  pinMode(D1, OUTPUT); // Servo
  pinMode(D2, INPUT); // Echo de ultrasonico
  pinMode(D3, OUTPUT); // LED
  pinMode(D4, OUTPUT); // Trigger de ultrasonico

  setup_wifi();
  setup_mqtt();
}

void loop() {
  
  readDistance(100);
  readLigth(100);

  connectMQTT();
}