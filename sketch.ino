#include <WiFi.h>
#include <PubSubClient.h> // Biblioteca para MQTT
#include "DHT.h"

// --- CONFIGURAÇÕES DO DISPOSITIVO ---
// Altere estes valores para simular diferentes motos/locais
#define ID_MOTO "MOTO003"
#define LOCALIZACAO "Liberada - Pátio A"

// --- CONFIGURAÇÕES DE REDE ---
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// --- CONFIGURAÇÕES MQTT ---
const char* mqtt_server = "broker.hivemq.com"; // Broker MQTT público
const int mqtt_port = 1883;
const char* mqtt_topic = "motthru/telemetria"; // Tópico para publicar os dados

// --- CLIENTES ---
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// --- PINOS (PINS) ---
const int trigPin = 5;
const int echoPin = 18;
const int ledPin = 0;
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  dht.begin();

  connectToWiFi();
  mqttClient.setServer(mqtt_server, mqtt_port); // Configura o servidor MQTT
}

void loop() {
  // Se não estiver conectado ao MQTT, tenta reconectar
  if (!mqttClient.connected()) {
    reconnectMQTT();
  }
  mqttClient.loop(); // Mantém a conexão MQTT ativa

  long duration = readUltrasonicDistance();
  float distance = duration * 0.034 / 2;

  Serial.print("Distância: ");
  Serial.println(distance);

  if (distance < 30) {
    digitalWrite(ledPin, HIGH);

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Falha ao ler o sensor DHT!");
      return;
    }

    // Cria o payload JSON com todos os dados
    String payload = "{\"id_moto\":\"" + String(ID_MOTO) + "\","
                     "\"status\":\"Detectado\","
                     "\"localizacao\":\"" + String(LOCALIZACAO) + "\","
                     "\"temperatura\":" + String(temperature) + ","
                     "\"umidade\":" + String(humidity) + "}";

    Serial.println("Publicando no MQTT: " + payload);
    
    // Publica a mensagem no tópico MQTT
    mqttClient.publish(mqtt_topic, payload.c_str());

    delay(5000); // Espera 5 segundos antes da próxima detecção
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(500);
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void reconnectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Tentando conectar ao MQTT broker...");
    // Tenta conectar com um ID de cliente único
    String clientId = "ESP32Client-" + String(ID_MOTO);
    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("conectado!");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

long readUltrasonicDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
}
