//-----------------------------------------------------------------------------
/*!
   \internal
   \file        motion.c
   \brief       main module of Motion sensor example application for TC3

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
#define TC3_MOTION_SENSOR_X "/sys/bus/i2c/devices/0-001c/x"
#define TC3_MOTION_SENSOR_Y "/sys/bus/i2c/devices/0-001c/y"
#define TC3_MOTION_SENSOR_Z "/sys/bus/i2c/devices/0-001c/z"
#define TC3G_MOTION_SENSOR_X "/sys/bus/i2c/devices/0-0018/x"
#define TC3G_MOTION_SENSOR_Y "/sys/bus/i2c/devices/0-0018/y"
#define TC3G_MOTION_SENSOR_Z "/sys/bus/i2c/devices/0-0018/z"
/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Module Global Variables --------------------------------------------- */
static uint8 mu8_TC3G = 0;

static sint16 ms16_fdX;    // file descriptor
static sint16 ms16_fdY; // file descriptor
static sint16 ms16_fdZ;    // file descriptor

static charn macn_motion_sensor_x[32] = {0};
static charn macn_motion_sensor_y[32] = {0};
static charn macn_motion_sensor_z[32] = {0};

static struct timeval mt_TimeSinceInit;

/* -- Module Global Function Prototypes ----------------------------------- */
static uint32 mu32_sys_get_time_ms (void);
static void mv_read (charn *const opcn_X, charn *const opcn_Y, charn *const opcn_Z);
static void mv_draw (const sint16 * const ops16_X, const sint16 * const ops16_Y,
                     const sint16 * const ops16_Z);
static sint16 ms16_MaxFd (sint16 *const ops16_X, sint16 *const ops16_Y, sint16 *const ops16_Z);
static void mv_open (void);
static void mv_close (void);

