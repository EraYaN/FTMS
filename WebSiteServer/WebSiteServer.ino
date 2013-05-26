#include <SPI.h>
#include <Ethernet.h>
#include "utility/w5100.h"

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,178,15);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);
volatile uint8_t i = 0;
volatile uint8_t m = 0;
volatile uint8_t S0 = 0;
volatile uint8_t S1 = 0;
volatile uint8_t S2 = 0;
volatile uint8_t S3 = 0;
void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(115200);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
pinMode(53, OUTPUT);
pinMode(2, INPUT);
pinMode(4, OUTPUT);
pinMode(13, OUTPUT);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  attachInterrupt(0,testInt,FALLING);
  //attachInterrupt(0,testIntR,RISING);
  W5100Class::writeIMR(B11101111);  
}


void loop() {
  delay(500);
  uint8_t res = digitalRead(2);
  digitalWrite(13, res);
  if(res==0){
    Serial.print("IR: ");
    cli();
    i = W5100Class::readIR();
    if(i & 1!=0)
      S0 = W5100Class::readSnIR(0);
      else 
      S0 = 0;
    if(i & 2!=0)
      S1 = W5100Class::readSnIR(1);
      else 
      S1 = 0;
    if(i & 4!=0)
      S2 = W5100Class::readSnIR(2);
      else 
      S2 = 0;
    if(i & 8!=0)
      S3 = W5100Class::readSnIR(3);
      else 
      S3 = 0;
      sei();
    Serial.print("\tIR: ");
    Serial.println(i, BIN);
    Serial.print("\tIMR: ");
    Serial.println(m, BIN);
    Serial.print("\tS0IR: ");
    Serial.println(S0, BIN);
    Serial.print("\tS1IR: ");
    Serial.println(S1, BIN);
    Serial.print("\tS2IR: ");
    Serial.println(S2, BIN);
    Serial.print("\tS3IR: ");
    Serial.println(S3, BIN);
    stopInt();
  }
}
void respond(){
  EthernetClient client = server.available();
  if (client) {    
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {        
        char c = client.read();
        //Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
	  //client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html><head><title>Arduino Server</title></head><body>");
          // output the value of each analog input pin
          client.println("<h1>Yay it works.</h1>");
          client.println("<p>Millis: ");
          client.println(millis());
          client.println("</p>");
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
    //delay(1);
    // close the connection:
    client.stop();
  }
}
void stopInt(){
  cli();
   i = W5100Class::readIR();
  W5100Class::writeIR(B11100000);
  if(i & 1!=0)
    W5100Class::writeSnIR(0, B00000001);
  if(i & 2!=0)
    W5100Class::writeSnIR(1, B00000001);
  if(i & 4!=0)
    W5100Class::writeSnIR(2, B00000001);
  if(i & 8!=0)
    W5100Class::writeSnIR(3, B00000001);
    
    sei();
}
void testInt(){ 
 digitalWrite(13, digitalRead(2)); 
      i = W5100Class::readIR();
      m = W5100Class::readIMR();
      if(i & 1!=0)
        S0 = W5100Class::readSnIR(0);
        else 
        S0 = 0;
      if(i & 2!=0)
        S1 = W5100Class::readSnIR(1);
        else 
        S1 = 0;
      if(i & 4!=0)
        S2 = W5100Class::readSnIR(2);
        else 
        S2 = 0;
      if(i & 8!=0)
        S3 = W5100Class::readSnIR(3);
        else 
        S3 = 0;
      if(i>=32)
        W5100Class::writeIR(B11100000);      
      if(S0>0)
        W5100Class::writeSnIR(0, B00011111);
      if(S1>0)
        W5100Class::writeSnIR(1, B00011111);
      if(S2>0)
        W5100Class::writeSnIR(2, B00011111);
      if(S3>0)
        W5100Class::writeSnIR(3, B00011111);
        
        respond();
}
