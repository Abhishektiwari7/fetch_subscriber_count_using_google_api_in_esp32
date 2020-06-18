#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
 
const char* ssid = "wifi's name";
const char* password = "wifi's password";
const char* name="channel name";
const char* key="api key"; 
const char* subCount;                               // subcriber count but as a string for serial communication
int sub;                                            // subcriber count as a integer for use in different functions

void setup() {
 
  Serial.begin(115200);             //for debug
  delay(50);
  WiFi.begin(ssid, password);        //wifi begins in which esp32 ready to connect router
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
}
 
void loop() {
 //----------------------call google api then get json file deserialze it extract subscriber count------------------------------------
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin("https://www.googleapis.com/youtube/v3/channels?part=statistics&id=name&key=key"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
 
     if (httpCode > 0)                               //in return youtube api gives you json file in which details are specified in class form
     { 
    String mydata = http.getString();              // 1st save everthing as a string
    StaticJsonDocument<605> doc;                      //make a json document size because if data is too much then saved  data in document is not  enough
    deserializeJson(doc,mydata);                    //deserializejson converte json file into usable file which is easy to work with it.
    JsonObject items0 = doc["items"][0];          // now deserialize data are in class form so call class member in which subcriber count is situated
    JsonObject itemstat = items0["statistics"];       //item<[0]<statistics<subscriberCount
    subCount = itemstat["subscriberCount"];            // copy that in subcount char
    Serial.println(subCount);                            // for debug
    sub=atoi(subCount);                             // subCoun as a string by use atoi convert into integer for future
    }
 
  else {
      Serial.println("Error on HTTP request");
       }
    http.end();                                       //Free the resources 
  }
 
}
