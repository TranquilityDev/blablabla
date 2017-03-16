#include <ESP8266WiFi.h>
//*-- Hardware Serial
#define Baudrate   115200
// Initialize TNumber

//*-- IoT Information
#define SSID    "Tranquility"
#define PASS    "11111112"
#define HOST    "192.168.137.16" // ThingSpeak IP Address: 184.106.153.149
#define PORT    3000

//String jsonStr = "{\"temp\":23.4, \"humid\":56.7}";

int pin = D8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 3000;//sampe 3s ;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;



void setup() {
    Serial.begin( Baudrate );
    Serial.println( "ESP8266 Ready!" );
    // Connecting to a WiFi network
    Serial.print("Connect to ");
    Serial.println( SSID );
    WiFi.begin( SSID, PASS );

    // Keep waiting to connect WiFi SSID
    while( WiFi.status() != WL_CONNECTED )
    {
        delay(500);
        Serial.print( "." );
    }
    Serial.println( "" );

    Serial.println( "WiFi connected" );
    Serial.println( "IP address: " );
    Serial.println( WiFi.localIP() );
    Serial.println( "" );

    Serial.println( "Tranquility System Ready!" );
    delay(10000);

}

void loop() {
  //Just number to test
    // Get value
    httpSend();
    // Delay
    delay( 60000 ); // 20 second
}

void httpSend() {
    WiFiClient client;

    if( !client.connect( HOST, PORT ) )
    {
        Serial.println( "connection failed" );
        return;
    }
    else
    {

          duration = pulseIn(pin, LOW);
          lowpulseoccupancy = lowpulseoccupancy+duration;

          if ((millis()-starttime) > sampletime_ms)//if the sampel time == 3s
          {
           ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
           concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
           Serial.print("concentration = ");
           Serial.print(concentration);
           Serial.println(" pcs/0.01cf");
           Serial.println("\n");
           lowpulseoccupancy = 0;
           starttime = millis();
           String jsonStr = "{\"temp\":23.4, \"humid\":56.7, \"PM\":0.62}";


               Serial.println("connected");
               client.println("POST / HTTP/1.1");
               client.println("Content-Type: application/json");
               client.print("Content-Length: ");
               client.println(jsonStr.length());
               client.println();
               client.print(jsonStr);

             delay(10);
             client.stop();

          }
    }
}
