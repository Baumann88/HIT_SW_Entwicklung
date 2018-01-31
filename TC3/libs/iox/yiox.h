//-----------------------------------------------------------------------------
/*!
   \file       yiox.h
   \brief      Library for using ESX-IOX (YIOX) modules on top of the COL2
               (CANopen on layer 2) library.

   The following ESX-IOX variants/types are supported:
   \li \c YIOX_TYPE_A (12 x digital input or 12 x voltage input (Variant: 34467))
   \li \c YIOX_TYPE_B (8 x digital input, 4 x PWM HS output (Variant: 34463))
   \li \c YIOX_TYPE_C (4 x digital input or 4 x voltage input, 4 x PWM HS output, 4 x digital output (Variant: 34464))
   \li \c YIOX_TYPE_D (8 x digital output, 4 x PWM LS output (Variant: 34460))

   \implementation
   project     project name
   copyright   STW (c) 1999-20xx
   license     use only under terms of contract / confidential

   created     05.02.2010  STW/S.Dragnef
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author                  Description
   11.01.2011        STW/F.Belser         Remove u8_SelectInputsValue
   25.02.2010        STW/F.Belser         Complete portation to YIOX
   05.02.2010        STW/S.Dragnef        Portation from YDIOS base implementation (rev. 23)
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _YIOX_H
#define _YIOX_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- Includes ------------------------------------------------------------ */
#include "stwtypes.h"

/* -- Defines ------------------------------------------------------------- */
// IOX' digital inputs
#define YIOX_DIN_01                 (0x00u)
#define YIOX_DIN_02                 (0x01u)
#define YIOX_DIN_03                 (0x02u)
#define YIOX_DIN_04                 (0x03u)
#define YIOX_DIN_05                 (0x04u)
#define YIOX_DIN_06                 (0x05u)
#define YIOX_DIN_07                 (0x06u)
#define YIOX_DIN_08                 (0x07u)
#define YIOX_DIN_09                 (0x08u)
#define YIOX_DIN_10                 (0x09u)
#define YIOX_DIN_11                 (0x0Au)
#define YIOX_DIN_12                 (0x0Bu)
#define YIOX_DIN_13                 (0x0Cu)
#define YIOX_DIN_14                 (0x0Du)
#define YIOX_DIN_15                 (0x0Eu)
#define YIOX_DIN_16                 (0x0Fu)
#define YIOX_DIN_17                 (0x10u)
#define YIOX_DIN_18                 (0x11u)
#define YIOX_DIN_19                 (0x12u)
#define YIOX_DIN_20                 (0x13u)
#define YIOX_DIN_21                 (0x14u)
#define YIOX_DIN_22                 (0x15u)
#define YIOX_DIN_23                 (0x16u)
#define YIOX_DIN_24                 (0x17u)
#define YIOX_DIN_25                 (0x18u)
#define YIOX_DIN_26                 (0x19u)
#define YIOX_DIN_27                 (0x1Au)
#define YIOX_DIN_28                 (0x1Bu)

// IOX' current inputs
#define YIOX_IIN_01                 (0x00u)
#define YIOX_IIN_02                 (0x01u)
#define YIOX_IIN_03                 (0x02u)
#define YIOX_IIN_04                 (0x03u)
#define YIOX_IIN_05                 (0x04u)
#define YIOX_IIN_06                 (0x05u)
#define YIOX_IIN_07                 (0x06u)
#define YIOX_IIN_08                 (0x07u)

// IOX' voltage inputs
#define YIOX_UIN_01                 (0x00u)
#define YIOX_UIN_02                 (0x01u)
#define YIOX_UIN_03                 (0x02u)
#define YIOX_UIN_04                 (0x03u)
#define YIOX_UIN_05                 (0x04u)
#define YIOX_UIN_06                 (0x05u)
#define YIOX_UIN_07                 (0x06u)
#define YIOX_UIN_08                 (0x07u)
#define YIOX_UIN_09                 (0x08u)
#define YIOX_UIN_10                 (0x09u)
#define YIOX_UIN_11                 (0x0au)
#define YIOX_UIN_12                 (0x0bu)
#define YIOX_UIN_13                 (0x0cu)
#define YIOX_UIN_14                 (0x0du)
#define YIOX_UIN_15                 (0x0eu)
#define YIOX_UIN_16                 (0x0fu)
#define YIOX_UIN_17                 (0x10u)
#define YIOX_UIN_18                 (0x11u)
// IOX' frequency inputs
#define YIOX_FREQ_IN_27             (0x00u)
#define YIOX_FREQ_IN_28             (0x01u)

