#include "RemoteControl.h"
#include "RemoteControlInterface.h"
#include "RemoteControlData.h"

#define RCPinControlWordTestMode        0x01000000
#define RCPinControlWordIsUsed          0x02000000
#define OmegaMotionMode                 0.2  //rad^2
#define AngleOffsetMotion               (6.0/180.0*pi)

#define KeyDriveModePark                0
#define KeyDriveModeAllrad              1
#define KeyDriveModeVorderrad           2
#define KeyDriveModeHinterrad           3
#define KeyDriveModeKrebsgang           4
#define KeyDriveModeRundgang            5

#define MaxRCToggleCounter              2

//value of the joystick
static float32 XValue;
static sint16 Y1Value;
static float32 Y2Value;
static float32 ZValue;
//Maximal steering angle
static float32 MaxDriveAngle;

uint16 tick;

//drive mode
static uint8 DriveMode;
//drive omega
static float32 MaxDriveOmega;
//maximal drive speed
static float32 MaxDriveSpeed;
//old Toggle Byte
static uint8 OldToggleByte;
//counter of the ToggleByte
static uint16 RCtogglecounter;
//time stamp for the RC
static uint32 timeStampRC;
//time stamp for the state Initial timeout
static uint32 timeStampInitFinish;
//old record of the Digital Input
static uint32 oldDigitalIn;

//=================================================================================================
/*!
    Function: generate the Interface
    output: None
*/
//=================================================================================================
void InitInterfaceRemoteControl(void){
    inputRemoteControlXVar=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlTPDO1LowDWord,TypeU8,0);
    inputRemoteControlY1Var=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlTPDO1LowDWord,TypeU8,1);
    inputRemoteControlY2Var=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlTPDO1LowDWord,TypeU8,2);
    inputRemoteControlZVar=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlTPDO1HighDWord,TypeU8,0);
    inputRemoteControlSpeedPoti=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlTPDO1LowDWord,TypeU8,3);
    inputRemoteControlDigitalIn=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlTPDO2LowDWord,TypeU32,0);
    inputRemoteControlToggle=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlTPDO2HighDWord,TypeU8,2);

    outputRCSetDriveSysSpeed=BindODMem(DriveModuleStartIndex,SubindexDriveSysSetSpeed,TypeF32,0); *outputRCSetDriveSysSpeed=0.0;
    outputRCSetDriveSysAngle=BindODMem(DriveModuleStartIndex,SubindexDriveSysSetAngle,TypeF32,0); *outputRCSetDriveSysAngle=0.0;

    inputRCJoystickXFactA=BindODMem(DriveModuleStartIndex,SubindexXJoystickCurveParaA,TypeS32,0);
    inputRCJoystickXFactB=BindODMem(DriveModuleStartIndex,SubindexXJoystickCurveParaB,TypeS32,0);
    inputRCJoystickXFactC=BindODMem(DriveModuleStartIndex,SubindexXJoystickCurveParaC,TypeS32,0);
    inputRCJoystickXFactD=BindODMem(DriveModuleStartIndex,SubindexXJoystickCurveParaD,TypeS32,0);


    inputHubsystemHeight=BindODMem(RemoteControlStartIndex,SubindexTelegramm1FromSlaveLowWord,TypeU8,1); *inputHubsystemHeight=0x00;
    inputHubsystemStatus=BindODMem(RemoteControlStartIndex,SubindexTelegramm1FromSlaveLowWord,TypeU8,0); *inputHubsystemStatus=0x00;

    outputRCSetDriveSysControlWord=BindODMem(DriveModuleStartIndex,SubindexDriveSysControlWord,TypeU32,0); *outputRCSetDriveSysControlWord=0;
    outputRCSetHubSysControlWord=BindODMem(HubSystemStartIndex,SubindexHubSystemControlWord,TypeU32,0); *outputRCSetHubSysControlWord=0;
    outputRCSetSafetyControlWord=BindODMem(SafetyStartIndex,SubindexSafetyControlWord,TypeU32,0); *outputRCSetSafetyControlWord=0;
    outputRCSetAutoDriveControlWord=BindODMem(AutoDriveStartIndex,SubindexAutoDriveControlWord,TypeU32,0); *outputRCSetAutoDriveControlWord=0;
    inputRCGetSlaveSafetyControlWord=BindODMem(RemoteControlStartIndex,SubindexTelegramm1FromSlaveHighWord,TypeU32,0); *inputRCGetSlaveSafetyControlWord=0;

    outputRemoteControlNMT=BindODMem(RemoteControlStartIndex,SubindexRemoteCtrlNMT,TypeU32,0); *outputRemoteControlNMT=0;

    outputIOPortHupe=BindODMem(IOPortStartIndex,SubindexOutput53,TypeU32,0);

    outputIOPortLampe11=BindODMem(IOPortStartIndex,SubindexOutput54,TypeU32,0);
    outputIOPortLampe12=BindODMem(IOPortStartIndex,SubindexOutput55,TypeU32,0);
    outputIOPortLampe21=BindODMem(IOPortStartIndex,SubindexOutput57,TypeU32,0);
    outputIOPortLampe22=BindODMem(IOPortStartIndex,SubindexOutput56,TypeU32,0);

    //Angle of drive system to slave
    outputRCToSlaveDriveSysAngle11=BindODMem(RemoteControlStartIndex,SubindexTelegramm1ToSlaveLowWord,TypeS8,0); *outputRCToSlaveDriveSysAngle11=0;
    outputRCToSlaveDriveSysAngle12=BindODMem(RemoteControlStartIndex,SubindexTelegramm1ToSlaveLowWord,TypeS8,1); *outputRCToSlaveDriveSysAngle12=0;
    outputRCToSlaveDriveSysAngle21=BindODMem(RemoteControlStartIndex,SubindexTelegramm1ToSlaveLowWord,TypeS8,2); *outputRCToSlaveDriveSysAngle21=0;
    outputRCToSlaveDriveSysAngle22=BindODMem(RemoteControlStartIndex,SubindexTelegramm1ToSlaveLowWord,TypeS8,3); *outputRCToSlaveDriveSysAngle22=0;

    outputRCToSlaveStatusMES=BindODMem(RemoteControlStartIndex,SubindexTelegramm1ToSlaveHighWord,TypeU8,1); *outputRCToSlaveStatusMES=0x00;
    outputRCToSlaveStatusExtMES=BindODMem(RemoteControlStartIndex,SubindexTelegramm2ToSlaveHighWord,TypeU8,1); *outputRCToSlaveStatusExtMES=0x00;
    outputRCToSlavePageState=BindODMem(RemoteControlStartIndex,SubindexTelegramm1ToSlaveHighWord,TypeU8,3); *outputRCToSlavePageState=0x00;
    outputRCToSlaveStatusAuto=BindODMem(RemoteControlStartIndex,SubindexTelegramm1ToSlaveHighWord,TypeU8,2); *outputRCToSlaveStatusAuto=0x00;
    outputRCToSlaveSteeringMode=BindODMem(RemoteControlStartIndex,SubindexTelegramm2ToSlaveHighWord,TypeU8,2); *outputRCToSlaveSteeringMode=0x00;

    inputIOPortHand=BindODMem(IOPortStartIndex,SubindexInput38,TypeU16,0);
    inputIOPortAutomatik=BindODMem(IOPortStartIndex,SubindexInput49,TypeU16,0);

    inputRCGetDriveModule11Angle=BindODMem(DriveModuleStartIndex,SubindexDriveModule11ActualAngle,TypeS32,0);
    inputRCGetDriveModule12Angle=BindODMem(DriveModuleStartIndex,SubindexDriveModule12ActualAngle,TypeS32,0);
    inputRCGetDriveModule21Angle=BindODMem(DriveModuleStartIndex,SubindexDriveModule21ActualAngle,TypeS32,0);
    inputRCGetDriveModule22Angle=BindODMem(DriveModuleStartIndex,SubindexDriveModule22ActualAngle,TypeS32,0);

    inputRCGetAutoDriveY1Value=BindODMem(AutoDriveStartIndex,SubindexAutoDriveYValue,TypeS16,0);
    inputRCGetAutoDriveY2Value=BindODMem(AutoDriveStartIndex,SubindexAutoDriveYValue,TypeS16,1);

    inputRCGetAutoDriveXValue=BindODMem(AutoDriveStartIndex,SubindexAutoDriveXValue,TypeS16,0);

}

