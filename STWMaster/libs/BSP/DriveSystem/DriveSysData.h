#ifndef _DATENMEM_H
#define _DATENMEM_H
#include "stwtypes.h"

#define ModeInit                             0x00
#define ModeRun                              0x01

#define KeyDriveSysStart                     0x00000001
#define KeyDriveSysReset                     0x00000002
#define KeyDriveSysStop                      0x00000004
#define KeyDriveSysEnable                    0x00000008
#define KeyDriveSysStartInverterDisable      0x00000010
#define KeyDriveSysTestMode                  0x00000020
#define KeyDriveSysTwoDimensionDrive         0x00000040
#define KeyDriveSysCrossDriveReq             0x00000080
#define KeyDriveSysLangDriveReq              0x00000100
#define KeyDriveSysCrossDriveSet             0x00000200
#define KeyDriveSysDisableReq                0x00000800
#define KeyDriveSysEnableReq                 0x00010000
#define KeyDriveSysIsStop                    0x00020000
#define KeyDriveSysZeroSet                   0x00040000
#define KeyDriveSysMotionReq                 0x00080000
#define KeyDriveSysNoBrake                   0x00100000
#define KeyDriveSysIsCrossSwitch             0x00200000
#define KeyDriveSysIsForward                 0x00400000
#define KeyDriveSysIsBackward                0x00800000


#define KeyDriveSysSteeringModeParken        0x00001000
#define KeyDriveSysSteeringModeVorderrad     0x00002000
#define KeyDriveSysSteeringModeHinterrad     0x00003000
#define KeyDriveSysSteeringModeAllrad        0x00004000
#define KeyDriveSysSteeringModeKrebsgang     0x00005000
#define KeyDriveSysSteeringModeRundgang      0x00006000

#define MotorContorlWordDriveEnable          0x0001
#define MotorContorlWordContactorEnable      0x0002
#define MotorContorlWordBrakeOn              0x0004
#define MotorContorlWordSafeStopActive       0x0040
#define MotorControlWordResetFault           0x8000

#define MaxToggleCounter                     1



//PI Controller for all 4 drive module
typedef struct{
    //Parameter in Cascade PI-Controller
    float32 ek;
    float32 yk;
    float32 yk_1;
    float32 ek_1;
    float32 Kp1;
    float32 Kp2;
    float32 Ki;
    float32 OutLimit;
}TypePIControllerDaten;

extern TypePIControllerDaten PIControllerDaten11;
extern TypePIControllerDaten PIControllerDaten12;
extern TypePIControllerDaten PIControllerDaten21;
extern TypePIControllerDaten PIControllerDaten22;

//tick for Drive System
extern uint16 DriveSysTick;

//Limit of the maximal velocity
extern float32 SpeedLimit;

//Factor of the angle sensor
extern float32 AngleFactor[4][2];

//state of the drive system
extern uint8 Mode;

//Sampling time
extern float32 Ts11;
extern float32 Ts12;
extern float32 Ts21;
extern float32 Ts22;


//Flag for aktiv the Drive Module
extern uint8 DriveModuleAktiv;

//toggle Bit
extern uint8 toggleBit[4][2];
extern uint16 toggleCounter[4];

extern float32 SetV11;
extern float32 SetV12;
extern float32 SetV21;
extern float32 SetV22;
extern float32 DriveModule11Speed;
extern float32 DriveModule12Speed;
extern float32 DriveModule21Speed;
extern float32 DriveModule22Speed;

extern float32 SetTheta11;
extern float32 SetTheta12;
extern float32 SetTheta21;
extern float32 SetTheta22;
extern float32 DriveModule11Angle;
extern float32 DriveModule12Angle;
extern float32 DriveModule21Angle;
extern float32 DriveModule22Angle;

extern float32 SpeedValue11;
extern float32 SpeedValue12;
extern float32 SpeedValue21;
extern float32 SpeedValue22;

//actual angle of the drive module
extern float32 DriveModule11ActualAngle;
extern float32 DriveModule12ActualAngle;
extern float32 DriveModule21ActualAngle;
extern float32 DriveModule22ActualAngle;

