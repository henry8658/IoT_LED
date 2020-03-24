/*
 * Title: IOT LED Display
 * Written by: Henry Park
 * Date: 03/21/2020
 * Description: Send a message Via HTTP and display the message on LED penel.
 */

#include <MD_Parola.h>
#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

const int MAX_DEVICES = 4;
const int CLK_PIN = D7, CS_PIN = D6, DATA_PIN = D5;
const int SPEED_TIME = 200;
const int PAUSE_TIME = 1000;

// initiate MD_Parola object 
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

uint8_t scrollSpeed = 500;    // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 500; // in milliseconds

// Global message buffers shared by Serial and Scrolling functions
const int BUF_SIZE = 75;
char curMessage[BUF_SIZE] = { "" };
char newMessage[BUF_SIZE] = { "Hello! Enter new message?" };
bool newMessageAvailable = true;



uint8_t Left[] = 
{ 
  9,
  B00011000,
  B00111100,
  B01111110,
  B11111111,
  B00111100,
  B00111100,
  B00111100,
  B00111100,
  B00000000,
};


uint8_t Right[] = 
{ 
  9,
  B00000000,
  B00111100,
  B00111100,
  B00111100,
  B00111100,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
};

uint8_t Mid[] = 
{ 
  10,
  B11110000,
  B11110000,
  B11110000,
  B11111111,
  B11111111,
  B11111111,
  B11100000,
  B11100000,
  B11000000,
  B11000000,
};

void readSerial(void)
{
  static char *cp = newMessage;

  while (Serial.available())
  {
    *cp = (char)Serial.read();
    if ((*cp == '\n') || (cp - newMessage >= BUF_SIZE-2)) // end of message character or full buffer
    {
      *cp = '\0'; // end the string
      // restart the index for next filling spree and flag we have a message waiting
      cp = newMessage;
      newMessageAvailable = true;
    }
    else  // move char pointer to next position
      cp++;
  }
}

void setup()
{
  Serial.begin(57600);

  P.begin();
  P.addChar('<', Left);
  P.addChar('>', Right);
  P.addChar('^', Mid);
  //P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
}

void loop()
{
//  if (P.displayAnimate())
//  {
//    if (newMessageAvailable)
//    {
//      strcpy(curMessage, newMessage);
//      newMessageAvailable = false;
//    }
//    P.displayReset();
//  }
//  readSerial();
  test3();
  P.displayReset();
}



void test1()
{
  P.displayText(">", PA_RIGHT, scrollSpeed, scrollPause, PA_PRINT, PA_PRINT);
  while(!P.displayAnimate());
}


void test()
{
  P.displayText(">", scrollAlign, scrollSpeed, scrollPause, PA_PRINT, PA_PRINT);
  while(!P.displayAnimate());
}

void test3()
{
  P.displayText("^", PA_CENTER, scrollSpeed, scrollPause, PA_PRINT, PA_PRINT);
  while(!P.displayAnimate());
}
