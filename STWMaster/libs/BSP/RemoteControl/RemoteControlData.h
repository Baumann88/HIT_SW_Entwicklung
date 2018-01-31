#ifndef _REMOTECONTROLDATA_H
#define _REMOTECONTROLDATA_H
#include "stwtypes.h"

#define RemoteControlSchutzRealis                 0x00000100

#define RemoteControlButtonReset                  0x00000008
#define RemoteControlButtonZeroSet                0x00000020
#define RemoteControlButtonStart                  0x00000002
#define RemoteControlButtonHupe                   0x00000010
#define RemoteControlButtonAutoBetrieb            0x00000040
#define RemoteControlButtonNotAus                 0x80000000

#define RemoteControlSwitchTotmann                0x00000080
#define RemoteControlSwitchJoystickMove           0x00000004
#define RemoteControlSwitchIndDrive               0x00002000
#define RemoteControlSwitchNoIndDrive             0x00004000
#define RemoteControlSwitchCrossDrive             0x00008000
#define RemoteControlSwitchLongDrive              0x00010000
#define RemoteControlSwitchErrorQuit              0x00040000
#define RemoteControlSwitchDriveSteeringMode      0x00080000
#define RemoteControlSwitchHubSysAktiv            0x00100000
#define RemoteControlSwitchLaserscannerDeaktiv    0x00200000

#define RemoteControlMenuTasterLeft               0x00000800
#define RemoteControlMenuTasterRight              0x00000400
#define RemoteControlMenuTasterPush               0x00001000

#define KeyRCSetDriveSysStart                     0x00000001
#define KeyRCSetDriveSysReset                     0x00000002
#define KeyRCSetDriveSysTestMode                  0x00000020
#define KeyRCSetDriveSysTwoDimensionDrive         0x00000040
#define KeyRCSetDriveSysCrossDriveReq             0x00000080
#define KeyRCGetDriveSysCrossDriveSet             0x00000200
#define KeyRCGetDriveSysIsCrossSwitch             0x00200000
#define KeyRCSetDriveSysMotionReq                 0x00000400
#define KeyRCSetDriveSysLangDriveReq              0x00000100
#define KeyRCSetDriveSysDisableReq                0x00000800
#define KeyRCSetDriveSysEnableReq                 0x00010000
#define KeyRCSetDriveSysZeroSet                   0x00040000
#define KeyRCGetDriveSysIsForward                 0x00400000
#define KeyRCGetDriveSysIsBackward                0x00800000
#define KeyRCSetDriveSysNoBrake                   0x00100000
#define KeyRCGetDriveSysIsStop                    0x00020000
#define KeyRCGetDriveSysIsEnable                  0x00000008


#define KeyRCGetHubSystemNormalMode               0x00000000
#define KeyRCGetHubSystemTestMode                 0x00000001
#define KeyRCSetHubSysEnable                      0x00000004
#define KeyRCSetHubSysHeben                       0x00000100
#define KeyRCSetHubSysSinken                      0x00000200
#define KeyRCSetHubSysAutoInit                    0x00000400

#define KeyRCGetHubSysFromSlaveIsStop             0x01
#define KeyRCGetHubSysFromSlaveOnlySinken         0x02
#define KeyRCGetHubSysFromSlaveNoAdd              0x04

#define KeyRCSetAutoDriveEnable                   0x00000001
#define KeyRCGetAutoDriveInStopZone               0x00000002
#define KeyRCSetAutoDriveForwardDrive             0x00000004
#define KeyRCSetAutoDriveBackwardDrive            0x00000008
#define KeyRCGetAutoDriveK1BandFind               0x00000010
#define KeyRCGetAutoDriveK2BandFind               0x00000020
#define KeyRCSetAutoDriveAutoQuitReq              0x00000080
#define KeyRCGetAutoDriveHupeReq                  0x00000100
#define KeyRCGetAutoDriveInPos                    0x00000200
#define KeyRCGetAutoDriveOnLane                   0x00000400

