#include "DriveSysData.h"
#include "DriveInterface.h"
#include "DriveSys.h"


/*----------------------------------------------------------------
Parameter definition of the drive module
----------------------------------------------------------------*/
#define PIControllerDeadZone          (0.3*pi/180.0)

static float32 inverseR11;
static float32 inverseR12;
static float32 inverseR21;
static float32 inverseR22;

//=================================================================================================
/*!
    Function: PI-Controller for Drive module 11
    output: None
*/
//=================================================================================================
void Controller11(void){
    float32 DeltaYk;
    float32 DeltaYi;
    float32 OmegaSP;
    float32 OmegaSet;

    //setting angle and speed of drive module
    if((*inputDriveSysControlWord&KeyDriveSysTestMode)==0){
        if((*inputDriveSysControlWord&KeyDriveSysMotionReq)==0){
            *outputMotor111ControlWord=0x0000;
            *outputMotor112ControlWord=0x0000;
            return;
        }
        else{
            *outputMotor111ControlWord=0x0005;
            *outputMotor112ControlWord=0x0005;
        }
        if(DriveModule11Angle<=(SetTheta11-0.01)) DriveModule11Angle+=(DriveSysOmega)*Ts11;
        else if(DriveModule11Angle>(SetTheta11+0.01)) DriveModule11Angle-=(DriveSysOmega)*Ts11;
        else DriveModule11Angle=SetTheta11;
        if(SetV11>0.0){
            if(DriveModule11Speed<(SetV11-0.01)) DriveModule11Speed+=(DriveSysAccel)*Ts11;
            else if(DriveModule11Speed>(SetV11+0.01)) DriveModule11Speed-=(DriveSysDecl)*Ts11;
            else DriveModule11Speed=SetV11;
        }
        else if(SetV11<0.0){
            if(DriveModule11Speed<(SetV11-0.01)) DriveModule11Speed+=(DriveSysDecl)*Ts11;
            else if(DriveModule11Speed>(SetV11+0.01)) DriveModule11Speed-=(DriveSysAccel)*Ts11;
            else DriveModule11Speed=SetV11;
        }
        else{
            if(DriveModule11Speed>0.0) DriveModule11Speed-=(DriveSysDecl)*Ts11;
            else if(DriveModule11Speed<0.0) DriveModule11Speed+=(DriveSysDecl)*Ts11;
            else DriveModule11Speed=0.0;
        }
    }
    else{
        DriveModule11Angle=(float32)(*inputSetDriveModule11Angle)*pi/180.0;
        DriveModule11Speed=0.0;
        *outputMotor111ControlWord=0x0005;
        *outputMotor112ControlWord=0x0005;
    }

    //calculate the maximum speed limit
    PIControllerDaten11.OutLimit=2.0/D*(SpeedLimit-DriveModule11Speed);

    //calculate the control error of the steering angle
    PIControllerDaten11.ek=DriveModule11Angle-DriveModule11ActualAngle;
    if((PIControllerDaten11.ek<PIControllerDeadZone)&&(PIControllerDaten11.ek>(0.0-PIControllerDeadZone)))
        PIControllerDaten11.ek=0.0;

    //cascade control
    OmegaSP=PIControllerDaten11.Kp1*PIControllerDaten11.ek;

    DeltaYk=PIControllerDaten11.Kp2*(OmegaSP-DriveModule11Omega-PIControllerDaten11.ek_1);
    DeltaYi=(OmegaSP-DriveModule11Omega)*PIControllerDaten11.Ki*Ts11;

    if((PIControllerDaten11.yk_1+DeltaYk+DeltaYi)>=PIControllerDaten11.OutLimit) PIControllerDaten11.yk=PIControllerDaten11.OutLimit;
    else if((PIControllerDaten11.yk_1+DeltaYk+DeltaYi)<=(0.0-PIControllerDaten11.OutLimit)) PIControllerDaten11.yk=0.0-PIControllerDaten11.OutLimit;
    else PIControllerDaten11.yk=PIControllerDaten11.yk_1+DeltaYk+DeltaYi;

    PIControllerDaten11.ek_1=OmegaSP-DriveModule11Omega;
    PIControllerDaten11.yk_1=PIControllerDaten11.yk;

    //generate the motor speed
    OmegaSet=PIControllerDaten11.yk+DriveModule11OmegaM;
    if(OmegaSet>PIControllerDaten11.OutLimit) OmegaSet=PIControllerDaten11.OutLimit;
    else if(OmegaSet<(0.0-PIControllerDaten11.OutLimit)) OmegaSet=0.0-PIControllerDaten11.OutLimit;

    *outputSetMotor111Speed=(sint16)((DriveModule11Speed-D/2.0*OmegaSet)*FactV2rpm);
    *outputSetMotor112Speed=(sint16)((DriveModule11Speed+D/2.0*OmegaSet)*FactV2rpm);
}

