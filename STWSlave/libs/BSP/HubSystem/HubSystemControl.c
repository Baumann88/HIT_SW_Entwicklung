#include "HubSystem.h"
#include "HubSystemData.h"

#define ControlWordDriveEnable        0x0001
#define ControlWordContactorEnable    0x0002
#define ControlWordSafeStopActive     0x0040
#define ControlWordResetFault         0x8000
#define PinControlWordTestMode        0x01000000

#define valveMaxPWMUp                 8000.0
#define valveMaxPWMDown               8000.0
#define valveMinPWM                   2700.0
#define valveDeadPWM                  1000.0
#define valveDiffPWMUp                (valveMaxPWMUp-valveMinPWM)
#define valveDiffPWMDown              (valveMaxPWMDown-valveMinPWM)
#define HeightDeadZone                1
#define StepPWMUp                     500
#define StepPWMDown                   500

uint16 StopMotorFlag;
void resetAllController(void);
//=================================================================================================
/*!
    Function: start the Inverter of Hub system
    output: None
*/
//=================================================================================================
void StartHubInverter(void){
    sint16 tmpRPM;
    sint16 setRPM;

    if(*inputHydraulicMotorStatusByte&KeyPumpeCtrlWordSafeStop) {
        *outputHydraulicMotorControlWord=0x0000;
        HubSysTick=8;
    }
    else  *outputHydraulicMotorControlWord=0x0001;

    if(HubMode==KeyHubModeHeben) setRPM=*inputDefaultHydraulicMotorRPM;
    else if(HubMode==KeyHubModeSinken) setRPM=*inputDefaultHydraulicMotorRPM/3;
    else {setRPM=0;HubSysTick=8;}

    *outputSetHydraulicMotorSpeed=setRPM;

    if((*outputSetBypassValve&PinControlWordTestMode)==0){
        if(HubSysTick==0) *outputSetBypassValve=(*outputSetBypassValve&0xffff0000)+0x00000001;
        else *outputSetBypassValve&=0xffff0000;
    }

}

//=================================================================================================
/*!
    Function: stop the Inverter of Hub system
    output: None
*/
//=================================================================================================
void StopHubInverter(void){
    if((*outputSetBypassValve&PinControlWordTestMode)==0) *outputSetBypassValve&=0xffff0000;
    *outputHydraulicMotorControlWord=0x0000;
    HubSysTick=8;
    resetAllController();
}

//=================================================================================================
/*!
    Function: stop the Inverter of Hub system
    output: None
*/
//=================================================================================================
float32 MaxHubDiff(uint8 iAxel){
    float32 resValue;
    float32 tmp;
    float32 k;

    k=1.0;
    if(iAxel==1){
        resValue=(float32)(*outputAxel11HubActualHeight)-(float32)(*outputAxel12HubActualHeight);
        if(resValue<0.0) return 0.0;
        tmp=(float32)(*outputAxel11HubActualHeight)-(float32)(*outputAxel21HubActualHeight);
        if(tmp<0.0) return 0.0;
        if(resValue<tmp) resValue=tmp;
        tmp=(float32)(*outputAxel11HubActualHeight)-(float32)(*outputAxel22HubActualHeight);
        if(tmp<0.0) return 0.0;
        if(resValue<tmp) resValue=tmp;
        return resValue;
        //if(resValue>0.0) return resValue;
        //else return 0.0;
    }
    else if(iAxel==2){
        resValue=(float32)(*outputAxel12HubActualHeight)-(float32)(*outputAxel11HubActualHeight);
        return (resValue*k);
    }
    else if(iAxel==3){
        resValue=(float32)(*outputAxel21HubActualHeight)-(float32)(*outputAxel11HubActualHeight);
        return (resValue*k);
    }
    else if(iAxel==4){
        resValue=(float32)(*outputAxel22HubActualHeight)-(float32)(*outputAxel11HubActualHeight);
        return (resValue*k);
    }
}

