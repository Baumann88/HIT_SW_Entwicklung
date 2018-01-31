#ifndef _SAFETYDRIVESYSDATA_H
#define _SAFETYDRIVESYSDATA_H
#include <stwtypes.h>

//====================================================================
//define Constant
//====================================================================
#define DriveModule11MaxAngle                (110)
#define DriveModule11MinAngle                (-110)
#define DriveModule12MaxAngle                (110)
#define DriveModule12MinAngle                (-110)
#define DriveModule21MaxAngle                (110)
#define DriveModule21MinAngle                (-110)
#define DriveModule22MaxAngle                (110)
#define DriveModule22MinAngle                (-110)
#define KeySafteyGetDriveSysZeroSet          (0x00040000)
#define AngleSensorErrorFault                (3.5)
#define DriveModuleLostKontakeMinSpeed       (30)
#define DriveModuleLostKontakeMinTorque      (40)
#define MotorPlausiWarnDrehzahl              (100)
#define MotorPlausiFehlerDrehzahl            (300)
#define KeySafetyMotorUmrichterFault         (0x02)
#define KeySafetyNodeDisconneted             (0x01)

//====================================================================
//intene parameter
//====================================================================
extern uint8 SafetyAngleSensor11TimeOutError;
extern uint8 SafetyAngleSensor12TimeOutError;
extern uint8 SafetyAngleSensor21TimeOutError;
extern uint8 SafetyAngleSensor22TimeOutError;
extern uint8 SafetyDriveModule11KontaktTimeOutError;
extern uint8 SafetyDriveModule12KontaktTimeOutError;
extern uint8 SafetyDriveModule21KontaktTimeOutError;
extern uint8 SafetyDriveModule22KontaktTimeOutError;
extern boolean SafetyErrorAngleSensor11Error;
extern boolean SafetyErrorAngleSensor12Error;
extern boolean SafetyErrorAngleSensor21Error;
extern boolean SafetyErrorAngleSensor22Error;
extern boolean SafetyErrorDriveModule11AngleOut;
extern boolean SafetyErrorDriveModule12AngleOut;
extern boolean SafetyErrorDriveModule21AngleOut;
extern boolean SafetyErrorDriveModule22AngleOut;
extern boolean SafetyErrorDriveModule11KontaktLose;
extern boolean SafetyErrorDriveModule12KontaktLose;
extern boolean SafetyErrorDriveModule21KontaktLose;
extern boolean SafetyErrorDriveModule22KontaktLose;
extern boolean SafetyWarnMotor111DrehzahlPlausiTimeOut;
extern boolean SafetyWarnMotor112DrehzahlPlausiTimeOut;
extern boolean SafetyWarnMotor121DrehzahlPlausiTimeOut;
extern boolean SafetyWarnMotor122DrehzahlPlausiTimeOut;
extern boolean SafetyWarnMotor211DrehzahlPlausiTimeOut;
extern boolean SafetyWarnMotor212DrehzahlPlausiTimeOut;
extern boolean SafetyWarnMotor221DrehzahlPlausiTimeOut;
extern boolean SafetyWarnMotor222DrehzahlPlausiTimeOut;
extern boolean SafetyErrorMotor111DrehzahlPlausiTimeOut;
extern boolean SafetyErrorMotor112DrehzahlPlausiTimeOut;
extern boolean SafetyErrorMotor121DrehzahlPlausiTimeOut;
extern boolean SafetyErrorMotor122DrehzahlPlausiTimeOut;
extern boolean SafetyErrorMotor211DrehzahlPlausiTimeOut;
extern boolean SafetyErrorMotor212DrehzahlPlausiTimeOut;
extern boolean SafetyErrorMotor221DrehzahlPlausiTimeOut;
extern boolean SafetyErrorMotor222DrehzahlPlausiTimeOut;
extern boolean SafetyWarnMotor111DrehzahlPlausi;
extern boolean SafetyWarnMotor112DrehzahlPlausi;
extern boolean SafetyWarnMotor121DrehzahlPlausi;
extern boolean SafetyWarnMotor122DrehzahlPlausi;
extern boolean SafetyWarnMotor211DrehzahlPlausi;
extern boolean SafetyWarnMotor212DrehzahlPlausi;
extern boolean SafetyWarnMotor221DrehzahlPlausi;
extern boolean SafetyWarnMotor222DrehzahlPlausi;
extern boolean SafetyErrorMotor111DrehzahlPlausi;
extern boolean SafetyErrorMotor112DrehzahlPlausi;
extern boolean SafetyErrorMotor121DrehzahlPlausi;
extern boolean SafetyErrorMotor122DrehzahlPlausi;
extern boolean SafetyErrorMotor211DrehzahlPlausi;
extern boolean SafetyErrorMotor212DrehzahlPlausi;
extern boolean SafetyErrorMotor221DrehzahlPlausi;
extern boolean SafetyErrorMotor222DrehzahlPlausi;
extern boolean SafetyErrorMotor111Umrichter;
extern boolean SafetyErrorMotor112Umrichter;
extern boolean SafetyErrorMotor121Umrichter;
extern boolean SafetyErrorMotor122Umrichter;
extern boolean SafetyErrorMotor211Umrichter;
extern boolean SafetyErrorMotor212Umrichter;
extern boolean SafetyErrorMotor221Umrichter;
extern boolean SafetyErrorMotor222Umrichter;
extern boolean SafetyErrorMotor111UmrichterOfflineTimeOut;
extern boolean SafetyErrorMotor112UmrichterOfflineTimeOut;
extern boolean SafetyErrorMotor121UmrichterOfflineTimeOut;
extern boolean SafetyErrorMotor122UmrichterOfflineTimeOut;
extern boolean SafetyErrorMotor211UmrichterOfflineTimeOut;
extern boolean SafetyErrorMotor212UmrichterOfflineTimeOut;
extern boolean SafetyErrorMotor221UmrichterOfflineTimeOut;
extern boolean SafetyErrorMotor222UmrichterOfflineTimeOut;
extern boolean SafetyErrorMotor111UmrichterOffline;
extern boolean SafetyErrorMotor112UmrichterOffline;
extern boolean SafetyErrorMotor121UmrichterOffline;
extern boolean SafetyErrorMotor122UmrichterOffline;
extern boolean SafetyErrorMotor211UmrichterOffline;
extern boolean SafetyErrorMotor212UmrichterOffline;
extern boolean SafetyErrorMotor221UmrichterOffline;
extern boolean SafetyErrorMotor222UmrichterOffline;
extern boolean SafetyErrorMotorUmrichterOffline;
extern boolean SafetyErrorKamera1OfflineTimeOut;
extern boolean SafetyErrorKamera2OfflineTimeOut;
extern boolean SafetyErrorKamera1Offline;
extern boolean SafetyErrorKamera2Offline;
extern boolean SafetyErrorKameraOffline;

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
extern uint8 *inputSafetyInverter111NodeStatus;
extern uint8 *inputSafetyInverter112NodeStatus;
extern uint8 *inputSafetyInverter121NodeStatus;
extern uint8 *inputSafetyInverter122NodeStatus;
extern uint8 *inputSafetyInverter211NodeStatus;
extern uint8 *inputSafetyInverter212NodeStatus;
extern uint8 *inputSafetyInverter221NodeStatus;
extern uint8 *inputSafetyInverter222NodeStatus;
extern uint8 *inputSafetyKamera1NodeStatus;
extern uint8 *inputSafetyKamera2NodeStatus;

//====================================================================
//out parameter
//====================================================================
extern uint32 *outputSafetySetDriveSystemWord;
#endif