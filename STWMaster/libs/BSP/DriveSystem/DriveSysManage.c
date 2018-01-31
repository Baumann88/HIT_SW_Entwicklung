#include "DriveSys.h"
#include "DriveSysData.h"

static uint16 Lang2Cross;

//=================================================================================================
/*!
    Function: Set the speed and angle of all drive module by Vorderrad
    output: None
*/
//=================================================================================================
void SetDriveModuleVorderrad(void){
    float32 r;
    float32 Vx;
    float32 tmp;
    float32 R11,R12,R21,R22;

    tmp=*inputDriveSysAngle;
    Vx=(*inputDriveSysSpeed)*cos(tmp);
    if(tmp!=0.0){
        if(*inputDriveSysControlWord&KeyDriveSysCrossDriveSet){
            r=B/tan(tmp);
            R11=r-L/2.0;
            R21=r+L/2.0;
            SetTheta12=atan(B/R11);
            SetTheta22=atan(B/R21);
            SetTheta11=0.0;
            SetTheta21=0.0;
            R12=B/sin(SetTheta12);
            R22=B/sin(SetTheta22);
            SetV11=-Vx/r*R11;
            SetV12=Vx/r*R12;
            SetV21=Vx/r*R21;
            SetV22=-Vx/r*R22;
        }
        else{
            r=L/tan(tmp);
            R21=r-B/2.0;
            R22=r+B/2.0;
            SetTheta11=atan(L/R21);
            SetTheta12=atan(L/R22);
            SetTheta21=0.0;
            SetTheta22=0.0;
            R11=L/sin(SetTheta11);
            R12=L/sin(SetTheta12);
            SetV11=Vx/r*R11;
            SetV12=Vx/r*R12;
            SetV21=Vx/r*R21;
            SetV22=Vx/r*R22;
        }

    }
    else{
        if(*inputDriveSysControlWord&KeyDriveSysCrossDriveSet){
            SetV11=-Vx;
            SetV12=Vx;
            SetV21=Vx;
            SetV22=-Vx;
        }
        else{
            SetV11=Vx;
            SetV12=Vx;
            SetV21=Vx;
            SetV22=Vx;
        }
        SetTheta11=0.0;
        SetTheta12=0.0;
        SetTheta21=0.0;
        SetTheta22=0.0;
    }
}

