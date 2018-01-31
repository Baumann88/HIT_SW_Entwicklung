//-----------------------------------------------------------------------------
/*!
   \file       ydios.h
   \brief      Library for using YDIOS I/O modules with ESX-3XL compatible CAN drivers.

   At the moment there 4 different DIOS models available at STW:
   \li \c YDIOS_TYPE_A  has 8 digital inputs which can be accessed using the defines YDIOS_IN_01 .. YDIOS_IN_08.
   \li \c YDIOS_TYPE_B  has 8 digital outputs which can be accessed using the defines YDIOS_OUT_01 .. YDIOS_OUT_08.
   \li \c YDIOS_TYPE_C  has 4 pwm outputs which can be accessed using the defines YDIOS_OUT_01 .. YDIOS_OUT_04 and
                            4 digital inputs which can be accessed using the defines YDIOS_IN_05 .. YDIOS_IN_08.
   \li \c YDIOS_TYPE_D  has 4 pwm outputs which can be accessed using the defines YDIOS_OUT_01 .. YDIOS_OUT_04 and
                            4 digital outputs which can be accessed using the defines YDIOS_OUT_05 .. YDIOS_OUT_08.

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   created     31.03.2008  STW/M.Heiss
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author        Description
   22.09.2008        STW/M.Heiss   common functions to set and get the value / current of the inputs or outputs (V0.03r0)
   20.06.2008        STW/M.Heiss   usage of fifo buffers, cyclical transmission of pdo output data (V0.02r4)
   09.06.2008        STW/M.Heiss   no fifo buffer for CAN object (V0.02r3)
   28.05.2008        STW/M.Heiss   function for busoff detection added (V0.02r2)
   08.05.2008        STW/M.Heiss   conditional sdo write implemented (V0.02r1)
   17.04.2008        STW/M.Heiss   version number increased (V0.02r0)
   15.04.2008        STW/M.Heiss   version number increased (V0.01r1)
   11.04.2008        STW/M.Heiss   basics are implemented now (V0.01r0)
   31.03.2008        STW/M.Heiss   portation from ESX2 implementation (V0.01r0)
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _YDIOS_H
#define _YDIOS_H


/* -- Includes ------------------------------------------------------------ */
#include "stwtypes.h"


/* -- Defines ------------------------------------------------------------- */

//DIOS' inputs
#define YDIOS_IN_01                 (0x0000u)   //digital input for dios type A
#define YDIOS_IN_02                 (0x0001u)   //digital input for dios type A
#define YDIOS_IN_03                 (0x0002u)   //digital input for dios type A
#define YDIOS_IN_04                 (0x0003u)   //digital input for dios type A
#define YDIOS_IN_05                 (0x0004u)   //digital input for dios type A
#define YDIOS_IN_06                 (0x0005u)   //digital input for dios type A
#define YDIOS_IN_07                 (0x0006u)   //digital input for dios type A
#define YDIOS_IN_08                 (0x0007u)   //digital input for dios type A

//DIOS' outputs
#define YDIOS_OUT_01                (0x0000u)   //pwm output for dios type C and D, digital output for dios type B
#define YDIOS_OUT_02                (0x0001u)   //pwm output for dios type C and D, digital output for dios type B
#define YDIOS_OUT_03                (0x0002u)   //pwm output for dios type C and D, digital output for dios type B
#define YDIOS_OUT_04                (0x0003u)   //pwm output for dios type C and D, digital output for dios type B
#define YDIOS_OUT_05                (0x0004u)   //digital output for dios type B and D
#define YDIOS_OUT_06                (0x0005u)   //digital output for dios type B and D
#define YDIOS_OUT_07                (0x0006u)   //digital output for dios type B and D
#define YDIOS_OUT_08                (0x0007u)   //digital output for dios type B and D


