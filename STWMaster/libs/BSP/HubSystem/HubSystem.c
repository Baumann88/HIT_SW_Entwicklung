#include "HubSystem.h"
#include "HubSystemData.h"
#include "HubSystemInterface.h"

#define MaxToggleCounter                            1

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

    //Input
    inputHydraulicMotorStatusByte=BindODMem(HubSystemStartIndex,SubindexHubSystemControlWord,TypeU8,0); *inputHydraulicMotorStatusByte=0;
    inputHydraulicMotorActualSpeed=BindODMem(HubSystemStartIndex,SubindexHubInverterTPDO1LowDWord,TypeS16,1); *inputHydraulicMotorActualSpeed=0;

    inputHydraulicInverterNMTStatus=BindODMem(HubSystemStartIndex,SubindexHubInverterNodeStatus,TypeU8,0); *inputHydraulicInverterNMTStatus=0;
    inputHydraulicInverterNodeStatus=BindODMem(HubSystemStartIndex,SubindexHubInverterNodeStatus,TypeU8,1); *inputHydraulicInverterNodeStatus=0;
    inputHeightSensor11=BindODMem(IOPortStartIndex,SubindexInput01,TypeU16,0); *inputHeightSensor11=0;
    inputHeightSensor12=BindODMem(IOPortStartIndex,SubindexInput02,TypeU16,0); *inputHeightSensor12=0;
    inputHeightSensor21=BindODMem(IOPortStartIndex,SubindexInput03,TypeU16,0); *inputHeightSensor21=0;
    inputHeightSensor22=BindODMem(IOPortStartIndex,SubindexInput04,TypeU16,0); *inputHeightSensor22=0;
    inputHydraulicTemperature=BindODMem(IOPortStartIndex,SubindexInput14,TypeU16,0); *inputHydraulicTemperature=0;

    inputPressureSensorValueAxel11=BindODMem(IOPortStartIndex,SubindexInput09,TypeU16,0); *inputPressureSensorValueAxel11=0;
    inputPressureSensorValueAxel12=BindODMem(IOPortStartIndex,SubindexInput10,TypeU16,0); *inputPressureSensorValueAxel12=0;
    inputPressureSensorValueAxel21=BindODMem(IOPortStartIndex,SubindexInput11,TypeU16,0); *inputPressureSensorValueAxel21=0;
    inputPressureSensorValueAxel22=BindODMem(IOPortStartIndex,SubindexInput12,TypeU16,0); *inputPressureSensorValueAxel22=0;
    inputPressureSensorValueMain=BindODMem(IOPortStartIndex,SubindexInput08,TypeU16,0);  *inputPressureSensorValueMain=0;

    inputHeightSensor11FactA=BindODMem(HubSystemStartIndex,SubindexHeightSensor11FactA,TypeS32,0);
    inputHeightSensor11FactB=BindODMem(HubSystemStartIndex,SubindexHeightSensor11FactB,TypeS32,0);
    inputHeightSensor11FactC=BindODMem(HubSystemStartIndex,SubindexHeightSensor11FactC,TypeS32,0);
    inputHeightSensor11FactD=BindODMem(HubSystemStartIndex,SubindexHeightSensor11FactD,TypeS32,0);
    inputHeightSensor12FactA=BindODMem(HubSystemStartIndex,SubindexHeightSensor12FactA,TypeS32,0);
    inputHeightSensor12FactB=BindODMem(HubSystemStartIndex,SubindexHeightSensor12FactB,TypeS32,0);
    inputHeightSensor12FactC=BindODMem(HubSystemStartIndex,SubindexHeightSensor12FactC,TypeS32,0);
    inputHeightSensor12FactD=BindODMem(HubSystemStartIndex,SubindexHeightSensor12FactD,TypeS32,0);
    inputHeightSensor21FactA=BindODMem(HubSystemStartIndex,SubindexHeightSensor21FactA,TypeS32,0);
    inputHeightSensor21FactB=BindODMem(HubSystemStartIndex,SubindexHeightSensor21FactB,TypeS32,0);
    inputHeightSensor21FactC=BindODMem(HubSystemStartIndex,SubindexHeightSensor21FactC,TypeS32,0);
    inputHeightSensor21FactD=BindODMem(HubSystemStartIndex,SubindexHeightSensor21FactD,TypeS32,0);
    inputHeightSensor22FactA=BindODMem(HubSystemStartIndex,SubindexHeightSensor22FactA,TypeS32,0);
    inputHeightSensor22FactB=BindODMem(HubSystemStartIndex,SubindexHeightSensor22FactB,TypeS32,0);
    inputHeightSensor22FactC=BindODMem(HubSystemStartIndex,SubindexHeightSensor22FactC,TypeS32,0);
    inputHeightSensor22FactD=BindODMem(HubSystemStartIndex,SubindexHeightSensor22FactD,TypeS32,0);

    inputAxel11ControlKp=BindODMem(HubSystemStartIndex,SubindexControlKpAxel11,TypeS32,0);
    inputAxel11ControlKi=BindODMem(HubSystemStartIndex,SubindexControlKpAxel11,TypeS32,0);
    inputAxel12ControlKp=BindODMem(HubSystemStartIndex,SubindexControlKpAxel12,TypeS32,0);
    inputAxel12ControlKi=BindODMem(HubSystemStartIndex,SubindexControlKpAxel12,TypeS32,0);
    inputAxel21ControlKp=BindODMem(HubSystemStartIndex,SubindexControlKpAxel21,TypeS32,0);
    inputAxel21ControlKi=BindODMem(HubSystemStartIndex,SubindexControlKpAxel21,TypeS32,0);
    inputAxel22ControlKp=BindODMem(HubSystemStartIndex,SubindexControlKpAxel22,TypeS32,0);
    inputAxel22ControlKi=BindODMem(HubSystemStartIndex,SubindexControlKpAxel22,TypeS32,0);

    //Output
    outputHydraulicMotorControlWord=BindODMem(HubSystemStartIndex,SubindexHubInverterRPDO1LowDWord,TypeU16,0); *outputHydraulicMotorControlWord=0;
    outputSetHydraulicMotorSpeed=BindODMem(HubSystemStartIndex,SubindexHubInverterRPDO1LowDWord,TypeS16,1); *outputSetHydraulicMotorSpeed=0;
    outputHydraulicInverterNMT=BindODMem(HubSystemStartIndex,SubindexHubInverterNMT,TypeU16,0); *outputHydraulicInverterNMT=0;

    //outputSetBypassValve=BindODMem(IOPortStartIndex,SubindexOutput24,TypeU32,0); *outputSetBypassValve&=0x11110000;

    outputSetPWMValveHubRaiseAxel11=BindODMem(IOPortStartIndex,SubindexOutput01,TypeU32,0); *outputSetPWMValveHubRaiseAxel11&=0x11110000;
    outputSetPWMValveHubRaiseAxel12=BindODMem(IOPortStartIndex,SubindexOutput02,TypeU32,0); *outputSetPWMValveHubRaiseAxel12&=0x11110000;
    outputSetPWMValveHubRaiseAxel21=BindODMem(IOPortStartIndex,SubindexOutput04,TypeU32,0); *outputSetPWMValveHubRaiseAxel21&=0x11110000;
    outputSetPWMValveHubRaiseAxel22=BindODMem(IOPortStartIndex,SubindexOutput06,TypeU32,0); *outputSetPWMValveHubRaiseAxel22&=0x11110000;

    outputSetPWMValveHubSinkAxel11=BindODMem(IOPortStartIndex,SubindexOutput01,TypeU32,0); *outputSetPWMValveHubSinkAxel11&=0x11110000;
    outputSetPWMValveHubSinkAxel12=BindODMem(IOPortStartIndex,SubindexOutput03,TypeU32,0); *outputSetPWMValveHubSinkAxel12&=0x11110000;
    outputSetPWMValveHubSinkAxel21=BindODMem(IOPortStartIndex,SubindexOutput05,TypeU32,0); *outputSetPWMValveHubSinkAxel21&=0x11110000;
    outputSetPWMValveHubSinkAxel22=BindODMem(IOPortStartIndex,SubindexOutput07,TypeU32,0); *outputSetPWMValveHubSinkAxel22&=0x11110000;

    //height of the hydraulic axle
    outputAxel11HubActualHeight=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel11,TypeU32,0); *outputAxel11HubActualHeight=0;
    outputAxel12HubActualHeight=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel12,TypeU32,0); *outputAxel12HubActualHeight=0;
    outputAxel21HubActualHeight=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel21,TypeU32,0); *outputAxel21HubActualHeight=0;
    outputAxel22HubActualHeight=BindODMem(HubSystemStartIndex,SubindexHeightHubAxel22,TypeU32,0); *outputAxel22HubActualHeight=0;

    //Value of pressure
    outputPressureAxel11=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel11,TypeS32,0); *outputPressureAxel11=0;
    outputPressureAxel12=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel12,TypeS32,0); *outputPressureAxel12=0;
    outputPressureAxel21=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel21,TypeS32,0); *outputPressureAxel21=0;
    outputPressureAxel22=BindODMem(HubSystemStartIndex,SubindexPressureSensorAxel22,TypeS32,0); *outputPressureAxel22=0;
    outputPressureMain=BindODMem(HubSystemStartIndex,SubindexPressureSensorPump,TypeS32,0); *outputPressureMain=0;

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
    uint16 tmp;
    float32 SetHeightPercent;
    tmp=(uint16)(*inputHubSystemControlWord&0xff00>>8);
    SetHeightPercent=(float32)tmp/100.0;

    if(*inputHubSystemControlWord&KeyHubSystemTestMode){
        if ((*inputHubSystemControlWord&0x0000ff00>>8)==1) Axel11HubSetHeight=SetHeightPercent*(*inputMaxHeight-*inputMinHeight);
        else if((*inputHubSystemControlWord&0x0000ff00>>8)==2) Axel12HubSetHeight=SetHeightPercent*(*inputMaxHeight-*inputMinHeight);
        else if((*inputHubSystemControlWord&0x0000ff00>>8)==3) Axel21HubSetHeight=SetHeightPercent*(*inputMaxHeight-*inputMinHeight);
        else if((*inputHubSystemControlWord&0x0000ff00>>8)==4) Axel22HubSetHeight=SetHeightPercent*(*inputMaxHeight-*inputMinHeight);
    }
    else if(*inputHubSystemControlWord&KeyHubSystemNormalMode){
        Axel11HubSetHeight=SetHeightPercent*(*inputMaxHeight-*inputMinHeight);
        Axel12HubSetHeight=Axel11HubSetHeight;
        Axel21HubSetHeight=Axel11HubSetHeight;
        Axel22HubSetHeight=Axel11HubSetHeight;
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
    Ts_Hub=0.012*(float)MaxToggleCounter;
    while(TRUE){
        if(*inputHubSystemControlWord&KeyHubSystemEnable){
            SetHubValueGenerate();
            StartHubInverter();
        }
        else StopHubInverter();
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
}




