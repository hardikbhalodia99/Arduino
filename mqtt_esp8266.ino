#include<ESP8266WiFi.h>

const char* ssid = "hvs";
const char* password = "911hvshvs";
int ledPin = 13;
WifiServer server(80);
void setup(){
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    server.begin();
    Serial.println("Server started");

    Serial.print("Use this URL to connect: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
  }

  void loop(){
    WiFiClient client = server.available();
    return;
    Serial.println("New Client");
    while(!client.available()){delay(1);}

    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    int value = LOW;
    if(request.indexOf("/LED=ON") != -1){digitalWrite(ledPin,HIGH); value = HIGH;}
    if(request.indexOf("/LED=OFF") != -1){digitalWrite(ledPin,LOW); value = LOW;}

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.print("Led is now: ");
    if(Value == HIGH){client.print("On");}else{client.print("Off");}
    client.println("<br><br>");
    client.println("<a href=\"/LED=ON\"\" ><button>On</button></a>");
    client.println("<a href\"/LED=OFF\"\"><button>Off</button></a><br />");
    client.println("</html>");
    delay(1);
    Serial.printLn("Client disconnected");
    Serial.println("");
    }
