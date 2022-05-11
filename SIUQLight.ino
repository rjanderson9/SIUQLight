/* UDP Messaging Cue Light System for 12 Cue lights
  The frst phase has been adding libraries, definitions, and creating the terminal control 
  for the operator to click buttons to identify neopixel LED for starting preset(RED) 
  to standby(YELLO) to Go(GREEN) and back to wait.
  
  April 2022
  Created by Zach Alley and Rob Anderson(Teaching Faculty)
 */


#include <Ethernet.h>   //Include Ethernet setup library 
#include <EthernetUdp.h>   //Include UDP Messaging on Ethernet library
#include <BtButton.h>   //INclude selective button funciton libary
#define UDP_TX_PACKET_MAX_SIZE 128   // Increase UDP Size
#define STATE_OFF 0   //Define Neo Pixels constant state as 0 *capitalize all define titles
#define STATE_STDBY 1 //Define Standby constant value for entire program
#define STATE_GO 2 // Define go state constant value for entire program
#define STATE_ACK 3 //Define acknowledge or preset constant value for entire program
#define STATE_ERROR 4 //Define error state when linking with receivers in the void setup program


const int maxChannels = 12;// set constant intger for max channels of data
byte standbyState [] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; // store set of stand by state variables
byte currentState []= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; //store set of stand by current variables
 
BtButton btn1 (1, 50, 500, false); //set 1 button with pin address, bounce back, read time, false=hold state  
BtButton btn2 (2, 50, 500, false); //set 2 button with pin address, bounce back, read time, false=hold state  
BtButton btn3 (3, 50, 500, false); //set 3 button with pin address, bounce back, read time, false=hold state  
BtButton btn4 (4, 50, 500, false); //set 4 button with pin address, bounce back, read time, false=hold state  
BtButton btn5 (5, 50, 500, false); //set 5 button with pin address, bounce back, read time, false=hold state  
BtButton btn6 (6, 50, 500, false); //set 6 button with pin address, bounce back, read time, false=hold state  
BtButton btn7 (7, 50, 500, false); //set 7 button with pin address, bounce back, read time, false=hold state  
BtButton btn8 (8, 50, 500, false); //set 8 button with pin address, bounce back, read time, false=hold state  
BtButton btn9 (9, 50, 500, false); //set 9 button with pin address, bounce back, read time, false=hold state  
BtButton btn10 (10, 50, 500, false); //set 10 button with pin address, bounce back, read time, false=hold state  
BtButton btn11 (11, 50, 500, false); //set 11 button with pin address, bounce back, read time, false=hold state  
BtButton btn12 (12, 50, 500, false); //set 12 button with pin address, bounce back, read time, false=hold state  
BtButton btnGo (13, 50, 500, false); //set go button with pin address, bounce back, read time, false=hold state  
BtButton btnReset(14, 50, 500, false); //set reset button with pin address, bounce back, read time, false=hold state  



byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};  //Mac address of Arduinio

IPAddress ip(192, 168, 1, 177);//IP address of Arduinio

unsigned int localPort = 8888;  // local port to listen on

char packetBuffer[] = "";  // buffer to hold incoming packet,

char statusData[] = "";  //Data to send to App

EthernetUDP Udp;  // An EthernetUDP instance to let us send and receive packets over UDP

void setup()
{
 
Ethernet.begin(mac, ip);    // start the Ethernet

Udp.begin(localPort);  // start UDP
  
// Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) 
{
    {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    }
    while (true)
    {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

Serial.begin(9600);  // Open serial communications and wait for port to open:

}

void loop() //program starts here
{
 {
   buttonRead(); //begin function to read through button program
 }
 {
   updateLEDs(); //begin function to read through to change LEDs program
 }
 {
   sendData(); //begin function to send data packets back from receivers
 }
  int packetSize = Udp.parsePacket (); // store the the Udp packet data in the variable packetSize
  if (packetSize)       // if you receive data goto
    {
      processPacket ();    //process the UDP data
    }
}
