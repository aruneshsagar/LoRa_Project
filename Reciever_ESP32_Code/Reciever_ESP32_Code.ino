#include <WiFi.h>
#include <FirebaseESP32.h>


#define FIREBASE_HOST "https://agriculture-lora-sensor-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "3nFEYLzqBunTN6TMEkaWIxu9Mvh2VSZCQOQVL4sc"
#define WIFI_SSID "Airtel_Fibernet"
#define WIFI_PASSWORD "air93338"


//Define FirebaseESP32 data object
FirebaseData firebaseData;
FirebaseJson json;
#include <LoRa.h>
#include <SPI.h>

#define SS 5
#define RST 14
#define DIO0 2


#define BAND 433E6
 

int rssi;
String loRaMessage;
String phValue0;
String temperature0;
String humidity0;
String soiltemp0;
String soilMoist0;
String nitrogen0;
String phosphorous0;
String potassium0;
String readingID;
String phValue1;

String temperature1;
String humidity1;
String soiltemp1;
String soilMoist1;
String nitrogen1;
String phosphorous1;
String potassium1;

String temperature2;
String humidity2;
String phValue2;
String soiltemp2;
String soilMoist2;
String nitrogen2;
String phosphorous2;
String potassium2;

String temperature3;
String humidity3;
String soiltemp3;
String soilMoist3;
String nitrogen3;
String phosphorous3;
String potassium3;
String phValue3;

String temperature4;
String humidity4;
String soiltemp4;
String soilMoist4;
String phValue4;
String nitrogen4;
String phosphorous4;
String potassium4;


String temperature5;
String humidity5;
String soiltemp5;
String soilMoist5;
String phValue5;

String temperature6;
String humidity6;
String soiltemp6;
String soilMoist6;
String temperature7;
String humidity7;
String soiltemp7;
String soilMoist7;
String temperature8;
String humidity8;
String soiltemp8;
String soilMoist8;
String temperature9;
String humidity9;
String soiltemp9;
String soilMoist9;