//=================================================================================================
/*!
    Function: get allowable the Max Drive Speed via actual Angle
    output: None
*/
//=================================================================================================
void GetMaxDriveSpeed(void){
    float32 r;
    float32 SpeedPoti;
    float32 setDriveAngle;
    float32 validAngle=5.0*Grad2Rad;

    SpeedPoti=(float32)(*inputRemoteControlSpeedPoti-127)/87.0*MaxSpeed;

    if((*outputRCSetDriveSysControlWord&KeyRCGetDriveSysCrossDriveSet)==0){
        if(SpeedPoti>(MaxSpeed*0.5)){
            if (DriveMode==KeyDriveModeAllrad){
                setDriveAngle=*outputRCSetDriveSysAngle;
                if (setDriveAngle>validAngle){
                    setDriveAngle=(float32)(*inputRCGetDriveModule11Angle)*Grad2Rad;
                    r=L/2.0/sinf(setDriveAngle);
                    MaxDriveSpeed=MaxSpeed/r*(r-1.2);
                }
                else if(setDriveAngle<-validAngle){
                    setDriveAngle=(float32)(*inputRCGetDriveModule12Angle)*Grad2Rad;
                    r=L/2.0/sinf(0.0-setDriveAngle);
                    MaxDriveSpeed=MaxSpeed/r*(r-1.2);
                }
                else MaxDriveSpeed=MaxSpeed;
            }
            else if(DriveMode==KeyDriveModeVorderrad){
                setDriveAngle=*outputRCSetDriveSysAngle;
                if (setDriveAngle>validAngle){
                    setDriveAngle=(float32)(*inputRCGetDriveModule12Angle)*Grad2Rad;
                    r=L/sinf(setDriveAngle);
                    MaxDriveSpeed=MaxSpeed/r*(r-0.8);
                }
                else if(setDriveAngle<-validAngle){
                    setDriveAngle=(float32)(*inputRCGetDriveModule11Angle)*Grad2Rad;
                    r=L/sinf(0.0-setDriveAngle);
                    MaxDriveSpeed=MaxSpeed/r*(r-0.8);
                }
                else MaxDriveSpeed=MaxSpeed;
            }
            else if(DriveMode==KeyDriveModeHinterrad){
                setDriveAngle=*outputRCSetDriveSysAngle;
                if (setDriveAngle>validAngle){
                    setDriveAngle=(float32)(*inputRCGetDriveModule21Angle)*Grad2Rad;
                    r=L/sinf(setDriveAngle);
                    MaxDriveSpeed=MaxSpeed/r*(r-0.8);
                }
                else if(setDriveAngle<-validAngle){
                    setDriveAngle=(float32)(*inputRCGetDriveModule22Angle)*Grad2Rad;
                    r=L/sinf(0.0-setDriveAngle);
                    MaxDriveSpeed=MaxSpeed/r*(r-0.8);
                }
                else MaxDriveSpeed=MaxSpeed;
            }
            else{
                MaxDriveSpeed=MaxSpeed;
            }
            if(SpeedPoti<MaxDriveSpeed) MaxDriveSpeed=SpeedPoti;
        }
        else MaxDriveSpeed=SpeedPoti;
    }
    else MaxDriveSpeed=SpeedPoti;

    if(*outputRCSetSafetyControlWord&KeyRCSetSafetySysLaserscanner1Deaktiv){
        if(*outputRCSetSafetyControlWord&KeyRCSetSafetySysLaserscanner2Deaktiv){
            if(MaxDriveSpeed>(MaxSpeed*0.4)) MaxDriveSpeed=MaxSpeed*0.4;
        }
    }

    if(*outputRCSetSafetyControlWord&(KeyRCGetSafetySysLaserscanner1Slow+KeyRCGetSafetySysLaserscanner2Slow)){
        if(MaxDriveSpeed>MaxSpeedSlow) MaxDriveSpeed=MaxSpeedSlow;
    }
    if(*outputRCSetSafetyControlWord&(KeyRCGetSafetySysLaserscanner1Warn+KeyRCGetSafetySysLaserscanner2Warn)){
        if(MaxDriveSpeed>MaxSpeedWarnFeld) MaxDriveSpeed=MaxSpeedWarnFeld;
    }
    MaxDriveOmega=0.4;
}

//=================================================================================================
/*!
    Function: calculate input value of the Joystick
    output: None
*/
//=================================================================================================
float32 FuncJoystickCal(sint16 x,uint16 joystick_num){
    float32 tmp;
    float32 JoyStickFactA=0.0;
    float32 JoyStickFactB=0.000225;
    float32 JoyStickFactC=-0.0017;
    float32 JoyStickFactD=0.0021;
    float32 resValue;

    tmp=(float32)x;

    /*if(x==0) return 0.0;
    else if(x>0) return 0.5*tanh(tmp/21.17-3.0)+0.5;
    else return -0.5*tanh(-tmp/21.17-3.0)-0.5;*/

    if(joystick_num==0){
        if(x==0) return 0.0;
        else if(x>0){
            resValue=tmp*tmp*JoyStickFactB+tmp*JoyStickFactC+JoyStickFactD;
            if(resValue<0.0) return 0.0;
            else if(resValue>1.0) return 1.0;
            else return resValue;
        }
        else{
            resValue=-tmp*tmp*JoyStickFactB+tmp*JoyStickFactC-JoyStickFactD;
            if(resValue>0.0) return 0.0;
            else if(resValue<-1.0) return -1.0;
            else return resValue;
        }
    }
    else if(joystick_num==1){
        resValue=1.0/127.0*x;
        if(resValue>1.0) return 1.0;
        else if(resValue<-1.0) return -1.0;
        else return resValue;
    }
}

//=================================================================================================
/*!
    Function: get the input value of the Joystick
    output: None
*/
//=================================================================================================
void RemoteControlGetJoystick(void){
    sint16 tmp;

    if((*inputRemoteControlXVar==127)&&(*inputRemoteControlY2Var==127)&&(*inputRemoteControlY1Var==127)) *outputRCSetSafetyControlWord|=KeyRCSetSafetySysRCNoMotion;
    else *outputRCSetSafetyControlWord&=~KeyRCSetSafetySysRCNoMotion;

    if(RCReqWord&KeyRCReqWordDriveSteeringMode)  XValue=FuncJoystickCal((sint16)(*inputRemoteControlXVar)-127,1);
    else XValue=FuncJoystickCal((sint16)(*inputRemoteControlXVar)-127,0);

    if(*inputRemoteControlDigitalIn&RemoteControlSwitchTotmann) Y2Value=FuncJoystickCal(127-(sint16)(*inputRemoteControlY2Var),0);
    else Y2Value=0.0;

    tmp=(sint16)(*inputRemoteControlY1Var)-127;
    if(tmp>10) Y1Value=1;
    else if(tmp<-10) Y1Value=-1;
    else Y1Value=0;

    //ZValue=FuncJoystickCal((sint16)(*inputRemoteControlZVar)-127,0);
    GetMaxDriveSpeed();
}

//=================================================================================================
/*!
    Function: get the button value of the remote controller
    output: Non
*/
//=================================================================================================
void GetButtonValue(void){
    if(*inputRemoteControlDigitalIn&RemoteControlButtonStart){
        if((oldDigitalIn&RemoteControlButtonStart)==0) RCReqWord|=KeyRCReqWordStart;
    }

    if(State==RCStateRun){
        if(*inputRemoteControlDigitalIn&RemoteControlButtonZeroSet){
            *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysZeroSet;
        }
        else{
            *outputRCSetDriveSysControlWord&=~KeyRCSetDriveSysZeroSet;
        }
    }

    if(*inputRemoteControlDigitalIn&RemoteControlButtonReset){
        if((oldDigitalIn&RemoteControlButtonReset)==0) RCReqWord|=KeyRCReqWordReset;
    }

    if(*inputRemoteControlDigitalIn&RemoteControlButtonHupe){
        RCReqWord|=KeyRCReqWordHupeReq;
    }
    else{
        RCReqWord&=~KeyRCReqWordHupeReq;
    }

    if(*inputIOPortHand==1) RCReqWord&=~KeyRCReqWordAutoHand;
    if(*inputIOPortAutomatik==1) RCReqWord|=KeyRCReqWordAutoHand;
}