// IOX' digital outputs
#define YIOX_DOUT_01                (0x00u)
#define YIOX_DOUT_02                (0x01u)
#define YIOX_DOUT_03                (0x02u)
#define YIOX_DOUT_04                (0x03u)
#define YIOX_DOUT_05                (0x04u)
#define YIOX_DOUT_06                (0x05u)
#define YIOX_DOUT_07                (0x06u)
#define YIOX_DOUT_08                (0x07u)
#define YIOX_DOUT_09                (0x08u)
#define YIOX_DOUT_10                (0x09u)
#define YIOX_DOUT_11                (0x0Au)
#define YIOX_DOUT_12                (0x0Bu)

// IOX' pwm outputs
#define YIOX_PWM_IREG_OUT_01        (0x00u)
#define YIOX_PWM_IREG_OUT_02        (0x01u)
#define YIOX_PWM_IREG_OUT_03        (0x02u)
#define YIOX_PWM_IREG_OUT_04        (0x03u)

// IOX' pwm output frequency
#define YIOX_PWM_OUT_FREQUENCY_1_2  (0x01u)
#define YIOX_PWM_OUT_FREQUENCY_3_4  (0x02u)

// IOX'  10 volt voltage output
#define YIOX_VOLTAGE_OUTPUT         (0x00u)

// Object dictionary
#define YIOX_DIGITAL_INPUTS_THRESHOLDS       (0x2000u)  //!< index of the "Digital input threshold" object within the IOX 'object dictionary'
#define YIOX_PIN_CONFIG                      (0x2001u)  //!< index of the "Pin configuration" object within the IOX 'object dictionary'
#define YIOX_PWM_FREQUENCY                   (0x2020u)  //!< index of the "PWM frequnecy out" object within the IOX 'object dictionary'
#define YIOX_DIGITAL_INPUTS_PULLUPS          (0x2030u)  //!< index of the "Digital inputs pullups" object within the IOX 'object dictionary'
#define YIOX_ENCODER_CONFIG                  (0x2035u)  //!< index of the "Encoder config" object within the IOX 'object dictionary'
#define YIOX_PWM_OUT_PID_TIME                (0x4000u)  //!< index of the "PWM output pid" object within the IOX 'object dictionary'
#define YIOX_PWM_OUT_PID_P_VALUE             (0x4001u)  //!< index of the "PWM output pid p value" object within the IOX 'object dictionary'
#define YIOX_PWM_OUT_PID_I_VALUE             (0x4002u)  //!< index of the "PWM output pid i value" object within the IOX 'object dictionary'
#define YIOX_PWM_OUT_PID_D_VALUE             (0x4003u)  //!< index of the "PWM output pid d value" object within the IOX 'object dictionary'

// IOX variant
#define YIOX_TYPE_A                (0)  //!< 12 x digital input or 12 x voltage input (Variant: 34467)
#define YIOX_TYPE_B                (1)  //!< 8 x digital input, 4 x PWM HS output (Variant: 34463)
#define YIOX_TYPE_C                (2)  //!< 4 x digital input or 4 x voltage input, 4 x PWM HS output, 4 x digital output (Variant: 34464)
#define YIOX_TYPE_D                (3)  //!< 8 x digital output, 4 x PWM LS output (Variant: 34460)

// Send modes
#define YIOX_SEND_MODE_ON_CHANGE   (0x01u)  //send when value(s) change(s)
#define YIOX_SEND_MODE_CYCLICALLY  (0x02u)  //send cyclically

//max input definitions for the different iox types
#define YIOX_MAX_NUM_OF_DIG_INPUTS        (28)  //!< an IOX can have maximal 28 digital inputs
#define YIOX_MAX_NUM_OF_CUR_INPUTS        (8)   //!< an IOX can have maximal 8 current inputs
#define YIOX_MAX_NUM_OF_VOL_INPUTS        (18)  //!< an IOX can have maximal 18 voltage inputs
#define YIOX_MAX_NUM_OF_FREQ_INPUTS       (2)   //!< an IOX can have maximal 2 freq inputs

