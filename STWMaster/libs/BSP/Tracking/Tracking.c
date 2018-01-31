#include <Tracking.h>
#include <TrackingData.h>
#include <TrackingInterface.h>

//=================================================================================================
/*!
    Function: Initial of the AutoDrive
    output: None
*/
//=================================================================================================
void InitInterfaceAutoDrive(void){
    //Input Parameter of the auto drive
    inputAutoDriveControlWord=BindODMem(AutoDriveStartIndex,SubindexAutoDriveControlWord,TypeU32,0); *inputAutoDriveControlWord=0;

    inputAutoDriveGetSafetyControlWord=BindODMem(SafetyStartIndex,SubindexSafetyControlWord,TypeU32,0);

    inputAutoDriveReferenzSpeed=BindODMem(AutoDriveStartIndex,SubindexAutoDriveRefenerzSpeed,TypeS32,0);
    inputAutoDriveControlKp1=BindODMem(AutoDriveStartIndex,SubindexAutoDriveControlKp1,TypeS32,0);
    inputAutoDriveControlKp2=BindODMem(AutoDriveStartIndex,SubindexAutoDriveControlKp2,TypeS32,0);
    inputAutoDriveControlKi1=BindODMem(AutoDriveStartIndex,SubindexAutoDriveControlKi1,TypeS32,0);
    inputAutoDriveControlKi2=BindODMem(AutoDriveStartIndex,SubindexAutoDriveControlKi2,TypeS32,0);

    inputKamera1NodeStatus=BindODMem(AutoDriveStartIndex,SubindexCamera1NodeStatus,TypeU8,1); *inputKamera1NodeStatus=0x00;
    inputKamera2NodeStatus=BindODMem(AutoDriveStartIndex,SubindexCamera2NodeStatus,TypeU8,1); *inputKamera2NodeStatus=0x00;

    //Y Value
    inputAutoDriveYp11=BindODMem(AutoDriveStartIndex,SubindexCamera1RPDO1LowWord,TypeU8,3); *inputAutoDriveYp11=0;
    inputAutoDriveYp12=BindODMem(AutoDriveStartIndex,SubindexCamera1RPDO1LowWord,TypeU8,2); *inputAutoDriveYp11=0;
    inputAutoDriveYp13=BindODMem(AutoDriveStartIndex,SubindexCamera1RPDO1LowWord,TypeU8,1); *inputAutoDriveYp11=0;
    inputAutoDriveYp14=BindODMem(AutoDriveStartIndex,SubindexCamera1RPDO1LowWord,TypeU8,0); *inputAutoDriveYp11=0;
    inputAutoDriveYp21=BindODMem(AutoDriveStartIndex,SubindexCamera2RPDO1LowWord,TypeU8,3); *inputAutoDriveYp21=0;
    inputAutoDriveYp22=BindODMem(AutoDriveStartIndex,SubindexCamera2RPDO1LowWord,TypeU8,2); *inputAutoDriveYp22=0;
    inputAutoDriveYp23=BindODMem(AutoDriveStartIndex,SubindexCamera2RPDO1LowWord,TypeU8,1); *inputAutoDriveYp23=0;
    inputAutoDriveYp24=BindODMem(AutoDriveStartIndex,SubindexCamera2RPDO1LowWord,TypeU8,0); *inputAutoDriveYp24=0;

    //X Value
    inputAutoDriveXp11=BindODMem(AutoDriveStartIndex,SubindexCamera1RPDO2LowWord,TypeU8,3); *inputAutoDriveXp11=0;
    inputAutoDriveXp12=BindODMem(AutoDriveStartIndex,SubindexCamera1RPDO2LowWord,TypeU8,2); *inputAutoDriveXp11=0;
    inputAutoDriveXp13=BindODMem(AutoDriveStartIndex,SubindexCamera1RPDO2LowWord,TypeU8,1); *inputAutoDriveXp11=0;
    inputAutoDriveXp14=BindODMem(AutoDriveStartIndex,SubindexCamera1RPDO2LowWord,TypeU8,0); *inputAutoDriveXp11=0;
    inputAutoDriveXp21=BindODMem(AutoDriveStartIndex,SubindexCamera2RPDO2LowWord,TypeU8,3); *inputAutoDriveXp21=0;
    inputAutoDriveXp22=BindODMem(AutoDriveStartIndex,SubindexCamera2RPDO2LowWord,TypeU8,2); *inputAutoDriveXp22=0;
    inputAutoDriveXp23=BindODMem(AutoDriveStartIndex,SubindexCamera2RPDO2LowWord,TypeU8,1); *inputAutoDriveXp23=0;
    inputAutoDriveXp24=BindODMem(AutoDriveStartIndex,SubindexCamera2RPDO2LowWord,TypeU8,0); *inputAutoDriveXp24=0;

    //AG Value
    inputAutoDriveAG11=BindODMem(AutoDriveStartIndex,SubindexCamera1RPDO2HighWord,TypeU8,1); *inputAutoDriveAG11=0;
    inputAutoDriveAG12=BindODMem(AutoDriveStartIndex,SubindexCamera1RPDO2HighWord,TypeU8,0); *inputAutoDriveAG12=0;
    inputAutoDriveAG21=BindODMem(AutoDriveStartIndex,SubindexCamera2RPDO2HighWord,TypeU8,1); *inputAutoDriveAG21=0;
    inputAutoDriveAG22=BindODMem(AutoDriveStartIndex,SubindexCamera2RPDO2HighWord,TypeU8,0); *inputAutoDriveAG22=0;

    //Status
    inputAutoDriveST11=BindODMem(AutoDriveStartIndex,SubindexCamera1RPDO3LowWord,TypeU8,1); *inputAutoDriveST11=0;
    inputAutoDriveST12=BindODMem(AutoDriveStartIndex,SubindexCamera1RPDO3LowWord,TypeU8,0); *inputAutoDriveST12=0;
    inputAutoDriveST21=BindODMem(AutoDriveStartIndex,SubindexCamera2RPDO3LowWord,TypeU8,1); *inputAutoDriveST21=0;
    inputAutoDriveST22=BindODMem(AutoDriveStartIndex,SubindexCamera2RPDO3LowWord,TypeU8,0); *inputAutoDriveST22=0;

    //Output Parameter of the auto drive
    outputKamera1NMT=BindODMem(AutoDriveStartIndex,SubindexCamera1NMT,TypeU16,0); *outputKamera1NMT=0x0000;
    outputKamera2NMT=BindODMem(AutoDriveStartIndex,SubindexCamera2NMT,TypeU16,0); *outputKamera2NMT=0x0000;

    outputAutoDriveY1Value=BindODMem(AutoDriveStartIndex,SubindexAutoDriveYValue,TypeS16,0); *outputAutoDriveY1Value=0;
    outputAutoDriveY2Value=BindODMem(AutoDriveStartIndex,SubindexAutoDriveYValue,TypeS16,1); *outputAutoDriveY2Value=0;

    outputAutoDriveX1Value=BindODMem(AutoDriveStartIndex,SubindexAutoDriveXValue,TypeS16,0); *outputAutoDriveX1Value=0;
    outputAutoDriveX2Value=BindODMem(AutoDriveStartIndex,SubindexAutoDriveXValue,TypeS16,1); *outputAutoDriveX2Value=0;

    outputAutoDriveAG1Value=BindODMem(AutoDriveStartIndex,SubindexAutoDriveAGValue,TypeS16,0); *outputAutoDriveAG1Value=0;
    outputAutoDriveAG2Value=BindODMem(AutoDriveStartIndex,SubindexAutoDriveAGValue,TypeS16,1); *outputAutoDriveAG2Value=0;

    outputAutoDriveToSlaveY1Value=BindODMem(RemoteControlStartIndex,SubindexTelegramm2ToSlaveLowWord,TypeS8,0); *outputAutoDriveToSlaveY1Value=0;
    outputAutoDriveToSlaveY2Value=BindODMem(RemoteControlStartIndex,SubindexTelegramm2ToSlaveLowWord,TypeS8,1); *outputAutoDriveToSlaveY2Value=0;
    outputAutoDriveToSlaveXValue=BindODMem(RemoteControlStartIndex,SubindexTelegramm2ToSlaveLowWord,TypeU16,1); *outputAutoDriveToSlaveXValue=0;

    outputAutoDriveToSlaveState=BindODMem(RemoteControlStartIndex,SubindexTelegramm2ToSlaveHighWord,TypeU8,3); *outputAutoDriveToSlaveState=0x00;

    outputAutoDriveSetSpeedX=BindODMem(DriveModuleStartIndex,SubindexDriveSysSetSpeedX,TypeF32,0); *outputAutoDriveSetSpeedX=0.0;
    outputAutoDriveSetSpeedY=BindODMem(DriveModuleStartIndex,SubindexDriveSysSetSpeedY,TypeF32,0); *outputAutoDriveSetSpeedY=0.0;
    outputAutoDriveSetOmegaZ=BindODMem(DriveModuleStartIndex,SubindexDriveSysSetOmegaZ,TypeF32,0); *outputAutoDriveSetOmegaZ=0.0;

    outputAutoDriveInitSDOControlWord=BindODMem(DevParaStartIndex,SubindexSysSDOControlWord,TypeU32,0);
    outputAutoDriveInitSDOContent=BindODMem(DevParaStartIndex,SubindexSysSDOContent,TypeU32,0);

    outputAutoDriveCameraControlWord=BindODMem(AutoDriveStartIndex,SubindexCameraTPDO1LowWord,TypeU32,0);
    outputIOPortFinishHupe=BindODMem(IOPortStartIndex,SubindexOutput53,TypeU32,0);

    outputAutoDriveState=BindODMem(AutoDriveStartIndex,SubindexAutoDriveControlWord,TypeU8,3); *outputAutoDriveState=AutoDriveStateNoLane;

    outputNumOfBand=BindODMem(AutoDriveStartIndex,SubindexAutoDriveControlWord,TypeS8,2);   *outputNumOfBand=-1;
}



