#include "Safety.h"
#include "SafetyData.h"
#include "SafetyInterface.h"

//define timeout for MES system in ms
#define TimeOutStartInverterDisable               1000
#define TimeOutNotAus                             300
#define TimeOutNoJoystick                         3000
#define TimeOutBrake                              1000

//actual system time
static uint32 actualTime;
static uint16 fault;

//=================================================================================================
/*!
    Function: generate the Interface
    output: None
*/
//=================================================================================================
void InitInterfaceSafety(void){
    uint16 i;
    outputErrorCount=BindODMem(RemoteControlStartIndex,SubindexTelegramm2ToSlaveHighWord,TypeU8,0);

    inputSafetyDateTime1=BindODMem(SafetyStartIndex,SubindexSafetyDateTime1,TypeU32,0);
    inputSafetyDateTime2=BindODMem(SafetyStartIndex,SubindexSafetyDateTime2,TypeU32,0);

    inputSafetySysControlWord=BindODMem(DevParaStartIndex,SubindexControlWord,TypeU32,0);

    outputSafetySDOControlWord=BindODMem(DevParaStartIndex,SubindexSysSDOControlWord,TypeU32,0);
    outputSafetySDOContent=BindODMem(DevParaStartIndex,SubindexSysSDOContent,TypeU32,0);

    for(i=0;i<32;i++){
        inputErrorRegister[i]=BindODMem(SafetyStartIndex,SubindexErrorRegister01+i,TypeU32,0);
        inputErrorTimeStamp[i][0]=BindODMem(SafetyStartIndex,SubindexErrorRegister01Timestamp1+i*2,TypeU32,0);
        inputErrorTimeStamp[i][1]=BindODMem(SafetyStartIndex,SubindexErrorRegister01Timestamp1+i*2+1,TypeU32,0);
    }

    InitSafetyDriveSys();
    InitSafetyPLC();
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
    Function: send the error register to Slave
    output: None
*/
//=================================================================================================
void SendRegisterToSlave(void){
    static uint32 local_timestamp;
    static uint32 iReg;

    if((*outputSafetySDOControlWord&KeySafetySDOControlWordEnable)==0){
        if((x_sys_get_time_ms()-local_timestamp)>300){
            local_timestamp=x_sys_get_time_ms();
            *outputSafetySDOControlWord=0x61650073;
            *outputSafetySDOControlWord+=(iReg<<24);
            *outputSafetySDOContent=*inputErrorRegister[iReg];
            iReg++;
            if(iReg==8) iReg=0;
        }
    }
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
    TimerSafetyDriveSys();
    TimerSafetyPLC();
}

//=================================================================================================
/*!
    Function: Quit the laser scanner
    output: None
*/
//=================================================================================================
void LaserScannerQuit(void){
    static boolean oldValueLS1;
    static boolean oldValueLS2;
    static uint16 tick1,tick2;

    if((SafetyErrorLS1Abschalten==FALSE)&&(oldValueLS1==TRUE)) tick1=20;
    if((SafetyErrorLS2Abschalten==FALSE)&&(oldValueLS2==TRUE)) tick2=20;

    if(tick1>0){
        tick1--;
        SafetyErrorLS1Quit=1;
    }
    else SafetyErrorLS1Quit=0;

    if(tick2>0){
        tick2--;
        SafetyErrorLS2Quit=1;
    }
    else SafetyErrorLS2Quit=0;

    oldValueLS1=SafetyErrorLS1Abschalten;
    oldValueLS2=SafetyErrorLS2Abschalten;
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
            case 0: HandleSafetyPLC(); break;
            case 1: HandleSafetyNormal(); break;
            case 2: HandleSafetyDriveSys(); break;
            default: break;
        }

        if(flag>=3) {
            *outputErrorCount=fault;
            if(*outputErrorCount>8) *outputErrorCount=8;
            fault=0;
            flag=0;
        }
        else flag++;
        LaserScannerQuit();
        SendRegisterToSlave();
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













