#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const char* ssid = "";
const char* password = "";
const char* mqtt_server = "10.0.3.201";
const char* mqtt_user = "";
const char* mqtt_password = "";
const char* mqtt_topic = "Sensor Infrarrojo";

const int pinEntrada = 2;
volatile unsigned long codigo = 0;
volatile bool recibido = false;

// Definir un diccionario que mapea códigos infrarrojos a mensajes MQTT
const unsigned long codigosMensajes[][2] = {
  {4278238976, "Prendido/Apagado"},
  {4261527296, "Vol+"},
  {4244815616, "Func/Stop"},
  {4211392256, "|<<"},
  {4194680576, ">||"},
  {4177968896, ">>|"},
  {4144545536, "Abajo"},
  {4127833856, "Vol-"},
  {4111122176, "Arriba"},
  {4060987136, "EQ"},
  {4044275456, "ST/REPT"},
  {4077698816, "0"},
  {4010852096, "1"},
  {3994140416, "2"},
  {3977428736, "3"},
  {3944005376, "4"},
  {3927293696, "5"},
  {3910582016, "6"},
  {3877158656, "7"},
  {3860446976, "8"},
  {3843735296, "9"},
};

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  attachInterrupt(digitalPinToInterrupt(pinEntrada), recibir, CHANGE);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (recibido) {
    for (unsigned int i = 0; i < sizeof(codigosMensajes) / sizeof(codigosMensajes[0]); i++) {
      if (codigo == codigosMensajes[i][0]) {
        enviarMQTT("boton/presionado", codigosMensajes[i][1]);
        break;
      }
    }
    recibido = false;
  }
}

void recibir() {
  static unsigned long startTime = 0;
  static unsigned int contarBits = 0;

  if (digitalRead(pinEntrada) == HIGH) {
    startTime = micros();
  } else {
    unsigned long elapsedTime = micros() - startTime;
    if (elapsedTime > 2000) {
      contarBits = 0;
      codigo = 0;
    } else if (elapsedTime > 1000) {
      codigo |= (1UL << contarBits);
      contarBits++;
    } else {
      contarBits++;
    }

    if (contarBits == 32) {
      recibido = true;
    }
  }
}

void enviarMQTT(const char* topic, const char* message) {
  if (client.publish(topic, message)) {
    Serial.print("Publicado en el topic: ");
    Serial.println(topic);
    Serial.print("Mensaje: ");
    Serial.println(message);
  } else {
    Serial.println("Error al publicar en MQTT");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando al servidor MQTT...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("conectado");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Error al conectarse a MQTT, rc=");
      Serial.print(client.state());
      Serial.println(" Intentando nuevamente...");
      delay(3000);
    }
  }
}
