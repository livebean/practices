// rf22_reliable_datagram_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, reliable messaging client
// with the RF22ReliableDatagram class.
// It is designed to work with the other example rf22_reliable_datagram_server

#include <RF22ReliableDatagram.h>
#include <RF22.h>
#include <SPI.h>

#include <U8glib.h>

//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2

// Singleton instance of the radio
RF22ReliableDatagram rf22(CLIENT_ADDRESS);

uint8_t data[] = "Hello World!";
// Dont put this on the stack:
uint8_t buf[RF22_MAX_MESSAGE_LEN];

void draw(char* msg) {  
  u8g.drawStr( 0, 42, msg);
}

void setup()
{
  Serial.begin(9600);

  u8g.setFont(u8g_font_courR14);
  u8g.setColorIndex(1);

  if (!rf22.init())
    Serial.println("RF22 init failed");
  // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
}

void loop()
{
  int i = 1;
  while (1)
  {
    i++;
    Serial.print("Sending to rf22_datagram_server");
    Serial.println(i);
    
    // Send a message to rf22_server
    if (!rf22.sendtoWait(data, sizeof(data), SERVER_ADDRESS))
      Serial.println("sendtoWait failed");
    else
    {
      // Now wait for a reply from the server
      //     Serial.println(rf22.lastRssi(), HEX); // of the ACK
      uint8_t len = sizeof(buf);
      uint8_t from;
      if (rf22.recvfromAckTimeout(buf, &len, 2000, &from))
      {
        Serial.print("client --- got reply from : 0x");
        Serial.print(from, HEX);
        Serial.print(": ");
        Serial.println((char*)buf);
      }
      else
      {
        Serial.println("No reply, is rf22_datagram_server running?");
      }
    }
    char buf[9];
    sprintf (buf, "%d", i);
    u8g.firstPage();
    do {
      draw(buf);
    } while ( u8g.nextPage() );
    delay(500);
  }
}