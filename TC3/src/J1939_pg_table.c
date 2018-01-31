//-----------------------------------------------------------------------------
/*!
   \internal
   \file
   \brief       main module example "parameter group configuration table"

   Example application main module.
   The application is controlled by the TC3 IO interface.
   The J1939 network is created between 1st and 2nd CAN of the TC3.

   \implementation
   project     J1939 library
   copyright   STW (c) 2011
   license     use only under terms of contract / confidential

   created     11.01.2011   STW/M.Greiner
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)    Author               Description
   11.01.2011          STW/M.Greiner        file created
   \endhistory
*/
//-----------------------------------------------------------------------------


/* -- Includes ------------------------------------------------------------ */
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "j1939.h" // include j1939 library header


/* -- Defines ------------------------------------------------------------- */
#define TRUE  1
#define FALSE 0


/* -- Types --------------------------------------------------------------- */


/* -- Global Variables ---------------------------------------------------- */


/* -- Module Global Variables --------------------------------------------- */
// PG data pool
static T_J1939_PGN_XBR  mt_XBR_Tx_0_12;  // PG on bus 0
static T_J1939_PGN_TSC1 mt_TSC1_Rx_0_13; // PG on bus 0
static T_J1939_PGN_XBR  mt_XBR_Rx_1_32;  // PG on bus 1
static T_J1939_PGN_TSC1 mt_TSC1_Tx_1_33; // PG on bus 1

// Misra deviation as offsetof macro defined by system header
// PRQA S 0306 ++
// Misra deviation as J1939_SELECT_SPN_END macro defined by j1939 library
// PRQA S 0686 ++
static const T_J1939_PG_declaration mat_PGs[] =
{
   J1939_BUS(J1939_CAN_CH_0)
      J1939_NODE(0x12)
         J1939_TX_PG_ALL_SPN(0x32, J1939_DEFAULT_TIME, mt_XBR_Tx_0_12, gt_J1939_PGN_CFG_XBR)
      J1939_NODE(0x13)
         J1939_RX_PG_SELECTED_SPN(0x33, J1939_DEFAULT_TIME, mt_TSC1_Rx_0_13, gt_J1939_PGN_CFG_TSC1)
            J1939_SELECT_SPN(T_J1939_PGN_TSC1, u16_RequestedSpeedLimit)
            J1939_SELECT_SPN(T_J1939_PGN_TSC1, u8_RequestedTorqueLimit)
            J1939_SELECT_SPN(T_J1939_PGN_TSC1, u16_RequestedSpeedLimit_rpm)
            J1939_SELECT_SPN(T_J1939_PGN_TSC1, s8_RequestedTorqueLimit_perc)
            J1939_SELECT_SPN_END
   J1939_BUS(J1939_CAN_CH_1)
      J1939_NODE(0x32)
         J1939_RX_PG_ALL_SPN(0x12, J1939_DEFAULT_TIME, mt_XBR_Rx_1_32, gt_J1939_PGN_CFG_XBR)
      J1939_NODE(0x33)
         J1939_TX_PG_SELECTED_SPN(0x13, J1939_DEFAULT_TIME, mt_TSC1_Tx_1_33, gt_J1939_PGN_CFG_TSC1)
            J1939_SELECT_SPN(T_J1939_PGN_TSC1, u16_RequestedSpeedLimit_rpm)
            J1939_SELECT_SPN(T_J1939_PGN_TSC1, s8_RequestedTorqueLimit_perc)
            J1939_SELECT_SPN_END
   J1939_CFG_TABLE_END
};
// PRQA S 0686 --
// PRQA S 0306 --


/* -- Module Global Function Prototypes ----------------------------------- */
static void* mpv_Thread(void *opv_Ptr);
static void  mv_DataShowTask(void);
static void  mv_CmdServerTask(void);
static void  mv_CmdExecute(const charn * const opcn_Command);
static void  mv_StdoutWriteString(const charn* opcn_String);
static void  mv_PrintHelp(void);


/* -- Implementation ------------------------------------------------------ */

