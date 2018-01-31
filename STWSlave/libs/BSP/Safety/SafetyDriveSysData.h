#ifndef _SAFETYDRIVESYSDATA_H
#define _SAFETYDRIVESYSDATA_H
#include <stwtypes.h>

//====================================================================
//define Constant
//====================================================================
#define DriveModule11MaxAngle                (170)
#define DriveModule11MinAngle                (-80)
#define DriveModule12MaxAngle                (80)
#define DriveModule12MinAngle                (-170)
#define DriveModule21MaxAngle                (-170)
#define DriveModule21MinAngle                (80)
#define DriveModule22MaxAngle                (170)
#define DriveModule22MinAngle                (-80)
#define KeySafetySetRCDriveSysStop           (0x00000080)
#define KeySafteyGetDriveSysZeroSet          (0x00040000)
#define AngleSensorErrorWarning              (1.5)
#define AngleSensorErrorFault                (3.5)

//====================================================================
//intene parameter
//====================================================================
extern uint8 SafetyAngleSensor11TimeOutWarn;
extern uint8 SafetyAngleSensor11TimeOutError;
extern uint8 SafetyAngleSensor12TimeOutWarn;
extern uint8 SafetyAngleSensor12TimeOutError;
extern uint8 SafetyAngleSensor21TimeOutWarn;
extern uint8 SafetyAngleSensor21TimeOutError;
extern uint8 SafetyAngleSensor22TimeOutWarn;
extern uint8 SafetyAngleSensor22TimeOutError;
extern boolean SafetyErrorAngleSensor11Warn;
extern boolean SafetyErrorAngleSensor11Error;
extern boolean SafetyErrorAngleSensor12Warn;
extern boolean SafetyErrorAngleSensor12Error;
extern boolean SafetyErrorAngleSensor21Warn;
extern boolean SafetyErrorAngleSensor21Error;
extern boolean SafetyErrorAngleSensor22Warn;
extern boolean SafetyErrorAngleSensor22Error;
extern boolean SafetyErrorDriveModule11AngleOut;
extern boolean SafetyErrorDriveModule12AngleOut;
extern boolean SafetyErrorDriveModule21AngleOut;
extern boolean SafetyErrorDriveModule22AngleOut;

//====================================================================
//input parameter
//====================================================================
extern sint32 *inputSafetyDriveModule11ActualAngle;
extern sint32 *inputSafetyDriveModule12ActualAngle;
extern sint32 *inputSafetyDriveModule21ActualAngle;
extern sint32 *inputSafetyDriveModule22ActualAngle;
extern sint32 *inputSafetyDriveModule11SetAngle;
extern sint32 *inputSafetyDriveModule12SetAngle;
extern sint32 *inputSafetyDriveModule21SetAngle;
extern sint32 *inputSafetyDriveModule22SetAngle;
extern sint16 *inputSafetyMotor111SetSpeed;
extern sint16 *inputSafetyMotor112SetSpeed;
extern sint16 *inputSafetyMotor121SetSpeed;
extern sint16 *inputSafetyMotor122SetSpeed;
extern sint16 *inputSafetyMotor211SetSpeed;
extern sint16 *inputSafetyMotor212SetSpeed;
extern sint16 *inputSafetyMotor221SetSpeed;
extern sint16 *inputSafetyMotor222SetSpeed;
extern sint16 *inputSafetyMotor111ActualTorque;
extern sint16 *inputSafetyMotor112ActualTorque;
extern sint16 *inputSafetyMotor121ActualTorque;
extern sint16 *inputSafetyMotor122ActualTorque;
extern sint16 *inputSafetyMotor211ActualTorque;
extern sint16 *inputSafetyMotor212ActualTorque;
extern sint16 *inputSafetyMotor221ActualTorque;
extern sint16 *inputSafetyMotor222ActualTorque;
extern sint16 *inputSafetyMotor111ActualSpeed;
extern sint16 *inputSafetyMotor112ActualSpeed;
extern sint16 *inputSafetyMotor121ActualSpeed;
extern sint16 *inputSafetyMotor122ActualSpeed;
extern sint16 *inputSafetyMotor211ActualSpeed;
extern sint16 *inputSafetyMotor212ActualSpeed;
extern sint16 *inputSafetyMotor221ActualSpeed;
extern sint16 *inputSafetyMotor222ActualSpeed;
extern uint8 *inputSafetyMotor111StatusByte;
extern uint8 *inputSafetyMotor112StatusByte;
extern uint8 *inputSafetyMotor121StatusByte;
extern uint8 *inputSafetyMotor122StatusByte;
extern uint8 *inputSafetyMotor211StatusByte;
extern uint8 *inputSafetyMotor212StatusByte;
extern uint8 *inputSafetyMotor221StatusByte;
extern uint8 *inputSafetyMotor222StatusByte;
extern uint16 *inputSafetyMotor111ErrorCode;
extern uint16 *inputSafetyMotor112ErrorCode;
extern uint16 *inputSafetyMotor121ErrorCode;
extern uint16 *inputSafetyMotor122ErrorCode;
extern uint16 *inputSafetyMotor211ErrorCode;
extern uint16 *inputSafetyMotor212ErrorCode;
extern uint16 *inputSafetyMotor221ErrorCode;
extern uint16 *inputSafetyMotor222ErrorCode;
extern uint16 *inputSafetyIOVersorgungBremsenAus;
extern uint32 *inputSafetyGetDriveSystemStatusWord;

//====================================================================
//out parameter
//====================================================================
extern uint32 *outputSafetySetDriveSystemWord;
#endif