//-----------------------------------------------------------------------------
/*!
   \internal
   \file
   \brief       main module example "diagnose messages 1,2,3"

   Example application main module.
   The application is controlled by the TC3 IO interface.
   The J1939 network is created between 1st and 2nd CAN of the TC3.

   \implementation
   project     J1939 library
   copyright   STW (c) 2010
   license     use only under terms of contract / confidential

   created     12.01.2011   STW/M.Greiner
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)    Author                  Description
   12.01.2011          STW/M.Greiner           file created
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
#define MAX_NR_RX_DTC         20           // maximal number of received DTC
#define OFF                   0
#define FALSE                 0
#define TRUE                  1


/* -- Types --------------------------------------------------------------- */


/* -- Global Variables ---------------------------------------------------- */


/* -- Module Global Variables --------------------------------------------- */

// define TP connection needed for DM messages
// Misra deviations as mat_BdtTx is also defined module global
// PRQA S 3218 1
static T_J1939_TP_BDT_rx_def mat_BdtRx[] =
{
   J1939_SET_DM1_RX(0, 0x12)
   J1939_SET_DM2_RX(0, 0x12)
   J1939_TPBDT_RX_TABLE_END
};

static T_J1939_TP_BDT_tx_def mat_BdtTx[] =
{
   J1939_SET_DM1_TX(1, 0x12)
   J1939_SET_DM2_TX(1, 0x12)
   J1939_TPBDT_TX_TABLE_END
};

// define DM1 Tx DTC table
static T_J1939_DM_tx_dtc mat_J1939_Node12TxDtc[] =
{
   // State, PrevActive, Failing SPN,  FMI, SPN conv mode, Occurrence counter
   { OFF,    FALSE,      {898,         11,  0,            1}}, // Engine Requested Speed Limit
   { OFF,    FALSE,      {190,         12,  0,            1}}, // Engine Speed
   { OFF,    FALSE,      {110,         13,  0,            1}}, // Engine Coolant Temperature
   { OFF,    FALSE,      {175,         14,  0,            1}}, // Engine Oil Temperature 1
   { OFF,    FALSE,      { 98,         15,  0,            1}}, // Engine Oil Level
   { OFF,    FALSE,      {101,         16,  0,            1}}, // Engine Crankcase Pressure
   { OFF,    FALSE,      {183,         17,  0,            1}}, // Engine Fuel Rate
   { OFF,    FALSE,      {177,         18,  0,            1}}, // Transmission Oil Temperature
   { OFF,    FALSE,      { 96,         19,  0,            1}}, // Fuel Level
};
J1939_DM1_TX_TABLE(mat_J1939_Node12TxDtc, mat_BdtTx[0])


/* -- Module Global Function Prototypes ----------------------------------- */
static void* mpv_Thread(void *opv_Ptr);
static void mv_StdoutWriteString(const charn* opcn_String);
static void mv_PrintHelp(void);
static void mv_CmdServerTask(void);
static void mv_CmdExecute(const charn * const opcn_Command);
static void mpr_Dm1RxCallback(const uint16 ou16_Channel, const uint8 ou8_SrcAddress,
                              const T_J1939_DM_rx_dtc * const opt_Data);
static void mpr_Dm2RxCallback(const uint16 ou16_Channel, const uint8 ou8_SrcAddress,
                              const T_J1939_DM_rx_dtc * const opt_Data);


/* -- Implementation ------------------------------------------------------ */