//=================================================================================================
/*!
    Function: Get the Measurement Value
    output: None
*/
//=================================================================================================
void SetHubHeight(void){
    static uint8 setflag;
    uint8 samplingrate;
    uint16 hebenFlag,noAddFlag;
    float32 tmp;
    float32 MainRate;

    hebenFlag=1;
    samplingrate=5;
    MainRate=0.4;

    if(setflag==samplingrate){
        setflag=0;
        if(HubMode==KeyHubModeHeben){
            noAddFlag=0;
            if((HubVirtualHeight-Axel11HubSetHeight)>5.0) noAddFlag=1;
            if((HubVirtualHeight-Axel12HubSetHeight)>5.0) noAddFlag=1;
            if((HubVirtualHeight-Axel21HubSetHeight)>5.0) noAddFlag=1;
            if((HubVirtualHeight-Axel22HubSetHeight)>5.0) noAddFlag=1;
            if(noAddFlag) *outputHubStatus|=KeyHubToMasterSetHeightNoAdd;
            else *outputHubStatus&=~KeyHubToMasterSetHeightNoAdd;

            if((HubVirtualHeight-Axel11HubSetHeight)>0.0){
                tmp=(HubVirtualHeight-(float32)(*outputAxel11HubActualHeight))*0.5;
                if(tmp>5.0) tmp=5.0;
                tmp=MainRate*tmp-(1.0-MainRate)*MaxHubDiff(1);
                if(tmp>5.0) tmp=5.0;
                else if(tmp<=0.5) tmp=0.5;
                Axel11HubSetHeight+=tmp;
            }
            if((HubVirtualHeight-Axel12HubSetHeight)>0.0){
                tmp=(HubVirtualHeight-(float32)(*outputAxel12HubActualHeight))*0.5;
                if(tmp>5.0) tmp=5.0;
                tmp=MainRate*tmp-(1.0-MainRate)*MaxHubDiff(2);
                if(tmp>5.0) tmp=5.0;
                else if(tmp<=0.5) tmp=0.5;
                Axel12HubSetHeight+=tmp;
            }
            if((HubVirtualHeight-Axel21HubSetHeight)>0.0){
                tmp=(HubVirtualHeight-(float32)(*outputAxel21HubActualHeight))*0.5;
                if(tmp>5.0) tmp=5.0;
                tmp=MainRate*tmp-(1.0-MainRate)*MaxHubDiff(3);
                if(tmp>5.0) tmp=5.0;
                else if(tmp<=0.5) tmp=0.5;
                Axel21HubSetHeight+=tmp;
            }
            if((HubVirtualHeight-Axel22HubSetHeight)>0.0){
                tmp=(HubVirtualHeight-(float32)(*outputAxel22HubActualHeight))*0.5;
                if(tmp>5.0) tmp=5.0;
                tmp=MainRate*tmp-(1.0-MainRate)*MaxHubDiff(4);
                if(tmp>5.0) tmp=5.0;
                else if(tmp<=0.5) tmp=0.5;
                Axel22HubSetHeight+=tmp;
            }
        }
        else if(HubMode==KeyHubModeSinken){
            if(ControllerDatenAxel11.ek<-5.0) hebenFlag=0;
            if(ControllerDatenAxel12.ek<-5.0) hebenFlag=0;
            if(ControllerDatenAxel21.ek<-5.0) hebenFlag=0;
            if(ControllerDatenAxel22.ek<-5.0) hebenFlag=0;

            noAddFlag=0;
            if((HubVirtualHeight-Axel11HubSetHeight)<-5.0) noAddFlag=1;
            if((HubVirtualHeight-Axel12HubSetHeight)<-5.0) noAddFlag=1;
            if((HubVirtualHeight-Axel21HubSetHeight)<-5.0) noAddFlag=1;
            if((HubVirtualHeight-Axel22HubSetHeight)<-5.0) noAddFlag=1;
            if(noAddFlag) *outputHubStatus|=KeyHubToMasterSetHeightNoAdd;
            else *outputHubStatus&=~KeyHubToMasterSetHeightNoAdd;

            if((HubVirtualHeight-Axel11HubSetHeight)<-1.0){
                if(hebenFlag) Axel11HubSetHeight-=1.0;
            }
            if((HubVirtualHeight-Axel12HubSetHeight)<-1.0){
                if(hebenFlag) Axel12HubSetHeight-=1.0;
            }
            if((HubVirtualHeight-Axel21HubSetHeight)<-1.0){
                if(hebenFlag) Axel21HubSetHeight-=1.0;
            }
            if((HubVirtualHeight-Axel22HubSetHeight)<-1.0){
                if(hebenFlag) Axel22HubSetHeight-=1.0;
            }
        }
    }
    if(setflag<samplingrate) setflag++;

}

