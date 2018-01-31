//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_sys.h
   \brief      system functions

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     01.02.2006  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_SYS_H
#define _X_SYS_H

/* -- Includes ------------------------------------------------------------ */

#include "x_stdtypes.h"
#include "x_sys_adc.h"


#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************
 * compiler check will be inserted here in post build step
 * do not edit!
 **********************************************************/
#if ((__GNUC__ != 3) || (__GNUC_MINOR__ != 4) || (__GNUC_PATCHLEVEL__ != 5))
 #error This Library should only be used with TRICORE GCC Compiler version 3.4.5
#endif


/***************************************************************************
 * temporary MISRA deviations:
 *
 * message 0341 off: GCC supports the stringify operator
 *                   (used by ALIAS macro)
 * message 2217 off: allow more than 120 characters for better readability
 ***************************************************************************/

// PRQA S 0341,2217 ++


/* -- Defines ------------------------------------------------------------- */

#define X_SYS_RELAY_CH_MAX       (1u)              // sys define: max. number of power relay channels
#define X_SYS_RELAY_01           (0u)              // sys define: main power relay 1

#define X_SYS_SENSOR_SUPPLY_CH_MAX (1u)            // sys define: max. number of sensor supply channels
#define X_SYS_SENSOR_SUPPLY_01   (0u)              // sys define: sensor supply output 1

#define X_SYS_LED_CH_MAX         (1u)              // sys define: max. number of user LED channels
#define X_SYS_LED_01             (0u)              // sys define: left user LED
#define X_SYS_LED_COLOR_RED      (0u)              // sys define: LED color = pure red
#define X_SYS_LED_COLOR_ORANGE   (35u)             // sys define: LED color = orange
#define X_SYS_LED_COLOR_YELLOW   (70u)             // sys define: LED color = yellow
#define X_SYS_LED_COLOR_GREEN    (100u)            // sys define: LED color = pure green

#define X_SYS_TEMP_CH_MAX        (2u)              // sys define: max. number of temperature channels
#define X_SYS_TEMP_BOARD         (0u)              // sys define: get board temperature
#define X_SYS_TEMP_CPU           (1u)              // sys define: get CPU temperature

#define X_SYS_CPUWD_OFF          (0xF0A5u)         // sys define: disable internal watchdog

// defines for t_MainboardInfo.u16_Version information
#define X_SYS_HW_VERSION_A       0x0000            // 3XM A-step hardware
#define X_SYS_HW_VERSION_C       0x0001            // 3XM C-step hardware
#define X_SYS_HW_VERSION_C2      0x0002            // 3XM C2-step hardware

#define X_SYS_COMPONENT_LIBRARY        (0)         // API Version
#define X_SYS_COMPONENT_FLASH_LOADER   (1)         // FLASH LOADER Version
#define X_SYS_COMPONENT_EEPROM_MAPPING (2)         // EEPROM Mapping Version
#define X_SYS_COMPONENT_SSV            (3)         // SSV Version
#define X_SYS_COMPONENT_SSV_PROGRAM    (4)         // SSV Program Version (since SSV Version v2.07r0)
#define X_SYS_COMPONENT_EXT_FLASH_BOOT (5)         // Extern Flash Bootsector Version
#define X_SYS_COMPONENT_MAINBOARD      (6)         // Mainboard HW version
#define X_SYS_COMPONENT_CPU            (7)         // TriCore CPU Version
#define X_SYS_COMPONENT_MAINBOARD_FPGA (8)         // Mainboard FPGA Version
#define X_SYS_COMPONENT_MODULE_FPGA    (9)         // Module FPGA Version
#define X_SYS_COMPONENT_CHANNEL_MAX    (10)


/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/

#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_sys.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */

typedef struct
{
   uint16 u16_Type;              // type information
   uint16 u16_Version;           // version information
} T_x_sys_info;

typedef struct
{
   uint16 u16_ExpBoardId;        // expansion board type identification
   uint16 u16_ArticleVersion;    // expansion board STW article version (hardware revision)
   uint32 u32_ArticleNumber;     // expansion board STW article number (variant number)
   uint16 u16_SwInterface;       // expansion board software interface
   charn  acn_SerialNumber[14];  // expansion board serial number (zero terminated string)
} T_x_sys_expboard_info;

typedef struct                   // information about last CPU trap
{
   uint16   u16_Class;           // trap class
   uint16   u16_Id;              // trap ID
   uint32   u32_Address;         // address where this trap occurred (NULL = no trap)
} T_x_sys_trap;

typedef struct
{
   uint8  au8_SerialNumber[6];            // STW serial number BCD coded
   uint32 u32_ArticleNumber;              // STW article number
   charn  acn_DeviceID[17];               // name of ECU, max. 16 characters + zero-termination
   uint8  au8_CommissioningDate[3];       // date of first commissioning BCD: dd.mm.yy
   uint8  au8_LastTestDate[3];            // date of last ECU test BCD: dd.mm.yy
   charn  acn_CompanyID[6];               // company ID, max. 5 characters + zero-termination
   charn  acn_ArticleVersion[17];         // STW article version, max. 16 characters + zero-termination
   charn  acn_InternalSerialNumber[11];   // internal serial number, max. 10 characters + zero-termination
} T_x_sys_logistic_data;


