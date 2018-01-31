//-----------------------------------------------------------------------------
/*!
   \internal
   \file        CAN.c
   \brief       main module of rtc example application for TC3

   This example shows you how to open a can socket connection, how to receive and
   send messages

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
#include <stdint.h>
#include "stwtypes.h"
#include "stwerror.h"   //STW errors
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <unistd.h>
#include <sys/uio.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <errno.h>
#include <pthread.h>


/* -- Defines ------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------- */

// With this structs the behaviour of the CAN sockets is more STW conform

typedef struct
{
   uint32 u32_Id; // CAN identifier 11/29bit
   uint8  u8_Xtd; // u8_XTD == TRUE: 29bit ID, u8_XTD == FALSE: 11bit ID
} T_can_id;

typedef struct
{
   T_can_id t_Id;   // CAN message ID
   uint8 u8_Dlc;      // Data Length Code (0..8)
   uint8 au8_Data[8]; // message data bytes
   uint32 u32_time;   // timestamp of reception in milliseconds (system time), not used for TX messages
} T_can_msg;

/* -- Global Variables ---------------------------------------------------- */

/* -- Module Global Variables --------------------------------------------- */
static struct timeval mt_TimeSinceInit;
static sint16 ms16_CAN1;
static sint16 ms16_CAN2;

static uint8 mu8_connect;


/* -- Module Global Function Prototypes ----------------------------------- */
static uint32 mu32_sys_get_time_ms (void);
static sint16 ms16_CAN_InitBus (sint16 * const ops16_Socket, const uint8 ou8_Bus);
static sint16 ms16_CAN_CloseBus(sint16 * const ops16_Socket);
static sint16 ms16_CAN_SendMsg(const sint16 * const ops16_Socket, const T_can_msg * const opt_Message);
static sint16 ms16_CAN_RecvMsg(const sint16 * const ops16_Socket, T_can_msg * const opt_Message);

static sint16 ms16_CheckConnection (void);
static sint16 ms16_Init (void);

/* -- Implementation ------------------------------------------------------ */