void startLoRA(){
  int counter;
  //SPI LoRa pins
//  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  while (!LoRa.begin(BAND) && counter < 10) {
    Serial.print(".");
    counter++;
    delay(500);
  }
  if (counter == 10) {
    // Increment readingID on every new reading
    Serial.println("Starting LoRa failed!"); 
  }
  Serial.println("LoRa Initialization OK!");
}
void getLoRaData() {
  Serial.print("Lora packet received: ");
  // Read packet
  while (LoRa.available()) {
    String LoRaData = LoRa.readString();
    // LoRaData format: readingID/temperature&soilMoisture#batterylevel
    // String example: 1/27.43&654#95.34
    Serial.print(LoRaData); 
    
    // Get readingID, temperature and soil moisture
    int pos1 = LoRaData.indexOf('/');
    int pos2 = LoRaData.indexOf('&');
    int pos3 = LoRaData.indexOf('#');
    int pos4 = LoRaData.indexOf('!');
    int pos5 = LoRaData.indexOf('@');
    int pos6 = LoRaData.indexOf('%');
    int pos7 = LoRaData.indexOf('^');
    int pos8 = LoRaData.indexOf('*');
    readingID = LoRaData.substring(0, pos1);
    if (readingID =="1"){
    temperature0 = LoRaData.substring(pos1 +1, pos2);
    humidity0 = LoRaData.substring(pos2+1, pos3);
    soiltemp0 = LoRaData.substring(pos3+1, pos4);
    soilMoist0 = LoRaData.substring(pos4+1, pos5);
    nitrogen0 = LoRaData.substring(pos5+1, pos6);
    phosphorous0 = LoRaData.substring(pos6+1, pos7);
    potassium0 = LoRaData.substring(pos7+1, pos8);
    phValue0 = LoRaData.substring(pos8+1, LoRaData.length());}
   if(readingID =="2"){
    temperature1 = LoRaData.substring(pos1 +1, pos2);
    humidity1 = LoRaData.substring(pos2+1, pos3);
   soiltemp1 = LoRaData.substring(pos3+1, pos4);
    soilMoist1 = LoRaData.substring(pos4+1, pos5);
    nitrogen1 = LoRaData.substring(pos5+1, pos6);
    phosphorous1 = LoRaData.substring(pos6+1, pos7);
    potassium1 = LoRaData.substring(pos7+1, pos8);
    phValue1 = LoRaData.substring(pos8+1, LoRaData.length());}
    if(readingID =="3"){
    temperature2 = LoRaData.substring(pos1 +1, pos2);
    humidity2 = LoRaData.substring(pos2+1, pos3);
   soiltemp2 = LoRaData.substring(pos3+1, pos4);
    soilMoist2 = LoRaData.substring(pos4+1, pos5);
    nitrogen2 = LoRaData.substring(pos5+1, pos6);
    phosphorous2 = LoRaData.substring(pos6+1, pos7);
    potassium2 = LoRaData.substring(pos7+1, pos8);
    phValue2 = LoRaData.substring(pos8+1, LoRaData.length());}
    if(readingID =="4"){
    temperature3 = LoRaData.substring(pos1 +1, pos2);
    humidity3 = LoRaData.substring(pos2+1, pos3);
   soiltemp3 = LoRaData.substring(pos3+1, pos4);
    soilMoist3 = LoRaData.substring(pos4+1,pos5);
    phValue3 = LoRaData.substring(pos8+1, LoRaData.length());
    nitrogen3 = LoRaData.substring(pos5+1, pos6);
    phosphorous3 = LoRaData.substring(pos6+1, pos7);
    potassium3 = LoRaData.substring(pos7+1, pos8);
   
    }
    if(readingID =="5"){
    temperature4 = LoRaData.substring(pos1 +1, pos2);
    humidity4 = LoRaData.substring(pos2+1, pos3);
   soiltemp4 = LoRaData.substring(pos3+1, pos4);
    soilMoist4 = LoRaData.substring(pos4+1, pos5);
    phValue4 = LoRaData.substring(pos8+1, LoRaData.length());
    
    }
   if(readingID =="6"){
    temperature5 = LoRaData.substring(pos1 +1, pos2);
    humidity5 = LoRaData.substring(pos2+1, pos3);
   soiltemp5= LoRaData.substring(pos3+1, pos4);
    soilMoist5 = LoRaData.substring(pos4+1, LoRaData.length());}
   if(readingID =="7"){
    temperature6 = LoRaData.substring(pos1 +1, pos2);
    humidity6 = LoRaData.substring(pos2+1, pos3);
   soiltemp6= LoRaData.substring(pos3+1, pos4);
    soilMoist6 = LoRaData.substring(pos4+1, LoRaData.length());}
   if(readingID =="8"){
    temperature7 = LoRaData.substring(pos1 +1, pos2);
    humidity7 = LoRaData.substring(pos2+1, pos3);
   soiltemp7 = LoRaData.substring(pos3+1, pos4);
    soilMoist7 = LoRaData.substring(pos4+1, LoRaData.length());}
   if(readingID =="9"){
    temperature8 = LoRaData.substring(pos1 +1, pos2);
    humidity8 = LoRaData.substring(pos2+1, pos3);
   soiltemp8= LoRaData.substring(pos3+1, pos4);
    soilMoist8 = LoRaData.substring(pos4+1, LoRaData.length());}
   if(readingID =="10"){
    temperature9 = LoRaData.substring(pos1 +1, pos2);
    humidity9 = LoRaData.substring(pos2+1, pos3);
   soiltemp9 = LoRaData.substring(pos3+1, pos4);
    soilMoist9 = LoRaData.substring(pos4+1, LoRaData.length());}
   
   

    
  }
  // Get RSSI
  rssi = LoRa.packetRssi();
  Serial.print(" with RSSI ");    
  Serial.println(rssi);
}


void setup()
{ 
  Serial.begin(115200);
 

 


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
   startLoRA();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  /*
  This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
  Firewall that allows only GET and POST requests.
  
  Firebase.enableClassicRequest(firebaseData, true);
  */

  //String path = "/data";
  

  Serial.println("------------------------------------");
  Serial.println("Connected...");
  
}

void loop()
{int packetSize = LoRa.parsePacket();    // try to parse packet
  if (packetSize) 
  {
    getLoRaData();
}
    
 
  json.set("/Temperature:", temperature0);
  json.set("/Humidity:", humidity0);
  json.set("/Soil Temperature:", soiltemp0);
  json.set("/Soil Moisture:", soilMoist0);
  json.set("/Nitrogen:", nitrogen0);
  json.set("/Phosphorous:", phosphorous0);
  json.set("/Potassium:", potassium0);
