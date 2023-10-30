#include <ESP8266WiFi.h>
#include <espnow.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(D5, D6, D0, D1, D2, D3);

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

// Create an array with all the structures
struct_message boardsStruct[2] = {board1, board2};

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
 // boardsStruct[myData.id-1].y = myData.y;
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

void loop(){
  
lcd.clear();
  lcd.setCursor(0,0);
lcd.print("POLE NO : 1");
  lcd.setCursor(0,1);
lcd.print("LED STATUS:");
  lcd.setCursor(11,1);
lcd.print(myData.status);

  delay(1000);

}


// Access the variables for each board
  /*int board1X = boardsStruct[0].x;
  int board1Y = boardsStruct[0].y;
  int board2X = boardsStruct[1].x;
  int board2Y = boardsStruct[1].y;
  */