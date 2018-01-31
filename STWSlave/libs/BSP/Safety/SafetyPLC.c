#include <SafetyData.h>
#include <Safety.h>

//====================================================================
/*!
Function: initial Satety PLC
Output: None
*/
//====================================================================
void InitSafetyPLC(void){
    inputSafetySafetySysControlWord=BindODMem(SafetyStartIndex,SubindexSafetyControlWord,TypeU32,0); *inputSafetySafetySysControlWord=0x00000000;
    inputSafetyGetCPUTemperatur=BindODMem(DevParaStartIndex,SubindexCPUTemperatur,TypeU32,0); *inputSafetyGetCPUTemperatur=0x00000000;
    inputSafetyGetCPUVoltageUb=BindODMem(DevParaStartIndex,SubindexCPUVoltageUb1,TypeU32,0); *inputSafetyGetCPUVoltageUb=0x00000000;
    inputSafetyGetCPUVoltageUc=BindODMem(DevParaStartIndex,SubindexCPUVoltageUC1,TypeU32,0); *inputSafetyGetCPUVoltageUc=0x00000000;
    inputSafetyGetCPUVoltageUext=BindODMem(DevParaStartIndex,SubindexCPUVoltageExt,TypeU32,0); *inputSafetyGetCPUVoltageUext=0x00000000;
    inputSafetyGetCPUCurrentUb=BindODMem(DevParaStartIndex,SubindexCPUCurrentUb1,TypeU32,0); *inputSafetyGetCPUCurrentUb=0x00000000;
    inputSafetyGetCANBusStatus=BindODMem(DevParaStartIndex,SubindexSysStatus,TypeU8,1); *inputSafetyGetCANBusStatus=0x00;

    outputSafetyIOLampe3=BindODMem(IOPortStartIndex,SubindexOutput30,TypeU32,0); *outputSafetyIOLampe3=0x00000000;
    outputSafetyIOLampe4=BindODMem(IOPortStartIndex,SubindexOutput31,TypeU32,0); *outputSafetyIOLampe4=0x00000000;
}

//====================================================================
/*!
Function: SafetyErrorCPU
Output: None
*/
//====================================================================
void SafetyErrorCPU(void){
    boolean m1,m2,m3,m4,m5,m6,m7;
    static boolean SafetyErrorCPUTemperaturOldValue;
    static boolean SafetyErrorCPUVoltageUbOldValue;
    static boolean SafetyErrorCPUVoltageUcOldValue;
    static boolean SafetyErrorCPUVoltageUextOldValue;
    static boolean SafetyErrorCPUCurrentUbOldValue;
    static boolean SafetyErrorCANBus1OldValue;
    static boolean SafetyErrorCANBus2OldValue;
    //1. Layer
    if(*inputSafetyGetCPUTemperatur>CPUMaxTemperatur)  m1=TRUE;
    else m1=FALSE;
    if((*inputSafetyGetCPUVoltageUb>CPUMaxVoltage)||(*inputSafetyGetCPUVoltageUb<CPUMinVoltage))  m2=TRUE;
    else m2=FALSE;
    if((*inputSafetyGetCPUVoltageUc>CPUMaxVoltage)||(*inputSafetyGetCPUVoltageUc<CPUMinVoltage))  m3=TRUE;
    else m3=FALSE;
    if((*inputSafetyGetCPUVoltageUext>CPUMaxVoltageExt)||(*inputSafetyGetCPUVoltageUext<CPUMinVoltageExt))  m4=TRUE;
    else m4=FALSE;
    if((*inputSafetyGetCPUCurrentUb>CPUMaxCurrent)||(*inputSafetyGetCPUCurrentUb<CPUMinCurrent))  m5=TRUE;
    else m5=FALSE;
    if(*inputSafetyGetCANBusStatus&KeySafetyGetCANBus1Error)  m6=TRUE;
    else m6=FALSE;
    if(*inputSafetyGetCANBusStatus&KeySafetyGetCANBus2Error)  m7=TRUE;
    else m7=FALSE;
    //2. Layer
    SafetyErrorCPUTemperatur=m1;
    SafetyErrorCPUVoltageUb=m2;
    SafetyErrorCPUVoltageUc=m3;
    SafetyErrorCPUVoltageUext=m4;
    SafetyErrorCPUCurrentUb=m5;
    SafetyErrorCANBus1=m6;
    SafetyErrorCANBus2=m7;
    SafetyErrorCANBus=m6|m7;
    //Output
    if(SafetyErrorCPUTemperatur){
         if(SafetyErrorCPUTemperatur!=SafetyErrorCPUTemperaturOldValue)
            SetErrorCode(1031000);
         setFault();
    }
    if(SafetyErrorCPUVoltageUb){
         if(SafetyErrorCPUVoltageUb!=SafetyErrorCPUVoltageUbOldValue)
            SetErrorCode(1031001);
         setFault();
    }
    if(SafetyErrorCPUVoltageUc){
         if(SafetyErrorCPUVoltageUc!=SafetyErrorCPUVoltageUcOldValue)
            SetErrorCode(1031004);
         setFault();
    }
    if(SafetyErrorCPUVoltageUext){
         if(SafetyErrorCPUVoltageUext!=SafetyErrorCPUVoltageUextOldValue)
            SetErrorCode(1031003);
         setFault();
    }
    if(SafetyErrorCPUCurrentUb){
         if(SafetyErrorCPUCurrentUb!=SafetyErrorCPUCurrentUbOldValue)
            SetErrorCode(1031002);
         setFault();
    }
    if(SafetyErrorCANBus1){
         if(SafetyErrorCANBus1!=SafetyErrorCANBus1OldValue)
            SetErrorCode(1031200);
         setFault();
    }
    if(SafetyErrorCANBus2){
         if(SafetyErrorCANBus2!=SafetyErrorCANBus2OldValue)
            SetErrorCode(1031201);
         setFault();
    }
    //OldValue
    SafetyErrorCPUTemperaturOldValue=SafetyErrorCPUTemperatur;
    SafetyErrorCPUVoltageUbOldValue=SafetyErrorCPUVoltageUb;
    SafetyErrorCPUVoltageUcOldValue=SafetyErrorCPUVoltageUc;
    SafetyErrorCPUVoltageUextOldValue=SafetyErrorCPUVoltageUext;
    SafetyErrorCPUCurrentUbOldValue=SafetyErrorCPUCurrentUb;
    SafetyErrorCANBus1OldValue=SafetyErrorCANBus1;
    SafetyErrorCANBus2OldValue=SafetyErrorCANBus2;
}

//====================================================================
/*!
Function: handle of safety PLC
Output: None
*/
//====================================================================
void HandleSafetyPLC(void){
    SafetyErrorCPU();
}

