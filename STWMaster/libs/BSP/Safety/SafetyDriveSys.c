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
    inputSafetyMotor111ActualTorque=BindODMem(InverterStartIndex,SubindexInverterTPDO1HighDWord,TypeS16,0); *inputSafetyMotor111ActualTorque=0;
    inputSafetyMotor112ActualTorque=BindODMem(InverterStartIndex+0x0001,SubindexInverterTPDO1HighDWord,TypeS16,0); *inputSafetyMotor112ActualTorque=0;
    inputSafetyMotor121ActualTorque=BindODMem(InverterStartIndex+0x0002,SubindexInverterTPDO1HighDWord,TypeS16,0); *inputSafetyMotor121ActualTorque=0;
    inputSafetyMotor122ActualTorque=BindODMem(InverterStartIndex+0x0003,SubindexInverterTPDO1HighDWord,TypeS16,0); *inputSafetyMotor122ActualTorque=0;
    inputSafetyMotor211ActualTorque=BindODMem(InverterStartIndex+0x0004,SubindexInverterTPDO1HighDWord,TypeS16,0); *inputSafetyMotor211ActualTorque=0;
    inputSafetyMotor212ActualTorque=BindODMem(InverterStartIndex+0x0005,SubindexInverterTPDO1HighDWord,TypeS16,0); *inputSafetyMotor212ActualTorque=0;
    inputSafetyMotor221ActualTorque=BindODMem(InverterStartIndex+0x0006,SubindexInverterTPDO1HighDWord,TypeS16,0); *inputSafetyMotor221ActualTorque=0;
    inputSafetyMotor222ActualTorque=BindODMem(InverterStartIndex+0x0007,SubindexInverterTPDO1HighDWord,TypeS16,0); *inputSafetyMotor222ActualTorque=0;
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
    inputSafetyInverter111NodeStatus=BindODMem(InverterStartIndex,SubindexInverterNodeStatus,TypeU8,1); *inputSafetyInverter111NodeStatus=0x00;
    inputSafetyInverter112NodeStatus=BindODMem(InverterStartIndex+0x0001,SubindexInverterNodeStatus,TypeU8,1); *inputSafetyInverter112NodeStatus=0x00;
    inputSafetyInverter121NodeStatus=BindODMem(InverterStartIndex+0x0002,SubindexInverterNodeStatus,TypeU8,1); *inputSafetyInverter121NodeStatus=0x00;
    inputSafetyInverter122NodeStatus=BindODMem(InverterStartIndex+0x0003,SubindexInverterNodeStatus,TypeU8,1); *inputSafetyInverter122NodeStatus=0x00;
    inputSafetyInverter211NodeStatus=BindODMem(InverterStartIndex+0x0004,SubindexInverterNodeStatus,TypeU8,1); *inputSafetyInverter211NodeStatus=0x00;
    inputSafetyInverter212NodeStatus=BindODMem(InverterStartIndex+0x0005,SubindexInverterNodeStatus,TypeU8,1); *inputSafetyInverter212NodeStatus=0x00;
    inputSafetyInverter221NodeStatus=BindODMem(InverterStartIndex+0x0006,SubindexInverterNodeStatus,TypeU8,1); *inputSafetyInverter221NodeStatus=0x00;
    inputSafetyInverter222NodeStatus=BindODMem(InverterStartIndex+0x0007,SubindexInverterNodeStatus,TypeU8,1); *inputSafetyInverter222NodeStatus=0x00;
    inputSafetyKamera1NodeStatus=BindODMem(AutoDriveStartIndex,SubindexCamera1NodeStatus,TypeU8,1); *inputSafetyKamera1NodeStatus=0x00;
    inputSafetyKamera2NodeStatus=BindODMem(AutoDriveStartIndex,SubindexCamera2NodeStatus,TypeU8,1); *inputSafetyKamera2NodeStatus=0x00;

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
    if((*inputSafetyGetDriveSystemStatusWord&KeySafteyGetDriveSysZeroSet)==0)  m9=TRUE;
    else m9=FALSE;
    //2. Layer
    SafetyErrorDriveModule11AngleOut=(m1|m2)&m9;
    SafetyErrorDriveModule12AngleOut=(m3|m4)&m9;
    SafetyErrorDriveModule21AngleOut=(m5|m6)&m9;
    SafetyErrorDriveModule22AngleOut=(m7|m8)&m9;
    //Output
    if(SafetyErrorDriveModule11AngleOut){
         if(SafetyErrorDriveModule11AngleOut!=SafetyErrorDriveModule11AngleOutOldValue)
            SetErrorCode(1022021);
         setFault();
    }
    if(SafetyErrorDriveModule12AngleOut){
         if(SafetyErrorDriveModule12AngleOut!=SafetyErrorDriveModule12AngleOutOldValue)
            SetErrorCode(1022022);
         setFault();
    }
    if(SafetyErrorDriveModule21AngleOut){
         if(SafetyErrorDriveModule21AngleOut!=SafetyErrorDriveModule21AngleOutOldValue)
            SetErrorCode(1022023);
         setFault();
    }
    if(SafetyErrorDriveModule22AngleOut){
         if(SafetyErrorDriveModule22AngleOut!=SafetyErrorDriveModule22AngleOutOldValue)
            SetErrorCode(1022024);
         setFault();
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
    boolean m1,m2,m3,m4;
    static boolean SafetyErrorAngleSensor11ErrorOldValue;
    static boolean SafetyErrorAngleSensor12ErrorOldValue;
    static boolean SafetyErrorAngleSensor21ErrorOldValue;
    static boolean SafetyErrorAngleSensor22ErrorOldValue;
    //1. Layer
    if(SafetyAngleSensor11TimeOutError==1)  m1=TRUE;
    else m1=FALSE;
    if(SafetyAngleSensor12TimeOutError==1)  m2=TRUE;
    else m2=FALSE;
    if(SafetyAngleSensor21TimeOutError==1)  m3=TRUE;
    else m3=FALSE;
    if(SafetyAngleSensor22TimeOutError==1)  m4=TRUE;
    else m4=FALSE;
    //2. Layer
    SafetyErrorAngleSensor11Error=m1;
    SafetyErrorAngleSensor12Error=m2;
    SafetyErrorAngleSensor21Error=m3;
    SafetyErrorAngleSensor22Error=m4;
    //Output
    if(SafetyErrorAngleSensor11Error){
         if(SafetyErrorAngleSensor11Error!=SafetyErrorAngleSensor11ErrorOldValue)
            SetErrorCode(1022011);
         setFault();
    }
    if(SafetyErrorAngleSensor12Error){
         if(SafetyErrorAngleSensor12Error!=SafetyErrorAngleSensor12ErrorOldValue)
            SetErrorCode(1022012);
         setFault();
    }
    if(SafetyErrorAngleSensor21Error){
         if(SafetyErrorAngleSensor21Error!=SafetyErrorAngleSensor21ErrorOldValue)
            SetErrorCode(1022013);
         setFault();
    }
    if(SafetyErrorAngleSensor22Error){
         if(SafetyErrorAngleSensor22Error!=SafetyErrorAngleSensor22ErrorOldValue)
            SetErrorCode(1022014);
         setFault();
    }
    //OldValue
    SafetyErrorAngleSensor11ErrorOldValue=SafetyErrorAngleSensor11Error;
    SafetyErrorAngleSensor12ErrorOldValue=SafetyErrorAngleSensor12Error;
    SafetyErrorAngleSensor21ErrorOldValue=SafetyErrorAngleSensor21Error;
    SafetyErrorAngleSensor22ErrorOldValue=SafetyErrorAngleSensor22Error;
}