//=================================================================================================
/*!
    Function: get the value of the Switch
    output: None
*/
//=================================================================================================
void GetSwitchValue(void){
    /*if(*inputRemoteControlDigitalIn&RemoteControlSwitchIndDrive){
        RCReqWord|=KeyRCReqWordIndDrive;
        *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysTwoDimensionDrive;
    }
    else if(*inputRemoteControlDigitalIn&RemoteControlSwitchNoIndDrive){
        RCReqWord&=~KeyRCReqWordIndDrive;
        *outputRCSetDriveSysControlWord&=~KeyRCSetDriveSysTwoDimensionDrive;
    }*/
    if(State==RCStateRun){
        if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsStop){
            if(*inputRemoteControlDigitalIn&RemoteControlSwitchCrossDrive) {
                RCReqWord|=KeyRCReqWordCrossDrive;
                *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysCrossDriveReq;
            }
            else if(*inputRemoteControlDigitalIn&RemoteControlSwitchLongDrive){
                RCReqWord&=~KeyRCReqWordCrossDrive;
                *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysLangDriveReq;
            }
        }
    }


    if(*inputRemoteControlDigitalIn&RemoteControlSwitchErrorQuit){
        if((oldDigitalIn&RemoteControlSwitchErrorQuit)==0){
            *outputRCSetAutoDriveControlWord|=KeyRCSetAutoDriveAutoQuitReq;
            //if(*outputRCSetDriveSysControlWord&KeyRCSetDriveSysTestMode) *outputRCSetDriveSysControlWord&=~KeyRCSetDriveSysTestMode;
            //else *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysTestMode;
        }
    }

    if(*inputRemoteControlDigitalIn&RemoteControlSwitchDriveSteeringMode){
        if((oldDigitalIn&RemoteControlSwitchDriveSteeringMode)==0){
            if(RCReqWord&KeyRCReqWordDriveSteeringMode) RCReqWord&=~KeyRCReqWordDriveSteeringMode;
            else RCReqWord|=KeyRCReqWordDriveSteeringMode;
        }
    }

    //Hub system aktiv
    if(*inputRemoteControlDigitalIn&RemoteControlSwitchHubSysAktiv){
        if((oldDigitalIn&RemoteControlSwitchHubSysAktiv)==0){
            if((RCReqWord&KeyRCReqWordHubSysAktiv)==0){
                if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsStop) RCReqWord|=KeyRCReqWordHubSysAktiv;
            }
            else{
                if(*inputHubsystemStatus&KeyRCGetHubSysFromSlaveIsStop) RCReqWord&=~KeyRCReqWordHubSysAktiv;
            }
        }
    }

    //Laser Scanner Deaktiv
    if(*inputRemoteControlDigitalIn&RemoteControlSwitchLaserscannerDeaktiv){
        if((oldDigitalIn&RemoteControlSwitchLaserscannerDeaktiv)==0){
            if(RCReqWord&KeyRCReqWordLSDeaktiv) RCReqWord&=~KeyRCReqWordLSDeaktiv;
            else RCReqWord|=KeyRCReqWordLSDeaktiv;
        }
    }
    /*if(*inputRemoteControlDigitalIn&RemoteControlSwitchLaserscannerDeaktiv) RCReqWord|=KeyRCReqWordLSDeaktiv;
    else RCReqWord&=~KeyRCReqWordLSDeaktiv;*/
}

//=================================================================================================
/*!
    Function: calculate the abs value
    output: None
*/
//=================================================================================================
sint16 Abs(sint16 value){
    if (value>=0) return value;
    else return (0-value);
}

//=================================================================================================
/*!
    Function: function for rc hupe
    output: None
*/
//=================================================================================================
void RCHupe(void){
    static uint16 local_tick;

    if((*outputRCSetSafetyControlWord&KeyRCSetSafetySysLaserscanner1Deaktiv)==0){
        if(*outputRCSetSafetyControlWord&KeyRCGetSafetySysLaserscanner1Stop) local_tick=3;
    }
    if((*outputRCSetSafetyControlWord&KeyRCSetSafetySysLaserscanner2Deaktiv)==0){
        if(*outputRCSetSafetyControlWord&KeyRCGetSafetySysLaserscanner2Stop) local_tick=3;
    }
    if(*outputRCSetAutoDriveControlWord&KeyRCGetAutoDriveHupeReq) local_tick=2;


    if(RCReqWord&KeyRCReqWordHupeReq) local_tick=3;

    if(State==RCStateRun||State==RCStateHub||State==RCStateAutoDrive){
        if(local_tick){
            if((*outputIOPortHupe&RCPinControlWordTestMode)==0) *outputIOPortHupe=(*outputIOPortHupe&0xffff0000)+0x00000001;
        }
        else{
            if((*outputIOPortHupe&RCPinControlWordTestMode)==0) *outputIOPortHupe&=0xffff0000;
        }
        if(local_tick>0) local_tick--;
    }

}



//=================================================================================================
/*!
    Function: calculate the Input value of the Controller for "Allradlenkung"
    output: None
*/
//=================================================================================================
void DriveAllradLenkung(void){
    float32 setMaxSpeed;
    float32 actualDriveAngle;
    float32 angleValue_rad;
    static float oldValue;

    if(RCReqWord&KeyRCReqWordCrossDrive){
        MaxDriveAngle=MaxDriveAngleCrossAllrad;
        setMaxSpeed=MaxDriveSpeed*0.5;
    }
    else{
       MaxDriveAngle=MaxDriveAngleLangAllrad;
       setMaxSpeed=MaxDriveSpeed;
    }

    *outputRCSetDriveSysSpeed=Y2Value*setMaxSpeed;
    if(RCReqWord&KeyRCReqWordDriveSteeringMode){
        if(XValue>0.0){
            if(*outputRCSetDriveSysAngle<MaxDriveAngle) *outputRCSetDriveSysAngle+=XValue*OmegaMotionMode;
            else *outputRCSetDriveSysAngle=MaxDriveAngle;
        }
        else if(XValue<0.0){
            if(*outputRCSetDriveSysAngle>-MaxDriveAngle) *outputRCSetDriveSysAngle+=XValue*OmegaMotionMode;
            else *outputRCSetDriveSysAngle=-MaxDriveAngle;
        }
        else{
            if(oldValue!=0.0){
                if(RCReqWord&KeyRCReqWordCrossDrive){
                    angleValue_rad=(float32)(*inputRCGetDriveModule12Angle)*Grad2Rad;
                    if(*inputRCGetDriveModule12Angle>1) actualDriveAngle=atanf(B/2.0/(B/2.0/tanf(angleValue_rad)+L/2.0));
                    else if(*inputRCGetDriveModule12Angle<-1) actualDriveAngle=atanf(B/2.0/(B/2.0/tanf(angleValue_rad)+L/2.0));
                    else actualDriveAngle=0.0;
                    if(oldValue>0.0) *outputRCSetDriveSysAngle=actualDriveAngle+AngleOffsetMotion/3.0;
                    else if(oldValue<0.0) *outputRCSetDriveSysAngle=actualDriveAngle-AngleOffsetMotion/3.0;
                }
                else{
                    angleValue_rad=(float32)(*inputRCGetDriveModule11Angle)*Grad2Rad;
                    if(*inputRCGetDriveModule11Angle>1) actualDriveAngle=atanf(L/2.0/(L/2.0/tanf(angleValue_rad)+B/2.0));
                    else if(*inputRCGetDriveModule11Angle<-1) actualDriveAngle=atanf(L/2.0/(L/2.0/tanf(angleValue_rad)+B/2.0));
                    else actualDriveAngle=0.0;
                    if(oldValue>0.0) *outputRCSetDriveSysAngle=actualDriveAngle+AngleOffsetMotion;
                    else if(oldValue<0.0) *outputRCSetDriveSysAngle=actualDriveAngle-AngleOffsetMotion;
                }
            }
        }
    }
    else
        *outputRCSetDriveSysAngle=XValue*MaxDriveAngle;
    *outputRCSetDriveSysControlWord&=0xffff0fff;
    *outputRCSetDriveSysControlWord+=KeyRCSetDriveSysSteeringModeAllrad;

    oldValue=XValue;
}

