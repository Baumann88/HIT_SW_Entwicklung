//-----------------------------------------------------------------------------
/*!
   \internal
   \file        CANopen.c
   \brief       main module of example application for yiox/ydios/col2 library for TC3

   For IOX usage:
   This example project requires 1 iox of type "D".
   The node id of the IOX is "13".
   For DIOS usage:
   This example project requires 1 DIOM/DIOS
   The node id is 2


   \implementation
   project     COL2/YIOX
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   created     18.03.2010  F.Belser
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author             Description
   18.03.2010        F.Belser           file created
   \endhistory
*/
//-----------------------------------------------------------------------------

/* -- Includes ------------------------------------------------------------ */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stwtypes.h>
#include <stwerror.h>   //STW errors
#include <sys/time.h>
#include <col2.h>       //include CANopen Layer2 function headers
#include <yiox.h>       //include YIOX library function headers
#include <ydios.h>

/* -- Defines ------------------------------------------------------------- */
#define CAN_BUS1                0            // Define for CAN1
#define CAN_BUS2                1            // Define for CAN2

#define YDIOS_NODE_ID           13           // NodeID of the DIOS
#define YIOX1_NODE_ID           (1)          // YIOX node id

#define YIOX_TYPE               YIOX_TYPE_D  // YIOX Type
#define DIOS_TYPE               YDIOS_TYPE_D // YDIOS Type

#define YIOX_SELECT             (4)          // Select inputs configuration for the iox


#define IOX_PWM_SEND_TIME_MIN   (20)
#define IOX_PWM_SEND_TIME_MAX   (100)
#define IOX_DOUT_SEND_TIME_MIN  (20)
#define IOX_DOUT_SEND_TIME_MAX  (100)

#define DIOS_PWM_SEND_TIME_MIN   (20)
#define DIOS_PWM_SEND_TIME_MAX   (100)
#define DIOS_DOUT_SEND_TIME_MIN  (20)
#define DIOS_DOUT_SEND_TIME_MAX  (100)
/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Module Global Variables --------------------------------------------- */
static struct timeval mt_TimeSinceInit;


/* -- Module Global Function Prototypes ----------------------------------- */
static uint32 mu32_sys_get_time_ms (void);
static sint16 ms16_SetPinsToDigitalOutputs (void *opv_HandleIOX, void *opv_HandleBusCOL2);
static sint16 ms16_IOX_ExitSequence (void *opv_HandleIOX);
static sint16 ms16_SetPinsToPWMOutputs (void *opv_HandleIOX, void *opv_HandleBusCOL2);
static sint16 ms16_SetPinsToVoltageInputs (void *opv_HandleIOX, void *opv_HandleBusCOL2);
static sint16 ms16_SetPinsToCurrentInputs (void *opv_HandleIOX, void *opv_HandleBusCOL2);
static sint16 ms16_DIOS_ExitSequence (void *opv_HandleDIOS);


/* -- Implementation ------------------------------------------------------ */
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
   \brief   ms16_SetPinsToPWMOutputs (void *opv_HandleIOX, void *opv_HandleBusCOL2)

   Function set pin group 6 -> 09 to PWM outputs

   \param[in]     opv_HandleIOX:     reference to the IOX
   \param[in]     opv_HandleBusCOL2: reference to the COL2

   \return
   C_NO_ERR       No error occured
   else           Error occured

   \created       18.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   18.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static sint16 ms16_SetPinsToPWMOutputs (void *opv_HandleIOX, void *opv_HandleBusCOL2)
{
   sint16 s16_retval = C_NO_ERR;
   uint8 u8_Counter = 0;

   // Set IOX pins 2 - 13 to digital outputs
   for (u8_Counter = 6; u8_Counter <= 9; u8_Counter++)
   {
      // set return value to C_BUSY
      s16_retval = C_BUSY;
      while (s16_retval == C_BUSY)
      {
         s16_retval = yiox_set_pin_configuration (opv_HandleIOX, u8_Counter, YIOX_PWM_OUTPUT);
         // trigger task systems
         col2_task (opv_HandleBusCOL2);
         yiox_task ();
      }
   }

   return (s16_retval);
}


