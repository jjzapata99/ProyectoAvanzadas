#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

//Configuracion de conexion wifi
const char* ssid = "Kenyi Panchana";
const char* password = "kenyi2603";

//Conexion con servidor MQTT
const char* mqtt_server = "192.168.3.28";

//Configuraciones inciales
void setup()
{
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  //Agregar codico adicional
}

//Configuracion para conexion wifi
void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Conectado a ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
   delay(500);
   Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Conectado!");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}

//
void callback(char* topic, byte* message, unsigned int length)
{
  Serial.print("Mensage recibido en topic: ");
  Serial.print(topic);
  Serial.print(", Message: ");
  String messageTemp;
  for (int i = 0; i < length; i++){
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
} 

//RECONEXION
void reconnect()
{
  while(!client.connected())
  {
    Serial.print("INTENTANDO CONEXION MQTT");
    if(client.connect("ESPCLIENT")){
      Serial.print("conectado");
      client.subscribe("panico");
    }
    else{
      Serial.print("fallo, rc =");
      Serial.print(client.state());
      Serial.println("intentelo de nuevo en 5s");
      delay(5000);
    }    
  }
} 

//VOID LOOP
void loop()
{
  if(!client.connected()){
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 4000) {
    lastMsg = now;

    client.publish("panico", "true"); //topic name (to which this ESP32 publishes its data). 37 is the dummy value.
    
  }
}