//=================================================================================================
/*!
    Function: calculate the Input value of the Controller for "Vorderradlenkung"
    output: None
*/
//=================================================================================================
void DriveVorderradLenkung(void){
    float32 setMaxSpeed;
    float32 actualDriveAngle;
    float32 angleValue_rad;
    static float oldValue;

    if(RCReqWord&KeyRCReqWordCrossDrive){
       MaxDriveAngle=MaxDriveAngleCrossNoAllrad;
       setMaxSpeed=MaxDriveSpeed*0.5;
    }
    else{
       MaxDriveAngle=MaxDriveAngleLangNoAllrad;
       setMaxSpeed=MaxDriveSpeed;
    }
    *outputRCSetDriveSysSpeed=Y2Value*setMaxSpeed;
    if(RCReqWord&KeyRCReqWordDriveSteeringMode){
        if((RCReqWord&KeyRCReqWordIndDrive)==0){
            if(XValue>0.0){
                if(*outputRCSetDriveSysAngle<MaxDriveAngle) *outputRCSetDriveSysAngle+=XValue*OmegaMotionMode;
                else *outputRCSetDriveSysAngle=MaxDriveAngle;
            }
            else if(XValue<0.0){
                if(*outputRCSetDriveSysAngle>-MaxDriveAngle) *outputRCSetDriveSysAngle+=XValue*OmegaMotionMode;
                else *outputRCSetDriveSysAngle=-MaxDriveAngle;
            }
            else{
                if(oldValue!=0.0){
                    if(RCReqWord&KeyRCReqWordCrossDrive){
                        angleValue_rad=(float32)(*inputRCGetDriveModule12Angle)*Grad2Rad;
                        if(*inputRCGetDriveModule12Angle>1) actualDriveAngle=atanf(B/(B/tanf(angleValue_rad)+L/2.0));
                        else if(*inputRCGetDriveModule12Angle<-1) actualDriveAngle=atanf(B/(B/tanf(angleValue_rad)+L/2.0));
                        else actualDriveAngle=0.0;
                        if(oldValue>0.0) *outputRCSetDriveSysAngle=actualDriveAngle+AngleOffsetMotion/3.0;
                        else if(oldValue<0.0) *outputRCSetDriveSysAngle=actualDriveAngle-AngleOffsetMotion/3.0;
                    }
                    else{
                        angleValue_rad=(float32)(*inputRCGetDriveModule11Angle)*Grad2Rad;
                        if(*inputRCGetDriveModule11Angle>1) actualDriveAngle=atanf(L/(L/tanf(angleValue_rad)+B/2.0));
                        else if(*inputRCGetDriveModule11Angle<-1) actualDriveAngle=atanf(L/(L/tanf(angleValue_rad)+B/2.0));
                        else actualDriveAngle=0.0;
                        if(oldValue>0.0) *outputRCSetDriveSysAngle=actualDriveAngle+AngleOffsetMotion;
                        else if(oldValue<0.0) *outputRCSetDriveSysAngle=actualDriveAngle-AngleOffsetMotion;
                    }
                }
            }
        }
    }
    else
        *outputRCSetDriveSysAngle=XValue*MaxDriveAngle;
    *outputRCSetDriveSysControlWord&=0xffff0fff;
    *outputRCSetDriveSysControlWord+=KeyRCSetDriveSysSteeringModeVorderrad;

    oldValue=XValue;
}

//=================================================================================================
/*!
    Function: calculate the Input value of the Controller for "Hinterradlenkung"
    output: None
*/
//=================================================================================================
void DriveHinterradLenkung(void){
    float32 setMaxSpeed;
    static float oldValue;
    float32 actualDriveAngle;
    float32 angleValue_rad;

    if(RCReqWord&KeyRCReqWordCrossDrive){
       MaxDriveAngle=MaxDriveAngleCrossNoAllrad;
       setMaxSpeed=MaxDriveSpeed*0.5;
    }
    else{
       MaxDriveAngle=MaxDriveAngleLangNoAllrad;
       setMaxSpeed=MaxDriveSpeed;
    }
    *outputRCSetDriveSysSpeed=Y2Value*setMaxSpeed;
    if(RCReqWord&KeyRCReqWordDriveSteeringMode){
        if((RCReqWord&KeyRCReqWordIndDrive)==0){
            if(XValue<0.0){
                if(*outputRCSetDriveSysAngle<MaxDriveAngle) *outputRCSetDriveSysAngle-=XValue*OmegaMotionMode;
                else *outputRCSetDriveSysAngle=MaxDriveAngle;
            }
            else if(XValue>0.0)
            {
                if(*outputRCSetDriveSysAngle>-MaxDriveAngle) *outputRCSetDriveSysAngle-=XValue*OmegaMotionMode;
                else *outputRCSetDriveSysAngle=-MaxDriveAngle;
            }
            else{
                if(oldValue!=0.0){
                    if(RCReqWord&KeyRCReqWordCrossDrive){
                        angleValue_rad=(float32)(*inputRCGetDriveModule11Angle)*Grad2Rad;
                        if(*inputRCGetDriveModule11Angle>1) actualDriveAngle=atanf(B/(B/tanf(angleValue_rad)+L/2.0));
                        else if(*inputRCGetDriveModule11Angle<-1) actualDriveAngle=atanf(B/(B/tanf(angleValue_rad)+L/2.0));
                        else actualDriveAngle=0.0;
                        if(oldValue>0.0) *outputRCSetDriveSysAngle=actualDriveAngle+AngleOffsetMotion/3.0;
                        else if(oldValue<0.0) *outputRCSetDriveSysAngle=actualDriveAngle-AngleOffsetMotion/3.0;
                    }
                    else{
                        angleValue_rad=(float32)(*inputRCGetDriveModule21Angle)*Grad2Rad;
                        if(*inputRCGetDriveModule21Angle>1) actualDriveAngle=atanf(L/(L/tanf(angleValue_rad)-B/2.0));
                        else if(*inputRCGetDriveModule21Angle<-1) actualDriveAngle=atanf(L/(L/tanf(angleValue_rad)-B/2.0));
                        else actualDriveAngle=0.0;
                        if(oldValue>0.0) *outputRCSetDriveSysAngle=actualDriveAngle-AngleOffsetMotion;
                        else if(oldValue<0.0) *outputRCSetDriveSysAngle=actualDriveAngle+AngleOffsetMotion;
                    }
                }
            }
        }
    }
    else
        *outputRCSetDriveSysAngle=0.0-XValue*MaxDriveAngle;
    *outputRCSetDriveSysControlWord&=0xffff0fff;
    *outputRCSetDriveSysControlWord+=KeyRCSetDriveSysSteeringModeHinterrad;

    oldValue=XValue;
}

//=================================================================================================
/*!
    Function: calculate the Input value of the Controller for "Krebsgang"
    output: None
*/
//=================================================================================================
void DriveKrebsgang(void){
    float32 setMaxSpeed;
    static float oldValue;
    float32 actualDriveAngle;
    float32 angleValue_rad;

    if(RCReqWord&KeyRCReqWordCrossDrive) {
        MaxDriveAngle=MaxDriveAngleCrossKrebsgang;
        setMaxSpeed=MaxDriveSpeed*0.5;
    }
    else{
        MaxDriveAngle=MaxDriveAngleLangKrebsgang;
        setMaxSpeed=MaxDriveSpeed;
    }

    *outputRCSetDriveSysSpeed=Y2Value*setMaxSpeed;
    if(RCReqWord&KeyRCReqWordDriveSteeringMode){
        if((RCReqWord&KeyRCReqWordIndDrive)==0){
            if(XValue>0.0){
                if(*outputRCSetDriveSysAngle<MaxDriveAngle) *outputRCSetDriveSysAngle+=XValue*OmegaMotionMode;
                else *outputRCSetDriveSysAngle=MaxDriveAngle;
            }
            else if(XValue<0.0){
                if(*outputRCSetDriveSysAngle>-MaxDriveAngle) *outputRCSetDriveSysAngle+=XValue*OmegaMotionMode;
                else *outputRCSetDriveSysAngle=-MaxDriveAngle;
            }
            else{
                if(oldValue!=0.0){
                    angleValue_rad=(float32)(*inputRCGetDriveModule11Angle)*Grad2Rad;
                    if((*inputRCGetDriveModule11Angle>1)||(*inputRCGetDriveModule11Angle<-1)) actualDriveAngle=angleValue_rad;
                    else actualDriveAngle=0.0;
                    if(oldValue>0.0) *outputRCSetDriveSysAngle=actualDriveAngle+AngleOffsetMotion;
                    else if(oldValue<0.0) *outputRCSetDriveSysAngle=actualDriveAngle-AngleOffsetMotion;
                }
            }
        }
    }
    else
        *outputRCSetDriveSysAngle=XValue*MaxDriveAngle;
    *outputRCSetDriveSysControlWord&=0xffff0fff;
    *outputRCSetDriveSysControlWord+=KeyRCSetDriveSysSteeringModeKrebsgang;

    oldValue=XValue;
}

//=================================================================================================
/*!
    Function: calculate the Input value of the Controller for "Parken"
    output: None
*/
//=================================================================================================
void DriveParken(void){
    *outputRCSetDriveSysSpeed=0.0;
    *outputRCSetDriveSysAngle=0.0;
    *outputRCSetDriveSysControlWord&=0xffff0fff;
    *outputRCSetDriveSysControlWord+=KeyRCSetDriveSysSteeringModeParken;
}

