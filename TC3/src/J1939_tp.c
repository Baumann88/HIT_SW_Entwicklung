//-----------------------------------------------------------------------------
/*!
   \internal
   \file
   \brief       main module example "transport protocol"

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
#define TRUE  1
#define FALSE 0


/* -- Types --------------------------------------------------------------- */


/* -- Global Variables ---------------------------------------------------- */


/* -- Module Global Variables --------------------------------------------- */
static uint8 mau8_BDT1[1500]  = {0};
static uint8 mau8_BDT2[1500]  = {0};
static uint8 mau8_CMDT1[1500] = {0};
static uint8 mau8_CMDT2[1500] = {0};

static T_J1939_TP_BDT_rx_def mat_BdtRx[]   =
{
   //             Bus  NodeAddr  PGN     Buffer     BufferSize         AppCallbackFct
   J1939_TPBDT_RX(0,   0x10,     0xFF34u, mau8_BDT1, sizeof(mau8_BDT1), NULL)
   J1939_TPBDT_RX_TABLE_END
};

static T_J1939_TP_BDT_tx_def mat_BdtTx[]   =
{
   //             Bus  NodeAddr  PGN     Buffer     BufferSize         AppCallbackFct
   J1939_TPBDT_TX(1,   0x10,     0xFF34u, mau8_BDT2, sizeof(mau8_BDT2), NULL)
   J1939_TPBDT_TX_TABLE_END
};

static T_J1939_TP_CMDT_rx_def mat_CmdtRx[] =
{
   //              Bus SrcNode DestNode PGN     Buffer      BufferSize          AppCallbackFct
   J1939_TPCMDT_RX(1,  0x11,   0x10,    0x9800u, mau8_CMDT1, sizeof(mau8_CMDT1), NULL)
   J1939_TPCMDT_RX_TABLE_END
};

static T_J1939_TP_CMDT_tx_def mat_CmdtTx[] =
{
   //              Bus SrcNode DestNode PGN     Buffer      BufferSize          AppCallbackFct
   J1939_TPCMDT_TX(0,  0x11,   0x10,    0x9800u, mau8_CMDT2, sizeof(mau8_CMDT2), NULL)
   J1939_TPCMDT_TX_TABLE_END
};


/* -- Module Global Function Prototypes ----------------------------------- */
static void* mpv_Thread(void *opv_Ptr);
static void mv_StdoutWriteString(const charn* opcn_String);
static void mv_PrintHelp(void);
static void mv_DataShowTask(void);
static void mv_CmdServerTask(void);
static void mv_CmdExecute(const charn * const opcn_Command);


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
   J1939_set_tp_configuration(mat_BdtRx, mat_BdtTx, mat_CmdtRx, mat_CmdtTx);

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

   Write array of char to stdout interface.

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
   mv_StdoutWriteString("  h <RETURN>        - print supported commands\n");
   mv_StdoutWriteString("  0 String <RETURN> - send/receive String with defined TP.BDT  connection\n");
   mv_StdoutWriteString("  1 String <RETURN> - send/receive String with defined TP.CMDT connection\n");
   mv_StdoutWriteString("  q <RETURN>        - exit from demo application\n");
}