#define KeyRCGetSafetyIsError                     0x00000001
#define KeyRCSetSafetySysLaserscanner1Deaktiv     0x00000002
#define KeyRCSetSafetySysLaserscanner2Deaktiv     0x00001000
#define KeyRCSetSafetySysRCNoMotion               0x00000004
#define KeyRCGetSafetySysLaserscanner1Warn        0x00000008
#define KeyRCGetSafetySysLaserscanner1Stop        0x00000010
#define KeyRCGetSafetySysLaserscanner2Warn        0x00000020
#define KeyRCGetSafetySysLaserscanner2Stop        0x00000040
#define KeyRCGetSafetySysLaserscanner1Slow        0x00000400
#define KeyRCGetSafetySysLaserscanner2Slow        0x00000800
#define KeyRCGetSafetyDriveSysStop                0x00000080
#define KeyRCGetSafetyHubSysStop                  0x00000100
#define KeyRCGetSafetyAutoDriveStop               0x00000200
#define KeyRCGetSafetyNotAusStatus                0x00002000
#define KeyRCGetSafetyLadungStatus                0x00004000

#define KeyRCSetDriveSysSteeringModeParken        0x00001000
#define KeyRCSetDriveSysSteeringModeVorderrad     0x00002000
#define KeyRCSetDriveSysSteeringModeHinterrad     0x00003000
#define KeyRCSetDriveSysSteeringModeAllrad        0x00004000
#define KeyRCSetDriveSysSteeringModeKrebsgang     0x00005000
#define KeyRCSetDriveSysSteeringModeRundgang      0x00006000
#define KeyRCSetDriveSysSteeringModeAutoReady     0x00007000

#define KeyRCReqWordStart                         0x0001
#define KeyRCReqWordReset                         0x0002
#define KeyRCReqWordAutoHand                      0x0008
#define KeyRCReqWordMeunTasterPush                0x0010
#define KeyRCReqWordMeunTasterLeft                0x0020
#define KeyRCReqWordMeunTasterRight               0x0040
#define KeyRCReqWordCrossDrive                    0x0080
#define KeyRCReqWordIndDrive                      0x0100
#define KeyRCReqWordDriveSteeringMode             0x0200
#define KeyRCReqWordHubSysAktiv                   0x0400
#define KeyRCReqWordHupeReq                       0x0800
#define KeyRCReqWordLSDeaktiv                     0x1000


#define KeyRCDisplayStatusCrossDrive              0x01
#define KeyRCDisplayStatusZeroSet                 0x02
#define KeyRCDisplayStatusPark                    0x04
#define KeyRCDisplayStatusPageUpdate              0x08
#define KeyRCDisplayStatusIsError                 0x10
#define KeyRCDisplayStatusIsSteeringMotion        0x20
#define KeyRCDisplayStatusNotAus                  0x40
#define KeyRCDisplayStatusLadung                  0x80

#define KeyRCDisplayStatusExtCrossIsSwitch        0x01
#define KeyRCDisplayStatusExtLSDeaktiv            0x04

#define KeyRCDisplayAutoStatusDriveForward        0x01
#define KeyRCDisplayAutoStatusDriveBackward       0x02
#define KeyRCDisplayAutoStatusK1BandFind          0x04
#define KeyRCDisplayAutoStatusK2BandFind          0x08
#define KeyRCDisplayAutoStatusAutoInit            0x10
#define KeyRCDisplayAutoStatusAutoStopZone        0x20

#define KeyRCDisplayPageStateInit                 0x00
#define KeyRCDisplayPageStateReady                0x01
#define KeyRCDisplayPageStateRun                  0x02
#define KeyRCDisplayPageStateHub                  0x03
#define KeyRCDisplayPageStateAuto                 0x04
#define KeyRCDisplayPageStateNotFall              0x05

#define KeyRCDisplaySteeringModePark              0x00
#define KeyRCDisplaySteeringModeVorderrad         0x01
#define KeyRCDisplaySteeringModeHinterrad         0x02
#define KeyRCDisplaySteeringModeKrebsgang         0x03
#define KeyRCDisplaySteeringModeRundgang          0x04
#define KeyRCDisplaySteeringModeAllrad            0x05


#define Parken                                    0x00400000
#define AllradLenkung                             0x02000000
#define VorderradLenkung                          0x00800000
#define HinterradLenkung                          0x01000000
#define Krebsgang                                 0x04000000
#define Rundgang                                  0x08000000

