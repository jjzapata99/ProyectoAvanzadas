#include <WiFi.h>
#include <ESP32Ping.h>
#include <stdio.h>
#include <HTTPClient.h>

#define ADC_VREF_mV    3300.0 
#define ADC_RESOLUTION 4096.0
#define PIN_LM35       35

String list[255];
const char* ssid = "Lab_Avanzadas";
const char* password =  "la1bo2ra3to4ri5o";
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  
 }
  
 
void loop() {
  while(1){
  scan();
  int adcVal = analogRead(PIN_LM35);
    float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
    float tempC = milliVolt / 10;
    float tempF = tempC * 9 / 5 + 32;
     Serial.print("Temperature: ");
  Serial.print(tempC);   // print the temperature in °C
  Serial.print("°C");
  
  }
}
void scan(){
  unsigned long period=200; //En Milisegundos

    static unsigned long previousMillis=0;

    if((millis()-previousMillis)>period){
    
  WiFiClient client;
  HTTPClient http;
  int x =200 ;
  
  while (x <= 255){
    String comando = "200.126.14." + String (x);
    Serial.print(comando);
    bool success = Ping.ping( comando.c_str(), 1);  
    x+=1;
    if(!success){
    Serial.println("Ping failed");
    http.begin(client, "https://d5c9-157-100-105-67.sa.ngrok.io/address?ip="+comando);
      int codigo_respuesta =http.GET();
      if(codigo_respuesta>0){
      Serial.println("Código HTTP ► " + String(codigo_respuesta));   //Print return code

      if(codigo_respuesta == 200){
        String cuerpo_respuesta = http.getString();
        Serial.println("El servidor respondió ▼ ");
        Serial.println(cuerpo_respuesta);

      }

    }else{

     Serial.print("Error enviando GET, código: ");
     Serial.println(codigo_respuesta);

    }
  }
  else{ 
  Serial.println("Ping succesful.");
 
  
  
  }
 
  }

   previousMillis += period;
    }  
}
void prueba(){

  unsigned long period=500; //En Milisegundos

    static unsigned long previousMillis=0;

    if((millis()-previousMillis)>period){

    int adcVal = analogRead(PIN_LM35);
    float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
    float tempC = milliVolt / 10;
    float tempF = tempC * 9 / 5 + 32;

    Serial.print("Temperature: ");
    Serial.print(tempC);   // print the temperature in °C
    Serial.print("°C");
    Serial.print("  ~  "); // separator between °C and °F
    Serial.print(tempF);   // print the temperature in °F
    Serial.println("°F");

    delay(500);
        
        
        
        
        
        
        
        
        previousMillis += period;
    }  
}