//====================================================================
/*!
Function: DriveSysSafetyHandleDriveModuleKontakeLose
Output: None
*/
//====================================================================
void DriveSysSafetyHandleDriveModuleKontakeLose(void){
    boolean m1,m2,m3,m4;
    static boolean SafetyErrorDriveModule11KontaktLoseOldValue;
    static boolean SafetyErrorDriveModule12KontaktLoseOldValue;
    static boolean SafetyErrorDriveModule21KontaktLoseOldValue;
    static boolean SafetyErrorDriveModule22KontaktLoseOldValue;
    //1. Layer
    if(SafetyDriveModule11KontaktTimeOutError==1)  m1=TRUE;
    else m1=FALSE;
    if(SafetyDriveModule12KontaktTimeOutError==1)  m2=TRUE;
    else m2=FALSE;
    if(SafetyDriveModule21KontaktTimeOutError==1)  m3=TRUE;
    else m3=FALSE;
    if(SafetyDriveModule22KontaktTimeOutError==1)  m4=TRUE;
    else m4=FALSE;
    //2. Layer
    SafetyErrorDriveModule11KontaktLose=m1;
    SafetyErrorDriveModule12KontaktLose=m2;
    SafetyErrorDriveModule21KontaktLose=m3;
    SafetyErrorDriveModule22KontaktLose=m4;
    //Output
    if(SafetyErrorDriveModule11KontaktLose){
         if(SafetyErrorDriveModule11KontaktLose!=SafetyErrorDriveModule11KontaktLoseOldValue)
            SetErrorCode(1022001);
         setFault();
    }
    if(SafetyErrorDriveModule12KontaktLose){
         if(SafetyErrorDriveModule12KontaktLose!=SafetyErrorDriveModule12KontaktLoseOldValue)
            SetErrorCode(1022002);
         setFault();
    }
    if(SafetyErrorDriveModule21KontaktLose){
         if(SafetyErrorDriveModule21KontaktLose!=SafetyErrorDriveModule21KontaktLoseOldValue)
            SetErrorCode(1022003);
         setFault();
    }
    if(SafetyErrorDriveModule22KontaktLose){
         if(SafetyErrorDriveModule22KontaktLose!=SafetyErrorDriveModule22KontaktLoseOldValue)
            SetErrorCode(1022004);
         setFault();
    }
    //OldValue
    SafetyErrorDriveModule11KontaktLoseOldValue=SafetyErrorDriveModule11KontaktLose;
    SafetyErrorDriveModule12KontaktLoseOldValue=SafetyErrorDriveModule12KontaktLose;
    SafetyErrorDriveModule21KontaktLoseOldValue=SafetyErrorDriveModule21KontaktLose;
    SafetyErrorDriveModule22KontaktLoseOldValue=SafetyErrorDriveModule22KontaktLose;
}

