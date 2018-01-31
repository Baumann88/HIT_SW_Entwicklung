
//-----------------------------------------------------------------------------
/*!
   \internal
   \file          ysignal-dbus-example.c
   \brief         Example application for the ysignald

   Example code to test the ysignald without using ynetworkd and ygpsd.

   \implementation
   copyright   STW (c) 1999-2015
   license     use only under terms of contract / confidential

   created     06.02.2015  STW/A.Appelt
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author            Description
   06.02.2015        STW/A.Appelt      funciton created
   \endhistory
*/
//---------------------------------------------------------------------------/*

/* -- Includes ------------------------------------------------------------ */
#include "stwtypes.h"
#include <stdbool.h>
#include "DP_dbus_handler.h"
#include "utils.h"
#include "Signal_handler.h"
/* -- Defines ------------------------------------------------------------- */
#define PROG_VERSION         "v0_01r0"
#define MY_DBUS_NAME         "dbus_ysignald_appl"
#define MY_DBUS_ADDINFO      "Example application for ysignald"

/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Module Global Variables --------------------------------------------- */
T_DBUS_Util mt_dbus_util;
/* -- Module Global Function Prototypes ----------------------------------- */
/* -- Implementation ------------------------------------------------------ */

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/*!
   \brief  int main(void)

   Main function of the ysignald dbus example application


   \param[in]     none

   \return        0

   \created       06.02.2015  STW/A.Appelt

   \internal
   \history
   Date(dd.mm.yyyy)  Author            Description
   06.02.2015        STW/A.Appelt      funciton created
   \endhistory
*/
//-----------------------------------------------------------------------------

int main(void)
{
   charn cn_inputState = '\0';
   charn cn_inputSignal = '\0';
   charn acn_signalState[32] = {0};
   sint32 s32_retval = C_NO_ERR;
   bool q_subLoop = true;
   bool q_send_message = false;


   // Initialise the dbus structure
   (void)sprintf(mt_dbus_util.acn_myNameString , MY_DBUS_NAME);
   (void)sprintf(mt_dbus_util.acn_myVersion    , PROG_VERSION);
   (void)sprintf(mt_dbus_util.acn_myStatus     , "unknown");
   (void)sprintf(mt_dbus_util.acn_myAddInfo    , MY_DBUS_ADDINFO);

   /* Register with DBUS*/
   if(dbus_get_on_the_bus(&mt_dbus_util) != 0)
   {
      (void)utils_log_print("Register ysignald_dbus_example on DBUS failed");
      return(1);
   }

   while (1)
   {
      // init loop variable
      q_subLoop = true;

      if (cn_inputSignal != '\n')
      {
         printf ("\nysignald Test Application TC3G\n");
         printf (".------------------------------------------------------------.\n");
         printf ("|                         Main-Menu                          |\n");
         printf ("'------------------------------------------------------------'\n");
         printf ("\t(0) Exit\n");
         printf ("\t(1) Send DBUS-signal: 'Internet_Connection_State'\n");
         printf ("\t(2) Send DBUS-signal: 'GPS_Connection_State'\n");
      }
      cn_inputSignal = getchar ();
      // switch between the different input values
      if (cn_inputSignal == '0')
      {
         // exit
         return 1;
      }
      else if (cn_inputSignal == '1')
      {
         // choose signal state for internet connection signal
         while (q_subLoop)
         {
            if (cn_inputState != '\n')
            {
               printf ("\n.------------------------------------------------------------.\n");
               printf ("|                  Internet_Connection_State                 |\n");
               printf ("'------------------------------------------------------------'\n");
               printf ("\t(0) Exit\n");
               printf ("\t(1) Select signal state: 'ETH'\n");
               printf ("\t(2) Select signal state: 'WLAN'\n");
               printf ("\t(3) Select signal state: 'PPP'\n");
               printf ("\t(4) Select signal state: 'NotConnected'\n");
               printf ("\t(r) Return to main menu\n");
            }
            cn_inputState = getchar ();
            // switch between the different input values
            if (cn_inputState == '0')
            {
               // exit
               return 1;
            }
            else if (cn_inputState == '1')
            {
               // set signal state to 'ETH'
               (void)sprintf(acn_signalState, "ETH");
               q_send_message = true;
            }
            else if (cn_inputState == '2')
            {
               // set signal state to 'WLAN'
               (void)sprintf(acn_signalState, "WLAN");
               q_send_message = true;
            }
            else if (cn_inputState == '3')
            {
               // set signal state to 'PPP'
               (void)sprintf(acn_signalState, "PPP");
               q_send_message = true;
            }
            else if (cn_inputState == '4')
            {
               // set signal state to 'NotConnected'
               (void)sprintf(acn_signalState, "NotConnected");
               q_send_message = true;
            }
            else if (cn_inputState == 'r')
            {
               // return to main loop
               q_subLoop = false;
            }

            if (q_send_message == true)
            {
               // send dbus signal
               s32_retval = ysignald_internet_con_state(&mt_dbus_util, acn_signalState);
               if (s32_retval == C_NO_ERR)
               {
                  printf("Sending 'Internet_Connection_State' signal with state '%s' -> successfull.\n",acn_signalState);

               }
               else
               {
                  printf("Sending 'Internet_Connection_State' signal with state '%s' -> faild.\n",acn_signalState);
                  // print retval
                  printf("Return value: %d\n", (int)s32_retval);
               }
               q_send_message = false;
            }
         }
      }
      else if (cn_inputSignal == '2')
      {
         // choose signal state for GPS connection signal
         while (q_subLoop)
         {
            if (cn_inputState != '\n')
            {
               printf ("\n.------------------------------------------------------------.\n");
               printf ("|                    GPS_Connection_State                    |\n");
               printf ("'------------------------------------------------------------'\n");
               printf ("\t(0) Exit\n");
               printf ("\t(1) Select signal state: 'Valid'\n");
               printf ("\t(2) Select signal state: 'Invalid'\n");
               printf ("\t(r) Return to main menu\n");
            }
            cn_inputState = getchar ();
            // switch between the different input values
            if (cn_inputState == '0')
            {
               // exit
               return 1;
            }
            else if (cn_inputState == '1')
            {
               // set signal state to 'Valid'
               (void)sprintf(acn_signalState, "Valid");
               q_send_message = true;
            }
            else if (cn_inputState == '2')
            {
               // set signal state to 'Invalid'
               (void)sprintf(acn_signalState, "Invalid");
               q_send_message = true;
            }
            else if (cn_inputState == 'r')
            {
               // return to main loop
               q_subLoop = false;
            }

            if (q_send_message == true)
            {
               // send dbus signal
               s32_retval = ysignald_GPS_con_state(&mt_dbus_util, acn_signalState);
               if (s32_retval == C_NO_ERR)
               {
                  printf("Sending 'GPS_Connection_State' signal with state '%s' -> successfull.\n",acn_signalState);

               }
               else
               {
                  printf("Sending 'GPS_Connection_State' signal with state '%s' -> faild.\n",acn_signalState);
                  // print retval
                  printf("Return value: %d\n", (int)s32_retval);
               }
               q_send_message = false;
            }
         }
      }
   }
   return 0;
}

