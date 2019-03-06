#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

// WiFi config
const char ssid[] = "Firefight";
const char password[] = "";
const char host[] = "192.168.43.239";
const String uri = "/GetDataFromServer?channel=temp";
const int port = 3000;

//WiFiClinet
WiFiClient client;

void setup() {
  // Initialize Serial
  Serial.begin(9600);
}

void loop() {
  GetRequest("http://192.168.43.239:3000/GetDataFromServer?type=temp");
  String req = "type=temp&value=1.5";
  PostRequest("http://192.168.43.239:3000/postFormData", req);
  delay(15000);
}


/*
   IsHostReachable
   parameter: Hostname: String (Domain/ IP:Port)
   response: bool
*/
bool IsHostReachable(String host, int port) {
  //Connecting to Server
  Serial.print("Connecting to ");
  Serial.println(host);
  if (client.connect(host, port) == 0) {
    Serial.println("Connection failed");
    return false;
  }
  return true;
}
/*
   GET Local IP address of active connection
   Note: Connection should be established prior to getting IP
*/
IPAddress GetLocalIP() {
  // Print IP address
  return WiFi.localIP();
}

/*
   Establish connection
   Parameters: SSID: String, Password: String
*/
void EstablishConnection(String ssid, String password) {
  // Connect to WiFi
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  delay(100);
  // Show that we are connected
  Serial.print("Connected to ");
  Serial.println(ssid);
}
/*
   HTTP GET Request
   Parameters: URL String
   Response: Response JSON
*/
String GetRequest(String url) {
  String response = "No Active connection";
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;  //Declare an object of class HTTPClient
    http.addHeader("Content-Type", "application/json");
    http.begin(url);  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
    if (httpCode > 0) { //Check the returning code
      response = http.getString();   //Get the request response payload
    }
    http.end();   //Close connection
  } else {
    Serial.println("No Active connection");
  }
  return response;
}

/*
   HTTP POST Request
   Parameters: URL String, Payload String (form-urlencoded)
   Response: Response JSON
*/
String PostRequest(String url, String payload) {
  String response = "No Active connection";
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;  //Declare an object of class HTTPClient
    http.begin(url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST(payload);
    http.writeToStream(&Serial);
    if (httpCode > 0) {
      response = http.getString();   //Get the request response payload
    }
    Serial.print(httpCode);
    http.end();   //Close connection
  } else {
    Serial.println("No Active connection");
  }
  return response;
}