//-----------------------------------------------------------------------------
/*!
   \brief   Application main function

   Init system and all modules. Call modules tasks.

   \return
   -

   \created     11.01.2011   STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)    Author               Description
   11.01.2010          STW/M.Greiner        function created
   \endhistory
*/
//-----------------------------------------------------------------------------
int main(void)
{
   T_J1939_bus_parameters t_J1939BusParameters = {0};
   pthread_t              t_J1939LibThread;
   charn                  acn_String[50];
   sint16                 s16_Return;

   // print supported commands
   mv_StdoutWriteString("\n Start J1939 demo application!\n");
   mv_StdoutWriteString("\n Please connect ESX CAN Bus 0 to Bus 1!\n");
   mv_PrintHelp();

   // config CAN0 and CAN1
   system("ifconfig can0 down");
   system("echo 250000 > /sys/class/net/can0/can_bitrate");
   system("ifconfig can0 up");
   system("ifconfig can1 down");
   system("echo 250000 > /sys/class/net/can1/can_bitrate");
   system("ifconfig can1 up");

   // init CAN on J1939 Stack
   t_J1939BusParameters.u16_Channel = J1939_CAN_CH_0;
   (void)J1939_init(&t_J1939BusParameters);
   t_J1939BusParameters.u16_Channel = J1939_CAN_CH_1;
   (void)J1939_init(&t_J1939BusParameters);

   // set PG configuration
   s16_Return = J1939_set_pgs_configuration(mat_PGs);
   if (s16_Return != C_NO_ERR)
   {
      (void)sprintf(acn_String, "\n Error while setting PG configuration: %d\n", s16_Return);
      mv_StdoutWriteString(acn_String);
   }

   // J1939 request on both CAN busses (only for testing CAN bus wiring and configuration)
   J1939_send_request(J1939_CAN_CH_0, 0x1234, 0x23, 0x34);
   J1939_send_request(J1939_CAN_CH_1, 0x1234, 0x23, 0x35);

   // create thread which call the J1939 library task function
   if (pthread_create(&t_J1939LibThread, NULL,  mpv_Thread, NULL) != C_NO_ERR)
   {
      mv_StdoutWriteString("Error: thread not created\n");
      exit(-1);
   }

   // Misra deviations for main loop
   // PRQA S 3323 1
   while (TRUE)
   {
      mv_CmdServerTask();
      usleep(10*1000); //10ms cycle time
   }
}


