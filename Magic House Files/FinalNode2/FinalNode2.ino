// Programa para NodeMCU 2 (Protoboard roja)

/* Sensores - Actuadores
Ultrasonico - Servo
Fotorresistencia - LED
 */

#include <Servo.h>

Servo servo;

// Definiciones de pins de NodeMCU 

#define D1 5 // Echo de ultrasonico
#define D2 4 // Trigger de ultrasonico
#define D5 14 // Servo
#define D6 12 // LED

// Definiciones de fotorresistencia

const int PHOTORRESISTANCE_PIN = A0;

// Definiciones de ESP8266MQTT

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Tec-IoT";
const char* password = "spotless.magnetic.bridge";
const char* mqtt_server = "broker.mqtt-dashboard.com";

const char* topico_salida_1 = "TopicOutDistance_Equipo2";
const char* topico_salida_2 = "TopicOutLigth_Equipo2";
const char* topico_salida_3 = "TopicOutIsDoorOpen_Equipo2";

char sTopicoOutDistance[50];
char sTopicoOutLigth[50];
char sTopicoOutIsDoorOpen[50];

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

    Serial.println(sTopicoOutIsDoorOpen);
    client.publish(topico_salida_3, sTopicoOutIsDoorOpen);
  }
}

// Función medidora de distancia con ultrasónico

void readDistance(unsigned short int echo, unsigned short int trigger, unsigned short int actuatorPin, float thresoldDistance, unsigned int durationThresold = 15000) {
  
  delay(1000);

  float distance = 0; 
  float duration = 0;
  bool isDoorOpen = false;

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  static unsigned long startTime = 0;
  unsigned long elapsedTime = 0;
  
  if(distance > thresoldDistance) {

    isDoorOpen = true;
    
    if(startTime = 0) {

      startTime = millis();
    } else {

      elapsedTime = millis() - startTime;

      if(elapsedTime >= durationThresold) {
          
          servo.write(90);
      }
    }
  }
  else {
    isDoorOpen = false;
    servo.write(0);
    startTime = 0;
  }

  snprintf(sTopicoOutIsDoorOpen, MSG_BUFFER_SIZE, "{\"type\":\"puertaAbierta\",\"value\":%d}", isDoorOpen);
  snprintf(sTopicoOutDistance, MSG_BUFFER_SIZE, "{\"type\":\"distance\",\"value\":%5.2f}", distance);
}

//  Funcion detectora de luz con fotorresistencia

void readLigth(unsigned short int photorresistancePin, unsigned short int actuatorPin) {

  delay(1000);

  unsigned short int photorresistanceVoltage = 0;
  unsigned short int brightness = 0;
  
  photorresistanceVoltage = analogRead(photorresistancePin);
  brightness = map(photorresistanceVoltage, 45, 1024, 255, 0);

  analogWrite(actuatorPin, brightness);

  snprintf(sTopicoOutLigth, MSG_BUFFER_SIZE, "{\"type\":\"luz\",\"value\":%d}", photorresistanceVoltage);
}

// Funcion que lee temperatura y humedad con el sensor DHT11

void setup() {

  Serial.begin(9600);

  pinMode(D1, INPUT); // Echo del ultrasonico
  pinMode(D2, OUTPUT); // Trigger de ultrasonico
  pinMode(D5, OUTPUT); // Servo
  pinMode(D6, OUTPUT); // LED

  servo.attach(D5);

  setup_wifi();
  setup_mqtt();
}

void loop() {

  readDistance(D1, D2, D5, 17, 2000);
  readLigth(PHOTORRESISTANCE_PIN, D6);

  connectMQTT();
}