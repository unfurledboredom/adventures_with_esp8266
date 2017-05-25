#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <ESP8266WiFi.h>

//The Wifi credentials
const char* ssid = "HomeSSID";
const char* password = "HOMEWIFIPASSWORD";

int serverPort = 80;
int activePxl = 0;
WiFiServer server(serverPort);

// Which pin on the Arduino is connected to the 
#define LED_DATA_PIN  14
// How many LEDs are attached to the ESP8266 
// DO NOT use more than 30 LEDs without an independent power source. Most ESP8266 boards can not handle more than that without burning out.
#define NUMBER_OF_LEDS  30
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
// For more information refer to the guide at the Adafruit site
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMBER_OF_LEDS, LED_DATA_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
	Serial.begin(115200);
	Serial.println();
	//wifi
	Serial.printf("Connecting to %s ", ssid);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
	delay(500);
	Serial.print(".");
	}
	Serial.println(" connected");
	server.begin();
	Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
	pixels.begin(); // This initializes the LED library.

}

void loop() {
	WiFiClient client = server.available(); 
	// wait for a client (web browser) to connect
	if (client) {
	Serial.println("\n[Client connected]");
	while (client.connected()) {
		// read line by line what the client (web browser) is requesting
		if (client.available()) {
			String line = client.readStringUntil('\r');        
			if (line.indexOf("and=") != -1 && line.indexOf("GET /?red=") != -1)  {
				Serial.println("Color Change Request innitiated");
				int red = line.substring(line.indexOf("red=") + 4, line.indexOf("green=") -1).toInt();
				Serial.print("Red:");          
				Serial.println(red);
				int green = line.substring(line.indexOf("green=") + 6, line.indexOf("blue=") -1).toInt();
				Serial.print("Green:");
				Serial.println(green);
				int blue = line.substring(line.indexOf("blue=") + 5, line.indexOf("and=") -1).toInt();
				Serial.print("Blue:");
				Serial.println(blue);
				letThereBeLight(red,green,blue);
			}
			// at the end of the request print an empty line
			if (line.length() == 1 && line[0] == '\n') {
				client.println(clientHTML());
				break;
			}
		}
	}
	delay(1); // give the web browser time to receive the data
	// close the connection:
	client.stop();
	Serial.println("[Client disonnected]");
}

// The HTML page for clients
String clientHTML() {
	String htmlPage = 
		String("HTTP/1.1 200 OK\r\n") +
			"Content-Type: text/html\r\n" +
			"\r\n" +
			"<!DOCTYPE HTML>" +
			"<html>" +
			    //I'm using the JScolor library. You can host it externally or choose not to use it at all. 
			    //If you are 1337 and don't want to use jsColor you can use it simply by typing in your own RGB codes
				"<script src='https://cdnjs.cloudflare.com/ajax/libs/jscolor/2.0.4/jscolor.min.js'></script>" +
				"<form id='light_form' name='light_form'>" +
					"Red: <input id='red' name='red' type='text' value='0'><br>" +
					"Green: <input id='green' name='green' type='text' value='0'><br>" +
					"Blue: <input id='blue' name='blue' type='text' value='0'><br>" +
					"Color Picker: <input name='and' type='text' class=\"jscolor {onFineChange:'update(this)', mode:'HVS'}\" value='FFFFFF'><br>" +
					"<br>" +
					"<input type='submit' value='Submit'>" +
				"</form>" +
				"<script>" +
					"function update(picker) {" +
						"document.getElementById('red').value = Math.round(picker.rgb[0]);" +
						"document.getElementById('green').value = Math.round(picker.rgb[1]);" +
						"document.getElementById('blue').value = Math.round(picker.rgb[2]);" +
					"}" +
				"</script>" +
			"</html>" +
			"\r\n";
	return htmlPage;
}

void letThereBeLight(int red, int green, int blue) {
	pixels.clear();
	for (int i = 0; i < NUMPIXELS; i++) {
		pixels.setPixelColor(i, red, green, blue, 0);
	}
	pixels.show();
}