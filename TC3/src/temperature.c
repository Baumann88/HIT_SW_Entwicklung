//-----------------------------------------------------------------------------
/*!
   \internal
   \file        temperature.c
   \brief       main module of Temperature sensor example application for TC3

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
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stwtypes.h"
#include "stwerror.h"   //STW errors
#include <sys/time.h>
#include <fcntl.h>



/* -- Defines ------------------------------------------------------------- */
#define TEMP_SENSOR "/sys/bus/spi/devices/spi32766.1/temp1_input"
/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Module Global Variables --------------------------------------------- */
static sint16 ms16_fdTemp;    // file descriptor

static struct timeval mt_TimeSinceInit;


/* -- Module Global Function Prototypes ----------------------------------- */
static uint32 mu32_sys_get_time_ms (void);
static void mv_read (charn *const opcn_Temp);
static void mv_open (void);
static void mv_close (void);

/* -- Implementation ------------------------------------------------------ */
//-----------------------------------------------------------------------------
/*!
   \brief   static void mv_open (void)

   function open fd to the necessary file

   \created       11.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   11.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mv_open (void)
{
   // open the motion sensor files
   ms16_fdTemp = open (TEMP_SENSOR, O_RDONLY);
   // check if we could open the file
   if (ms16_fdTemp < 0)
   {
      printf ("Can't open the temperature sensor file: %i \n", ms16_fdTemp);
   }
}


//-----------------------------------------------------------------------------
/*!
   \brief   static void mv_close (void)

   function closes the fd

   \created       11.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   11.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mv_close (void)
{
   // check if we have a fd
   if (ms16_fdTemp >= 0)
   {
      (void)close(ms16_fdTemp);
   }
}


//-----------------------------------------------------------------------------
/*!
   \brief   Implementaition of mu32_sys_get_time_ms
            The function returns the actual TC3 time since init was called
            in milliseconds

   \return
   Up Time in millisecsonds

   \created       11.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   11.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static uint32 mu32_sys_get_time_ms (void)
{
   struct timeval t_TimeNow;
   uint64 u64_TimeMsNow                = 0;
   uint64 u64_TimeMsInit               = 0;
   uint32 u32_ActualTimeInMilliseconds = 0;
   static uint8 hu8_FirstTimeFlag      = 1;

   // store the actual time on init
   if (hu8_FirstTimeFlag == 1)
   {
      (void) gettimeofday (&mt_TimeSinceInit, NULL);
      hu8_FirstTimeFlag = 0;
   }
   // get actual time
   (void) gettimeofday (&t_TimeNow, NULL);
   // complete time in ms of the actual time
   u64_TimeMsNow  = (((uint64)t_TimeNow.tv_sec        * 1000) + ((uint64)t_TimeNow.tv_usec        / 1000));
   // complete time in ms of the init call time
   u64_TimeMsInit = (((uint64)mt_TimeSinceInit.tv_sec * 1000) + ((uint64)mt_TimeSinceInit.tv_usec / 1000));
   u32_ActualTimeInMilliseconds = (uint32)(u64_TimeMsNow - u64_TimeMsInit);
   return (u32_ActualTimeInMilliseconds);
}


//-----------------------------------------------------------------------------
/*!
   \brief   mv_read (charn *const opcn_Temp)

   \param[out] opcn_Temp reference to the read X value



   \created       11.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   11.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mv_read (charn *const opcn_Temp)
{
   fd_set t_readfds;
   struct timeval t_Timeout;
   // Set timeout to zero --> no wait time
   t_Timeout.tv_sec = 0;
   t_Timeout.tv_usec = 0;
   // open the files
   mv_open ();
   // check the fd
   if (ms16_fdTemp >= 0)
   {
      // clear fds
      FD_ZERO (&t_readfds);
      // set
      FD_SET (ms16_fdTemp, &t_readfds);
      // check if we are ready to read)
      if (select (ms16_fdTemp + 1, &t_readfds, NULL, NULL, &t_Timeout) > 0)
      {
         // check if the corresponding bit is set in the fds
         if (FD_ISSET (ms16_fdTemp, &t_readfds))
         {
            (void)read (ms16_fdTemp, opcn_Temp, 9);
         }
      }
   }
   else
   {
      printf ("No valid file descriptors\n");
      usleep (1000 * 1000);
   }
   mv_close ();
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
   charn cn_Input        = '\0';
   charn acn_Read[10]    = {0};
   sint32 s32_Read       = 0;
   uint32 u32_Timer1     = 0;
   fd_set t_readfds;
   struct timeval t_Timeout;

   // Set timeout to zero --> no wait time
   t_Timeout.tv_sec = 0;
   t_Timeout.tv_usec = 0;

   u32_Timer1 = mu32_sys_get_time_ms ();
   while (1)
   {
      if ((u32_Timer1 + 100) < mu32_sys_get_time_ms())
      {
         // read the actual x,y,z position
         mv_read (acn_Read);
         // reload timer;
         u32_Timer1 = mu32_sys_get_time_ms ();
         // clear screen
         printf ("\033[2J");
         // print menu
         printf ("\nTemperature Sensor Test Application TC3\n");
         printf (".---------------------------------.\n");
         printf ("|              Menu               |\n");
         printf ("'---------------------------------'\n");
         printf ("\t(0) Exit\n\n\n");
         // convert array of charn to sint16
         s32_Read = atoi (acn_Read);
         printf ("Actual temperature in Celsius   : %ld.%ld\n", s32_Read / 1000, s32_Read % 1000);
         s32_Read = (s32_Read * 9) / 5 + 32; // * 1.8 +32
         printf ("Actual temperature in Fahrenheit: %ld.%ld\n", s32_Read / 1000, s32_Read % 1000);
      }
      // clear fds
      FD_ZERO(&t_readfds);
      // set read fds
      FD_SET(STDIN_FILENO, &t_readfds);
      // check if we are ready to read
      if (select (STDIN_FILENO + 1, &t_readfds, NULL, NULL, &t_Timeout) > 0)
      {
         // check if corresponding bit is set in the fds
         if (FD_ISSET(STDIN_FILENO, &t_readfds))
         {
            (void)read (STDIN_FILENO, &cn_Input, 1);
         }
      }
      // switch between the different input values
      if (cn_Input == '0')
      {
         break;
      }
   }
   return (0);
}