#define MaxSpeed                                  (45.0/60.0) //in m/s
#define MaxSpeedSlow                              (10.0/60.0) //in m/s
#define MaxSpeedWarnFeld                          (4.0/60.0) //in m/s

#define MaxDriveAngleLangNoAllrad                 (60.0/180.0*pi)
#define MaxDriveAngleLangAllrad                   (45.0/180.0*pi)
#define MaxDriveAngleLangKrebsgang                (80.0/180.0*pi)
#define MaxDriveAngleCrossNoAllrad                (25.0/180.0*pi)
#define MaxDriveAngleCrossAllrad                  (15.0/180.0*pi)
#define MaxDriveAngleCrossKrebsgang               (80.0/180.0*pi)

#define RCStateInit                               0
#define RCStateReady                              1
#define RCStateRun                                2
#define RCStateHub                                3
#define RCStateAutoDrive                          4
#define RCStateNotFall                            5

//============================================================
//Normal Parameter
//============================================================
//state of the RC System
extern uint8 State;

//Actual time for the RC System
extern uint32 RCActualTime;

//Request Key of the RC System
extern uint16 RCReqWord;

//actual page for display
extern uint16 akt_page;

//============================================================
//Input Parameter
//============================================================
//control word from the slave safety system
extern uint32 *inputRCGetSlaveSafetyControlWord;

//input value of the remote controller
extern uint8 *inputRemoteControlXVar;
extern uint8 *inputRemoteControlY1Var;
extern uint8 *inputRemoteControlY2Var;
extern uint8 *inputRemoteControlZVar;
extern uint8 *inputRemoteControlSpeedPoti;
extern uint8 *inputRemoteControlToggle;
extern uint32 *inputRemoteControlDigitalIn;

//Joystick parameter
extern sint32 *inputRCJoystickXFactA;
extern sint32 *inputRCJoystickXFactB;
extern sint32 *inputRCJoystickXFactC;
extern sint32 *inputRCJoystickXFactD;

//input for Auto/Hand mode
extern uint16 *inputIOPortHand;
extern uint16 *inputIOPortAutomatik;

//get actual angle of the drive module
extern sint32 *inputRCGetDriveModule11Angle;
extern sint32 *inputRCGetDriveModule12Angle;
extern sint32 *inputRCGetDriveModule21Angle;
extern sint32 *inputRCGetDriveModule22Angle;

//get actual y value of the auto drive
extern sint16 *inputRCGetAutoDriveY1Value;
extern sint16 *inputRCGetAutoDriveY2Value;

extern sint16 *inputRCGetAutoDriveXValue;

//actual height of hub system
extern uint8 *inputHubsystemHeight;

//actual status of hub system
extern uint8 *inputHubsystemStatus;

//============================================================
//Output Parameter
//============================================================
//control word to the drive system
extern uint32 *outputRCSetDriveSysControlWord;

//control word to the hub system
extern uint32 *outputRCSetHubSysControlWord;

//control word to the safety system
extern uint32 *outputRCSetSafetyControlWord;

//control word to the auto drive system
extern uint32 *outputRCSetAutoDriveControlWord;

//set speed of the drive module for 1 dimensional steering
extern float32 *outputRCSetDriveSysSpeed;
extern float32 *outputRCSetDriveSysAngle;

//output value of the remote controller
extern uint32 *outputIOPortHupe;
extern uint32 *outputIOPortLampe11;
extern uint32 *outputIOPortLampe12;
extern uint32 *outputIOPortLampe21;
extern uint32 *outputIOPortLampe22;

//Angle of drive system to slave
extern sint8 *outputRCToSlaveDriveSysAngle11;
extern sint8 *outputRCToSlaveDriveSysAngle12;
extern sint8 *outputRCToSlaveDriveSysAngle21;
extern sint8 *outputRCToSlaveDriveSysAngle22;

//status of the MES to slave
extern uint8 *outputRCToSlaveStatusMES;
extern uint8 *outputRCToSlaveStatusExtMES;
extern uint8 *outputRCToSlavePageState;
extern uint8 *outputRCToSlaveStatusAuto;
extern uint8 *outputRCToSlaveSteeringMode;

extern uint16 *outputRemoteControlNMT;

#endif
