#include "HubSystem.h"
#include "HubSystemData.h"
#include "HubSystemInterface.h"

#define MaxToggleCounter                            2
#define MaxHeight                                   125.0
#define MinHeight                                   10.0
#define DiffHeight                                  (MaxHeight-MinHeight)

//=================================================================================================
/*!
    Function: generate the Interface
    output: None
*/
//=================================================================================================
void InitInterfaceHubSys(void){
    //generate the interface of drive system
    //Intermediate
    inputHubSystemControlWord=BindODMem(HubSystemStartIndex,SubindexHubSystemControlWord,TypeU32,0); *inputHubSystemControlWord=0;
    inputHubSystemGetSafetyControlWord=BindODMem(SafetyStartIndex,SubindexSafetyControlWord,TypeU32,0);

    //Input
    inputHydraulicMotorStatusByte=BindODMem(InverterStartIndex,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputHydraulicMotorStatusByte=0;
    inputHydraulicMotorActualSpeed=BindODMem(InverterStartIndex,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputHydraulicMotorActualSpeed=0;
    inputHydraulicInverterNMTStatus=BindODMem(InverterStartIndex,SubindexInverterNodeStatus,TypeU8,0); *inputHydraulicInverterNMTStatus=0;
    inputHydraulicInverterNodeStatus=BindODMem(InverterStartIndex,SubindexInverterNodeStatus,TypeU8,1); *inputHydraulicInverterNodeStatus=0;

    inputHeightSensor11=BindODMem(IOPortStartIndex,SubindexInput01,TypeU16,0); *inputHeightSensor11=0;
    inputHeightSensor12=BindODMem(IOPortStartIndex,SubindexInput02,TypeU16,0); *inputHeightSensor12=0;
    inputHeightSensor21=BindODMem(IOPortStartIndex,SubindexInput04,TypeU16,0); *inputHeightSensor21=0;
    inputHeightSensor22=BindODMem(IOPortStartIndex,SubindexInput03,TypeU16,0); *inputHeightSensor22=0;
    inputHydraulicTemperature=BindODMem(IOPortStartIndex,SubindexInput14,TypeU16,0); *inputHydraulicTemperature=0;

    inputPressureSensorValueAxel11=BindODMem(IOPortStartIndex,SubindexInput10,TypeU16,0); *inputPressureSensorValueAxel11=0;
    inputPressureSensorValueAxel12=BindODMem(IOPortStartIndex,SubindexInput11,TypeU16,0); *inputPressureSensorValueAxel12=0;
    inputPressureSensorValueAxel21=BindODMem(IOPortStartIndex,SubindexInput13,TypeU16,0); *inputPressureSensorValueAxel21=0;
    inputPressureSensorValueAxel22=BindODMem(IOPortStartIndex,SubindexInput12,TypeU16,0); *inputPressureSensorValueAxel22=0;
    inputPressureSensorValueMain=BindODMem(IOPortStartIndex,SubindexInput09,TypeU16,0);  *inputPressureSensorValueMain=0;

    inputHeightSensor11FactA=BindODMem(HubSystemStartIndex,SubindexHeightSensor11FactA,TypeS32,0);
    inputHeightSensor11FactB=BindODMem(HubSystemStartIndex,SubindexHeightSensor11FactB,TypeS32,0);
    inputHeightSensor12FactA=BindODMem(HubSystemStartIndex,SubindexHeightSensor12FactA,TypeS32,0);
    inputHeightSensor12FactB=BindODMem(HubSystemStartIndex,SubindexHeightSensor12FactB,TypeS32,0);
    inputHeightSensor21FactA=BindODMem(HubSystemStartIndex,SubindexHeightSensor21FactA,TypeS32,0);
    inputHeightSensor21FactB=BindODMem(HubSystemStartIndex,SubindexHeightSensor21FactB,TypeS32,0);
    inputHeightSensor22FactA=BindODMem(HubSystemStartIndex,SubindexHeightSensor22FactA,TypeS32,0);
    inputHeightSensor22FactB=BindODMem(HubSystemStartIndex,SubindexHeightSensor22FactB,TypeS32,0);

    inputAxel11ControlKp=BindODMem(HubSystemStartIndex,SubindexControlKpAxel11,TypeS32,0);
    inputAxel11ControlKi=BindODMem(HubSystemStartIndex,SubindexControlKiAxel11,TypeS32,0);
    inputAxel12ControlKp=BindODMem(HubSystemStartIndex,SubindexControlKpAxel12,TypeS32,0);
    inputAxel12ControlKi=BindODMem(HubSystemStartIndex,SubindexControlKiAxel12,TypeS32,0);
    inputAxel21ControlKp=BindODMem(HubSystemStartIndex,SubindexControlKpAxel21,TypeS32,0);
    inputAxel21ControlKi=BindODMem(HubSystemStartIndex,SubindexControlKiAxel21,TypeS32,0);
    inputAxel22ControlKp=BindODMem(HubSystemStartIndex,SubindexControlKpAxel22,TypeS32,0);
    inputAxel22ControlKi=BindODMem(HubSystemStartIndex,SubindexControlKiAxel22,TypeS32,0);

    inputDefaultHydraulicMotorRPM=BindODMem(HubSystemStartIndex,SubindexDefaultHydraulicMotorRPM,TypeS16,0);
    inputMinHeight=BindODMem(HubSystemStartIndex,SubindexDefaultMinHeight,TypeU32,0);
    inputMaxHeight=BindODMem(HubSystemStartIndex,SubindexDefaultMaxHeight,TypeU32,0);

    //Output
    outputHydraulicMotorControlWord=BindODMem(InverterStartIndex,SubindexInverterRPDO1LowDWord,TypeU16,0); *outputHydraulicMotorControlWord=0;
    outputSetHydraulicMotorSpeed=BindODMem(InverterStartIndex,SubindexInverterRPDO1LowDWord,TypeS16,1); *outputSetHydraulicMotorSpeed=0;
    outputHydraulicInverterNMT=BindODMem(InverterStartIndex,SubindexInverterNMT,TypeU16,0); *outputHydraulicInverterNMT=0;

    outputSetBypassValve=BindODMem(IOPortStartIndex,SubindexOutput26,TypeU32,0); *outputSetBypassValve&=0xffff0000;

    outputSetPWMValveHubRaiseAxel11=BindODMem(IOPortStartIndex,SubindexOutput01,TypeU32,0); *outputSetPWMValveHubRaiseAxel11&=0xffff0000;
    outputSetPWMValveHubRaiseAxel12=BindODMem(IOPortStartIndex,SubindexOutput03,TypeU32,0); *outputSetPWMValveHubRaiseAxel12&=0xffff0000;
    outputSetPWMValveHubRaiseAxel21=BindODMem(IOPortStartIndex,SubindexOutput07,TypeU32,0); *outputSetPWMValveHubRaiseAxel21&=0xffff0000;
    outputSetPWMValveHubRaiseAxel22=BindODMem(IOPortStartIndex,SubindexOutput05,TypeU32,0); *outputSetPWMValveHubRaiseAxel22&=0xffff0000;

    outputSetPWMValveHubSinkAxel11=BindODMem(IOPortStartIndex,SubindexOutput02,TypeU32,0); *outputSetPWMValveHubSinkAxel11&=0xffff0000;
    outputSetPWMValveHubSinkAxel12=BindODMem(IOPortStartIndex,SubindexOutput04,TypeU32,0); *outputSetPWMValveHubSinkAxel12&=0xffff0000;
    outputSetPWMValveHubSinkAxel21=BindODMem(IOPortStartIndex,SubindexOutput08,TypeU32,0); *outputSetPWMValveHubSinkAxel21&=0xffff0000;
    outputSetPWMValveHubSinkAxel22=BindODMem(IOPortStartIndex,SubindexOutput06,TypeU32,0); *outputSetPWMValveHubSinkAxel22&=0xffff0000;

    //height of the hydraulic axle
    outputAxel11HubActualHeight=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel11,TypeU32,0); *outputAxel11HubActualHeight=0;
    outputAxel12HubActualHeight=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel12,TypeU32,0); *outputAxel12HubActualHeight=0;
    outputAxel21HubActualHeight=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel21,TypeU32,0); *outputAxel21HubActualHeight=0;
    outputAxel22HubActualHeight=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel22,TypeU32,0); *outputAxel22HubActualHeight=0;

    //height speed of the hydraulic axle
    outputSpeedHubAxel11=BindODMem(HubSystemStartIndex,SubindexHubSpeedAxel11,TypeS32,0); *outputSpeedHubAxel11=0;
    outputSpeedHubAxel12=BindODMem(HubSystemStartIndex,SubindexHubSpeedAxel12,TypeS32,0); *outputSpeedHubAxel12=0;
    outputSpeedHubAxel21=BindODMem(HubSystemStartIndex,SubindexHubSpeedAxel21,TypeS32,0); *outputSpeedHubAxel21=0;
    outputSpeedHubAxel22=BindODMem(HubSystemStartIndex,SubindexHubSpeedAxel22,TypeS32,0); *outputSpeedHubAxel22=0;

    //Value of pressure
    outputPressureAxel11=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel11,TypeS32,0); *outputPressureAxel11=0;
    outputPressureAxel12=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel12,TypeS32,0); *outputPressureAxel12=0;
    outputPressureAxel21=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel21,TypeS32,0); *outputPressureAxel21=0;
    outputPressureAxel22=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel22,TypeS32,0); *outputPressureAxel22=0;
    outputPressureMain=BindODMem(HubSystemStartIndex,SubindexPressureSensorPump,TypeS32,0); *outputPressureMain=0;

    //Value of CG
    outputHubWeight=BindODMem(HubSystemStartIndex,SubindexWeight,TypeS32,0); *outputHubWeight=0;
    outputHubCGPosL=BindODMem(HubSystemStartIndex,SubindexXValueCG,TypeS32,0); *outputHubCGPosL=0;
    outputHubCGPosB=BindODMem(HubSystemStartIndex,SubindexYValueCG,TypeS32,0); *outputHubCGPosB=0;

    outputHubStatus=BindODMem(HubSystemStartIndex,SubindexHubSystemTelegramm,TypeU8,0); *outputHubStatus=0x00;
    outputHubHeight=BindODMem(HubSystemStartIndex,SubindexHubSystemTelegramm,TypeU8,1); *outputHubHeight=0;

    //Temperature of the main pipe
    outputMainTemperature=BindODMem(HubSystemStartIndex,SubindexActualTemperature,TypeS32,0); *outputMainTemperature=0;
}



