/*
 * Home Automation with Adafruit.io using the MQTT protocol 
 * NodeMCU is the aggregator in this build
 * The relay is operated under Normally Open configuration
 * Remote operability of AC devices is accomplished using this project
 */
#include<Adafruit_MQTT_Client.h>  //Adafruit Client 
#include<ESP8266WiFi.h> 
WiFiClient esp; //Creating a wifi client
#define ssid "Rajeev-2.4GHz"  //ssid of the WiFi network
#define pass "latham36"       //password of the WiFi network
#define server "io.adafruit.com"  //Server of Adafruit
#define port 1883 //Port
#define username "Rajeev_Marada"  //Adafruit Username
#define key "aio_uUfu15u6eyQOzssN33MaB62DMCEa"  //aio Key
#define relay 5
Adafruit_MQTT_Client mqtt(&esp,server,port,username,key); //creating a server-client connection
Adafruit_MQTT_Subscribe led(&mqtt,username"/feeds/switch-led"); //subscribing to access data from server
void setup() 
{
  // put your setup code here, to run once:
  WiFi.begin(ssid,pass);  //starting WiFi
  Serial.begin(115200);
  pinMode(relay,OUTPUT);
  while(WiFi.status()!=WL_CONNECTED)
  { delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to : ");
  Serial.println(ssid);
  Serial.print("IP :");
  Serial.println(WiFi.localIP());
  Serial.println("Connecting To AdaFruit: ");
  mqtt.subscribe(&led); //Subscribing to led field to recieve data
  while(mqtt.connect()) //Start connection with Adafruit
  { delay(500);
    Serial.print(".");
  }
  Serial.println("Connected To Adafruit");

}

void loop() 
{
  
  while(mqtt.readSubscription(5000))  //runs when subscription service is active
  {
    int a  = atoi((char*)led.lastread); //Convert incoming ASCII data from the server into integer
    Serial.print("Value of LED: ");
    Serial.println(a);
    if(a==0)
    digitalWrite(relay,LOW);  //The light is connected in Normally Open Configuration so bulb will glow 
    else
    digitalWrite(relay,HIGH); //Bulb will turn off
  }
  
}
