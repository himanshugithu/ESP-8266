#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t broadcastAddress[] = { 0x30, 0x83, 0x98, 0x83, 0x1D, 0xF8 };  //master adderess

#define BOARD_ID 3  // Set your Board ID (ESP32 Sender #1 = BOARD_ID 1, ESP32 Sender #2 = BOARD_ID 2, etc)

// Structure example to send data
typedef struct struct_message {
  int id;
  int x;
  int y;
  String status;
} struct_message;

struct_message myData;  // Create a struct_message called test to store variables to be sent


// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) 
{
  Serial.print("\r\nLast Packet Send Status: ");
  if (sendStatus == 0)
   {
     Serial.println("Delivery success");
   } 
  else
    {
     Serial.println("Delivery fail");
    }
}

void setup() {
 
  Serial.begin(115200); // Init Serial Monitor
  WiFi.mode(WIFI_STA);  // Set device as a Wi-Fi Station
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);  // Set ESP-NOW role
  esp_now_register_send_cb(OnDataSent);   // Once ESPNow is successfully init, we will register for Send CB to  // get the status of Trasnmitted packet

  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);  
}

void loop() {

  // Set values to send
  myData.id = BOARD_ID;
  myData.x  = analogRead1();
  Serial.print("sensor 1 :");
  Serial.println(myData.x);
  delay(200);
  myData.y  = analogRead2();
  Serial.print("sensor 2 :");
  Serial.println(myData.y);
  delay(200);  

  if(myData.x <700  )  //NIGHT ERROR
    {
      digitalWrite(D3, HIGH);
      myData.status = "ON";    
      
    }  
  // else if (myData.x<=750 && myData.y <=600 ) 
  // {
  //     digitalWrite(D3, HIGH);
  //     myData.status = "ON";
  // }

  else {
  digitalWrite(D3, LOW);
  myData.status = "OFF";
  }
  
  
  
  
  
      

  esp_now_send(0, (uint8_t *)&myData, sizeof(myData)); // Send message via ESP-NOW
  delay(500);
}


int analogRead1()
{
   digitalWrite(D1,HIGH);
   digitalWrite(D2,LOW);
   return analogRead(A0);
}

int analogRead2()
{
   digitalWrite(D1,LOW);
   digitalWrite(D2,HIGH);
   return analogRead(A0);
}





// if (myData.x >= 400 && myData.y >= 200) {
//    myData.status = "ERROR";
//    digitalWrite(D3, HIGH);
//   }

  
//   else if(myData.x >= 650 && myData.y <=25)
//   {
//     digitalWrite(D3, HIGH);
//     myData.status = "ON";
//   }

//   else if (myData.x <=100 && myData.y<=60) {
//       myData.status = "ERROR";
//   }
//   else {
//   digitalWrite(D3, LOW);
//    myData.status = "OFF";
//  }