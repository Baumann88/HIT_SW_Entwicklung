#include "HubSystem.h"
#include "HubSystemData.h"

#define ControlWordDriveEnable        0x0001
#define ControlWordContactorEnable    0x0002
#define ControlWordSafeStopActive     0x0040
#define ControlWordResetFault         0x8000
#define PinControlWordTestMode        0x01000000

#define valveMaxPWM                   10000.0
#define valveMinPWM                   3000.0
#define HeightDeadZone                10


typedef struct{
    //Parameter in Cascade PI-Controller
    float32 ek;
    float32 yk;
    float32 yk_1;
    float32 ek_1;
}TypeHubControllerDaten;

static TypeHubControllerDaten ControllerDatenAxel11={0.0f,0.0f,0.0f,0.0f};
static TypeHubControllerDaten ControllerDatenAxel12={0.0f,0.0f,0.0f,0.0f};
static TypeHubControllerDaten ControllerDatenAxel21={0.0f,0.0f,0.0f,0.0f};
static TypeHubControllerDaten ControllerDatenAxel22={0.0f,0.0f,0.0f,0.0f};

//=================================================================================================
/*!
    Function: start the Inverter of Hub system
    output: None
*/
//=================================================================================================
void StartHubInverter(void){
    if (*inputHydraulicInverterNodeStatus==NodeStatusPRE_OPERATIONAL){
        *outputHydraulicInverterNMT=NODE_START;
        *outputHydraulicInverterNMT=(*outputHydraulicInverterNMT<<8)+0x0001;
    }
    *outputHydraulicMotorControlWord=ControlWordDriveEnable&(~ControlWordSafeStopActive)&(~ControlWordResetFault);
    *inputHydraulicMotorActualSpeed=*inputDefaultHydraulicMotorRPM;
    if(*outputSetBypassValve&PinControlWordTestMode==0)
        *outputSetBypassValve=*outputSetBypassValve&0xffff0000+0x00000001;

}

//=================================================================================================
/*!
    Function: stop the Inverter of Hub system
    output: None
*/
//=================================================================================================
void StopHubInverter(void){
    *outputHydraulicMotorControlWord=(~ControlWordDriveEnable)&(~ControlWordSafeStopActive)&(~ControlWordResetFault);
    *inputHydraulicMotorActualSpeed=0;
    if(*outputSetBypassValve&PinControlWordTestMode==0)
        *outputSetBypassValve&=0xffff0000;
}



//=================================================================================================
/*!
    Function: Get the Measurement Value
    output: None
*/
//=================================================================================================
void GetHubMeasurement(void){
    float32 SensorValue;
    float32 Value;
    float32 FactA;
    float32 FactB;
    float32 FactC;
    float32 FactD;

    FactA=(float32)(*inputHeightSensor11FactA)*0.001;
    FactB=(float32)(*inputHeightSensor11FactB)*0.001;
    FactC=(float32)(*inputHeightSensor11FactC)*0.001;
    FactD=(float32)(*inputHeightSensor11FactD)*0.001;
    SensorValue=(float32)(*inputHeightSensor11);
    Value=pow(SensorValue,3.0)*FactA+pow(SensorValue,2.0)*FactB+SensorValue*FactC+FactD;
    *outputAxel11HubActualHeight=(uint32)Value;


    FactA=(float32)(*inputHeightSensor12FactA)*0.001;
    FactB=(float32)(*inputHeightSensor12FactB)*0.001;
    FactC=(float32)(*inputHeightSensor12FactC)*0.001;
    FactD=(float32)(*inputHeightSensor12FactD)*0.001;
    SensorValue=(float32)(*inputHeightSensor12);
    Value=pow(SensorValue,3.0)*FactA+pow(SensorValue,2.0)*FactB+SensorValue*FactC+FactD;
    *outputAxel12HubActualHeight=(uint32)Value;

    FactA=(float32)(*inputHeightSensor21FactA)*0.001;
    FactB=(float32)(*inputHeightSensor21FactB)*0.001;
    FactC=(float32)(*inputHeightSensor21FactC)*0.001;
    FactD=(float32)(*inputHeightSensor21FactD)*0.001;
    SensorValue=(float32)(*inputHeightSensor21);
    Value=pow(SensorValue,3.0)*FactA+pow(SensorValue,2.0)*FactB+SensorValue*FactC+FactD;
    *outputAxel21HubActualHeight=(uint32)Value;

    FactA=(float32)(*inputHeightSensor22FactA)*0.001;
    FactB=(float32)(*inputHeightSensor22FactB)*0.001;
    FactC=(float32)(*inputHeightSensor22FactC)*0.001;
    FactD=(float32)(*inputHeightSensor22FactD)*0.001;
    SensorValue=(float32)(*inputHeightSensor22);
    Value=pow(SensorValue,3.0)*FactA+pow(SensorValue,2.0)*FactB+SensorValue*FactC+FactD;
    *outputAxel22HubActualHeight=(uint32)Value;

    SensorValue=(float32)(*inputPressureSensorValueAxel11)*0.001;
    *outputPressureAxel11=(sint32)((15.625*SensorValue-62.5)*1000.0);
    SensorValue=(float32)(*inputPressureSensorValueAxel12)*0.001;
    *outputPressureAxel12=(sint32)((15.625*SensorValue-62.5)*1000.0);
    SensorValue=(float32)(*inputPressureSensorValueAxel21)*0.001;
    *outputPressureAxel21=(sint32)((15.625*SensorValue-62.5)*1000.0);
    SensorValue=(float32)(*inputPressureSensorValueAxel22)*0.001;
    *outputPressureAxel22=(sint32)((15.625*SensorValue-62.5)*1000.0);
    SensorValue=(float32)(*inputPressureSensorValueMain)*0.001;
    *outputPressureMain=(sint32)((15.625*SensorValue-62.5)*1000.0);

    SensorValue=(float32)(*inputHydraulicTemperature)*0.001;
    *outputMainTemperature=(sint32)((15.625*SensorValue-62.5)*1000.0);
}