//=================================================================================================
/*!
    Function: hupe for auto drive
    output: None
*/
//=================================================================================================
void FinishHupe(void){
    static uint16 local_tick;

    if(*outputAutoDriveState==AutoDriveStateInPos) local_tick=3;
    if(local_tick){
        *inputAutoDriveControlWord|=KeyAutoDriveHupeReq;
    }
    else{
        *inputAutoDriveControlWord&=~KeyAutoDriveHupeReq;
    }
    if(local_tick>0) local_tick--;
}

//=================================================================================================
/*!
    Function: set the speed according to the y-error
    output: None
*/
//=================================================================================================
void setDriveSpeed(void){
    static uint16 state;
    static uint16 local_tick;
    uint16 flag;
    sint16 limit_up_Y=20;
    sint16 limit_down_Y=10;

    flag=0;
    if(state==0){
        if(Abs(*outputAutoDriveY1Value)>limit_up_Y) flag=1;
        if(Abs(*outputAutoDriveY2Value)>limit_up_Y) flag=1;
        if(flag==1) local_tick++;
        if(local_tick>30){
            local_tick=0;
            state=1;
        }
        *inputAutoDriveControlWord&=~KeyAutoDriveCurveDrive;
        AutoDriveControllerDaten.Vc=(float32)(*inputAutoDriveReferenzSpeed)*0.001;
    }
    else if(state==1){
        if((Abs(*outputAutoDriveY1Value)<limit_down_Y)&&(Abs(*outputAutoDriveY2Value)<limit_down_Y)) flag=1;
        if(flag==1) local_tick++;
        if(local_tick>100){
            local_tick=0;
            state=0;
        }
        *inputAutoDriveControlWord|=KeyAutoDriveCurveDrive;
        AutoDriveControllerDaten.Vc=(float32)(*inputAutoDriveReferenzSpeed)*0.001*0.;
    }
}