//-----------------------------------------------------------------------------
/*!
   \brief    Print data to stdout interface

   Task for data printing

   \return
    -

   \created            12.01.2011   STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)    Author                Description
   12.01.2011          STW/M.Greiner         function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mv_DataShowTask(void)
{
   T_J1939_TP_BDT_rx_def  * const pt_BdtRx  = &mat_BdtRx[0];
   T_J1939_TP_CMDT_rx_def * const pt_CmdtRx = &mat_CmdtRx[0];
   charn acn_String[50];

   // BDT
   switch (pt_BdtRx->t_Ctrl.u8_LinkState)
   {
   case J1939_TP_CTRL_FINISHED: // eJ1939_FINISHED:
      // transmission finished, restart connection
      pt_BdtRx->t_Ctrl.u8_LinkState = J1939_TP_CTRL_START_TRANSFER;
      // print received string size
      mv_StdoutWriteString("\n TP.BDT received\n");
      (void)sprintf(acn_String, " %d Bytes\n", pt_BdtRx->t_Ctrl.u16_NrBytes);
      mv_StdoutWriteString(acn_String);
      // print received string
      mv_StdoutWriteString(" Rx String: ");
      mv_StdoutWriteString((charn*)(void*)mau8_BDT1);
      mv_StdoutWriteString("\n");
      break;

   case J1939_TP_CTRL_ERROR: // eJ1939_ERROR:
      // transmission finished, restart connaction
      pt_BdtRx->t_Ctrl.u8_LinkState = J1939_TP_CTRL_START_TRANSFER; // eJ1939_START_TRANSFER;
      mv_StdoutWriteString("\n TP.BDT receive ERROR!!!\n");
      break;

   default:
      break;
   }

   // CMDT
   switch(pt_CmdtRx->t_Ctrl.u8_LinkState)
   {
   case J1939_TP_CTRL_FINISHED: // eJ1939_FINISHED:
      // transmission finished, set connection to ready mode
      pt_CmdtRx->t_Ctrl.u8_LinkState = J1939_TP_CTRL_START_TRANSFER; // eJ1939_START_TRANSFER;
      // print received string size
      mv_StdoutWriteString("\n TP.CMDT received\n");
      (void)sprintf(acn_String, " %d Bytes\n", pt_CmdtRx->t_Ctrl.u16_NrBytes);
      mv_StdoutWriteString(acn_String);
      // print received string
      mv_StdoutWriteString(" Rx String: ");
      mv_StdoutWriteString((charn*)(void*)mau8_CMDT1);
      mv_StdoutWriteString("\n");
      break;

   case J1939_TP_CTRL_ERROR: // eJ1939_ERROR:
      // transmission finished, restart connaction
      pt_CmdtRx->t_Ctrl.u8_LinkState = J1939_TP_CTRL_START_TRANSFER; // eJ1939_START_TRANSFER;
      mv_StdoutWriteString("\n TP.CMDT receive ERROR!!!\n");
      break;

   default:
      break;
   }
}


//-----------------------------------------------------------------------------
/*!
   \brief    Read user commands from stdin interface

   Read commands from stdin interface and call the command function.

   \return
    -

   \created            12.01.2011   STW/M.Greiner

   \internal
   \history
   Date(dd.mm.yyyy)    Author                Description
   12.01.2011          STW/M.Greiner         function created
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
   Date(dd.mm.yyyy)    Author                Description
   12.01.2011          STW/M.Greiner         function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mv_CmdExecute(const charn * const opcn_Command)
{
   switch (opcn_Command[0])
   {
   case 'h':
      mv_PrintHelp();
      break;
   case 'q':
      exit(0);
      break;
   case '0':
      // start BDT transfer
      mat_BdtTx[0].t_Ctrl.u8_LinkState = J1939_TP_CTRL_START_TRANSFER; // eJ1939_START_TRANSFER;
      mat_BdtTx[0].t_Ctrl.u16_NrBytes = strlen(&opcn_Command[2]) + 1;
      (void)strncpy((charn*)(void*)mau8_BDT2, &opcn_Command[2], sizeof(mau8_BDT2));
      break;
   case '1':
      // start CMDT transfer
      mat_CmdtTx[0].t_Ctrl.u8_LinkState = J1939_TP_CTRL_START_TRANSFER; // eJ1939_START_TRANSFER;
      mat_CmdtTx[0].t_Ctrl.u16_NrBytes = strlen(&opcn_Command[2]) + 1;
      (void)strncpy((charn*)(void*)mau8_CMDT2, &opcn_Command[2], sizeof(mau8_CMDT2));
      break;
   default:
      // unknown command
      break;
   }
}
