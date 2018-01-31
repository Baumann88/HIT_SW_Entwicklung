#include "Safety.h"
#include "SafetyData.h"
#include "SafetyInterface.h"

//=================================================================================================
/*!
    Function: generate the Interface
    output: None
*/
//=================================================================================================
void InitInterfaceSafety(void){
    uint16 i;
    inputErrorCount=BindODMem(SafetyStartIndex,SubindexNumOfError,TypeU16,0); *inputErrorCount=0;

    inputSafetyDateTime1=BindODMem(DevParaStartIndex,SubindexSysDateTime1,TypeU32,0);
    inputSafetyDateTime2=BindODMem(DevParaStartIndex,SubindexSysDateTime2,TypeU32,0);

    inputSafetySysControlWord=BindODMem(DevParaStartIndex,SubindexControlWord,TypeU32,0);

    for(i=0;i<32;i++){
        inputErrorRegister[i]=BindODMem(SafetyStartIndex,SubindexErrorRegister01+i,TypeU32,0);
        inputErrorTimeStamp[i][0]=BindODMem(SafetyStartIndex,SubindexErrorRegister01Timestamp1+i*2,TypeU32,0);
        inputErrorTimeStamp[i][1]=BindODMem(SafetyStartIndex,SubindexErrorRegister01Timestamp1+i*2+1,TypeU32,0);
    }

    InitSafetyPLC();
    InitSafetyHubSys();
}


//=================================================================================================
/*!
    Function: Set the error in the error counter
    output: None
*/
//=================================================================================================
void setFault(void){
    fault++;
}

//=================================================================================================
/*!
    Function: Set the error code in error register
    output: None
*/
//=================================================================================================
void SetErrorCode(uint32 code){
    uint16 iError;

    if(code==0) return;

    for(iError=0;iError<31;iError++){
        *inputErrorRegister[31-iError]=*inputErrorRegister[30-iError];
        *inputErrorTimeStamp[31-iError][0]=*inputErrorTimeStamp[30-iError][0];
        *inputErrorTimeStamp[31-iError][1]=*inputErrorTimeStamp[30-iError][1];
    }

    *inputErrorRegister[0]=code;
    *inputErrorTimeStamp[0][0]=*inputSafetyDateTime1;
    *inputErrorTimeStamp[0][1]=*inputSafetyDateTime2;

    for(iError=0x01;iError<0x61;iError++){
        StoreLoadOD(0x6500,iError,StoreODToEEP);
    }

    return;
}

//=================================================================================================
/*!
    Function: Clear the error code in error register
    output: None
*/
//=================================================================================================
void ClearErrorCode(void){
    uint16 iError;
    for(iError=0;iError<32;iError++){
        *inputErrorRegister[iError]=0;
        *inputErrorTimeStamp[iError][0]=0;
        *inputErrorTimeStamp[iError][1]=0;
    }
    for(iError=0x01;iError<0x61;iError++){
        StoreLoadOD(0x6500,iError,StoreODToEEP);
    }
    return;
}

//=================================================================================================
/*!
    Function: get the system time in ms
    output: None
*/
//=================================================================================================
void SafetyTimer(void){
    TimerSafetyHubSys();
}

//=================================================================================================
/*!
    Function: Main Task of the safety
    output: None
*/
//=================================================================================================
void Task_Safety(void *argv){
    argv=argv;
    uint32 u32_Events;
    uint16 flag;

    while(TRUE){
        SafetyTimer();
        switch(flag){
            case 0: HandleSafetyHubSys(); break;
            case 1: HandleSafetyNormal(); break;
            case 2: HandleSafetyPLC(); break;
            default: break;
        }
        if(flag>=2) {
            *inputErrorCount=fault;
            if(*inputErrorCount>8) *inputErrorCount=8;
            fault=0;
            flag=0;
        }
        else flag++;
        if(*inputSafetySysControlWord&0x00000008){
            *inputSafetySysControlWord&=~0x00000008;
            ClearErrorCode();
        }


        x_os_wait_for_events();
    }
}


//=================================================================================================
/*!
    Function: Initial of the Safety System
    output: None
*/
//=================================================================================================
void InitSafety(void){
    InitInterfaceSafety();
    x_os_install_task(PrioSafety, 500, 100, Task_Safety, 128);
}













