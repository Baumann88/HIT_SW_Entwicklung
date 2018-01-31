#include <Tracking.h>
#include <TrackingData.h>


#define LimitThetaM           (15.0/180.0*pi)
#define ControlDistance       50
#define StopXDistance         4
#define StopYDistance         2

//=================================================================================================
/*!
    Function: get the measurement value for auto drive
    output: None
*/
//=================================================================================================
void GetMeasurementAutoDrive(void){
    uint32 u32_tmp;
    sint32 s32_tmp;
    sint16 s16_tmp;
    static float32 oldValueError[2];
    static sint16 oldValueY[2];

    if((*inputAutoDriveST12&0x02)||((*inputAutoDriveST11&0x02)==0)) *inputAutoDriveControlWord|=KeyAutoDriveK1BandFind;
    else *inputAutoDriveControlWord&=~KeyAutoDriveK1BandFind;

    s32_tmp=*inputAutoDriveYp14;
    s32_tmp=(uint32)(*inputAutoDriveYp13)+(s32_tmp<<8);
    s32_tmp=(uint32)(*inputAutoDriveYp12)+(s32_tmp<<8);
    s32_tmp=(uint32)(*inputAutoDriveYp11)+(s32_tmp<<8);
    if((*inputAutoDriveST11&0x02)==0) *outputAutoDriveY1Value=(sint16)s32_tmp;
    else *outputAutoDriveY1Value=(sint16)(0-s32_tmp);
    if((*inputAutoDriveControlWord&KeyAutoDriveK1BandFind)==0){
        *outputAutoDriveY1Value=oldValueY[0];
    }
    else{
        oldValueY[0]=*outputAutoDriveY1Value;
    }


    if((*inputAutoDriveST22&0x02)||((*inputAutoDriveST21&0x02)==0)) *inputAutoDriveControlWord|=KeyAutoDriveK2BandFind;
    else *inputAutoDriveControlWord&=~KeyAutoDriveK2BandFind;

    s32_tmp=*inputAutoDriveYp24;
    s32_tmp=(uint32)(*inputAutoDriveYp23)+(s32_tmp<<8);
    s32_tmp=(uint32)(*inputAutoDriveYp22)+(s32_tmp<<8);
    s32_tmp=(uint32)(*inputAutoDriveYp21)+(s32_tmp<<8);
    if((*inputAutoDriveST21&0x02)==0) *outputAutoDriveY2Value=(sint16)s32_tmp;
    else *outputAutoDriveY2Value=(sint16)s32_tmp;
    if((*inputAutoDriveControlWord&KeyAutoDriveK2BandFind)==0){
        *outputAutoDriveY2Value=oldValueY[1];
    }
    else{
        oldValueY[1]=*outputAutoDriveY2Value;
    }

    s32_tmp=*inputAutoDriveXp14;
    s32_tmp=(uint32)(*inputAutoDriveXp13)+(s32_tmp<<8);
    s32_tmp=(uint32)(*inputAutoDriveXp12)+(s32_tmp<<8);
    s32_tmp=(uint32)(*inputAutoDriveXp11)+(s32_tmp<<8);
    *outputAutoDriveX1Value=(sint16)s32_tmp;

    /*s32_tmp=*inputAutoDriveXp24;
    s32_tmp=(uint32)(*inputAutoDriveXp23)+(s32_tmp<<8);
    s32_tmp=(uint32)(*inputAutoDriveXp22)+(s32_tmp<<8);
    s32_tmp=(uint32)(*inputAutoDriveXp21)+(s32_tmp<<8);
    *outputAutoDriveX2Value=(sint16)s32_tmp;*/

    if((*inputAutoDriveST11&0x02)==0) *inputAutoDriveControlWord|=KeyAutoDriveInStopZone;
    else *inputAutoDriveControlWord&=~KeyAutoDriveInStopZone;

    /*s16_tmp=*inputAutoDriveAG12;
    s16_tmp=(uint16)(*inputAutoDriveAG11)+(s16_tmp<<8);
    if(s16_tmp>55) s16_tmp=s16_tmp-360;
    *outputAutoDriveAG1Value=(sint16)s16_tmp;

    s16_tmp=*inputAutoDriveAG22;
    s16_tmp=(uint16)(*inputAutoDriveAG21)+(s16_tmp<<8);
    if(s16_tmp>55) s16_tmp=s16_tmp-360;
    *outputAutoDriveAG2Value=(sint16)s16_tmp;*/

    AutoDriveControllerDaten.e_n=(float32)(*outputAutoDriveY1Value+*outputAutoDriveY2Value)/2.0;
    AutoDriveControllerDaten.e_theta=(float32)(*outputAutoDriveY1Value-*outputAutoDriveY2Value);
}

//=================================================================================================
/*!
    Function: reset Controller for auto drive
    output: None
*/
//=================================================================================================
void AutoDriveResetController(void){
    *outputAutoDriveSetSpeedX=0.0;
    *outputAutoDriveSetSpeedY=0.0;
    *outputAutoDriveSetOmegaZ=0.0;
}