//=================================================================================================
/*!
    Function: PI-Controller for Drive module 12
    output: None
*/
//=================================================================================================
void Controller12(void){
    float32 DeltaYk;
    float32 DeltaYi;
    float32 OmegaSP;
    float32 OmegaSet;

    //setting angle and speed of drive module
    if((*inputDriveSysControlWord&KeyDriveSysTestMode)==0){
        if((*inputDriveSysControlWord&KeyDriveSysMotionReq)==0){
            *outputMotor121ControlWord=0x0000;
            *outputMotor122ControlWord=0x0000;
            return;
        }
        else{
            *outputMotor121ControlWord=0x0005;
            *outputMotor122ControlWord=0x0005;
        }
        if(DriveModule12Angle<=(SetTheta12-0.01)) DriveModule12Angle+=(DriveSysOmega)*Ts12;
        else if(DriveModule12Angle>(SetTheta12+0.01)) DriveModule12Angle-=(DriveSysOmega)*Ts12;
        else DriveModule12Angle=SetTheta12;
        if(SetV12>0.0){
            if(DriveModule12Speed<(SetV12-0.01)) DriveModule12Speed+=(DriveSysAccel)*Ts12;
            else if(DriveModule12Speed>(SetV12+0.01)) DriveModule12Speed-=(DriveSysDecl)*Ts12;
            else DriveModule12Speed=SetV12;
        }
        else if(SetV12<0.0){
            if(DriveModule12Speed<(SetV12-0.01)) DriveModule12Speed+=(DriveSysDecl)*Ts12;
            else if(DriveModule12Speed>(SetV12+0.01)) DriveModule12Speed-=(DriveSysAccel)*Ts12;
            else DriveModule12Speed=SetV12;
        }
        else{
            if(DriveModule12Speed>0.0) DriveModule12Speed-=(DriveSysDecl)*Ts12;
            else if(DriveModule12Speed<0.0) DriveModule12Speed+=(DriveSysDecl)*Ts12;
            else DriveModule12Speed=0.0;
        }
    }
    else{
        DriveModule12Angle=(float32)(*inputSetDriveModule12Angle)*pi/180.0;
        DriveModule12Speed=0.0;
        *outputMotor121ControlWord=0x0005;
        *outputMotor122ControlWord=0x0005;
    }

    //calculate the maximum speed limit
    PIControllerDaten12.OutLimit=2.0/D*(SpeedLimit-DriveModule12Speed);

    //calculate the control error of the steering angle
    PIControllerDaten12.ek=DriveModule12Angle-DriveModule12ActualAngle;
    if((PIControllerDaten12.ek<PIControllerDeadZone)&&(PIControllerDaten12.ek>(0.0-PIControllerDeadZone)))
        PIControllerDaten12.ek=0.0;

    //cascade control
    OmegaSP=PIControllerDaten12.Kp1*PIControllerDaten12.ek;

    DeltaYk=PIControllerDaten12.Kp2*(OmegaSP-DriveModule12Omega-PIControllerDaten12.ek_1);
    DeltaYi=(OmegaSP-DriveModule12Omega)*PIControllerDaten12.Ki*Ts12;

    if((PIControllerDaten12.yk_1+DeltaYk+DeltaYi)>=PIControllerDaten12.OutLimit) PIControllerDaten12.yk=PIControllerDaten12.OutLimit;
    else if((PIControllerDaten12.yk_1+DeltaYk+DeltaYi)<=(0.0-PIControllerDaten12.OutLimit)) PIControllerDaten12.yk=0.0-PIControllerDaten12.OutLimit;
    else PIControllerDaten12.yk=PIControllerDaten12.yk_1+DeltaYk+DeltaYi;

    PIControllerDaten12.ek_1=OmegaSP-DriveModule12Omega;
    PIControllerDaten12.yk_1=PIControllerDaten12.yk;

    //generate the motor speed
    OmegaSet=PIControllerDaten12.yk+DriveModule12OmegaM;
    if(OmegaSet>PIControllerDaten12.OutLimit) OmegaSet=PIControllerDaten12.OutLimit;
    else if(OmegaSet<(0.0-PIControllerDaten12.OutLimit)) OmegaSet=0.0-PIControllerDaten12.OutLimit;
    *outputSetMotor121Speed=(sint16)((DriveModule12Speed-D/2.0*OmegaSet)*FactV2rpm);
    *outputSetMotor122Speed=(sint16)((DriveModule12Speed+D/2.0*OmegaSet)*FactV2rpm);
}

