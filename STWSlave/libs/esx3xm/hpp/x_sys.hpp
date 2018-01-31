//-----------------------------------------------------------------------------
/*!
   \file        x_sys.hpp
   \brief       CPP namespace extention for x_sys.h

   This header was automatically created. DO NOT EDIT!

   \implementation
   copyright   STW (c) 1999-20xx
   license     use only under terms of contract / confidential

   created     by hpp_generator.pl
   \endimplementation


   \internal
   \history
   Date(dd.mm.yyyy)  Author                Description
   \endhistory
*/
//-----------------------------------------------------------------------------

#ifndef __X_SYS_HPP
#define __X_SYS_HPP



/* -- Types --------------------------------------------------------------- */

typedef struct
{
   stw_types::uint16 u16_Type;              // type information
   stw_types::uint16 u16_Version;           // version information
} T_x_sys_info;

typedef struct
{
   stw_types::uint16 u16_ExpBoardId;        // expansion board type identification
   stw_types::uint16 u16_ArticleVersion;    // expansion board STW article version (hardware revision)
   stw_types::uint32 u32_ArticleNumber;     // expansion board STW article number (variant number)
   stw_types::uint16 u16_SwInterface;       // expansion board software interface
   stw_types::charn  acn_SerialNumber[14];  // expansion board serial number (zero terminated string)
} T_x_sys_expboard_info;

typedef struct                   // information about last CPU trap
{
   stw_types::uint16   u16_Class;           // trap class
   stw_types::uint16   u16_Id;              // trap ID
   stw_types::uint32   u32_Address;         // address where this trap occurred (NULL = no trap)
} T_x_sys_trap;

typedef struct
{
   stw_types::uint8  au8_SerialNumber[6];            // STW serial number BCD coded
   stw_types::uint32 u32_ArticleNumber;              // STW article number
   stw_types::charn  acn_DeviceID[17];               // name of ECU, max. 16 characters + zero-termination
   stw_types::uint8  au8_CommissioningDate[3];       // date of first commissioning BCD: dd.mm.yy
   stw_types::uint8  au8_LastTestDate[3];            // date of last ECU test BCD: dd.mm.yy
   stw_types::charn  acn_CompanyID[6];               // company ID, max. 5 characters + zero-termination
   stw_types::charn  acn_ArticleVersion[17];         // STW article version, max. 16 characters + zero-termination
   stw_types::charn  acn_InternalSerialNumber[11];   // internal serial number, max. 10 characters + zero-termination
} T_x_sys_logistic_data;


typedef struct
{
   stw_types::uint16 u16_Line;                                   // instruction line, where the error happened
   stw_types::sint16 s16_Error;                                  // error that the instruction returned
} T_x_sys_init_err;


typedef struct
{
   T_x_sys_info            t_MainboardInfo;           // main board type and version information
   T_x_sys_info            t_CpuInfo;                 // CPU type and version information
   T_x_sys_info            t_SupervisorInfo;          // system supervisor type and version information
   T_x_sys_expboard_info   at_ExpBoardInfo[6];        // expansion board information
   T_x_sys_logistic_data   t_LogisticData;            // logistic data (usually from System EEPROM)
   stw_types::uint16                  u16_CpuFreq;               // CPU clock frequency in MHz
   stw_types::uint16                  u16_SysFreq;               // system (peripheral) clock frequency in MHz
   stw_types::uint32                  u32_RamSize;               // RAM size in kbyte (external RAM)
   stw_types::uint32                  u32_RomSize;               // ROM size in kbyte (external ROM)
   stw_types::uint32                  u32_EepromSize;            // EEPROM size in byte
   stw_types::uint32                  u32_HeapSize;              // heap size in byte
   stw_types::uint32                  u32_HeapSizeInternal;      // internal heap size in byte
   stw_types::uint32                  u32_LastReset;             // cause of last reset
   T_x_sys_trap            t_LastTrap;                // info: last trap, not handled by application
   T_x_sys_init_err        t_InitErr;                 // detailed error number set in case of a x_sys_init error
} T_x_sys_system_information;


/* -- Types --------------------------------------------------------------- */

typedef void (*PR_x_sys_OffReactionCallback)(const stw_types::uint32 ou32_CallbackParameter);


/* -- Function Prototypes ------------------------------------------------- */