//=================================================================================================
/*!
    Function: Controller for auto drive
    output: None
*/
//=================================================================================================
void AutoDriveController(void){
    static uint16 tick_local;
    float32 ThetaM;
    float32 OmegaLimit;
    sint16 ErrorX;
    uint16 slow;
    static float32 setVx,setVy,setOmegaZ;


    /*if(tick_local<3){
        tick_local++;
        return;
    }
    else tick_local=0;*/


    if((*outputAutoDriveState==AutoDriveStateOnTagNoUsed)||(*outputAutoDriveState==AutoDriveStateInPos)||(*outputAutoDriveState==AutoDriveStateLiftButtom)) slow=1;
    else slow=0;


    ThetaM=AutoDriveControllerDaten.e_n*AutoDriveControllerDaten.kp1;

    if(ThetaM>LimitThetaM) ThetaM=LimitThetaM;
    else if(ThetaM<(0.0-LimitThetaM)) ThetaM=-LimitThetaM;
    OmegaLimit=AutoDriveControllerDaten.Vc/Rmin2Dim/5.0;

    if(*inputAutoDriveControlWord&KeyAutoDriveForwardDrive){
        if(slow){
            ErrorX=*outputAutoDriveX1Value-AutoDriveStopPos[*outputNumOfBand];
            if((ErrorX<StopXDistance)&&(ErrorX>-StopXDistance)){
                *inputAutoDriveControlWord|=KeyAutoDrivePosReady;
                *outputAutoDriveSetSpeedX=0.0;
                setVy=0.0;
                setOmegaZ=0.0;
            }
            else{
                *inputAutoDriveControlWord&=~KeyAutoDrivePosReady;
                if((ErrorX<ControlDistance)&&(ErrorX>-ControlDistance)){
                    *outputAutoDriveSetSpeedX=AutoDriveControllerDaten.Vc/18.0;
                    setVy=0.0;
                    setOmegaZ=0.0;
                }
                else *outputAutoDriveSetSpeedX=AutoDriveControllerDaten.Vc/5.0;
            }
            setVx=0;
        }
        else{
            //*outputAutoDriveSetSpeedX=AutoDriveControllerDaten.Vc;
            if(setVx<AutoDriveControllerDaten.Vc) setVx+=0.0002;
            else setVx=AutoDriveControllerDaten.Vc;
            *outputAutoDriveSetSpeedX=setVx;
        }
        setVy=*outputAutoDriveSetSpeedX*ThetaM;
        setOmegaZ=*outputAutoDriveSetSpeedX*AutoDriveControllerDaten.kp2*AutoDriveControllerDaten.e_theta;
        if(setOmegaZ>OmegaLimit) setOmegaZ=OmegaLimit;
        else if(setOmegaZ<-OmegaLimit) setOmegaZ=-OmegaLimit;
    }
    else if(*inputAutoDriveControlWord&KeyAutoDriveBackwardDrive){
        if(slow){
            ErrorX=*outputAutoDriveX1Value-AutoDriveStopPos[*outputNumOfBand];
            if((ErrorX<StopXDistance)&&(ErrorX>-StopXDistance)){
                *inputAutoDriveControlWord|=KeyAutoDrivePosReady;
                *outputAutoDriveSetSpeedX=0.0;
                setVy=0.0;
                setOmegaZ=0.0;
            }
            else{
                *inputAutoDriveControlWord&=~KeyAutoDrivePosReady;
                if((ErrorX<ControlDistance)&&(ErrorX>-ControlDistance)){
                    *outputAutoDriveSetSpeedX=-AutoDriveControllerDaten.Vc/18.0;
                    setVy=0.0;
                    setOmegaZ=0.0;
                }
                else *outputAutoDriveSetSpeedX=-AutoDriveControllerDaten.Vc/5.0;
            }
            setVx=0;
        }
        else{
            //*outputAutoDriveSetSpeedX=-AutoDriveControllerDaten.Vc;
            if(setVx>-AutoDriveControllerDaten.Vc) setVx-=0.0002;
            else setVx=-AutoDriveControllerDaten.Vc;
            *outputAutoDriveSetSpeedX=setVx;
        }
        setVy=-*outputAutoDriveSetSpeedX*ThetaM;
        setOmegaZ=-*outputAutoDriveSetSpeedX*AutoDriveControllerDaten.kp2*AutoDriveControllerDaten.e_theta;
        if(setOmegaZ>OmegaLimit) setOmegaZ=OmegaLimit;
        else if(setOmegaZ<-OmegaLimit) setOmegaZ=-OmegaLimit;
    }
    else{
        setVx=0.0;
        setVy=0.0;
        setOmegaZ=0.0;
        *outputAutoDriveSetSpeedX=0.0;
        *outputAutoDriveSetSpeedY=0.0;
        *outputAutoDriveSetOmegaZ=0.0;
    }

    if(abs(setVy-*outputAutoDriveSetSpeedY)<0.005) *outputAutoDriveSetSpeedY=setVy;
    else{
        if(*outputAutoDriveSetSpeedY>setVy) *outputAutoDriveSetSpeedY-=AutoDriveControllerDaten.ki1;
        else if(*outputAutoDriveSetSpeedY<setVy) *outputAutoDriveSetSpeedY+=AutoDriveControllerDaten.ki1;
    }

    if(abs(setOmegaZ-*outputAutoDriveSetOmegaZ)<0.005) *outputAutoDriveSetOmegaZ=setOmegaZ;
    else{
        if(*outputAutoDriveSetOmegaZ>setOmegaZ) *outputAutoDriveSetOmegaZ-=AutoDriveControllerDaten.ki2;
        else if(*outputAutoDriveSetOmegaZ<setOmegaZ) *outputAutoDriveSetOmegaZ+=AutoDriveControllerDaten.ki2;
    }
}


