//-----------------------------------------------------------------------------
/*!
   \internal
   \file       main.c
   \brief      empty project for ESX3XM

   - initialize the ESX-3XM hardware with x_sys_init

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   created     14.12.2007  STW/CB
   \endimplementation
*/
//-----------------------------------------------------------------------------


 /* -- Includes ------------------------------------------------------------ */
#include "AppConfig.h"

/* -- Defines ------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */
uint32 *sysCycleTime;
uint32 *sysControlWord;
uint8 *sysStatus;
uint32 *sysCPUTemperatur;
uint32 *sysCPUVoltageUb1;
uint32 *sysCPUCurrentUb1;
uint32 *sysCPUVoltageExt;
uint32 *sysCPUVoltageUC1;

//system date time
uint8 *sysDateTimeSec;
uint8 *sysDateTimeMin;
uint8 *sysDateTimeHour;
uint8 *sysDateTimeDay;
uint8 *sysDateTimeMonth;
uint16 *sysDateTimeYear;

T_x_sys_system_information tSys;


/***************************************************************************
 * This struct with the Application information is not used within the
 * Software. It will be placed in a special memory region (defined by
 * X_MEM_APPLICATION_INFO).
 * The information contained in this struct can be read by STW flash tools
 * (like e.g. Winflash) to determine the type of software that has been
 * flashed to the ECU.
 * Note:
 * There can only be one application information block defined.
 ***************************************************************************/
const T_x_lib_info gt_AppInfo X_MEM_APPLICATION_INFO =
{
  X_LIB_INFO_APPL_MAGIC,                        // Magic key (signaling a valid Application Info Block) (do not edit!)
  X_LIB_INFO_STRUCT_VERSION,                    // Version information of the info struct               (do not edit!)
  X_LIB_INFO_CONTAINS_DEVICE_ID       |         // Bit - coded content Map;
  X_LIB_INFO_CONTAINS_DATE_TIME       |         // -> remove bit from content Map and the content itself
  X_LIB_INFO_CONTAINS_PROJECT_NAME    |
  X_LIB_INFO_CONTAINS_PROJECT_VERSION |
  X_LIB_INFO_CONTAINS_ADDITIONAL_INFO,
  X_LIB_INFO_DEVICE_ID,                         // ECU device ID  ; masked by X_LIB_INFO_CONTAINS_DEVICE_ID
  __DATE__,                                     // current date   ; masked by X_LIB_INFO_CONTAINS_DATE_TIME
  __TIME__,                                     // current time   ; masked by X_LIB_INFO_CONTAINS_DATE_TIME
  "3xm_empty",                                  // project name   ; masked by X_LIB_INFO_CONTAINS_PROJECT_NAME
  "V1_23r4",                                    // project version; masked by X_LIB_INFO_CONTAINS_PROJECT_VERSION
  X_LIB_INFO_CONTAINS_ADDITIONAL_MAX,           // size of additional Info (max. 0xFF); masked by X_LIB_INFO_CONTAINS_ADDITIONAL_INFO
  "Additional info of \"3xm_empty\"."           // Additional Info (max. 255 chars)   ; masked by X_LIB_INFO_CONTAINS_ADDITIONAL_INFO
};


/* -- Module Global Function Prototypes ----------------------------------- */

/* -- Module Global Function Prototypes ----------------------------------- */
void InitSys(void){
   sint16 s16_Error;

   s16_Error  = x_sys_init(&tSys);        // init ESX3XL hardware
   s16_Error |= x02_sys_init();           // init expansion board hardware of type EB02
   s16_Error |= x05_sys_init();           // init expansion board hardware of type EB05

   if (s16_Error == C_NO_ERR)             // system init OK?
   {
      // setup system...
      x_sys_stay_alive(X_ON);             // set power hold signal
      x_sys_set_all_relays(X_ON);
   }


   x_sys_delay_us(1000000);
}
/* -- Implementation ------------------------------------------------------ */