//=================================================================================================
/*!
    Function: Set the speed and angle of all drive module by Hinterrad
    output: None
*/
//=================================================================================================
void SetDriveModuleHinterrad(void){
    float32 r;
    float32 Vx;
    float32 tmp;
    float32 R11,R12,R21,R22;

    tmp=*inputDriveSysAngle;
    Vx=(*inputDriveSysSpeed)*cos(tmp);
    if(tmp!=0.0){
        if(*inputDriveSysControlWord&KeyDriveSysCrossDriveSet){
            r=B/tan(tmp);
            R12=r+L/2.0;
            R22=r-L/2.0;
            SetTheta12=0.0;
            SetTheta22=0.0;
            SetTheta11=atan(B/R12);
            SetTheta21=atan(B/R22);
            R11=B/sin(SetTheta11);
            R21=B/sin(SetTheta21);
            SetV11=-Vx/r*R11;
            SetV12=Vx/r*R12;
            SetV21=Vx/r*R21;
            SetV22=-Vx/r*R22;
        }
        else{
            r=L/tan(tmp);
            R11=r+B/2.0;
            R12=r-B/2.0;
            SetTheta11=0.0;
            SetTheta12=0.0;
            SetTheta21=atan(L/R11);
            SetTheta22=atan(L/R12);
            R21=L/sin(SetTheta21);
            R22=L/sin(SetTheta22);
            SetV11=Vx/r*R11;
            SetV12=Vx/r*R12;
            SetV21=Vx/r*R21;
            SetV22=Vx/r*R22;
        }

    }
    else{
        if(*inputDriveSysControlWord&KeyDriveSysCrossDriveSet){
            SetV11=-Vx;
            SetV12=Vx;
            SetV21=Vx;
            SetV22=-Vx;
        }
        else{
            SetV11=Vx;
            SetV12=Vx;
            SetV21=Vx;
            SetV22=Vx;
        }
        SetTheta11=0.0;
        SetTheta12=0.0;
        SetTheta21=0.0;
        SetTheta22=0.0;
    }
}
//=================================================================================================
/*!
    Function: Set the speed and angle of all drive module by Allrad
    output: None
*/
//=================================================================================================
void SetDriveModuleAllrad(void){
    float32 r;
    float32 V;
    float32 tmp;
    float32 r1,r2;
    float32 R1,R2;

    tmp=*inputDriveSysAngle;
    V=*inputDriveSysSpeed;
    if(tmp!=0.0){
        if(*inputDriveSysControlWord&KeyDriveSysCrossDriveSet){
            r=B/2.0/tan(tmp);
            r1=r-L/2.0;
            r2=r+L/2.0;
            SetTheta12=atan(B/2.0/r1);
            SetTheta22=atan(B/2.0/r2);
            SetTheta11=0.0-SetTheta12;
            SetTheta21=0.0-SetTheta22;
            R1=B/2.0/sin(SetTheta12);
            R2=B/2.0/sin(SetTheta22);
            SetV11=-V/r*R1;
            SetV12=V/r*R1;
            SetV21=V/r*R2;
            SetV22=-V/r*R2;
        }
        else{
            r=L/2.0/tan(tmp);
            r1=r-B/2.0;
            r2=r+B/2.0;
            SetTheta11=atan(L/2.0/r1);
            SetTheta12=atan(L/2.0/r2);
            SetTheta21=0.0-SetTheta11;
            SetTheta22=0.0-SetTheta12;
            R1=L/2.0/sin(SetTheta11);
            R2=L/2.0/sin(SetTheta12);
            SetV11=V/r*R1;
            SetV12=V/r*R2;
            SetV21=V/r*R1;
            SetV22=V/r*R2;
        }
    }
    else{
        if(*inputDriveSysControlWord&KeyDriveSysCrossDriveSet){
            SetV11=-V;
            SetV12=V;
            SetV21=V;
            SetV22=-V;
        }
        else{
            SetV11=V;
            SetV12=V;
            SetV21=V;
            SetV22=V;
        }
        SetTheta11=0.0;
        SetTheta12=0.0;
        SetTheta21=0.0;
        SetTheta22=0.0;

    }
}
//=================================================================================================
/*!
    Function: Set the speed and angle of all drive module by Krebsgang
    output: None
*/
//=================================================================================================
void SetDriveModuleKrebsgang(void){
    SetTheta11=*inputDriveSysAngle;
    SetTheta12=*inputDriveSysAngle;
    SetTheta21=*inputDriveSysAngle;
    SetTheta22=*inputDriveSysAngle;
    if(*inputDriveSysControlWord&KeyDriveSysCrossDriveSet){
        SetV11=-*inputDriveSysSpeed;
        SetV12=*inputDriveSysSpeed;
        SetV21=*inputDriveSysSpeed;
        SetV22=-*inputDriveSysSpeed;
    }
    else{
        SetV11=*inputDriveSysSpeed;
        SetV12=*inputDriveSysSpeed;
        SetV21=*inputDriveSysSpeed;
        SetV22=*inputDriveSysSpeed;
    }

}


