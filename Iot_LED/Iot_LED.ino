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
const int SPEED_TIME  25
const int PAUSE_TIME  1000

// initiate MD_Parola object 
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

uint8_t  curText;

const char  *pc[] =
{
  "Henry"
};

uint8_t  inFX, outFX;
textEffect_t  effect[] =
{
  PA_PRINT,
  PA_SCAN_HORIZ,
  PA_SCROLL_LEFT,
  PA_WIPE,
  PA_SCROLL_UP_LEFT,
  PA_SCROLL_UP,
  PA_OPENING_CURSOR,
  PA_GROW_UP,
  PA_MESH,
  PA_SCROLL_UP_RIGHT,
  PA_BLINDS,
  PA_CLOSING,
  PA_RANDOM,
  PA_GROW_DOWN,
  PA_SCAN_VERT,
  PA_SCROLL_DOWN_LEFT,
  PA_WIPE_CURSOR,
  PA_DISSOLVE,
  PA_OPENING,
  PA_CLOSING_CURSOR,
  PA_SCROLL_DOWN_RIGHT,
  PA_SCROLL_RIGHT,
  PA_SLICE,
  PA_SCROLL_DOWN,
};

void setup(void)
{
  P.begin();
  P.setInvert(false);
  P.displayText(pc[curText], PA_CENTER, SPEED_TIME, PAUSE_TIME, effect[inFX], effect[outFX]);
}

void loop(void)
{

  if (P.displayAnimate()) // animates and returns true when an animation is completed
  {
    // Set the display for the next string.
    curText = (curText + 1) % ARRAY_SIZE(pc);
    P.setTextBuffer(pc[curText]);

    // When we have gone back to the first string, set a new exit effect
    // and when we have done all those set a new entry effect.
    if (curText == 0)
    {
      outFX = (outFX + 1) % ARRAY_SIZE(effect);
      if (outFX == 0)
      {
        inFX = (inFX + 1) % ARRAY_SIZE(effect);
        if (inFX == 0)
          P.setInvert(!P.getInvert());
      }

      P.setTextEffect(effect[inFX], effect[outFX]);
    }

    // Tell Parola we have a new animation
    P.displayReset();
  }
}
