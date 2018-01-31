//-----------------------------------------------------------------------------
/*!
   \internal
   \file        LED.c
   \brief       main module of LED example application for TC3

   \implementation
   project
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   created     23.03.2010  F.Belser
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author             Description
   23.03.2010        F.Belser           file created
   \endhistory
*/
//-----------------------------------------------------------------------------

/* -- Includes ------------------------------------------------------------ */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stwtypes.h"
#include "stwerror.h"   //STW errors
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

/* -- Defines ------------------------------------------------------------- */
#define LED_OFF             "0"
#define LED_RED             "1"
#define LED_GREEN           "2"
#define LED_YELLOW          "3"
#define LED_BLUE            "4"
#define LED_Pink            "5"
#define LED_CYAN            "6"
#define LED_WHITE           "7"

#define TRIGGER_TIMER       "timer"
#define TRIGGER_HEART       "heartbeat"
#define TRIGGER_NANDD       "nand-disk"
#define TRIGGER_NONE        "none"

#define DELAY_ON            "400"
#define DELAY_OFF           "1000"

#define LED_TRIGGER         "/sys/class/leds/status_led/trigger"
#define LED_BRIGHTNESS      "/sys/class/leds/status_led/brightness"
#define LED_TIMER_DELAY_ON  "/sys/class/leds/status_led/delay_on"
#define LED_TIMER_DELAY_OFF "/sys/class/leds/status_led/delay_off"

/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Module Global Variables --------------------------------------------- */
static sint16 ms16_fdTrigger;    // file descriptor
static sint16 ms16_fdBrightness; // file descriptor
static sint16 ms16_fdDelayOn;    // file descriptor
static sint16 ms16_fdDelayOff;   // file descriptor


/* -- Module Global Function Prototypes ----------------------------------- */

/* -- Implementation ------------------------------------------------------ */