//=================================================================================================
/*!
    Function: PI-Controller for Drive module 21
    output: None
*/
//=================================================================================================
void Controller21(void){
    float32 DeltaYk;
    float32 DeltaYi;
    float32 OmegaSP;
    float32 OmegaSet;

    //setting angle and speed of drive module
    if((*inputDriveSysControlWord&KeyDriveSysTestMode)==0){
        if((*inputDriveSysControlWord&KeyDriveSysMotionReq)==0){
            *outputMotor211ControlWord=0x0000;
            *outputMotor212ControlWord=0x0000;
            return;
        }
        else{
            *outputMotor211ControlWord=0x0005;
            *outputMotor212ControlWord=0x0005;
        }
        if(DriveModule21Angle<=(SetTheta21-0.01)) DriveModule21Angle+=(DriveSysOmega)*Ts21;
        else if(DriveModule21Angle>(SetTheta21+0.01)) DriveModule21Angle-=(DriveSysOmega)*Ts21;
        else DriveModule21Angle=SetTheta21;
        if(SetV21>0.0){
            if(DriveModule21Speed<(SetV21-0.01)) DriveModule21Speed+=(DriveSysAccel)*Ts21;
            else if(DriveModule21Speed>(SetV21+0.01)) DriveModule21Speed-=(DriveSysDecl)*Ts21;
            else DriveModule21Speed=SetV21;
        }
        else if(SetV21<0.0){
            if(DriveModule21Speed<(SetV21-0.01)) DriveModule21Speed+=(DriveSysDecl)*Ts21;
            else if(DriveModule21Speed>(SetV21+0.01)) DriveModule21Speed-=(DriveSysAccel)*Ts21;
            else DriveModule21Speed=SetV21;
        }
        else{
            if(DriveModule21Speed>0.0) DriveModule21Speed-=(DriveSysDecl)*Ts21;
            else if(DriveModule21Speed<0.0) DriveModule21Speed+=(DriveSysDecl)*Ts21;
            else DriveModule21Speed=0.0;
        }
    }
    else{
        DriveModule21Angle=(float32)(*inputSetDriveModule21Angle)*pi/180.0;
        DriveModule21Speed=0.0;
        *outputMotor211ControlWord=0x0005;
        *outputMotor212ControlWord=0x0005;
    }

    //calculate the maximum speed limit
    PIControllerDaten21.OutLimit=2.0/D*(SpeedLimit-DriveModule21Speed);

    //calculate the control error of the steering angle
    PIControllerDaten21.ek=DriveModule21Angle-DriveModule21ActualAngle;
    if((PIControllerDaten21.ek<PIControllerDeadZone)&&(PIControllerDaten21.ek>(0.0-PIControllerDeadZone)))
        PIControllerDaten21.ek=0.0;

    //cascade control
    OmegaSP=PIControllerDaten21.Kp1*PIControllerDaten21.ek;

    DeltaYk=PIControllerDaten21.Kp2*(OmegaSP-DriveModule21Omega-PIControllerDaten21.ek_1);
    DeltaYi=(OmegaSP-DriveModule21Omega)*PIControllerDaten21.Ki*Ts21;

    if((PIControllerDaten21.yk_1+DeltaYk+DeltaYi)>=PIControllerDaten21.OutLimit) PIControllerDaten21.yk=PIControllerDaten21.OutLimit;
    else if((PIControllerDaten21.yk_1+DeltaYk+DeltaYi)<=(0.0-PIControllerDaten21.OutLimit)) PIControllerDaten21.yk=0.0-PIControllerDaten21.OutLimit;
    else PIControllerDaten21.yk=PIControllerDaten21.yk_1+DeltaYk+DeltaYi;

    PIControllerDaten21.ek_1=OmegaSP-DriveModule21Omega;
    PIControllerDaten21.yk_1=PIControllerDaten21.yk;

    //generate the motor speed
    OmegaSet=PIControllerDaten21.yk+DriveModule21OmegaM;
    if(OmegaSet>PIControllerDaten21.OutLimit) OmegaSet=PIControllerDaten21.OutLimit;
    else if(OmegaSet<(0.0-PIControllerDaten21.OutLimit)) OmegaSet=0.0-PIControllerDaten21.OutLimit;
    *outputSetMotor211Speed=(sint16)((DriveModule21Speed-D/2.0*OmegaSet)*FactV2rpm);
    *outputSetMotor212Speed=(sint16)((DriveModule21Speed+D/2.0*OmegaSet)*FactV2rpm);
}

