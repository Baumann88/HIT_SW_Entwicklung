#include <SafetyData.h>
#include <Safety.h>

//====================================================================
/*!
Function: initial Satety PLC
Output: None
*/
//====================================================================
void InitSafetyPLC(void){
    inputSafetyIONotAusFunkeKanal1=BindODMem(IOPortStartIndex,SubindexInput28,TypeU16,0); *inputSafetyIONotAusFunkeKanal1=0x0000;
    inputSafetyIONotAusFunkeKanal2=BindODMem(IOPortStartIndex,SubindexInput41,TypeU16,0); *inputSafetyIONotAusFunkeKanal2=0x0000;
    inputSafetyIONotAusEckVorneKanal1=BindODMem(IOPortStartIndex,SubindexInput29,TypeU16,0); *inputSafetyIONotAusEckVorneKanal1=0x0000;
    inputSafetyIONotAusEckVorneKanal2=BindODMem(IOPortStartIndex,SubindexInput42,TypeU16,0); *inputSafetyIONotAusEckVorneKanal2=0x0000;
    inputSafetyIONotAusEckHintenKanal1=BindODMem(IOPortStartIndex,SubindexInput30,TypeU16,0); *inputSafetyIONotAusEckHintenKanal1=0x0000;
    inputSafetyIONotAusEckHintenKanal2=BindODMem(IOPortStartIndex,SubindexInput43,TypeU16,0); *inputSafetyIONotAusEckHintenKanal2=0x0000;
    inputSafetyIOLS1Warnfeld1=BindODMem(IOPortStartIndex,SubindexInput32,TypeU16,0); *inputSafetyIOLS1Warnfeld1=0x0000;
    inputSafetyIOLS2Warnfeld1=BindODMem(IOPortStartIndex,SubindexInput45,TypeU16,0); *inputSafetyIOLS2Warnfeld1=0x0000;
    inputSafetyIOLS1AbschaltFeldKanal1=BindODMem(IOPortStartIndex,SubindexInput33,TypeU16,0); *inputSafetyIOLS1AbschaltFeldKanal1=0x0000;
    inputSafetyIOLS1AbschaltFeldKanal2=BindODMem(IOPortStartIndex,SubindexInput46,TypeU16,0); *inputSafetyIOLS1AbschaltFeldKanal2=0x0000;
    inputSafetyIOLS2AbschaltFeldKanal1=BindODMem(IOPortStartIndex,SubindexInput34,TypeU16,0); *inputSafetyIOLS2AbschaltFeldKanal1=0x0000;
    inputSafetyIOLS2AbschaltFeldKanal2=BindODMem(IOPortStartIndex,SubindexInput47,TypeU16,0); *inputSafetyIOLS2AbschaltFeldKanal2=0x0000;
    inputSafetyIOLS1Warnfeld2=BindODMem(IOPortStartIndex,SubindexInput35,TypeU16,0); *inputSafetyIOLS1Warnfeld2=0x0000;
    inputSafetyIOLS2Warnfeld2=BindODMem(IOPortStartIndex,SubindexInput48,TypeU16,0); *inputSafetyIOLS2Warnfeld2=0x0000;
    inputSafetyIOLS1Quittierung=BindODMem(IOPortStartIndex,SubindexOutput36,TypeU32,0); *inputSafetyIOLS1Quittierung=0x00000000;
    inputSafetyIOLS2Quittierung=BindODMem(IOPortStartIndex,SubindexOutput49,TypeU32,0); *inputSafetyIOLS2Quittierung=0x00000000;
    inputSafetyIONotAusSchutz=BindODMem(IOPortStartIndex,SubindexInput52,TypeU16,0); *inputSafetyIONotAusSchutz=0x0000;
    inputSafetyIOLadeStecker=BindODMem(IOPortStartIndex,SubindexInput39,TypeU16,0); *inputSafetyIOLadeStecker=0x0000;
    inputSafetySafetySysControlWord=BindODMem(SafetyStartIndex,SubindexSafetyControlWord,TypeU32,0); *inputSafetySafetySysControlWord=0x00000000;
    inputSafetyGetSlaveMESStatus=BindODMem(RemoteControlStartIndex,SubindexTelegramm1FromSlaveLowWord,TypeU8,0); *inputSafetyGetSlaveMESStatus=0x00;
    inputSafetyGetCPUTemperatur=BindODMem(DevParaStartIndex,SubindexCPUTemperatur,TypeU32,0); *inputSafetyGetCPUTemperatur=0x00000000;
    inputSafetyGetCPUVoltageUb=BindODMem(DevParaStartIndex,SubindexCPUVoltageUb1,TypeU32,0); *inputSafetyGetCPUVoltageUb=0x00000000;
    inputSafetyGetCPUVoltageUc=BindODMem(DevParaStartIndex,SubindexCPUVoltageUC1,TypeU32,0); *inputSafetyGetCPUVoltageUc=0x00000000;
    inputSafetyGetCPUVoltageUext=BindODMem(DevParaStartIndex,SubindexCPUVoltageExt,TypeU32,0); *inputSafetyGetCPUVoltageUext=0x00000000;
    inputSafetyGetCPUCurrentUb=BindODMem(DevParaStartIndex,SubindexCPUCurrentUb1,TypeU32,0); *inputSafetyGetCPUCurrentUb=0x00000000;
    inputSafetyGetCANBusStatus=BindODMem(DevParaStartIndex,SubindexSysStatus,TypeU8,1); *inputSafetyGetCANBusStatus=0x00;
    inputSafetyRCNodeStatus=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlNodeStatus,TypeU8,1); *inputSafetyRCNodeStatus=0x00;

    outputSafetyIOLeistungSchutz1=BindODMem(IOPortStartIndex,SubindexOutput01,TypeU32,0); *outputSafetyIOLeistungSchutz1=0x00000000;
    outputSafetyIOLeistungSchutz2=BindODMem(IOPortStartIndex,SubindexOutput50,TypeU32,0); *outputSafetyIOLeistungSchutz2=0x00000000;
    outputSafetyIOMESAus=BindODMem(IOPortStartIndex,SubindexOutput06,TypeU32,0); *outputSafetyIOMESAus=0x00000000;
    outputSafetyIOQuittierungLS1=BindODMem(IOPortStartIndex,SubindexOutput36,TypeU32,0); *outputSafetyIOQuittierungLS1=0x00000000;
    outputSafetyIOQuittierungLS2=BindODMem(IOPortStartIndex,SubindexOutput49,TypeU32,0); *outputSafetyIOQuittierungLS2=0x00000000;
    outputSafetyIOMotorSafetyStop=BindODMem(IOPortStartIndex,SubindexOutput51,TypeU32,0); *outputSafetyIOMotorSafetyStop=0x00000000;
    outputSafetyIO15minAus=BindODMem(IOPortStartIndex,SubindexOutput07,TypeU32,0); *outputSafetyIO15minAus=0x00000000;
}

