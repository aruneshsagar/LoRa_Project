#include "DHT.h"
#include <SPI.h>
#include <LoRa.h>
#include "DFRobot_SHT20.h"
DFRobot_SHT20 sht20(&Wire, SHT20_I2C_ADDR);
#define DHTPIN 4
#define DHTTYPE DHT11  // DHT 11
DHT dht(DHTPIN, DHTTYPE);
#include <SoftwareSerial.h>
#define RE 8
#define DE 7
#include <SimpleTimer.h>
//define the pins used by the LoRa transceiver module
//#define SCK 13
//#define MISO 12
//#define MOSI 11
#define SS 10
#define RST 9
#define DIO0 2

//433E6 for Asia
//866E6 for Europe
//915E6 for North America
#define BAND 433E6
SimpleTimer timer;
 
float calibration_value = 21.34 - 0.7;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;
 
float ph_act;

const byte nitro[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

byte values[11];
SoftwareSerial mod(5,6);



//packet counter
int readingID = 4;

int counter = 0;
String LoRaMessage = "";

String phValue0;
String temperature0;
String humidity0;
String soiltemp0;
String soilMoist0;
String nitrogen0;
String phosphorous0;
String potassium0;




//Initialize LoRa module
void startLoRA(){
  //SPI LoRa pins
  //SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  while (!LoRa.begin(BAND) && counter < 10) {
    Serial.print(".");
    counter++;
    delay(500);
  }
  if (counter == 10) {
    // Increment readingID on every new reading
    readingID++;
    Serial.println("Starting LoRa failed!"); 
  }
  Serial.println("LoRa Initialization OK!");
  delay(2000);
}


void getReadings(){
  temperature0 = dht.readTemperature();
  Serial.print("TEMP- ");
  Serial.println(temperature0);
  humidity0 = dht.readHumidity();
  Serial.print("HUM- ");
  Serial.println(humidity0);
  soiltemp0 =sht20.readTemperature();
  Serial.print("SOIL TEMP- ");
  Serial.println(soiltemp0);
  soilMoist0 = sht20.readHumidity();
  Serial.print("SOIL HUM- ");
  Serial.println(soilMoist0);
  nitrogen0 = nitrogen();
  delay(250);
  phosphorous0 = phosphorous();
  delay(250);
  potassium0 = potassium();
  delay(250);
//  timer.run(); // Initiates SimpleTimer
 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6; 
  ph_act = (-5.70 * volt + calibration_value);
  phValue0= ph_act;
 Serial.print("pH Val: ");
 Serial.println(ph_act);
 delay(1000);
//  nitrogen0;
//  phosphorus0;
//  potassium0;
//  phValue0;

}
void sendReadings() {
  LoRaMessage = String(readingID) + "/" +String(temperature0) + "&" + String(humidity0) + "#" + String(soiltemp0) + "!" + String(soilMoist0) + "@" + String(nitrogen0) + "%" + String(phosphorous0) + "^" + String(potassium0) + "*" + String(phValue0);
  //Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  Serial.println(LoRaMessage);
  LoRa.endPacket();
}
void setup() {
  //initialize Serial Monitor
  Serial.begin(9600);
  mod.begin(9600);
  sht20.initSHT20();
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  startLoRA();
  dht.begin();
  sht20.checkSHT20();
  
}
void loop() {
  Serial.println("NODE 2");
  getReadings();
  Serial.println("check 1");
  sendReadings();
  Serial.println("check 2");
  
}
byte nitrogen(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(nitro,sizeof(nitro))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
 
byte phosphorous(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(phos,sizeof(phos))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
 
byte potassium(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(pota,sizeof(pota))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