//-----------------------------------------------------------------------------
/*!
   \brief   int main(void)

   \return

   \created       23.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   23.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
int main(void)
{
   charn cn_Input = '\0';

   // open the beeper file
   ms16_fdTrigger = open (LED_TRIGGER, O_WRONLY);
   // check if we could open the trigger file
   if (ms16_fdTrigger < 0)
   {
      printf ("Can't open the Trigger file: %i \n", ms16_fdTrigger);
   }
   else
   {
      // we use the brightness file for setting the LED colour. Brightness isn't necessary
      // becaue we use a LED (on or off)
      ms16_fdBrightness = open (LED_BRIGHTNESS, O_WRONLY);
      if (ms16_fdBrightness < 0)
      {
         printf ("Can't open the Brightness file: %i \n", ms16_fdBrightness);
      }
      else
      {
         while (1)
         {
            if (cn_Input != '\n')
            {
               printf ("\nLED Test Application TC3\n");
               printf (".---------------------------------.\n");
               printf ("|              Menu               |\n");
               printf ("'---------------------------------'\n");
               printf ("\t(0) Exit\n");
               printf ("\t(1) Set LED OFF\n");
               printf ("\t(2) Set LED RED\n");
               printf ("\t(3) Set LED Green\n");
               printf ("\t(4) Set LED Yellow\n");
               printf ("\t(5) Set LED Blue\n");
               printf ("\t(6) Set LED Pink\n");
               printf ("\t(7) Set LED Cyan\n");
               printf ("\t(8) Set LED White\n");
               printf ("\t(9) Activate LED Heartbeat\n");
               printf ("\t(a) Activate LED Timer\n");
               printf ("\t(b) Activate LED Nand disk\n");
            }
            cn_Input = getchar ();
            // switch between the different input values
            //------------------------------------------------------------------
            //
            //------------------------------------------------------------------
            if (cn_Input == '0')
            {
               // check if we have an trigger file descriptor
               if (ms16_fdBrightness >= 0)
               {
                  close(ms16_fdBrightness);
               }
               // check if we have an trigger file descriptor
               if (ms16_fdTrigger >= 0)
               {
                  close (ms16_fdTrigger);
               }
               break;
            }
            else if (cn_Input == '1')
            {
               // set trigger to none
               (void) write (ms16_fdTrigger, TRIGGER_NONE, strlen (TRIGGER_NONE));
               // set colour
               (void) write (ms16_fdBrightness, LED_OFF, strlen (LED_OFF));
            }
            else if (cn_Input == '2')
            {
               // set trigger to none
               (void) write (ms16_fdTrigger, TRIGGER_NONE, strlen (TRIGGER_NONE));
               // set colour
               (void) write (ms16_fdBrightness, LED_RED, strlen (LED_RED));
            }
            else if (cn_Input == '3')
            {
               // set trigger to none
               (void) write (ms16_fdTrigger, TRIGGER_NONE, strlen (TRIGGER_NONE));
               // set colour
               (void) write (ms16_fdBrightness, LED_GREEN, strlen (LED_GREEN));
            }
            else if (cn_Input == '4')
            {
               // set trigger to none
               (void) write (ms16_fdTrigger, TRIGGER_NONE, strlen (TRIGGER_NONE));
               // set colour
               (void) write (ms16_fdBrightness, LED_YELLOW, strlen (LED_YELLOW));
            }
            else if (cn_Input == '5')
            {
               // set trigger to none
               (void) write (ms16_fdTrigger, TRIGGER_NONE, strlen (TRIGGER_NONE));
               // set colour
               (void) write (ms16_fdBrightness, LED_BLUE, strlen (LED_BLUE));
            }
            else if (cn_Input == '6')
            {
               // set trigger to none
               (void) write (ms16_fdTrigger, TRIGGER_NONE, strlen (TRIGGER_NONE));
               // set colour
               (void) write (ms16_fdBrightness, LED_Pink, strlen (LED_Pink));
            }
            else if (cn_Input == '7')
            {
               /// set trigger to none
               (void) write (ms16_fdTrigger, TRIGGER_NONE, strlen (TRIGGER_NONE));
               // set colour
               (void) write (ms16_fdBrightness, LED_CYAN, strlen (LED_CYAN));
            }
            else if (cn_Input == '8')
            {
               // set trigger to none
               (void) write (ms16_fdTrigger, TRIGGER_NONE, strlen (TRIGGER_NONE));
               // set colour
               (void) write (ms16_fdBrightness, LED_WHITE, strlen (LED_WHITE));
            }
            else if (cn_Input == '9')
            {
               // set trigger to HEART
               (void) write (ms16_fdTrigger, TRIGGER_HEART, strlen (TRIGGER_HEART));
            }
            else if (cn_Input == 'a')
            {
               // set trigger to TIMER
               (void) write (ms16_fdTrigger, TRIGGER_TIMER, strlen (TRIGGER_TIMER));
               // open fd to delay_on
               ms16_fdDelayOn = open(LED_TIMER_DELAY_ON, O_WRONLY);
               if (ms16_fdDelayOn >= 0)
               {
                  ms16_fdDelayOff = open(LED_TIMER_DELAY_OFF, O_WRONLY);
                  if (ms16_fdDelayOff >= 0)
                  {
                     (void) write (ms16_fdDelayOn, DELAY_ON, strlen (DELAY_ON));
                     (void) write (ms16_fdDelayOff, DELAY_OFF, strlen (DELAY_OFF));
                  }
                  else
                  {
                     printf ("Can't open delay off file\n");
                  }
               }
               else
               {
                  printf ("Can't open delay on file\n");
               }
               // close file descriptors
               if (ms16_fdDelayOn >= 0)
               {
                  close (ms16_fdDelayOn);
               }
               if (ms16_fdDelayOff >= 0)
               {
                  close (ms16_fdDelayOff);
               }
            }
            else if (cn_Input == 'b')
            {
               // set trigger to NAND Disk
               (void) write (ms16_fdTrigger, TRIGGER_NANDD, strlen (TRIGGER_NANDD));
            }
         }
      }
   }
   return (0);
}
