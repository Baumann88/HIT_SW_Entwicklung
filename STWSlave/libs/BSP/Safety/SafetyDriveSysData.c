#include <SafetyDriveSysData.h>

//====================================================================
//intene parameter
//====================================================================
uint8 SafetyAngleSensor11TimeOutWarn;
uint8 SafetyAngleSensor11TimeOutError;
uint8 SafetyAngleSensor12TimeOutWarn;
uint8 SafetyAngleSensor12TimeOutError;
uint8 SafetyAngleSensor21TimeOutWarn;
uint8 SafetyAngleSensor21TimeOutError;
uint8 SafetyAngleSensor22TimeOutWarn;
uint8 SafetyAngleSensor22TimeOutError;
boolean SafetyErrorAngleSensor11Warn;
boolean SafetyErrorAngleSensor11Error;
boolean SafetyErrorAngleSensor12Warn;
boolean SafetyErrorAngleSensor12Error;
boolean SafetyErrorAngleSensor21Warn;
boolean SafetyErrorAngleSensor21Error;
boolean SafetyErrorAngleSensor22Warn;
boolean SafetyErrorAngleSensor22Error;
boolean SafetyErrorDriveModule11AngleOut;
boolean SafetyErrorDriveModule12AngleOut;
boolean SafetyErrorDriveModule21AngleOut;
boolean SafetyErrorDriveModule22AngleOut;

//====================================================================
//input parameter
//====================================================================
sint32 *inputSafetyDriveModule11ActualAngle;
sint32 *inputSafetyDriveModule12ActualAngle;
sint32 *inputSafetyDriveModule21ActualAngle;
sint32 *inputSafetyDriveModule22ActualAngle;
sint32 *inputSafetyDriveModule11SetAngle;
sint32 *inputSafetyDriveModule12SetAngle;
sint32 *inputSafetyDriveModule21SetAngle;
sint32 *inputSafetyDriveModule22SetAngle;
sint16 *inputSafetyMotor111SetSpeed;
sint16 *inputSafetyMotor112SetSpeed;
sint16 *inputSafetyMotor121SetSpeed;
sint16 *inputSafetyMotor122SetSpeed;
sint16 *inputSafetyMotor211SetSpeed;
sint16 *inputSafetyMotor212SetSpeed;
sint16 *inputSafetyMotor221SetSpeed;
sint16 *inputSafetyMotor222SetSpeed;
sint16 *inputSafetyMotor111ActualTorque;
sint16 *inputSafetyMotor112ActualTorque;
sint16 *inputSafetyMotor121ActualTorque;
sint16 *inputSafetyMotor122ActualTorque;
sint16 *inputSafetyMotor211ActualTorque;
sint16 *inputSafetyMotor212ActualTorque;
sint16 *inputSafetyMotor221ActualTorque;
sint16 *inputSafetyMotor222ActualTorque;
sint16 *inputSafetyMotor111ActualSpeed;
sint16 *inputSafetyMotor112ActualSpeed;
sint16 *inputSafetyMotor121ActualSpeed;
sint16 *inputSafetyMotor122ActualSpeed;
sint16 *inputSafetyMotor211ActualSpeed;
sint16 *inputSafetyMotor212ActualSpeed;
sint16 *inputSafetyMotor221ActualSpeed;
sint16 *inputSafetyMotor222ActualSpeed;
uint8 *inputSafetyMotor111StatusByte;
uint8 *inputSafetyMotor112StatusByte;
uint8 *inputSafetyMotor121StatusByte;
uint8 *inputSafetyMotor122StatusByte;
uint8 *inputSafetyMotor211StatusByte;
uint8 *inputSafetyMotor212StatusByte;
uint8 *inputSafetyMotor221StatusByte;
uint8 *inputSafetyMotor222StatusByte;
uint16 *inputSafetyMotor111ErrorCode;
uint16 *inputSafetyMotor112ErrorCode;
uint16 *inputSafetyMotor121ErrorCode;
uint16 *inputSafetyMotor122ErrorCode;
uint16 *inputSafetyMotor211ErrorCode;
uint16 *inputSafetyMotor212ErrorCode;
uint16 *inputSafetyMotor221ErrorCode;
uint16 *inputSafetyMotor222ErrorCode;
uint16 *inputSafetyIOVersorgungBremsenAus;
uint32 *inputSafetyGetDriveSystemStatusWord;

//====================================================================
//out parameter
//====================================================================
uint32 *outputSafetySetDriveSystemWord;