stw_types::sint16 x_sys_init(T_x_sys_system_information* const opt_SysInfo);                         // ECU init
stw_types::sint16 x_sys_get_system_information(T_x_sys_system_information * const opt_SysInfo);      // read system information
stw_types::sint16 x_sys_get_component_info(const stw_types::uint16 ou16_Component, T_x_sys_info * const opt_Info);   // get system component type/version information

stw_types::sint16 x_sys_init_off_reaction(const stw_types::uint32 ou32_CallbackParameter, const PR_x_sys_OffReactionCallback opr_OffCallback);   // callback interrupt on ignition signal off

stw_types::sint16 x_sys_close(void);                                                                 // shut down ECU
void   x_sys_reset(void);                                                                 // system reset initiated by TriCore CPU
stw_types::sint16 x_sys_trigger_cpu_watchdog(const stw_types::uint16 ou16_WDTimeout);                           // reload cpu internal watchdog with timeout value in ms
stw_types::uint32 x_sys_enter_critical(void) ALIAS(x_os_enter_critical);                             // lock all interrupt levels potentially used by application code
void   x_sys_leave_critical(const stw_types::uint32 ou32_PreviousState) ALIAS(x_os_leave_critical);  // unlock all interrupt levels potentially used by application code

stw_types::sint16 x_sys_get_ignition(stw_types::uint8* const opu8_OnOff);                                       // read ignition signal
stw_types::sint16 x_sys_stay_alive(const stw_types::uint8 ou8_OnOff);                                           // set / clear power hold signal
stw_types::sint16 x_sys_set_relay(const stw_types::uint16 ou16_Channel, const stw_types::uint8 ou8_OnOff);                 // set main relay 0..2 ON/OFF
stw_types::sint16 x_sys_set_all_relays(const stw_types::uint8 ou8_OnOff);                                       // set all main relays ON/OFF
stw_types::sint16 x_sys_set_beeper(const stw_types::uint32 ou32_Frequency);                                     // set ECU beeper frequency
stw_types::sint16 x_sys_set_led(const stw_types::uint16 ou16_Channel, const stw_types::uint8 ou8_OnOff, const stw_types::uint16 ou16_Color);   // set ECU user LEDs
stw_types::sint16 x_sys_set_sensor_supply(const stw_types::uint16 ou16_Channel, const stw_types::sint32 os32_Voltage);              // set ext. sensor supply in mV
stw_types::sint16 x_sys_get_temperature(const stw_types::uint16 ou16_Channel, stw_types::sint16* const ops16_Value);       // read board or CPU temperature in x10 degree Celsius

stw_types::sint16 x_sys_get_adc_raw_value(const stw_types::uint16 ou16_Channel, stw_types::uint16* const opu16_Value);     // read raw ADC value (not filtered) from channel ou16_Channel
stw_types::sint16 x_sys_get_adc_raw_value_scaled(const stw_types::uint16 ou16_Channel, stw_types::sint32* const ops32_Value); // read raw scaled ADC value (not filtered) from channel ou16_Channel
stw_types::sint16 x_sys_get_adc_value(const stw_types::uint16 ou16_Channel, stw_types::uint16* const opu16_Value);         // read ADC value from channel ou16_Channel
stw_types::sint16 x_sys_get_adc_value_scaled(const stw_types::uint16 ou16_Channel, stw_types::sint32* const ops32_Value);  // read scaled ADC value from channel ou16_Channel
stw_types::sint16 x_sys_set_adc_filter(const stw_types::uint16 ou16_Channel, const stw_types::uint16 ou16_Filter );        // set ADC channel filter behavior
stw_types::sint16 x_sys_get_adc_filter(const stw_types::uint16 ou16_Channel, stw_types::uint16* const opu16_Filter);       // get ADC channel filter configuration

stw_types::uint32 x_sys_get_time_ms(void);                                                           // read system time in milli seconds
stw_types::uint64 x_sys_get_time_us(void);                                                           // read system time in micro seconds
void   x_sys_delay_us(const stw_types::uint32 ou32_Delay_us);                                        // delay in micro seconds
stw_types::uint64 x_sys_get_timer(void);                                                             // read 56bit system timer (resolution 26.67ns)


#endif  // __X_SYS_HPP