//=================================================================================================
/*!
    Function: calculate the Input value of the Controller for "Rundgang"
    output: None
*/
//=================================================================================================
void DriveRundgang(void){
    *outputRCSetDriveSysSpeed=Y2Value*MaxDriveSpeed*0.5;
    *outputRCSetDriveSysAngle=0.0;
    *outputRCSetDriveSysControlWord&=0xffff0fff;
    *outputRCSetDriveSysControlWord+=KeyRCSetDriveSysSteeringModeRundgang;
}



//=================================================================================================
/*!
    Function: generate the Input value of the Controller for "auto drive ready"
    output: None
*/
//=================================================================================================
void DriveAutoDriveReady(void){
    float32 setSpeed;
    setSpeed=0.15;
}

//=================================================================================================
/*!
    Function: generate the value for Hub system
    output: None
*/
//=================================================================================================
void RCHubSystem(void){
    uint32 tmpValue;
    uint32 StepInPercentUp=0x00020000;
    uint32 StepInPercentDown=0x00020000;
    uint8 setDefaultHeight=40;
    uint8 ErrHeight;
    static uint16 Local_tick;
    static uint32 timestamp_local;


    tmpValue=*outputRCSetHubSysControlWord>>16;
    if(State==RCStateReady){
        timestamp_local=x_sys_get_time_ms();
    }
    else if(State==RCStateHub){
        if(Y1Value==1){
            if((*inputHubsystemStatus&KeyRCGetHubSysFromSlaveOnlySinken)==0){
                if((Local_tick==0)&&(*inputHubsystemHeight<125)) *outputRCSetHubSysControlWord|=KeyRCSetHubSysHeben;
                else *outputRCSetHubSysControlWord&=~KeyRCSetHubSysHeben;
                if((*inputHubsystemStatus&KeyRCGetHubSysFromSlaveNoAdd)==0){
                    if(tmpValue<100) *outputRCSetHubSysControlWord+=StepInPercentUp;
                }
            }
            else *outputRCSetHubSysControlWord&=~KeyRCSetHubSysHeben;
            *outputRCSetHubSysControlWord&=~KeyRCSetHubSysSinken;
        }
        else if(Y1Value==-1){
            if((Local_tick==0)&&(*inputHubsystemHeight>10)) *outputRCSetHubSysControlWord|=KeyRCSetHubSysSinken;
            else *outputRCSetHubSysControlWord&=~KeyRCSetHubSysSinken;
            *outputRCSetHubSysControlWord&=~KeyRCSetHubSysHeben;
            if((*inputHubsystemStatus&KeyRCGetHubSysFromSlaveNoAdd)==0){
                if(tmpValue>0) *outputRCSetHubSysControlWord-=StepInPercentDown;
            }
        }
        else{
            *outputRCSetHubSysControlWord&=~KeyRCSetHubSysSinken;
            *outputRCSetHubSysControlWord&=~KeyRCSetHubSysHeben;
            Local_tick=5;
        }
    }
    else if(State==RCStateAutoDrive){
        if((x_sys_get_time_ms()-timestamp_local)>6000){
            if(*inputHubsystemHeight>setDefaultHeight){
                ErrHeight=*inputHubsystemHeight-setDefaultHeight;
                if(ErrHeight>2){
                    *outputRCSetHubSysControlWord|=KeyRCSetHubSysAutoInit;
                    *outputRCSetHubSysControlWord|=KeyRCSetHubSysSinken;
                    *outputRCSetHubSysControlWord&=~KeyRCSetHubSysHeben;
                    *outputRCSetHubSysControlWord&=0x0000ffff;
                    *outputRCSetHubSysControlWord+=(setDefaultHeight<<16);
                }
                else{
                    *outputRCSetHubSysControlWord&=~KeyRCSetHubSysAutoInit;
                    *outputRCSetHubSysControlWord&=~KeyRCSetHubSysSinken;
                    *outputRCSetHubSysControlWord&=~KeyRCSetHubSysHeben;
                }
            }
            else{
                ErrHeight=setDefaultHeight-*inputHubsystemHeight;
                if(ErrHeight>2){
                    *outputRCSetHubSysControlWord|=KeyRCSetHubSysAutoInit;
                    *outputRCSetHubSysControlWord|=KeyRCSetHubSysHeben;
                    *outputRCSetHubSysControlWord&=~KeyRCSetHubSysSinken;
                    *outputRCSetHubSysControlWord&=0x0000ffff;
                    *outputRCSetHubSysControlWord+=(setDefaultHeight<<16);
                }
                else{
                    *outputRCSetHubSysControlWord&=~KeyRCSetHubSysAutoInit;
                    *outputRCSetHubSysControlWord&=~KeyRCSetHubSysSinken;
                    *outputRCSetHubSysControlWord&=~KeyRCSetHubSysHeben;
                }
            }
        }
    }
    if(Local_tick>0) Local_tick--;
}
//=================================================================================================
/*!
    Function: Choice the different calculate for according drive modus
    output: None
*/
//=================================================================================================
void RCDriveSteering(void){
    uint16 disable;
    disable=0;
    RemoteControlGetJoystick();
    if(State==RCStateRun){
        if((*outputRCSetDriveSysControlWord&KeyRCSetDriveSysTwoDimensionDrive)==0){
            //Rotary Switch
            if(*inputRemoteControlDigitalIn&AllradLenkung){
                if(DriveMode!=KeyDriveModeAllrad){
                    if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsStop) DriveMode=KeyDriveModeAllrad;
                    else disable=1;
                }
                if(RCReqWord&KeyRCReqWordDriveSteeringMode){
                    if((oldDigitalIn&AllradLenkung)==0) *outputRCSetDriveSysAngle=0.0;
                }

            }
            else if(*inputRemoteControlDigitalIn&VorderradLenkung){
                if(DriveMode!=KeyDriveModeVorderrad){
                    if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsStop) DriveMode=KeyDriveModeVorderrad;
                    else disable=1;
                }
                if(RCReqWord&KeyRCReqWordDriveSteeringMode){
                    if((oldDigitalIn&VorderradLenkung)==0) *outputRCSetDriveSysAngle=0.0;
                }
            }
            else if(*inputRemoteControlDigitalIn&HinterradLenkung){
                if(DriveMode!=KeyDriveModeHinterrad){
                    if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsStop) DriveMode=KeyDriveModeHinterrad;
                    else disable=1;
                }
                if(RCReqWord&KeyRCReqWordDriveSteeringMode){
                    if((oldDigitalIn&HinterradLenkung)==0) *outputRCSetDriveSysAngle=0.0;
                }
            }
            else if(*inputRemoteControlDigitalIn&Krebsgang){
                if(DriveMode!=KeyDriveModeKrebsgang){
                    if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsStop) DriveMode=KeyDriveModeKrebsgang;
                    else disable=1;
                }
                if(RCReqWord&KeyRCReqWordDriveSteeringMode){
                    if((oldDigitalIn&Krebsgang)==0) *outputRCSetDriveSysAngle=0.0;
                }
            }
            else if(*inputRemoteControlDigitalIn&Rundgang){
                if(DriveMode!=KeyDriveModeRundgang){
                    if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsStop) DriveMode=KeyDriveModeRundgang;
                    else disable=1;
                }
            }
            else if(*inputRemoteControlDigitalIn&Parken){
                if(DriveMode!=KeyDriveModePark){
                    if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsStop) DriveMode=KeyDriveModePark;
                    else disable=1;
                }
            }
            switch(DriveMode){
                case KeyDriveModeAllrad:
                    *outputRCToSlaveSteeringMode=KeyRCDisplaySteeringModeAllrad;
                    if(disable==0) DriveAllradLenkung();
                    break;
                case KeyDriveModeVorderrad:
                    *outputRCToSlaveSteeringMode=KeyRCDisplaySteeringModeVorderrad;
                    if(disable==0) DriveVorderradLenkung();
                    break;
                case KeyDriveModeHinterrad:
                    *outputRCToSlaveSteeringMode=KeyRCDisplaySteeringModeHinterrad;
                    if(disable==0) DriveHinterradLenkung();
                    break;
                case KeyDriveModeKrebsgang:
                    *outputRCToSlaveSteeringMode=KeyRCDisplaySteeringModeKrebsgang;
                    if(disable==0) DriveKrebsgang();
                    break;
                case KeyDriveModeRundgang:
                    *outputRCToSlaveSteeringMode=KeyRCDisplaySteeringModeRundgang;
                    if(disable==0) DriveRundgang();
                    break;
                case KeyDriveModePark:
                    *outputRCToSlaveSteeringMode=KeyRCDisplaySteeringModePark;
                    if(disable==0) DriveParken();
                    break;
            }
            if(disable==1){
                *outputRCSetDriveSysSpeed=0.0;
                *outputRCSetDriveSysAngle=0.0;
            }
            if(*outputRCSetDriveSysControlWord&KeyRCSetDriveSysZeroSet){
                *outputRCSetDriveSysAngle=0.0;
            }
        }
    }
}
//=================================================================================================
/*!
    Function: Get the Joystick value for the Auto drive
    output: None
*/
//=================================================================================================
void RCAutoDrive(void){
    if(State==RCStateAutoDrive){
        //ForWords/BackWords drive
        if((*outputRCSetHubSysControlWord&KeyRCSetHubSysAutoInit)==0){
            if(*outputRCSetAutoDriveControlWord&KeyRCGetAutoDriveOnLane){
                if(Y2Value>0.0){
                    *outputRCSetAutoDriveControlWord|=KeyRCSetAutoDriveForwardDrive;
                    *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveBackwardDrive;
                }
                else if(Y2Value<0.0){
                    *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveForwardDrive;
                    *outputRCSetAutoDriveControlWord|=KeyRCSetAutoDriveBackwardDrive;
                }
                else{
                    *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveForwardDrive;
                    *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveBackwardDrive;
                }
            }
            else{
                *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveForwardDrive;
                *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveBackwardDrive;
            }
            *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysTwoDimensionDrive;
        }
        else{
            *outputRCSetDriveSysControlWord&=~KeyRCSetDriveSysTwoDimensionDrive;
        }
    }
    else{
        *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveForwardDrive;
        *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveBackwardDrive;
        *outputRCSetDriveSysControlWord&=~KeyRCSetDriveSysTwoDimensionDrive;
    }
}