//=================================================================================================
/*!
    Function: Set the speed and angle of all drive module by Rundgang
    output: None
*/
//=================================================================================================
void SetDriveModuleRundgang(void){
    uint8 flagSetV;
    float32 ErrAngle;
    float32 MaxErrAngle,MinErrAngle;

    MaxErrAngle=10.0*Grad2Rad;
    MinErrAngle=-MaxErrAngle;
    flagSetV=0x00;
    if(*inputDriveSysControlWord&KeyDriveSysCrossDriveSet){
        SetTheta11=pi/2.0-asin(L/S);
        SetTheta12=asin(L/S)-pi/2.0;
        SetTheta21=asin(L/S)-pi/2.0;
        SetTheta22=pi/2.0-asin(L/S);
        ErrAngle=SetTheta11-DriveModule11ActualAngle;
        if((ErrAngle<MaxErrAngle)&&(ErrAngle>MinErrAngle)) flagSetV+=0x01;
        ErrAngle=SetTheta12-DriveModule12ActualAngle;
        if((ErrAngle<MaxErrAngle)&&(ErrAngle>MinErrAngle)) flagSetV+=0x02;
        ErrAngle=SetTheta21-DriveModule21ActualAngle;
        if((ErrAngle<MaxErrAngle)&&(ErrAngle>MinErrAngle)) flagSetV+=0x04;
        ErrAngle=SetTheta22-DriveModule22ActualAngle;
        if((ErrAngle<MaxErrAngle)&&(ErrAngle>MinErrAngle)) flagSetV+=0x08;
        if(flagSetV==0x0f){
            SetV11=0.0-*inputDriveSysSpeed;
            SetV12=*inputDriveSysSpeed;
            SetV21=0.0-*inputDriveSysSpeed;
            SetV22=*inputDriveSysSpeed;
        }
        else{
            SetV11=0.0;
            SetV12=0.0;
            SetV21=0.0;
            SetV22=0.0;
        }
    }
    else{
        SetTheta11=-asin(L/S);
        SetTheta12=asin(L/S);
        SetTheta21=asin(L/S);
        SetTheta22=-asin(L/S);
        ErrAngle=SetTheta11-DriveModule11ActualAngle;
        if((ErrAngle<MaxErrAngle)&&(ErrAngle>MinErrAngle)) flagSetV+=0x01;
        ErrAngle=SetTheta12-DriveModule12ActualAngle;
        if((ErrAngle<MaxErrAngle)&&(ErrAngle>MinErrAngle)) flagSetV+=0x02;
        ErrAngle=SetTheta21-DriveModule21ActualAngle;
        if((ErrAngle<MaxErrAngle)&&(ErrAngle>MinErrAngle)) flagSetV+=0x04;
        ErrAngle=SetTheta22-DriveModule22ActualAngle;
        if((ErrAngle<MaxErrAngle)&&(ErrAngle>MinErrAngle)) flagSetV+=0x08;
        if(flagSetV==0x0f){
            SetV11=*inputDriveSysSpeed;
            SetV12=0.0-*inputDriveSysSpeed;
            SetV21=*inputDriveSysSpeed;
            SetV22=0.0-*inputDriveSysSpeed;
        }
        else{
            SetV11=0.0;
            SetV12=0.0;
            SetV21=0.0;
            SetV22=0.0;
        }
    }
}

//=================================================================================================
/*!
    Function: Set the speed and angle of all drive module by Parken
    output: None
*/
//=================================================================================================
void SetDriveModuleParken(void){
    if(*inputDriveSysControlWord&KeyDriveSysCrossDriveSet){
        SetTheta11=-20.0*Grad2Rad;
        SetTheta12=20.0*Grad2Rad;
        SetTheta21=20.0*Grad2Rad;
        SetTheta22=-20.0*Grad2Rad;
    }
    else{
        SetTheta11=20.0*Grad2Rad;
        SetTheta12=-20.0*Grad2Rad;
        SetTheta21=-20.0*Grad2Rad;
        SetTheta22=20.0*Grad2Rad;
    }
    SetV11=0.0;
    SetV12=0.0;
    SetV21=0.0;
    SetV22=0.0;
}