/* -- Implementation ------------------------------------------------------ */
//-----------------------------------------------------------------------------
/*!
   \brief   static void mv_open (void)

   function open the fd to the necessary files

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
   ms16_fdX = open (macn_motion_sensor_x, O_RDONLY);
   // check if we could open the file
   if (ms16_fdX < 0)
   {
      printf ("Can't open the motion sensor x file: %i \n", ms16_fdX);
   }
   ms16_fdY = open (macn_motion_sensor_y, O_RDONLY);
   if (ms16_fdY < 0)
   {
      printf ("Can't open the motion sensor y file: %i \n", ms16_fdY);
   }
   ms16_fdZ = open (macn_motion_sensor_z, O_RDONLY);
   if (ms16_fdZ < 0)
   {
      printf ("Can't open the motion sensor z file: %i \n", ms16_fdZ);
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
   // check if we have fds
   if (ms16_fdX >= 0)
   {
      (void)close(ms16_fdX);
   }
   // check if we have an trigger file descriptor
   if (ms16_fdY >= 0)
   {
      (void)close (ms16_fdY);
   }
   // check if we have an trigger file descriptor
   if (ms16_fdZ >= 0)
   {
      (void)close (ms16_fdZ);
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
   \brief   ms16_MaxFd (charn *const opcn_X, charn *const opcn_Y, charn *const opcn_Z)

   Function returns the highest fd

   \param[out] ops16_X reference to the X fd
   \param[out] ops16_Y reference to the Y fd
   \param[out] ops16_Z reference to the Z fd


   \created       11.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   11.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static sint16 ms16_MaxFd (sint16 *const ops16_X, sint16 *const ops16_Y, sint16 *const ops16_Z)
{
   sint16 as16_Fds[3];
   sint16 s16_tmp   = 0;
   uint8 u8_counter = 0;

   as16_Fds[0] = *ops16_X;
   as16_Fds[1] = *ops16_Y;
   as16_Fds[2] = *ops16_Z;
   for (u8_counter = 1; u8_counter < 3; u8_counter++)
   {
      if (as16_Fds[0] < as16_Fds[u8_counter])
      {
         s16_tmp = as16_Fds[0];
         as16_Fds[0] = as16_Fds[u8_counter];
         as16_Fds[u8_counter] = s16_tmp;
      }
   }
   return (as16_Fds[0]);
}


//-----------------------------------------------------------------------------
/*!
   \brief   mv_read (charn *const opcn_X, charn *const opcn_Y, charn *const opcn_Z)

   \param[out] opcn_X reference to the read X value
   \param[out] opcn_Y reference to the read Y value
   \param[out] opcn_Z reference to the read Z value


   \created       11.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   11.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mv_read (charn *const opcn_X, charn *const opcn_Y, charn *const opcn_Z)
{
   fd_set t_readfds;
   struct timeval t_Timeout;
   sint16 s16_MaxFd = 0;
   // Set timeout to zero --> no wait time
   t_Timeout.tv_sec = 0;
   t_Timeout.tv_usec = 0;
   // open the files
   mv_open ();
   // check the fd
   if ((ms16_fdX >= 0) && (ms16_fdY >=0) && (ms16_fdZ >=0))
   {
      // clear fds
      FD_ZERO (&t_readfds);
      // set
      FD_SET (ms16_fdX, &t_readfds);
      FD_SET (ms16_fdY, &t_readfds);
      FD_SET (ms16_fdZ, &t_readfds);
      // get the greatest fd
      s16_MaxFd = ms16_MaxFd (&ms16_fdX, &ms16_fdY, &ms16_fdZ);
      // check if we are ready to read)
      if (select (s16_MaxFd + 1, &t_readfds, NULL, NULL, &t_Timeout) > 0)
      {
         // check if the corresponding bit is set in the fds
         if (FD_ISSET (ms16_fdX, &t_readfds))
         {
            (void)read (ms16_fdX, opcn_X, 9);
         }
         // check if the corresponding bit is set in the fds
         if (FD_ISSET (ms16_fdY, &t_readfds))
         {
            (void)read (ms16_fdY, opcn_Y, 9);
         }
         // check if the corresponding bit is set in the fds
         if (FD_ISSET (ms16_fdZ, &t_readfds))
         {
            (void)read (ms16_fdZ, opcn_Z, 9);
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
   charn acn_Read[3][10] = {{0},{0},{0}};
   sint16 as16_Read[3]   = {0};
   uint32 u32_Timer1     = 0;
   uint8 u8_counter1     = 0;
   fd_set t_readfds;
   struct timeval t_Timeout;
   FILE * in_stream;
   charn acn_deviceID[10] = {0};

   // Set timeout to zero --> no wait time
   t_Timeout.tv_sec = 0;
   t_Timeout.tv_usec = 0;

   // check if device is TC3 or TC3G
   if ((in_stream = fopen ("/proc/device-tree/deviceID", "r")) == NULL)
   {
      printf ("Can't open the deviceID file.\n");
      return 1;
   }
   // read file
   (void)fread(acn_deviceID, sizeof(acn_deviceID), 1, in_stream);
   // close file
   fclose(in_stream);

   if (strcmp(acn_deviceID, "TC3G") == 0)
   {
      // TC3G detected
      (void)sprintf(macn_motion_sensor_x, "%s", TC3G_MOTION_SENSOR_X);
      (void)sprintf(macn_motion_sensor_y, "%s", TC3G_MOTION_SENSOR_Y);
      (void)sprintf(macn_motion_sensor_z, "%s", TC3G_MOTION_SENSOR_Z);
      mu8_TC3G = 1;
   }
   else
   {
      // TC3 detected
      (void)sprintf(macn_motion_sensor_x, "%s", TC3_MOTION_SENSOR_X);
      (void)sprintf(macn_motion_sensor_y, "%s", TC3_MOTION_SENSOR_Y);
      (void)sprintf(macn_motion_sensor_z, "%s", TC3_MOTION_SENSOR_Z);
   }

   u32_Timer1 = mu32_sys_get_time_ms ();
   while (1)
   {
      if ((u32_Timer1 + 1000) < mu32_sys_get_time_ms())
      {
         // clear screen
         printf ("\033[2J");
         // read the actual x,y,z position
         mv_read (acn_Read[0], acn_Read[1], acn_Read[2]);
         // reload timer;
         u32_Timer1 = mu32_sys_get_time_ms ();

         // print menu
         if (mu8_TC3G == 1)
         {
            printf ("\nMotion Sensor Test Application TC3G\n");
         }
         else
         {
            printf ("\nMotion Sensor Test Application TC3\n");
         }
         printf (".---------------------------------.\n");
         printf ("|              Menu               |\n");
         printf ("'---------------------------------'\n");
         printf ("\t(0) Exit\n\n\n");
         // convert array of charn to sint16
         for (u8_counter1 = 0; u8_counter1 < 3; u8_counter1 ++)
         {
            as16_Read[u8_counter1] = atoi (acn_Read[u8_counter1]);
         }
         printf ("X:%i\tY:%i\tZ:%i\n", as16_Read[0], as16_Read[1], as16_Read[2]);
         mv_draw (&as16_Read[0], &as16_Read[1], &as16_Read[2]);
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


//-----------------------------------------------------------------------------
/*!
   \brief mv_draw (const sint16 * const ops16_X, const sint16 * const ops16_Y,
                   const sint16 * const ops16_Z)

   Only for fun

   \param[out] ops16_X reference to the read X value
   \param[out] ops16_Y reference to the read Y value
   \param[out] ops16_Z reference to the read Z value

   \created       11.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   11.03.2010
          STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mv_draw (const sint16 * const ops16_X, const sint16 * const ops16_Y,
                     const sint16 * const ops16_Z)
{
   // ---------------------------------
   // in the TC3G was x and y switched
   // ---------------------------------

   printf ("\n\n");

   // in case of TC3G, use other limits
   if (mu8_TC3G == 1)
   {
      if (((*ops16_Y <= -500)                      ) &&
          ((*ops16_Z <= 500) && (*ops16_Z >= -500)))
      {
         printf("   -y                ,-------, \n");
         printf("    |  , -x         /        /! \n");
         printf("    |.'            /        / ! \n");
         printf("    +--- z        /        /  ! \n");
         printf("                 /        /   ! \n");
         printf("                ,-------,'    ! \n");
         printf("                !       !     ! \n");
         printf("                !   T   !     ! \n");
         printf("                !   C   !     ! \n");
         printf("                !   3   !     ! \n");
         printf("                !   G   !     ! \n");
         printf("                !       !   P !------ \n");
         printf("                !       !  O E!     /! \n");
         printf("                !       ! T D !    / ! \n");
         printf("                !       !  I /    /  ! \n");
         printf("               /!       ! S /    /   ! \n");
         printf("              / !       !  /    /   / \n");
         printf("             /  !       ! /    /   / \n");
         printf("            /   '-------''    /   / \n");
         printf("           /                 /   / \n");
         printf("          !------------------!  / \n");
         printf("          !                  ! / \n");
         printf("          !                  !/ \n");
         printf("          !------------------! \n");
      }
      else if (((*ops16_Y > -500) && (*ops16_Y < 500)) &&
               ((*ops16_Z >  500)                   ))
      {
         printf("         z                 _____ \n");
         printf("   -x ,  |                !\\    \\ \n");
         printf("       '.|                ! \\    \\ \n");
         printf("   -y ---+                !  \\    \\ \n");
         printf("                          !   \\    \\ \n");
         printf("                          !    \\    \\ \n");
         printf("                          !     \\    \\ \n");
         printf("                          !      \\    \\ \n");
         printf("        ____________________      \\    \\ \n");
         printf("       !\\                   \\      \\ ___\\ \n");
         printf("       ! \\       TOP         \\      !   ! \n");
         printf("       !  \\       SIDE        \\     !   ! \n");
         printf("       !    ____________________    !   ! \n");
         printf("       !   !                    !   !   ! \n");
         printf("       !   !                    !   !   ! \n");
         printf("       \\   !     TC3G           !   !   ! \n");
         printf("        \\  !                    !   !   ! \n");
         printf("         \\ !                    !   !   ! \n");
         printf("          \\!____________________!   !   ! \n");
         printf("                             \\      !   ! \n");
         printf("                              \\     !   ! \n");
         printf("                               \\    !   ! \n");
         printf("                                \\   !   ! \n");
         printf("                                 \\  !   ! \n");
         printf("                                  \\ !   ! \n");
         printf("                                   \\!___! \n");
      }
      else if (((*ops16_Y > -500) && (*ops16_Y < 500)) &&
               ((*ops16_Z < -500)                   ))
      {
         printf("   -z            ------ \n");
         printf("    |  , -x     /     /! \n");
         printf("    |.'        /     / ! \n");
         printf("    +--- -y   /     /  ! \n");
         printf("             /     /   ___________________ \n");
         printf("            /     /  /                   /! \n");
         printf("           /     /  /      BOTTOM       / ! \n");
         printf("          ------/  /      SIDE         /  ! \n");
         printf("          !    !  /___________________/   ! \n");
         printf("          !    ! !                    !   ! \n");
         printf("          !    ! !                    !   ! \n");
         printf("          !    ! !     TC3G           !   / \n");
         printf("          !    ! !                    !  / \n");
         printf("          !    ! !                    ! / \n");
         printf("          !    ! !____________________!/ \n");
         printf("          !    !      / \n");
         printf("          !    !     / \n");
         printf("          !    !    / \n");
         printf("          !    !   / \n");
         printf("          !    !  / \n");
         printf("          !    ! / \n");
         printf("          ------/ \n");
      }
      else
      {
         printf ("Not supported\n");
      }
   }
   else
   {     //TC3
      if (((*ops16_X <= -30)                     ) &&
          ((*ops16_Z <= 30) && (*ops16_Z >= -30)))
      {
         printf("   -x                ,-------, \n");
         printf("    |  , y          /        /! \n");
         printf("    |.'            /        / ! \n");
         printf("    +--- z        /        /  ! \n");
         printf("                 /        /   ! \n");
         printf("                ,-------,'    ! \n");
         printf("                !       !     ! \n");
         printf("                !   T   !     ! \n");
         printf("                !   C   !     ! \n");
         printf("                !   3   !     ! \n");
         printf("                !       !     ! \n");
         printf("                !       !   P !------ \n");
         printf("                !       !  O E!     /! \n");
         printf("                !       ! T D !    / ! \n");
         printf("                !       !  I /    /  ! \n");
         printf("               /!       ! S /    /   ! \n");
         printf("              / !       !  /    /   / \n");
         printf("             /  !       ! /    /   / \n");
         printf("            /   '-------''    /   / \n");
         printf("           /                 /   / \n");
         printf("          !------------------!  / \n");
         printf("          !                  ! / \n");
         printf("          !                  !/ \n");
         printf("          !------------------! \n");
      }
      else if (((*ops16_X > -30) && (*ops16_X < 30)) &&
               ((*ops16_Z > 30)                   ))
      {
         printf("         z                 _____ \n");
         printf("    y ,  |                !\\    \\ \n");
         printf("       '.|                ! \\    \\ \n");
         printf("   -x ---+                !  \\    \\ \n");
         printf("                          !   \\    \\ \n");
         printf("                          !    \\    \\ \n");
         printf("                          !     \\    \\ \n");
         printf("                          !      \\    \\ \n");
         printf("        ____________________      \\    \\ \n");
         printf("       !\\                   \\      \\ ___\\ \n");
         printf("       ! \\       TOP         \\      !   ! \n");
         printf("       !  \\       SIDE        \\     !   ! \n");
         printf("       !    ____________________    !   ! \n");
         printf("       !   !                    !   !   ! \n");
         printf("       !   !                    !   !   ! \n");
         printf("       \\   !     TC3            !   !   ! \n");
         printf("        \\  !                    !   !   ! \n");
         printf("         \\ !                    !   !   ! \n");
         printf("          \\!____________________!   !   ! \n");
         printf("                             \\      !   ! \n");
         printf("                              \\     !   ! \n");
         printf("                               \\    !   ! \n");
         printf("                                \\   !   ! \n");
         printf("                                 \\  !   ! \n");
         printf("                                  \\ !   ! \n");
         printf("                                   \\!___! \n");
      }


      else if (((*ops16_X > -30) && (*ops16_X < 30)) &&
               ((*ops16_Z < -30)                  ))
      {
         printf("   -z            ------ \n");
         printf("    |  , y      /     /! \n");
         printf("    |.'        /     / ! \n");
         printf("    +--- -x   /     /  ! \n");
         printf("             /     /   ___________________ \n");
         printf("            /     /  /                   /! \n");
         printf("           /     /  /      BOTTOM       / ! \n");
         printf("          ------/  /      SIDE         /  ! \n");
         printf("          !    !  /___________________/   ! \n");
         printf("          !    ! !                    !   ! \n");
         printf("          !    ! !                    !   ! \n");
         printf("          !    ! !     TC3            !   / \n");
         printf("          !    ! !                    !  / \n");
         printf("          !    ! !                    ! / \n");
         printf("          !    ! !____________________!/ \n");
         printf("          !    !      / \n");
         printf("          !    !     / \n");
         printf("          !    !    / \n");
         printf("          !    !   / \n");
         printf("          !    !  / \n");
         printf("          !    ! / \n");
         printf("          ------/ \n");
      }
      else
      {
         printf ("Not supported\n");
      }
   }
}