//object dictionary
#define YDIOS_EMERGENCY_CUTOFF      (0x3208u)     //!< index of the "Emergency Cutoff" object within DIOS' object dictonary
#define YDIOS_CYCLE_TIMER           (0x2200u)     //!< index of the "Cycle Timer" object within DIOS' object dictonary
#define YDIOS_DEVICE_INTERNAL       (0x3206u)     //!< index of the "Device Internal" object within DIOS' object dictonary
#define YDIOS_BITRATE_EE            (0x3201u)     //!< index of the "Bitrate EE" object within the DIOS' object dictonary
#define YDIOS_PWM_FREQUENCY_EE      (0x3202u)     //!< index of the "PWM Frequency EE" object within the DIOS' object dictonary
#define YDIOS_PWM_REGULATION_EE     (0x3203u)     //!< index of the "PWM Regulation EE" object within the DIOS' object dictonary
#define YDIOS_STATUS_REGISTER       (0x1002u)     //!< index of the "Manufacturer Status Register" object within the DIOS' object dictonary
#define YDIOS_CURRENT_VALUES        (0x3401u)     //!< index of the "PWM and current values" object within the DIOS' object dictonary
#define YDIOS_PREOPERA_OUT          (0x3207u)     //!< index of the "Preoperational outputs off" object within the DIOS' object dictonary
#define YDIOS_GUARD_TIME            (0x100Cu)     //!< index of the "Guard Time" object within the DIOS' object dictonary
#define YDIOS_LIFE_TIME_FACTOR      (0x100Du)     //!< index of the "Life Time Factor" object within the DIOS' object dictonary


#define YDIOS_TYPE_A                (0)           //!< 8 x digital input
#define YDIOS_TYPE_B                (1)           //!< 8 x digital output
#define YDIOS_TYPE_C                (2)           //!< 4 x pwm output, 4 x digital input
#define YDIOS_TYPE_D                (3)           //!< 4 x pwm output, 4 x digital output

//send modes
#define YDIOS_SEND_MODE_ON_CHANGE  (0x01)  //send when value(s) change(s)
#define YDIOS_SEND_MODE_CYCLICALLY (0x02)  //send cyclically

/* -- Types --------------------------------------------------------------- */

/*! \brief  DIOS' configuration. */
typedef struct
{
   void *       pv_COL2BusHandle;        //!< handle to instance of COL2 (as returned by col2_init)
   uint8        u8_NodeID;               //!< DIOS' node ID
   uint8        u8_DIOSType;             //!< Model type of the DIOS
   uint8        au8_PWMOutReg[4];        //!< Current Controlled PWM (1) / Standard PWM (0)

   uint8        u8_PWMOutSendMode;       //!< bit coded: YDIOS_SEND_MODE_ON_CHANGE; YDIOS_SEND_MODE_CYCLICALLY
   uint16       u16_PWMOutMinIntervalMS; //!< minimum interval to keep between PWM PDOs (used with YDIOS_SEND_MODE_ON_CHANGE)
   uint16       u16_PWMOutMaxIntervalMS; //!< maximum interval to keep between PWM PDOs (used with YDIOS_SEND_MODE_CYCLICALLY)
   uint16       au16_PWMHysteresis[4];   //!< Maximal tolerated PWM jitter (without re-sending the modified values)

   uint8        u8_DigOutSendMode;       //!< bit coded: YDIOS_SEND_MODE_ON_CHANGE; YDIOS_SEND_MODE_CYCLICALLY
   uint16       u16_DigOutMinIntervalMS; //!< minimum interval to keep between DOUT PDOs (used with YDIOS_SEND_MODE_ON_CHANGE)
   uint16       u16_DigOutMaxIntervalMS; //!< maximum interval to keep between DOUT PDOs (used with YDIOS_SEND_MODE_CYCLICALLY)
} T_ydios_config;

/*! \brief  DIOS' internal data. */
typedef struct
{
   uint8 u8_Temp;                            //!< DIOS' internal temperature
   uint8 u8_Ub;                              //!< Supply voltage (batterie)
   uint8 u8_Uc;                              //!< Supply voltage
   uint8 u8_Itot;                            //!< Total current
} T_ydios_internals;