//=================================================================================================
/*!
    Function: PI-Controller for Drive module 22
    output: None
*/
//=================================================================================================
void Controller22(void){
    float32 DeltaYk;
    float32 DeltaYi;
    float32 OmegaSP;
    float32 OmegaSet;

    //setting angle and speed of drive module
    if((*inputDriveSysControlWord&KeyDriveSysTestMode)==0){
        if((*inputDriveSysControlWord&KeyDriveSysMotionReq)==0){
            *outputMotor221ControlWord=0x0000;
            *outputMotor222ControlWord=0x0000;
            return;
        }
        else{
            *outputMotor221ControlWord=0x0005;
            *outputMotor222ControlWord=0x0005;
        }
        if(DriveModule22Angle<=(SetTheta22-0.01)) DriveModule22Angle+=(DriveSysOmega)*Ts22;
        else if(DriveModule22Angle>(SetTheta22+0.01)) DriveModule22Angle-=(DriveSysOmega)*Ts22;
        else DriveModule22Angle=SetTheta22;
        if(SetV22>0.0){
            if(DriveModule22Speed<(SetV22-0.01)) DriveModule22Speed+=DriveSysAccel*Ts22;
            else if(DriveModule22Speed>(SetV22+0.01)) DriveModule22Speed-=(DriveSysDecl)*Ts22;
            else DriveModule22Speed=SetV22;
        }
        else if(SetV22<0.0){
            if(DriveModule22Speed<(SetV22-0.01)) DriveModule22Speed+=(DriveSysDecl)*Ts22;
            else if(DriveModule22Speed>(SetV22+0.01)) DriveModule22Speed-=DriveSysAccel*Ts22;
            else DriveModule22Speed=SetV22;
        }
        else{
            if(DriveModule22Speed>0.0) DriveModule22Speed-=(DriveSysDecl)*Ts22;
            else if(DriveModule22Speed<0.0) DriveModule22Speed+=(DriveSysDecl)*Ts22;
            else DriveModule22Speed=0.0;
        }
    }
    else{
        DriveModule22Angle=(float32)(*inputSetDriveModule22Angle)*pi/180.0;
        DriveModule22Speed=0.0;
        *outputMotor221ControlWord=0x0005;
        *outputMotor222ControlWord=0x0005;
    }

    //calculate the maximum speed limit
    PIControllerDaten22.OutLimit=2.0/D*(SpeedLimit-DriveModule22Speed);

    //calculate the control error of the steering angle
    PIControllerDaten22.ek=DriveModule22Angle-DriveModule22ActualAngle;
    if((PIControllerDaten22.ek<PIControllerDeadZone)&&(PIControllerDaten22.ek>(0.0-PIControllerDeadZone)))
        PIControllerDaten22.ek=0.0;

    //cascade control
    OmegaSP=PIControllerDaten22.Kp1*PIControllerDaten22.ek;

    DeltaYk=PIControllerDaten22.Kp2*(OmegaSP-DriveModule22Omega-PIControllerDaten22.ek_1);
    DeltaYi=(OmegaSP-DriveModule22Omega)*PIControllerDaten22.Ki*Ts22;

    if((PIControllerDaten22.yk_1+DeltaYk+DeltaYi)>=PIControllerDaten22.OutLimit) PIControllerDaten22.yk=PIControllerDaten22.OutLimit;
    else if((PIControllerDaten22.yk_1+DeltaYk+DeltaYi)<=(0.0-PIControllerDaten22.OutLimit)) PIControllerDaten22.yk=0.0-PIControllerDaten22.OutLimit;
    else PIControllerDaten22.yk=PIControllerDaten22.yk_1+DeltaYk+DeltaYi;

    PIControllerDaten22.ek_1=OmegaSP-DriveModule22Omega;
    PIControllerDaten22.yk_1=PIControllerDaten22.yk;

    //generate the motor speed
    OmegaSet=PIControllerDaten22.yk+DriveModule22OmegaM;
    if(OmegaSet>PIControllerDaten22.OutLimit) OmegaSet=PIControllerDaten22.OutLimit;
    else if(OmegaSet<(0.0-PIControllerDaten22.OutLimit)) OmegaSet=0.0-PIControllerDaten22.OutLimit;

    *outputSetMotor221Speed=(sint16)((DriveModule22Speed-D/2.0*OmegaSet)*FactV2rpm);
    *outputSetMotor222Speed=(sint16)((DriveModule22Speed+D/2.0*OmegaSet)*FactV2rpm);
}