//=================================================================================================
/*!
    Function: calculate the set speed and steering angle for all 4 drive module during the given
    SpeedX, SpeedY, OmegaZ or Speed with Angle from RC
    output: None
*/
//=================================================================================================
void SetSteering(void){
    uint32 steeringWord_Tmp;
    static uint32 steeringWord_Tmp_OldValue;



    //two dimensional drive
    if(*inputDriveSysControlWord&KeyDriveSysTwoDimensionDrive){
        if((*inputDriveSysSpeedX!=0.0)||(*inputDriveSysSpeedY!=0.0)||(*inputDriveSysOmegaZ!=0.0)) DriveSysTick=5;

        /*LmulOmegaZ=(*inputDriveSysOmegaZ)*L;
        BmulOmegaZ=(*inputDriveSysOmegaZ)*B;
        Vxmul2=(*inputDriveSysSpeedX)*2.0;
        Vymul2=(*inputDriveSysSpeedY)*2.0;
        if((Vxmul2-BmulOmegaZ)==0.0){
            SetTheta11=0.0;
            SetTheta21=0.0;
        }
        else{
            SetTheta11=atanf((Vymul2+LmulOmegaZ)/(Vxmul2-BmulOmegaZ));
            SetTheta21=atanf((Vymul2-LmulOmegaZ)/(Vxmul2-BmulOmegaZ));
        }
        if((Vxmul2+BmulOmegaZ)==0.0){
            SetTheta12=0.0;
            SetTheta22=0.0;
        }
        else {
            SetTheta12=atanf((Vymul2+LmulOmegaZ)/(Vxmul2+BmulOmegaZ));
            SetTheta22=atanf((Vymul2-LmulOmegaZ)/(Vxmul2+BmulOmegaZ));
        }

        SetV11=(*inputDriveSysSpeedX)*cosf(SetTheta11);
        SetV11+=(*inputDriveSysSpeedY)*sinf(SetTheta11);
        SetV11+=0.5*(L*sinf(SetTheta11)-B*cosf(SetTheta11))*(*inputDriveSysOmegaZ);
        SetV12=(*inputDriveSysSpeedX)*cosf(SetTheta12);
        SetV12+=(*inputDriveSysSpeedY)*sinf(SetTheta12);
        SetV12+=0.5*(L*sinf(SetTheta12)+B*cosf(SetTheta12))*(*inputDriveSysOmegaZ);
        SetV21=(*inputDriveSysSpeedX)*cosf(SetTheta21);
        SetV21+=(*inputDriveSysSpeedY)*sinf(SetTheta21);
        SetV21+=-0.5*(L*sinf(SetTheta21)+B*cosf(SetTheta21))*(*inputDriveSysOmegaZ);
        SetV22=(*inputDriveSysSpeedX)*cosf(SetTheta22);
        SetV22+=(*inputDriveSysSpeedY)*sinf(SetTheta22);
        SetV22+=-0.5*(L*sinf(SetTheta22)-B*cosf(SetTheta22))*(*inputDriveSysOmegaZ);
        DriveModule11Angle=SetTheta11;
        DriveModule12Angle=SetTheta12;
        DriveModule21Angle=SetTheta21;
        DriveModule22Angle=SetTheta22;
        DriveModule11Speed=SetV11;
        DriveModule12Speed=SetV12;
        DriveModule21Speed=SetV21;
        DriveModule22Speed=SetV22;*/
    }
    //one dimensional drive
    else{
        if(*inputDriveSysSpeed!=0.0) DriveSysTick=17;
        if(*inputDriveSysAngle!=0.0) DriveSysTick=50;
        steeringWord_Tmp=*inputDriveSysControlWord&0x0000f000;

        //Vorderrad steering
        if(steeringWord_Tmp==KeyDriveSysSteeringModeVorderrad) SetDriveModuleVorderrad();
        //Hinterrad steering
        else if(steeringWord_Tmp==KeyDriveSysSteeringModeHinterrad) SetDriveModuleHinterrad();
        //Allrad steering
        else if(steeringWord_Tmp==KeyDriveSysSteeringModeAllrad) SetDriveModuleAllrad();
        //Krebsgang steering
        else if(steeringWord_Tmp==KeyDriveSysSteeringModeKrebsgang) SetDriveModuleKrebsgang();
        //Rundgang steering
        else if(steeringWord_Tmp==KeyDriveSysSteeringModeRundgang) SetDriveModuleRundgang();
        //Parken
        else if(steeringWord_Tmp==KeyDriveSysSteeringModeParken) SetDriveModuleParken();

        if(steeringWord_Tmp!=steeringWord_Tmp_OldValue) DriveSysTick=40;
        steeringWord_Tmp_OldValue=steeringWord_Tmp;

        //Zero Set Drive
        if(*inputDriveSysControlWord&KeyDriveSysZeroSet){
            DriveSysTick=10;
            SetTheta11=0.0;
            SetTheta12=0.0;
            SetTheta21=0.0;
            SetTheta22=0.0;
        }
    }
}

