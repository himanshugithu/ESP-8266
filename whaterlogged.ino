#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#define TRIG_PIN D4  // Pin connected to the TRIG pin of the ultrasonic sensor
#define ECHO_PIN D5

const char* ssid = "pass : FFH"; //--> Your wifi name or SSID.
const char* password = "11111111"; //--> Your wifi password.
#define ON_Board_LED 2
 
//----------------------------------------Host & httpsPort
const char* host = "script.google.com";
const int httpsPort = 443;
#define pushButton D8
//----------------------------------------
 
WiFiClientSecure client; //--> Create a WiFiClientSecure object.
 
String GAS_ID = "AKfycbwdXRW0xf1ZTwLK0yZqFenbyv2DxCvr1PSNTjet38Hzb_N_W0XyeuOxPxBJfRnG6zeYCw"; //--> spreadsheet script ID
//https://script.google.com/macros/s/AKfycbyHyNrqt44cHPsrncU5doKCupRV-ALXKIqQ9MaikU1WEv7BoQJDDi_hjyblqBHeUf-U7A/exec
//https://script.google.com/macros/s/AKfycbwdXRW0xf1ZTwLK0yZqFenbyv2DxCvr1PSNTjet38Hzb_N_W0XyeuOxPxBJfRnG6zeYCw/exec
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(pushButton, INPUT);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  delay(500);  
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------
 
  client.setInsecure();
}
 
void loop() {
  int buttonState = digitalRead(pushButton);
  if(buttonState == 0)
  {  
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * 0.0343) / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if(distance <= 30)
  {
    digitalWrite(D0,HIGH);
    digitalWrite(D1,LOW);
  }
  else
  {
    digitalWrite(D0,LOW);
    digitalWrite(D1,HIGH);
  }
  sendData(distance); //--> Calls the sendData Subroutine
}
else{digitalWrite(D0,LOW);
    digitalWrite(D1,LOW);}
}
// Subroutine for sending data to Google Sheets
void sendData(int distance) {
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);
  
  //----------------------------------------Connect to Google host
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  //----------------------------------------
 
  //----------------------------------------Processing data and sending data
  
  String url = "/macros/s/" + GAS_ID + "/exec?temperature=" + (String)distance;
  Serial.print("requesting URL: ");
  Serial.println(url);
 
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");
 
  Serial.println("request sent");
  //----------------------------------------
 
  //----------------------------------------Checking whether the data was sent successfully or not
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();
  //----------------------------------------
}

/*
function doGet(e) { 
Logger.log( JSON.stringify(e) );
var result = 'Ok';
if (e.parameter == 'undefined') {
result = 'No Parameters';
}
else {
var sheet_id = '1eRGdUS3ytQ27gRKq_QH8eiJaNSG3im1kBDcn1GMDgVs'; // Spreadsheet ID
var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();
var newRow = sheet.getLastRow() + 1; 
var rowData = [];

var Curr_Date = new Date();
rowData[0] = Curr_Date; // Date in column A
var Curr_Time = Utilities.formatDate(Curr_Date,"Asia/Kolkata", 'HH:mm:ss');


rowData[1] = Curr_Time; // Time in column B
for (var param in e.parameter) {
Logger.log('In for loop, param=' + param);
var value = stripQuotes(e.parameter[param]);
Logger.log(param + ':' + e.parameter[param]);
switch (param) {
case 'temperature':
rowData[2] = value; // Temperature in column C
result = 'Temperature Written on column C'; 
break;
case 'humidity':
rowData[3] = value; // Humidity in column D
result += ' ,Humidity Written on column D'; 
break; 
default:
result = "unsupported parameter";
}
}
Logger.log(JSON.stringify(rowData));
var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
newRange.setValues([rowData]);
}
return ContentService.createTextOutput(result);
}
function stripQuotes( value ) {
return value.replace(/^["']|['"]$/g, "");
}

*/
