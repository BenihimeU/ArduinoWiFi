#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

// WiFi config
const char ssid[] = "Firefight";
const char password[] = "Uzumaki123";
const char host[] = "192.168.43.239";
const String uri = "/GetDataFromServer?channel=temp";
const int port = 3000;

//WiFiClinet
WiFiClient client;

void setup() {

  // Initialize Serial
  Serial.begin(9600);
  delay(100);

  // Connect to WiFi
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  // Show that we are connected
  Serial.print("Connected to ");
  Serial.println(ssid);

  // Print IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  //Connecting to Server
  Serial.print("Connecting to ");
  Serial.println(host);
  if (client.connect(host, port) == 0) {
    Serial.println("Connection failed");
  }
  GetRequest("http://192.168.43.239:3000/GetDataFromServer?channel=temp");
  //  GetRequest("http://" + host + ":" + port + uri + ");
  //Send Request for Client
  //  Serial.println("GET" + uri + " HTTP / 1.1\r\n" +
  //  "Host : "+ host +"\r\n" +
  //  "Connection : Close\r\n" +
  //  +"\r\n");


  //  hClient.get(");
  delay(15000);
}

void GetRequest(String url) {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;  //Declare an object of class HTTPClient
    http.addHeader("Content-Type", "application/json");
    http.begin(url);  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request

    if (httpCode > 0) { //Check the returning code

      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
    }

    http.end();   //Close connection
  } else {
    Serial.println("No Active connection");
  }
}

void PostRequest(String url, String payload) {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;  //Declare an object of class HTTPClient
    http.addHeader("Content-Type", "application/json");
    http.begin(url);  //Specify request destination
    String req = "{\"channel\":\"temp\",\"data\":{\"name\":\"temp\",\"value\":2}}";
    int httpCode = http.POST(req);                                                                  //Send the request

    if (httpCode > 0) { //Check the returning code

      String response = http.getString();   //Get the request response payload
      Serial.println(response);                     //Print the response payload
    }

    http.end();   //Close connection
  } else {
    Serial.println("No Active connection");
  }
}