typedef struct
{
   uint16 u16_Line;                                   // instruction line, where the error happened
   sint16 s16_Error;                                  // error that the instruction returned
} T_x_sys_init_err;


typedef struct
{
   T_x_sys_info            t_MainboardInfo;           // main board type and version information
   T_x_sys_info            t_CpuInfo;                 // CPU type and version information
   T_x_sys_info            t_SupervisorInfo;          // system supervisor type and version information
   T_x_sys_expboard_info   at_ExpBoardInfo[6];        // expansion board information
   T_x_sys_logistic_data   t_LogisticData;            // logistic data (usually from System EEPROM)
   uint16                  u16_CpuFreq;               // CPU clock frequency in MHz
   uint16                  u16_SysFreq;               // system (peripheral) clock frequency in MHz
   uint32                  u32_RamSize;               // RAM size in kbyte (external RAM)
   uint32                  u32_RomSize;               // ROM size in kbyte (external ROM)
   uint32                  u32_EepromSize;            // EEPROM size in byte
   uint32                  u32_HeapSize;              // heap size in byte
   uint32                  u32_HeapSizeInternal;      // internal heap size in byte
   uint32                  u32_LastReset;             // cause of last reset
   T_x_sys_trap            t_LastTrap;                // info: last trap, not handled by application
   T_x_sys_init_err        t_InitErr;                 // detailed error number set in case of a x_sys_init error
} T_x_sys_system_information;


/* -- Types --------------------------------------------------------------- */

typedef void (*PR_x_sys_OffReactionCallback)(const uint32 ou32_CallbackParameter);


/* -- Function Prototypes ------------------------------------------------- */

sint16 x_sys_init(T_x_sys_system_information* const opt_SysInfo);                         // ECU init
sint16 x_sys_get_system_information(T_x_sys_system_information * const opt_SysInfo);      // read system information
sint16 x_sys_get_component_info(const uint16 ou16_Component, T_x_sys_info * const opt_Info);   // get system component type/version information

sint16 x_sys_init_off_reaction(const uint32 ou32_CallbackParameter, const PR_x_sys_OffReactionCallback opr_OffCallback);   // callback interrupt on ignition signal off

sint16 x_sys_close(void);                                                                 // shut down ECU
void   x_sys_reset(void);                                                                 // system reset initiated by TriCore CPU
sint16 x_sys_trigger_cpu_watchdog(const uint16 ou16_WDTimeout);                           // reload cpu internal watchdog with timeout value in ms
uint32 x_sys_enter_critical(void) ALIAS(x_os_enter_critical);                             // lock all interrupt levels potentially used by application code
void   x_sys_leave_critical(const uint32 ou32_PreviousState) ALIAS(x_os_leave_critical);  // unlock all interrupt levels potentially used by application code

sint16 x_sys_get_ignition(uint8* const opu8_OnOff);                                       // read ignition signal
sint16 x_sys_stay_alive(const uint8 ou8_OnOff);                                           // set / clear power hold signal
sint16 x_sys_set_relay(const uint16 ou16_Channel, const uint8 ou8_OnOff);                 // set main relay 0..2 ON/OFF
sint16 x_sys_set_all_relays(const uint8 ou8_OnOff);                                       // set all main relays ON/OFF
sint16 x_sys_set_beeper(const uint32 ou32_Frequency);                                     // set ECU beeper frequency
sint16 x_sys_set_led(const uint16 ou16_Channel, const uint8 ou8_OnOff, const uint16 ou16_Color);   // set ECU user LEDs
sint16 x_sys_set_sensor_supply(const uint16 ou16_Channel, const sint32 os32_Voltage);              // set ext. sensor supply in mV
sint16 x_sys_get_temperature(const uint16 ou16_Channel, sint16* const ops16_Value);       // read board or CPU temperature in x10 degree Celsius

sint16 x_sys_get_adc_raw_value(const uint16 ou16_Channel, uint16* const opu16_Value);     // read raw ADC value (not filtered) from channel ou16_Channel
sint16 x_sys_get_adc_raw_value_scaled(const uint16 ou16_Channel, sint32* const ops32_Value); // read raw scaled ADC value (not filtered) from channel ou16_Channel
sint16 x_sys_get_adc_value(const uint16 ou16_Channel, uint16* const opu16_Value);         // read ADC value from channel ou16_Channel
sint16 x_sys_get_adc_value_scaled(const uint16 ou16_Channel, sint32* const ops32_Value);  // read scaled ADC value from channel ou16_Channel
sint16 x_sys_set_adc_filter(const uint16 ou16_Channel, const uint16 ou16_Filter );        // set ADC channel filter behavior
sint16 x_sys_get_adc_filter(const uint16 ou16_Channel, uint16* const opu16_Filter);       // get ADC channel filter configuration

uint32 x_sys_get_time_ms(void);                                                           // read system time in milli seconds
uint64 x_sys_get_time_us(void);                                                           // read system time in micro seconds
void   x_sys_delay_us(const uint32 ou32_Delay_us);                                        // delay in micro seconds
uint64 x_sys_get_timer(void);                                                             // read 56bit system timer (resolution 26.67ns)


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_SYS_H */
