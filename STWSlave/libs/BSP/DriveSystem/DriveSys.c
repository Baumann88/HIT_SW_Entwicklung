#include "DriveInterface.h"
#include "DriveSys.h"
#include "DriveSysData.h"

//=================================================================================================
/*!
    Function: generate the Interface
    output: None
*/
//=================================================================================================
void InitInterfaceDriveSys(void){
    //generate the interface of drive system
    inputDriveSysControlWord=BindODMem(DriveModuleStartIndex,SubindexDriveSysControlWord,TypeU32,0); *inputDriveSysControlWord=0;

    inputDriveSysSpeedX=BindODMem(DriveModuleStartIndex,SubindexDriveSysSetSpeedX,TypeF32,0); *inputDriveSysSpeedX=0.0;
    inputDriveSysSpeedY=BindODMem(DriveModuleStartIndex,SubindexDriveSysSetSpeedY,TypeF32,0); *inputDriveSysSpeedY=0.0;
    inputDriveSysOmegaZ=BindODMem(DriveModuleStartIndex,SubindexDriveSysSetOmegaZ,TypeF32,0); *inputDriveSysOmegaZ=0.0;
    inputDriveSysSpeed=BindODMem(DriveModuleStartIndex,SubindexDriveSysSetSpeed,TypeF32,0); *inputDriveSysSpeed=0.0;
    inputDriveSysAngle=BindODMem(DriveModuleStartIndex,SubindexDriveSysSetAngle,TypeF32,0); *inputDriveSysAngle=0.0;

    inputDriveSysOmega=BindODMem(DriveModuleStartIndex,SubindexDriveSysOmega,TypeS32,0);
    inputDriveSysAccel=BindODMem(DriveModuleStartIndex,SubindexDriveSysAccel,TypeS32,0);
    inputDriveSysDecl=BindODMem(DriveModuleStartIndex,SubindexDriveSysDecl,TypeS32,0);

    inputDriveModuleMaxSpeed=BindODMem(DriveModuleStartIndex,SubindexMaximalSpeed,TypeU32,0);

    inputDriveModule11AngleFactA=BindODMem(DriveModuleStartIndex,SubindexAngleSensor11FactA,TypeS32,0);
    inputDriveModule11AngleFactB=BindODMem(DriveModuleStartIndex,SubindexAngleSensor11FactB,TypeS32,0);
    inputDriveModule12AngleFactA=BindODMem(DriveModuleStartIndex,SubindexAngleSensor12FactA,TypeS32,0);
    inputDriveModule12AngleFactB=BindODMem(DriveModuleStartIndex,SubindexAngleSensor12FactB,TypeS32,0);
    inputDriveModule21AngleFactA=BindODMem(DriveModuleStartIndex,SubindexAngleSensor21FactA,TypeS32,0);
    inputDriveModule21AngleFactB=BindODMem(DriveModuleStartIndex,SubindexAngleSensor21FactB,TypeS32,0);
    inputDriveModule22AngleFactA=BindODMem(DriveModuleStartIndex,SubindexAngleSensor22FactA,TypeS32,0);
    inputDriveModule22AngleFactB=BindODMem(DriveModuleStartIndex,SubindexAngleSensor22FactB,TypeS32,0);

    inputDriveModule11PIControlKp1=BindODMem(DriveModuleStartIndex,SubindexDriveModule11Kp1,TypeS32,0);
    inputDriveModule11PIControlKp2=BindODMem(DriveModuleStartIndex,SubindexDriveModule11Kp1,TypeS32,0);
    inputDriveModule11PIControlKi=BindODMem(DriveModuleStartIndex,SubindexDriveModule11Ki,TypeS32,0);
    inputDriveModule12PIControlKp1=BindODMem(DriveModuleStartIndex,SubindexDriveModule12Kp1,TypeS32,0);
    inputDriveModule12PIControlKp2=BindODMem(DriveModuleStartIndex,SubindexDriveModule12Kp2,TypeS32,0);
    inputDriveModule12PIControlKi=BindODMem(DriveModuleStartIndex,SubindexDriveModule12Ki,TypeS32,0);
    inputDriveModule21PIControlKp1=BindODMem(DriveModuleStartIndex,SubindexDriveModule21Kp1,TypeS32,0);
    inputDriveModule21PIControlKp2=BindODMem(DriveModuleStartIndex,SubindexDriveModule21Kp2,TypeS32,0);
    inputDriveModule21PIControlKi=BindODMem(DriveModuleStartIndex,SubindexDriveModule21Ki,TypeS32,0);
    inputDriveModule22PIControlKp1=BindODMem(DriveModuleStartIndex,SubindexDriveModule22Kp1,TypeS32,0);
    inputDriveModule22PIControlKp2=BindODMem(DriveModuleStartIndex,SubindexDriveModule22Kp2,TypeS32,0);
    inputDriveModule22PIControlKi=BindODMem(DriveModuleStartIndex,SubindexDriveModule22Ki,TypeS32,0);

    //generate the interface of inverter
    inputDriveModule11ActualAngle=BindODMem(IOPortStartIndex,SubindexInput01,TypeU16,0); *inputDriveModule11ActualAngle=0;
    inputDriveModule12ActualAngle=BindODMem(IOPortStartIndex,SubindexInput02,TypeU16,0); *inputDriveModule12ActualAngle=0;
    inputDriveModule21ActualAngle=BindODMem(IOPortStartIndex,SubindexInput04,TypeU16,0); *inputDriveModule21ActualAngle=0;
    inputDriveModule22ActualAngle=BindODMem(IOPortStartIndex,SubindexInput03,TypeU16,0); *inputDriveModule22ActualAngle=0;

    inputSetDriveModule11Angle=BindODMem(DriveModuleStartIndex,SubindexSetDriveModule11Angle,TypeS32,0); *inputSetDriveModule11Angle=0;
    inputSetDriveModule12Angle=BindODMem(DriveModuleStartIndex,SubindexSetDriveModule12Angle,TypeS32,0); *inputSetDriveModule12Angle=0;
    inputSetDriveModule21Angle=BindODMem(DriveModuleStartIndex,SubindexSetDriveModule21Angle,TypeS32,0); *inputSetDriveModule21Angle=0;
    inputSetDriveModule22Angle=BindODMem(DriveModuleStartIndex,SubindexSetDriveModule22Angle,TypeS32,0); *inputSetDriveModule22Angle=0;

    inputMotor111StatusByte=BindODMem(InverterStartIndex,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputMotor111StatusByte=0x00;
    inputMotor112StatusByte=BindODMem(InverterStartIndex+0x0001,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputMotor112StatusByte=0x00;
    inputMotor121StatusByte=BindODMem(InverterStartIndex+0x0002,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputMotor121StatusByte=0x00;
    inputMotor122StatusByte=BindODMem(InverterStartIndex+0x0003,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputMotor122StatusByte=0x00;
    inputMotor211StatusByte=BindODMem(InverterStartIndex+0x0004,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputMotor211StatusByte=0x00;
    inputMotor212StatusByte=BindODMem(InverterStartIndex+0x0005,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputMotor212StatusByte=0x00;
    inputMotor221StatusByte=BindODMem(InverterStartIndex+0x0006,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputMotor221StatusByte=0x00;
    inputMotor222StatusByte=BindODMem(InverterStartIndex+0x0007,SubindexInverterTPDO1LowDWord,TypeU8,0); *inputMotor222StatusByte=0x00;

    inputMotor111ActualSpeed=BindODMem(InverterStartIndex,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputMotor111ActualSpeed=0;
    inputMotor112ActualSpeed=BindODMem(InverterStartIndex+0x0001,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputMotor112ActualSpeed=0;
    inputMotor121ActualSpeed=BindODMem(InverterStartIndex+0x0002,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputMotor121ActualSpeed=0;
    inputMotor122ActualSpeed=BindODMem(InverterStartIndex+0x0003,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputMotor122ActualSpeed=0;
    inputMotor211ActualSpeed=BindODMem(InverterStartIndex+0x0004,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputMotor211ActualSpeed=0;
    inputMotor212ActualSpeed=BindODMem(InverterStartIndex+0x0005,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputMotor212ActualSpeed=0;
    inputMotor221ActualSpeed=BindODMem(InverterStartIndex+0x0006,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputMotor221ActualSpeed=0;
    inputMotor222ActualSpeed=BindODMem(InverterStartIndex+0x0007,SubindexInverterTPDO1LowDWord,TypeS16,1); *inputMotor222ActualSpeed=0;

    inputInverter111NMTStatus=BindODMem(InverterStartIndex,SubindexInverterNodeStatus,TypeU8,0); *inputInverter111NMTStatus=0x00;
    inputInverter112NMTStatus=BindODMem(InverterStartIndex+0x0001,SubindexInverterNodeStatus,TypeU8,0); *inputInverter112NMTStatus=0x00;
    inputInverter121NMTStatus=BindODMem(InverterStartIndex+0x0002,SubindexInverterNodeStatus,TypeU8,0); *inputInverter121NMTStatus=0x00;
    inputInverter122NMTStatus=BindODMem(InverterStartIndex+0x0003,SubindexInverterNodeStatus,TypeU8,0); *inputInverter122NMTStatus=0x00;
    inputInverter211NMTStatus=BindODMem(InverterStartIndex+0x0004,SubindexInverterNodeStatus,TypeU8,0); *inputInverter211NMTStatus=0x00;
    inputInverter212NMTStatus=BindODMem(InverterStartIndex+0x0005,SubindexInverterNodeStatus,TypeU8,0); *inputInverter212NMTStatus=0x00;
    inputInverter221NMTStatus=BindODMem(InverterStartIndex+0x0006,SubindexInverterNodeStatus,TypeU8,0); *inputInverter221NMTStatus=0x00;
    inputInverter222NMTStatus=BindODMem(InverterStartIndex+0x0007,SubindexInverterNodeStatus,TypeU8,0); *inputInverter222NMTStatus=0x00;

    inputInverter111NodeStatus=BindODMem(InverterStartIndex,SubindexInverterNodeStatus,TypeU8,1); *inputInverter111NodeStatus=0x00;
    inputInverter112NodeStatus=BindODMem(InverterStartIndex+0x0001,SubindexInverterNodeStatus,TypeU8,1); *inputInverter112NodeStatus=0x00;
    inputInverter121NodeStatus=BindODMem(InverterStartIndex+0x0002,SubindexInverterNodeStatus,TypeU8,1); *inputInverter121NodeStatus=0x00;
    inputInverter122NodeStatus=BindODMem(InverterStartIndex+0x0003,SubindexInverterNodeStatus,TypeU8,1); *inputInverter122NodeStatus=0x00;
    inputInverter211NodeStatus=BindODMem(InverterStartIndex+0x0004,SubindexInverterNodeStatus,TypeU8,1); *inputInverter211NodeStatus=0x00;
    inputInverter212NodeStatus=BindODMem(InverterStartIndex+0x0005,SubindexInverterNodeStatus,TypeU8,1); *inputInverter212NodeStatus=0x00;
    inputInverter221NodeStatus=BindODMem(InverterStartIndex+0x0006,SubindexInverterNodeStatus,TypeU8,1); *inputInverter221NodeStatus=0x00;
    inputInverter222NodeStatus=BindODMem(InverterStartIndex+0x0007,SubindexInverterNodeStatus,TypeU8,1); *inputInverter222NodeStatus=0x00;

    outputMotor111ControlWord=BindODMem(InverterStartIndex,SubindexInverterRPDO1LowDWord,TypeU16,0); *outputMotor111ControlWord=0x0000;
    outputMotor112ControlWord=BindODMem(InverterStartIndex+0x0001,SubindexInverterRPDO1LowDWord,TypeU16,0); *outputMotor112ControlWord=0x0000;
    outputMotor121ControlWord=BindODMem(InverterStartIndex+0x0002,SubindexInverterRPDO1LowDWord,TypeU16,0); *outputMotor121ControlWord=0x0000;
    outputMotor122ControlWord=BindODMem(InverterStartIndex+0x0003,SubindexInverterRPDO1LowDWord,TypeU16,0); *outputMotor122ControlWord=0x0000;
    outputMotor211ControlWord=BindODMem(InverterStartIndex+0x0004,SubindexInverterRPDO1LowDWord,TypeU16,0); *outputMotor211ControlWord=0x0000;
    outputMotor212ControlWord=BindODMem(InverterStartIndex+0x0005,SubindexInverterRPDO1LowDWord,TypeU16,0); *outputMotor212ControlWord=0x0000;
    outputMotor221ControlWord=BindODMem(InverterStartIndex+0x0006,SubindexInverterRPDO1LowDWord,TypeU16,0); *outputMotor221ControlWord=0x0000;
    outputMotor222ControlWord=BindODMem(InverterStartIndex+0x0007,SubindexInverterRPDO1LowDWord,TypeU16,0); *outputMotor222ControlWord=0x0000;

    outputSetMotor111Speed=BindODMem(InverterStartIndex,SubindexInverterRPDO1LowDWord,TypeS16,1); *outputSetMotor111Speed=0;
    outputSetMotor112Speed=BindODMem(InverterStartIndex+0x0001,SubindexInverterRPDO1LowDWord,TypeS16,1); *outputSetMotor112Speed=0;
    outputSetMotor121Speed=BindODMem(InverterStartIndex+0x0002,SubindexInverterRPDO1LowDWord,TypeS16,1); *outputSetMotor121Speed=0;
    outputSetMotor122Speed=BindODMem(InverterStartIndex+0x0003,SubindexInverterRPDO1LowDWord,TypeS16,1); *outputSetMotor122Speed=0;
    outputSetMotor211Speed=BindODMem(InverterStartIndex+0x0004,SubindexInverterRPDO1LowDWord,TypeS16,1); *outputSetMotor211Speed=0;
    outputSetMotor212Speed=BindODMem(InverterStartIndex+0x0005,SubindexInverterRPDO1LowDWord,TypeS16,1); *outputSetMotor212Speed=0;
    outputSetMotor221Speed=BindODMem(InverterStartIndex+0x0006,SubindexInverterRPDO1LowDWord,TypeS16,1); *outputSetMotor221Speed=0;
    outputSetMotor222Speed=BindODMem(InverterStartIndex+0x0007,SubindexInverterRPDO1LowDWord,TypeS16,1); *outputSetMotor222Speed=0;

    outputInverter111NMT=BindODMem(InverterStartIndex,SubindexInverterNMT,TypeU16,0); *outputInverter111NMT=0x0000;
    outputInverter112NMT=BindODMem(InverterStartIndex+0x0001,SubindexInverterNMT,TypeU16,0); *outputInverter112NMT=0x0000;
    outputInverter121NMT=BindODMem(InverterStartIndex+0x0002,SubindexInverterNMT,TypeU16,0); *outputInverter121NMT=0x0000;
    outputInverter122NMT=BindODMem(InverterStartIndex+0x0003,SubindexInverterNMT,TypeU16,0); *outputInverter122NMT=0x0000;
    outputInverter211NMT=BindODMem(InverterStartIndex+0x0004,SubindexInverterNMT,TypeU16,0); *outputInverter211NMT=0x0000;
    outputInverter212NMT=BindODMem(InverterStartIndex+0x0005,SubindexInverterNMT,TypeU16,0); *outputInverter212NMT=0x0000;
    outputInverter221NMT=BindODMem(InverterStartIndex+0x0006,SubindexInverterNMT,TypeU16,0); *outputInverter221NMT=0x0000;
    outputInverter222NMT=BindODMem(InverterStartIndex+0x0007,SubindexInverterNMT,TypeU16,0); *outputInverter222NMT=0x0000;

    outputDriveModule11ActualAngle=BindODMem(DriveModuleStartIndex,SubindexDriveModule11ActualAngle,TypeS32,0); *outputDriveModule11ActualAngle=0;
    outputDriveModule12ActualAngle=BindODMem(DriveModuleStartIndex,SubindexDriveModule12ActualAngle,TypeS32,0); *outputDriveModule12ActualAngle=0;
    outputDriveModule21ActualAngle=BindODMem(DriveModuleStartIndex,SubindexDriveModule21ActualAngle,TypeS32,0); *outputDriveModule21ActualAngle=0;
    outputDriveModule22ActualAngle=BindODMem(DriveModuleStartIndex,SubindexDriveModule22ActualAngle,TypeS32,0); *outputDriveModule22ActualAngle=0;

    outputDriveModule11ActualSpeed=BindODMem(DriveModuleStartIndex,SubindexDriveModule11ActualSpeed,TypeS32,0); *outputDriveModule11ActualSpeed=0;
    outputDriveModule12ActualSpeed=BindODMem(DriveModuleStartIndex,SubindexDriveModule12ActualSpeed,TypeS32,0); *outputDriveModule12ActualSpeed=0;
    outputDriveModule21ActualSpeed=BindODMem(DriveModuleStartIndex,SubindexDriveModule21ActualSpeed,TypeS32,0); *outputDriveModule21ActualSpeed=0;
    outputDriveModule22ActualSpeed=BindODMem(DriveModuleStartIndex,SubindexDriveModule22ActualSpeed,TypeS32,0); *outputDriveModule22ActualSpeed=0;

    outputDriveModule11Omega=BindODMem(DriveModuleStartIndex,SubindexDriveModule11ActualOmega,TypeS32,0); *outputDriveModule11Omega=0;
    outputDriveModule12Omega=BindODMem(DriveModuleStartIndex,SubindexDriveModule12ActualOmega,TypeS32,0); *outputDriveModule12Omega=0;
    outputDriveModule21Omega=BindODMem(DriveModuleStartIndex,SubindexDriveModule21ActualOmega,TypeS32,0); *outputDriveModule21Omega=0;
    outputDriveModule22Omega=BindODMem(DriveModuleStartIndex,SubindexDriveModule22ActualOmega,TypeS32,0); *outputDriveModule22Omega=0;
}

//=================================================================================================
/*!
    Function: Initial of the Drive system
    output: None
*/
//=================================================================================================
void InitDriveSys(void){
    InitInterfaceDriveSys();
    InitInverter(); //Setup all Inverter
    x_os_install_task(PrioDriveSysManage, 500, 10, Task_DriveSysManage, 128);
    x_os_install_task(PrioDrvieSysControl, 0, 0, Task_DriveSysControl, 256);
}

//=================================================================================================
/*!
    Function: Awake the Task from sleep state, the time interval of awake is activated by toggle bit
    input:
    output: None
*/
//=================================================================================================
void TaskDriveSysAwake(void){
    static uint32 timeStamp;
    uint16 SetTaskEventFlag=0;

    toggleBit[0][0]=*inputMotor111StatusByte&0x80;
    if(toggleBit[0][0]!=toggleBit[0][1]) toggleCounter[0]++;
    if(toggleCounter[0]>=MaxToggleCounter){
        DriveModuleAktiv|=0x01;
        toggleCounter[0]=0;
        SetTaskEventFlag=1;
    }
    toggleBit[1][0]=*inputMotor121StatusByte&0x80;
    if(toggleBit[1][0]!=toggleBit[1][1]) toggleCounter[1]++;
    if(toggleCounter[1]>=MaxToggleCounter){
        DriveModuleAktiv|=0x02;
        toggleCounter[1]=0;
        SetTaskEventFlag=1;
    }
    toggleBit[2][0]=*inputMotor211StatusByte&0x80;
    if(toggleBit[2][0]!=toggleBit[2][1]) toggleCounter[2]++;
    if(toggleCounter[2]>=MaxToggleCounter){
        DriveModuleAktiv|=0x04;
        toggleCounter[2]=0;
        SetTaskEventFlag=1;
    }
    toggleBit[3][0]=*inputMotor221StatusByte&0x80;
    if(toggleBit[3][0]!=toggleBit[3][1]) toggleCounter[3]++;
    if(toggleCounter[3]>=MaxToggleCounter){
        DriveModuleAktiv|=0x08;
        toggleCounter[3]=0;
        SetTaskEventFlag=1;
    }

    toggleBit[0][1]=toggleBit[0][0];
    toggleBit[1][1]=toggleBit[1][0];
    toggleBit[2][1]=toggleBit[2][0];
    toggleBit[3][1]=toggleBit[3][0];

    if(SetTaskEventFlag==1) x_os_set_events(Event_DriveSysControl);

    /*if(x_sys_get_time_ms()-timeStamp>12){
        timeStamp=x_sys_get_time_ms();
        x_os_set_events(Event_DriveSysControl);
    }*/
}