/*! \brief Data structure representing a DIOS. */
//This structure is defined in the header, so that the required memory can be instances by the application.
//Note: that does not mean that the application can rely on any of the data contained therein !
//      Always use the ydios_... functions to interface with the library functionality.
typedef struct
{
   uint8                u8_Operational;         //!< 1 if node is in state OPERATIONAL
   T_ydios_config       t_Config;               //!< the DIOS' configuration
   uint8                u8_DigitalIn;           //!< the last received digital input values
   uint32               u32_NextDigTxMinTime;   //!< the timestamp the digital output values shall be sent if changed
   uint32               u32_NextDigTxMaxTime;   //!< the timestamp the digital output values shall be sent unconditional

   uint16               au16_PwmOut[4];         //!< the current pwm output values to transmit (0 .. 4000 / 0 .. 10000)
   uint16               au16_PrevPwmOut[4];     //!< the last transmitted pwm output values
   uint32               u32_NextPwmTxMinTime;   //!< the timestamp the pwm output values shall be sent if changed
   uint32               u32_NextPwmTxMaxTime;   //!< the timestamp the pwm output values shall be sent unconditional
   uint16               au16_PwmLowThreshold[4];
   uint16               au16_PwmHighThreshold[4];

   void *               pv_PDOHandle;           //!< a handle to the CANopen Layer 2 project data objects relevant for DIOS

   uint8  u8_SDOWriteConditionalState;
   uint8  u8_BusOffDetectionState;

   uint8 u8_DigOutData;
   uint8 u8_LastDigOutData;
} T_ydios_status;


/* -- Global Variables ---------------------------------------------------- */


/* -- Function Prototypes ------------------------------------------------- */
extern sint16 ydios_task(void);
extern sint16 ydios_init(const T_ydios_config * const opt_Config, void ** const oppv_Handle);
extern sint16 ydios_close(void);

//network management NMT
extern sint16 ydios_start(void * const opv_Handle);
extern sint16 ydios_reset(void * const opv_Handle);
extern sint16 ydios_stop(void * const opv_Handle);

//input / output
extern sint16 ydios_in_get_value(void * const opv_Handle, const uint8 ou8_Channel, uint16 * const opu16_Value);
extern sint16 ydios_out_set_value(void * const opv_Handle, const uint8 ou8_Channel, const uint16 ou16_Value);

//sdo transfers
extern sint16 ydios_out_get_current(void * const opv_Handle, const uint8 ou8_Channel,
                                    uint16 * const opu16_Value);
extern sint16 ydios_emergency_stop(void * const opv_Handle);
extern sint16 ydios_set_cyclic_transmission(void * const opv_Handle, const uint16 ou16_CycleTime);
extern sint16 ydios_get_internals(void * const opv_Handle, T_ydios_internals * const opt_Internals);
extern sint16 ydios_set_can_bitrate(void * const opv_Handle, const uint16 ou16_Bitrate);
extern sint16 ydios_set_pwm_frequency(void * const opv_Handle, const uint8 ou8_Frequency);
extern sint16 ydios_set_ccp_multiplier(void * const opv_Handle, const uint8 ou8_Channel, const uint8 ou8_Value);
extern sint16 ydios_set_ccp_time_factor(void * const opv_Handle, const uint8 ou8_Value);
extern sint16 ydios_get_diagnostic_data(void * const opv_Handle, uint8 * const opu8_Data);

extern sint16 ydios_set_preop_outputs(void * const opv_Handle, const uint8 ou8_Channels);
extern sint16 ydios_set_guarding_parameters(void * const opv_Handle, const uint16 ou16_GuardTime,
                                            const uint8 ou8_LifeTimeFactor);

//library info
extern uint16 ydios_library_get_version(void);

/* -- Implementation ------------------------------------------------------ */



#endif