//====================================================================
/*!
Function: DriveSysSafetyHandleMotorDrehzahl
Output: None
*/
//====================================================================
void DriveSysSafetyHandleMotorDrehzahl(void){
    boolean m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12,m13,m14,m15,m16;
    static boolean SafetyWarnMotor111DrehzahlPlausiOldValue;
    static boolean SafetyWarnMotor112DrehzahlPlausiOldValue;
    static boolean SafetyWarnMotor121DrehzahlPlausiOldValue;
    static boolean SafetyWarnMotor122DrehzahlPlausiOldValue;
    static boolean SafetyWarnMotor211DrehzahlPlausiOldValue;
    static boolean SafetyWarnMotor212DrehzahlPlausiOldValue;
    static boolean SafetyWarnMotor221DrehzahlPlausiOldValue;
    static boolean SafetyWarnMotor222DrehzahlPlausiOldValue;
    static boolean SafetyErrorMotor111DrehzahlPlausiOldValue;
    static boolean SafetyErrorMotor112DrehzahlPlausiOldValue;
    static boolean SafetyErrorMotor121DrehzahlPlausiOldValue;
    static boolean SafetyErrorMotor122DrehzahlPlausiOldValue;
    static boolean SafetyErrorMotor211DrehzahlPlausiOldValue;
    static boolean SafetyErrorMotor212DrehzahlPlausiOldValue;
    static boolean SafetyErrorMotor221DrehzahlPlausiOldValue;
    static boolean SafetyErrorMotor222DrehzahlPlausiOldValue;
    //1. Layer
    if(SafetyWarnMotor111DrehzahlPlausiTimeOut==1)  m1=TRUE;
    else m1=FALSE;
    if(SafetyWarnMotor112DrehzahlPlausiTimeOut==1)  m2=TRUE;
    else m2=FALSE;
    if(SafetyWarnMotor121DrehzahlPlausiTimeOut==1)  m3=TRUE;
    else m3=FALSE;
    if(SafetyWarnMotor122DrehzahlPlausiTimeOut==1)  m4=TRUE;
    else m4=FALSE;
    if(SafetyWarnMotor211DrehzahlPlausiTimeOut==1)  m5=TRUE;
    else m5=FALSE;
    if(SafetyWarnMotor212DrehzahlPlausiTimeOut==1)  m6=TRUE;
    else m6=FALSE;
    if(SafetyWarnMotor221DrehzahlPlausiTimeOut==1)  m7=TRUE;
    else m7=FALSE;
    if(SafetyWarnMotor222DrehzahlPlausiTimeOut==1)  m8=TRUE;
    else m8=FALSE;
    if(SafetyErrorMotor111DrehzahlPlausiTimeOut==1)  m9=TRUE;
    else m9=FALSE;
    if(SafetyErrorMotor112DrehzahlPlausiTimeOut==1)  m10=TRUE;
    else m10=FALSE;
    if(SafetyErrorMotor121DrehzahlPlausiTimeOut==1)  m11=TRUE;
    else m11=FALSE;
    if(SafetyErrorMotor122DrehzahlPlausiTimeOut==1)  m12=TRUE;
    else m12=FALSE;
    if(SafetyErrorMotor211DrehzahlPlausiTimeOut==1)  m13=TRUE;
    else m13=FALSE;
    if(SafetyErrorMotor212DrehzahlPlausiTimeOut==1)  m14=TRUE;
    else m14=FALSE;
    if(SafetyErrorMotor221DrehzahlPlausiTimeOut==1)  m15=TRUE;
    else m15=FALSE;
    if(SafetyErrorMotor222DrehzahlPlausiTimeOut==1)  m16=TRUE;
    else m16=FALSE;
    //2. Layer
    SafetyWarnMotor111DrehzahlPlausi=m1;
    SafetyWarnMotor112DrehzahlPlausi=m2;
    SafetyWarnMotor121DrehzahlPlausi=m3;
    SafetyWarnMotor122DrehzahlPlausi=m4;
    SafetyWarnMotor211DrehzahlPlausi=m5;
    SafetyWarnMotor212DrehzahlPlausi=m6;
    SafetyWarnMotor221DrehzahlPlausi=m7;
    SafetyWarnMotor222DrehzahlPlausi=m8;
    SafetyErrorMotor111DrehzahlPlausi=m9;
    SafetyErrorMotor112DrehzahlPlausi=m10;
    SafetyErrorMotor121DrehzahlPlausi=m11;
    SafetyErrorMotor122DrehzahlPlausi=m12;
    SafetyErrorMotor211DrehzahlPlausi=m13;
    SafetyErrorMotor212DrehzahlPlausi=m14;
    SafetyErrorMotor221DrehzahlPlausi=m15;
    SafetyErrorMotor222DrehzahlPlausi=m16;
    //Output
    if(SafetyWarnMotor111DrehzahlPlausi){
         if(SafetyWarnMotor111DrehzahlPlausi!=SafetyWarnMotor111DrehzahlPlausiOldValue)
            SetErrorCode(2022111);
         setFault();
    }
    if(SafetyWarnMotor112DrehzahlPlausi){
         if(SafetyWarnMotor112DrehzahlPlausi!=SafetyWarnMotor112DrehzahlPlausiOldValue)
            SetErrorCode(2022112);
         setFault();
    }
    if(SafetyWarnMotor121DrehzahlPlausi){
         if(SafetyWarnMotor121DrehzahlPlausi!=SafetyWarnMotor121DrehzahlPlausiOldValue)
            SetErrorCode(2022113);
         setFault();
    }
    if(SafetyWarnMotor122DrehzahlPlausi){
         if(SafetyWarnMotor122DrehzahlPlausi!=SafetyWarnMotor122DrehzahlPlausiOldValue)
            SetErrorCode(2022114);
         setFault();
    }
    if(SafetyWarnMotor211DrehzahlPlausi){
         if(SafetyWarnMotor211DrehzahlPlausi!=SafetyWarnMotor211DrehzahlPlausiOldValue)
            SetErrorCode(2022115);
         setFault();
    }
    if(SafetyWarnMotor212DrehzahlPlausi){
         if(SafetyWarnMotor212DrehzahlPlausi!=SafetyWarnMotor212DrehzahlPlausiOldValue)
            SetErrorCode(2022116);
         setFault();
    }
    if(SafetyWarnMotor221DrehzahlPlausi){
         if(SafetyWarnMotor221DrehzahlPlausi!=SafetyWarnMotor221DrehzahlPlausiOldValue)
            SetErrorCode(2022117);
         setFault();
    }
    if(SafetyWarnMotor222DrehzahlPlausi){
         if(SafetyWarnMotor222DrehzahlPlausi!=SafetyWarnMotor222DrehzahlPlausiOldValue)
            SetErrorCode(2022118);
         setFault();
    }
    if(SafetyErrorMotor111DrehzahlPlausi){
         if(SafetyErrorMotor111DrehzahlPlausi!=SafetyErrorMotor111DrehzahlPlausiOldValue)
            SetErrorCode(1022121);
         setFault();
    }
    if(SafetyErrorMotor112DrehzahlPlausi){
         if(SafetyErrorMotor112DrehzahlPlausi!=SafetyErrorMotor112DrehzahlPlausiOldValue)
            SetErrorCode(1022122);
         setFault();
    }
    if(SafetyErrorMotor121DrehzahlPlausi){
         if(SafetyErrorMotor121DrehzahlPlausi!=SafetyErrorMotor121DrehzahlPlausiOldValue)
            SetErrorCode(1022123);
         setFault();
    }
    if(SafetyErrorMotor122DrehzahlPlausi){
         if(SafetyErrorMotor122DrehzahlPlausi!=SafetyErrorMotor122DrehzahlPlausiOldValue)
            SetErrorCode(1022124);
         setFault();
    }
    if(SafetyErrorMotor211DrehzahlPlausi){
         if(SafetyErrorMotor211DrehzahlPlausi!=SafetyErrorMotor211DrehzahlPlausiOldValue)
            SetErrorCode(1022125);
         setFault();
    }
    if(SafetyErrorMotor212DrehzahlPlausi){
         if(SafetyErrorMotor212DrehzahlPlausi!=SafetyErrorMotor212DrehzahlPlausiOldValue)
            SetErrorCode(1022126);
         setFault();
    }
    if(SafetyErrorMotor221DrehzahlPlausi){
         if(SafetyErrorMotor221DrehzahlPlausi!=SafetyErrorMotor221DrehzahlPlausiOldValue)
            SetErrorCode(1022127);
         setFault();
    }
    if(SafetyErrorMotor222DrehzahlPlausi){
         if(SafetyErrorMotor222DrehzahlPlausi!=SafetyErrorMotor222DrehzahlPlausiOldValue)
            SetErrorCode(1022128);
         setFault();
    }
    //OldValue
    SafetyWarnMotor111DrehzahlPlausiOldValue=SafetyWarnMotor111DrehzahlPlausi;
    SafetyWarnMotor112DrehzahlPlausiOldValue=SafetyWarnMotor112DrehzahlPlausi;
    SafetyWarnMotor121DrehzahlPlausiOldValue=SafetyWarnMotor121DrehzahlPlausi;
    SafetyWarnMotor122DrehzahlPlausiOldValue=SafetyWarnMotor122DrehzahlPlausi;
    SafetyWarnMotor211DrehzahlPlausiOldValue=SafetyWarnMotor211DrehzahlPlausi;
    SafetyWarnMotor212DrehzahlPlausiOldValue=SafetyWarnMotor212DrehzahlPlausi;
    SafetyWarnMotor221DrehzahlPlausiOldValue=SafetyWarnMotor221DrehzahlPlausi;
    SafetyWarnMotor222DrehzahlPlausiOldValue=SafetyWarnMotor222DrehzahlPlausi;
    SafetyErrorMotor111DrehzahlPlausiOldValue=SafetyErrorMotor111DrehzahlPlausi;
    SafetyErrorMotor112DrehzahlPlausiOldValue=SafetyErrorMotor112DrehzahlPlausi;
    SafetyErrorMotor121DrehzahlPlausiOldValue=SafetyErrorMotor121DrehzahlPlausi;
    SafetyErrorMotor122DrehzahlPlausiOldValue=SafetyErrorMotor122DrehzahlPlausi;
    SafetyErrorMotor211DrehzahlPlausiOldValue=SafetyErrorMotor211DrehzahlPlausi;
    SafetyErrorMotor212DrehzahlPlausiOldValue=SafetyErrorMotor212DrehzahlPlausi;
    SafetyErrorMotor221DrehzahlPlausiOldValue=SafetyErrorMotor221DrehzahlPlausi;
    SafetyErrorMotor222DrehzahlPlausiOldValue=SafetyErrorMotor222DrehzahlPlausi;
}