//max output definitions for the different iox types
#define YIOX_MAX_NUM_OF_DIG_OUTPUTS       (12)  //!< an IOX can have maximal 8 digital outputs
#define YIOX_MAX_NUM_OF_PWM_OUTPUTS       (4)   //!< an IOX can have maximal 4 pwm outputs

// Maximal number of pins
#define YIOX_MAX_NUM_OF_PINS              (42)  //!< an IOX has 42 pins
// Maximal number of TPDOs
#define YIOX_MAX_NUM_OF_TPDOS             (10)

// IOX Pin Configuration
#define YIOX_SYSTEM_PIN                   (0x00u)  //!< possible pin configurations
#define YIOX_SELECT_INPUT                 (0x01u)  //!< for yiox_set_pin_configuration
#define YIOX_ANALOGUE_INPUT               (0x02u)
#define YIOX_DIGITAL_INPUT                (0x04u)
#define YIOX_PWM_OUTPUT                   (0x08u)
#define YIOX_DIGITAL_OUTPUT               (0x10u)
#define YIOX_CURRENT_REG_OUTPUT           (0x20u)
#define YIOX_RPM_INPUT                    (0x40u)
#define YIOX_ENCODER_INPUT                (0x80u)


/* -- Types --------------------------------------------------------------- */
/*! \brief  IOX' configuration. */
typedef struct
{
   void * pv_COL2BusHandle;                    //!< handle to instance of COL2 (as returned by col2_init)
   uint8  u8_NodeID;                           //!< IOX' node ID which includes the Base_ID + CodingInputs
                                               //!< For further informations please refer to the HW part
                                               //!< of the ESX-IOX_CANopen manual, chapter Getting Started
   uint8  u8_IOXType;                          //!< Model type of the IOX
   uint32 au32_TPDOIDs[YIOX_MAX_NUM_OF_TPDOS]; //!< IDs of every single TPDO without NodeId
                                               //!< for example : TPD01 = 0x180
                                               //!<               TPD02 = 0x280
                                               //!<               TPD03 = 0x380
                                               //!<               TPD04 = 0x480
                                               //!< not used TPDOs must be set to 0x80000000 !!!!!
   uint8  u8_PWMOutSendMode;                   //!< bit coded: YIOX_SEND_MODE_ON_CHANGE; YIOX_SEND_MODE_CYCLICALLY
   uint16 u16_PWMOutMinIntervalMS;             //!< minimum interval to keep between PWM PDOs (used with YIOX_SEND_MODE_ON_CHANGE)
   uint16 u16_PWMOutMaxIntervalMS;             //!< maximum interval to keep between PWM PDOs (used with YIOX_SEND_MODE_CYCLICALLY)

   uint8  u8_DigOutSendMode;                   //!< bit coded: YIOX_SEND_MODE_ON_CHANGE; YIOX_SEND_MODE_CYCLICALLY
   uint16 u16_DigOutMinIntervalMS;             //!< minimum interval to keep between DOUT PDOs (used with YIOX_SEND_MODE_ON_CHANGE)
   uint16 u16_DigOutMaxIntervalMS;             //!< maximum interval to keep between DOUT PDOs (used with YIOX_SEND_MODE_CYCLICALLY)
} T_yiox_config;

