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