//-----------------------------------------------------------------------------
/*!
   \brief    Thread function

   The thread cyclicaly call the J1939 library task and the data show
   task functions.

   \param[in]          opv_Ptr      not used

   \return
    void*              not used

   \created            11.01.2011   STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)    Author                Description
   11.01.2011          STW/M.Greiner         function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void* mpv_Thread(void *opv_Ptr)
{
   if (opv_Ptr != NULL)
   {
      // should not entry here (needed to eliminate compiler warning "unused variable opv_Ptr")
      exit(-1);
   }

   while (TRUE)
   {
      mv_DataShowTask(); // call the data show task function
      J1939_task();      // call the J1939 library task
      usleep(1*1000);    // call tasks each 1ms
   }
}


//-----------------------------------------------------------------------------
/*!
   \brief    Print array of char

   Write array of char to stdoout interface.

   \param[in]          opcn_String    pointer to array of char

   \return
    -

   \created            11.01.2011   STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)    Author                Description
   11.01.2011          STW/M.Greiner         function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mv_StdoutWriteString(const charn* opcn_String)
{
   (void)printf("%s", opcn_String);
}


//-----------------------------------------------------------------------------
/*!
   \brief    Print help text

   Show all supported commands

   \return
    -

   \created            11.01.2011   STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)    Author                Description
   11.01.2011          STW/M.Greiner         function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mv_PrintHelp(void)
{
   mv_StdoutWriteString("\n");
   mv_StdoutWriteString(" Supported commands:\n");
   mv_StdoutWriteString("  h <RETURN>                - print supported commands\n");
   mv_StdoutWriteString("  0 <RETURN>                - disable Tx PG on Bus 0\n");
   mv_StdoutWriteString("  1 <RETURN>                - enable  Tx PG on Bus 0\n");
   mv_StdoutWriteString("  2 [0..6] Integer <RETURN> - set integer to [0..6] SPN of Tx PG\n");
   mv_StdoutWriteString("  5 <RETURN>                - disable Tx PG on Bus 1\n");
   mv_StdoutWriteString("  6 <RETURN>                - enable  Tx PG on Bus 1\n");
   mv_StdoutWriteString("  7 [0..1] Integer <RETURN> - set integer to [0..1] SPN of Tx PG\n");
   mv_StdoutWriteString("  q <RETURN>                - exit from demo application\n");
}


//-----------------------------------------------------------------------------
/*!
   \brief    Print data to STDIO interface

   Task for data printing

   \return
    -

   \created            11.01.2011   STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)    Author                Description
   11.01.2011          STW/M.Greiner         function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mv_DataShowTask(void)
{
   static T_J1939_PGN_XBR  ht_OldState1; // need for detecting changes
   static T_J1939_PGN_TSC1 ht_OldState2; // need for detecting changes
   charn acn_String[150];

   // first Rx PG
   if (memcmp(&ht_OldState1, &mt_XBR_Rx_1_32, sizeof(ht_OldState1)) != 0)
   {
      // any data in structure changed
      ht_OldState1 = mt_XBR_Rx_1_32;
      // print structure to STDOUT
      mv_StdoutWriteString("\n");
      mv_StdoutWriteString("Data pool: mt_XBR_Rx_1_32\n");
      (void)sprintf(acn_String, "t_Ctrl.q_ValidDataFlag = %d\n", mt_XBR_Rx_1_32.t_Ctrl.u8_ValidDataFlag);
      mv_StdoutWriteString(acn_String);
      (void)sprintf(acn_String, "t_Ctrl.q_NewDataFlag   = %d\n", mt_XBR_Rx_1_32.t_Ctrl.u8_NewDataFlag);
      mv_StdoutWriteString(acn_String);
      (void)sprintf(acn_String, "u16_ExternalAccelerationDemand       = %d\n", mt_XBR_Rx_1_32.u16_ExternalAccelerationDemand);
      mv_StdoutWriteString(acn_String);
      (void)sprintf(acn_String, "u8_XBREBIMode                        = %d\n", mt_XBR_Rx_1_32.u8_XBREBIMode);
      mv_StdoutWriteString(acn_String);
      (void)sprintf(acn_String, "u8_XBRPriority                       = %d\n", mt_XBR_Rx_1_32.u8_XBRPriority);
      mv_StdoutWriteString(acn_String);
      (void)sprintf(acn_String, "u8_u8_XBRControlMode                 = %d\n", mt_XBR_Rx_1_32.u8_XBRControlMode);
      mv_StdoutWriteString(acn_String);
      (void)sprintf(acn_String, "u8_XBRMessageCounter                 = %d\n", mt_XBR_Rx_1_32.u8_XBRMessageCounter);
      mv_StdoutWriteString(acn_String);
      (void)sprintf(acn_String, "u8_XBRMessageChecksum                = %d\n", mt_XBR_Rx_1_32.u8_XBRMessageChecksum);
      mv_StdoutWriteString(acn_String);
      (void)sprintf(acn_String, "s16_ExternalAccelerationDemand_mm_s2 = %d\n", mt_XBR_Rx_1_32.s16_ExternalAccelerationDemand_mm_s2);
      mv_StdoutWriteString(acn_String);
   }

   // second Rx PG
   if (memcmp(&ht_OldState2, &mt_TSC1_Rx_0_13, sizeof(ht_OldState2)) != 0)
   {
      // any data in structure changed
      ht_OldState2 = mt_TSC1_Rx_0_13;
      // print structure to STDOUT
      mv_StdoutWriteString("\n");
      mv_StdoutWriteString("Data pool: mt_TSC1_Rx_0_13\n");
      (void)sprintf(acn_String, "t_Ctrl.q_ValidDataFlag = %d\n", mt_TSC1_Rx_0_13.t_Ctrl.u8_ValidDataFlag);
      mv_StdoutWriteString(acn_String);
      (void)sprintf(acn_String, "t_Ctrl.q_NewDataFlag   = %d\n", mt_TSC1_Rx_0_13.t_Ctrl.u8_NewDataFlag);
      mv_StdoutWriteString(acn_String);
      (void)sprintf(acn_String, "u16_RequestedSpeedLimit     = %d\n", mt_TSC1_Rx_0_13.u16_RequestedSpeedLimit);
      mv_StdoutWriteString(acn_String);
      (void)sprintf(acn_String, "u8_RequestedTorqueLimit     = %d\n", mt_TSC1_Rx_0_13.u8_RequestedTorqueLimit);
      mv_StdoutWriteString(acn_String);
      (void)sprintf(acn_String, "u16_RequestedSpeedLimit_rpm = %d\n", mt_TSC1_Rx_0_13.u16_RequestedSpeedLimit_rpm);
      mv_StdoutWriteString(acn_String);
      (void)sprintf(acn_String, "s8_RequestedTorqueLimit_prc = %d\n", mt_TSC1_Rx_0_13.s8_RequestedTorqueLimit_perc);
      mv_StdoutWriteString(acn_String);
   }
}


//-----------------------------------------------------------------------------
/*!
   \brief    Read user commands from STDIN interface

   Read commands from STDIN interface and call the command function.

   \return
    -

   \created            11.01.2011   STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)    Author                Description
   11.01.2011          STW/M.Greiner         function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mv_CmdServerTask(void)
{
   static charn hacn_CmdBuffer[350] = {0};   // command buffer

   // read line from STDIN (blocking operation)
   if (fgets(hacn_CmdBuffer, sizeof(hacn_CmdBuffer), stdin) != NULL)
   {
       // line readed, decode and execute command
       mv_CmdExecute(hacn_CmdBuffer);
   }
}


//-----------------------------------------------------------------------------
/*!
   \brief    Execute commands

   Execute the command from string.

   \param[in]          opcn_Command    pointer to array with command string

   \return
    -

   \created            11.01.2011   STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)    Author                Description
   11.01.2011          STW/M.Greiner         function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mv_CmdExecute(const charn * const opcn_Command)
{
   sint32 s32_Data;

   switch (opcn_Command[0])
   {
   case 'h':
      mv_PrintHelp();
      break;
   case 'q':
      exit(0);
      break;

   // send on BUS 0
   case '0':
      mt_XBR_Tx_0_12.t_Ctrl.u8_ValidDataFlag = FALSE;
      break;
   case '1':
      mt_XBR_Tx_0_12.t_Ctrl.u8_ValidDataFlag = TRUE;
      break;
   case '2':
      // Misra deviation as only used for terminal interface
      // PRQA S 5125 1
      s32_Data = atoi(&opcn_Command[4]);
      switch (opcn_Command[2])
      {
      case '0':
         mt_XBR_Tx_0_12.u16_ExternalAccelerationDemand = (uint16)s32_Data;
         break;
      case '1':
         mt_XBR_Tx_0_12.u8_XBREBIMode = (uint8)s32_Data;
         break;
      case '2':
         mt_XBR_Tx_0_12.u8_XBRPriority = (uint8)s32_Data;
         break;
      case '3':
         mt_XBR_Tx_0_12.u8_XBRControlMode = (uint8)s32_Data;
         break;
      case '4':
         mt_XBR_Tx_0_12.u8_XBRMessageCounter = (uint8)s32_Data;
         break;
      case '5':
         mt_XBR_Tx_0_12.u8_XBRMessageChecksum = (uint8)s32_Data;
         break;
      case '6':
         mt_XBR_Tx_0_12.s16_ExternalAccelerationDemand_mm_s2 = (sint16)s32_Data;
         break;
      default:
         //unknown command
         break;
      }
      break;

   // send on BUS 1
   case '5':
      mt_TSC1_Tx_1_33.t_Ctrl.u8_ValidDataFlag = FALSE;
      break;
   case '6':
      mt_TSC1_Tx_1_33.t_Ctrl.u8_ValidDataFlag = TRUE;
      break;
   case '7':
      // Misra deviation as only used for terminal interface
      // PRQA S 5125 1
      s32_Data = atoi(&opcn_Command[4]);
      switch (opcn_Command[2])
      {
      case '0':
         mt_TSC1_Tx_1_33.u16_RequestedSpeedLimit_rpm = (uint16)s32_Data;
         break;
      case '1':
         mt_TSC1_Tx_1_33.s8_RequestedTorqueLimit_perc = (sint8)s32_Data;
         break;
      default:
         //unknown command
         break;
      }
      break;

   default:
      //unknown command
      mv_StdoutWriteString("Unknown command: ");
      mv_StdoutWriteString(opcn_Command);
      mv_StdoutWriteString("\n");
      break;
   }
}