//actual Omega of the drive module
extern float32 DriveModule11OmegaM;
extern float32 DriveModule12OmegaM;
extern float32 DriveModule21OmegaM;
extern float32 DriveModule22OmegaM;

extern float32 DriveModule11Omega;
extern float32 DriveModule12Omega;
extern float32 DriveModule21Omega;
extern float32 DriveModule22Omega;


//set the Accel and decl for Speed and Omega for row
extern float32 DriveSysOmega;
extern float32 DriveSysAccel;
extern float32 DriveSysDecl;

//koefizient of the angle sensor
extern float32 AngleSensor11FactA;
extern float32 AngleSensor11FactB;
extern float32 AngleSensor12FactA;
extern float32 AngleSensor12FactB;
extern float32 AngleSensor21FactA;
extern float32 AngleSensor21FactB;
extern float32 AngleSensor22FactA;
extern float32 AngleSensor22FactB;

//============================================================
//Output Parameter
//============================================================
//control word of the motor
extern uint16 *outputMotor111ControlWord;
extern uint16 *outputMotor112ControlWord;
extern uint16 *outputMotor121ControlWord;
extern uint16 *outputMotor122ControlWord;
extern uint16 *outputMotor211ControlWord;
extern uint16 *outputMotor212ControlWord;
extern uint16 *outputMotor221ControlWord;
extern uint16 *outputMotor222ControlWord;

//set the speed of the motor
extern sint16 *outputSetMotor111Speed;
extern sint16 *outputSetMotor112Speed;
extern sint16 *outputSetMotor121Speed;
extern sint16 *outputSetMotor122Speed;
extern sint16 *outputSetMotor211Speed;
extern sint16 *outputSetMotor212Speed;
extern sint16 *outputSetMotor221Speed;
extern sint16 *outputSetMotor222Speed;

extern uint8 *outputIOPort;

//NMT message for all node byte0: 0x01 send the actual NMT; 0x00 not send | byte 1 NMT message
extern uint16 *outputInverter111NMT;
extern uint16 *outputInverter112NMT;
extern uint16 *outputInverter121NMT;
extern uint16 *outputInverter122NMT;
extern uint16 *outputInverter211NMT;
extern uint16 *outputInverter212NMT;
extern uint16 *outputInverter221NMT;
extern uint16 *outputInverter222NMT;

//actual angle of the drive module
extern sint32 *outputDriveModule11ActualAngle;
extern sint32 *outputDriveModule12ActualAngle;
extern sint32 *outputDriveModule21ActualAngle;
extern sint32 *outputDriveModule22ActualAngle;

//actual Omega of the drive module
extern sint32 *outputDriveModule11Omega;
extern sint32 *outputDriveModule12Omega;
extern sint32 *outputDriveModule21Omega;
extern sint32 *outputDriveModule22Omega;

//actual speed of the drive module
extern sint32 *outputDriveModule11ActualSpeed;
extern sint32 *outputDriveModule12ActualSpeed;
extern sint32 *outputDriveModule21ActualSpeed;
extern sint32 *outputDriveModule22ActualSpeed;

//set the torque of the motor
extern sint16 *outputSetMotor111FeedForwardTorque;
extern sint16 *outputSetMotor112FeedForwardTorque;
extern sint16 *outputSetMotor121FeedForwardTorque;
extern sint16 *outputSetMotor122FeedForwardTorque;
extern sint16 *outputSetMotor211FeedForwardTorque;
extern sint16 *outputSetMotor212FeedForwardTorque;
extern sint16 *outputSetMotor221FeedForwardTorque;
extern sint16 *outputSetMotor222FeedForwardTorque;

//============================================================
//Input Parameter
//============================================================
//control word of the drive system
extern uint32 *inputDriveSysControlWord;

//status of the motor
extern uint8 *inputMotor111StatusByte;
extern uint8 *inputMotor112StatusByte;
extern uint8 *inputMotor121StatusByte;
extern uint8 *inputMotor122StatusByte;
extern uint8 *inputMotor211StatusByte;
extern uint8 *inputMotor212StatusByte;
extern uint8 *inputMotor221StatusByte;
extern uint8 *inputMotor222StatusByte;