//=================================================================================================
/*!
    Function: manage for auto drive
    output: None
*/
//=================================================================================================
void AutoDriveManage(void){
    uint32 tmp;
    static uint16 local_tick[2];

    tmp=KeyAutoDriveK1BandFind+KeyAutoDriveK2BandFind;
    if((*inputAutoDriveControlWord&tmp)==tmp){
        local_tick[1]=200;
        if(*inputAutoDriveControlWord&KeyAutoDriveInStopZone){
            *outputNumOfBand=(*outputAutoDriveX1Value+500)/1000-1;
            if(*outputAutoDriveState==AutoDriveStateOnLane){
                *outputAutoDriveState=AutoDriveStateOnTagNoUsed;
            }
            else if(*outputAutoDriveState==AutoDriveStateOnTagNoUsed){
                if(*inputAutoDriveControlWord&KeyAutoDrivePosReady){
                    *outputAutoDriveState=AutoDriveStateInPos;
                    local_tick[0]=10;
                }
                if(*inputAutoDriveControlWord&KeyAutoDriveQuitReq){
                    *inputAutoDriveControlWord&=~KeyAutoDriveQuitReq;
                    *outputAutoDriveState=AutoDriveStateOnTagUsed;
                }
            }
            else if(*outputAutoDriveState==AutoDriveStateInPos){
                if(local_tick[0]==0) *outputAutoDriveState=AutoDriveStateLiftButtom;
            }
            else if(*outputAutoDriveState==AutoDriveStateLiftButtom){
                if(*inputAutoDriveControlWord&KeyAutoDriveQuitReq){
                    *inputAutoDriveControlWord&=~KeyAutoDriveQuitReq;
                    *outputAutoDriveState=AutoDriveStateOnTagUsed;
                }
            }
            else if(*outputAutoDriveState==AutoDriveStateOnTagUsed){
                local_tick[0]++;
            }
            else *outputAutoDriveState=AutoDriveStateOnLane;
        }
        else {
            *outputAutoDriveState=AutoDriveStateOnLane;
            *outputNumOfBand=-1;
        }
    }
    else{
        if(local_tick[1]==0) *outputAutoDriveState=AutoDriveStateNoLane;
    }
    if(local_tick[0]>0) local_tick[0]--;
    if(local_tick[1]>0) local_tick[1]--;
    if((*outputAutoDriveState!=AutoDriveStateLiftButtom)||(*outputAutoDriveState!=AutoDriveStateOnTagNoUsed)) *inputAutoDriveControlWord&=~KeyAutoDriveQuitReq;
}