//-----------------------------------------------------------------------------
/*!
   \brief   ms16_SetPinsToDigitalOutputs (void *opv_HandleIOX, void *opv_HandleBusCOL2)

   Function set pin group 2 -> 13 to digital outputs

   \param[in]     opv_HandleIOX:     reference to the IOX
   \param[in]     opv_HandleBusCOL2: reference to the COL2

   \return
   C_NO_ERR       No error occured
   else           Error occured

   \created       18.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   18.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static sint16 ms16_SetPinsToDigitalOutputs (void *opv_HandleIOX, void *opv_HandleBusCOL2)
{
   sint16 s16_retval = C_NO_ERR;
   uint8 u8_Counter = 0;

   // Set IOX pins 2 - 13 to digital outputs
   for (u8_Counter = 2; u8_Counter <= 13; u8_Counter++)
   {
      // set return value to C_BUSY
      s16_retval = C_BUSY;
      while (s16_retval == C_BUSY)
      {
         s16_retval = yiox_set_pin_configuration (opv_HandleIOX, u8_Counter, YIOX_DIGITAL_OUTPUT);
         // trigger task systems
         col2_task (opv_HandleBusCOL2);
         yiox_task ();
      }
   }

   return (s16_retval);
}


//-----------------------------------------------------------------------------
/*!
   \brief   ms16_SetPinsToVoltageInputs (void *opv_HandleIOX, void *opv_HandleBusCOL2)

   Function set pin20 to analogue input

   \param[in]     opv_HandleIOX:     reference to the IOX
   \param[in]     opv_HandleBusCOL2: reference to the COL2

   \return
   C_NO_ERR       No error occured
   else           Error occured

   \created       18.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   18.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static sint16 ms16_SetPinsToVoltageInputs (void *opv_HandleIOX, void *opv_HandleBusCOL2)
{
   sint16 s16_retval = C_NO_ERR;

   // Set IOX pin 20 to Analogue input
   //set return value to C_BUSY
   s16_retval = C_BUSY;
   while (s16_retval == C_BUSY)
   {
      s16_retval = yiox_set_pin_configuration (opv_HandleIOX, 20, YIOX_ANALOGUE_INPUT);
      // trigger task systems
      col2_task (opv_HandleBusCOL2);
      yiox_task ();
   }

   return (s16_retval);
}

//-----------------------------------------------------------------------------
/*!
   \brief   static sint16 ms16_SetPinsToCurrentInputs (void *opv_HandleIOX, void *opv_HandleBusCOL2)

   Function set pin24 to current input

   \param[in]     opv_HandleIOX:     reference to the IOX
   \param[in]     opv_HandleBusCOL2: reference to the COL2

   \return
   C_NO_ERR       No error occured
   else           Error occured

   \created       18.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   18.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static sint16 ms16_SetPinsToCurrentInputs (void *opv_HandleIOX, void *opv_HandleBusCOL2)
{
   sint16 s16_retval = C_NO_ERR;

   // Set IOX pin 20 to Analogue input
   //set return value to C_BUSY
   s16_retval = C_BUSY;
   while (s16_retval == C_BUSY)
   {
      s16_retval = yiox_set_pin_configuration (opv_HandleIOX, 24, YIOX_ANALOGUE_INPUT);
      // trigger task systems
      col2_task (opv_HandleBusCOL2);
      yiox_task ();
   }

   return (s16_retval);
}


//-----------------------------------------------------------------------------
/*!
   \brief   ms16_IOX_ExitSequence (void *opv_HandleIOX)

   Stops the IOX, close all instances of the IOX. If everything works finde, the
   COL2 will be also closed

   \param[in]     opv_HandleIOX:     reference to the IOX

   \return
   C_NO_ERR       No error occured
   else           Error occured

   \created       18.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   18.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static sint16 ms16_IOX_ExitSequence (void *opv_HandleIOX)
{
   sint16 s16_retval = C_NO_ERR;
   s16_retval = yiox_stop (opv_HandleIOX);
   if (s16_retval == C_NO_ERR)
   {
      // close IOX
      s16_retval = yiox_close ();
   }
   return (s16_retval);
}


//-----------------------------------------------------------------------------
/*!
   \brief   ms16_DIOS_ExitSequence (void *opv_HandleDIOS)

   Stops the IOX, close all instances of the IOX. If everything works finde, the
   COL2 will be also closed

   \param[in]     opv_HandleDIOS:     reference to the DIOS

   \return
   C_NO_ERR       No error occured
   else           Error occured

   \created       18.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   18.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static sint16 ms16_DIOS_ExitSequence (void *opv_HandleDIOS)
{
   sint16 s16_retval = C_NO_ERR;
   s16_retval = ydios_stop (opv_HandleDIOS);
   if (s16_retval == C_NO_ERR)
   {
      // close IOX
      s16_retval = ydios_close ();
   }
   return (s16_retval);
}



//-----------------------------------------------------------------------------
/*!
   \brief   int main(void)

   \return

   \created       18.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   18.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
int main(void)
{
   sint16 s16_retval                     = C_NO_ERR;     // return value
   sint16 s16_retval2                    = C_NO_ERR;     // return value
   T_yiox_config t_ConfigIOX;                            // IOX configuration structure
   T_ydios_config t_ConfigDIOS;                          // DIOS configuration structure
   T_col2_bus_parameters t_LibraryConfig = {0};          // COL2 configuration structure
   charn cn_Input                        = '\0';         // Input value
   uint16 u16_toggleDig                  = 0x0000u;
   sint16 s16_togglePWM                  = 0;
   uint32 u32_timer1                     = 0;
   uint32 u32_timer2                     = 0;
   uint8  u8_counter                     = 0;
   uint8 u8_SwitchFlag                   = 0;
   static void * hpv_IOX1;                               //handle for IOX module
   static void * hpv_DIOS1;                              //handl for DIOS module
   static void * hpv_Bus;                                //handle for CANopen bus

   // set CAN Bus 1
   t_LibraryConfig.u8_Channel = CAN_BUS1;

   // init CANopen to CAN Bus1, with SDO timeout 500ms, TC3 node ID 100
   s16_retval = col2_init (&t_LibraryConfig, 500, 100, &hpv_Bus);
   if (s16_retval == C_NO_ERR)
   {
      //------------------------------------------------------------------
      //               Configuration of the IOX init structure
      //------------------------------------------------------------------
      // IOX is supposed to be present on this COL2 bus
      t_ConfigIOX.pv_COL2BusHandle         = hpv_Bus;
      // Set IOX node ID to1
      t_ConfigIOX.u8_NodeID                = YIOX1_NODE_ID;
      // Set IOX type to TYPE D
      t_ConfigIOX.u8_IOXType               = YIOX_TYPE;
      // Not used TPDOs must be set to 0x80000000u !!!!
      t_ConfigIOX.au32_TPDOIDs[0]          = 0x180u;
      t_ConfigIOX.au32_TPDOIDs[1]          = 0x280u;
      t_ConfigIOX.au32_TPDOIDs[2]          = 0x380u;
      t_ConfigIOX.au32_TPDOIDs[3]          = 0x480u;
      t_ConfigIOX.au32_TPDOIDs[4]          = 0x80000000u;
      t_ConfigIOX.au32_TPDOIDs[5]          = 0x80000000u;
      t_ConfigIOX.au32_TPDOIDs[6]          = 0x80000000u;
      t_ConfigIOX.au32_TPDOIDs[7]          = 0x80000000u;
      t_ConfigIOX.au32_TPDOIDs[8]          = 0x80000000u;
      t_ConfigIOX.au32_TPDOIDs[9]          = 0x80000000u;
      // Set PWM send mode
      t_ConfigIOX.u8_PWMOutSendMode        = YIOX_SEND_MODE_ON_CHANGE |
                                             YIOX_SEND_MODE_CYCLICALLY;
      // keep a minimm PDO interval of 20 ms
      t_ConfigIOX.u16_PWMOutMinIntervalMS  = IOX_PWM_SEND_TIME_MIN;
      // if no change send after 100 ms nevertheless
      t_ConfigIOX.u16_PWMOutMaxIntervalMS  = IOX_PWM_SEND_TIME_MAX;
      // Set DOut send mode
      t_ConfigIOX.u8_DigOutSendMode        = YIOX_SEND_MODE_ON_CHANGE |
                                             YIOX_SEND_MODE_CYCLICALLY;
      // keep a minimm PDO interval of 20 ms
      t_ConfigIOX.u16_DigOutMinIntervalMS  = IOX_DOUT_SEND_TIME_MIN;
      // if no change send after 100 ms nevertheless
      t_ConfigIOX.u16_DigOutMaxIntervalMS  = IOX_DOUT_SEND_TIME_MAX;

      //------------------------------------------------------------------
      //               Configuration of the DIOS init structure
      //------------------------------------------------------------------
      t_ConfigDIOS.pv_COL2BusHandle        = hpv_Bus;// DIOS is supposed to be present on this COL2 bus
      t_ConfigDIOS.au16_PWMHysteresis[0]   = 100;    // PWM output values 1 should only be re-sent,
                                                     // if its value has changes by more than 100
      t_ConfigDIOS.au16_PWMHysteresis[1]   = 100;
      t_ConfigDIOS.au16_PWMHysteresis[2]   = 100;
      t_ConfigDIOS.au16_PWMHysteresis[3]   = 100;
      t_ConfigDIOS.au8_PWMOutReg[0]        = 0;      // standard pwm output shall be used -> (0 .. 10000)*0,01%
      t_ConfigDIOS.au8_PWMOutReg[1]        = 0;
      t_ConfigDIOS.au8_PWMOutReg[2]        = 1;      // the pwm output shall be current controlled -> (0 .. 4000)*1mA
      t_ConfigDIOS.au8_PWMOutReg[3]        = 1;

      // send PWM PDO on change (considering hysteresis) or after max - interval
      t_ConfigDIOS.u8_PWMOutSendMode       = YDIOS_SEND_MODE_ON_CHANGE |
                                             YDIOS_SEND_MODE_CYCLICALLY;
      t_ConfigDIOS.u16_PWMOutMinIntervalMS = DIOS_PWM_SEND_TIME_MIN;
      t_ConfigDIOS.u16_PWMOutMaxIntervalMS = DIOS_PWM_SEND_TIME_MAX;

      // send PWM PDO on change (considering hysteresis) or after max - interval
      t_ConfigDIOS.u8_DigOutSendMode       = YDIOS_SEND_MODE_ON_CHANGE |
                                             YDIOS_SEND_MODE_CYCLICALLY;
      t_ConfigDIOS.u16_DigOutMinIntervalMS = DIOS_DOUT_SEND_TIME_MIN;
      t_ConfigDIOS.u16_DigOutMaxIntervalMS = DIOS_DOUT_SEND_TIME_MAX;

      t_ConfigDIOS.u8_DIOSType             = DIOS_TYPE;
      t_ConfigDIOS.u8_NodeID               = YDIOS_NODE_ID;


      //------------------------------------------------------------------
      //               IOX init sequence
      //------------------------------------------------------------------
      s16_retval = yiox_init (&t_ConfigIOX, &hpv_IOX1);
      if (s16_retval == C_NO_ERR)
      {
         // start iox
         s16_retval = yiox_start (hpv_IOX1);
      }
      //------------------------------------------------------------------
      //               DIOS init sequence
      //------------------------------------------------------------------
      s16_retval2 = ydios_init (&t_ConfigDIOS, &hpv_DIOS1);
      if (s16_retval == C_NO_ERR)
      {
         // start dios
         s16_retval2 = ydios_start (hpv_DIOS1);
      }
      if ((s16_retval == C_NO_ERR) && (s16_retval2 == C_NO_ERR))
      {
         while (1)
         {
            // trigger task systems
            col2_task (hpv_Bus);
            yiox_task ();
            ydios_task ();
            if (cn_Input != '\n')
            {
               printf ("CANopen Test Application for IOX/DIOS/DIOM\n");
               printf (".---------------------------------.\n");
               printf ("|              Menu               |\n");
               printf ("'---------------------------------'\n");
               printf ("\t(0) Exit\n");
               printf ("\t(1) IOX Toggle Digital outputs 1 - 12\n");
               printf ("\t(2) IOX Sequence Light 5 seconds\n");
               printf ("\t(3) IOX PWM outputs 1 - 4 toggle \n");
               printf ("\t(4) IOX PWM outputs 1 - 4 dim to zero\n");
               printf ("\t(5) IOX Get Voltage Input: YIOX_UIN_02\n");
               printf ("\t(6) IOX Get Current Input: YIOX_IIN_02\n");
               printf ("\t(7) DIOS Toggle Digital outputs 1- 4\n");
            }
            cn_Input = getchar ();
            // switch between the different input values
            //------------------------------------------------------------------
            //               EXIT
            //------------------------------------------------------------------
            if (cn_Input == '0')
            {
               // IOX exit sequence
               s16_retval = ms16_IOX_ExitSequence (hpv_IOX1);
               if (s16_retval != C_NO_ERR)
               {
                  printf ("IOX_close... FAILED\n");
               }
               // DIOS exit sequence
               s16_retval = ms16_DIOS_ExitSequence (hpv_DIOS1);
               if (s16_retval != C_NO_ERR)
               {
                  printf ("DIOS_close... FAILED\n");
               }
               // Close COL2
               (void) col2_close (hpv_Bus);
               break;
            }
            //------------------------------------------------------------------
            //               IOX Toggle Digital Inputs
            //------------------------------------------------------------------
            else if (cn_Input == '1')
            {
               s16_retval = ms16_SetPinsToDigitalOutputs(hpv_IOX1, hpv_Bus);
               if (s16_retval == C_NO_ERR)
               {
                  // toggle digital outputs
                  u16_toggleDig = (u16_toggleDig == 0x0000u)? 0x0FFFu: 0x0000;
                  s16_retval = yiox_out_set_digital_values_all (hpv_IOX1, u16_toggleDig);
               }
               if (s16_retval != C_NO_ERR)
               {
                  printf ("Toggle Pins... Failed\n");
               }
            }
            //------------------------------------------------------------------
            //               IOX Sequence Light
            //------------------------------------------------------------------
            else if (cn_Input == '2')
            {
               s16_retval = ms16_SetPinsToDigitalOutputs(hpv_IOX1, hpv_Bus);
               if (s16_retval == C_NO_ERR)
               {
                  // u16_toogle reset
                  u16_toggleDig = 0x0001u;
                  (void) yiox_out_set_digital_values_all (hpv_IOX1, u16_toggleDig);
                  u32_timer1 = mu32_sys_get_time_ms ();
                  u32_timer2 = mu32_sys_get_time_ms ();
                  while ((u32_timer1 + 5000) >= mu32_sys_get_time_ms ())
                  {
                     // trigger task systems
                     col2_task (hpv_Bus);
                     yiox_task ();
                     if ((u32_timer2 + 30) < mu32_sys_get_time_ms ())
                     {
                        if (u8_SwitchFlag == 0)
                        {
                           u16_toggleDig <<= 1;
                        }
                        else
                        {
                           u16_toggleDig >>=1;
                        }
                        (void) yiox_out_set_digital_values_all (hpv_IOX1, u16_toggleDig);
                        if (u16_toggleDig >= 0x0800u)
                        {
                           u8_SwitchFlag = 1;
                        }
                        if (u16_toggleDig <= 0x0001u)
                        {
                           u8_SwitchFlag =0;
                        }
                        u32_timer2 = mu32_sys_get_time_ms ();
                     }
                  }
                  // u16_toogle reset
                  u16_toggleDig = 0x0000u;
               }
               if (s16_retval != C_NO_ERR)
               {
                  printf ("Sequence Light... Failed\n");
               }
            }
            //------------------------------------------------------------------
            //               Set IOX PWM outputs 1 -4 toggle
            //------------------------------------------------------------------
            else if (cn_Input == '3')
            {
               s16_retval = ms16_SetPinsToPWMOutputs(hpv_IOX1, hpv_Bus);
               if (s16_retval == C_NO_ERR)
               {
                  col2_task (hpv_Bus);
                  yiox_task ();
                  // toggle pwm outputs
                  s16_togglePWM = (s16_togglePWM == 0)? 1000: 0;
                  for (u8_counter = YIOX_PWM_IREG_OUT_01; u8_counter <= YIOX_PWM_IREG_OUT_04; u8_counter++)
                  {
                     col2_task (hpv_Bus);
                     yiox_task ();
                     s16_retval = yiox_out_set_pwm_value (hpv_IOX1, u8_counter, s16_togglePWM);
                     col2_task (hpv_Bus);
                     yiox_task ();
                  }
               }
               if (s16_retval != C_NO_ERR)
               {
                  printf ("Set PWM outputs... Failed\n");
               }
            }
            //------------------------------------------------------------------
            //               PWM outputs 1 -4 tim to zero
            //------------------------------------------------------------------
            else if (cn_Input == '4')
            {
               s16_retval = ms16_SetPinsToPWMOutputs(hpv_IOX1, hpv_Bus);
               if (s16_retval == C_NO_ERR)
               {
                  // set pwm output value for start
                  s16_togglePWM = 1000;
                  // set timer
                  u32_timer1 = mu32_sys_get_time_ms ();
                  while (s16_togglePWM >= 0)
                  {
                     if ((u32_timer1 + 2) <= mu32_sys_get_time_ms ())
                     {
                        for (u8_counter = YIOX_PWM_IREG_OUT_01; u8_counter <= YIOX_PWM_IREG_OUT_04; u8_counter++)
                        {
                           s16_retval = yiox_out_set_pwm_value (hpv_IOX1, u8_counter, s16_togglePWM);
                        }
                        s16_togglePWM -= 1;
                        u32_timer1 = mu32_sys_get_time_ms ();
                     }
                     col2_task (hpv_Bus);
                     yiox_task ();
                  }
                  // reset s16_togglePWM value
                  s16_togglePWM = 50;
               }
               if (s16_retval != C_NO_ERR)
               {
                  printf ("Set PWM outputs... Failed\n");
               }
            }
            //------------------------------------------------------------------
            //               Get IOX analogue input 2
            //------------------------------------------------------------------
            else if (cn_Input == '5')
            {
               s16_retval = ms16_SetPinsToVoltageInputs(hpv_IOX1, hpv_Bus);
               if (s16_retval == C_NO_ERR)
               {
                  u32_timer1 = mu32_sys_get_time_ms ();
                  while ((u32_timer1 + 1000) > mu32_sys_get_time_ms ())
                  {
                     col2_task (hpv_Bus);
                     yiox_task ();
                  }
                  // get PWM Input value
                  s16_retval = yiox_in_get_voltage_value (hpv_IOX1, YIOX_UIN_02, &s16_togglePWM);
                  col2_task (hpv_Bus);
                  yiox_task ();
                  printf ("Voltage Value: %i mV\n", s16_togglePWM);
               }
               if (s16_retval != C_NO_ERR)
               {
                  printf ("Set PWM outputs... Failed\n");
               }
            }
            //------------------------------------------------------------------
            //               Get IOX current input 2
            //------------------------------------------------------------------
            else if (cn_Input == '6')
            {
               s16_retval = ms16_SetPinsToCurrentInputs(hpv_IOX1, hpv_Bus);
               if (s16_retval == C_NO_ERR)
               {
                  u32_timer1 = mu32_sys_get_time_ms ();
                  while ((u32_timer1 + 1000) > mu32_sys_get_time_ms ())
                  {
                     col2_task (hpv_Bus);
                     yiox_task ();
                  }
                  // get PWM Input value
                  s16_retval = yiox_in_get_current_value (hpv_IOX1, YIOX_IIN_02, &s16_togglePWM);
                  col2_task (hpv_Bus);
                  yiox_task ();
                  printf ("Current Value: %i mA, %i uA\n", s16_togglePWM / 1000, s16_togglePWM);
               }
               if (s16_retval != C_NO_ERR)
               {
                  printf ("Set PWM outputs... Failed\n");
               }
            }
            //------------------------------------------------------------------
            //               Toggle Dios digital outputs
            //------------------------------------------------------------------
            else if (cn_Input == '7')
            {
               // toggle pwm outputs
               u16_toggleDig = (u16_toggleDig == 0)? 1: 0;
               for (u8_counter = YDIOS_OUT_05; u8_counter <= YDIOS_OUT_08; u8_counter++)
               {
                  col2_task (hpv_Bus);
                  ydios_task ();
                  s16_retval = ydios_out_set_value (hpv_DIOS1, u8_counter, u16_toggleDig);
                  col2_task (hpv_Bus);
                  ydios_task ();
               }
               if (s16_retval != C_NO_ERR)
               {
                  printf ("Set PWM outputs... Failed\n");
               }
            }
         }
      }
      else
      {
         printf ("IOX_init... failed\n");
      }
   }
   else
   {
      printf ("COL2_init... failed\n");
   }
   return (0);
}
