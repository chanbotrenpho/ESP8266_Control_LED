#include <SPI.h>
#include <ESP8266WiFi.h>

const char *ssid = "Bao_Linh";
const char *password = "24061986";
IPAddress ip(192, 168, 0, 90);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

WiFiServer server(80);

const int led1 = 0;
const int led2 = 2;


void setup ( void ) {
	pinMode ( led1, OUTPUT );
  pinMode (led2, OUTPUT);
	Serial.begin ( 115200 );
	WiFi.begin ( ssid, password );
  WiFi.config(ip, gateway, subnet);
	Serial.println ( "" );
  WiFi.mode(WIFI_STA);

	// Wait for connection
	while ( WiFi.status() != WL_CONNECTED ) {
		delay ( 500 );
		Serial.print ( "." );
	}

	Serial.println ( "" );
	Serial.print ( "Connected to " );
	Serial.println ( ssid );
	Serial.print ( "IP address: " );
	Serial.println ( WiFi.localIP() );
	server.begin();
	Serial.println ( "HTTP server started" );
}

void loop ( void ) {
	WiFiClient client = server.available();
 if(!client){
    return;
  }
  while(!client.available()){
    delay(1);
    }
  Serial.println("New Client Come");
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 //-----------------------------------------------------//
  if(request.indexOf("/Batden1")>0){
      digitalWrite(0,LOW);
    }
  if(request.indexOf("/Tatden1")>0){
      digitalWrite(0,HIGH);
    }
  if(request.indexOf("/Batden2")>0){
      digitalWrite(2,LOW);
    }
  if(request.indexOf("/Tatden2")>0){
      digitalWrite(2,LOW);
    }
 //-----------------------------------------------------//
   if(digitalRead(2)==1){
      Serial.println("Da bat den 1");
    }
   if(digitalRead(2)==0){
      Serial.println("Da tat den 1");
    }
    if(digitalRead(0)==1){
      Serial.println("Da bat den 2");
    }
   if(digitalRead(0)==0){
      Serial.println("Da tat den 2");
    }
//---------------------------------------------------//  
 client.println("HTTP/1.1 200 OK");
client.println("Content-Type:text/html");
client.println("");
client.println("<!DOCTYPE HTML");
client.println("charset=UTF-8/>");
client.print("<title>ESP8266 Control LED</title>");
client.println("<html>");
client.println("<head>");
client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
client.println("<meta name='apple-mobile-web-app-status-bar-style' content=black-translucent' />");
client.println("<head>");
client.println("<body>");
client.println("<hr/><hr>");
client.print("<h1><center> Dieu khien thiet bi qua ESP8266 </center></h1>");
client.println("<hr/><hr>");
client.println("<br><br>");
client.println("<center>");
client.println("Thiet bi 1");
client.println("<a href=\"/Batden1\"\"><button>Bat </button></a>");
client.println("<a href=\"/Tatden1\"\"><button>Tat </button></a><br />");
client.println("<br><br>");
client.println("<hr/><hr>");
client.println("</center>");
client.println("<br><br>");
client.println("<center>");
client.println("Thiet bi 2");
client.println("<a href=\"/Batden2\"\"><button>Bat </button></a>");
client.println("<a href=\"/Tatden2\"\"><button>Tat </button></a><br />");
client.println("</center>");
client.println("<br><br>");
client.println("<hr></hr>");
client.println("<hr></hr>");
client.println("</body>");
client.println("</html>");
}