//=================================================================================================
/*!
    Function: parameter update for auto drive
    output: None
*/
//=================================================================================================
void AutoDriveParaUpdate(void){
    static uint8 updateflag[4];

    if(updateflag[0]>=100){
        AutoDriveControllerDaten.kp1=(float32)(*inputAutoDriveControlKp1)*0.001;
        AutoDriveControllerDaten.kp2=(float32)(*inputAutoDriveControlKp2)*0.001;
        AutoDriveControllerDaten.ki1=(float32)(*inputAutoDriveControlKi1)*0.001;
        AutoDriveControllerDaten.ki2=(float32)(*inputAutoDriveControlKi2)*0.001;
        updateflag[0]=0;
    }
    if(updateflag[1]>=1){
        *outputAutoDriveToSlaveY1Value=(sint8)(*outputAutoDriveY1Value);
        *outputAutoDriveToSlaveY2Value=(sint8)(*outputAutoDriveY2Value);
        *outputAutoDriveToSlaveXValue=(uint16)(*outputAutoDriveX1Value);

        *outputAutoDriveToSlaveState=*outputAutoDriveState;

        if(*outputAutoDriveState==AutoDriveStateNoLane) *inputAutoDriveControlWord&=~KeyAutoDriveOnLane;
        else *inputAutoDriveControlWord|=KeyAutoDriveOnLane;

        updateflag[1]=0;
    }
    setDriveSpeed();

    updateflag[0]++;
    updateflag[1]++;
}