//set angle of the drive module
extern sint32 *inputSetDriveModule11Angle;
extern sint32 *inputSetDriveModule12Angle;
extern sint32 *inputSetDriveModule21Angle;
extern sint32 *inputSetDriveModule22Angle;

//actual speed of the motor
extern sint16 *inputMotor111ActualSpeed;
extern sint16 *inputMotor112ActualSpeed;
extern sint16 *inputMotor121ActualSpeed;
extern sint16 *inputMotor122ActualSpeed;
extern sint16 *inputMotor211ActualSpeed;
extern sint16 *inputMotor212ActualSpeed;
extern sint16 *inputMotor221ActualSpeed;
extern sint16 *inputMotor222ActualSpeed;

//actual torque of the motor
extern sint16 *inputMotor111ActualTorque;
extern sint16 *inputMotor112ActualTorque;
extern sint16 *inputMotor121ActualTorque;
extern sint16 *inputMotor122ActualTorque;
extern sint16 *inputMotor211ActualTorque;
extern sint16 *inputMotor212ActualTorque;
extern sint16 *inputMotor221ActualTorque;
extern sint16 *inputMotor222ActualTorque;

//NMT status of the inverter
extern uint8 *inputInverter111NMTStatus;
extern uint8 *inputInverter112NMTStatus;
extern uint8 *inputInverter121NMTStatus;
extern uint8 *inputInverter122NMTStatus;
extern uint8 *inputInverter211NMTStatus;
extern uint8 *inputInverter212NMTStatus;
extern uint8 *inputInverter221NMTStatus;
extern uint8 *inputInverter222NMTStatus;

//node status of the inverter
extern uint8 *inputInverter111NodeStatus;
extern uint8 *inputInverter112NodeStatus;
extern uint8 *inputInverter121NodeStatus;
extern uint8 *inputInverter122NodeStatus;
extern uint8 *inputInverter211NodeStatus;
extern uint8 *inputInverter212NodeStatus;
extern uint8 *inputInverter221NodeStatus;
extern uint8 *inputInverter222NodeStatus;

//angle sensor
extern uint16 *inputDriveModule11ActualAngle;
extern uint16 *inputDriveModule12ActualAngle;
extern uint16 *inputDriveModule21ActualAngle;
extern uint16 *inputDriveModule22ActualAngle;

//parameter of the pi controller
extern sint32 *inputDriveModule11PIControlKp1;
extern sint32 *inputDriveModule11PIControlKp2;
extern sint32 *inputDriveModule11PIControlKi;
extern sint32 *inputDriveModule12PIControlKp1;
extern sint32 *inputDriveModule12PIControlKp2;
extern sint32 *inputDriveModule12PIControlKi;
extern sint32 *inputDriveModule21PIControlKp1;
extern sint32 *inputDriveModule21PIControlKp2;
extern sint32 *inputDriveModule21PIControlKi;
extern sint32 *inputDriveModule22PIControlKp1;
extern sint32 *inputDriveModule22PIControlKp2;
extern sint32 *inputDriveModule22PIControlKi;

//factor for calculate the steering angle
extern sint32 *inputDriveModule11AngleFactA;
extern sint32 *inputDriveModule11AngleFactB;
extern sint32 *inputDriveModule12AngleFactA;
extern sint32 *inputDriveModule12AngleFactB;
extern sint32 *inputDriveModule21AngleFactA;
extern sint32 *inputDriveModule21AngleFactB;
extern sint32 *inputDriveModule22AngleFactA;
extern sint32 *inputDriveModule22AngleFactB;

//set the linear speed in X and Y direction and row speed around
//the Z axis for 2 dimensional drive
extern float32 *inputDriveSysSpeedX;
extern float32 *inputDriveSysSpeedY;
extern float32 *inputDriveSysOmegaZ;

//set the linear speed and row speed for 1 dimensional drive
extern float32 *inputDriveSysAngle;
extern float32 *inputDriveSysSpeed;

//set the Accel and decl for Speed and Omega for row
extern sint32 *inputDriveSysOmega;
extern sint32 *inputDriveSysAccel;
extern sint32 *inputDriveSysDecl;

//Parameter of the drive system
extern uint32 *inputDriveModuleMaxSpeed;

#endif // _DATENMEM_H