/*! \brief Data structure representing a IOX. */
//This structure is defined in the header, so that the required memory can be instanced by the application.
//Note: that does not mean that the application can rely on any of the data contained therein !
//      Always use the yiox_... functions to interface with the library functionality.
typedef struct
{
   T_yiox_config t_Config;                                           //!< the IOX configuration
   uint8         u8_Operational;                                     //!< operational state of the node
   void *        apv_PDOHandle[YIOX_MAX_NUM_OF_TPDOS];               //!< TPDO handles array for the IOX

   uint32        u32_DIN_Status;                                     //!< actual status of the digital inputs

   sint16        as16_CurrentInputs[YIOX_MAX_NUM_OF_CUR_INPUTS];     //!< actual value of the current inputs 1 - 8
   sint16        as16_VoltageInputs[YIOX_MAX_NUM_OF_VOL_INPUTS];     //!< actual value of the voltage inputs 1 - 8
   sint16        as16_FreqInputs[YIOX_MAX_NUM_OF_FREQ_INPUTS];       //!< actual value of the freq inputs 1 - 8

   uint8         u8_10VoltOutput;                                    //!< actual value of the 10 volt output
   uint8         u8_10VoltOutput_Old;                                //!< last value of the 10 volt output

   uint16        u16_DOUT_Values;                                    //!< actual values of the digital outputs
   uint16        u16_DOUT_Values_Old;                                //!< last values of the digital outputs

   sint16        as16_PWMOut_values[YIOX_MAX_NUM_OF_PWM_OUTPUTS];    //!< actual values of the PWM output values
   sint16        as16_PWMOut_values_Old[YIOX_MAX_NUM_OF_PWM_OUTPUTS];//!< last values of the PWM output values

   uint32        u32_NextDigTxMinTime;                               //!< the timestamp the digital output values shall be sent if changed
   uint32        u32_NextDigTxMaxTime;                               //!< the timestamp the digital output values shall be sent unconditional
   uint32        u32_NextPwmTxMinTime;                               //!< the timestamp the PWM output values shall be sent if changed
   uint32        u32_NextPwmTxMaxTime;                               //!< the timestamp the PWM output values shall be sent unconditional
} T_yiox_status;

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint16 yiox_task(void);
extern sint16 yiox_init(const T_yiox_config * const opt_Config, void ** const oppv_Handle);
extern sint16 yiox_close(void);

// Network Management NMT
extern sint16 yiox_start(void * const opv_Handle);
extern sint16 yiox_reset(void * const opv_Handle);
extern sint16 yiox_stop(void * const opv_Handle);
extern sint16 yiox_preop(void * const opv_Handle);

// SDO transfers
extern sint16 yiox_set_pin_configuration(void * const opv_Handle, const uint8 ou8_Channel,
                                         const uint8 ou8_PinConfiguration);
extern sint16 yiox_set_din_threshold_configuration(void * const opv_Handle, const uint8 ou8_Channel,
                                                   const uint16 ou16_LowerThresholdValue,
                                                   const uint16 ou16_UpperThresholdValue);
extern sint16 yiox_set_preset_encoder_value(void * const opv_Handle, const sint16 os16_PresetEncValue);
extern sint16 yiox_set_pwm_output_frequency(void * const opv_Handle, const uint8 ou8_Channel,
                                            const uint16 ou16_PwmOutputFrequency);
extern sint16 yiox_set_pwm_sample_time(void * const opv_Handle, const uint8 ou8_PwmSampleTime);
extern sint16 yiox_set_pwm_pid_value(void * const opv_Handle,const uint8 ou8_Channel, const uint8 ou8_WhichPidValue,
                                     const uint16 ou16_PwmPidValue);
extern sint16 yiox_set_din_pullups_configuration(void * const opv_Handle, const uint8 ou8_ChannelRange,
                                                 const uint8 ou8_PullupConfiguration);

// input functions
// ---------------- single vlaues
extern sint16 yiox_in_get_digital_value(void * const opv_Handle, const uint8 ou8_Channel, uint8 * const opu8_Value);
extern sint16 yiox_in_get_current_value(void * const opv_Handle, const uint8 ou8_Channel, sint16 * const ops16_Value);
extern sint16 yiox_in_get_voltage_value(void * const opv_Handle, const uint8 ou8_Channel, sint16 * const ops16_Value);
extern sint16 yiox_in_get_frequency_value(void * const opv_Handle, const uint8 ou8_Channel, sint16 * const ops16_Value);
// ---------------- all values
extern sint16 yiox_in_get_digital_values_all(void * const opv_Handle, uint32 * const opu32_Value);

// output functions
// ---------------- single values
extern sint16 yiox_out_set_voltage_value(void * const opv_Handle, const uint8 ou8_Channel, const uint8 ou8_Value);
extern sint16 yiox_out_set_digital_value(void * const opv_Handle, const uint8 ou8_Channel, const uint8 ou8_Value);
extern sint16 yiox_out_set_pwm_value(void * const opv_Handle, const uint8 ou8_Channel, const sint16 os16_Value);
// ---------------- all values
extern sint16 yiox_out_set_digital_values_all(void * const opv_Handle, const uint16 ou16_Value);
// Library version
extern uint16 yiox_library_get_version(void);

/* -- Implementation ------------------------------------------------------ */

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif   //_YIOX_H
