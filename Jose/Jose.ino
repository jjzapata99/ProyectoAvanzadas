#include <WiFi.h>
#include <ESP32Ping.h>
#include <stdio.h>
#include <HTTPClient.h>

#define ADC_VREF_mV    3300.0 
#define ADC_RESOLUTION 4096.0
#define PIN_LM35       35

TaskHandle_t Task1;
TaskHandle_t Task2;

const char* ssid = "Lab_Avanzadas";
const char* password =  "la1bo2ra3to4ri5o";


void Task1code(void * pvParameters){
  
  for(;;){
  WiFiClient client;
  HTTPClient http;
  int x =200 ;
  
  while (x <= 255){
    String comando = "200.126.14." + String (x);
    Serial.println(comando);
    bool success = Ping.ping( comando.c_str(), 1);  
    x+=1;
    if(!success){
    Serial.println("Ping failed");
    http.begin(client, "http://200.126.14.228:8800/address/off?ip="+comando);
    http.GET();
    
  }
  else{ 
  Serial.println("Ping succesful.");
 
  http.begin(client, "http://200.126.14.228:8800/address/on?ip="+comando);
  http.GET();
  
  }
 
  }

   
}
}
void Task2code(void * pvParameters){
  for(;;){
  WiFiClient client;
  HTTPClient http;
   
    int adcVal = analogRead(PIN_LM35);
    float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
    float tempC = milliVolt / 10;
    Serial.println(tempC);
    http.begin(client, "http://200.126.14.228:8800/temperature?degrees="+String(tempC));
    http.GET();
    delay(1500);
}
}






void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  xTaskCreatePinnedToCore(
                    Task1code,  
                    "scan",   
                    10000,     
                    NULL,       
                    1,          
                    &Task1,     
                    0);                            
  delay(500); 
  xTaskCreatePinnedToCore(
                    Task2code, 
                    "sense",    
                    10000,       
                    NULL,        
                    1,           
                    &Task2,     
                    1);          
    delay(5000); 
}
  
 
 
void loop() {
  
}