//=================================================================================================
/*!
    Function: initial all the Camera
    output: None
*/
//=================================================================================================
void InitKamera(void){
    static uint16 local_tick;
    static uint16 sendflag;

    if(local_tick>100){
        if(sendflag==0){
            if((*outputAutoDriveInitSDOControlWord&KeyAutoDriveSDOControlWordEnable)==0){
                *outputAutoDriveInitSDOControlWord=0x0b3001bf;
                *outputAutoDriveInitSDOContent=0x00000002;
                sendflag++;
                local_tick=70;
            }
        }
        else if(sendflag==1){
            if((*outputAutoDriveInitSDOControlWord&KeyAutoDriveSDOControlWordEnable)==0){
                *outputAutoDriveInitSDOControlWord=0x0b3001df;
                *outputAutoDriveInitSDOContent=0x00000002;
                sendflag++;
                local_tick=70;
            }
        }
        else if(sendflag==2){
            if((*outputAutoDriveInitSDOControlWord&KeyAutoDriveSDOControlWordEnable)==0){
                *outputAutoDriveInitSDOControlWord=0x0c3001bf;
                *outputAutoDriveInitSDOContent=0x00000001;
                sendflag++;
                local_tick=70;
            }
        }
        else if(sendflag==3){
            if((*outputAutoDriveInitSDOControlWord&KeyAutoDriveSDOControlWordEnable)==0){
                *outputAutoDriveInitSDOControlWord=0x0c3001bf;
                *outputAutoDriveInitSDOContent=0x00000001;
                sendflag++;
                local_tick=70;
            }
        }
        else if(sendflag==4){
            if((*outputAutoDriveInitSDOControlWord&KeyAutoDriveSDOControlWordEnable)==0){
                *outputAutoDriveInitSDOControlWord=0x0c3001df;
                *outputAutoDriveInitSDOContent=0x00000001;
                sendflag++;
                local_tick=70;
            }
        }
        else if(sendflag==5){
            if((*outputAutoDriveInitSDOControlWord&KeyAutoDriveSDOControlWordEnable)==0){
                *outputAutoDriveInitSDOControlWord=0x001017af;
                *outputAutoDriveInitSDOContent=0x000001f4;
                sendflag++;
                local_tick=60;
            }
        }
        else if(sendflag==6){
            if((*outputAutoDriveInitSDOControlWord&KeyAutoDriveSDOControlWordEnable)==0){
                *outputAutoDriveInitSDOControlWord=0x001017cf;
                *outputAutoDriveInitSDOContent=0x000001f4;
                sendflag++;
                local_tick=60;
            }
        }
    }
    if(local_tick<300) local_tick++;
}

//=================================================================================================
/*!
    Function: start all the Camera
    output: None
*/
//=================================================================================================
void startKarmea(void){
    if (*inputKamera1NodeStatus==NodeStatusPRE_OPERATIONAL){
        *outputKamera1NMT=NODE_START;
        *outputKamera1NMT=(*outputKamera1NMT<<8)+0x0001;
    }
    if (*inputKamera2NodeStatus==NodeStatusPRE_OPERATIONAL){
        *outputKamera2NMT=NODE_START;
        *outputKamera2NMT=(*outputKamera2NMT<<8)+0x0001;
    }

    if(*inputAutoDriveControlWord&KeyAutoDriveEnable){
        *outputAutoDriveCameraControlWord=KeyCameraControlWordMuster;
    }
    else{
        *outputAutoDriveCameraControlWord=0x00000011;
    }
}

//=================================================================================================
/*!
    Function: this is a task for auto drive control
    output: None
*/
//=================================================================================================
void Task_AutoDriveControl(void* argv){
    argv=argv;
    while(TRUE){
        InitKamera();
        startKarmea();
        AutoDriveParaUpdate();
        GetMeasurementAutoDrive();
        AutoDriveManage();
        if(*inputAutoDriveControlWord&KeyAutoDriveEnable){
            switch(AutoDriveState){
                case AutoDriveStateOnLane: AutoDriveController();
                case AutoDriveStateNoLane: AutoDriveResetController();
                case AutoDriveStateInPos: AutoDriveController();
                case AutoDriveStateLiftButtom: AutoDriveController();
                case AutoDriveStateOnTagNoUsed: AutoDriveController();
                case AutoDriveStateOnTagUsed: AutoDriveController();
            }
            FinishHupe();
        }
        x_os_wait_for_events();
    }
}


//=================================================================================================
/*!
    Function: Initial of the auto drive
    output: None
*/
//=================================================================================================
void InitAutoDrive(void){
    InitInterfaceAutoDrive();
    x_os_install_task(PrioTrackingControl, 100, 10, Task_AutoDriveControl, 64);
}
