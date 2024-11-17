#define BLYNK_TEMPLATE_ID "Your_Template_ID"
#define BLYNK_TEMPLATE_NAME "Your_Template_Name"
#define BLYNK_AUTH_TOKEN "Your_Auth_Token"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define PIR_PIN D1           // PIR sensor OUT pin connected to D1
#define LED_PIN D2           // LED connected to D2 for feedback
#define BUZZER_PIN D5        // Buzzer connected to D5

char ssid[] = "Your_WiFi_SSID";        // Replace with your Wi-Fi SSID
char pass[] = "Your_WiFi_PASSWORD";    // Replace with your Wi-Fi Password

void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);   // Initialize Blynk connection
}

void loop() {
  Blynk.run();                     
  int pirState = digitalRead(PIR_PIN);  

  if (pirState == HIGH) {   
    Serial.println("Motion Detected!");
    digitalWrite(LED_PIN, HIGH);       
    tone(BUZZER_PIN, 1000);           
    Blynk.logEvent("motion_detected", "Motion Detected!");
    Blynk.virtualWrite(V1, 255);       
  } else {
    Serial.println("No Motion");
    digitalWrite(LED_PIN, LOW);        
    noTone(BUZZER_PIN);                
    Blynk.virtualWrite(V1, 0);         
  }
  
  delay(500);  
}