String myAPIkey = "0D8JS57OEP8UZW9T"; 
#include <SoftwareSerial.h> 
#include <Wire.h>  
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
SoftwareSerial ESP8266(2, 3); 

#define led1 5 
#define led2 6 
#define led3 9 
#define led4 10 
 
#define ir1 4 
#define ir2 7 
#define ir3 A2 
#define ir4 A3 
 
#define s1 A0 
#define s2 A1 
#define s3 8 
#define s4 11 
#define ldr 12 
 
int ir11;
int ir22; 
int ir33; 
int ir44; 
int s11; 
int s22; 
int s33; 
int s44; 
int llddrr; 
long writingTimer = 30;  
long startTime = 0; 
long waitTime = 0; 
unsigned char check_connection=0; 
unsigned char times_check=0; 
boolean error; 
int s444; 
int s111;
int s222;
int s333; 

void readSensors(void) 
{ 
  ir11=digitalRead(ir1); 
  ir22=digitalRead(ir2); 
  ir33=digitalRead(ir3); 
  ir44=digitalRead(ir4); 
  llddrr=digitalRead(ldr); 
 
  s11=digitalRead(s1); 
  s22=digitalRead(s2); 
  s33=digitalRead(s3); 
  s44=digitalRead(s4); 
  Serial.println(llddrr); 
   
  if(llddrr==1){ 
    analogWrite(led1,0); 
    analogWrite(led2,0); 
    analogWrite(led3,0); 
    analogWrite(led4,0); 
  } 
  else 
  { 
    if(s11==0){ 
      s111=1; 
      if(ir11==0){ 
        analogWrite(led1,250); 
      } 
      else 
      { 
        analogWrite(led1,10); 
      } 
      lcd.setCursor(0,1); 
      lcd.print(s111); 
    } 
    else 
    { 
      s111=0;
      analogWrite(led1,10);
      lcd.setCursor(0,1); 
      lcd.print(s111);  
    } 
    if(s22==0){ 
      s222=1; 
      if(ir22==0){ 
        analogWrite(led2,250); 
      } 
      else 
      { 
        analogWrite(led2,10); 
      } 
      lcd.setCursor(5,1); 
      lcd.print(s222); 
    } 
    else 
    { 
      s222=0;
      analogWrite(led2,10);
      lcd.setCursor(5,1); 
      lcd.print(s222);  
    }  
    if(s33==0){ 
      s333=1; 
      if(ir33==0){ 
        analogWrite(led3,250); 
      } 
      else 
      { 
        analogWrite(led3,10); 
      } 
      lcd.setCursor(10,1); 
      lcd.print(s333); 
    } 
    else 
    { 
      s333=0;
      analogWrite(led3,10);
      lcd.setCursor(10,1); 
      lcd.print("0");  
    } 
    if(s44==0){ 
      s444=1; 
      if(ir44==0){ 
        analogWrite(led4,250); 
      } 
      else 
      { 
        analogWrite(led4,10);
      } 
      lcd.setCursor(15,1); 
      lcd.print(s444); 
    } 
    else 
    { 
      s444=0; 
      analogWrite(led4,10); 
      lcd.setCursor(15,1); 
      lcd.print(s444); 
    }
  }  
} 
void setup() { 
  pinMode(led1,OUTPUT); 
  pinMode(led2,OUTPUT); 
  pinMode(led3,OUTPUT); 
  pinMode(led4,OUTPUT); 
  pinMode(ir1,INPUT); 
  pinMode(ir2,INPUT); 
  pinMode(ir3,INPUT); 
  pinMode(ir4,INPUT); 
  pinMode(s1,INPUT_PULLUP); 
  pinMode(s2,INPUT_PULLUP); 
  pinMode(s3,INPUT_PULLUP); 
  pinMode(s4,INPUT_PULLUP); 
  pinMode(ldr,INPUT); 
  analogWrite(led1,10); 
  analogWrite(led2,10); 
  analogWrite(led3,10); 
  analogWrite(led4,10); 
  Serial.begin(9600); 
  ESP8266.begin(9600); 
  lcd.begin(); 
  lcd.backlight(); 
  lcd.clear(); 
  lcd.print("Connecting to"); 
  lcd.setCursor(0,1); 
  lcd.print("HAVASYA"); 
  delay(1000); 
  startTime = millis();  
  ESP8266.println("AT+RST"); 
  delay(2000); 
  Serial.println("Connecting to Wifi"); 
   
  while(check_connection==0) 
  { 
    Serial.print("."); 
    ESP8266.print("AT+CWJAP=\"HAVASYA\",\"Havasya_9\"\r\n"); 
    ESP8266.setTimeout(5000); 
    if(ESP8266.find("OK\r\n")==1) 
    { 
      Serial.println("WIFI CONNECTED"); 
      break; 
    } 
    times_check++; 
    if(times_check>3)  
    { 
      times_check=0; 
      Serial.println("Trying to Reconnect.."); 
      lcd.clear(); 
      lcd.print("Trying to Reconnect"); 
    } 
  } 
  lcd.clear(); 
  lcd.print("WiFi connected"); 
  delay(2000); 
  lcd.clear(); 
  lcd.print("IoT BSD HIGHWAY"); 
  lcd.setCursor(0,1); 
  lcd.print("Light Cntrl SYS"); 
  delay(1000); 
  lcd.clear(); 
  lcd.print("S1   S2   S3  S4"); 
  lcd.setCursor(0,1); 
  lcd.print("1    1    1    1"); 
} 
 
void loop()
{
    readSensors();

    waitTime = millis() - startTime;

    if (waitTime > (writingTimer * 1000))
    {
        writeThingSpeak();
        startTime = millis();
    }

    delay(1000);
}

void writeThingSpeak(void) 
{ 
  startThingSpeakCmd(); 
  // preparacao da string GET 
  String getStr = "GET /update?api_key="; 
  getStr += myAPIkey; 
  getStr +="&field1="; 
  getStr += String(s111); 
  getStr +="&field2="; 
  getStr += String(s222); 
  getStr +="&field3="; 
  getStr += String(s333); 
  getStr +="&field4="; 
  getStr += String(s444); 
  getStr += "\r\n\r\n"; 
  GetThingspeakcmd(getStr);  
}
void startThingSpeakCmd(void) 
{ 
  ESP8266.flush(); 
  String cmd = "AT+CIPSTART=\"TCP\",\""; 
  cmd += "184.106.153.149"; // api.thingspeak.com IP address 
  cmd += "\",80"; 
  ESP8266.println(cmd); 
  Serial.print("Start Commands: "); 
  Serial.println(cmd); 
  if(ESP8266.find("Error")) 
  { 
    Serial.println("AT+CIPSTART error"); 
    return; 
  } 
} 
String GetThingspeakcmd(String getStr) 
{ 
  String cmd = "AT+CIPSEND="; 
  cmd += String(getStr.length()); 
  ESP8266.println(cmd); 
  Serial.println(cmd); 
 
  if(ESP8266.find(">")) 
  { 
    ESP8266.print(getStr); 
    Serial.println(getStr); 
    delay(500);
    String messageBody = ""; 
    while (ESP8266.available())  
    { 
      String line = ESP8266.readStringUntil('\n'); 
      if (line.length() == 1)  
      {  
        messageBody = ESP8266.readStringUntil('\n'); 
      } 
    } 
    Serial.print("MessageBody received: "); 
    Serial.println(messageBody); 
    return messageBody; 
  } 
  else 
  { 
    ESP8266.println("AT+CIPCLOSE");      
    Serial.println("AT+CIPCLOSE");  
  } 