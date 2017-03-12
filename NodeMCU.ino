#include <ESP8266WiFi.h>
//*-- Hardware Serial
#define Baudrate   115200
// Initialize TNumber

//*-- IoT Information
#define SSID    "Tranquility"
#define PASS    "11111112"
#define HOST    "192.168.137.104" // ThingSpeak IP Address: 184.106.153.149
#define PORT    3000

String jsonStr = "{\"temp\":23.4, \"humid\":56.7}";

void setup() {
    Serial.begin( Baudrate );
    Serial.println( "ESP8266 Ready!" );
    // Connecting to a WiFi network
    Serial.print("Connect to ");
    Serial.println( SSID );
    WiFi.begin( SSID, PASS );

    // 持續等待並連接到指定的 WiFi SSID
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
    delay(2000);

}

void loop() {
  //Just number to test
    // 確認取回的溫溼度數據可用
    httpSend();  
    // 每隔多久傳送一次資料
    delay( 2000 ); // 20 second
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
        // 準備上傳到 ThingSpeak IoT Server 的資料
        // 已經預先設定好 ThingSpeak IoT Channel 的欄位
        // field1：溫度；field2：濕度
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