//====================================================================
/*!
Function: PLCSafetyNoVersorgung
Output: None
*/
//====================================================================
void PLCSafetyNoVersorgung(void){
    boolean m1,m2,m3;
    static boolean SafetyErrorNoVersorgungOldValue;
    //1. Layer
    if(*inputSafetyIONotAusSchutz==1)  m1=TRUE;
    else m1=FALSE;
    if(*outputSafetyIOLeistungSchutz1&0x0000ffff)  m2=TRUE;
    else m2=FALSE;
    if(*outputSafetyIOLeistungSchutz2&0x0000ffff)  m3=TRUE;
    else m3=FALSE;
    //2. Layer
    SafetyErrorNoVersorgung=m2&m3&m1;
    //Output
    if(SafetyErrorNoVersorgung){
         if(SafetyErrorNoVersorgung!=SafetyErrorNoVersorgungOldValue)
            SetErrorCode(1021005);
         setFault();
    }
    //OldValue
    SafetyErrorNoVersorgungOldValue=SafetyErrorNoVersorgung;
}

//====================================================================
/*!
Function: PLCSafetyLaserscanner
Output: None
*/
//====================================================================
void PLCSafetyLaserscanner(void){
    boolean m1,m2,m3,m4,m5,m6,m7,m8;
    //1. Layer
    if(*inputSafetyIOLS1Warnfeld1==0)  m1=TRUE;
    else m1=FALSE;
    if(*inputSafetyIOLS1Warnfeld2==0)  m2=TRUE;
    else m2=FALSE;
    if(*inputSafetyIOLS2Warnfeld1==0)  m3=TRUE;
    else m3=FALSE;
    if(*inputSafetyIOLS2Warnfeld2==0)  m4=TRUE;
    else m4=FALSE;
    if((*inputSafetyIOLS1AbschaltFeldKanal1==0)&&(*inputSafetyIOLS1AbschaltFeldKanal2==0))  m5=TRUE;
    else m5=FALSE;
    if((*inputSafetyIOLS2AbschaltFeldKanal1==0)&&(*inputSafetyIOLS2AbschaltFeldKanal2==0))  m6=TRUE;
    else m6=FALSE;
    if(*inputSafetySafetySysControlWord&KeySafetyGetRCLaserscanner1Deaktiv)  m7=TRUE;
    else m7=FALSE;
    if(*inputSafetySafetySysControlWord&KeySafetyGetRCLaserscanner2Deaktiv)  m8=TRUE;
    else m8=FALSE;
    //2. Layer
    SafetyErrorLS1Warn1=~m5&m1&~m7;
    SafetyErrorLS1Warn2=~(m5|m1)&m2&~m7;
    SafetyErrorLS1Abschalten=m5&~m7;
    SafetyErrorLS2Warn1=~m6&m3&~m8;
    SafetyErrorLS2Warn2=~(m6|m3)&m4&~m8;
    SafetyErrorLS2Abschalten=m6&~m8;
    //Output
    //OldValue
}

