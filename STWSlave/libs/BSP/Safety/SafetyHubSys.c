#include <SafetyData.h>
#include <Safety.h>

//====================================================================
/*!
Function: initial Satety HubSys
Output: None
*/
//====================================================================
void InitSafetyHubSys(void){
    inputSafetyHubSystemWeight=BindODMem(HubSystemStartIndex,SubindexWeight,TypeS32,0); *inputSafetyHubSystemWeight=0;
    inputSafetyHubSystemCGValueX=BindODMem(HubSystemStartIndex,SubindexXValueCG,TypeS32,0); *inputSafetyHubSystemCGValueX=0;
    inputSafetyHubSystemCGValueY=BindODMem(HubSystemStartIndex,SubindexYValueCG,TypeS32,0); *inputSafetyHubSystemCGValueY=0;
    inputSafetyHubSystemHeight11=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel11,TypeU32,0); *inputSafetyHubSystemHeight11=0x00000000;
    inputSafetyHubSystemHeight12=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel12,TypeU32,0); *inputSafetyHubSystemHeight12=0x00000000;
    inputSafetyHubSystemHeight21=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel21,TypeU32,0); *inputSafetyHubSystemHeight21=0x00000000;
    inputSafetyHubSystemHeight22=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel22,TypeU32,0); *inputSafetyHubSystemHeight22=0x00000000;
    inputSafetyHubSystemPressure11=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel11,TypeS32,0); *inputSafetyHubSystemPressure11=0;
    inputSafetyHubSystemPressure12=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel12,TypeS32,0); *inputSafetyHubSystemPressure12=0;
    inputSafetyHubSystemPressure21=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel21,TypeS32,0); *inputSafetyHubSystemPressure21=0;
    inputSafetyHubSystemPressure22=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel22,TypeS32,0); *inputSafetyHubSystemPressure22=0;
    inputSafetyHubSystemPressureMain=BindODMem(HubSystemStartIndex,SubindexPressureSensorPump,TypeS32,0); *inputSafetyHubSystemPressureMain=0;
    inputSafetyHubSystemTemperaturMain=BindODMem(HubSystemStartIndex,SubindexActualTemperature,TypeS32,0); *inputSafetyHubSystemTemperaturMain=0;
    inputSafetyHubSystemPumpeStatusByte=BindODMem(InverterStartIndex,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputSafetyHubSystemPumpeStatusByte=0x00;
    inputSafetyHubSystemPumpeActualSpeed=BindODMem(InverterStartIndex,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputSafetyHubSystemPumpeActualSpeed=0;
    inputSafetyHubSystemSpeedHeight11=BindODMem(HubSystemStartIndex,SubindexHubSpeedAxel11,TypeS32,0); *inputSafetyHubSystemSpeedHeight11=0;
    inputSafetyHubSystemSpeedHeight12=BindODMem(HubSystemStartIndex,SubindexHubSpeedAxel12,TypeS32,0); *inputSafetyHubSystemSpeedHeight12=0;
    inputSafetyHubSystemSpeedHeight21=BindODMem(HubSystemStartIndex,SubindexHubSpeedAxel21,TypeS32,0); *inputSafetyHubSystemSpeedHeight21=0;
    inputSafetyHubSystemSpeedHeight22=BindODMem(HubSystemStartIndex,SubindexHubSpeedAxel22,TypeS32,0); *inputSafetyHubSystemSpeedHeight22=0;
    inputSafetyHubSystemPumpeNodeStatus=BindODMem(InverterStartIndex,SubindexInverterNodeStatus,TypeU8,1); *inputSafetyHubSystemPumpeNodeStatus=0x00;

    outputSafetyHubSystemControlWord=BindODMem(HubSystemStartIndex,SubindexHubSystemControlWord ,TypeU32,0); *outputSafetyHubSystemControlWord=0x00000000;
    outputSafetyHubSystemAxel11HebenPWM=BindODMem(IOPortStartIndex,SubindexOutput01,TypeU16,0); *outputSafetyHubSystemAxel11HebenPWM=0x0000;
    outputSafetyHubSystemAxel11SinkenPWM=BindODMem(IOPortStartIndex,SubindexOutput02,TypeU16,0); *outputSafetyHubSystemAxel11SinkenPWM=0x0000;
    outputSafetyHubSystemAxel12HebenPWM=BindODMem(IOPortStartIndex,SubindexOutput03,TypeU16,0); *outputSafetyHubSystemAxel12HebenPWM=0x0000;
    outputSafetyHubSystemAxel12SinkenPWM=BindODMem(IOPortStartIndex,SubindexOutput04,TypeU16,0); *outputSafetyHubSystemAxel12SinkenPWM=0x0000;
    outputSafetyHubSystemAxel21HebenPWM=BindODMem(IOPortStartIndex,SubindexOutput07,TypeU16,0); *outputSafetyHubSystemAxel21HebenPWM=0x0000;
    outputSafetyHubSystemAxel21SinkenPWM=BindODMem(IOPortStartIndex,SubindexOutput08,TypeU16,0); *outputSafetyHubSystemAxel21SinkenPWM=0x0000;
    outputSafetyHubSystemAxel22HebenPWM=BindODMem(IOPortStartIndex,SubindexOutput05,TypeU16,0); *outputSafetyHubSystemAxel22HebenPWM=0x0000;
    outputSafetyHubSystemAxel22SinkenPWM=BindODMem(IOPortStartIndex,SubindexOutput06,TypeU16,0); *outputSafetyHubSystemAxel22SinkenPWM=0x0000;
}

//====================================================================
/*!
Function: HubSysSafetyHandleTemperatur
Output: None
*/
//====================================================================
void HubSysSafetyHandleTemperatur(void){
    boolean m1;
    static boolean SafteyErrorHubTemperaturHighOldValue;
    //1. Layer
    if(*inputSafetyHubSystemTemperaturMain>PumpeMaxTemperatur)  m1=TRUE;
    else m1=FALSE;
    //2. Layer
    SafteyErrorHubTemperaturHigh=m1;
    //Output
    if(SafteyErrorHubTemperaturHigh){
         if(SafteyErrorHubTemperaturHigh!=SafteyErrorHubTemperaturHighOldValue)
            SetErrorCode(1033001);
         setFault();
    }
    //OldValue
    SafteyErrorHubTemperaturHighOldValue=SafteyErrorHubTemperaturHigh;
}

//====================================================================
/*!
Function: HubSysSafetyHandleHubLast
Output: None
*/
//====================================================================
void HubSysSafetyHandleHubLast(void){
    boolean m1,m2,m3,m4,m5;
    static boolean SafteyErrorMainDruckHighOldValue;
    static boolean SafteyErrorAchse11lastetOldValue;
    static boolean SafteyErrorAchse12lastetOldValue;
    static boolean SafteyErrorAchse21lastetOldValue;
    static boolean SafteyErrorAchse22lastetOldValue;
    //1. Layer
    if(*inputSafetyHubSystemPressureMain>MaxMainDruckValue)  m1=TRUE;
    else m1=FALSE;
    if(*inputSafetyHubSystemPressure11>MaxValveDruckValue)  m2=TRUE;
    else m2=FALSE;
    if(*inputSafetyHubSystemPressure12>MaxValveDruckValue)  m3=TRUE;
    else m3=FALSE;
    if(*inputSafetyHubSystemPressure21>MaxValveDruckValue)  m4=TRUE;
    else m4=FALSE;
    if(*inputSafetyHubSystemPressure22>MaxValveDruckValue)  m5=TRUE;
    else m5=FALSE;
    //2. Layer
    SafteyErrorMainDruckHigh=m1;
    SafteyErrorAchse11lastet=m2;
    SafteyErrorAchse12lastet=m3;
    SafteyErrorAchse21lastet=m4;
    SafteyErrorAchse22lastet=m5;
    //Output
    if(SafteyErrorMainDruckHigh){
         if(SafteyErrorMainDruckHigh!=SafteyErrorMainDruckHighOldValue)
            SetErrorCode(1033000);
         setFault();
    }
    if(SafteyErrorAchse11lastet){
         if(SafteyErrorAchse11lastet!=SafteyErrorAchse11lastetOldValue)
            SetErrorCode(1033010);
         setFault();
    }
    if(SafteyErrorAchse12lastet){
         if(SafteyErrorAchse12lastet!=SafteyErrorAchse12lastetOldValue)
            SetErrorCode(1033011);
         setFault();
    }
    if(SafteyErrorAchse21lastet){
         if(SafteyErrorAchse21lastet!=SafteyErrorAchse21lastetOldValue)
            SetErrorCode(1033012);
         setFault();
    }
    if(SafteyErrorAchse22lastet){
         if(SafteyErrorAchse22lastet!=SafteyErrorAchse22lastetOldValue)
            SetErrorCode(1033013);
         setFault();
    }
    //OldValue
    SafteyErrorMainDruckHighOldValue=SafteyErrorMainDruckHigh;
    SafteyErrorAchse11lastetOldValue=SafteyErrorAchse11lastet;
    SafteyErrorAchse12lastetOldValue=SafteyErrorAchse12lastet;
    SafteyErrorAchse21lastetOldValue=SafteyErrorAchse21lastet;
    SafteyErrorAchse22lastetOldValue=SafteyErrorAchse22lastet;
}

//====================================================================
/*!
Function: HubSysSafetyHandlePumpe
Output: None
*/
//====================================================================
void HubSysSafetyHandlePumpe(void){
    boolean m1,m2;
    static boolean SafteyErrorPumpeUmrichterOldValue;
    static boolean SafteyErrorPumpeDrehzahlOutOldValue;
    //1. Layer
    if(*inputSafetyHubSystemPumpeStatusByte&KeySafetyMotorStatusFehler)  m1=TRUE;
    else m1=FALSE;
    if(SafteyErrorPumpeDrehzahlTimeOut==1)  m2=TRUE;
    else m2=FALSE;
    //2. Layer
    SafteyErrorPumpeUmrichter=m1;
    SafteyErrorPumpeDrehzahlOut=m2;
    //Output
    if(SafteyErrorPumpeUmrichter){
         if(SafteyErrorPumpeUmrichter!=SafteyErrorPumpeUmrichterOldValue)
            SetErrorCode(1082101);
         setFault();
    }
    if(SafteyErrorPumpeDrehzahlOut){
         if(SafteyErrorPumpeDrehzahlOut!=SafteyErrorPumpeDrehzahlOutOldValue)
            SetErrorCode(1033003);
         setFault();
    }
    //OldValue
    SafteyErrorPumpeUmrichterOldValue=SafteyErrorPumpeUmrichter;
    SafteyErrorPumpeDrehzahlOutOldValue=SafteyErrorPumpeDrehzahlOut;
}

//====================================================================
/*!
Function: HubSysSafetyHandleVentil
Output: None
*/
//====================================================================
void HubSysSafetyHandleVentil(void){
    boolean m1,m2,m3,m4;
    static boolean SafteyErrorVentil11OldValue;
    static boolean SafteyErrorVentil12OldValue;
    static boolean SafteyErrorVentil21OldValue;
    static boolean SafteyErrorVentil22OldValue;
    //1. Layer
    if(SafteyErrorVentil11TimeOut==1)  m1=TRUE;
    else m1=FALSE;
    if(SafteyErrorVentil12TimeOut==1)  m2=TRUE;
    else m2=FALSE;
    if(SafteyErrorVentil21TimeOut==1)  m3=TRUE;
    else m3=FALSE;
    if(SafteyErrorVentil22TimeOut==1)  m4=TRUE;
    else m4=FALSE;
    //2. Layer
    SafteyErrorVentil11=m1;
    SafteyErrorVentil12=m2;
    SafteyErrorVentil21=m3;
    SafteyErrorVentil22=m4;
    SafteyErrorVentil=m1|m2|m3|m4;
    //Output
    if(SafteyErrorVentil11){
         if(SafteyErrorVentil11!=SafteyErrorVentil11OldValue)
            SetErrorCode(1033020);
         setFault();
    }
    if(SafteyErrorVentil12){
         if(SafteyErrorVentil12!=SafteyErrorVentil12OldValue)
            SetErrorCode(1033021);
         setFault();
    }
    if(SafteyErrorVentil21){
         if(SafteyErrorVentil21!=SafteyErrorVentil21OldValue)
            SetErrorCode(1033022);
         setFault();
    }
    if(SafteyErrorVentil22){
         if(SafteyErrorVentil22!=SafteyErrorVentil22OldValue)
            SetErrorCode(1033023);
         setFault();
    }
    //OldValue
    SafteyErrorVentil11OldValue=SafteyErrorVentil11;
    SafteyErrorVentil12OldValue=SafteyErrorVentil12;
    SafteyErrorVentil21OldValue=SafteyErrorVentil21;
    SafteyErrorVentil22OldValue=SafteyErrorVentil22;
}

//====================================================================
/*!
Function: HubSysSafetyNodeStatus
Output: None
*/
//====================================================================
void HubSysSafetyNodeStatus(void){
    boolean m1;
    static boolean SafteyErrorPumpeOfflineOldValue;
    //1. Layer
    if(SafteyErrorPumpeOfflineTimeOut==1)  m1=TRUE;
    else m1=FALSE;
    //2. Layer
    SafteyErrorPumpeOffline=m1;
    //Output
    if(SafteyErrorPumpeOffline){
         if(SafteyErrorPumpeOffline!=SafteyErrorPumpeOfflineOldValue)
            SetErrorCode(1081211);
         setFault();
    }
    //OldValue
    SafteyErrorPumpeOfflineOldValue=SafteyErrorPumpeOffline;
}

//====================================================================
/*!
Function: handle of safety hub system
Output: None
*/
//====================================================================
void HandleSafetyHubSys(void){
    HubSysSafetyHandleTemperatur();
    HubSysSafetyHandleHubLast();
    HubSysSafetyHandlePumpe();
    HubSysSafetyHandleVentil();
    HubSysSafetyNodeStatus();
}

//====================================================================
/*!
Function: timer of safety hub system
Output: None
*/
//====================================================================
void TimerSafetyHubSys(void){
    boolean m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12,m13,m14,m15,m16,m17,m18;
    static uint8 tick1,tick2,tick3,tick4,tick5,tick6;
    //1. Layer
    if(abs(*inputSafetyHubSystemPumpeActualSpeed-1500)>MaxPumpeDrehzahlError)  m1=TRUE;
    else m1=FALSE;
    if(abs(*inputSafetyHubSystemPumpeActualSpeed-500)>MaxPumpeDrehzahlError)  m2=TRUE;
    else m2=FALSE;
    if(*inputSafetyHubSystemPumpeStatusByte&KeySafetyMotorStatusEnable)  m3=TRUE;
    else m3=FALSE;
    if(*outputSafetyHubSystemControlWord&KeySafetySetHubsystemHeben)  m4=TRUE;
    else m4=FALSE;
    if(*outputSafetyHubSystemControlWord&KeySafetySetHubsystemSinken)  m5=TRUE;
    else m5=FALSE;
    if(abs(*inputSafetyHubSystemSpeedHeight11)>2000)  m6=TRUE;
    else m6=FALSE;
    if(abs(*inputSafetyHubSystemSpeedHeight12)>2000)  m7=TRUE;
    else m7=FALSE;
    if(abs(*inputSafetyHubSystemSpeedHeight21)>2000)  m8=TRUE;
    else m8=FALSE;
    if(abs(*inputSafetyHubSystemSpeedHeight22)>2000)  m9=TRUE;
    else m9=FALSE;
    if(*outputSafetyHubSystemAxel11HebenPWM>2000)  m10=TRUE;
    else m10=FALSE;
    if(*outputSafetyHubSystemAxel11SinkenPWM>2000)  m11=TRUE;
    else m11=FALSE;
    if(*outputSafetyHubSystemAxel12HebenPWM>2000)  m12=TRUE;
    else m12=FALSE;
    if(*outputSafetyHubSystemAxel12SinkenPWM>2000)  m13=TRUE;
    else m13=FALSE;
    if(*outputSafetyHubSystemAxel21HebenPWM>2000)  m14=TRUE;
    else m14=FALSE;
    if(*outputSafetyHubSystemAxel21SinkenPWM>2000)  m15=TRUE;
    else m15=FALSE;
    if(*outputSafetyHubSystemAxel22HebenPWM>2000)  m16=TRUE;
    else m16=FALSE;
    if(*outputSafetyHubSystemAxel22SinkenPWM>2000)  m17=TRUE;
    else m17=FALSE;
    if(*inputSafetyHubSystemPumpeNodeStatus<KeySafetyNodeDisconneted)  m18=TRUE;
    else m18=FALSE;
    //2. Layer
    if(((m1&m4)|(m2&m5))&m3){ if(tick1<255) tick1++;}
    else tick1=0;
    if((~m6)&(m10|m11)){ if(tick2<255) tick2++;}
    else tick2=0;
    if((~m7)&(m12|m13)){ if(tick3<255) tick3++;}
    else tick3=0;
    if((~m8)&(m14|m15)){ if(tick4<255) tick4++;}
    else tick4=0;
    if((~m9)&(m16|m17)){ if(tick5<255) tick5++;}
    else tick5=0;
    if(m18){ if(tick6<255) tick6++;}
    else tick6=0;
    //output
    if(tick1>=30) SafteyErrorPumpeDrehzahlTimeOut=1;
    else SafteyErrorPumpeDrehzahlTimeOut=0;
    if(tick2>=30) SafteyErrorVentil11TimeOut=1;
    else SafteyErrorVentil11TimeOut=0;
    if(tick3>=30) SafteyErrorVentil12TimeOut=1;
    else SafteyErrorVentil12TimeOut=0;
    if(tick4>=30) SafteyErrorVentil21TimeOut=1;
    else SafteyErrorVentil21TimeOut=0;
    if(tick5>=30) SafteyErrorVentil22TimeOut=1;
    else SafteyErrorVentil22TimeOut=0;
    if(tick6>=50) SafteyErrorPumpeOfflineTimeOut=1;
    else SafteyErrorPumpeOfflineTimeOut=0;
}
