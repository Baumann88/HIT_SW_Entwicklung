//-----------------------------------------------------------------------------
/*!
   \internal
   \file          can.c
   \brief         TC3 training

   \implementation
   copyright   STW (c) 1999-2011
   license     use only under terms of contract / confidential

   created     21.02.12 Florian Belser
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author            Description
   21.02.12          Florian Belser    file created
   \endhistory
*/
//-----------------------------------------------------------------------------/*

/* -- Includes ------------------------------------------------------------ */
#include "can.h"

/* -- Defines ------------------------------------------------------------- */
#define MAX_WAIT_TIME 1 // max socket read wait time in milliseconds
/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Module Global Variables --------------------------------------------- */
static struct timeval mt_TimeSinceInit;
/* -- Module Global Function Prototypes ----------------------------------- */


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
sint32 gs32_CAN_RecvMsg(const sint16 * const ops16_Socket, T_can_msg * const opt_Message)
{
   sint32 s32_retval                     = C_NO_ERR;
   uint64 u64_TimeMsInit                 = 0;
   uint64 u64_TimeMsCanTimeStamp         = 0;
   fd_set t_readfds;
   struct timeval t_Timeout;
   struct timeval t_CanMsgTimeStamp;
   static struct can_frame ht_frame;
   // Set timeout to seconds
   t_Timeout.tv_sec  = 0;
   t_Timeout.tv_usec = MAX_WAIT_TIME * 1000;

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
               opt_Message->t_Id.u8_Xtd = (0x01 & (ht_frame.can_id >> 31));  // get extended flag
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
                  s32_retval = C_NOACT;
               }
            }
            else
            {
               // no new message
               s32_retval = C_NOACT;
            }
         }
         else
         {
            // no new message
            s32_retval = C_NOACT;
         }
      }
      else
      {
          // no new message
          s32_retval = C_NOACT;
      }
   }
   else
   {
      s32_retval = C_CONFIG;
   }
   return (s32_retval);
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
sint32 gs32_CAN_SendMsg(const sint16 * const ops16_Socket, const T_can_msg * const opt_Message)
{
   sint32 s32_retval     = C_NO_ERR;
   sint16 s16_NumOfBytes = 0;
   static struct can_frame ht_frame;
   uint8 u8_retries = 0;
   uint8 u8_retry = 0;
   // check if the socket is correct bind
   if (*ops16_Socket >= 0)
   {
      ht_frame.can_id =  (0x1FFFFFFFu & opt_Message->t_Id.u32_Id);  // set id
      ht_frame.can_id |= (0x80000000u & (opt_Message->t_Id.u8_Xtd << 31));   // set extended flag
      ht_frame.can_dlc = opt_Message->u8_Dlc;                       // set data length code
      (void) memcpy (ht_frame.data, opt_Message->au8_Data,
                     sizeof (ht_frame.data));                              // copy data

      s32_retval = C_OVERFLOW;
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
               s32_retval = C_NO_ERR;
            }
         }
      } while ((u8_retry == 1) && (u8_retries < 5u));
   }
   else
   {
      // socket error
      s32_retval = C_CONFIG;
   }
   return (s32_retval);
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
//-----------------------------------------------------------------------------
sint32 gs32_CAN_InitBus (sint16 * const ops16_Socket, const uint8 ou8_Bus)
{
   sint32 s32_retval              = C_NO_ERR;
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
      s32_retval = C_CONFIG;
   }
   // If no error occured, go on
   if (s32_retval == C_NO_ERR)
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
                  (void) gs32_CAN_CloseBus(ops16_Socket);
                  // set return value
                  s32_retval = C_CONFIG;
               }
            }
            else
            {
               // close socket
               (void) gs32_CAN_CloseBus(ops16_Socket);
               // set return value
               s32_retval = C_CONFIG;
            }
         }
         else
         {
            // close socket
            (void) gs32_CAN_CloseBus(ops16_Socket);
            // set return value
            s32_retval = C_CONFIG;
         }
      }
      else
      {
         // error occured while creating new Socket
         s32_retval = C_CONFIG;
      }
   }
   return (s32_retval);
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
sint32 gs32_CAN_CloseBus(sint16 * const ops16_Socket)
{
   // check if the socket is correct bind
   if (*ops16_Socket >= 0)
   {
      // close previously initialized socket
      (void) close(*ops16_Socket);
   }
   return (C_NO_ERR);
}
