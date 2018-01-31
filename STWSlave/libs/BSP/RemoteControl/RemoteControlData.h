#ifndef _REMOTECONTROLDATA_H
#define _REMOTECONTROLDATA_H
#include "stwtypes.h"

#define RemoteControlMenuTasterLeft               0x00000800
#define RemoteControlMenuTasterRight              0x00000400
#define RemoteControlMenuTasterPush               0x00001000

#define RemoteControlButtonNotAus                 0x80000000

#define KeyRCGetHubSystemNormalMode               0x00000000
#define KeyRCGetHubSystemTestMode                 0x00000001
#define KeyRCSetHubSysEnable                      0x00000004
#define KeyRCGetHubSysIsStop                      0x00000008
#define KeyRCSetHubSysHeben                       0x00000100
#define KeyRCSetHubSysSinken                      0x00000200
#define KeyRCSetHubSysAutoInit                    0x00000400

#define KeyRCGetSafetyIsError                     0x00000001
#define KeyRCSetSafetySysLaserscanner1Deaktiv     0x00000002
#define KeyRCSetSafetySysLaserscanner2Deaktiv     0x00001000
#define KeyRCGetSafetySysLaserscanner1Warn        0x00000008
#define KeyRCGetSafetySysLaserscanner1Stop        0x00000010
#define KeyRCGetSafetySysLaserscanner2Warn        0x00000020
#define KeyRCGetSafetySysLaserscanner2Stop        0x00000040
#define KeyRCGetSafetySysLaserscanner1Slow        0x00000400
#define KeyRCGetSafetySysLaserscanner2Slow        0x00000800
#define KeyRCGetSafetyHubSysStop                  0x00000100
#define KeyRCGetSafetySystemSperrn                0x00008000

#define KeyRCReqWordMeunTasterPush                0x0010
#define KeyRCReqWordMeunTasterLeft                0x0020
#define KeyRCReqWordMeunTasterRight               0x0040

#define KeyRCDisplayStatusCrossDrive              0x01
#define KeyRCDisplayStatusZeroSet                 0x02
#define KeyRCDisplayStatusPark                    0x04
#define KeyRCDisplayStatusPageUpdate              0x08
#define KeyRCDisplayStatusIsError                 0x10
#define KeyRCDisplayStatusIsSteeringMotion        0x20
#define KeyRCDisplayStatusNotAus                  0x40
#define KeyRCDisplayStatusLadung                  0x80

#define KeyRCDisplayStatusExtCrossIsSwitch        0x01
#define KeyRCDisplayStatusExtRCRelaisAus          0x02
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

#define KeyRCDisplayAutoDriveStateNoLane          0x00    //None
#define KeyRCDisplayAutoDriveStateOnLane          0x01    //Lane
#define KeyRCDisplayAutoDriveStateOnTagNoUsed     0x02
#define KeyRCDisplayAutoDriveStateOnTagUsed       0x03
#define KeyRCDisplayAutoDriveStateInPos           0x04    //In Pos.
#define KeyRCDisplayAutoDriveStateLiftUp          0x05
#define KeyRCDisplayAutoDriveStateLiftTop         0x06
#define KeyRCDisplayAutoDriveStateLiftDown        0x07
#define KeyRCDisplayAutoDriveStateLiftButtom      0x08


//============================================================
//Normal Parameter
//============================================================
//Actual time for the RC System
extern uint32 RCActualTime;

//Request Key of the RC System
extern uint16 RCReqWord;

//actual page for display
extern uint16 akt_page;

//============================================================
//Input Parameter
//============================================================
//control word from the safety system
extern uint32 *inputRCGetSafetyControlWord;
extern uint32 *inputRCGetSafetyMasterControlWord;
extern uint32 *inputRCGetHubSystemControlWord;

//input value of the remote controller
extern uint8 *inputRemoteControlToggle;
extern uint32 *inputRemoteControlDigitalIn;

//get actual height of the Hub System
extern uint32 *inputRCGetHubWerk11Height;
extern uint32 *inputRCGetHubWerk12Height;
extern uint32 *inputRCGetHubWerk21Height;
extern uint32 *inputRCGetHubWerk22Height;

//get actual Pressure of the Hub System
extern sint32 *inputRCGetHubWerk11Pressure;
extern sint32 *inputRCGetHubWerk12Pressure;
extern sint32 *inputRCGetHubWerk21Pressure;
extern sint32 *inputRCGetHubWerk22Pressure;

//Angle of drive system to slave
extern sint8 *inputRCFromMasterDriveSysAngle11;
extern sint8 *inputRCFromMasterDriveSysAngle12;
extern sint8 *inputRCFromMasterDriveSysAngle21;
extern sint8 *inputRCFromMasterDriveSysAngle22;

//status of the MES to slave
extern uint8 *inputRCFromMasterStatusMES;
extern uint8 *inputRCFromMasterStatusExtMES;
extern uint8 *inputRCFromMasterPageState;
extern uint8 *inputRCFromMasterStatusAutoDrive;
extern uint8 *inputRCFromMasterSteeringMode;
extern sint8 *inputRCFromMasterSpeedMES;
extern uint8 *inputRCFromMasterAutoDriveState;

//value of the Error Camera
extern sint8 *inputRCFromMasterY1Value;
extern sint8 *inputRCFromMasterY2Value;
extern uint16 *inputRCFromMasterXValue;

//get Number of Error from the Safety System
extern uint8 *inputRCGetErrorNum;

//get Number of Error from the Safety System of SlaveCPU
extern uint8 *inputRCGetMasterCPUErrorNum;

//get Error code from the Safety System
extern uint32 *inputRCGetErrorCode[8];

//get Error code from the Safety System of SlaveCPU
extern uint32 *inputRCGetErrorCodeMasterCPU[8];

//============================================================
//Output Parameter
//============================================================
extern uint32 *outputRemoteControlString0;
extern uint32 *outputRemoteControlString1;
extern uint32 *outputRemoteControlString2;
extern uint32 *outputRemoteControlString3;

#endif