//====================================================================
/*!
Function: DriveSysSafetyHandleMotorUmrichter
Output: None
*/
//====================================================================
void DriveSysSafetyHandleMotorUmrichter(void){
    boolean m1,m2,m3,m4,m5,m6,m7,m8;
    static boolean SafetyErrorMotor111UmrichterOldValue;
    static boolean SafetyErrorMotor112UmrichterOldValue;
    static boolean SafetyErrorMotor121UmrichterOldValue;
    static boolean SafetyErrorMotor122UmrichterOldValue;
    static boolean SafetyErrorMotor211UmrichterOldValue;
    static boolean SafetyErrorMotor212UmrichterOldValue;
    static boolean SafetyErrorMotor221UmrichterOldValue;
    static boolean SafetyErrorMotor222UmrichterOldValue;
    //1. Layer
    if(*inputSafetyMotor111StatusByte&KeySafetyMotorUmrichterFault)  m1=TRUE;
    else m1=FALSE;
    if(*inputSafetyMotor112StatusByte&KeySafetyMotorUmrichterFault)  m2=TRUE;
    else m2=FALSE;
    if(*inputSafetyMotor121StatusByte&KeySafetyMotorUmrichterFault)  m3=TRUE;
    else m3=FALSE;
    if(*inputSafetyMotor122StatusByte&KeySafetyMotorUmrichterFault)  m4=TRUE;
    else m4=FALSE;
    if(*inputSafetyMotor211StatusByte&KeySafetyMotorUmrichterFault)  m5=TRUE;
    else m5=FALSE;
    if(*inputSafetyMotor212StatusByte&KeySafetyMotorUmrichterFault)  m6=TRUE;
    else m6=FALSE;
    if(*inputSafetyMotor221StatusByte&KeySafetyMotorUmrichterFault)  m7=TRUE;
    else m7=FALSE;
    if(*inputSafetyMotor222StatusByte&KeySafetyMotorUmrichterFault)  m8=TRUE;
    else m8=FALSE;
    //2. Layer
    SafetyErrorMotor111Umrichter=m1;
    SafetyErrorMotor112Umrichter=m2;
    SafetyErrorMotor121Umrichter=m3;
    SafetyErrorMotor122Umrichter=m4;
    SafetyErrorMotor211Umrichter=m5;
    SafetyErrorMotor212Umrichter=m6;
    SafetyErrorMotor221Umrichter=m7;
    SafetyErrorMotor222Umrichter=m8;
    //Output
    if(SafetyErrorMotor111Umrichter){
         if(SafetyErrorMotor111Umrichter!=SafetyErrorMotor111UmrichterOldValue)
            SetErrorCode(1092101);
         setFault();
    }
    if(SafetyErrorMotor112Umrichter){
         if(SafetyErrorMotor112Umrichter!=SafetyErrorMotor112UmrichterOldValue)
            SetErrorCode(1112102);
         setFault();
    }
    if(SafetyErrorMotor121Umrichter){
         if(SafetyErrorMotor121Umrichter!=SafetyErrorMotor121UmrichterOldValue)
            SetErrorCode(1122103);
         setFault();
    }
    if(SafetyErrorMotor122Umrichter){
         if(SafetyErrorMotor122Umrichter!=SafetyErrorMotor122UmrichterOldValue)
            SetErrorCode(1132104);
         setFault();
    }
    if(SafetyErrorMotor211Umrichter){
         if(SafetyErrorMotor211Umrichter!=SafetyErrorMotor211UmrichterOldValue)
            SetErrorCode(1162105);
         setFault();
    }
    if(SafetyErrorMotor212Umrichter){
         if(SafetyErrorMotor212Umrichter!=SafetyErrorMotor212UmrichterOldValue)
            SetErrorCode(1152106);
         setFault();
    }
    if(SafetyErrorMotor221Umrichter){
         if(SafetyErrorMotor221Umrichter!=SafetyErrorMotor221UmrichterOldValue)
            SetErrorCode(1142107);
         setFault();
    }
    if(SafetyErrorMotor222Umrichter){
         if(SafetyErrorMotor222Umrichter!=SafetyErrorMotor222UmrichterOldValue)
            SetErrorCode(1132108);
         setFault();
    }
    //OldValue
    SafetyErrorMotor111UmrichterOldValue=SafetyErrorMotor111Umrichter;
    SafetyErrorMotor112UmrichterOldValue=SafetyErrorMotor112Umrichter;
    SafetyErrorMotor121UmrichterOldValue=SafetyErrorMotor121Umrichter;
    SafetyErrorMotor122UmrichterOldValue=SafetyErrorMotor122Umrichter;
    SafetyErrorMotor211UmrichterOldValue=SafetyErrorMotor211Umrichter;
    SafetyErrorMotor212UmrichterOldValue=SafetyErrorMotor212Umrichter;
    SafetyErrorMotor221UmrichterOldValue=SafetyErrorMotor221Umrichter;
    SafetyErrorMotor222UmrichterOldValue=SafetyErrorMotor222Umrichter;
}