//-----------------------------------------------------------------------------
/*!
   \brief   Application main function

   Init system and all modules. Call modules tasks.

   \return
   -

   \created     12.01.2011   STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)    Author               Description
   12.01.2011          STW/M.Greiner        function created
   \endhistory
*/
//-----------------------------------------------------------------------------
int main(void)
{
   T_J1939_bus_parameters t_J1939BusParameters = {0};
   pthread_t              t_J1939LibThread;
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

   // set TP configuration
   J1939_set_tp_configuration(mat_BdtRx, mat_BdtTx, NULL, NULL);

   // set DM1 Tx DTC table
   s16_Return = J1939_dm1_tx_register_dtc_list(J1939_DM1_GET_TX_TABLE_MNG(mat_J1939_Node12TxDtc));
   if (s16_Return != C_NO_ERR)
   {
      mv_StdoutWriteString("\nCould not register DM1 DTC list!\n");
   }

   // set the callback function for Rx DM1
   J1939_dm1_rx_init_callback(&mpr_Dm1RxCallback);

   // set DM2 Tx
   s16_Return = J1939_dm2_tx_register(&mat_BdtTx[1]);
   if (s16_Return != C_NO_ERR)
   {
      mv_StdoutWriteString("\nCould not register DM2 TX connection!\n");
   }

   // set the callback function for Rx DM2
   J1939_dm2_rx_init_callback(&mpr_Dm2RxCallback);

   // J1939 request on Bus0 and Bus1 (only for testing corect CAN bus wiring and configuration)
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
   mv_StdoutWriteString("  h <RETURN>              - print supported commands\n");
   mv_StdoutWriteString("  0 [0..7] <RETURN>       - DM1 set DTC with index [0..7] to status OFF\n");
   mv_StdoutWriteString("  1 [0..7] <RETURN>       - DM1 set DTC with index [0..7] to status ON\n");
   mv_StdoutWriteString("  2 <RETURN>              - DM2 request the DM2 datas from provider node\n");
   mv_StdoutWriteString("  3 <RETURN>              - DM3 reset DM2 datas on provider node\n");
   mv_StdoutWriteString("  4 [0..3] [0,1] <RETURN> - set lamp [0..3] status [0..1]\n");
   mv_StdoutWriteString("  q <RETURN>              - exit from demo application\n");
}


