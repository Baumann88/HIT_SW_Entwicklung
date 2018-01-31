#include "DriveSysData.h"

//============================================================
//Intern Parameter
//============================================================
//PI Controller for all 4 drive module
TypePIControllerDaten PIControllerDaten11={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
TypePIControllerDaten PIControllerDaten12={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
TypePIControllerDaten PIControllerDaten21={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
TypePIControllerDaten PIControllerDaten22={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};

//tick for Drive System
uint16 DriveSysTick;


//Limit of the maximal velocity
float32 SpeedLimit;

//Factor of the angle sensor
float32 AngleFactor[4][2];

//state of the drive system
uint8 Mode;

//Sampling time
float32 Ts11;
float32 Ts12;
float32 Ts21;
float32 Ts22;

//Flag for aktiv the Drive Module
uint8 DriveModuleAktiv;

//toggle Bit
uint8 toggleBit[4][2];
uint16 toggleCounter[4];

//set speed of the drive module
float32 SetV11;
float32 SetV12;
float32 SetV21;
float32 SetV22;
float32 DriveModule11Speed;
float32 DriveModule12Speed;
float32 DriveModule21Speed;
float32 DriveModule22Speed;


//set angle of the drive module
float32 SetTheta11;
float32 SetTheta12;
float32 SetTheta21;
float32 SetTheta22;
float32 DriveModule11Angle;
float32 DriveModule12Angle;
float32 DriveModule21Angle;
float32 DriveModule22Angle;

float32 SpeedValue11;
float32 SpeedValue12;
float32 SpeedValue21;
float32 SpeedValue22;

//actual angle of the drive module
float32 DriveModule11ActualAngle;
float32 DriveModule12ActualAngle;
float32 DriveModule21ActualAngle;
float32 DriveModule22ActualAngle;

//actual Omega of the drive module in curve
float32 DriveModule11OmegaM;
float32 DriveModule12OmegaM;
float32 DriveModule21OmegaM;
float32 DriveModule22OmegaM;

//actual Omega of the drive module
float32 DriveModule11Omega;
float32 DriveModule12Omega;
float32 DriveModule21Omega;
float32 DriveModule22Omega;

//set the Accel and decl for Speed and Omega for row
float32 DriveSysOmega;
float32 DriveSysAccel;
float32 DriveSysDecl;

//koefizient of the angle sensor
float32 AngleSensor11FactA;
float32 AngleSensor11FactB;
float32 AngleSensor12FactA;
float32 AngleSensor12FactB;
float32 AngleSensor21FactA;
float32 AngleSensor21FactB;
float32 AngleSensor22FactA;
float32 AngleSensor22FactB;

//============================================================
//Output Parameter
//============================================================
//control word of the motor
uint16 *outputMotor111ControlWord;
uint16 *outputMotor112ControlWord;
uint16 *outputMotor121ControlWord;
uint16 *outputMotor122ControlWord;
uint16 *outputMotor211ControlWord;
uint16 *outputMotor212ControlWord;
uint16 *outputMotor221ControlWord;
uint16 *outputMotor222ControlWord;

//set the speed of the motor
sint16 *outputSetMotor111Speed;
sint16 *outputSetMotor112Speed;
sint16 *outputSetMotor121Speed;
sint16 *outputSetMotor122Speed;
sint16 *outputSetMotor211Speed;
sint16 *outputSetMotor212Speed;
sint16 *outputSetMotor221Speed;
sint16 *outputSetMotor222Speed;

//set the torque of the motor
sint16 *outputSetMotor111FeedForwardTorque;
sint16 *outputSetMotor112FeedForwardTorque;
sint16 *outputSetMotor121FeedForwardTorque;
sint16 *outputSetMotor122FeedForwardTorque;
sint16 *outputSetMotor211FeedForwardTorque;
sint16 *outputSetMotor212FeedForwardTorque;
sint16 *outputSetMotor221FeedForwardTorque;
sint16 *outputSetMotor222FeedForwardTorque;

//NMT message for all node byte0: 0x01 send the actual NMT; 0x00 not send | byte 1 NMT message
uint16 *outputInverter111NMT;
uint16 *outputInverter112NMT;
uint16 *outputInverter121NMT;
uint16 *outputInverter122NMT;
uint16 *outputInverter211NMT;
uint16 *outputInverter212NMT;
uint16 *outputInverter221NMT;
uint16 *outputInverter222NMT;

//actual angle of the drive module
sint32 *outputDriveModule11ActualAngle;
sint32 *outputDriveModule12ActualAngle;
sint32 *outputDriveModule21ActualAngle;
sint32 *outputDriveModule22ActualAngle;

//actual Omega of the drive module
sint32 *outputDriveModule11Omega;
sint32 *outputDriveModule12Omega;
sint32 *outputDriveModule21Omega;
sint32 *outputDriveModule22Omega;

//actual speed of the drive module
sint32 *outputDriveModule11ActualSpeed;
sint32 *outputDriveModule12ActualSpeed;
sint32 *outputDriveModule21ActualSpeed;
sint32 *outputDriveModule22ActualSpeed;

//============================================================
//Input Parameter
//============================================================
//control word of the drive system
uint32 *inputDriveSysControlWord;

//status of the motor
uint8 *inputMotor111StatusByte;
uint8 *inputMotor112StatusByte;
uint8 *inputMotor121StatusByte;
uint8 *inputMotor122StatusByte;
uint8 *inputMotor211StatusByte;
uint8 *inputMotor212StatusByte;
uint8 *inputMotor221StatusByte;
uint8 *inputMotor222StatusByte;

//set angle of the drive module
sint32 *inputSetDriveModule11Angle;
sint32 *inputSetDriveModule12Angle;
sint32 *inputSetDriveModule21Angle;
sint32 *inputSetDriveModule22Angle;

//actual speed of the motor
sint16 *inputMotor111ActualSpeed;
sint16 *inputMotor112ActualSpeed;
sint16 *inputMotor121ActualSpeed;
sint16 *inputMotor122ActualSpeed;
sint16 *inputMotor211ActualSpeed;
sint16 *inputMotor212ActualSpeed;
sint16 *inputMotor221ActualSpeed;
sint16 *inputMotor222ActualSpeed;

//actual torque of the motor
sint16 *inputMotor111ActualTorque;
sint16 *inputMotor112ActualTorque;
sint16 *inputMotor121ActualTorque;
sint16 *inputMotor122ActualTorque;
sint16 *inputMotor211ActualTorque;
sint16 *inputMotor212ActualTorque;
sint16 *inputMotor221ActualTorque;
sint16 *inputMotor222ActualTorque;

//NMT status of the inverter
uint8 *inputInverter111NMTStatus;
uint8 *inputInverter112NMTStatus;
uint8 *inputInverter121NMTStatus;
uint8 *inputInverter122NMTStatus;
uint8 *inputInverter211NMTStatus;
uint8 *inputInverter212NMTStatus;
uint8 *inputInverter221NMTStatus;
uint8 *inputInverter222NMTStatus;

//node status of the inverter
uint8 *inputInverter111NodeStatus;
uint8 *inputInverter112NodeStatus;
uint8 *inputInverter121NodeStatus;
uint8 *inputInverter122NodeStatus;
uint8 *inputInverter211NodeStatus;
uint8 *inputInverter212NodeStatus;
uint8 *inputInverter221NodeStatus;
uint8 *inputInverter222NodeStatus;

//angle sensor
uint16 *inputDriveModule11ActualAngle;
uint16 *inputDriveModule12ActualAngle;
uint16 *inputDriveModule21ActualAngle;
uint16 *inputDriveModule22ActualAngle;

//parameter of the pi controller
sint32 *inputDriveModule11PIControlKp1;
sint32 *inputDriveModule11PIControlKp2;
sint32 *inputDriveModule11PIControlKi;
sint32 *inputDriveModule12PIControlKp1;
sint32 *inputDriveModule12PIControlKp2;
sint32 *inputDriveModule12PIControlKi;
sint32 *inputDriveModule21PIControlKp1;
sint32 *inputDriveModule21PIControlKp2;
sint32 *inputDriveModule21PIControlKi;
sint32 *inputDriveModule22PIControlKp1;
sint32 *inputDriveModule22PIControlKp2;
sint32 *inputDriveModule22PIControlKi;

//factor for calculate the steering angle
sint32 *inputDriveModule11AngleFactA;
sint32 *inputDriveModule11AngleFactB;
sint32 *inputDriveModule12AngleFactA;
sint32 *inputDriveModule12AngleFactB;
sint32 *inputDriveModule21AngleFactA;
sint32 *inputDriveModule21AngleFactB;
sint32 *inputDriveModule22AngleFactA;
sint32 *inputDriveModule22AngleFactB;


//set the linear speed in X and Y direction and row speed around
//the Z axis for 2 dimensional drive
float32 *inputDriveSysSpeedX;
float32 *inputDriveSysSpeedY;
float32 *inputDriveSysOmegaZ;

//set the linear speed and row speed for 1 dimensional drive
float32 *inputDriveSysAngle;
float32 *inputDriveSysSpeed;

//set the accel and decl for Speed and Omega for row
sint32 *inputDriveSysOmega;
sint32 *inputDriveSysAccel;
sint32 *inputDriveSysDecl;

//Parameter of the drive system
uint32 *inputDriveModuleMaxSpeed;