//=================================================================================================
/*!
    Function: Initial all Inverter
    output: None
*/
//=================================================================================================
void InitInverter(void){
    *outputMotor111ControlWord=0x0000;
    *outputMotor112ControlWord=0x0000;
    *outputMotor121ControlWord=0x0000;
    *outputMotor122ControlWord=0x0000;
    *outputMotor211ControlWord=0x0000;
    *outputMotor212ControlWord=0x0000;
    *outputMotor221ControlWord=0x0000;
    *outputMotor222ControlWord=0x0000;
}
//=================================================================================================
/*!
    Function: Start all Inverter
    output: None
*/
//=================================================================================================
void StartInverter(void){

    if(*inputDriveSysControlWord&KeyDriveSysEnable){
        if (*inputInverter111NodeStatus==NodeStatusPRE_OPERATIONAL){
            *outputInverter111NMT=NODE_START;
            *outputInverter111NMT=(*outputInverter111NMT<<8)+0x0001;
        }
        if (*inputInverter112NodeStatus==NodeStatusPRE_OPERATIONAL){
            *outputInverter112NMT=NODE_START;
            *outputInverter112NMT=(*outputInverter112NMT<<8)+0x0001;
        }
        if (*inputInverter121NodeStatus==NodeStatusPRE_OPERATIONAL){
            *outputInverter121NMT=NODE_START;
            *outputInverter121NMT=(*outputInverter121NMT<<8)+0x0001;
        }
        if (*inputInverter122NodeStatus==NodeStatusPRE_OPERATIONAL){
            *outputInverter122NMT=NODE_START;
            *outputInverter122NMT=(*outputInverter122NMT<<8)+0x0001;
        }
        if (*inputInverter211NodeStatus==NodeStatusPRE_OPERATIONAL){
            *outputInverter211NMT=NODE_START;
            *outputInverter211NMT=(*outputInverter211NMT<<8)+0x0001;
        }
        if (*inputInverter212NodeStatus==NodeStatusPRE_OPERATIONAL){
            *outputInverter212NMT=NODE_START;
            *outputInverter212NMT=(*outputInverter212NMT<<8)+0x0001;
        }
        if (*inputInverter221NodeStatus==NodeStatusPRE_OPERATIONAL){
            *outputInverter221NMT=NODE_START;
            *outputInverter221NMT=(*outputInverter221NMT<<8)+0x0001;
        }
        if (*inputInverter222NodeStatus==NodeStatusPRE_OPERATIONAL){
            *outputInverter222NMT=NODE_START;
            *outputInverter222NMT=(*outputInverter222NMT<<8)+0x0001;
        }
    }
}

//=================================================================================================
/*!
    Function: Reset all Inverter
    output: None
*/
//=================================================================================================
void ResetInverter(void){
    uint16 ControlWordTmp;
    ControlWordTmp=0x0000;
    *outputMotor111ControlWord=ControlWordTmp;
    *outputMotor112ControlWord=ControlWordTmp;
    *outputMotor121ControlWord=ControlWordTmp;
    *outputMotor122ControlWord=ControlWordTmp;
    *outputMotor211ControlWord=ControlWordTmp;
    *outputMotor212ControlWord=ControlWordTmp;
    *outputMotor221ControlWord=ControlWordTmp;
    *outputMotor222ControlWord=ControlWordTmp;
}