//-----------------------------------------------------------------------------
/*!
   \brief   Receive new CAN message if available

   \param[in]     ops16_Socket         reference to socket
   \param[out]    opt_Config           reference to result

   \return
   C_NO_ERR       terminated with no error \n
   else           error

   \created       11.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   15.04.2010        STW/F.Belser   created
   \endhistory
*/
//-----------------------------------------------------------------------------
static sint16 ms16_CAN_RecvMsg(const sint16 * const ops16_Socket, T_can_msg * const opt_Message)
{
   sint16 s16_retval                     = C_NO_ERR;
   uint64 u64_TimeMsInit                 = 0;
   uint64 u64_TimeMsCanTimeStamp         = 0;
   fd_set t_readfds;
   struct timeval t_Timeout;
   struct timeval t_CanMsgTimeStamp;
   static struct can_frame ht_frame;

   // Set timeout to zero --> no timeout
   t_Timeout.tv_sec  = 0;
   t_Timeout.tv_usec = 0;

   // check if he have a filedescriptor
   if (*ops16_Socket >= 0)
   {
      // clear fds
      FD_ZERO (&t_readfds);
      // set read fds
      FD_SET (*ops16_Socket, &t_readfds);
      // check if we are ready to read
      if (select ((*ops16_Socket) + 1, &t_readfds, NULL, NULL, &t_Timeout) > 0)
      {
         // check if corresponding bit is set in the fds
         if (FD_ISSET (*ops16_Socket, &t_readfds))
         {
            if (read (*ops16_Socket, &ht_frame, sizeof (ht_frame)) >= 0)
            {
               // new message received
               opt_Message->t_Id.u32_Id = (ht_frame.can_id & 0x1FFFFFFFu); // get received ID
               opt_Message->t_Id.u8_Xtd = (0x01 & (ht_frame.can_id >> 31)); ; // get extended flag
               opt_Message->u8_Dlc = ht_frame.can_dlc;                     // get data length code
               (void) memcpy (opt_Message->au8_Data, ht_frame.data,
                              sizeof(opt_Message->au8_Data));                     // copy received data
               // get timestamp
               if (ioctl (*ops16_Socket, SIOCGSTAMP, &t_CanMsgTimeStamp) >= 0 )
               {
                  // complete time in ms of the last read CAN timestamp
                  u64_TimeMsCanTimeStamp = (((uint64)t_CanMsgTimeStamp.tv_sec * 1000) + ((uint64)t_CanMsgTimeStamp.tv_usec / 1000));
                  // complete time in ms of the call Init time
                  u64_TimeMsInit         = (((uint64)mt_TimeSinceInit.tv_sec  * 1000) + ((uint64)mt_TimeSinceInit.tv_usec  / 1000));
                  // set timestamp
                  opt_Message->u32_time = (uint32)(u64_TimeMsCanTimeStamp - u64_TimeMsInit);
               }
               else
               {
                  // ioctl failed
                  s16_retval = C_NOACT;
               }
            }
            else
            {
               // no new message
               s16_retval = C_NOACT;
            }
         }
         else
         {
            // no new message
            s16_retval = C_NOACT;
         }
      }
      else
      {
          // no new message
          s16_retval = C_NOACT;
      }
   }
   else
   {
      s16_retval = C_CONFIG;
   }
   return (s16_retval);
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
   \brief   Send new CAN message

   \param[in]     ops16_Socket         reference to to socket
   \param[out]    opt_Message          reference to new Message

   \return
   C_NO_ERR       terminated with no error \n
   else           error

   \created       11.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   11.03.2010        STW/F.Belser   created
   \endhistory
*/
//-----------------------------------------------------------------------------
static sint16 ms16_CAN_SendMsg(const sint16 * const ops16_Socket, const T_can_msg * const opt_Message)
{
   sint16 s16_retval     = C_NO_ERR;
   sint16 s16_NumOfBytes = 0;
   static struct can_frame ht_frame;
   uint8 u8_retries = 0;
   uint8 u8_retry = 0;
   // check if the socket is correct bind
   if (*ops16_Socket >= 0)
   {
      ht_frame.can_id =  (0x1FFFFFFFu & opt_Message->t_Id.u32_Id);  // set id
      ht_frame.can_id |= (0x80000000u & (opt_Message->t_Id.u8_Xtd << 31)); ;  // set extended flag
      ht_frame.can_dlc = opt_Message->u8_Dlc;                       // set data length code
      (void) memcpy (ht_frame.data, opt_Message->au8_Data,
                     sizeof (ht_frame.data));                              // copy data

      s16_retval = C_OVERFLOW;
      do
      {
         u8_retries++;
         u8_retry = 0;
         s16_NumOfBytes = write (*ops16_Socket, &ht_frame, sizeof (ht_frame));
         if (s16_NumOfBytes < 0)
         {
            if (errno == ENOBUFS) // No buffer space available (txqueuelen of CAN netdevice is exhausted)
            {
               usleep (10000); //10ms, it is only an example value which have to be added for your needs
               u8_retry = 1;
            }
         }
         else
         {
            if (s16_NumOfBytes >= (sint16) sizeof (ht_frame))
            {
               s16_retval = C_NO_ERR;
            }
         }
      } while ((u8_retry == 1) && (u8_retries < 5u));
   }
   else
   {
      // socket error
      s16_retval = C_CONFIG;
   }
   return (s16_retval);
}
//-----------------------------------------------------------------------------
/*!
   \brief   Initialize the CAN interface to be used with TC3 test application

   \attention
   This function initialize the CAN Socket referenced by ops16_Socket
   for the chosen CAN referenced by ou8_Bus

   \param[in]     ms16_InitBus         reference to the socket
   \param[in]     ou8_Bus              CAN bus

   \return
   C_NO_ERR       terminated with no error \n
   else           error

   \created       15.04.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   15.04.2010        STW/F.Belser   created
   \endhistory
*/
static sint16 ms16_CAN_InitBus (sint16 * const ops16_Socket, const uint8 ou8_Bus)
{
   sint16 s16_retval              = C_NO_ERR;
   static uint8 hu8_FirstTimeFlag = 1;
   struct can_filter t_CanFilter;
   struct sockaddr_can t_addr;
   struct ifreq t_ifr;

   // store the actual time on init
   if (hu8_FirstTimeFlag == 1)
   {
      (void) gettimeofday (&mt_TimeSinceInit, NULL);
      hu8_FirstTimeFlag = 0;
   }
   // set the can filter to zero, so that we receive everything!
   // here it's possible to set the CAN filters
   t_CanFilter.can_id = CAN_EFF_MASK; // CAN ID which must match with incoming IDs after passing the mask
                                      // CAN_EFF_MASK = Bit mask for extended CAN IDs (0x1FFFFFFF)
   t_CanFilter.can_mask = 0; // Mask which is applied to incoming IDs
   // Check for CAN bus number correctnes
   // check CAN_BUS
   if (ou8_Bus == 0) // CAN0 selected
   {
      (void) memcpy (t_ifr.ifr_name, "can0\0", sizeof (t_ifr.ifr_name));
   }
   else if (ou8_Bus == 1) //CAN1 selected
   {
      (void) memcpy (t_ifr.ifr_name, "can1\0", sizeof (t_ifr.ifr_name));
   }
   else
   {
      // CAN Bus Number to high for TC3
      s16_retval = C_CONFIG;
   }
   // If no error occured, go on
   if (s16_retval == C_NO_ERR)
   {
      // ************************* RxTx Socket configuration*************************
      // open socket
      // function shall create an unbound socket in a communications domain, and return a file descriptor
      // CAN_RAW = Raw protocol of PF_CAN, applicable to socket type SOCK_RAW
      *ops16_Socket = socket (PF_CAN, SOCK_RAW, CAN_RAW);
      if (*ops16_Socket >= 0)
      {
         // SIOCGIFINDEX is an macro, which retrieve the interface index of the interface into t_ifr.ifr_index
         if (ioctl(*ops16_Socket, SIOCGIFINDEX, &t_ifr) >= 0)
         {
            // disable default receive filter on this raw socket
            // CAN filter definition
            // A CAN raw filter list with elements of struct can_filter can be installed with setsockopt. This
            // list is used upon reception of CAN frames to decide whether the bound socket will receive a
            // freame. An empty filter list can also be defined using optlen = 0, which is recommended for write-only
            // sockets. If the socket was already bound with BIND, the old filter list gets replaced with the new one.
            // Be aware that already received, but not read out CAN frames may stay in the socket buffer.
            if (setsockopt (*ops16_Socket, SOL_CAN_RAW, CAN_RAW_FILTER, &t_CanFilter, sizeof (t_CanFilter)) == 0)
            {
               t_addr.can_family = AF_CAN;
               // set the received index from the ioctl!!!
               t_addr.can_ifindex = t_ifr.ifr_ifindex;
               // bind socket
               // The function shall assign a local socket address address to a socket identified by descriptor socket
               if (bind(*ops16_Socket, (struct sockaddr *)&t_addr, sizeof(t_addr)) < 0)
               {
                  // close socket
                  (void) ms16_CAN_CloseBus(ops16_Socket);
                  // set return value
                  s16_retval = C_CONFIG;
               }
            }
            else
            {
               // close socket
               (void) ms16_CAN_CloseBus(ops16_Socket);
               // set return value
               s16_retval = C_CONFIG;
            }
         }
         else
         {
            // close socket
            (void) ms16_CAN_CloseBus(ops16_Socket);
            // set return value
            s16_retval = C_CONFIG;
         }
      }
      else
      {
         // error occured while creating new Socket
         s16_retval = C_CONFIG;
      }
   }
   return (s16_retval);
}


//-----------------------------------------------------------------------------
/*!
   \brief   Close previously allocated CAN ressources

   \param[in]     ops16_Socket         reference to socket

   \created       15.04.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   15.04.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static sint16 ms16_CAN_CloseBus(sint16 * const ops16_Socket)
{
   // check if the socket is correct bind
   if (*ops16_Socket >= 0)
   {
      // close previously initialized socket
      (void) close(*ops16_Socket);
   }
   return (C_NO_ERR);
}



//-----------------------------------------------------------------------------
/*!
   \brief   ms16_Init(void)

   \return
   C_NO_ERR       terminated with no error \n
   else           error

   \created       15.04.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   15.04.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static sint16 ms16_Init (void)
{
   sint16 s16_retval = C_NO_ERR;

   // try to get socket descriptor
   s16_retval = ms16_CAN_InitBus (&ms16_CAN1, 0);
   if (s16_retval == C_NO_ERR)
   {
      s16_retval = ms16_CAN_InitBus (&ms16_CAN2, 1);
   }
   else{
        printf("can bus inital fail!");
   }
   return (s16_retval);
}


//-----------------------------------------------------------------------------
/*!
   \brief   ms16_CheckConnection(void)

   \return
   C_NO_ERR       terminated with no error \n
   else           error

   \created       15.04.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   15.04.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static sint16 ms16_CheckConnection (void)
{
   sint16 s16_retval = C_NO_ERR;
   uint32 u32_time = 0;
   uint32 u32_time2 = 0;
   T_can_msg t_CanMsg;

   t_CanMsg.t_Id.u32_Id = 0x100;
   t_CanMsg.t_Id.u8_Xtd = 0;
   t_CanMsg.u8_Dlc = 4;
   t_CanMsg.au8_Data[0] = 0xDE;
   t_CanMsg.au8_Data[1] = 0xAD;
   t_CanMsg.au8_Data[2] = 0xBE;
   t_CanMsg.au8_Data[3] = 0xEF;
   // Send Message
   s16_retval = ms16_CAN_SendMsg(&ms16_CAN1, &t_CanMsg);
   if (s16_retval == C_NO_ERR)
   {
      printf ("Message send: \t\tID\tDB0\tDB1\tDB2\tDB3\tDLC\n");
      printf ("\t\t\t0x%lx\t0x%x\t0x%x\t0x%x\t0x%x\t%u\n\n", t_CanMsg.t_Id.u32_Id,
                                                         t_CanMsg.au8_Data[0],
                                                         t_CanMsg.au8_Data[1],
                                                         t_CanMsg.au8_Data[2],
                                                         t_CanMsg.au8_Data[3],
                                                         t_CanMsg.u8_Dlc);
      memset (&t_CanMsg, 0, sizeof (T_can_msg));
      u32_time = mu32_sys_get_time_ms ();
      u32_time2 = mu32_sys_get_time_ms ();
      while ((u32_time + 1000) > mu32_sys_get_time_ms ())
      {
         if ((u32_time2 + 50) <= mu32_sys_get_time_ms ())
         {
            (void) ms16_CAN_RecvMsg (&ms16_CAN2, &t_CanMsg);
            if ((t_CanMsg.t_Id.u32_Id == 0x100) &&
                (t_CanMsg.au8_Data[0] == 0xDE ) &&
                (t_CanMsg.au8_Data[1] == 0xAD ) &&
                (t_CanMsg.au8_Data[2] == 0xBE ) &&
                (t_CanMsg.au8_Data[3] == 0xEF ))
            {
               printf ("Message received: \tID\tDB0\tDB1\tDB2\tDB3\tDLC\n");
               printf ("\t\t\t0x%lx\t0x%x\t0x%x\t0x%x\t0x%x\t%u\n", t_CanMsg.t_Id.u32_Id,
                                                                  t_CanMsg.au8_Data[0],
                                                                  t_CanMsg.au8_Data[1],
                                                                  t_CanMsg.au8_Data[2],
                                                                  t_CanMsg.au8_Data[3],
                                                                  t_CanMsg.u8_Dlc);
               s16_retval = C_NO_ERR;
               break;
            }
            else
            {
               s16_retval = C_COM;
               u32_time2 = mu32_sys_get_time_ms ();
            }
         }
      }
   }
   return (s16_retval);
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

   // set mu8_connect to false
   mu8_connect = 0;
   // try to init interface
   if (ms16_Init () != C_NO_ERR)
   {
      // something goes wrong, better close everything
      (void) ms16_CAN_CloseBus (&ms16_CAN1);
      (void) ms16_CAN_CloseBus (&ms16_CAN2);
      printf ("Error occured while opening CAN \n");
   }
   else
   {
      while (1)
      {
         if (cn_Input != '\n')
         {
            printf ("\nCAN Test Application TC3\n");
            printf (".---------------------------------.\n");
            printf ("|              Menu               |\n");
            printf ("'---------------------------------'\n");
            printf ("\tPlease connect CAN1 with CAN2!\n\n");
            printf ("\t(0) Exit\n");
            printf ("\t(1) Check Connection\n");
            printf ("hahaha!");
         }
         cn_Input = getchar ();
         // switch between the different input values
         //------------------------------------------------------------------
         //
         //------------------------------------------------------------------
         if (cn_Input == '0')
         {
            // close everything
            (void) ms16_CAN_CloseBus (&ms16_CAN1);
            (void) ms16_CAN_CloseBus (&ms16_CAN2);
            break;
         }
         else if (cn_Input == '1')
         {
            // check connection
            if (ms16_CheckConnection () == C_NO_ERR)
            {
               printf ("\n--> Connection established\n");
            }
            else
            {
               printf ("Nothing received!!\n");
               printf ("\n--> Connection error\n");
            }
         }
      }
   }
   return (0);
}


