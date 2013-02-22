#include <Ethernet.h>
#include "EthernetFunctions.h"

void initEthernet(){
	server.begin();
}
void checkForHTTPConnections(){
	String readString = String(100); //string for fetching data from address
//server
// listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
		//read char by char HTTP request
		if (readString.length() < 100) {

		//store characters to string 
		readString += c; 
		} 
		Serial.print("\"");
		Serial.print(readString);
        Serial.println("\"");
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connnection: close");
          client.println();
          client.println("<!doctype html>");
          client.println("<html>");
		  client.println("<meta><title>It Works!</title></meta><body>");
          client.println("<p>It modderfukking works.</p>");
          client.println("</body></html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}