//=================================================================================================
/*!
    Function: Get the Measurement Value
    output: None
*/
//=================================================================================================
void GetHubMeasurement(void){
    static float32 HubHeightOldValve[4];
    float32 SensorValue;
    float32 Value;

    SensorValue=(float32)(*inputHeightSensor11);
    Value=SensorValue*HubSersor11FactA+HubSersor11FactB;
    *outputAxel11HubActualHeight=(uint32)Value;
    Axel11HubSpeed=(Value-HubHeightOldValve[0])/Ts_Hub;
    *outputSpeedHubAxel11=(sint32)(Axel11HubSpeed*1000.0);
    HubHeightOldValve[0]=Value;


    SensorValue=(float32)(*inputHeightSensor12);
    Value=SensorValue*HubSersor12FactA+HubSersor12FactB;
    *outputAxel12HubActualHeight=(uint32)Value;
    Axel12HubSpeed=(Value-HubHeightOldValve[1])/Ts_Hub;
    *outputSpeedHubAxel12=(sint32)(Axel12HubSpeed*1000.0);
    HubHeightOldValve[1]=Value;

    SensorValue=(float32)(*inputHeightSensor21);
    Value=SensorValue*HubSersor21FactA+HubSersor21FactB;
    *outputAxel21HubActualHeight=(uint32)Value;
    Axel21HubSpeed=(Value-HubHeightOldValve[2])/Ts_Hub;
    *outputSpeedHubAxel21=(sint32)(Axel21HubSpeed*1000.0);
    HubHeightOldValve[2]=Value;

    SensorValue=(float32)(*inputHeightSensor22);
    Value=SensorValue*HubSersor22FactA+HubSersor22FactB;
    *outputAxel22HubActualHeight=(uint32)Value;
    Axel22HubSpeed=(Value-HubHeightOldValve[3])/Ts_Hub;
    *outputSpeedHubAxel22=(sint32)(Axel22HubSpeed*1000.0);
    HubHeightOldValve[3]=Value;

    *outputHubHeight=(uint8)*outputAxel11HubActualHeight;
}