//====================================================================
/*!
Function: PLCSafetyNotAus
Output: None
*/
//====================================================================
void PLCSafetyNotAus(void){
    boolean m1,m2,m3,m4,m5,m6;
    //1. Layer
    if(*inputSafetyIONotAusFunkeKanal1==0)  m1=TRUE;
    else m1=FALSE;
    if(*inputSafetyIONotAusFunkeKanal2==0)  m2=TRUE;
    else m2=FALSE;
    if(*inputSafetyIONotAusEckVorneKanal1==0)  m3=TRUE;
    else m3=FALSE;
    if(*inputSafetyIONotAusEckVorneKanal2==0)  m4=TRUE;
    else m4=FALSE;
    if(*inputSafetyIONotAusEckHintenKanal1==0)  m5=TRUE;
    else m5=FALSE;
    if(*inputSafetyIONotAusEckHintenKanal2==0)  m6=TRUE;
    else m6=FALSE;
    //2. Layer
    SafetyErrorNotAusFunke=m1&m2;
    SafetyErrorNotAusEckVorne=m3&m4;
    SafetyErrorNotAusEckHinten=m5&m6;
    //Output
    //OldValue
}

//====================================================================
/*!
Function: PLCSafetyLadeStecker
Output: None
*/
//====================================================================
void PLCSafetyLadeStecker(void){
    boolean m1;
    //1. Layer
    if(*inputSafetyIOLadeStecker==1)  m1=TRUE;
    else m1=FALSE;
    //2. Layer
    SafetyErrorLadenZustand=m1;
    //Output
    //OldValue
}

//====================================================================
/*!
Function: PLCSafetyHubSinkenOnly
Output: None
*/
//====================================================================
void PLCSafetyHubSinkenOnly(void){
    boolean m1,m2;
    //1. Layer
    if(*inputSafetyGetSlaveMESStatus&KeySafetyGetSlaveMESStatusOnlySinken)  m1=TRUE;
    else m1=FALSE;
    if(*inputSafetyGetSlaveMESStatus&KeySafetyGetSlaveMESStatusHubStopReq)  m2=TRUE;
    else m2=FALSE;
    //2. Layer
    SafetyErrorHubSystemOnlySinken=m1;
    SafetyErrorHubSystemStopReq=m2;
    //Output
    //OldValue
}