//=================================================================================================
/*!
    Function: Get the Measurement Value for Drive Module 11
    output: None
*/
//=================================================================================================
void GetDriveMeasurementDriveModule11(void){

    if(*inputDriveSysControlWord&KeyDriveSysCrossDriveSet){
        //get the actual steering angle of the drive module
        DriveModule11ActualAngle=((float32)(*inputDriveModule11ActualAngle)*AngleSensor11FactA+AngleSensor11FactB-90.0)*Grad2Rad;
        //get the actual forward speed of drive module
        SpeedValue11=0.0-(float32)(*inputMotor111ActualSpeed+*inputMotor112ActualSpeed)/FactV2rpm/2.0;
        //calculate the radius on each drive module
        inverseR11=(tan(DriveModule12ActualAngle)-tan(DriveModule11ActualAngle))*cos(DriveModule11ActualAngle)/B;
    }
    else{
        //get the actual steering angle of the drive module
        DriveModule11ActualAngle=((float32)(*inputDriveModule11ActualAngle)*AngleSensor11FactA+AngleSensor11FactB)*Grad2Rad;
        //get the actual forward speed of drive module
        SpeedValue11=(float32)(*inputMotor111ActualSpeed+*inputMotor112ActualSpeed)/FactV2rpm/2.0;
        //calculate the radius on each drive module
        inverseR11=(tan(DriveModule11ActualAngle)-tan(DriveModule21ActualAngle))*cos(DriveModule11ActualAngle)/L;
    }
    //get the actual omega of the drive module in curve
    DriveModule11OmegaM=(SpeedValue11)*inverseR11;
    //calculate the actual omega of drive module
    DriveModule11Omega=(float32)(*inputMotor112ActualSpeed-*inputMotor111ActualSpeed)*RPM2Omega-DriveModule11OmegaM;
}

//=================================================================================================
/*!
    Function: Get the Measurement Value for Drive Module 12
    output: None
*/
//=================================================================================================
void GetDriveMeasurementDriveModule12(void){
    if(*inputDriveSysControlWord&KeyDriveSysCrossDriveSet){
        //get the actual steering angle of the drive module
        DriveModule12ActualAngle=((float32)(*inputDriveModule12ActualAngle)*AngleSensor12FactA+AngleSensor12FactB+90.0)*Grad2Rad;
        //calculate the radius on each drive module
        inverseR12=(tan(DriveModule12ActualAngle)-tan(DriveModule11ActualAngle))*cos(DriveModule12ActualAngle)/B;
    }
    else{
        //get the actual steering angle of the drive module
        DriveModule12ActualAngle=((float32)(*inputDriveModule12ActualAngle)*AngleSensor12FactA+AngleSensor12FactB)*Grad2Rad;
        //calculate the radius on each drive module
        inverseR12=(tan(DriveModule12ActualAngle)-tan(DriveModule22ActualAngle))*cos(DriveModule12ActualAngle)/L;
    }

    //get the actual forward speed of drive module
    SpeedValue12=(float32)(*inputMotor121ActualSpeed+*inputMotor122ActualSpeed)/FactV2rpm/2.0;
    //get the actual omega of the drive module in curve
    DriveModule12OmegaM=(SpeedValue12)*inverseR12;
    //calculate the actual omega of drive module
    DriveModule12Omega=(float32)(*inputMotor122ActualSpeed-*inputMotor121ActualSpeed)*RPM2Omega-DriveModule12OmegaM;
}