//=================================================================================================
/*!
    Function: generate the set value of the Hub system
    output: None
*/
//=================================================================================================
void SetHubValueGenerate(void){
    static uint32 local_timestamp;
    uint16 tmp;
    float32 SetHeightPercent;

    tmp=(uint16)((*inputHubSystemControlWord&0xffff0000)>>16);
    SetHeightPercent=(float32)tmp/100.0;
    HubVirtualHeight=SetHeightPercent*DiffHeight+MinHeight;

    //set the hub mode
    if(*inputHubSystemControlWord&KeyHubSystemHeben){
        HubMode=KeyHubModeHeben;
        local_timestamp=x_sys_get_time_ms();
    }
    else if(*inputHubSystemControlWord&KeyHubSystemSinken){
        HubMode=KeyHubModeSinken;
        local_timestamp=x_sys_get_time_ms();
    }
    else{
        if(x_sys_get_time_ms()-local_timestamp>2000){
            HubMode=KeyHubModeStop;
        }
    }
}

//=================================================================================================
/*!
    Function: update the parameter of the Hub system
    output: None
*/
//=================================================================================================
void HubParameterUpdate(void){
    static uint16 updateFlag;
    float32 SensorValue;

    if(updateFlag>30){
        updateFlag=0;
        HubSersor11FactA=(float32)(*inputHeightSensor11FactA)*0.001;
        HubSersor11FactB=(float32)(*inputHeightSensor11FactB)*0.001;

        HubSersor12FactA=(float32)(*inputHeightSensor12FactA)*0.001;
        HubSersor12FactB=(float32)(*inputHeightSensor12FactB)*0.001;

        HubSersor21FactA=(float32)(*inputHeightSensor21FactA)*0.001;
        HubSersor21FactB=(float32)(*inputHeightSensor21FactB)*0.001;

        HubSersor22FactA=(float32)(*inputHeightSensor22FactA)*0.001;
        HubSersor22FactB=(float32)(*inputHeightSensor22FactB)*0.001;

        ControllerDatenAxel11.kp=(float32)(*inputAxel11ControlKp)*0.001;
        ControllerDatenAxel11.ki=(float32)(*inputAxel11ControlKi)*0.001;
        ControllerDatenAxel12.kp=(float32)(*inputAxel12ControlKp)*0.001;
        ControllerDatenAxel12.ki=(float32)(*inputAxel12ControlKi)*0.001;
        ControllerDatenAxel21.kp=(float32)(*inputAxel21ControlKp)*0.001;
        ControllerDatenAxel21.ki=(float32)(*inputAxel21ControlKi)*0.001;
        ControllerDatenAxel22.kp=(float32)(*inputAxel22ControlKp)*0.001;
        ControllerDatenAxel22.ki=(float32)(*inputAxel22ControlKi)*0.001;
    }
    else updateFlag++;

    SensorValue=(float32)(*inputHydraulicTemperature-4000)*0.001;
    *outputMainTemperature=(sint32)(12500.0*SensorValue-50000.0);

    SensorValue=(float32)(*inputPressureSensorValueAxel11-4000)*0.001;
    *outputPressureAxel11=(sint32)(15625.0*SensorValue);
    SensorValue=(float32)(*inputPressureSensorValueAxel12-4000)*0.001;
    *outputPressureAxel12=(sint32)(15625.0*SensorValue);
    SensorValue=(float32)(*inputPressureSensorValueAxel21-4000)*0.001;
    *outputPressureAxel21=(sint32)(15625.0*SensorValue);
    SensorValue=(float32)(*inputPressureSensorValueAxel22-4000)*0.001;
    *outputPressureAxel22=(sint32)(15625.0*SensorValue);
    SensorValue=(float32)(*inputPressureSensorValueMain-4000)*0.001;
    *outputPressureMain=(sint32)(15625.0*SensorValue);

    *outputHubWeight=*outputPressureAxel11+*outputPressureAxel12+*outputPressureAxel21+*outputPressureAxel22;
    if(*outputHubWeight!=0){
        *outputHubCGPosL=(sint32)((float32)(*outputPressureAxel21+*outputPressureAxel22)*L/((float32)(*outputHubWeight))*1000.0);
        *outputHubCGPosB=(sint32)((float32)(*outputPressureAxel12+*outputPressureAxel22)*B/((float32)(*outputHubWeight))*1000.0);
    }
    *outputHubWeight=*outputHubWeight/4;

    if((*outputSetBypassValve&0x0000ffff)==0) *outputHubStatus|=KeyHubToMasterIsStop;
    else *outputHubStatus&=~KeyHubToMasterIsStop;

    if(*inputHubSystemGetSafetyControlWord&KeyHubSystemGetSafetyOnlySinken) *outputHubStatus|=KeyHubToMasterOnlySinken;
    else *outputHubStatus&=~KeyHubToMasterOnlySinken;
    if(*inputHubSystemGetSafetyControlWord&KeyHubSystemGetSafetyStop) *outputHubStatus|=KeyHubToMasterStopReq;
    else *outputHubStatus&=~KeyHubToMasterStopReq;



    if (*inputHydraulicInverterNodeStatus==NodeStatusPRE_OPERATIONAL){
        *outputHydraulicInverterNMT=NODE_START;
        *outputHydraulicInverterNMT=(*outputHydraulicInverterNMT<<8)+0x0001;
    }
}