//====================================================================
/*!
Function: KeySafetyNodeStatus
Output: None
*/
//====================================================================
void KeySafetyNodeStatus(void){
    boolean m1,m2,m3,m4,m5,m6,m7,m8,m9,m10;
    static boolean SafetyErrorMotor111UmrichterOfflineOldValue;
    static boolean SafetyErrorMotor112UmrichterOfflineOldValue;
    static boolean SafetyErrorMotor121UmrichterOfflineOldValue;
    static boolean SafetyErrorMotor122UmrichterOfflineOldValue;
    static boolean SafetyErrorMotor211UmrichterOfflineOldValue;
    static boolean SafetyErrorMotor212UmrichterOfflineOldValue;
    static boolean SafetyErrorMotor221UmrichterOfflineOldValue;
    static boolean SafetyErrorMotor222UmrichterOfflineOldValue;
    static boolean SafetyErrorKamera1OfflineOldValue;
    static boolean SafetyErrorKamera2OfflineOldValue;
    //1. Layer
    if(SafetyErrorMotor111UmrichterOfflineTimeOut==1)  m1=TRUE;
    else m1=FALSE;
    if(SafetyErrorMotor112UmrichterOfflineTimeOut==1)  m2=TRUE;
    else m2=FALSE;
    if(SafetyErrorMotor121UmrichterOfflineTimeOut==1)  m3=TRUE;
    else m3=FALSE;
    if(SafetyErrorMotor122UmrichterOfflineTimeOut==1)  m4=TRUE;
    else m4=FALSE;
    if(SafetyErrorMotor211UmrichterOfflineTimeOut==1)  m5=TRUE;
    else m5=FALSE;
    if(SafetyErrorMotor212UmrichterOfflineTimeOut==1)  m6=TRUE;
    else m6=FALSE;
    if(SafetyErrorMotor221UmrichterOfflineTimeOut==1)  m7=TRUE;
    else m7=FALSE;
    if(SafetyErrorMotor222UmrichterOfflineTimeOut==1)  m8=TRUE;
    else m8=FALSE;
    if(SafetyErrorKamera1OfflineTimeOut==1)  m9=TRUE;
    else m9=FALSE;
    if(SafetyErrorKamera2OfflineTimeOut==1)  m10=TRUE;
    else m10=FALSE;
    //2. Layer
    SafetyErrorMotor111UmrichterOffline=m1;
    SafetyErrorMotor112UmrichterOffline=m2;
    SafetyErrorMotor121UmrichterOffline=m3;
    SafetyErrorMotor122UmrichterOffline=m4;
    SafetyErrorMotor211UmrichterOffline=m5;
    SafetyErrorMotor212UmrichterOffline=m6;
    SafetyErrorMotor221UmrichterOffline=m7;
    SafetyErrorMotor222UmrichterOffline=m8;
    SafetyErrorKamera1Offline=m9;
    SafetyErrorKamera2Offline=m10;
    SafetyErrorMotorUmrichterOffline=m1|m2|m3|m4|m5|m6|m7|m8;
    SafetyErrorKameraOffline=m9|m10;
    //Output
    if(SafetyErrorMotor111UmrichterOffline){
         if(SafetyErrorMotor111UmrichterOffline!=SafetyErrorMotor111UmrichterOfflineOldValue)
            SetErrorCode(1091211);
         setFault();
    }
    if(SafetyErrorMotor112UmrichterOffline){
         if(SafetyErrorMotor112UmrichterOffline!=SafetyErrorMotor112UmrichterOfflineOldValue)
            SetErrorCode(1101212);
         setFault();
    }
    if(SafetyErrorMotor121UmrichterOffline){
         if(SafetyErrorMotor121UmrichterOffline!=SafetyErrorMotor121UmrichterOfflineOldValue)
            SetErrorCode(1111213);
         setFault();
    }
    if(SafetyErrorMotor122UmrichterOffline){
         if(SafetyErrorMotor122UmrichterOffline!=SafetyErrorMotor122UmrichterOfflineOldValue)
            SetErrorCode(1121214);
         setFault();
    }
    if(SafetyErrorMotor211UmrichterOffline){
         if(SafetyErrorMotor211UmrichterOffline!=SafetyErrorMotor211UmrichterOfflineOldValue)
            SetErrorCode(1161215);
         setFault();
    }
    if(SafetyErrorMotor212UmrichterOffline){
         if(SafetyErrorMotor212UmrichterOffline!=SafetyErrorMotor212UmrichterOfflineOldValue)
            SetErrorCode(1151216);
         setFault();
    }
    if(SafetyErrorMotor221UmrichterOffline){
         if(SafetyErrorMotor221UmrichterOffline!=SafetyErrorMotor221UmrichterOfflineOldValue)
            SetErrorCode(1141217);
         setFault();
    }
    if(SafetyErrorMotor222UmrichterOffline){
         if(SafetyErrorMotor222UmrichterOffline!=SafetyErrorMotor222UmrichterOfflineOldValue)
            SetErrorCode(1131218);
         setFault();
    }
    if(SafetyErrorKamera1Offline){
         if(SafetyErrorKamera1Offline!=SafetyErrorKamera1OfflineOldValue)
            SetErrorCode(1051236);
         setFault();
    }
    if(SafetyErrorKamera2Offline){
         if(SafetyErrorKamera2Offline!=SafetyErrorKamera2OfflineOldValue)
            SetErrorCode(1061237);
         setFault();
    }
    //OldValue
    SafetyErrorMotor111UmrichterOfflineOldValue=SafetyErrorMotor111UmrichterOffline;
    SafetyErrorMotor112UmrichterOfflineOldValue=SafetyErrorMotor112UmrichterOffline;
    SafetyErrorMotor121UmrichterOfflineOldValue=SafetyErrorMotor121UmrichterOffline;
    SafetyErrorMotor122UmrichterOfflineOldValue=SafetyErrorMotor122UmrichterOffline;
    SafetyErrorMotor211UmrichterOfflineOldValue=SafetyErrorMotor211UmrichterOffline;
    SafetyErrorMotor212UmrichterOfflineOldValue=SafetyErrorMotor212UmrichterOffline;
    SafetyErrorMotor221UmrichterOfflineOldValue=SafetyErrorMotor221UmrichterOffline;
    SafetyErrorMotor222UmrichterOfflineOldValue=SafetyErrorMotor222UmrichterOffline;
    SafetyErrorKamera1OfflineOldValue=SafetyErrorKamera1Offline;
    SafetyErrorKamera2OfflineOldValue=SafetyErrorKamera2Offline;
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
    DriveSysSafetyHandleDriveModuleKontakeLose();
    DriveSysSafetyHandleMotorDrehzahl();
    DriveSysSafetyHandleMotorUmrichter();
    KeySafetyNodeStatus();
}

