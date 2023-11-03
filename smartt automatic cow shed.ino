
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Servo.h>
////////////////////////////////////////////////////////////
#include <SoftwareSerial.h>
SoftwareSerial sim(D7,D8);//7.5
int _timeout;
String _buffer;
String number = "0791629303"; //-> change with your number

/////////////////////////////////////////////
Servo myservo; 
#define HOST "itaratec.000webhostapp.com"          // Enter HOST URL without "http:// "  and "/" at the end of URL
#define WIFI_SSID "A"  //A          //HUAWEI-E5330-2714                                   
#define WIFI_PASSWORD "12345678" //90nre4a2//1234567890

//#define WIFI_SSID "A"            // WIFI SSID here                                   
//#define WIFI_PASSWORD "1234567890" 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DHT.h"

#define DHTPIN D6 
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
/////////////////////////////////////////////////////////////////////

int pos = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int pump =D7;
int motor_pin= A0;

String sendval, sendval2, sendval3, postData;
float t;
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
long trig= D0;
long echo= D1;
long duration;
long distance;

//.....................................................................
long trig2= D2;
long echo2= D3;
long duration2;
long distance2;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int j=0;
int k=0;
int l=0;
int m=0;
int n=0;
int o=0;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
    _buffer.reserve(50);
    sim.begin(9600);
    myservo.attach(D8); 
    Serial.begin(112500);
    pinMode(trig,OUTPUT);
       pinMode(motor_pin,OUTPUT);
    pinMode(echo,INPUT);
    pinMode(trig2,OUTPUT);
    pinMode(echo2,INPUT);
    pinMode(pump,OUTPUT);
    Serial.print("START");
    dht.begin();
    ///////////////////////////////////////////////////////
    /*
while (!sim.available()) {
    sim.println("AT");
  delay(1000);
  Serial.println("connecting....");
}
*/
  ///////////////////////////////////////////////////////
   WiFi.mode(WIFI_STA);           
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
   Serial.print("Connecting to ");
   Serial.print(WIFI_SSID);
   while (WiFi.status() != WL_CONNECTED) 
{
  
  Serial.print(".");
  delay(500); }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());    //print local IP address
  delay(30);
//callNumber();
   //  Reply("water is full");
     myservo.write(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void loop(){
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 WiFiClient client;
HTTPClient http;    // http object of clas HTTPClient
    sendval = String(distance2);  
    sendval2 = String(distance);   
    sendval3 = String(t); 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // grass();
 // water();
  //dht11();
  //gabura();
 // motor();
 // digitalWrite(motor_pin,HIGH);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
///////////////////////////////////////////////////////////////////////////////////
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);
  distance=duration*0.017;
  Serial.print("Grass is :   ");
  Serial.println(distance);
  Serial.print("");


////////////////////////////////////////////////////////////////////////////////////////

  digitalWrite(trig2,LOW);
  delayMicroseconds(2);
  digitalWrite(trig2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2,LOW);
  duration2 = pulseIn(echo2,HIGH);
  distance2=duration2*0.017;
  Serial.print("Water is:   ");
  Serial.println(distance2);
  ///////////////////////////////////////////////////////////////////////////////////
//grasss
if(distance>6 && j==0){
  
       //sevo();
       Serial.println("NO GRASS");
       Serial.println(distance);
      // Reply("no grass");
       //callNumber(); 
       myservo.write(90);
       delay(1000); 
       myservo.write(0);
       Serial.print("servo close");
       j=1;
       }
       else{
        j=0;
        }

  if(distance<4 && l==0) {
   
         Serial.println("GRASS IS FULL");
         Serial.println(distance); 
       //  Reply("glass is full");
         Serial.print("servo close");
         myservo.write(0);  
         delay(15);
         l==1;
         }

         else{
       l=0; 
          
          }
   ///////////////////////////////////////////////////////////
  
   if(distance2>4 &&  k==0){
   digitalWrite(pump,HIGH);
   delay(4000);
   digitalWrite(pump,LOW); 
   Serial.println("NO WATER");
   Serial.println(distance2);
 //  Reply("water is low");
   k=1;
   }
   else{
      k=0;
    }
    if(distance2<3 && o==0){
          digitalWrite(pump,LOW); 
          digitalWrite(pump,LOW);
          Serial.println("WATER IS FULL");
          Serial.println(distance2);
         // Reply("water is full");
        o=1;
  
  }
  else{
    o=0;
    }
  
 postData = "sendval=" + sendval + "&sendval2=" + sendval2+ "&sendval3=" + sendval3;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//http.begin(client,"http://192.168.1.122/dash/insert_data.php");              // Connect to host where MySQL databse is hosted
http.begin(client,"http://itaratec.xyz/djm/dbwrite.php");
http.addHeader("Content-Type", "application/x-www-form-urlencoded");            //Specify content-type header
int httpCode = http.POST(postData);   // Send POST request to php file and store server response code in variable named httpCode
Serial.println("Values are, sendval = " + sendval + " and sendval2 = "+sendval2);
delay(100);
// if connection eatablished then do this
if (httpCode == 200) { Serial.println("Values uploaded successfully."); Serial.println(httpCode); 
String webpage = http.getString();    // Get html webpage output and store it in a string
Serial.println(webpage + "\n"); 
}

// if failed to connect then return and restart

else { 
  Serial.println(httpCode); 
  Serial.println("Failed to upload values. \n"); 
  http.end(); 
  return; }


}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


 
  

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
  

  ///////////////////////////////////////////////////////

  ///////////////////////////////////////////
  void motor(){
   // analogWrite(motor_pin,255);
   // Serial.print("motor is high:");
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void dht11(){
    
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
    }
   void Reply( String texte) {
  
 //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(200);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(200);
  //String SMS = "Hello ";
  sim.println(texte);
 
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(200);
  _buffer = _readSerial();
  Serial.print(texte);
}

String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
}
void callNumber() {
  
  sim.print (F("ATD"));
  sim.print (number);
  sim.print (F(";\r\n"));
  _buffer = _readSerial();
  Serial.println(_buffer);
}
