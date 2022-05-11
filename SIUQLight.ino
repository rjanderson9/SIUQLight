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

void buttonRead() // set up a function to run reading buttons being pressed
{
  btn1.read(); //Read Button 1
    if (btn1.changed()&&btn1.isPressed()) //if button 1 changed state and is pressed goto below
    {
     incrementState(1); // change increment state to send data for color change
    }
  
  btn2.read(); //Read Button 2
    if (btn2.changed()&&btn2.isPressed()) //if button 2 changed state and is pressed goto below
    {
     incrementState(2); // change increment state to send data for color change
    }
  
  btn3.read(); //Read Button 3
    if (btn3.changed()&&btn3.isPressed()) //if button 3 changed state and is pressed goto below
    {
     incrementState(3);// change increment state to send data for color change
    }
  
  btn4.read(); //Read Button 4 
   if (btn4.changed()&&btn4.isPressed()) //if button 4 changed state and is pressed goto below
    {
     incrementState(4);// change increment state to send data for color change
    }
    
  btn5.read(); //Read Button 5
   if (btn5.changed()&&btn5.isPressed()) //if button 5 changed state and is pressed goto below
    {
     incrementState(4);// change increment state to send data for color change
    }
  
  btn6.read(); //Read Button 6
   if (btn6.changed()&&btn6.isPressed()) //if button 6 changed state and is pressed goto below
    {
     incrementState(5);// change increment state to send data for color change
    }
  
  btn7.read(); //Read Button 7
   if (btn7.changed()&&btn7.isPressed()) //if button 7 changed state and is pressed goto below
    {
     incrementState(6);// change increment state to send data for color change
    }
  
  btn8.read(); //Read Button 8
   if (btn6.changed()&&btn8.isPressed()) //if button 8 changed state and is pressed goto
    {
     incrementState(7);// change increment state to send data for color change 
    }
  
  btn9.read(); //Read Button 9
   if (btn6.changed()&&btn9.isPressed()) //if button 9 changed state and is pressed goto  
    {
     incrementState(8);// change increment state to send data for color change 
    }
  
  btn10.read(); //Read Button 10 
   if (btn6.changed()&&btn10.isPressed()) //if button 10 changed state and is pressed goto
    {
     incrementState(9);// change increment state to send data for color change 
    }
  
  btn11.read(); //Read Button 11
   if (btn6.changed()&&btn11.isPressed()) //if button 11 changed state and is pressed goto
    {
     incrementState(10);// change increment state to send data for color change 
    }
  
  btn12.read();  //Read Button 12
   if (btn6.changed()&&btn12.isPressed()) //if button 12 changed state and is pressed goto
    {
     incrementState(11);// change increment state to send data for color change 
    }
  
  btnGo.read();  //Read Go Button
      if (btnGo.changed()&&btnGo.isPressed()) //if Go button changed and state and is pressed goto
       {
         for( int i=0; i<maxChannels; ++i) // creating loop to collect all data channels
            {
              currentState[i]=standbyState[i]; // sets the current state as the stand by state
            }
        }
     
  btnReset.read();  //Read Reset Button
      if (btnReset.changed()&&btnReset.isPressed())  //if Reset button changed and state and is pressed goto
       {
         for( int i=0; i<maxChannels; i++) // a for loop to collect all data channels
           {
             standbyState[i]=STATE_OFF; // sets the standby state to zero
             currentState[i]=STATE_OFF; // sets the current state to zero
            }
       }
}

  
void incrementState (int ch)  //sets a function to search and set stand by state
  { 
  if( standbyState[ch-1] == STATE_OFF ) // if the standby state is off goto...
  {
    standbyState[ch-1] == STATE_GO;   // sets the stand by state channel to a go state
    currentState[ch-1] == STATE_STDBY; //sets the current state channel to stand by state
  }
  if( standbyState[ch-1] == STATE_GO ) // if the standby state is go/on goto...
  {
    standbyState[ch-1] == STATE_OFF; // sets the standby state channel to off/0
    currentState[ch-1] == STATE_OFF;  // sets the current state channel to off/0
  }

  }

void updateLEDs() //program to change leds after changing of states
{
  
}
void sendData() //program to send data to receivers 
{
  
}
void processPacket () //program to process data packets sent to receivers and data sent to transmitter
{
  
}
