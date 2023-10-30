#include <ESP8266WiFi.h>
#include <espnow.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(D6, D5, D4, D3, D2, D1);

typedef struct struct_message {
  int id;
  int x;
  int y;
  String status;
 } struct_message;

// Create a struct_message called myData  
struct_message myData;

// Create a structure to hold the readings from each board
struct_message board1;
struct_message board2;
struct_message board3;

// Create an array with all the structures
struct_message boardsStruct[3] = {board1, board2,board3};

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac_addr, uint8_t *incomingData, uint8_t len)
 {
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.printf("Board ID %u: %u bytes\n", myData.id, len);
  // Update the structures with the new incoming data
  boardsStruct[myData.id-1].x = myData.x;
  boardsStruct[myData.id-1].status = myData.status;
  //boardsStruct[myData.id-1].y = myData.y;
  Serial.printf("x value: %d \n", boardsStruct[myData.id-1].x);
  //Serial.printf("y value: %d \n", boardsStruct[myData.id-1].y);
  Serial.printf("status value: %s \n", boardsStruct[myData.id-1].status);
  Serial.println();

 }
 
void setup()
 {
 
  lcd.begin(16, 2);
  lcd.print("hello, world!");
  Serial.begin(115200);     // Initialize Serial Monitor  
  WiFi.mode(WIFI_STA);  // Set device as a Wi-Fi Station
  WiFi.disconnect();
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
  int board1X = boardsStruct[0].x;
  String board1status= boardsStruct[0].status;
 
  int board2X = boardsStruct[1].x;
  String board2status= boardsStruct[1].status;
  
  int board3X = boardsStruct[2].x;
  String board3status= boardsStruct[2].status;
lcd.clear();
  
lcd.setCursor(0, 0);
lcd.print(board1status);
lcd.setCursor(0, 1);
lcd.print("p1");

lcd.setCursor(5, 0);
lcd.print(board2status);
lcd.setCursor(5, 1);
lcd.print("p2");


lcd.setCursor(10, 0);
lcd.print(board3status);
lcd.setCursor(10, 1);
lcd.print("p3");
delay(500);
}


// Access the variables for each board
  /*int board1X = boardsStruct[0].x;
  int board1Y = boardsStruct[0].y;
  int board2X = boardsStruct[1].x;
  int board2Y = boardsStruct[1].y;
  */