//=================================================================================================
/*!
    Function: drive system handle
    output: None
*/
//=================================================================================================
void DriveSysHandle(void){
    static uint32 timeStampDriveSysEnable;

    //switch between cross or lange drive
    if((*inputMotor111StatusByte&0x01)==0&&(*inputMotor112StatusByte&0x01)==0&&(*inputMotor121StatusByte&0x01)==0&&(*inputMotor122StatusByte&0x01)==0){
        if((*inputMotor211StatusByte&0x01)==0&&(*inputMotor212StatusByte&0x01)==0&&(*inputMotor221StatusByte&0x01)==0&&(*inputMotor222StatusByte&0x01)==0){
            if(*inputDriveSysControlWord&KeyDriveSysCrossDriveReq){
                *inputDriveSysControlWord&=~KeyDriveSysCrossDriveReq;
                if((*inputDriveSysControlWord&KeyDriveSysCrossDriveSet)==0){
                    if((*inputDriveSysControlWord&KeyDriveSysIsCrossSwitch)==0){
                        Lang2Cross=1;
                        *inputDriveSysControlWord|=KeyDriveSysIsCrossSwitch;
                        SetTheta11=pi/2.0;
                        SetTheta22=pi/2.0;
                        DriveSysTick=50;
                    }
                }
            }
            if(*inputDriveSysControlWord&KeyDriveSysLangDriveReq){
                if(*inputDriveSysControlWord&KeyDriveSysCrossDriveSet){
                *inputDriveSysControlWord&=~KeyDriveSysLangDriveReq;
                    if((*inputDriveSysControlWord&KeyDriveSysIsCrossSwitch)==0){
                        Lang2Cross=2;
                        *inputDriveSysControlWord|=KeyDriveSysIsCrossSwitch;
                        SetTheta11=-pi/2.0;
                        SetTheta22=-pi/2.0;
                        DriveSysTick=50;
                    }
                }
            }
        }
    }

    //Enable and Disable the Drive System
    if(*inputDriveSysControlWord&KeyDriveSysDisableReq){
        *inputDriveSysControlWord&=~KeyDriveSysDisableReq;
        *inputDriveSysControlWord|=KeyDriveSysStop;
        //*inputDriveSysControlWord&=~KeyDriveSysEnable;
    }
    if(*inputDriveSysControlWord&KeyDriveSysEnableReq){
        *inputDriveSysControlWord&=~KeyDriveSysEnableReq;
        *inputDriveSysControlWord&=~KeyDriveSysStop;
        //*inputDriveSysControlWord&=~KeyDriveSysEnable;
        timeStampDriveSysEnable=x_sys_get_time_ms();
    }
    //Enable the Drive System
    if(Mode==ModeRun){
        if(((*inputDriveSysControlWord&KeyDriveSysStop)==0)&&((*inputDriveSysControlWord&KeyDriveSysEnable)==0)){
            if(x_sys_get_time_ms()-timeStampDriveSysEnable>100)
                *inputDriveSysControlWord|=KeyDriveSysEnable;
        }
        if(*inputDriveSysControlWord&KeyDriveSysStop) *inputDriveSysControlWord&=~KeyDriveSysEnable;
    }
    //Are all motors Stop?
    if((*outputDriveModule11ActualSpeed==0)&&(*outputDriveModule12ActualSpeed==0)&&(*outputDriveModule21ActualSpeed==0)&&(*outputDriveModule22ActualSpeed==0))
        *inputDriveSysControlWord|=KeyDriveSysIsStop;
    else
        *inputDriveSysControlWord&=~KeyDriveSysIsStop;

    //generate the actual speed for output
    *outputDriveModule11ActualSpeed=(sint32)(SpeedValue11*1000.0);
    *outputDriveModule12ActualSpeed=(sint32)(SpeedValue12*1000.0);
    *outputDriveModule21ActualSpeed=(sint32)(SpeedValue21*1000.0);
    *outputDriveModule22ActualSpeed=(sint32)(SpeedValue22*1000.0);

    //generate the actual omega for output
    *outputDriveModule11Omega=(sint32)(DriveModule11Omega*1000.0);
    *outputDriveModule12Omega=(sint32)(DriveModule12Omega*1000.0);
    *outputDriveModule21Omega=(sint32)(DriveModule21Omega*1000.0);
    *outputDriveModule22Omega=(sint32)(DriveModule22Omega*1000.0);

    //generate the actual angle for output
    *outputDriveModule11ActualAngle=(sint32)(DriveModule11ActualAngle*Rad2Grad);
    *outputDriveModule12ActualAngle=(sint32)(DriveModule12ActualAngle*Rad2Grad);
    *outputDriveModule21ActualAngle=(sint32)(DriveModule21ActualAngle*Rad2Grad);
    *outputDriveModule22ActualAngle=(sint32)(DriveModule22ActualAngle*Rad2Grad);

    //for test mode aus kommentieren
    if((*inputDriveSysControlWord&KeyDriveSysTestMode)==0){
        *inputSetDriveModule11Angle=(sint32)(DriveModule11Angle/Grad2Rad);
        *inputSetDriveModule12Angle=(sint32)(DriveModule12Angle/Grad2Rad);
        *inputSetDriveModule21Angle=(sint32)(DriveModule21Angle/Grad2Rad);
        *inputSetDriveModule22Angle=(sint32)(DriveModule22Angle/Grad2Rad);
    }

    if((*inputDriveSysControlWord&KeyDriveSysCrossDriveSet)==0){
       if(SpeedValue11>0.02){
            *inputDriveSysControlWord|=KeyDriveSysIsForward;
            *inputDriveSysControlWord&=~KeyDriveSysIsBackward;
       }
       else if(SpeedValue11<-0.02){
            *inputDriveSysControlWord|=KeyDriveSysIsBackward;
            *inputDriveSysControlWord&=~KeyDriveSysIsForward;
       }
       else{
            *inputDriveSysControlWord&=~KeyDriveSysIsBackward;
            *inputDriveSysControlWord&=~KeyDriveSysIsForward;
       }
    }
    else{
       if(SpeedValue11<-0.02){
            *inputDriveSysControlWord|=KeyDriveSysIsForward;
            *inputDriveSysControlWord&=~KeyDriveSysIsBackward;
       }
       else if(SpeedValue11>0.02){
            *inputDriveSysControlWord|=KeyDriveSysIsBackward;
            *inputDriveSysControlWord&=~KeyDriveSysIsForward;
       }
       else{
            *inputDriveSysControlWord&=~KeyDriveSysIsBackward;
            *inputDriveSysControlWord&=~KeyDriveSysIsForward;
       }
    }

}

