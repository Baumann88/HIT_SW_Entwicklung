#include <SafetyData.h>
#include <Safety.h>

//====================================================================
/*!
Function: initial Satety DriveSys
Output: None
*/
//====================================================================
void InitSafetyDriveSys(void){
    inputSafetyDriveModule11ActualAngle=BindODMem(DriveModuleStartIndex,SubindexDriveModule11ActualAngle,TypeS32,0); *inputSafetyDriveModule11ActualAngle=0;
    inputSafetyDriveModule12ActualAngle=BindODMem(DriveModuleStartIndex,SubindexDriveModule12ActualAngle,TypeS32,0); *inputSafetyDriveModule12ActualAngle=0;
    inputSafetyDriveModule21ActualAngle=BindODMem(DriveModuleStartIndex,SubindexDriveModule21ActualAngle,TypeS32,0); *inputSafetyDriveModule21ActualAngle=0;
    inputSafetyDriveModule22ActualAngle=BindODMem(DriveModuleStartIndex,SubindexDriveModule22ActualAngle,TypeS32,0); *inputSafetyDriveModule22ActualAngle=0;
    inputSafetyDriveModule11SetAngle=BindODMem(DriveModuleStartIndex,SubindexSetDriveModule11Angle,TypeS32,0); *inputSafetyDriveModule11SetAngle=0;
    inputSafetyDriveModule12SetAngle=BindODMem(DriveModuleStartIndex,SubindexSetDriveModule12Angle,TypeS32,0); *inputSafetyDriveModule12SetAngle=0;
    inputSafetyDriveModule21SetAngle=BindODMem(DriveModuleStartIndex,SubindexSetDriveModule21Angle,TypeS32,0); *inputSafetyDriveModule21SetAngle=0;
    inputSafetyDriveModule22SetAngle=BindODMem(DriveModuleStartIndex,SubindexSetDriveModule22Angle,TypeS32,0); *inputSafetyDriveModule22SetAngle=0;
    inputSafetyMotor111SetSpeed=BindODMem(InverterStartIndex,SubindexInverterRPDO1LowDWord,TypeS16,1); *inputSafetyMotor111SetSpeed=0;
    inputSafetyMotor112SetSpeed=BindODMem(InverterStartIndex+0x0001,SubindexInverterRPDO1LowDWord,TypeS16,1); *inputSafetyMotor112SetSpeed=0;
    inputSafetyMotor121SetSpeed=BindODMem(InverterStartIndex+0x0002,SubindexInverterRPDO1LowDWord,TypeS16,1); *inputSafetyMotor121SetSpeed=0;
    inputSafetyMotor122SetSpeed=BindODMem(InverterStartIndex+0x0003,SubindexInverterRPDO1LowDWord,TypeS16,1); *inputSafetyMotor122SetSpeed=0;
    inputSafetyMotor211SetSpeed=BindODMem(InverterStartIndex+0x0004,SubindexInverterRPDO1LowDWord,TypeS16,1); *inputSafetyMotor211SetSpeed=0;
    inputSafetyMotor212SetSpeed=BindODMem(InverterStartIndex+0x0005,SubindexInverterRPDO1LowDWord,TypeS16,1); *inputSafetyMotor212SetSpeed=0;
    inputSafetyMotor221SetSpeed=BindODMem(InverterStartIndex+0x0006,SubindexInverterRPDO1LowDWord,TypeS16,1); *inputSafetyMotor221SetSpeed=0;
    inputSafetyMotor222SetSpeed=BindODMem(InverterStartIndex+0x0007,SubindexInverterRPDO1LowDWord,TypeS16,1); *inputSafetyMotor222SetSpeed=0;
    inputSafetyMotor111ActualTorque=BindODMem(InverterStartIndex,SubindexInverterTPDO1LowDWord,TypeS16,2); *inputSafetyMotor111ActualTorque=0;
    inputSafetyMotor112ActualTorque=BindODMem(InverterStartIndex+0x0001,SubindexInverterTPDO1LowDWord,TypeS16,2); *inputSafetyMotor112ActualTorque=0;
    inputSafetyMotor121ActualTorque=BindODMem(InverterStartIndex+0x0002,SubindexInverterTPDO1LowDWord,TypeS16,2); *inputSafetyMotor121ActualTorque=0;
    inputSafetyMotor122ActualTorque=BindODMem(InverterStartIndex+0x0003,SubindexInverterTPDO1LowDWord,TypeS16,2); *inputSafetyMotor122ActualTorque=0;
    inputSafetyMotor211ActualTorque=BindODMem(InverterStartIndex+0x0004,SubindexInverterTPDO1LowDWord,TypeS16,2); *inputSafetyMotor211ActualTorque=0;
    inputSafetyMotor212ActualTorque=BindODMem(InverterStartIndex+0x0005,SubindexInverterTPDO1LowDWord,TypeS16,2); *inputSafetyMotor212ActualTorque=0;
    inputSafetyMotor221ActualTorque=BindODMem(InverterStartIndex+0x0006,SubindexInverterTPDO1LowDWord,TypeS16,2); *inputSafetyMotor221ActualTorque=0;
    inputSafetyMotor222ActualTorque=BindODMem(InverterStartIndex+0x0007,SubindexInverterTPDO1LowDWord,TypeS16,2); *inputSafetyMotor222ActualTorque=0;
    inputSafetyMotor111ActualSpeed=BindODMem(InverterStartIndex,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputSafetyMotor111ActualSpeed=0;
    inputSafetyMotor112ActualSpeed=BindODMem(InverterStartIndex+0x0001,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputSafetyMotor112ActualSpeed=0;
    inputSafetyMotor121ActualSpeed=BindODMem(InverterStartIndex+0x0002,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputSafetyMotor121ActualSpeed=0;
    inputSafetyMotor122ActualSpeed=BindODMem(InverterStartIndex+0x0003,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputSafetyMotor122ActualSpeed=0;
    inputSafetyMotor211ActualSpeed=BindODMem(InverterStartIndex+0x0004,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputSafetyMotor211ActualSpeed=0;
    inputSafetyMotor212ActualSpeed=BindODMem(InverterStartIndex+0x0005,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputSafetyMotor212ActualSpeed=0;
    inputSafetyMotor221ActualSpeed=BindODMem(InverterStartIndex+0x0006,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputSafetyMotor221ActualSpeed=0;
    inputSafetyMotor222ActualSpeed=BindODMem(InverterStartIndex+0x0007,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputSafetyMotor222ActualSpeed=0;
    inputSafetyMotor111StatusByte=BindODMem(InverterStartIndex,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputSafetyMotor111StatusByte=0x00;
    inputSafetyMotor112StatusByte=BindODMem(InverterStartIndex+0x0001,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputSafetyMotor112StatusByte=0x00;
    inputSafetyMotor121StatusByte=BindODMem(InverterStartIndex+0x0002,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputSafetyMotor121StatusByte=0x00;
    inputSafetyMotor122StatusByte=BindODMem(InverterStartIndex+0x0003,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputSafetyMotor122StatusByte=0x00;
    inputSafetyMotor211StatusByte=BindODMem(InverterStartIndex+0x0004,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputSafetyMotor211StatusByte=0x00;
    inputSafetyMotor212StatusByte=BindODMem(InverterStartIndex+0x0005,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputSafetyMotor212StatusByte=0x00;
    inputSafetyMotor221StatusByte=BindODMem(InverterStartIndex+0x0006,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputSafetyMotor221StatusByte=0x00;
    inputSafetyMotor222StatusByte=BindODMem(InverterStartIndex+0x0007,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputSafetyMotor222StatusByte=0x00;
    inputSafetyMotor111ErrorCode=BindODMem(InverterStartIndex,SubindexInverterTPDO2LowDWord,TypeU16,0); *inputSafetyMotor111ErrorCode=0x0000;
    inputSafetyMotor112ErrorCode=BindODMem(InverterStartIndex+0x0001,SubindexInverterTPDO2LowDWord,TypeU16,0); *inputSafetyMotor112ErrorCode=0x0000;
    inputSafetyMotor121ErrorCode=BindODMem(InverterStartIndex+0x0002,SubindexInverterTPDO2LowDWord,TypeU16,0); *inputSafetyMotor121ErrorCode=0x0000;
    inputSafetyMotor122ErrorCode=BindODMem(InverterStartIndex+0x0003,SubindexInverterTPDO2LowDWord,TypeU16,0); *inputSafetyMotor122ErrorCode=0x0000;
    inputSafetyMotor211ErrorCode=BindODMem(InverterStartIndex+0x0004,SubindexInverterTPDO2LowDWord,TypeU16,0); *inputSafetyMotor211ErrorCode=0x0000;
    inputSafetyMotor212ErrorCode=BindODMem(InverterStartIndex+0x0005,SubindexInverterTPDO2LowDWord,TypeU16,0); *inputSafetyMotor212ErrorCode=0x0000;
    inputSafetyMotor221ErrorCode=BindODMem(InverterStartIndex+0x0006,SubindexInverterTPDO2LowDWord,TypeU16,0); *inputSafetyMotor221ErrorCode=0x0000;
    inputSafetyMotor222ErrorCode=BindODMem(InverterStartIndex+0x0007,SubindexInverterTPDO2LowDWord,TypeU16,0); *inputSafetyMotor222ErrorCode=0x0000;
    inputSafetyIOVersorgungBremsenAus=BindODMem(IOPortStartIndex,SubindexInput37,TypeU16,0); *inputSafetyIOVersorgungBremsenAus=0x0000;
    inputSafetyGetDriveSystemStatusWord=BindODMem(DriveModuleStartIndex,SubindexDriveSysControlWord,TypeU32,0); *inputSafetyGetDriveSystemStatusWord=0x00000000;

    outputSafetySetDriveSystemWord=BindODMem(DriveModuleStartIndex,SubindexDriveSysControlWord,TypeU32,0); *outputSafetySetDriveSystemWord=0x00000000;
}

//====================================================================
/*!
Function: DriveSysSafetyHandleDriveModuleAngle
Output: None
*/
//====================================================================
void DriveSysSafetyHandleDriveModuleAngle(void){
    boolean m1,m2,m3,m4,m5,m6,m7,m8,m9;
    static boolean SafetyErrorDriveModule11AngleOutOldValue;
    static boolean SafetyErrorDriveModule12AngleOutOldValue;
    static boolean SafetyErrorDriveModule21AngleOutOldValue;
    static boolean SafetyErrorDriveModule22AngleOutOldValue;
    //1. Layer
    if(*inputSafetyDriveModule11ActualAngle>DriveModule11MaxAngle)  m1=TRUE;
    else m1=FALSE;
    if(*inputSafetyDriveModule11ActualAngle<DriveModule11MinAngle)  m2=TRUE;
    else m2=FALSE;
    if(*inputSafetyDriveModule12ActualAngle>DriveModule12MaxAngle)  m3=TRUE;
    else m3=FALSE;
    if(*inputSafetyDriveModule12ActualAngle<DriveModule12MinAngle)  m4=TRUE;
    else m4=FALSE;
    if(*inputSafetyDriveModule21ActualAngle>DriveModule21MaxAngle)  m5=TRUE;
    else m5=FALSE;
    if(*inputSafetyDriveModule21ActualAngle<DriveModule21MinAngle)  m6=TRUE;
    else m6=FALSE;
    if(*inputSafetyDriveModule22ActualAngle>DriveModule22MaxAngle)  m7=TRUE;
    else m7=FALSE;
    if(*inputSafetyDriveModule22ActualAngle<DriveModule22MinAngle)  m8=TRUE;
    else m8=FALSE;
    if((*inputSafetyGetDriveSystemStatusWord&DriveModule21MaxAngle)==0)  m9=TRUE;
    else m9=FALSE;
    //2. Layer
    SafetyErrorDriveModule11AngleOut=(m1|m2)&m9;
    SafetyErrorDriveModule12AngleOut=(m3|m4)&m9;
    SafetyErrorDriveModule21AngleOut=(m5|m6)&m9;
    SafetyErrorDriveModule22AngleOut=(m7|m8)&m9;
    //Output
    if(SafetyErrorDriveModule11AngleOut){
         if(SafetyErrorDriveModule11AngleOut!=SafetyErrorDriveModule11AngleOutOldValue)
            SetErrorCode(123456);
    }
    if(SafetyErrorDriveModule12AngleOut){
         if(SafetyErrorDriveModule12AngleOut!=SafetyErrorDriveModule12AngleOutOldValue)
            SetErrorCode(123456);
    }
    if(SafetyErrorDriveModule21AngleOut){
         if(SafetyErrorDriveModule21AngleOut!=SafetyErrorDriveModule21AngleOutOldValue)
            SetErrorCode(123456);
    }
    if(SafetyErrorDriveModule22AngleOut){
         if(SafetyErrorDriveModule22AngleOut!=SafetyErrorDriveModule22AngleOutOldValue)
            SetErrorCode(123456);
    }
    //OldValue
    SafetyErrorDriveModule11AngleOutOldValue=SafetyErrorDriveModule11AngleOut;
    SafetyErrorDriveModule12AngleOutOldValue=SafetyErrorDriveModule12AngleOut;
    SafetyErrorDriveModule21AngleOutOldValue=SafetyErrorDriveModule21AngleOut;
    SafetyErrorDriveModule22AngleOutOldValue=SafetyErrorDriveModule22AngleOut;
}

//====================================================================
/*!
Function: DriveSysSafetyHandleDriveModuleSensor
Output: None
*/
//====================================================================
void DriveSysSafetyHandleDriveModuleSensor(void){
    boolean m1,m2,m3,m4,m5,m6,m7,m8;
    static boolean SafetyErrorAngleSensor11WarnOldValue;
    static boolean SafetyErrorAngleSensor11ErrorOldValue;
    static boolean SafetyErrorAngleSensor12WarnOldValue;
    static boolean SafetyErrorAngleSensor12ErrorOldValue;
    static boolean SafetyErrorAngleSensor21WarnOldValue;
    static boolean SafetyErrorAngleSensor21ErrorOldValue;
    static boolean SafetyErrorAngleSensor22WarnOldValue;
    static boolean SafetyErrorAngleSensor22ErrorOldValue;
    //1. Layer
    if(SafetyAngleSensor11TimeOutWarn==1)  m1=TRUE;
    else m1=FALSE;
    if(SafetyAngleSensor11TimeOutError==1)  m2=TRUE;
    else m2=FALSE;
    if(SafetyAngleSensor12TimeOutWarn==1)  m3=TRUE;
    else m3=FALSE;
    if(SafetyAngleSensor12TimeOutError==1)  m4=TRUE;
    else m4=FALSE;
    if(SafetyAngleSensor21TimeOutWarn==1)  m5=TRUE;
    else m5=FALSE;
    if(SafetyAngleSensor21TimeOutError==1)  m6=TRUE;
    else m6=FALSE;
    if(SafetyAngleSensor22TimeOutWarn==1)  m7=TRUE;
    else m7=FALSE;
    if(SafetyAngleSensor22TimeOutError==1)  m8=TRUE;
    else m8=FALSE;
    //2. Layer
    SafetyErrorAngleSensor11Warn=m1;
    SafetyErrorAngleSensor11Error=m2;
    SafetyErrorAngleSensor12Warn=m3;
    SafetyErrorAngleSensor12Error=m4;
    SafetyErrorAngleSensor21Warn=m5;
    SafetyErrorAngleSensor21Error=m6;
    SafetyErrorAngleSensor22Warn=m7;
    SafetyErrorAngleSensor22Error=m8;
    //Output
    if(SafetyErrorAngleSensor11Warn){
         if(SafetyErrorAngleSensor11Warn!=SafetyErrorAngleSensor11WarnOldValue)
            SetErrorCode(123456);
    }
    if(SafetyErrorAngleSensor11Error){
         if(SafetyErrorAngleSensor11Error!=SafetyErrorAngleSensor11ErrorOldValue)
            SetErrorCode(123456);
    }
    if(SafetyErrorAngleSensor12Warn){
         if(SafetyErrorAngleSensor12Warn!=SafetyErrorAngleSensor12WarnOldValue)
            SetErrorCode(123456);
    }
    if(SafetyErrorAngleSensor12Error){
         if(SafetyErrorAngleSensor12Error!=SafetyErrorAngleSensor12ErrorOldValue)
            SetErrorCode(123456);
    }
    if(SafetyErrorAngleSensor21Warn){
         if(SafetyErrorAngleSensor21Warn!=SafetyErrorAngleSensor21WarnOldValue)
            SetErrorCode(123456);
    }
    if(SafetyErrorAngleSensor21Error){
         if(SafetyErrorAngleSensor21Error!=SafetyErrorAngleSensor21ErrorOldValue)
            SetErrorCode(123456);
    }
    if(SafetyErrorAngleSensor22Warn){
         if(SafetyErrorAngleSensor22Warn!=SafetyErrorAngleSensor22WarnOldValue)
            SetErrorCode(123456);
    }
    if(SafetyErrorAngleSensor22Error){
         if(SafetyErrorAngleSensor22Error!=SafetyErrorAngleSensor22ErrorOldValue)
            SetErrorCode(123456);
    }
    //OldValue
    SafetyErrorAngleSensor11WarnOldValue=SafetyErrorAngleSensor11Warn;
    SafetyErrorAngleSensor11ErrorOldValue=SafetyErrorAngleSensor11Error;
    SafetyErrorAngleSensor12WarnOldValue=SafetyErrorAngleSensor12Warn;
    SafetyErrorAngleSensor12ErrorOldValue=SafetyErrorAngleSensor12Error;
    SafetyErrorAngleSensor21WarnOldValue=SafetyErrorAngleSensor21Warn;
    SafetyErrorAngleSensor21ErrorOldValue=SafetyErrorAngleSensor21Error;
    SafetyErrorAngleSensor22WarnOldValue=SafetyErrorAngleSensor22Warn;
    SafetyErrorAngleSensor22ErrorOldValue=SafetyErrorAngleSensor22Error;
}

//====================================================================
/*!
Function: handle of safety drive system
Output: None
*/
//====================================================================
void HandleSafetyDriveSys(void){
    DriveSysSafetyHandleDriveModuleAngle();
    DriveSysSafetyHandleDriveModuleSensor();
}

//====================================================================
/*!
Function: timer of safety drive system
Output: None
*/
//====================================================================
void TimerSafetyDriveSys(void){
    boolean m1,m2,m3,m4,m5,m6,m7,m8;
    static uint8 tick1,tick2,tick3,tick4,tick5,tick6,tick7,tick8;
    //1. Layer
    if(abs(*inputSafetyDriveModule11SetAngle-*inputSafetyDriveModule11ActualAngle)>AngleSensorErrorWarning)  m1=TRUE;
    else m1=FALSE;
    if(abs(*inputSafetyDriveModule11SetAngle-*inputSafetyDriveModule11ActualAngle)<AngleSensorErrorFault)  m2=TRUE;
    else m2=FALSE;
    if(abs(*inputSafetyDriveModule12SetAngle-*inputSafetyDriveModule12ActualAngle)>AngleSensorErrorWarning)  m3=TRUE;
    else m3=FALSE;
    if(abs(*inputSafetyDriveModule12SetAngle-*inputSafetyDriveModule12ActualAngle)<AngleSensorErrorFault)  m4=TRUE;
    else m4=FALSE;
    if(abs(*inputSafetyDriveModule21SetAngle-*inputSafetyDriveModule21ActualAngle)>AngleSensorErrorWarning)  m5=TRUE;
    else m5=FALSE;
    if(abs(*inputSafetyDriveModule21SetAngle-*inputSafetyDriveModule21ActualAngle)<AngleSensorErrorFault)  m6=TRUE;
    else m6=FALSE;
    if(abs(*inputSafetyDriveModule22SetAngle-*inputSafetyDriveModule22ActualAngle)>AngleSensorErrorWarning)  m7=TRUE;
    else m7=FALSE;
    if(abs(*inputSafetyDriveModule22SetAngle-*inputSafetyDriveModule22ActualAngle)<AngleSensorErrorFault)  m8=TRUE;
    else m8=FALSE;
    //2. Layer
    if(m1&m2){ if(tick1<255) tick1++;}
    else tick1=0;
    if(m2==FALSE){ if(tick2<255) tick2++;}
    else tick2=0;
    if(m3&m4){ if(tick3<255) tick3++;}
    else tick3=0;
    if(m4==FALSE){ if(tick4<255) tick4++;}
    else tick4=0;
    if(m5&m6){ if(tick5<255) tick5++;}
    else tick5=0;
    if(m6==FALSE){ if(tick6<255) tick6++;}
    else tick6=0;
    if(m7&m8){ if(tick7<255) tick7++;}
    else tick7=0;
    if(m8==FALSE){ if(tick8<255) tick8++;}
    else tick8=0;
    //output
    if(tick1>=5) SafetyAngleSensor11TimeOutWarn=1;
    else SafetyAngleSensor11TimeOutWarn=0;
    if(tick2>=5) SafetyAngleSensor11TimeOutError=1;
    else SafetyAngleSensor11TimeOutError=0;
    if(tick3>=5) SafetyAngleSensor12TimeOutWarn=1;
    else SafetyAngleSensor12TimeOutWarn=0;
    if(tick4>=5) SafetyAngleSensor12TimeOutError=1;
    else SafetyAngleSensor12TimeOutError=0;
    if(tick5>=5) SafetyAngleSensor21TimeOutWarn=1;
    else SafetyAngleSensor21TimeOutWarn=0;
    if(tick6>=5) SafetyAngleSensor21TimeOutError=1;
    else SafetyAngleSensor21TimeOutError=0;
    if(tick7>=5) SafetyAngleSensor22TimeOutWarn=1;
    else SafetyAngleSensor22TimeOutWarn=0;
    if(tick8>=5) SafetyAngleSensor22TimeOutError=1;
    else SafetyAngleSensor22TimeOutError=0;
}
