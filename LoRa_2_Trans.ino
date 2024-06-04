#include <SoftwareSerial.h>
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#include <WiFi.h>

#define WIFI_SSID "177.3 BHN"
#define WIFI_PASSWORD "177buihuunghia"
#define FIREBASE_AUTH "WbQ1TYNlDBZN3x2LWOJBP64ZfvizYCq2Fw2k1HRN"
#define FIREBASE_HOST "https://ledtest-84bdb-default-rtdb.asia-southeast1.firebasedatabase.app/"

SoftwareSerial mySerial(17, 5); //RX nối với TX(lora), TX - RX(lora)

#define M0 19
#define M1 18
#define LED 13
#define trig 14    // chân trig của HC-SR04
#define echo 27    // chân echo của HC-SR04
// M0, M1 đấu với gnd: Normal mode
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
  pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  pinMode(M0, OUTPUT);        
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);       // Set 2 chân M0 và M1 xuống LOW 
  digitalWrite(M1, LOW);       // để hoạt động ở chế độ Normal
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".\n");
    delay(300);
}
Serial.printf("CONNECTED SUCCESFULLY!");

Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.reconnectWiFi(true);

Firebase.setReadTimeout(fbdo, 1000*60);
Firebase.setwriteSizeLimit(fbdo, "tiny");
}

void loop()
{
  unsigned long duration; // biến đo thời gian
  int distance;
  int data;           // biến lưu khoảng cách
  digitalWrite(trig,0);   // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig,1);   // phát xung từ chân trig
  delayMicroseconds(5);   // xung có độ dài 5 microSeconds
  digitalWrite(trig,0);   // tắt chân trig
  duration = pulseIn(echo,HIGH);  
  distance = int(duration/2/29.412);
  if(distance < 20 ) data = 1;
  else data = 0;
  Firebase.setInt(fbdo, "/Sensor/data", data);
  /*
     Đọc dữ liệu  từ cổng Serial monitor
     Gửi dữ liệu đi bằng uart Lora
  */
  mySerial.println(String(data));
  delay(500);
}