//=================================================================================================
/*!
    Function: Get the Measurement Value for Drive Module 21
    output: None
*/
//=================================================================================================
void GetDriveMeasurementDriveModule21(void){

    if(*inputDriveSysControlWord&KeyDriveSysCrossDriveSet){
        //get the actual steering angle of the drive module
        DriveModule21ActualAngle=((float32)(*inputDriveModule21ActualAngle)*AngleSensor21FactA+AngleSensor21FactB+90.0)*Grad2Rad;
        //calculate the radius on each drive module
        inverseR21=(tan(DriveModule22ActualAngle)-tan(DriveModule21ActualAngle))*cos(DriveModule21ActualAngle)/B;
    }

    else{
        //get the actual steering angle of the drive module
        DriveModule21ActualAngle=((float32)(*inputDriveModule21ActualAngle)*AngleSensor21FactA+AngleSensor21FactB)*Grad2Rad;
        //calculate the radius on each drive module
        inverseR21=(tan(DriveModule11ActualAngle)-tan(DriveModule21ActualAngle))*cos(DriveModule21ActualAngle)/L;
    }

    //get the actual forward speed of drive module
    SpeedValue21=(float32)(*inputMotor211ActualSpeed+*inputMotor212ActualSpeed)/FactV2rpm/2.0;
    //get the actual omega of the drive module in curve
    DriveModule21OmegaM=(SpeedValue21)*inverseR21;
    //calculate the actual omega of drive module
    DriveModule21Omega=(float32)(*inputMotor212ActualSpeed-*inputMotor211ActualSpeed)*RPM2Omega-DriveModule21OmegaM;
}

//=================================================================================================
/*!
    Function: Get the Measurement Value for Drive Module 22
    output: None
*/
//=================================================================================================
void GetDriveMeasurementDriveModule22(void){

    if(*inputDriveSysControlWord&KeyDriveSysCrossDriveSet){
        //get the actual steering angle of the drive module
        DriveModule22ActualAngle=((float32)(*inputDriveModule22ActualAngle)*AngleSensor22FactA+AngleSensor22FactB-90.0)*Grad2Rad;
        //calculate the radius on each drive module
        inverseR22=(tan(DriveModule22ActualAngle)-tan(DriveModule21ActualAngle))*cos(DriveModule22ActualAngle)/B;
        //get the actual forward speed of drive module
        SpeedValue22=0.0-(float32)(*inputMotor221ActualSpeed+*inputMotor222ActualSpeed)/FactV2rpm/2.0;
    }

    else{
        //get the actual steering angle of the drive module
        DriveModule22ActualAngle=((float32)(*inputDriveModule22ActualAngle)*AngleSensor22FactA+AngleSensor22FactB)*Grad2Rad;
        //calculate the radius on each drive module
        inverseR22=(tan(DriveModule12ActualAngle)-tan(DriveModule22ActualAngle))*cos(DriveModule22ActualAngle)/L;
        //get the actual forward speed of drive module
        SpeedValue22=(float32)(*inputMotor221ActualSpeed+*inputMotor222ActualSpeed)/FactV2rpm/2.0;
    }

    //get the actual omega of the drive module in curve
    DriveModule22OmegaM=(SpeedValue22)*inverseR22;
    //calculate the actual omega of drive module
    DriveModule22Omega=(float32)(*inputMotor222ActualSpeed-*inputMotor221ActualSpeed)*RPM2Omega-DriveModule22OmegaM;
}