//=================================================================================================
/*!
    Function: Cascade-Controller for Axel11
    output: None
*/
//=================================================================================================
void ControllerAxel11(void){
    float32 DeltaYk;
    float32 DeltaYi;
    float32 Kp,Ki;
    uint32 PWMOutput;

    //calculate the control error of the steering angle
    ControllerDatenAxel11.ek=Axel11HubSetHeight-(float32)(*outputAxel11HubActualHeight);
    if((ControllerDatenAxel11.ek<HeightDeadZone)&&(ControllerDatenAxel11.ek>(0.0-HeightDeadZone)))
        ControllerDatenAxel11.ek=0.0;

    Kp=(float32)(*inputAxel11ControlKp)*0.001;
    Ki=(float32)(*inputAxel11ControlKi)*0.001;
    DeltaYk=Kp*(ControllerDatenAxel11.ek-ControllerDatenAxel11.ek_1);
    DeltaYi=ControllerDatenAxel11.ek*Ki*Ts_Hub;

    if(ControllerDatenAxel11.yk_1+DeltaYk+DeltaYi>=1.0)
        ControllerDatenAxel11.yk=1.0;
    else if(ControllerDatenAxel11.yk_1+DeltaYk+DeltaYi<=-1.0)
        ControllerDatenAxel11.yk=-1.0;
    else
        ControllerDatenAxel11.yk=ControllerDatenAxel11.yk_1+DeltaYk+DeltaYi;

    ControllerDatenAxel11.ek_1=ControllerDatenAxel11.ek;
    ControllerDatenAxel11.yk_1=ControllerDatenAxel11.yk;

    if(ControllerDatenAxel11.yk>=0.0){
        PWMOutput=(uint32)((valveMaxPWM-valveMinPWM)*ControllerDatenAxel11.yk+valveMinPWM);
        if(*outputSetPWMValveHubRaiseAxel11&PinControlWordTestMode==0)
            *outputSetPWMValveHubRaiseAxel11=*outputSetPWMValveHubRaiseAxel11&0xffff0000+PWMOutput&0x0000ffff;
        if(*outputSetPWMValveHubSinkAxel11&PinControlWordTestMode==0)
            *outputSetPWMValveHubSinkAxel11&=0xffff0000;
    }
    else{
        PWMOutput=0-(uint32)((valveMaxPWM-valveMinPWM)*ControllerDatenAxel11.yk-valveMinPWM);
        if(*outputSetPWMValveHubRaiseAxel11&PinControlWordTestMode==0)
            *outputSetPWMValveHubRaiseAxel11&=0xffff0000;
        if(*outputSetPWMValveHubSinkAxel11&PinControlWordTestMode==0)
            *outputSetPWMValveHubSinkAxel11=*outputSetPWMValveHubSinkAxel11&0xffff0000+PWMOutput&0x0000ffff;
    }
}

