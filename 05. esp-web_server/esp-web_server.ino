#include<ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);

#define led D5

void setup() {
  Serial.begin(9600);
  WiFi.begin("Redmi Note 9 Pro","123456789");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("...");
    delay(100); 
  }
  Serial.println();
  Serial.println("connected");
  Serial.println(WiFi.localIP());
  server.begin();
  pinMode(led,OUTPUT);
}

void loop() {
client = server.available();
     if(client == 1)
     {
      String req = client.readStringUntil('\n');
      req.trim();
      Serial.println(req);

      if(req == "GET /ledon HTTP/1.1")
      {
        digitalWrite(led,HIGH);
      }

      
      if(req == "GET /ledoff HTTP/1.1")
      {
        digitalWrite(led,LOW);
      }
      }
   client.println("HTTP/1.1 200 OK");
   client.println("Content-Type: text/html");
   client.println("");
   client.println("<!DOCTYPE html>");
  // client.println("<html lang="en">");
   client.println("<head>");
   //client.println(" <meta charset="UTF-8">");
   // client.println("<meta http-equiv="X-UA-Compatible" content="IE=edge">");
//client.println("<meta name="viewport" content="width=device-width, initial-scale=1.0">");
   client.println("<title>Document</title>");
   client.println("</head>");
   client.println("<body>");
   client.println(" <h1>ESP 8266</h1>");
   client.println("<h2>led control</h2>"); 
   client.println(" <a href=\"/ledon\"\"><button>led1 on</button></a> ");
   client.println("<a href=\"/ledoff\"\"><button>led1 off</button></a>");
   client.println("</body>");
   client.println("</html>");
     
      
     

    




  

}