//-----------------------------------------------------------------------------
/*!
   \brief    Read user commands from RS232 interface

   Read commands from stdin interface and call the command function.

   \return
    -

   \created            12.01.2011   STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)   Author                Description
   12.01.2011         STW/M.Greiner         function created
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

   \created            12.01.2011   STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)   Author                Description
   12.01.2011         STW/M.Greiner         function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mv_CmdExecute(const charn * const opcn_Command)
{
   static T_J1939_DM_lamp ht_Lamp = {OFF, OFF, OFF, OFF};

   switch (opcn_Command[0])
   {
   case 'h':
      mv_PrintHelp();
      break;
   case 'q':
      exit(0);
      break;

   case '0':
   case '1':
      // set DM1 DTC ON or OFF
      if ((opcn_Command[2] >= '0') && (opcn_Command[2] < '8'))
      {
         mat_J1939_Node12TxDtc[opcn_Command[2] - (uint8)'0'].u8_State = opcn_Command[0] - (uint8)'0';
      }
      break;

   case '2':
      // request DM2 message
      J1939_dm2_rx_send_request(0, 0x34, 0x12);
      break;

   case '3':
      // send DM3 to DM1,2 provider node
      J1939_dm3_tx_send_clear(0, 0x34, 0x12);
      break;

   case '4':
      // set lamp status for DTC list
      switch (opcn_Command[2])
      {
      case '0':
         ht_Lamp.u8_MalfIndLamp   = opcn_Command[4] - (uint8)'0';
         break;
      case '1':
         ht_Lamp.u8_RedStopLamp   = opcn_Command[4] - (uint8)'0';
         break;
      case '2':
         ht_Lamp.u8_AmberWarnLamp = opcn_Command[4] - (uint8)'0';
         break;
      case '3':
         ht_Lamp.u8_ProtectLamp   = opcn_Command[4] - (uint8)'0';
         break;
      default:
         break;
      }
      J1939_dm1_tx_set_lamps(J1939_DM1_GET_TX_TABLE_MNG(mat_J1939_Node12TxDtc), &ht_Lamp);
      break;

   default:
      break;
   }
}


//-----------------------------------------------------------------------------
/*!
   \brief    Callback function for DM1

   For each received DTC and lamp info, J1939 stack call this function.

   \param[in]          ou16_Channel     on which bus is receive the DM1
   \param[in]          ou8_SenderAddr   the node which send the DM1
   \param[in]          opt_Dm1Data      decoded DM1 DTC info

   \return
    -

   \created            12.01.2011   STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)   Author                Description
   12.01.2011         STW/M.Greiner         function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mpr_Dm1RxCallback(const uint16 ou16_Channel, const uint8 ou8_SrcAddress,
                              const T_J1939_DM_rx_dtc * const opt_Data)
{
   static T_J1939_DM_lamp ht_OldLamp;
   static T_J1939_DM_dtc  hat_OldDtcList[MAX_NR_RX_DTC];
   static T_J1939_DM_dtc  hat_DtcList[MAX_NR_RX_DTC];
   charn  acn_String[200] = {0};
   uint16 u16_Cnt;
   sint16 s16_Return;

   if ((ou16_Channel == 0) && (ou8_SrcAddress == 0x12))
   {
      // this is the searched node (relevant if more DM1 connection are active)
      if (opt_Data->t_DtcState.u16_DtcIndex == 1)
      {
         // first callback, reset DTC buffer
         (void)memset(hat_DtcList, 0x00, sizeof(hat_DtcList));
      }
      if (opt_Data->t_DtcState.u16_DtcIndex <= opt_Data->t_DtcState.u16_TotalNrDtc)
      {
         // save DTC
         if ((opt_Data->t_DtcState.u16_DtcIndex > 0             ) &&
             (opt_Data->t_DtcState.u16_DtcIndex <= MAX_NR_RX_DTC))
         {
            hat_DtcList[opt_Data->t_DtcState.u16_DtcIndex - 1].u32_Spn         = opt_Data->t_Dtc.u32_Spn;
            hat_DtcList[opt_Data->t_DtcState.u16_DtcIndex - 1].u8_Fmi          = opt_Data->t_Dtc.u8_Fmi;
            hat_DtcList[opt_Data->t_DtcState.u16_DtcIndex - 1].u8_OccurCounter = opt_Data->t_Dtc.u8_OccurCounter;
            hat_DtcList[opt_Data->t_DtcState.u16_DtcIndex - 1].u8_SpnConvMode  = opt_Data->t_Dtc.u8_SpnConvMode;
         }
      }
      if (opt_Data->t_DtcState.u16_DtcIndex >= opt_Data->t_DtcState.u16_TotalNrDtc)
      {
         // all DTC received
         // compare lamp status
         s16_Return = (sint16)memcmp(&ht_OldLamp, &opt_Data->t_Lamp, sizeof(ht_OldLamp));
         // compare DTC list
         s16_Return += (sint16)memcmp(&hat_OldDtcList, &hat_DtcList, sizeof(hat_OldDtcList));
         if (s16_Return != 0)
         {
            // data has changed, print to stdout
            // print lamp status
            mv_StdoutWriteString("\n DM1 RX:\n");
            (void)sprintf(acn_String, " MalfunctionIndicationLamp = %d\n", opt_Data->t_Lamp.u8_MalfIndLamp);
            mv_StdoutWriteString(acn_String);
            (void)sprintf(acn_String, " RedStopLamp               = %d\n", opt_Data->t_Lamp.u8_RedStopLamp);
            mv_StdoutWriteString(acn_String);
            (void)sprintf(acn_String, " AmberWarningLamp          = %d\n", opt_Data->t_Lamp.u8_AmberWarnLamp);
            mv_StdoutWriteString(acn_String);
            (void)sprintf(acn_String, " ProtectLamp               = %d\n", opt_Data->t_Lamp.u8_ProtectLamp);
            mv_StdoutWriteString(acn_String);
            // print DTCs
            (void)sprintf(acn_String, " \n Active DTCs = %d\n\n", opt_Data->t_DtcState.u16_TotalNrDtc);
            mv_StdoutWriteString(acn_String);
            for (u16_Cnt = 0; u16_Cnt < opt_Data->t_DtcState.u16_TotalNrDtc; u16_Cnt++)
            {
               (void)sprintf(acn_String, " DTC Nr %d\n", u16_Cnt + 1);
               mv_StdoutWriteString(acn_String);
               (void)sprintf(acn_String, "   SPN = 0x%04X\n", (uint16)hat_DtcList[u16_Cnt].u32_Spn);
               mv_StdoutWriteString(acn_String);
               (void)sprintf(acn_String, "   FMI = %d\n", hat_DtcList[u16_Cnt].u8_Fmi);
               mv_StdoutWriteString(acn_String);
               (void)sprintf(acn_String, "   SpnConvMode = %d\n", hat_DtcList[u16_Cnt].u8_SpnConvMode);
               mv_StdoutWriteString(acn_String);
               (void)sprintf(acn_String, "   OccurCounter = %d\n", hat_DtcList[u16_Cnt].u8_OccurCounter);
               mv_StdoutWriteString(acn_String);
            }
            // replace the old states with the actual states
            ht_OldLamp = opt_Data->t_Lamp;
            (void)memcpy(&hat_OldDtcList, &hat_DtcList, sizeof(hat_OldDtcList));
         }
      }
   }
}


//-----------------------------------------------------------------------------
/*!
   \brief    Callback function for DM2

   After DM2 request, the DM2 provider node send the Lamp and DTC info for
   previous active DTC. This function is called for each received info.
   Because the DM2 is only send after request, is not necesary to store
   the old states.

   \param[in]          ou16_Channel     on which bus is receive the DM2
   \param[in]          ou8_SenderAddr   the node which send the DM2
   \param[in]          opt_Dm1Data      decoded DM2 DTC info

   \return
    -

   \created            12.01.2011   STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)   Author                Description
   12.01.2011         STW/M.Greiner         function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mpr_Dm2RxCallback(const uint16 ou16_Channel, const uint8 ou8_SrcAddress,
                              const T_J1939_DM_rx_dtc * const opt_Data)
{
   charn  acn_String[200] = {0x00};

   if ((ou16_Channel == 0) && (ou8_SrcAddress == 0x12))
   {
      if (opt_Data->t_DtcState.u16_DtcIndex <= 1)
      {
         mv_StdoutWriteString("\n DM2 RX:\n");
         (void)sprintf(acn_String, " MalfunctionIndicationLamp = %d\n", opt_Data->t_Lamp.u8_MalfIndLamp);
         mv_StdoutWriteString(acn_String);
         (void)sprintf(acn_String, " RedStopLamp               = %d\n", opt_Data->t_Lamp.u8_RedStopLamp);
         mv_StdoutWriteString(acn_String);
         (void)sprintf(acn_String, " AmberWarningLamp          = %d\n", opt_Data->t_Lamp.u8_AmberWarnLamp);
         mv_StdoutWriteString(acn_String);
         (void)sprintf(acn_String, " ProtectLamp               = %d\n", opt_Data->t_Lamp.u8_ProtectLamp);
         mv_StdoutWriteString(acn_String);
         // print number of previous active DTCs
         (void)sprintf(acn_String, " \n Previous Active DTCs = %d\n\n", opt_Data->t_DtcState.u16_TotalNrDtc);
         mv_StdoutWriteString(acn_String);
      }
      // print DTC if available
      if (opt_Data->t_DtcState.u16_TotalNrDtc != 0)
      {
         (void)sprintf(acn_String, " DTC Nr %d\n", opt_Data->t_DtcState.u16_DtcIndex);
         mv_StdoutWriteString(acn_String);
         (void)sprintf(acn_String, "   SPN = 0x%04X\n", (uint16)opt_Data->t_Dtc.u32_Spn);
         mv_StdoutWriteString(acn_String);
         (void)sprintf(acn_String, "   FMI = %d\n", opt_Data->t_Dtc.u8_Fmi);
         mv_StdoutWriteString(acn_String);
         (void)sprintf(acn_String, "   SpnConvMode = %d\n", opt_Data->t_Dtc.u8_SpnConvMode);
         mv_StdoutWriteString(acn_String);
         (void)sprintf(acn_String, "   OccurCounter = %d\n", opt_Data->t_Dtc.u8_OccurCounter);
         mv_StdoutWriteString(acn_String);
      }
   }
}
