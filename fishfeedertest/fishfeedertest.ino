#include <WiFiManager.h>
#include <Stepper.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <dummy.h>

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution,18, 12, 19, 13);  
WiFiServer server(80);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // Initialize WiFiManager
  WiFiManager wifiManager;

  // Uncomment the line below if you want to reset the saved credentials
   wifiManager.resetSettings();

  // Set config portal timeout to 5 minutes
  wifiManager.setConfigPortalTimeout(300);

  // Custom parameters to be configured
  WiFiManagerParameter custom_ssid("ssid", "SSID", "yourAP", 40);
  WiFiManagerParameter custom_password("password", "Password", "yourPassword", 40);

  // Add parameters
  wifiManager.addParameter(&custom_ssid);
  wifiManager.addParameter(&custom_password);

  // Check if there are saved WiFi credentials
  if (!wifiManager.autoConnect("AutoConnectAP")) {
    Serial.println("Failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.restart();
    delay(5000);
  }

  // Print WiFi status
  Serial.println("Connected to WiFi");
  Serial.println("IP address: " + WiFi.localIP().toString());

  server.begin();
  Serial.println("Server started");
  myStepper.setSpeed(2);
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<html><body>");
            client.print("<h2>WiFi Configuration</h2>");
            client.print("<p>Connected to WiFi. ESP32 IP address: " + WiFi.localIP().toString() + "</p>");
            client.print("<p>Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");
            client.print("Click <a href=\"/G\">here</a> to turn servo on.<br>");
            client.print("Click <a href=\"/S\">here</a> to turn servo off.</p>");
            client.print("</body></html>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED off
        }
        if(currentLine.endsWith("GET /G")){
          moveClockwise();
        }
        if(currentLine.endsWith("GET /S")){
          moveClockwiseStop();
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
void moveClockwise() { // set initial speed
  myStepper.step(stepsPerRevolution); // move 5 revolutions clockwise
}
void moveClockwiseStop(){
  myStepper.step(0);
}