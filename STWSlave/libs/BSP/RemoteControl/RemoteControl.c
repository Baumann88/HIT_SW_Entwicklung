#include "RemoteControl.h"
#include "RemoteControlInterface.h"
#include "RemoteControlData.h"

//old record of the Digital Input
static uint32 oldDigitalIn;

//=================================================================================================
/*!
    Function: generate the Interface
    output: None
*/
//=================================================================================================
void InitInterfaceRemoteControl(void){
    uint16 i;
    inputRemoteControlDigitalIn=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlTPDO2LowDWord,TypeU32,0);
    inputRemoteControlToggle=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlTPDO2HighDWord,TypeU8,2);

    inputRCGetSafetyControlWord=BindODMem(SafetyStartIndex,SubindexSafetyControlWord,TypeU32,0); *inputRCGetSafetyControlWord=0x00000000;
    inputRCGetSafetyMasterControlWord=BindODMem(SafetyStartIndex,SubindexSafetyControlWordMaster,TypeU32,0); *inputRCGetSafetyMasterControlWord=0x00000000;
    inputRCGetHubSystemControlWord=BindODMem(HubSystemStartIndex,SubindexHubSystemControlWord,TypeU32,0); *inputRCGetHubSystemControlWord=0x00000000;

    outputRemoteControlString0=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO2LowDWord,TypeU32,0); *outputRemoteControlString0=0x00000000;
    outputRemoteControlString1=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO2HighDWord,TypeU32,0); *outputRemoteControlString1=0x00000000;
    outputRemoteControlString2=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO4LowDWord,TypeU32,0); *outputRemoteControlString2=0x00000000;
    outputRemoteControlString3=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO4HighDWord,TypeU32,0); *outputRemoteControlString3=0x00000000;

    inputRCGetHubWerk11Height=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel11,TypeU32,0);
    inputRCGetHubWerk12Height=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel12,TypeU32,0);
    inputRCGetHubWerk21Height=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel21,TypeU32,0);
    inputRCGetHubWerk22Height=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel22,TypeU32,0);

    inputRCGetHubWerk11Pressure=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel11,TypeS32,0);
    inputRCGetHubWerk12Pressure=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel12,TypeS32,0);
    inputRCGetHubWerk21Pressure=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel21,TypeS32,0);
    inputRCGetHubWerk22Pressure=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel22,TypeS32,0);

    inputRCFromMasterDriveSysAngle11=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO1LowDWORD,TypeS8,0); *inputRCFromMasterDriveSysAngle11=0;
    inputRCFromMasterDriveSysAngle12=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO1LowDWORD,TypeS8,1); *inputRCFromMasterDriveSysAngle12=0;
    inputRCFromMasterDriveSysAngle21=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO1LowDWORD,TypeS8,2); *inputRCFromMasterDriveSysAngle21=0;
    inputRCFromMasterDriveSysAngle22=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO1LowDWORD,TypeS8,3); *inputRCFromMasterDriveSysAngle22=0;

    //status of the MES to slave
    inputRCFromMasterStatusMES=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO1HighDWORD,TypeU8,1); *inputRCFromMasterStatusMES=0x00;
    inputRCFromMasterStatusExtMES=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO2HighDWORD,TypeU8,1); *inputRCFromMasterStatusExtMES=0x00;
    inputRCFromMasterSteeringMode=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO2HighDWORD,TypeU8,2); *inputRCFromMasterSteeringMode=0x00;
    inputRCFromMasterPageState=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO1HighDWORD,TypeU8,3); *inputRCFromMasterPageState=0x00;
    inputRCFromMasterStatusAutoDrive=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO1HighDWORD,TypeU8,2); *inputRCFromMasterStatusAutoDrive=0x00;
    inputRCFromMasterSpeedMES=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO1HighDWORD,TypeS8,0); *inputRCFromMasterSpeedMES=0;
    inputRCFromMasterAutoDriveState=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO2HighDWORD,TypeU8,3); *inputRCFromMasterAutoDriveState=0x00;

    //value of the Error Camera
    inputRCFromMasterY1Value=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO2LowDWORD,TypeS8,0); *inputRCFromMasterY1Value=0;
    inputRCFromMasterY2Value=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO2LowDWORD,TypeS8,1); *inputRCFromMasterY2Value=0;
    inputRCFromMasterXValue=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO2LowDWORD,TypeU16,1); *inputRCFromMasterXValue=0;

    inputRCGetErrorNum=BindODMem(SafetyStartIndex,SubindexNumOfError,TypeU8,0); *inputRCGetErrorNum=0;
    inputRCGetMasterCPUErrorNum=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlRPDO2HighDWORD,TypeU8,0); *inputRCGetMasterCPUErrorNum=0;

    for(i=0;i<8;i++){
        inputRCGetErrorCode[i]=BindODMem(SafetyStartIndex,SubindexErrorRegister01+i,TypeU32,0);
    }

    for(i=0;i<8;i++){
        inputRCGetErrorCodeMasterCPU[i]=BindODMem(SafetyStartIndex,SubindexMasterCPUErrorRegister01+i,TypeU32,0);
    }
}