//====================================================================
/*!
Function: timer of safety drive system
Output: None
*/
//====================================================================
void TimerSafetyDriveSys(void){
    boolean m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12,m13,m14,m15,m16,m17,m18,m19,m20,m21,m22,m23,m24,m25,m26,m27,m28,m29,m30,m31,m32,m33,m34,m35,m36,m37,m38;
    static uint8 tick1,tick2,tick3,tick4,tick5,tick6,tick7,tick8,tick9,tick10,tick11,tick12,tick13,tick14,tick15,tick16,tick17,tick18,tick19,tick20,tick21,tick22,tick23,tick24,tick25,tick26,tick27,tick28,tick29,tick30,tick31,tick32,tick33,tick34;
    //1. Layer
    if(abs(*inputSafetyDriveModule11SetAngle-*inputSafetyDriveModule11ActualAngle)<AngleSensorErrorFault)  m1=TRUE;
    else m1=FALSE;
    if(abs(*inputSafetyDriveModule12SetAngle-*inputSafetyDriveModule12ActualAngle)<AngleSensorErrorFault)  m2=TRUE;
    else m2=FALSE;
    if(abs(*inputSafetyDriveModule21SetAngle-*inputSafetyDriveModule21ActualAngle)<AngleSensorErrorFault)  m3=TRUE;
    else m3=FALSE;
    if(abs(*inputSafetyDriveModule22SetAngle-*inputSafetyDriveModule22ActualAngle)<AngleSensorErrorFault)  m4=TRUE;
    else m4=FALSE;
    if((abs(*inputSafetyMotor111ActualSpeed)>DriveModuleLostKontakeMinSpeed)&&(abs(*inputSafetyMotor111ActualTorque)<DriveModuleLostKontakeMinTorque))  m5=TRUE;
    else m5=FALSE;
    if((abs(*inputSafetyMotor112ActualSpeed)>DriveModuleLostKontakeMinSpeed)&&(abs(*inputSafetyMotor112ActualTorque)<DriveModuleLostKontakeMinTorque))  m6=TRUE;
    else m6=FALSE;
    if((abs(*inputSafetyMotor121ActualSpeed)>DriveModuleLostKontakeMinSpeed)&&(abs(*inputSafetyMotor121ActualTorque)<DriveModuleLostKontakeMinTorque))  m7=TRUE;
    else m7=FALSE;
    if((abs(*inputSafetyMotor122ActualSpeed)>DriveModuleLostKontakeMinSpeed)&&(abs(*inputSafetyMotor122ActualTorque)<DriveModuleLostKontakeMinTorque))  m8=TRUE;
    else m8=FALSE;
    if((abs(*inputSafetyMotor211ActualSpeed)>DriveModuleLostKontakeMinSpeed)&&(abs(*inputSafetyMotor211ActualTorque)<DriveModuleLostKontakeMinTorque))  m9=TRUE;
    else m9=FALSE;
    if((abs(*inputSafetyMotor212ActualSpeed)>DriveModuleLostKontakeMinSpeed)&&(abs(*inputSafetyMotor212ActualTorque)<DriveModuleLostKontakeMinTorque))  m10=TRUE;
    else m10=FALSE;
    if((abs(*inputSafetyMotor221ActualSpeed)>DriveModuleLostKontakeMinSpeed)&&(abs(*inputSafetyMotor221ActualTorque)<DriveModuleLostKontakeMinTorque))  m11=TRUE;
    else m11=FALSE;
    if((abs(*inputSafetyMotor222ActualSpeed)>DriveModuleLostKontakeMinSpeed)&&(abs(*inputSafetyMotor222ActualTorque)<DriveModuleLostKontakeMinTorque))  m12=TRUE;
    else m12=FALSE;
    if(abs(*inputSafetyMotor111SetSpeed-*inputSafetyMotor111ActualSpeed)>MotorPlausiWarnDrehzahl)  m13=TRUE;
    else m13=FALSE;
    if(abs(*inputSafetyMotor111SetSpeed-*inputSafetyMotor111ActualSpeed)>MotorPlausiFehlerDrehzahl)  m14=TRUE;
    else m14=FALSE;
    if(abs(*inputSafetyMotor112SetSpeed-*inputSafetyMotor112ActualSpeed)>MotorPlausiWarnDrehzahl)  m15=TRUE;
    else m15=FALSE;
    if(abs(*inputSafetyMotor112SetSpeed-*inputSafetyMotor112ActualSpeed)>MotorPlausiFehlerDrehzahl)  m16=TRUE;
    else m16=FALSE;
    if(abs(*inputSafetyMotor121SetSpeed-*inputSafetyMotor121ActualSpeed)>MotorPlausiWarnDrehzahl)  m17=TRUE;
    else m17=FALSE;
    if(abs(*inputSafetyMotor121SetSpeed-*inputSafetyMotor121ActualSpeed)>MotorPlausiFehlerDrehzahl)  m18=TRUE;
    else m18=FALSE;
    if(abs(*inputSafetyMotor122SetSpeed-*inputSafetyMotor122ActualSpeed)>MotorPlausiWarnDrehzahl)  m19=TRUE;
    else m19=FALSE;
    if(abs(*inputSafetyMotor122SetSpeed-*inputSafetyMotor122ActualSpeed)>MotorPlausiFehlerDrehzahl)  m20=TRUE;
    else m20=FALSE;
    if(abs(*inputSafetyMotor211SetSpeed-*inputSafetyMotor211ActualSpeed)>MotorPlausiWarnDrehzahl)  m21=TRUE;
    else m21=FALSE;
    if(abs(*inputSafetyMotor211SetSpeed-*inputSafetyMotor211ActualSpeed)>MotorPlausiFehlerDrehzahl)  m22=TRUE;
    else m22=FALSE;
    if(abs(*inputSafetyMotor212SetSpeed-*inputSafetyMotor212ActualSpeed)>MotorPlausiWarnDrehzahl)  m23=TRUE;
    else m23=FALSE;
    if(abs(*inputSafetyMotor212SetSpeed-*inputSafetyMotor212ActualSpeed)>MotorPlausiFehlerDrehzahl)  m24=TRUE;
    else m24=FALSE;
    if(abs(*inputSafetyMotor221SetSpeed-*inputSafetyMotor221ActualSpeed)>MotorPlausiWarnDrehzahl)  m25=TRUE;
    else m25=FALSE;
    if(abs(*inputSafetyMotor221SetSpeed-*inputSafetyMotor221ActualSpeed)>MotorPlausiFehlerDrehzahl)  m26=TRUE;
    else m26=FALSE;
    if(abs(*inputSafetyMotor222SetSpeed-*inputSafetyMotor222ActualSpeed)>MotorPlausiWarnDrehzahl)  m27=TRUE;
    else m27=FALSE;
    if(abs(*inputSafetyMotor222SetSpeed-*inputSafetyMotor222ActualSpeed)>MotorPlausiFehlerDrehzahl)  m28=TRUE;
    else m28=FALSE;
    if(*inputSafetyInverter111NodeStatus<=KeySafetyNodeDisconneted)  m29=TRUE;
    else m29=FALSE;
    if(*inputSafetyInverter112NodeStatus<=KeySafetyNodeDisconneted)  m30=TRUE;
    else m30=FALSE;
    if(*inputSafetyInverter121NodeStatus<=KeySafetyNodeDisconneted)  m31=TRUE;
    else m31=FALSE;
    if(*inputSafetyInverter122NodeStatus<=KeySafetyNodeDisconneted)  m32=TRUE;
    else m32=FALSE;
    if(*inputSafetyInverter211NodeStatus<=KeySafetyNodeDisconneted)  m33=TRUE;
    else m33=FALSE;
    if(*inputSafetyInverter212NodeStatus<=KeySafetyNodeDisconneted)  m34=TRUE;
    else m34=FALSE;
    if(*inputSafetyInverter221NodeStatus<=KeySafetyNodeDisconneted)  m35=TRUE;
    else m35=FALSE;
    if(*inputSafetyInverter222NodeStatus<=KeySafetyNodeDisconneted)  m36=TRUE;
    else m36=FALSE;
    if(*inputSafetyKamera1NodeStatus<=KeySafetyNodeDisconneted)  m37=TRUE;
    else m37=FALSE;
    if(*inputSafetyKamera2NodeStatus<=KeySafetyNodeDisconneted)  m38=TRUE;
    else m38=FALSE;
    //2. Layer
    if(m1==FALSE){ if(tick1<255) tick1++;}
    else tick1=0;
    if(m2==FALSE){ if(tick2<255) tick2++;}
    else tick2=0;
    if(m3==FALSE){ if(tick3<255) tick3++;}
    else tick3=0;
    if(m4==FALSE){ if(tick4<255) tick4++;}
    else tick4=0;
    if(m5|m6){ if(tick5<255) tick5++;}
    else tick5=0;
    if(m7|m8){ if(tick6<255) tick6++;}
    else tick6=0;
    if(m9|m10){ if(tick7<255) tick7++;}
    else tick7=0;
    if(m11|m12){ if(tick8<255) tick8++;}
    else tick8=0;
    if(m13&~m14){ if(tick9<255) tick9++;}
    else tick9=0;
    if(m14){ if(tick10<255) tick10++;}
    else tick10=0;
    if(m15&~m16){ if(tick11<255) tick11++;}
    else tick11=0;
    if(m16){ if(tick12<255) tick12++;}
    else tick12=0;
    if(m17&~m18){ if(tick13<255) tick13++;}
    else tick13=0;
    if(m18){ if(tick14<255) tick14++;}
    else tick14=0;
    if(m19&~m20){ if(tick15<255) tick15++;}
    else tick15=0;
    if(m20){ if(tick16<255) tick16++;}
    else tick16=0;
    if(m21&~m22){ if(tick17<255) tick17++;}
    else tick17=0;
    if(m22){ if(tick18<255) tick18++;}
    else tick18=0;
    if(m23&~m24){ if(tick19<255) tick19++;}
    else tick19=0;
    if(m24){ if(tick20<255) tick20++;}
    else tick20=0;
    if(m25&~m26){ if(tick21<255) tick21++;}
    else tick21=0;
    if(m26){ if(tick22<255) tick22++;}
    else tick22=0;
    if(m27&~m28){ if(tick23<255) tick23++;}
    else tick23=0;
    if(m28){ if(tick24<255) tick24++;}
    else tick24=0;
    if(m29){ if(tick25<255) tick25++;}
    else tick25=0;
    if(m30){ if(tick26<255) tick26++;}
    else tick26=0;
    if(m31){ if(tick27<255) tick27++;}
    else tick27=0;
    if(m32){ if(tick28<255) tick28++;}
    else tick28=0;
    if(m33){ if(tick29<255) tick29++;}
    else tick29=0;
    if(m34){ if(tick30<255) tick30++;}
    else tick30=0;
    if(m35){ if(tick31<255) tick31++;}
    else tick31=0;
    if(m36){ if(tick32<255) tick32++;}
    else tick32=0;
    if(m37){ if(tick33<255) tick33++;}
    else tick33=0;
    if(m38){ if(tick34<255) tick34++;}
    else tick34=0;
    //output
    if(tick1>=50) SafetyAngleSensor11TimeOutError=1;
    else SafetyAngleSensor11TimeOutError=0;
    if(tick2>=50) SafetyAngleSensor12TimeOutError=1;
    else SafetyAngleSensor12TimeOutError=0;
    if(tick3>=50) SafetyAngleSensor21TimeOutError=1;
    else SafetyAngleSensor21TimeOutError=0;
    if(tick4>=50) SafetyAngleSensor22TimeOutError=1;
    else SafetyAngleSensor22TimeOutError=0;
    if(tick5>=50) SafetyDriveModule11KontaktTimeOutError=1;
    else SafetyDriveModule11KontaktTimeOutError=0;
    if(tick6>=50) SafetyDriveModule12KontaktTimeOutError=1;
    else SafetyDriveModule12KontaktTimeOutError=0;
    if(tick7>=50) SafetyDriveModule21KontaktTimeOutError=1;
    else SafetyDriveModule21KontaktTimeOutError=0;
    if(tick8>=50) SafetyDriveModule22KontaktTimeOutError=1;
    else SafetyDriveModule22KontaktTimeOutError=0;
    if(tick9>=20) SafetyWarnMotor111DrehzahlPlausiTimeOut=1;
    else SafetyWarnMotor111DrehzahlPlausiTimeOut=0;
    if(tick10>=20) SafetyErrorMotor111DrehzahlPlausiTimeOut=1;
    else SafetyErrorMotor111DrehzahlPlausiTimeOut=0;
    if(tick11>=20) SafetyWarnMotor112DrehzahlPlausiTimeOut=1;
    else SafetyWarnMotor112DrehzahlPlausiTimeOut=0;
    if(tick12>=20) SafetyErrorMotor112DrehzahlPlausiTimeOut=1;
    else SafetyErrorMotor112DrehzahlPlausiTimeOut=0;
    if(tick13>=20) SafetyWarnMotor121DrehzahlPlausiTimeOut=1;
    else SafetyWarnMotor121DrehzahlPlausiTimeOut=0;
    if(tick14>=20) SafetyErrorMotor121DrehzahlPlausiTimeOut=1;
    else SafetyErrorMotor121DrehzahlPlausiTimeOut=0;
    if(tick15>=20) SafetyWarnMotor122DrehzahlPlausiTimeOut=1;
    else SafetyWarnMotor122DrehzahlPlausiTimeOut=0;
    if(tick16>=20) SafetyErrorMotor122DrehzahlPlausiTimeOut=1;
    else SafetyErrorMotor122DrehzahlPlausiTimeOut=0;
    if(tick17>=20) SafetyWarnMotor211DrehzahlPlausiTimeOut=1;
    else SafetyWarnMotor211DrehzahlPlausiTimeOut=0;
    if(tick18>=20) SafetyErrorMotor211DrehzahlPlausiTimeOut=1;
    else SafetyErrorMotor211DrehzahlPlausiTimeOut=0;
    if(tick19>=20) SafetyWarnMotor212DrehzahlPlausiTimeOut=1;
    else SafetyWarnMotor212DrehzahlPlausiTimeOut=0;
    if(tick20>=20) SafetyErrorMotor212DrehzahlPlausiTimeOut=1;
    else SafetyErrorMotor212DrehzahlPlausiTimeOut=0;
    if(tick21>=20) SafetyWarnMotor221DrehzahlPlausiTimeOut=1;
    else SafetyWarnMotor221DrehzahlPlausiTimeOut=0;
    if(tick22>=20) SafetyErrorMotor221DrehzahlPlausiTimeOut=1;
    else SafetyErrorMotor221DrehzahlPlausiTimeOut=0;
    if(tick23>=20) SafetyWarnMotor222DrehzahlPlausiTimeOut=1;
    else SafetyWarnMotor222DrehzahlPlausiTimeOut=0;
    if(tick24>=20) SafetyErrorMotor222DrehzahlPlausiTimeOut=1;
    else SafetyErrorMotor222DrehzahlPlausiTimeOut=0;
    if(tick25>=50) SafetyErrorMotor111UmrichterOfflineTimeOut=1;
    else SafetyErrorMotor111UmrichterOfflineTimeOut=0;
    if(tick26>=50) SafetyErrorMotor112UmrichterOfflineTimeOut=1;
    else SafetyErrorMotor112UmrichterOfflineTimeOut=0;
    if(tick27>=50) SafetyErrorMotor121UmrichterOfflineTimeOut=1;
    else SafetyErrorMotor121UmrichterOfflineTimeOut=0;
    if(tick28>=50) SafetyErrorMotor122UmrichterOfflineTimeOut=1;
    else SafetyErrorMotor122UmrichterOfflineTimeOut=0;
    if(tick29>=50) SafetyErrorMotor211UmrichterOfflineTimeOut=1;
    else SafetyErrorMotor211UmrichterOfflineTimeOut=0;
    if(tick30>=50) SafetyErrorMotor212UmrichterOfflineTimeOut=1;
    else SafetyErrorMotor212UmrichterOfflineTimeOut=0;
    if(tick31>=50) SafetyErrorMotor221UmrichterOfflineTimeOut=1;
    else SafetyErrorMotor221UmrichterOfflineTimeOut=0;
    if(tick32>=50) SafetyErrorMotor222UmrichterOfflineTimeOut=1;
    else SafetyErrorMotor222UmrichterOfflineTimeOut=0;
    if(tick33>=50) SafetyErrorKamera1OfflineTimeOut=1;
    else SafetyErrorKamera1OfflineTimeOut=0;
    if(tick34>=50) SafetyErrorKamera2OfflineTimeOut=1;
    else SafetyErrorKamera2OfflineTimeOut=0;
}