//=================================================================================================
/*!
    Function: Cascade-Controller for Axel12
    output: None
*/
//=================================================================================================
void ControllerAxel12(void){
    float32 DeltaYk;
    float32 DeltaYi;
    float32 Kp,Ki;
    uint32 PWMOutput;

    //calculate the control error of the steering angle
    ControllerDatenAxel12.ek=Axel12HubSetHeight-(float32)(*outputAxel12HubActualHeight);
    if((ControllerDatenAxel12.ek<HeightDeadZone)&&(ControllerDatenAxel12.ek>(0.0-HeightDeadZone)))
        ControllerDatenAxel12.ek=0.0;

    Kp=(float32)(*inputAxel12ControlKp)*0.001;
    Ki=(float32)(*inputAxel12ControlKi)*0.001;

    DeltaYk=Kp*(ControllerDatenAxel12.ek-ControllerDatenAxel12.ek_1);
    DeltaYi=ControllerDatenAxel12.ek*Ki*Ts_Hub;

    if(ControllerDatenAxel12.yk_1+DeltaYk+DeltaYi>=1.0)
        ControllerDatenAxel12.yk=1.0;
    else if(ControllerDatenAxel12.yk_1+DeltaYk+DeltaYi<=-1.0)
        ControllerDatenAxel12.yk=-1.0;
    else
        ControllerDatenAxel12.yk=ControllerDatenAxel12.yk_1+DeltaYk+DeltaYi;

    ControllerDatenAxel12.ek_1=ControllerDatenAxel12.ek;
    ControllerDatenAxel12.yk_1=ControllerDatenAxel12.yk;

    if(ControllerDatenAxel12.yk>=0.0){
        PWMOutput=(uint32)((valveMaxPWM-valveMinPWM)*ControllerDatenAxel12.yk+valveMinPWM);
        if(*outputSetPWMValveHubRaiseAxel12&PinControlWordTestMode==0)
            *outputSetPWMValveHubRaiseAxel12=*outputSetPWMValveHubRaiseAxel12&0xffff0000+PWMOutput&0x0000ffff;
        if(*outputSetPWMValveHubSinkAxel12&PinControlWordTestMode==0)
            *outputSetPWMValveHubSinkAxel12&=0xffff0000;
    }
    else{
        PWMOutput=0-(uint32)((valveMaxPWM-valveMinPWM)*ControllerDatenAxel12.yk-valveMinPWM);
        if(*outputSetPWMValveHubRaiseAxel12&PinControlWordTestMode==0)
            *outputSetPWMValveHubRaiseAxel12&=0xffff0000;
        if(*outputSetPWMValveHubSinkAxel12&PinControlWordTestMode==0)
            *outputSetPWMValveHubSinkAxel12=*outputSetPWMValveHubSinkAxel12&0xffff0000+PWMOutput&0x0000ffff;
    }
}

//=================================================================================================
/*!
    Function: Cascade-Controller for Axel21
    output: None
*/
//=================================================================================================
void ControllerAxel21(void){
    float32 DeltaYk;
    float32 DeltaYi;
    float32 Kp,Ki;
    uint32 PWMOutput;

    //calculate the control error of the steering angle
    ControllerDatenAxel21.ek=Axel21HubSetHeight-(float32)(*outputAxel21HubActualHeight);
    if((ControllerDatenAxel21.ek<HeightDeadZone)&&(ControllerDatenAxel21.ek>(0.0-HeightDeadZone)))
        ControllerDatenAxel21.ek=0.0;

    Kp=(float32)(*inputAxel21ControlKp)*0.001;
    Ki=(float32)(*inputAxel21ControlKi)*0.001;

    DeltaYk=Kp*(ControllerDatenAxel21.ek-ControllerDatenAxel21.ek_1);
    DeltaYi=ControllerDatenAxel21.ek*Ki*Ts_Hub;

    if(ControllerDatenAxel21.yk_1+DeltaYk+DeltaYi>=1.0)
        ControllerDatenAxel21.yk=1.0;
    else if(ControllerDatenAxel21.yk_1+DeltaYk+DeltaYi<=-1.0)
        ControllerDatenAxel21.yk=-1.0;
    else
        ControllerDatenAxel21.yk=ControllerDatenAxel21.yk_1+DeltaYk+DeltaYi;

    ControllerDatenAxel21.ek_1=ControllerDatenAxel21.ek;
    ControllerDatenAxel21.yk_1=ControllerDatenAxel21.yk;

    if(ControllerDatenAxel21.yk>=0.0){
        PWMOutput=(uint32)((valveMaxPWM-valveMinPWM)*ControllerDatenAxel21.yk+valveMinPWM);
        if(*outputSetPWMValveHubRaiseAxel21&PinControlWordTestMode==0)
            *outputSetPWMValveHubRaiseAxel21=*outputSetPWMValveHubRaiseAxel21&0xffff0000+PWMOutput&0x0000ffff;
        if(*outputSetPWMValveHubSinkAxel21&PinControlWordTestMode==0)
            *outputSetPWMValveHubSinkAxel21&=0xffff0000;
    }
    else{
        PWMOutput=0-(uint32)((valveMaxPWM-valveMinPWM)*ControllerDatenAxel21.yk-valveMinPWM);
        if(*outputSetPWMValveHubRaiseAxel21&PinControlWordTestMode==0)
            *outputSetPWMValveHubRaiseAxel21&=0xffff0000;
        if(*outputSetPWMValveHubSinkAxel21&PinControlWordTestMode==0)
            *outputSetPWMValveHubSinkAxel21=*outputSetPWMValveHubSinkAxel21&0xffff0000+PWMOutput&0x0000ffff;
    }
}