//=================================================================================================
/*!
    Function: Task of the hub system
    output: None
*/
//=================================================================================================
void Task_HubSysManage(void* argv){
    argv=argv;
    uint32 timestamp_local;
    uint32 initFlag;

    Ts_Hub=0.02*(float)MaxToggleCounter;
    timestamp_local=x_sys_get_time_ms();
    initFlag=1;
    while(TRUE){
        if(initFlag){
            if((x_sys_get_time_ms()-timestamp_local)>5000){
                GetHubMeasurement();
                Axel11HubSetHeight=(float32)(*outputAxel11HubActualHeight);
                Axel12HubSetHeight=(float32)(*outputAxel12HubActualHeight);
                Axel21HubSetHeight=(float32)(*outputAxel21HubActualHeight);
                Axel22HubSetHeight=(float32)(*outputAxel22HubActualHeight);
                initFlag=0;
            }
        }

        if(*inputHubSystemControlWord&KeyHubSystemEnable){
            SetHubValueGenerate();
            StartHubInverter();
        }
        else{
            StopHubInverter();
        }
        HubParameterUpdate();
        if(HubSysTick>0) HubSysTick--;
        x_os_wait_for_events();
    }
}

//=================================================================================================
/*!
    Function: Initial of the hub system
    output: None
*/
//=================================================================================================
void InitHubSystem(void){
    InitInterfaceHubSys();
    x_os_install_task(PrioHubSySControl, 0, 0, Task_HubSysControl, 256);
    x_os_install_task(PrioHubSysManage, 500, 0, Task_HubSysManage, 128);
}

//=================================================================================================
/*!
    Function: Awake the Task from sleep state, the time interval of awake is activated by toggle bit
    output: 1: awake the hub system/ 0: not to awake the hub system
*/
//=================================================================================================
void HubSysAwake(void){
    HubSystemToggleBit[0]=*inputHydraulicMotorStatusByte&0x80;
    if(HubSystemToggleBit[0]!=HubSystemToggleBit[1]) HubSystemToggleCounter++;
    if(HubSystemToggleCounter>=MaxToggleCounter){
        x_os_set_events(Event_HubSysControl);
        HubSystemToggleCounter=0;
    }
    HubSystemToggleBit[1]=HubSystemToggleBit[0];

    /*static uint16 timeStamp;
    if(x_sys_get_time_ms()-timeStamp>20){
        timeStamp=x_sys_get_time_ms();
        x_os_set_events(Event_HubSysControl);
    }*/
}