//=================================================================================================
/*!
    Function: get the button value of the remote controller
    output: None
*/
//=================================================================================================
void GetButtonValue(void){
    //menu taster
    if(*inputRemoteControlDigitalIn&RemoteControlMenuTasterLeft){
        if((oldDigitalIn&RemoteControlMenuTasterLeft)==0) RCReqWord|=KeyRCReqWordMeunTasterLeft;
    }
    else if(*inputRemoteControlDigitalIn&RemoteControlMenuTasterRight){
        if((oldDigitalIn&RemoteControlMenuTasterRight)==0) RCReqWord|=KeyRCReqWordMeunTasterRight;
    }
    if(*inputRemoteControlDigitalIn&RemoteControlMenuTasterPush) {
        if((oldDigitalIn&RemoteControlMenuTasterPush)==0) RCReqWord|=KeyRCReqWordMeunTasterPush;
    }
}


//=================================================================================================
/*!
    Function: Main Task of the Remote control
    output: None
*/
//=================================================================================================
void Task_RemoteControl(void* argv){
    argv=argv;
    uint32 u32_Events;

    x_os_set_event_mask(Event_RC);
    akt_page=0;

    while(TRUE){
        x_os_wait_for_events();
        u32_Events = x_os_get_events(); // get events
        if((u32_Events&Event_RC)!=0){
            GetButtonValue();
            oldDigitalIn=*inputRemoteControlDigitalIn;
        }
    }
}
//=================================================================================================
/*!
    Function: Main Task of the Remote control Display
    output: None
*/
//=================================================================================================
void Task_RemoteControlDisplay(void* argv){
    argv=argv;

    while(TRUE){
        Display();
        x_os_wait_for_events();
    }
}



//=================================================================================================
/*!
    Function: Initial of the Remote Control
    output: None
*/
//=================================================================================================
void InitRemoteControl(void){
    SetPageInit();

    InitInterfaceRemoteControl();
    x_os_install_task(PrioRemoteControl, 0, 0, Task_RemoteControl, 32);
    x_os_install_task(PrioRemoteControlDisplay, 150, 5, Task_RemoteControlDisplay, 256);
}

//=================================================================================================
/*!
    Function: Awake the Task from sleep state
    input:
    output: None
*/
//=================================================================================================
void TaskRemoteControlAwake(void){
    uint16 MaxRCToggleCounter=1;
    static uint8 OldToggleByte;
    static uint16 RCtogglecounter;
    if(*inputRemoteControlToggle!=OldToggleByte) {
        RCtogglecounter++;
        OldToggleByte=*inputRemoteControlToggle;
    }

    if(RCtogglecounter>=MaxRCToggleCounter){
        x_os_set_events(Event_RC);
        RCtogglecounter=0;
    }
}