//-----------------------------------------------------------------------------
/*!
   \brief   Initializes the ESX-3XM hardware with x_sys_init
*/
//-----------------------------------------------------------------------------
int main(void)
{
   uint8  u8_Ignition;
   uint32 timeStamp_us;
   uint32 timeStamp_ms;
   uint16 u16_Temp;
   sint32 s32_Temp;
   float32 f32_Temp;
   uint16 Addr;
   uint32 VersionNum;
   InitSys();

   // init Os
   x_os_init(X_OS_HEAP_DEFAULT);

   InitTaskCommInterface();
   InitDriveSys();
   InitSafety();
   InitMultiIO();
   InitRemoteControl();
   InitAutoDrive();

   sysCycleTime=BindODMem(DevParaStartIndex,SubindexSysCycleTime,TypeU32,0); *sysCycleTime=0;
   sysStatus=BindODMem(DevParaStartIndex,SubindexSysStatus,TypeU8,0); *sysStatus=0x00;
   sysCPUTemperatur=BindODMem(DevParaStartIndex,SubindexCPUTemperatur,TypeU32,0); *sysCPUTemperatur=0;
   sysCPUVoltageUb1=BindODMem(DevParaStartIndex,SubindexCPUVoltageUb1,TypeU32,0); *sysCPUVoltageUb1=0;
   sysCPUCurrentUb1=BindODMem(DevParaStartIndex,SubindexCPUCurrentUb1,TypeU32,0); *sysCPUCurrentUb1=0;
   sysCPUVoltageExt=BindODMem(DevParaStartIndex,SubindexCPUVoltageExt,TypeU32,0); *sysCPUVoltageExt=0;
   sysCPUVoltageUC1=BindODMem(DevParaStartIndex,SubindexCPUVoltageUC1,TypeU32,0); *sysCPUVoltageUC1=0;
   sysControlWord=BindODMem(DevParaStartIndex,SubindexControlWord,TypeU32,0); *sysControlWord=0;

   sysDateTimeSec=BindODMem(SafetyStartIndex,SubindexSafetyDateTime1,TypeU8,0);
   sysDateTimeMin=BindODMem(SafetyStartIndex,SubindexSafetyDateTime1,TypeU8,1);
   sysDateTimeHour=BindODMem(SafetyStartIndex,SubindexSafetyDateTime1,TypeU8,2);
   sysDateTimeDay=BindODMem(SafetyStartIndex,SubindexSafetyDateTime1,TypeU8,3);
   sysDateTimeMonth=BindODMem(SafetyStartIndex,SubindexSafetyDateTime2,TypeU8,0);
   sysDateTimeYear=BindODMem(SafetyStartIndex,SubindexSafetyDateTime2,TypeU16,1);

    VersionNum=NodeHWVersion;
    GetSetOD(DevParaStartIndex,SubindexHwtype,&Addr,&VersionNum,SetOD);
    VersionNum=NodeSerialNummer;
    GetSetOD(DevParaStartIndex,SubindexSerNr,&Addr,&VersionNum,SetOD);

   x_os_start(200);
   timeStamp_ms=x_sys_get_time_ms();

   while (TRUE)                  // main loop...
   {
      timeStamp_us=(uint32)(x_sys_get_time_us());

      x_sys_get_ignition(&u8_Ignition);     // read D+ signal

      if (u8_Ignition!=0x01)             // no D+ signal?
      {
         // clean up...
         *sysStatus&=~0x01;
         x_sys_delay_us(3000000);        // delay 3 sec
         x_sys_close();                  // shut down system ...
      }
      else
         *sysStatus|=0x01;

      if(*sysControlWord&0x00000004){
         *sysControlWord&=~0x00000004;
         x_sys_delay_us(500000);
         x_sys_close();
      }

      TaskCommInterface();
      TaskRemoteControlAwake();
      TaskDriveSysAwake();

      //Get System Status
      x_sys_get_temperature(X_SYS_TEMP_CPU,&u16_Temp); *sysCPUTemperatur=(uint32)u16_Temp*100;
      x_sys_get_adc_value_scaled(X_ADC_U_UB1,&s32_Temp);  *sysCPUVoltageUb1=(uint32)s32_Temp;
      x_sys_get_adc_value_scaled(X_ADC_I_UB1,&s32_Temp);  *sysCPUCurrentUb1=(uint32)s32_Temp/1000;
      x_sys_get_adc_value_scaled(X_ADC_U_EXT1,&s32_Temp); *sysCPUVoltageExt=(uint32)s32_Temp;
      x_sys_get_adc_value_scaled(X_ADC_U_UC1,&s32_Temp); *sysCPUVoltageUC1=(uint32)s32_Temp;

      *sysCycleTime=(uint32)(x_sys_get_time_us())-timeStamp_us;



      //uhr time
      /*if((x_sys_get_time_ms()-timeStamp_ms)>1000){
        *sysDateTimeSec++;
        if(*sysDateTimeSec>=60){
            *sysDateTimeSec=0;
            *sysDateTimeMin++;
        }
        timeStamp_ms=x_sys_get_time_ms();
      }
      *sysDateTimeMonth=12;
      *sysDateTimeYear=2017;*/

      /*us+=*sysCycleTime;
      if(us>1000000){
        us=0;
        *sysDateTimeSec++;

        if(*sysDateTimeMin>=60){
            *sysDateTimeMin=0;
            *sysDateTimeHour++;
        }
        if(*sysDateTimeHour>=24){
            *sysDateTimeHour=0;
            *sysDateTimeDay++;
        }
        if(*sysDateTimeDay>=30){
            *sysDateTimeDay=0;
        }
        *sysDateTimeMonth=12;
        *sysDateTimeYear=2017;
      }*/

   }
}