//=================================================================================================
/*!
    Function: Cascade-Controller for Axel22
    output: None
*/
//=================================================================================================
void ControllerAxel22(void){
    float32 DeltaYk;
    float32 DeltaYi;
    float32 Kp,Ki;
    uint32 PWMOutput;

    //calculate the control error of the steering angle
    ControllerDatenAxel22.ek=Axel22HubSetHeight-(float32)(*outputAxel22HubActualHeight);
    if((ControllerDatenAxel22.ek<HeightDeadZone)&&(ControllerDatenAxel22.ek>(0.0-HeightDeadZone)))
        ControllerDatenAxel22.ek=0.0;

    Kp=(float32)(*inputAxel22ControlKp)*0.001;
    Ki=(float32)(*inputAxel22ControlKi)*0.001;

    DeltaYk=Kp*(ControllerDatenAxel22.ek-ControllerDatenAxel22.ek_1);
    DeltaYi=ControllerDatenAxel22.ek*Ki*Ts_Hub;

    if(ControllerDatenAxel22.yk_1+DeltaYk+DeltaYi>=1.0)
        ControllerDatenAxel22.yk=1.0;
    else if(ControllerDatenAxel22.yk_1+DeltaYk+DeltaYi<=-1.0)
        ControllerDatenAxel22.yk=-1.0;
    else
        ControllerDatenAxel22.yk=ControllerDatenAxel22.yk_1+DeltaYk+DeltaYi;

    ControllerDatenAxel22.ek_1=ControllerDatenAxel22.ek;
    ControllerDatenAxel22.yk_1=ControllerDatenAxel22.yk;

    if(ControllerDatenAxel22.yk>=0.0){
        PWMOutput=(uint32)((valveMaxPWM-valveMinPWM)*ControllerDatenAxel22.yk+valveMinPWM);
        if(*outputSetPWMValveHubRaiseAxel22&PinControlWordTestMode==0)
            *outputSetPWMValveHubRaiseAxel22=*outputSetPWMValveHubRaiseAxel22&0xffff0000+PWMOutput&0x0000ffff;
        if(*outputSetPWMValveHubSinkAxel22&PinControlWordTestMode==0)
            *outputSetPWMValveHubSinkAxel22&=0xffff0000;
    }
    else{
        PWMOutput=0-(uint32)((valveMaxPWM-valveMinPWM)*ControllerDatenAxel22.yk-valveMinPWM);
        if(*outputSetPWMValveHubRaiseAxel22&PinControlWordTestMode==0)
            *outputSetPWMValveHubRaiseAxel22&=0xffff0000;
        if(*outputSetPWMValveHubSinkAxel22&PinControlWordTestMode==0)
            *outputSetPWMValveHubSinkAxel22=*outputSetPWMValveHubSinkAxel22&0xffff0000+PWMOutput&0x0000ffff;
    }
}

//=================================================================================================
/*!
    Function: this is a task for control of the Hub system
    output: None
*/
//=================================================================================================
void Task_HubSysControl(void* argv){
    argv=argv;
    uint32 u32_Events;

    x_os_set_event_mask(Event_HubSysControl);

    while(TRUE){
        x_os_wait_for_events();
        u32_Events = x_os_get_events(); // get events
        if(*inputHubSystemControlWord&KeyHubSystemEnable){
            if((u32_Events&Event_HubSysControl)!=0){
                GetHubMeasurement();
                if(*inputHubSystemControlWord&KeyHubSystemTestMode){
                    if ((*inputHubSystemControlWord&0x0000ff00>>8)==1) ControllerAxel11();
                    else if((*inputHubSystemControlWord&0x0000ff00>>8)==2) ControllerAxel12();
                    else if((*inputHubSystemControlWord&0x0000ff00>>8)==3) ControllerAxel21();
                    else if((*inputHubSystemControlWord&0x0000ff00>>8)==4) ControllerAxel22();
                }
                else if(*inputHubSystemControlWord&KeyHubSystemNormalMode){
                    ControllerAxel11();
                    ControllerAxel12();
                    ControllerAxel21();
                    ControllerAxel22();
                }
            }
        }
    }
}