//=================================================================================================
/*!
    Function: Brake the Vehicle
    output: None
*/
//=================================================================================================
void DriveBrake(void){
    uint16 ControlWordTmp;

    PIControllerDaten11.ek=0.0;
    PIControllerDaten11.ek_1=0.0;
    PIControllerDaten11.yk=0.0;
    PIControllerDaten11.yk_1=0.0;

    PIControllerDaten12.ek=0.0;
    PIControllerDaten12.ek_1=0.0;
    PIControllerDaten12.yk=0.0;
    PIControllerDaten12.yk_1=0.0;

    PIControllerDaten21.ek=0.0;
    PIControllerDaten21.ek_1=0.0;
    PIControllerDaten21.yk=0.0;
    PIControllerDaten21.yk_1=0.0;

    PIControllerDaten22.ek=0.0;
    PIControllerDaten22.ek_1=0.0;
    PIControllerDaten22.yk=0.0;
    PIControllerDaten22.yk_1=0.0;


    if(*inputDriveSysControlWord&KeyDriveSysStop){
        if((*inputMotor111ActualSpeed==0)&&(*inputMotor112ActualSpeed==0)&&(*inputMotor121ActualSpeed==0)&&(*inputMotor122ActualSpeed==0)){
            if((*inputMotor211ActualSpeed==0)&&(*inputMotor212ActualSpeed==0)&&(*inputMotor221ActualSpeed==0)&&(*inputMotor222ActualSpeed==0)){
                *outputMotor111ControlWord=0x0000;
                *outputMotor112ControlWord=0x0000;
                *outputMotor121ControlWord=0x0000;
                *outputMotor122ControlWord=0x0000;
                *outputMotor211ControlWord=0x0000;
                *outputMotor212ControlWord=0x0000;
                *outputMotor221ControlWord=0x0000;
                *outputMotor222ControlWord=0x0000;
            }
            else{
                ControlWordTmp=0x0004;
                *outputMotor111ControlWord=ControlWordTmp;
                *outputMotor112ControlWord=ControlWordTmp;
                *outputMotor121ControlWord=ControlWordTmp;
                *outputMotor122ControlWord=ControlWordTmp;
                *outputMotor211ControlWord=ControlWordTmp;
                *outputMotor212ControlWord=ControlWordTmp;
                *outputMotor221ControlWord=ControlWordTmp;
                *outputMotor222ControlWord=ControlWordTmp;
            }
        }
        else{
            ControlWordTmp=0x0004;
            *outputMotor111ControlWord=ControlWordTmp;
            *outputMotor112ControlWord=ControlWordTmp;
            *outputMotor121ControlWord=ControlWordTmp;
            *outputMotor122ControlWord=ControlWordTmp;
            *outputMotor211ControlWord=ControlWordTmp;
            *outputMotor212ControlWord=ControlWordTmp;
            *outputMotor221ControlWord=ControlWordTmp;
            *outputMotor222ControlWord=ControlWordTmp;
        }
    }
    if((*inputDriveSysControlWord&KeyDriveSysStop)==0){
        ControlWordTmp=0x0004;
        *outputMotor111ControlWord=ControlWordTmp;
        *outputMotor112ControlWord=ControlWordTmp;
        *outputMotor121ControlWord=ControlWordTmp;
        *outputMotor122ControlWord=ControlWordTmp;
        *outputMotor211ControlWord=ControlWordTmp;
        *outputMotor212ControlWord=ControlWordTmp;
        *outputMotor221ControlWord=ControlWordTmp;
        *outputMotor222ControlWord=ControlWordTmp;
    }
}

//=================================================================================================
/*!
    Function: Controller of the Vehicle, it output the Value for the Motor
    output: None
*/
//=================================================================================================
void DriveControl(void){
    if(DriveModuleAktiv&0x01){
        GetDriveMeasurementDriveModule11();
        if((*inputDriveSysControlWord&KeyDriveSysStop)==0){
            if(*inputDriveSysControlWord&KeyDriveSysEnable) Controller11();
        }
        DriveModuleAktiv&=~0x01;
    }
    if(DriveModuleAktiv&0x02){
        GetDriveMeasurementDriveModule12();
        if((*inputDriveSysControlWord&KeyDriveSysStop)==0){
            if(*inputDriveSysControlWord&KeyDriveSysEnable) Controller12();
        }
        DriveModuleAktiv&=~0x02;
    }
    if(DriveModuleAktiv&0x04){
        GetDriveMeasurementDriveModule21();
        if((*inputDriveSysControlWord&KeyDriveSysStop)==0){
            if(*inputDriveSysControlWord&KeyDriveSysEnable) Controller21();
        }
        DriveModuleAktiv&=~0x04;
    }
    if(DriveModuleAktiv&0x08){
        GetDriveMeasurementDriveModule22();
        if((*inputDriveSysControlWord&KeyDriveSysStop)==0){
            if(*inputDriveSysControlWord&KeyDriveSysEnable) Controller22();
        }
        DriveModuleAktiv&=~0x08;
    }
    if((*inputDriveSysControlWord&KeyDriveSysEnable)==0) DriveBrake();
}

//=================================================================================================
/*!
    Function: this is a task for control of the Drive system
    output: None
*/
//=================================================================================================
void Task_DriveSysControl(void* argv){
    argv=argv;
    uint32 u32_Events;

    x_os_set_event_mask(Event_DriveSysControl);

    while(TRUE){
        x_os_wait_for_events();
        u32_Events = x_os_get_events(); // get events
        if((u32_Events&Event_DriveSysControl)!=0){
            DriveControl();
        }
    }
}