//====================================================================
/*!
Function: SafetyErrorCPU
Output: None
*/
//====================================================================
void SafetyErrorCPU(void){
    boolean m1,m2,m3,m4,m5,m6,m7,m8,m9;
    static boolean SafetyErrorCPUTemperaturOldValue;
    static boolean SafetyErrorCPUVoltageUbOldValue;
    static boolean SafetyErrorCPUVoltageUcOldValue;
    static boolean SafetyErrorCPUVoltageUextOldValue;
    static boolean SafetyErrorCPUCurrentUbOldValue;
    static boolean SafetyErrorCANBus1OldValue;
    static boolean SafetyErrorCANBus2OldValue;
    static boolean SafetyErrorCANBus3OldValue;
    static boolean SafetyErrorCANBus4OldValue;
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
    if(*inputSafetyGetCANBusStatus&KeySafetyGetCANBus3Error)  m8=TRUE;
    else m8=FALSE;
    if(*inputSafetyGetCANBusStatus&KeySafetyGetCANBus4Error)  m9=TRUE;
    else m9=FALSE;
    //2. Layer
    SafetyErrorCPUTemperatur=m1;
    SafetyErrorCPUVoltageUb=m2;
    SafetyErrorCPUVoltageUc=m3;
    SafetyErrorCPUVoltageUext=m4;
    SafetyErrorCPUCurrentUb=m5;
    SafetyErrorCANBus1=m6;
    SafetyErrorCANBus2=m7;
    SafetyErrorCANBus3=m8;
    SafetyErrorCANBus4=m9;
    SafetyErrorCANBus=m6|m7|m8|m9;
    //Output
    if(SafetyErrorCPUTemperatur){
         if(SafetyErrorCPUTemperatur!=SafetyErrorCPUTemperaturOldValue)
            SetErrorCode(1021000);
         setFault();
    }
    if(SafetyErrorCPUVoltageUb){
         if(SafetyErrorCPUVoltageUb!=SafetyErrorCPUVoltageUbOldValue)
            SetErrorCode(1021001);
         setFault();
    }
    if(SafetyErrorCPUVoltageUc){
         if(SafetyErrorCPUVoltageUc!=SafetyErrorCPUVoltageUcOldValue)
            SetErrorCode(1021004);
         setFault();
    }
    if(SafetyErrorCPUVoltageUext){
         if(SafetyErrorCPUVoltageUext!=SafetyErrorCPUVoltageUextOldValue)
            SetErrorCode(1021003);
         setFault();
    }
    if(SafetyErrorCPUCurrentUb){
         if(SafetyErrorCPUCurrentUb!=SafetyErrorCPUCurrentUbOldValue)
            SetErrorCode(1021002);
         setFault();
    }
    if(SafetyErrorCANBus1){
         if(SafetyErrorCANBus1!=SafetyErrorCANBus1OldValue)
            SetErrorCode(1021200);
         setFault();
    }
    if(SafetyErrorCANBus2){
         if(SafetyErrorCANBus2!=SafetyErrorCANBus2OldValue)
            SetErrorCode(1021201);
         setFault();
    }
    if(SafetyErrorCANBus3){
         if(SafetyErrorCANBus3!=SafetyErrorCANBus3OldValue)
            SetErrorCode(1021202);
         setFault();
    }
    if(SafetyErrorCANBus4){
         if(SafetyErrorCANBus4!=SafetyErrorCANBus4OldValue)
            SetErrorCode(1021203);
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
    SafetyErrorCANBus3OldValue=SafetyErrorCANBus3;
    SafetyErrorCANBus4OldValue=SafetyErrorCANBus4;
}

//====================================================================
/*!
Function: SafetyErrorRCStatus
Output: None
*/
//====================================================================
void SafetyErrorRCStatus(void){
    boolean m1;
    static boolean SafetyErrorRCOfflineOldValue;
    //1. Layer
    if(SafetyErrorRCOfflineTimeOut==1)  m1=TRUE;
    else m1=FALSE;
    //2. Layer
    SafetyErrorRCOffline=m1;
    //Output
    if(SafetyErrorRCOffline){
         if(SafetyErrorRCOffline!=SafetyErrorRCOfflineOldValue)
            SetErrorCode(1021204);
         setFault();
    }
    //OldValue
    SafetyErrorRCOfflineOldValue=SafetyErrorRCOffline;
}

//====================================================================
/*!
Function: handle of safety PLC
Output: None
*/
//====================================================================
void HandleSafetyPLC(void){
    PLCSafetyNoVersorgung();
    PLCSafetyLaserscanner();
    PLCSafetyNotAus();
    PLCSafetyLadeStecker();
    PLCSafetyHubSinkenOnly();
    SafetyErrorCPU();
    SafetyErrorRCStatus();
}

//====================================================================
/*!
Function: timer of safety PLC
Output: None
*/
//====================================================================
void TimerSafetyPLC(void){
    boolean m1,m2,m3;
    static uint16 tick1,tick2,tick3;
    //1. Layer
    if(*inputSafetySafetySysControlWord&KeySafetyGetRCNoMotion)  m1=TRUE;
    else m1=FALSE;
    if(SafetyErrorNotAusEckVorne|SafetyErrorNotAusEckHinten|SafetyErrorNotAusFunke)  m2=TRUE;
    else m2=FALSE;
    if(*inputSafetyRCNodeStatus<=0x01)  m3=TRUE;
    else m3=FALSE;
    //2. Layer
    if(m1){ if(tick1<65530) tick1++;}
    else tick1=0;
    if(m2){ if(tick2<65530) tick2++;}
    else tick2=0;
    if(m3){ if(tick3<65530) tick3++;}
    else tick3=0;
    //output
    if(tick1>=15000) SafetyErrorMESTimeOut=TRUE;
    else SafetyErrorMESTimeOut=FALSE;
    if(tick2>=15) SafetyErrorNotAusSchutzAus=TRUE;
    else SafetyErrorNotAusSchutzAus=FALSE;
    if(tick3>=50) SafetyErrorRCOfflineTimeOut=TRUE;
    else SafetyErrorRCOfflineTimeOut=FALSE;
}
