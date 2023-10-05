#define D2  5 //trigPind d2
#define D3  4 // echoPin d3
#define D1  0 //aqui va el led del sensor ultrasónico d1

// ----- Funcion que dispara un rayo, lo apaga y espera el echo
//       para medir distancia

void medirDistanciaCm() {
  int trigPin = D2;
  int echoPin = D3;
  float v = 331.5+0.6*20;   // m/
  int ledSonic = 5;  // Equivale a D1
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin,LOW);

  //listen for echo
  float tUs = pulseIn(echoPin, HIGH);  //microseconds
  float t = tUs / 1000.0 / 1000.0 / 2.0;    //s
  float d = t*v;  //m
  float dCm = d*100;  // cm  
  Serial.print("Distancia(cm): ");
  Serial.println(dCm);
  delay(200);  //ms

  if (dCm > 20)
    digitalWrite(ledSonic, HIGH);
  else
    digitalWrite(ledSonic, LOW);

}



// =================================================================
void setup() {
   pinMode(D1,OUTPUT); // Led del sensor ultrasónico

   // ----- Iniciar consola: Herramientas, Monitor serie
   Serial.begin(9600);  

   // ----- Inicializacion sensor de distancia
   int trigPin = D2;
   int echoPin = D3;
   pinMode(trigPin,OUTPUT);
   pinMode(echoPin,INPUT);
   Serial.println("Iniciando Sensor Distancia");
}

void loop() {
   
   medirDistanciaCm();
}