//=================================================================================================
/*!
    Function: Lampe Blink
    output: None
*/
//=================================================================================================
void RCLampeBlink(uint16 on){
    static sint16 BlinkTick;
    if(on){
        if(BlinkTick>-5) BlinkTick--;
        else BlinkTick=7;
    }
    else{
        BlinkTick=0;
    }
    if(BlinkTick>0){
        if((*outputIOPortLampe11&RCPinControlWordTestMode)==0) *outputIOPortLampe11=(*outputIOPortLampe11&0xffff0000)+0x00000001;
        if((*outputIOPortLampe12&RCPinControlWordTestMode)==0) *outputIOPortLampe12=(*outputIOPortLampe12&0xffff0000)+0x00000001;
        if((*outputIOPortLampe21&RCPinControlWordTestMode)==0) *outputIOPortLampe21=(*outputIOPortLampe21&0xffff0000)+0x00000001;
        if((*outputIOPortLampe22&RCPinControlWordTestMode)==0) *outputIOPortLampe22=(*outputIOPortLampe22&0xffff0000)+0x00000001;
    }
    else{
        if((*outputIOPortLampe11&RCPinControlWordTestMode)==0) *outputIOPortLampe11&=0xffff0000;
        if((*outputIOPortLampe12&RCPinControlWordTestMode)==0) *outputIOPortLampe12&=0xffff0000;
        if((*outputIOPortLampe21&RCPinControlWordTestMode)==0) *outputIOPortLampe21&=0xffff0000;
        if((*outputIOPortLampe22&RCPinControlWordTestMode)==0) *outputIOPortLampe22&=0xffff0000;
    }
}

//=================================================================================================
/*!
    Function: Update the Parameter
    output: None
*/
//=================================================================================================
void RCParameterUpdate(void){
    static uint16 updateflag;

    if(updateflag==0){
        *outputRCToSlaveDriveSysAngle11=(sint8)(*inputRCGetDriveModule11Angle);
        *outputRCToSlaveDriveSysAngle12=(sint8)(*inputRCGetDriveModule12Angle);
        *outputRCToSlaveDriveSysAngle21=(sint8)(*inputRCGetDriveModule21Angle);
        *outputRCToSlaveDriveSysAngle22=(sint8)(*inputRCGetDriveModule22Angle);
        if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysCrossDriveSet) *outputRCToSlaveStatusMES|=KeyRCDisplayStatusCrossDrive;
        else *outputRCToSlaveStatusMES&=~KeyRCDisplayStatusCrossDrive;
        if(*inputRemoteControlDigitalIn&Parken) *outputRCToSlaveStatusMES|=KeyRCDisplayStatusPark;
        else *outputRCToSlaveStatusMES&=~KeyRCDisplayStatusPark;
        if(*outputRCSetDriveSysControlWord&KeyRCSetDriveSysZeroSet) *outputRCToSlaveStatusMES|=KeyRCDisplayStatusZeroSet;
        else *outputRCToSlaveStatusMES&=~KeyRCDisplayStatusZeroSet;
        if(*outputRCSetSafetyControlWord&KeyRCGetSafetyIsError) *outputRCToSlaveStatusMES|=KeyRCDisplayStatusIsError;
        else *outputRCToSlaveStatusMES&=~KeyRCDisplayStatusIsError;
        if(*outputRCSetSafetyControlWord&KeyRCGetSafetyNotAusStatus) *outputRCToSlaveStatusMES|=KeyRCDisplayStatusNotAus;
        else *outputRCToSlaveStatusMES&=~KeyRCDisplayStatusNotAus;
        if(*outputRCSetSafetyControlWord&KeyRCGetSafetyLadungStatus) *outputRCToSlaveStatusMES|=KeyRCDisplayStatusLadung;
        else *outputRCToSlaveStatusMES&=~KeyRCDisplayStatusLadung;
        if(*outputRCSetAutoDriveControlWord&KeyRCSetAutoDriveForwardDrive) *outputRCToSlaveStatusAuto|=KeyRCDisplayAutoStatusDriveForward;
        else *outputRCToSlaveStatusAuto&=~KeyRCDisplayAutoStatusDriveForward;
        if(*outputRCSetAutoDriveControlWord&KeyRCSetAutoDriveBackwardDrive) *outputRCToSlaveStatusAuto|=KeyRCDisplayAutoStatusDriveBackward;
        else *outputRCToSlaveStatusAuto&=~KeyRCDisplayAutoStatusDriveBackward;
        if(*outputRCSetAutoDriveControlWord&KeyRCGetAutoDriveK1BandFind) *outputRCToSlaveStatusAuto|=KeyRCDisplayAutoStatusK1BandFind;
        else *outputRCToSlaveStatusAuto&=~KeyRCDisplayAutoStatusK1BandFind;
        if(*outputRCSetAutoDriveControlWord&KeyRCGetAutoDriveK2BandFind) *outputRCToSlaveStatusAuto|=KeyRCDisplayAutoStatusK2BandFind;
        else *outputRCToSlaveStatusAuto&=~KeyRCDisplayAutoStatusK2BandFind;
        if(*outputRCSetHubSysControlWord&KeyRCSetHubSysAutoInit) *outputRCToSlaveStatusAuto|=KeyRCDisplayAutoStatusAutoInit;
        else *outputRCToSlaveStatusAuto&=~KeyRCDisplayAutoStatusAutoInit;
        if(*outputRCSetAutoDriveControlWord&KeyRCGetAutoDriveInStopZone) *outputRCToSlaveStatusAuto|=KeyRCDisplayAutoStatusAutoStopZone;
        else *outputRCToSlaveStatusAuto&=~KeyRCDisplayAutoStatusAutoStopZone;
        if(RCReqWord&KeyRCReqWordDriveSteeringMode) *outputRCToSlaveStatusMES|=KeyRCDisplayStatusIsSteeringMotion;
        else *outputRCToSlaveStatusMES&=~KeyRCDisplayStatusIsSteeringMotion;
        if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsCrossSwitch) *outputRCToSlaveStatusExtMES|=KeyRCDisplayStatusExtCrossIsSwitch;
        else *outputRCToSlaveStatusExtMES&=~KeyRCDisplayStatusExtCrossIsSwitch;
        if(RCReqWord&KeyRCReqWordLSDeaktiv) *outputRCToSlaveStatusExtMES|=KeyRCDisplayStatusExtLSDeaktiv;
        else *outputRCToSlaveStatusExtMES&=~KeyRCDisplayStatusExtLSDeaktiv;
    }
    updateflag++;
    if(updateflag==1) updateflag=0;

    if((State==RCStateRun)||(State==RCStateAutoDrive)){
        if((*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsStop)==0) RCLampeBlink(X_ON);
        else RCLampeBlink(X_OFF);
    }
    else if(State==RCStateHub){
        if((*inputHubsystemStatus&KeyRCGetHubSysFromSlaveIsStop)==0) RCLampeBlink(X_ON);
        else RCLampeBlink(X_OFF);
    }
    else RCLampeBlink(X_OFF);
}