//=================================================================================================
/*!
    Function: reset all controller
    output: None
*/
//=================================================================================================
void resetAllController(void){
    ControllerDatenAxel11.ek_1=0.0;
    ControllerDatenAxel12.ek_1=0.0;
    ControllerDatenAxel21.ek_1=0.0;
    ControllerDatenAxel22.ek_1=0.0;
    ControllerDatenAxel11.yk_1=0.0;
    ControllerDatenAxel12.yk_1=0.0;
    ControllerDatenAxel21.yk_1=0.0;
    ControllerDatenAxel22.yk_1=0.0;

    if((*outputSetPWMValveHubRaiseAxel11&PinControlWordTestMode)==0) *outputSetPWMValveHubRaiseAxel11&=0xffff0000;
    if((*outputSetPWMValveHubRaiseAxel12&PinControlWordTestMode)==0) *outputSetPWMValveHubRaiseAxel12&=0xffff0000;
    if((*outputSetPWMValveHubRaiseAxel21&PinControlWordTestMode)==0) *outputSetPWMValveHubRaiseAxel21&=0xffff0000;
    if((*outputSetPWMValveHubRaiseAxel22&PinControlWordTestMode)==0) *outputSetPWMValveHubRaiseAxel22&=0xffff0000;

    if((*outputSetPWMValveHubSinkAxel11&PinControlWordTestMode)==0) *outputSetPWMValveHubSinkAxel11&=0xffff0000;
    if((*outputSetPWMValveHubSinkAxel12&PinControlWordTestMode)==0) *outputSetPWMValveHubSinkAxel12&=0xffff0000;
    if((*outputSetPWMValveHubSinkAxel21&PinControlWordTestMode)==0) *outputSetPWMValveHubSinkAxel21&=0xffff0000;
    if((*outputSetPWMValveHubSinkAxel22&PinControlWordTestMode)==0) *outputSetPWMValveHubSinkAxel22&=0xffff0000;
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
    uint32 PWMOutput;

    ControllerDatenAxel11.ek=Axel11HubSetHeight-(float32)(*outputAxel11HubActualHeight);
    if(HubMode==KeyHubModeHeben){
        if(ControllerDatenAxel11.ek<HeightDeadZone){
            ControllerDatenAxel11.ek=0.0;
            ControllerDatenAxel11.yk_1=0.0;
            StopMotorFlag++;
        }
        DeltaYk=ControllerDatenAxel11.kp*(ControllerDatenAxel11.ek-ControllerDatenAxel11.ek_1);
        DeltaYi=ControllerDatenAxel11.ek*ControllerDatenAxel11.ki*Ts_Hub;
        if(ControllerDatenAxel11.yk_1+DeltaYk+DeltaYi>=1.0) ControllerDatenAxel11.yk=1.0;
        else if(ControllerDatenAxel11.yk_1+DeltaYk+DeltaYi<=0.0) ControllerDatenAxel11.yk=0.0;
        else ControllerDatenAxel11.yk=ControllerDatenAxel11.yk_1+DeltaYk+DeltaYi;

        if(ControllerDatenAxel11.yk!=0.0) PWMOutput=(uint32)(valveDiffPWMUp*ControllerDatenAxel11.yk+valveMinPWM);
        else PWMOutput=valveDeadPWM;

        if(PWMOutput>ControllerDatenAxel11.PWM1) ControllerDatenAxel11.PWM1+=StepPWMUp;
        else if(PWMOutput<ControllerDatenAxel11.PWM1) ControllerDatenAxel11.PWM1-=StepPWMUp;
        if(ControllerDatenAxel11.yk==0.0) ControllerDatenAxel11.PWM1=PWMOutput;

        if((*outputSetPWMValveHubRaiseAxel11&PinControlWordTestMode)==0)
            *outputSetPWMValveHubRaiseAxel11=(*outputSetPWMValveHubRaiseAxel11&0xffff0000)+ControllerDatenAxel11.PWM1;
        if((*outputSetPWMValveHubSinkAxel11&PinControlWordTestMode)==0)
            *outputSetPWMValveHubSinkAxel11&=0xffff0000;
    }
    else if(HubMode==KeyHubModeSinken){
        if(ControllerDatenAxel11.ek>(0.0-HeightDeadZone)){
            ControllerDatenAxel11.ek=0.0;
            ControllerDatenAxel11.yk_1=0.0;
            StopMotorFlag++;
        }
        DeltaYk=ControllerDatenAxel11.kp*(ControllerDatenAxel11.ek-ControllerDatenAxel11.ek_1);
        DeltaYi=ControllerDatenAxel11.ek*ControllerDatenAxel11.ki*Ts_Hub;
        if(ControllerDatenAxel11.yk_1+DeltaYk+DeltaYi>=0.0) ControllerDatenAxel11.yk=0.0;
        else if(ControllerDatenAxel11.yk_1+DeltaYk+DeltaYi<=-1.0) ControllerDatenAxel11.yk=-1.0;
        else ControllerDatenAxel11.yk=ControllerDatenAxel11.yk_1+DeltaYk+DeltaYi;

        if(ControllerDatenAxel11.yk!=0.0) PWMOutput=(uint32)(valveDiffPWMDown*(0.0-ControllerDatenAxel11.yk)+valveMinPWM);
        else PWMOutput=valveDeadPWM;

        if(PWMOutput>ControllerDatenAxel11.PWM2) ControllerDatenAxel11.PWM2+=StepPWMDown;
        else if(PWMOutput<ControllerDatenAxel11.PWM2) ControllerDatenAxel11.PWM2-=StepPWMDown;
        if(ControllerDatenAxel11.yk==0.0) ControllerDatenAxel11.PWM2=PWMOutput;

        if((*outputSetPWMValveHubRaiseAxel11&PinControlWordTestMode)==0)
            *outputSetPWMValveHubRaiseAxel11&=0xffff0000;
        if((*outputSetPWMValveHubSinkAxel11&PinControlWordTestMode)==0)
            *outputSetPWMValveHubSinkAxel11=(*outputSetPWMValveHubSinkAxel11&0xffff0000)+ControllerDatenAxel11.PWM2;
    }
    ControllerDatenAxel11.ek_1=ControllerDatenAxel11.ek;
    ControllerDatenAxel11.yk_1=ControllerDatenAxel11.yk;
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
    uint32 PWMOutput;

    ControllerDatenAxel12.ek=Axel12HubSetHeight-(float32)(*outputAxel12HubActualHeight);
    if(HubMode==KeyHubModeHeben){
        if(ControllerDatenAxel12.ek<HeightDeadZone){
            ControllerDatenAxel12.ek=0.0;
            ControllerDatenAxel12.yk_1=0.0;
            StopMotorFlag++;
        }
        DeltaYk=ControllerDatenAxel12.kp*(ControllerDatenAxel12.ek-ControllerDatenAxel12.ek_1);
        DeltaYi=ControllerDatenAxel12.ek*ControllerDatenAxel12.ki*Ts_Hub;
        if(ControllerDatenAxel12.yk_1+DeltaYk+DeltaYi>=1.0) ControllerDatenAxel12.yk=1.0;
        else if(ControllerDatenAxel12.yk_1+DeltaYk+DeltaYi<=0.0) ControllerDatenAxel12.yk=0.0;
        else ControllerDatenAxel12.yk=ControllerDatenAxel12.yk_1+DeltaYk+DeltaYi;

        if(ControllerDatenAxel12.yk!=0.0) PWMOutput=(uint32)(valveDiffPWMUp*ControllerDatenAxel12.yk+valveMinPWM);
        else PWMOutput=valveDeadPWM;

        if(PWMOutput>ControllerDatenAxel12.PWM1) ControllerDatenAxel12.PWM1+=StepPWMUp;
        else if(PWMOutput<ControllerDatenAxel12.PWM1) ControllerDatenAxel12.PWM1-=StepPWMUp;
        if(ControllerDatenAxel12.yk==0.0) ControllerDatenAxel12.PWM1=PWMOutput;

        if((*outputSetPWMValveHubRaiseAxel12&PinControlWordTestMode)==0)
            *outputSetPWMValveHubRaiseAxel12=(*outputSetPWMValveHubRaiseAxel12&0xffff0000)+ControllerDatenAxel12.PWM1;
        if((*outputSetPWMValveHubSinkAxel12&PinControlWordTestMode)==0)
            *outputSetPWMValveHubSinkAxel12&=0xffff0000;
    }
    else if(HubMode==KeyHubModeSinken){
        if(ControllerDatenAxel12.ek>(0.0-HeightDeadZone)){
            ControllerDatenAxel12.ek=0.0;
            ControllerDatenAxel12.yk_1=0.0;
            StopMotorFlag++;
        }
        DeltaYk=ControllerDatenAxel12.kp*(ControllerDatenAxel12.ek-ControllerDatenAxel12.ek_1);
        DeltaYi=ControllerDatenAxel12.ek*ControllerDatenAxel12.ki*Ts_Hub;
        if(ControllerDatenAxel12.yk_1+DeltaYk+DeltaYi>=0.0) ControllerDatenAxel12.yk=0.0;
        else if(ControllerDatenAxel12.yk_1+DeltaYk+DeltaYi<=-1.0) ControllerDatenAxel12.yk=-1.0;
        else ControllerDatenAxel12.yk=ControllerDatenAxel12.yk_1+DeltaYk+DeltaYi;

        if(ControllerDatenAxel12.yk!=0.0) PWMOutput=(uint32)(valveDiffPWMDown*(0.0-ControllerDatenAxel12.yk)+valveMinPWM);
        else PWMOutput=valveDeadPWM;

        if(PWMOutput>ControllerDatenAxel12.PWM2) ControllerDatenAxel12.PWM2+=StepPWMDown;
        else if(PWMOutput<ControllerDatenAxel12.PWM2) ControllerDatenAxel12.PWM2-=StepPWMDown;
        if(ControllerDatenAxel12.yk==0.0) ControllerDatenAxel12.PWM2=PWMOutput;

        if((*outputSetPWMValveHubRaiseAxel12&PinControlWordTestMode)==0)
            *outputSetPWMValveHubRaiseAxel12&=0xffff0000;
        if((*outputSetPWMValveHubSinkAxel12&PinControlWordTestMode)==0)
            *outputSetPWMValveHubSinkAxel12=(*outputSetPWMValveHubSinkAxel12&0xffff0000)+ControllerDatenAxel12.PWM2;
    }
    ControllerDatenAxel12.ek_1=ControllerDatenAxel12.ek;
    ControllerDatenAxel12.yk_1=ControllerDatenAxel12.yk;
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
    uint32 PWMOutput;

    ControllerDatenAxel21.ek=Axel21HubSetHeight-(float32)(*outputAxel21HubActualHeight);
    if(HubMode==KeyHubModeHeben){
        if(ControllerDatenAxel21.ek<HeightDeadZone){
            ControllerDatenAxel21.ek=0.0;
            ControllerDatenAxel21.yk_1=0.0;
            StopMotorFlag++;
        }
        DeltaYk=ControllerDatenAxel21.kp*(ControllerDatenAxel21.ek-ControllerDatenAxel21.ek_1);
        DeltaYi=ControllerDatenAxel21.ek*ControllerDatenAxel21.ki*Ts_Hub;
        if(ControllerDatenAxel21.yk_1+DeltaYk+DeltaYi>=1.0) ControllerDatenAxel21.yk=1.0;
        else if(ControllerDatenAxel21.yk_1+DeltaYk+DeltaYi<=0.0) ControllerDatenAxel21.yk=0.0;
        else ControllerDatenAxel21.yk=ControllerDatenAxel21.yk_1+DeltaYk+DeltaYi;

        if(ControllerDatenAxel21.yk!=0.0) PWMOutput=(uint32)(valveDiffPWMUp*ControllerDatenAxel21.yk+valveMinPWM);
        else PWMOutput=valveDeadPWM;

        if(PWMOutput>ControllerDatenAxel21.PWM1) ControllerDatenAxel21.PWM1+=StepPWMUp;
        else if(PWMOutput<ControllerDatenAxel21.PWM1) ControllerDatenAxel21.PWM1-=StepPWMUp;
        if(ControllerDatenAxel21.yk==0.0) ControllerDatenAxel21.PWM1=PWMOutput;

        if((*outputSetPWMValveHubRaiseAxel21&PinControlWordTestMode)==0)
            *outputSetPWMValveHubRaiseAxel21=(*outputSetPWMValveHubRaiseAxel21&0xffff0000)+ControllerDatenAxel21.PWM1;
        if((*outputSetPWMValveHubSinkAxel21&PinControlWordTestMode)==0)
            *outputSetPWMValveHubSinkAxel21&=0xffff0000;
    }
    else if(HubMode==KeyHubModeSinken){
        if(ControllerDatenAxel21.ek>(0.0-HeightDeadZone)){
            ControllerDatenAxel21.ek=0.0;
            ControllerDatenAxel21.yk_1=0.0;
            StopMotorFlag++;
        }
        DeltaYk=ControllerDatenAxel21.kp*(ControllerDatenAxel21.ek-ControllerDatenAxel21.ek_1);
        DeltaYi=ControllerDatenAxel21.ek*ControllerDatenAxel21.ki*Ts_Hub;
        if(ControllerDatenAxel21.yk_1+DeltaYk+DeltaYi>=0.0) ControllerDatenAxel21.yk=0.0;
        else if(ControllerDatenAxel21.yk_1+DeltaYk+DeltaYi<=-1.0) ControllerDatenAxel21.yk=-1.0;
        else ControllerDatenAxel21.yk=ControllerDatenAxel21.yk_1+DeltaYk+DeltaYi;

        if(ControllerDatenAxel21.yk!=0.0) PWMOutput=(uint32)(valveDiffPWMDown*(0.0-ControllerDatenAxel21.yk)+valveMinPWM);
        else PWMOutput=valveDeadPWM;

        if(PWMOutput>ControllerDatenAxel21.PWM2) ControllerDatenAxel21.PWM2+=StepPWMDown;
        else if(PWMOutput<ControllerDatenAxel21.PWM2) ControllerDatenAxel21.PWM2-=StepPWMDown;
        if(ControllerDatenAxel21.yk==0.0) ControllerDatenAxel21.PWM2=PWMOutput;

        if((*outputSetPWMValveHubRaiseAxel21&PinControlWordTestMode)==0)
            *outputSetPWMValveHubRaiseAxel21&=0xffff0000;
        if((*outputSetPWMValveHubSinkAxel21&PinControlWordTestMode)==0)
            *outputSetPWMValveHubSinkAxel21=(*outputSetPWMValveHubSinkAxel21&0xffff0000)+ControllerDatenAxel21.PWM2;
    }
    ControllerDatenAxel21.ek_1=ControllerDatenAxel21.ek;
    ControllerDatenAxel21.yk_1=ControllerDatenAxel21.yk;
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
    uint32 PWMOutput;

    ControllerDatenAxel22.ek=Axel22HubSetHeight-(float32)(*outputAxel22HubActualHeight);
    if(HubMode==KeyHubModeHeben){
        if(ControllerDatenAxel22.ek<HeightDeadZone){
            ControllerDatenAxel22.ek=0.0;
            ControllerDatenAxel22.yk_1=0.0;
            StopMotorFlag++;
        }
        DeltaYk=ControllerDatenAxel22.kp*(ControllerDatenAxel22.ek-ControllerDatenAxel22.ek_1);
        DeltaYi=ControllerDatenAxel22.ek*ControllerDatenAxel22.ki*Ts_Hub;
        if(ControllerDatenAxel22.yk_1+DeltaYk+DeltaYi>=1.0) ControllerDatenAxel22.yk=1.0;
        else if(ControllerDatenAxel22.yk_1+DeltaYk+DeltaYi<=0.0) ControllerDatenAxel22.yk=0.0;
        else ControllerDatenAxel22.yk=ControllerDatenAxel22.yk_1+DeltaYk+DeltaYi;

        if(ControllerDatenAxel22.yk!=0.0) PWMOutput=(uint32)(valveDiffPWMUp*ControllerDatenAxel22.yk+valveMinPWM);
        else PWMOutput=valveDeadPWM;

        if(PWMOutput>ControllerDatenAxel22.PWM1) ControllerDatenAxel22.PWM1+=StepPWMUp;
        else if(PWMOutput<ControllerDatenAxel22.PWM1) ControllerDatenAxel22.PWM1-=StepPWMUp;
        if(ControllerDatenAxel22.yk==0.0) ControllerDatenAxel22.PWM1=PWMOutput;

        if((*outputSetPWMValveHubRaiseAxel22&PinControlWordTestMode)==0)
            *outputSetPWMValveHubRaiseAxel22=(*outputSetPWMValveHubRaiseAxel22&0xffff0000)+ControllerDatenAxel22.PWM1;
        if((*outputSetPWMValveHubSinkAxel22&PinControlWordTestMode)==0)
            *outputSetPWMValveHubSinkAxel22&=0xffff0000;
    }
    else if(HubMode==KeyHubModeSinken){
        if(ControllerDatenAxel22.ek>(0.0-HeightDeadZone)){
            ControllerDatenAxel22.ek=0.0;
            ControllerDatenAxel22.yk_1=0.0;
            StopMotorFlag++;
        }
        DeltaYk=ControllerDatenAxel22.kp*(ControllerDatenAxel22.ek-ControllerDatenAxel22.ek_1);
        DeltaYi=ControllerDatenAxel22.ek*ControllerDatenAxel22.ki*Ts_Hub;
        if(ControllerDatenAxel22.yk_1+DeltaYk+DeltaYi>=0.0) ControllerDatenAxel22.yk=0.0;
        else if(ControllerDatenAxel22.yk_1+DeltaYk+DeltaYi<=-1.0) ControllerDatenAxel22.yk=-1.0;
        else ControllerDatenAxel22.yk=ControllerDatenAxel22.yk_1+DeltaYk+DeltaYi;

        if(ControllerDatenAxel22.yk!=0.0) PWMOutput=(uint32)(valveDiffPWMDown*(0.0-ControllerDatenAxel22.yk)+valveMinPWM);
        else PWMOutput=valveDeadPWM;

        if(PWMOutput>ControllerDatenAxel22.PWM2) ControllerDatenAxel22.PWM2+=StepPWMDown;
        else if(PWMOutput<ControllerDatenAxel22.PWM2) ControllerDatenAxel22.PWM2-=StepPWMDown;
        if(ControllerDatenAxel22.yk==0.0) ControllerDatenAxel22.PWM2=PWMOutput;

        if((*outputSetPWMValveHubRaiseAxel22&PinControlWordTestMode)==0)
            *outputSetPWMValveHubRaiseAxel22&=0xffff0000;
        if((*outputSetPWMValveHubSinkAxel22&PinControlWordTestMode)==0)
            *outputSetPWMValveHubSinkAxel22=(*outputSetPWMValveHubSinkAxel22&0xffff0000)+ControllerDatenAxel22.PWM2;
    }
    ControllerDatenAxel22.ek_1=ControllerDatenAxel22.ek;
    ControllerDatenAxel22.yk_1=ControllerDatenAxel22.yk;
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
        if((u32_Events&Event_HubSysControl)!=0){
            GetHubMeasurement();
            if(*inputHubSystemControlWord&KeyHubSystemEnable){
                StopMotorFlag=0;
                SetHubHeight();
                ControllerAxel11();
                ControllerAxel12();
                ControllerAxel21();
                ControllerAxel22();
            }
            if(HubMode==KeyHubModeStop)
                resetAllController();
        }
                //if(StopMotorFlag==0){
                //    *outputSetHydraulicMotorSpeed=*inputDefaultHydraulicMotorRPM;
                //}
                //else *outputSetHydraulicMotorSpeed=0;
    }
}