//=================================================================================================
/*!
    Function: drive system parameter update
    output: None
*/
//=================================================================================================
void ParameterUpdate(void){
    //ParameterUpdate
    DriveSysOmega=(float32)(*inputDriveSysOmega)*0.001;
    DriveSysAccel=(float32)(*inputDriveSysAccel)*0.001;
    DriveSysDecl=(float32)(*inputDriveSysDecl)*0.001;
    SpeedLimit=(float32)(*inputDriveModuleMaxSpeed)/FactV2rpm;
    PIControllerDaten11.Kp1=(float32)(*inputDriveModule11PIControlKp1)*0.001;
    PIControllerDaten11.Kp2=(float32)(*inputDriveModule11PIControlKp2)*0.001;
    PIControllerDaten11.Ki=(float32)(*inputDriveModule11PIControlKi)*0.001;
    PIControllerDaten12.Kp1=(float32)(*inputDriveModule12PIControlKp1)*0.001;
    PIControllerDaten12.Kp2=(float32)(*inputDriveModule12PIControlKp2)*0.001;
    PIControllerDaten12.Ki=(float32)(*inputDriveModule12PIControlKi)*0.001;
    PIControllerDaten21.Kp1=(float32)(*inputDriveModule21PIControlKp1)*0.001;
    PIControllerDaten21.Kp2=(float32)(*inputDriveModule21PIControlKp2)*0.001;
    PIControllerDaten21.Ki=(float32)(*inputDriveModule21PIControlKi)*0.001;
    PIControllerDaten22.Kp1=(float32)(*inputDriveModule22PIControlKp1)*0.001;
    PIControllerDaten22.Kp2=(float32)(*inputDriveModule22PIControlKp2)*0.001;
    PIControllerDaten22.Ki=(float32)(*inputDriveModule22PIControlKi)*0.001;
    AngleSensor11FactA=(float32)(*inputDriveModule11AngleFactA)*0.001;
    AngleSensor11FactB=(float32)(*inputDriveModule11AngleFactB)*0.001;
    AngleSensor12FactA=(float32)(*inputDriveModule12AngleFactA)*0.001;
    AngleSensor12FactB=(float32)(*inputDriveModule12AngleFactB)*0.001;
    AngleSensor21FactA=(float32)(*inputDriveModule21AngleFactA)*0.001;
    AngleSensor21FactB=(float32)(*inputDriveModule21AngleFactB)*0.001;
    AngleSensor22FactA=(float32)(*inputDriveModule22AngleFactA)*0.001;
    AngleSensor22FactB=(float32)(*inputDriveModule22AngleFactB)*0.001;
}
//=================================================================================================
/*!
    Function: this is a automat of the Drive system
    output: None
*/
//=================================================================================================
void Task_DriveSysManage(void* argv){
    argv=argv;
    uint16 UpdateFlag;

    Mode=ModeInit;
    *inputDriveSysControlWord&=~KeyDriveSysStart;
    *inputDriveSysControlWord&=~KeyDriveSysReset;
    *inputDriveSysControlWord|=KeyDriveSysStop;
    *inputDriveSysControlWord&=~KeyDriveSysEnable;

    Ts11=0.02*1.0;
    Ts12=0.02*1.0;
    Ts21=0.02*1.0;
    Ts22=0.02*1.0;
    Lang2Cross=0;
    while(TRUE){
        switch(Mode){
            //State Init
            case ModeInit:
                //judge the Transifer for State "Run"
                if(*inputDriveSysControlWord&KeyDriveSysStart){
                    *inputDriveSysControlWord&=~KeyDriveSysStart;
                    *inputDriveSysControlWord&=~KeyDriveSysStop;
                    *inputDriveSysControlWord|=KeyDriveSysEnable;
                    Mode=ModeRun;
                }
                break;
            //State Run
            case ModeRun:
                StartInverter();//Start all Inverter
                //judge the Transifer for State "Init"
                if(*inputDriveSysControlWord&KeyDriveSysReset){
                    *inputDriveSysControlWord&=~KeyDriveSysReset;
                    *inputDriveSysControlWord&=~KeyDriveSysEnable;
                    *inputDriveSysControlWord|=KeyDriveSysStop;
                    ResetInverter();
                    Mode=ModeInit;
                }
                break;
            default: break;
        }

        if((*inputDriveSysControlWord&KeyDriveSysEnable)==0){
            DriveModuleReset();
            DriveBrake();
        }

        if(UpdateFlag>=50){
            ParameterUpdate(); // Update the Parameter
            UpdateFlag=0;
        }
        else DriveSysHandle(); // Drive System handle
        UpdateFlag++;

        // Drive or not?
        if(Lang2Cross==1){
            if(DriveSysTick==0){
                DriveSysTick=50;
                Lang2Cross=3;
                SetTheta12=-pi/2.0;
                SetTheta21=-pi/2.0;
            }
        }
        else if(Lang2Cross==3){
            if(DriveSysTick==0){
                *inputDriveSysControlWord|=KeyDriveSysStop;
                *inputDriveSysControlWord&=~KeyDriveSysEnable;
                Lang2Cross=5;
                DriveSysTick=10;
            }
        }
        if(Lang2Cross==2){
            if(DriveSysTick==0){
                SetTheta12=pi/2.0;
                SetTheta21=pi/2.0;
                DriveSysTick=50;
                Lang2Cross=4;
            }
        }
        else if(Lang2Cross==4){
            if(DriveSysTick==0){
                *inputDriveSysControlWord|=KeyDriveSysStop;
                *inputDriveSysControlWord&=~KeyDriveSysEnable;
                Lang2Cross=6;
                DriveSysTick=10;
            }
        }
        if(Lang2Cross==5){
            *inputDriveSysControlWord|=KeyDriveSysCrossDriveSet;
            SetTheta11=0.0;
            DriveModule11Angle=0.0;
            DriveModule11ActualAngle=0.0;
            SetTheta12=0.0;
            DriveModule12Angle=0.0;
            DriveModule12ActualAngle=0.0;
            SetTheta21=0.0;
            DriveModule21Angle=0.0;
            DriveModule21ActualAngle=0.0;
            SetTheta22=0.0;
            DriveModule22Angle=0.0;
            DriveModule22ActualAngle=0.0;
            if(DriveSysTick==0) {
                Lang2Cross=0;
                *inputDriveSysControlWord&=~KeyDriveSysIsCrossSwitch;
                *inputDriveSysControlWord&=~KeyDriveSysStop;
            }
        }
        else if(Lang2Cross==6){
            *inputDriveSysControlWord&=~KeyDriveSysCrossDriveSet;
            SetTheta11=0.0;
            DriveModule11Angle=0.0;
            DriveModule11ActualAngle=0.0;
            SetTheta12=0.0;
            DriveModule12Angle=0.0;
            DriveModule12ActualAngle=0.0;
            SetTheta21=0.0;
            DriveModule21Angle=0.0;
            DriveModule21ActualAngle=0.0;
            SetTheta22=0.0;
            DriveModule22Angle=0.0;
            DriveModule22ActualAngle=0.0;
            if(DriveSysTick==0) {
                Lang2Cross=0;
                *inputDriveSysControlWord&=~KeyDriveSysIsCrossSwitch;
                *inputDriveSysControlWord&=~KeyDriveSysStop;
            }
        }

        if(DriveSysTick==0){
            *inputDriveSysControlWord&=~KeyDriveSysMotionReq;
        }
        else{
            DriveSysTick--;
            if(Lang2Cross<5) *inputDriveSysControlWord|=KeyDriveSysMotionReq;
            else *inputDriveSysControlWord&=~KeyDriveSysMotionReq;
        }

        if(*inputDriveSysControlWord&KeyDriveSysEnable) {
            if(Lang2Cross==0) SetSteering();
        }
        x_os_wait_for_events();
    }
}