//=================================================================================================
/*!
    Function: management of the laser scanner
    output: None
*/
//=================================================================================================
void LaserScannerManage(void){
    if(State==RCStateRun){
        if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysCrossDriveSet){
            if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsStop){
                if(Y2Value==0.0){
                    *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner1Deaktiv;
                    *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner2Deaktiv;
                }
            }
            else if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsForward){
                if(RCReqWord&KeyRCReqWordLSDeaktiv){
                    *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner1Deaktiv;
                    *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner2Deaktiv;
                }
                else{
                    *outputRCSetSafetyControlWord&=~KeyRCSetSafetySysLaserscanner1Deaktiv;
                    *outputRCSetSafetyControlWord&=~KeyRCSetSafetySysLaserscanner2Deaktiv;
                }
            }
            else if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsBackward){
                if(RCReqWord&KeyRCReqWordLSDeaktiv){
                    *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner1Deaktiv;
                    *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner2Deaktiv;
                }
                else{
                    *outputRCSetSafetyControlWord&=~KeyRCSetSafetySysLaserscanner1Deaktiv;
                    *outputRCSetSafetyControlWord&=~KeyRCSetSafetySysLaserscanner2Deaktiv;
                }
            }
            return;
        }

        if(DriveMode!=KeyDriveModeRundgang){
            if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsStop){
                if(Y2Value==0.0){
                    *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner1Deaktiv;
                    *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner2Deaktiv;
                }
            }
            else if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsForward){
                if(RCReqWord&KeyRCReqWordLSDeaktiv) *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner1Deaktiv;
                else *outputRCSetSafetyControlWord&=~KeyRCSetSafetySysLaserscanner1Deaktiv;
                *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner2Deaktiv;
            }
            else if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsBackward){
                if(RCReqWord&KeyRCReqWordLSDeaktiv) *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner2Deaktiv;
                else *outputRCSetSafetyControlWord&=~KeyRCSetSafetySysLaserscanner2Deaktiv;
                *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner1Deaktiv;
            }
        }
        else{
            if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsStop){
                *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner1Deaktiv;
                *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner2Deaktiv;
            }
            else {
                if(RCReqWord&KeyRCReqWordLSDeaktiv){
                    *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner1Deaktiv;
                    *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner2Deaktiv;
                }
                else{
                   *outputRCSetSafetyControlWord&=~KeyRCSetSafetySysLaserscanner1Deaktiv;
                   *outputRCSetSafetyControlWord&=~KeyRCSetSafetySysLaserscanner2Deaktiv;
                }
            }
        }
    }
    else if(State==RCStateHub){
        if(RCReqWord&KeyRCReqWordLSDeaktiv){
            *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner1Deaktiv;
            *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner2Deaktiv;
        }
        else{
            *outputRCSetSafetyControlWord&=~KeyRCSetSafetySysLaserscanner1Deaktiv;
            *outputRCSetSafetyControlWord&=~KeyRCSetSafetySysLaserscanner2Deaktiv;
        }
    }
    else if(State==RCStateAutoDrive){
        if(*outputRCSetHubSysControlWord&KeyRCSetHubSysAutoInit){
            *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner1Deaktiv;
            *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner2Deaktiv;
        }
        else{
            if(Y2Value>0.0){
                *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner2Deaktiv;
                *outputRCSetSafetyControlWord&=~KeyRCSetSafetySysLaserscanner1Deaktiv;
                //*outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner1Deaktiv;
            }
            else if(Y2Value<0.0){
                *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner1Deaktiv;
                *outputRCSetSafetyControlWord&=~KeyRCSetSafetySysLaserscanner2Deaktiv;
                //*outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner2Deaktiv;
            }
            else{
                *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner1Deaktiv;
                *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner2Deaktiv;
            }
        }
    }
    else{
        *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner1Deaktiv;
        *outputRCSetSafetyControlWord|=KeyRCSetSafetySysLaserscanner2Deaktiv;
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
    uint8 oldState;
    uint8 flag;

    x_os_set_event_mask(Event_RC);
    akt_page=0;
    tick=0;
    oldState=State;

    while(TRUE){
        x_os_wait_for_events();
        u32_Events = x_os_get_events(); // get events
        if((u32_Events&Event_RC)!=0){
            if(State==RCStateInit){
                *outputRCToSlavePageState=KeyRCDisplayPageStateInit;
                if((RCActualTime-timeStampInitFinish)>10000){
                    State=RCStateReady;
                    *outputRCToSlaveStatusMES|=KeyRCDisplayStatusPageUpdate;
                }
            }
            else{
                if(State==RCStateReady){
                    *outputRCToSlavePageState=KeyRCDisplayPageStateReady;
                    //to run or auto drive state
                    if(RCReqWord&KeyRCReqWordStart){
                        RCReqWord&=~KeyRCReqWordStart;
                        if(RCReqWord&KeyRCReqWordAutoHand){
                           State=RCStateAutoDrive;
                           //*outputRCSetHubSysControlWord|=KeyRCSetHubSysAutoInit;
                        }
                        else State=RCStateRun;
                        *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysStart;
                        *outputRCToSlaveStatusMES|=KeyRCDisplayStatusPageUpdate;
                    }
                    //to Not fall
                    flag=0;
                    if(*outputRCSetSafetyControlWord&KeyRCGetSafetyNotAusStatus) flag=1;
                    if(*outputRCSetSafetyControlWord&KeyRCGetSafetyLadungStatus) flag=1;
                    if(flag){
                        oldState=RCStateReady;
                        flag=0;
                        *outputRCToSlaveStatusMES|=KeyRCDisplayStatusPageUpdate;
                        State=RCStateNotFall;
                    }
                    //normal manipulation
                    if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsEnable)  *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysDisableReq;
                    if(*outputRCSetHubSysControlWord&KeyRCSetHubSysEnable) *outputRCSetHubSysControlWord&=~KeyRCSetHubSysEnable;
                    if(*outputRCSetAutoDriveControlWord&KeyRCSetAutoDriveEnable) *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveEnable;
                }
                else if(State==RCStateRun){
                    *outputRCToSlavePageState=KeyRCDisplayPageStateRun;
                    //reset
                    if(RCReqWord&KeyRCReqWordReset){
                        RCReqWord&=~KeyRCReqWordReset;
                        timeStampInitFinish=RCActualTime;
                        State=RCStateInit;
                        *outputRCToSlaveStatusMES|=KeyRCDisplayStatusPageUpdate;
                        *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysReset;
                    }
                    //to hub state
                    else if(RCReqWord&KeyRCReqWordHubSysAktiv){
                        oldState=RCStateRun;
                        State=RCStateHub;
                        tick=70;
                        if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysCrossDriveSet)
                            *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysLangDriveReq;
                        *outputRCToSlaveStatusMES|=KeyRCDisplayStatusPageUpdate;
                    }
                    //to Not fall
                    flag=0;
                    if(*outputRCSetSafetyControlWord&KeyRCGetSafetyNotAusStatus) flag=1;
                    if(*outputRCSetSafetyControlWord&KeyRCGetSafetyLadungStatus) flag=1;
                    if((*inputRemoteControlDigitalIn&RemoteControlSchutzRealis)==0) flag=1;
                    if(flag){
                        oldState=RCStateRun;
                        flag=0;
                        *outputRCToSlaveStatusMES|=KeyRCDisplayStatusPageUpdate;
                        State=RCStateNotFall;
                    }
                    //normal manipulation
                    if((*outputRCSetSafetyControlWord&KeyRCGetSafetyDriveSysStop)==0){
                        if((*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsEnable)==0){
                            if(tick==0){
                                *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysEnableReq;
                                tick=50;
                            }
                        }
                    }
                    else *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysDisableReq;
                    if(*outputRCSetHubSysControlWord&KeyRCSetHubSysEnable) *outputRCSetHubSysControlWord&=~KeyRCSetHubSysEnable;
                    if(*outputRCSetAutoDriveControlWord&KeyRCSetAutoDriveEnable) *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveEnable;
                    *outputRCSetDriveSysControlWord&=~KeyRCSetDriveSysNoBrake;
                }
                else if(State==RCStateHub){
                    *outputRCToSlavePageState=KeyRCDisplayPageStateHub;
                    //reset
                    if(RCReqWord&KeyRCReqWordReset){
                        RCReqWord&=~KeyRCReqWordReset;
                        timeStampInitFinish=RCActualTime;
                        State=RCStateInit;
                        *outputRCToSlaveStatusMES|=KeyRCDisplayStatusPageUpdate;
                        *outputRCSetHubSysControlWord&=~KeyRCSetHubSysEnable;
                        *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysReset;
                        *outputRCSetDriveSysControlWord&=~KeyRCSetDriveSysNoBrake;
                    }
                    //to run state
                    if((RCReqWord&KeyRCReqWordHubSysAktiv)==0){
                        *outputRCToSlaveStatusMES|=KeyRCDisplayStatusPageUpdate;
                        *outputRCSetDriveSysAngle=0.0;
                        State=RCStateRun;
                    }
                    //to Not fall
                    flag=0;
                    if(*outputRCSetSafetyControlWord&KeyRCGetSafetyNotAusStatus) flag=1;
                    if(*outputRCSetSafetyControlWord&KeyRCGetSafetyLadungStatus) flag=1;
                    if((*inputRemoteControlDigitalIn&RemoteControlSchutzRealis)==0) flag=1;
                    if(flag){
                        oldState=RCStateHub;
                        flag=0;
                        *outputRCToSlaveStatusMES|=KeyRCDisplayStatusPageUpdate;
                        State=RCStateNotFall;
                    }
                    //normal manipulation
                    if((*outputRCSetDriveSysControlWord&KeyRCGetDriveSysCrossDriveSet)==0){
                        if(tick==0){
                            if((*outputRCSetSafetyControlWord&KeyRCGetSafetyHubSysStop)==0) *outputRCSetHubSysControlWord|=KeyRCSetHubSysEnable;
                            else *outputRCSetHubSysControlWord&=~KeyRCSetHubSysEnable;
                            if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsEnable) *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysDisableReq;
                            if(*outputRCSetAutoDriveControlWord&KeyRCSetAutoDriveEnable) *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveEnable;
                            *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysNoBrake;
                            *outputRCSetDriveSysControlWord&=~KeyRCSetDriveSysZeroSet;
                        }
                        else{
                            if(*outputRCSetHubSysControlWord&KeyRCSetHubSysEnable) *outputRCSetHubSysControlWord&=~KeyRCSetHubSysEnable;
                            if(*outputRCSetAutoDriveControlWord&KeyRCSetAutoDriveEnable) *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveEnable;
                            *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysZeroSet;
                        }
                    }
                    else{
                        if(*outputRCSetHubSysControlWord&KeyRCSetHubSysEnable) *outputRCSetHubSysControlWord&=~KeyRCSetHubSysEnable;
                        if(*outputRCSetAutoDriveControlWord&KeyRCSetAutoDriveEnable) *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveEnable;
                        //*outputRCSetDriveSysControlWord|=KeyRCSetDriveSysNoBrake;
                    }
                }
                else if(State==RCStateAutoDrive){
                    *outputRCToSlavePageState=KeyRCDisplayPageStateAuto;
                    //reset
                    if(RCReqWord&KeyRCReqWordReset){
                        RCReqWord&=~KeyRCReqWordReset;
                        timeStampInitFinish=RCActualTime;
                        State=RCStateInit;
                        *outputRCToSlaveStatusMES|=KeyRCDisplayStatusPageUpdate;
                        *outputRCSetHubSysControlWord&=~KeyRCSetHubSysAutoInit;
                        *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveEnable;
                        *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysReset;
                        *outputRCSetDriveSysControlWord&=~KeyRCSetDriveSysNoBrake;
                    }
                    //to Not fall
                    flag=0;
                    if(*outputRCSetSafetyControlWord&KeyRCGetSafetyNotAusStatus) flag=1;
                    if(*outputRCSetSafetyControlWord&KeyRCGetSafetyLadungStatus) flag=1;
                    if((*inputRemoteControlDigitalIn&RemoteControlSchutzRealis)==0) flag=1;
                    if(flag){
                        oldState=RCStateAutoDrive;
                        flag=0;
                        *outputRCToSlaveStatusMES|=KeyRCDisplayStatusPageUpdate;
                        State=RCStateNotFall;
                    }
                    //normal manipulation
                    if((*outputRCSetSafetyControlWord&KeyRCGetSafetyAutoDriveStop)==0) *outputRCSetAutoDriveControlWord|=KeyRCSetAutoDriveEnable;
                    else *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveEnable;

                    if((*outputRCSetHubSysControlWord&KeyRCSetHubSysAutoInit)==0){
                        if((*outputRCSetSafetyControlWord&KeyRCGetSafetyDriveSysStop)==0){
                            if((*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsEnable)==0){
                                if(tick==0){
                                    *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysEnableReq;
                                    tick=50;
                                }
                            }
                        }
                        else *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysDisableReq;
                        if(*outputRCSetHubSysControlWord&KeyRCSetHubSysEnable) *outputRCSetHubSysControlWord&=~KeyRCSetHubSysEnable;
                        *outputRCSetDriveSysControlWord&=~KeyRCSetDriveSysNoBrake;
                    }
                    else{
                        if((*outputRCSetSafetyControlWord&KeyRCGetSafetyHubSysStop)==0) *outputRCSetHubSysControlWord|=KeyRCSetHubSysEnable;
                        if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsEnable) *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysDisableReq;
                        *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysNoBrake;
                    }
                }
                else if(State==RCStateNotFall){
                    *outputRCToSlavePageState=KeyRCDisplayPageStateNotFall;
                    //to normal state
                    flag=0;
                    if(*outputRCSetSafetyControlWord&KeyRCGetSafetyNotAusStatus) flag=1;
                    if(*outputRCSetSafetyControlWord&KeyRCGetSafetyLadungStatus) flag=1;
                    if((*inputRemoteControlDigitalIn&RemoteControlSchutzRealis)==0) flag=1;
                    if(flag==0){
                        flag=0;
                        *outputRCToSlaveStatusMES|=KeyRCDisplayStatusPageUpdate;
                        State=oldState;
                    }
                    //normal manipulation
                    if(*outputRCSetDriveSysControlWord&KeyRCGetDriveSysIsEnable)  *outputRCSetDriveSysControlWord|=KeyRCSetDriveSysDisableReq;
                    if(*outputRCSetHubSysControlWord&KeyRCSetHubSysEnable) *outputRCSetHubSysControlWord&=~KeyRCSetHubSysEnable;
                    if(*outputRCSetAutoDriveControlWord&KeyRCSetAutoDriveEnable) *outputRCSetAutoDriveControlWord&=~KeyRCSetAutoDriveEnable;
                    *outputRCSetDriveSysControlWord&=~KeyRCSetDriveSysNoBrake;
                }
                GetSwitchValue();
                GetButtonValue();
                RCDriveSteering();
                RCHubSystem();
                RCAutoDrive();
                LaserScannerManage();
                RCHupe();
            }
            oldDigitalIn=*inputRemoteControlDigitalIn;
            RCParameterUpdate();
            if(tick>0) tick--;
        }
    }
}

//=================================================================================================
/*!
    Function: Initial of the Remote Control
    output: None
*/
//=================================================================================================
void InitRemoteControl(void){
    DriveMode=Parken;
    timeStampInitFinish=x_sys_get_time_ms();
    State=RCStateInit;

    InitInterfaceRemoteControl();
    x_os_install_task(PrioRemoteControl, 0, 0, Task_RemoteControl, 128);
}

//=================================================================================================
/*!
    Function: Awake the Task from sleep state
    input:
    output: None
*/
//=================================================================================================
void TaskRemoteControlAwake(void){
    RCActualTime=x_sys_get_time_ms();

    if((RCActualTime-timeStampRC)>2000){
        timeStampRC=RCActualTime;
        *outputRemoteControlNMT=NODE_START;
        *outputRemoteControlNMT=(*outputRemoteControlNMT<<8)+0x0001;
    }

    if(*inputRemoteControlToggle!=OldToggleByte) {
        RCtogglecounter++;
        OldToggleByte=*inputRemoteControlToggle;
    }
    if(RCtogglecounter>=MaxRCToggleCounter){
        x_os_set_events(Event_RC);
        RCtogglecounter=0;
    }
}


