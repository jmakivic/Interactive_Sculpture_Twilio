#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <WiFiClientSecure.h>

char* ssid = "My WaiFi~ 2.4Ghz";
char* password = "yourwaifuistrash";

#define TFT_DC 15
#define TFT_CS 0

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS,TFT_DC);

WiFiClientSecure client;

long checkDueTime;
int checkDelay = 60000;

String title;

//color names
#define LIGHT_PINK 0xFEBC
#define LIGHT_PURPLE 0xEE9F
#define LIGHT_GREEN 0xDFDA
#define LIGHT_YELLOW 0xFFBA
#define CORAL 0xF9EB
#define NEON_PINK 0xF973
#define NEON_BLUE  0x2F3F
#define NEON_GREEN 0x2FEE


void setup() {
  Serial.begin(115200);
  tft.begin();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
    }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  client.setInsecure();
}

void showResponses() {
  String title ="";
  String headers = "";
  String body = "";

  bool finishedHeaders = false;
  bool currentLineIsBlank = true;
  bool gotResponse = false;
  long now;

  int a_counter =0;
  int b_counter =0;
  int c_counter =0;
  int a_amount =0;
  int b_amount=0;
  int c_amount =0;

  char host[] = "api.airtable.com";
  
  Serial.println("accessing this function");
  if(client.connect(host, 443)){
     Serial.println("connected");

     String URL = "/v0/appOmfamXLJabgtEH/CamParkData";

     Serial.println(URL);

     client.println("GET " + URL + " HTTP/1.1");
     client.print("Host: ");
     client.println(host);
     client.println("Authorization: Bearer keydUirPfIGbgC80E");
     client.println("User-Agent: arduino/1.0");
     client.println("");

     now = millis();
     //checking the time out
     while (millis() - now < 1500){
        while(client.available()){
          char c = client.read();

          if(finishedHeaders){
            body = body + c;
           
          }else {
            if(currentLineIsBlank && c == '\n'){
                finishedHeaders = true;
             
            }else{
                headers = headers + c;
            }  
          }

          if(c == '\n'){
            currentLineIsBlank = true;
          }else if(c != '\r'){
            currentLineIsBlank = false;  
          }

          gotResponse = true;
        }
        if(gotResponse){
          Serial.println("Got Response");
          DynamicJsonBuffer jsonBuffer;
          JsonObject& root = jsonBuffer.parseObject(body);
          if(root.success()){
            Serial.println("Success!");
            if(root.containsKey("records")){
              
              for(int i=0; i<10; i++){
                  Serial.print("i: ");
                  Serial.println(i);
                  JsonObject& post = root["records"][i]["fields"];
                  for(int j=0; j<4; j++){
                      Serial.print("j: ");
                      Serial.println(j);
                      if(j==0){
                        if(post.containsKey("Question1")){
                            title = post["Question1"].as<String>();
                            Serial.println("Question1");
                            Serial.println("Title: ");
                            Serial.println(title);
                            if(title == "A" || title == "a"){
                              tft.fillScreen(ILI9341_BLACK);
                              tft.setCursor(0,10);
                              tft.setTextSize(2);
                              tft.setTextColor(ILI9341_WHITE);
                              neon_grid(NEON_BLUE);
                              delay(200);
                              tft.print(F("Sending files to Floating Glow Cloud DB . . ."));
                              delay(2000);
                              diagonal_lines(NEON_GREEN, 30,100);
                              diagonal_lines(CORAL, 10,10);
                              a_counter++;
                             
                            }
                           if(title=="B" || title =="b"){
                              tft.fillScreen(ILI9341_BLACK);
                              tft.setCursor(0,10);
                              tft.setTextSize(2);
                              tft.setTextColor(LIGHT_GREEN);
                              neon_grid(CORAL);
                              delay(100);
                              tft.print(F("Configuring web crawlers . . ."));
                              delay(200);
                              tft.setCursor(0,100);
                              tft.print(F("Thank you for your enduring patience"));
                              delay(2000);
                              neon_grid(LIGHT_PURPLE);
                              diagonal_lines(NEON_BLUE, 40,200);
                              diagonal_lines(LIGHT_YELLOW, 20,20);
                              b_counter++;
                            }
                           if(title=="C" || title=="c"){
                             tft.fillScreen(ILI9341_BLACK);
                             tft.setCursor(0,10);
                             tft.setTextSize(2);
                             tft.setTextColor(LIGHT_YELLOW);
                             
                             neon_grid(LIGHT_PURPLE);
                             tft.print(F("Pinging the amorphous blob . . ."));
                             diagonal_lines(NEON_GREEN, 12,40);
                             diagonal_lines(NEON_BLUE, 30,60);
                             c_counter++;
                           }

                           delay(1000);
                           
                         
                        } 
                      }
                      if(j==1){
                        if(post.containsKey("Question2")){
                            title = post["Question2"].as<String>();
                            Serial.println("Question2");
                            Serial.println("Title: ");
                            Serial.println(title);  
                            if(title == "A" || title == "a"){
                              tft.fillScreen(ILI9341_BLACK);
                              tft.setCursor(0,10);
                              tft.setTextSize(2);
                              tft.setTextColor(ILI9341_WHITE);
                              neon_grid(NEON_BLUE);
                              delay(200);
                              tft.print(F("Oscillating Glow Cloud data packets . . ."));
                              delay(2000);
                              diagonal_lines(NEON_GREEN, 30,20);
                              diagonal_lines(CORAL, 10,80);
                              a_counter++;
                            }
                           if(title=="B" || title =="b"){
                              tft.fillScreen(ILI9341_BLACK);
                              tft.setCursor(0,10);
                              tft.setTextSize(2);
                              tft.setTextColor(LIGHT_GREEN);
                              neon_grid(CORAL);
                              delay(100);
                              tft.print(F("Querying web crawlers . . "));
                              delay(200);
                              tft.setCursor(0,100);
                              tft.print(F("Traversing the net . . ."));
                              delay(2000);
                              neon_grid(LIGHT_PURPLE);
                              diagonal_lines(NEON_BLUE, 40,120);
                              diagonal_lines(LIGHT_YELLOW, 20,280);
                              b_counter++;
                            }
                           if(title=="C" || title=="c"){
                             tft.fillScreen(ILI9341_BLACK);
                             tft.setCursor(0,10);
                             tft.setTextSize(2);
                             tft.setTextColor(LIGHT_YELLOW);
                             
                             neon_grid(LIGHT_PURPLE);
                             tft.print(F("connecting tendril sockets . . ."));
                             diagonal_lines(NEON_GREEN, 12,60);
                             diagonal_lines(NEON_BLUE, 30,90);
                             c_counter++;
                               
                   
                           }

                           delay(1000);
                        }  
                      }
                      if(j==2){
                         if(post.containsKey("Question3")){
                            title = post["Question3"].as<String>();  
                            Serial.println("Question3");
                            Serial.println("Title: ");
                            Serial.println(title);
                            if(title == "A" || title == "a"){
                              tft.fillScreen(ILI9341_BLACK);
                              tft.setCursor(0,10);
                              tft.setTextSize(2);
                              tft.setTextColor(ILI9341_WHITE);
                              neon_grid(LIGHT_PINK);
                              delay(200);
                              tft.print(F("Buzzing connection . . . "));
                              delay(2000);
                              diagonal_lines(NEON_GREEN, 30,20);
                              diagonal_lines(CORAL, 10,0);
                              a_counter++;
                            }
                           if(title=="B" || title =="b"){
                              tft.fillScreen(ILI9341_BLACK);
                              tft.setCursor(0,10);
                              tft.setTextSize(2);
                              tft.setTextColor(LIGHT_GREEN);
                              neon_grid(CORAL);
                              delay(100);
                              tft.print(F("Querying vibrations . . ."));
                              delay(2000);
                              neon_grid(LIGHT_PURPLE);
                              diagonal_lines(NEON_BLUE, 40,30);
                              diagonal_lines(LIGHT_YELLOW, 20,10);
                              b_counter++;
                            }
                           if(title=="C" || title=="c"){
                             tft.fillScreen(ILI9341_BLACK);
                             tft.setCursor(0,10);
                             tft.setTextSize(2);
                             tft.setTextColor(LIGHT_YELLOW);
                            
                             neon_grid(LIGHT_PURPLE);
                             tft.print(F("Connecting pins . . one and two . . ."));
                             diagonal_lines(NEON_GREEN, 12,0);
                             diagonal_lines(NEON_BLUE, 30,220);
                             c_counter++;
                           }

                           delay(1000);
                        }  
                      }
                      if(j==3){
                         if(post.containsKey("Question4")){
                            title = post["Question4"].as<String>();
                            Serial.println("Question4");
                            Serial.println("Title: ");
                            Serial.println(title);
                            if(title == "A" || title == "a"){
                              tft.fillScreen(ILI9341_BLACK);
                              tft.setCursor(0,10);
                              tft.setTextSize(2);
                              tft.setTextColor(ILI9341_WHITE);
                              neon_grid(NEON_BLUE);
                              delay(200);
                              tft.print(F("Melting the circuits . . ."));
                              delay(2000);
                              diagonal_lines(NEON_GREEN, 30,30);
                              diagonal_lines(CORAL, 10,240);
                               a_counter++;
                            }
                           if(title=="B" || title =="b"){
                              tft.fillScreen(ILI9341_BLACK);
                              tft.setCursor(0,10);
                              tft.setTextSize(2);
                              tft.setTextColor(LIGHT_GREEN);
                              neon_grid(CORAL);
                              delay(100);
                              tft.print(F("Connecting to liquid computer . . ."));
                              delay(2000);
                              neon_grid(LIGHT_PURPLE);
                              diagonal_lines(NEON_BLUE, 40, 100);
                              diagonal_lines(LIGHT_YELLOW, 20,30);
                              b_counter++;
                            }
                           if(title=="C" || title=="c"){
                             tft.fillScreen(ILI9341_BLACK);
                             tft.setCursor(0,10);
                             tft.setTextSize(2);
                             tft.setTextColor(LIGHT_YELLOW);
                          
                             neon_grid(LIGHT_PURPLE);
                             tft.print(F("pinging . . .fossil . . . server . . ."));
                             diagonal_lines(NEON_GREEN, 12,0);
                             diagonal_lines(NEON_BLUE, 30,50);
                             c_counter++;
                           }

                           delay(1000);
                        }  
                      }  
                  }
                  if(a_counter>b_counter && a_counter>c_counter){
                    tft.fillScreen(0x2ADF);
                    tft.setTextColor(ILI9341_WHITE);
                    tft.setCursor(0,10);
                    tft.setTextSize(2);
                    tft.print("Calculating final location . . .");
                    delay(2000);
                    neon_grid(LIGHT_YELLOW);
                    delay(500);
                    a_amount++;    
                  }
                  if(b_counter>a_counter && b_counter>c_counter){
                    tft.fillScreen(0x2ADF);
                    tft.setTextColor(ILI9341_WHITE);
                    tft.setCursor(0,10);
                    tft.setTextSize(2);
                    tft.print("Calculating final location . . .");
                    delay(2000);
                    neon_grid(LIGHT_YELLOW);
                    delay(500);
                    b_amount++;
                  }
                  if(c_counter>a_counter && c_counter>b_counter){
                     tft.fillScreen(0x2ADF);
                    tft.setTextColor(ILI9341_WHITE);
                    tft.setCursor(0,10);
                    tft.setTextSize(2);
                    tft.print("Calculating final location . . .");
                    delay(2000);
                    neon_grid(LIGHT_YELLOW);
                    delay(500);
                    c_amount++;
                  }
         
                }
                //This is where you determine the results and show them on the screen
             
                if(a_amount>=b_amount && a_amount>=c_amount){
                  tft.fillScreen(NEON_BLUE);
                  tft.setCursor(0,10);
                  tft.setTextSize(3);
                  tft.setTextColor(LIGHT_YELLOW);
                  neon_grid(NEON_PINK);
                  tft.print(F("They have entered the Spirit Garden."));
                  delay(2000);
                  diagonal_lines(LIGHT_PURPLE, 30,60);
                  delay(1000);
                  
                  }

                 if(b_amount>=a_amount && b_amount>=c_amount){
                  tft.fillScreen(NEON_PINK);
                  tft.setCursor(0,10);
                  tft.setTextSize(3);
                  tft.setTextColor(LIGHT_YELLOW);
                  neon_grid(LIGHT_YELLOW);
                  tft.print(F("They have entered the Fortress."));
                  delay(2000);
                  diagonal_lines(LIGHT_YELLOW, 30,60);
                  delay(1000);
                  
                  }

                  if(c_amount>=a_amount && c_amount>=b_amount){
                    tft.fillScreen(NEON_GREEN);
                    tft.setCursor(0,10);
                    tft.setTextSize(3);
                    tft.setTextColor(LIGHT_YELLOW);
                    neon_grid(LIGHT_GREEN);
                    tft.print(F("They have entered the Amorphous Temple"));
                    delay(2000);
                    diagonal_lines(LIGHT_PINK,20,60);
                    delay(1000);
                  
                  }         
            }  
          }else{
            Serial.println("failed to parse JSON");
          }
          break;
        }
      }
    }
  }


void neon_grid(uint16_t color){
int width = 280;
int height = 320;
int w = 0;
int h= 0;
  while(w < width){
      tft.drawLine(w,0,w+=20,height,color);
      w+=20;
      delay(100);
      while(h<height){
        tft.drawLine(0,h,width,h+=20,color);
        h+=20;
        delay(100);
        }
    }
  }
void diagonal_lines(uint16_t color,int spacing, int xpos){
  for(int i=0; i<10; i++){
      tft.drawLine(xpos,0,xpos+(spacing*i), 320, color);
      delay(100);
    }
  }

void loop() {
  long now = millis();
  if(now >= checkDueTime){
    Serial.println("--------");
   
    showResponses();
    //Serial.println(title);
 
    Serial.println("--------");
    checkDueTime = now +checkDelay;
  }

}
