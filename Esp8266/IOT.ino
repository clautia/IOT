//Ultrasónico
#include "DHT.h"

//Pines
#define trigPin 5 //D1
#define echoPin 4 //D2
#define DHTPIN 13
#define led 12
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float h,t,f;
void temperatura() {
    delay(2000);                          //esperar 2 segundos, sensor lento
    h = dht.readHumidity();               // Humedad
    t = dht.readTemperature();            // Temp en Celsius (default)
    f = dht.readTemperature(true);        // Temp Fahrenheit (isFahrenheit = true)

    if (isnan(h) || isnan(t) || isnan(f)) {                         
        Serial.println(F("Failed to read from DHT sensor!"));
        return;

    } else {
        Serial.print("temp: ");
        Serial.println(t);
        Serial.print("hum: ");
        Serial.println(h);

        if (t > 24)
            digitalWrite(led, HIGH);
        else 
            digitalWrite(led, LOW);
    }
}

void setup() {
    Serial.begin(9600);
    //    pinMode(trigPin, OUTPUT);
    //    pinMode(echoPin, INPUT);
    dht.begin();
    pinMode(led, OUTPUT);

}

void loop() {

    //Checar temperatura
    temperatura();
       
  
}
