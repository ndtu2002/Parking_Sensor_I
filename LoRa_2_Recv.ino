#include <SoftwareSerial.h>
SoftwareSerial mySerial(6, 7); //RX nối với TX(lora), TX - RX(lora)

#define M0 9
#define M1 8
#define LED 13
// M0, M1 đấu với gnd: Normal mode

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  pinMode(M0, OUTPUT);        
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);       // Set 2 chân M0 và M1 xuống LOW 
  digitalWrite(M1, LOW);       // để hoạt động ở chế độ Normal
}

void loop()
{
  /*
     Đọc dữ liệu  từ cổng Serial monitor
     Gửi dữ liệu đi bằng uart Lora
  */
  String data = "";
  if (mySerial.available() > 0)
  {
    data = mySerial.readStringUntil('\n');
    Serial.println(data);
    int x = data.toInt();
    digitalWrite(LED, x);
  }
  
  delay(500);
}
