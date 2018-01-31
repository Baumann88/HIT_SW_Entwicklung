//-----------------------------------------------------------------------------
/*!
   \internal
   \file        in_out.c
   \brief       main module of input output example application for TC3

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
#define OUTPUT         "/proc/stw_io/PIN1"  // PIN 1 is also an input, we use this functionality
                                            // to read back the actual output status
#define INPUT          "/proc/stw_io/PIN2"

/* -- Types --------------------------------------------------------------- */


/* -- Global Variables ---------------------------------------------------- */

/* -- Module Global Variables --------------------------------------------- */
static sint16 ms16_Input;
static sint16 ms16_InOut;

/* -- Module Global Function Prototypes ----------------------------------- */
static void mv_ToggleOutput (void);
static void mv_ReadInput (void);

/* -- Implementation ------------------------------------------------------ */

//-----------------------------------------------------------------------------
/*!
   \brief   mv_ToggleOutput (void)

   The function read back the actual output status, After that, the function toggles the pin
   \return
   --

   \created       15.04.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   15.04.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void  mv_ToggleOutput (void)
{
   charn cn_status = 0;
   fd_set t_readfds;
   struct timeval t_Timeout;

   // Set timeout to zero --> no wait time
   t_Timeout.tv_sec = 0;
   t_Timeout.tv_usec = 0;
   ms16_InOut = open (OUTPUT, O_RDWR);
   if (ms16_InOut >=0)
   {
      // clear fds
      FD_ZERO (&t_readfds);

      // set
      FD_SET (ms16_InOut, &t_readfds);
      if (select (ms16_InOut + 1, &t_readfds, NULL, NULL, &t_Timeout) > 0)
      {
         // check if the corresponding bit is set in the fds
         if (FD_ISSET (ms16_InOut, &t_readfds))
         {
            (void)read (ms16_InOut, &cn_status, sizeof (charn));

            cn_status = (cn_status != 0x30)? 0x30: 0x31;  // 0x30 == 0
            (void) write (ms16_InOut, &cn_status, sizeof (charn));
         }
      }
      (void) close(ms16_InOut);
   }
}

//-----------------------------------------------------------------------------
/*!
   \brief   mv_ReadInput (void)

   The function read the Input Pin
   \return
   --

   \created       15.04.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   15.04.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void  mv_ReadInput (void)
{
   charn cn_status = 0;
   fd_set t_readfds;
   struct timeval t_Timeout;

   // Set timeout to zero --> no wait time
   t_Timeout.tv_sec = 0;
   t_Timeout.tv_usec = 0;
   ms16_Input = open (INPUT, O_RDONLY);
   if (ms16_InOut >=0)
   {
      // clear fds
      FD_ZERO (&t_readfds);

      // set
      FD_SET (ms16_Input, &t_readfds);
      if (select (ms16_Input + 1, &t_readfds, NULL, NULL, &t_Timeout) > 0)
      {
         // check if the corresponding bit is set in the fds
         if (FD_ISSET (ms16_Input, &t_readfds))
         {
            (void)read (ms16_Input, &cn_status, sizeof (charn));

            cn_status = (cn_status > 0x30)? 0x31: 0x30;  // 0x30 == 0
            printf ("Actual Input Pin status: %c\n", cn_status);
         }
      }
      (void) close(ms16_Input);
   }
}


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

   while (1)
   {
      if (cn_Input != '\n')
      {
         printf ("\nInput/Output Test Application TC3\n");
         printf (".---------------------------------.\n");
         printf ("|              Menu               |\n");
         printf ("'---------------------------------'\n");
         printf ("\t(0) Exit\n");
         printf ("\t(1) Toggle Output\n");
         printf ("\t(2) Read Input Pin\n");
      }
      cn_Input = getchar ();
      // switch between the different input values
      //------------------------------------------------------------------
      //
      //------------------------------------------------------------------
      if (cn_Input == '0')
      {
         // check if we have an filedescriptor still here opened
         if (ms16_InOut >= 0)
         {
            close(ms16_InOut);
         }
         if (ms16_Input >= 0)
         {
            close(ms16_Input);
         }
         break;
      }
      else if (cn_Input == '1')
      {
         // toggle output
         mv_ToggleOutput ();
      }
      else if (cn_Input == '2')
      {
         // read input
         mv_ReadInput ();
      }
   }
   return (0);
}


