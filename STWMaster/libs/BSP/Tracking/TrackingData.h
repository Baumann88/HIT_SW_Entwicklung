#ifndef _TRACKINGDATA_H
#define _TRACKINGDATA_H
#include "stwtypes.h"

#define KeyAutoDriveEnable                       0x00000001
#define KeyAutoDriveInStopZone                   0x00000002
#define KeyAutoDriveForwardDrive                 0x00000004
#define KeyAutoDriveBackwardDrive                0x00000008
#define KeyAutoDriveK1BandFind                   0x00000010
#define KeyAutoDriveK2BandFind                   0x00000020
#define KeyAutoDrivePosReady                     0x00000040
#define KeyAutoDriveQuitReq                      0x00000080
#define KeyAutoDriveHupeReq                      0x00000100
#define KeyAutoDriveInPos                        0x00000200
#define KeyAutoDriveOnLane                       0x00000400
#define KeyAutoDriveCurveDrive                   0x00000800


#define KeyAutoDriveKameraDetektB1               0x02
#define KeyAutoDriveKameraDetektB2               0x04
#define KeyAutoDriveKameraDetektB3               0x06
#define KeyAutoDriveKameraDetektTag              0x80

#define KeyAutoDriveSDOControlWordEnable         0x00000001
#define KeyCameraControlWordMuster               0x00000001

#define KeyAutoGetSafetySysLaserscanner1Warn     0x00000008
#define KeyAutoGetSafetySysLaserscanner2Warn     0x00000020
#define KeyAutoGetSafetySysLaserscanner1Slow     0x00000400
#define KeyAutoGetSafetySysLaserscanner2Slow     0x00000800
#define KeyAutoGetSafetySysLaserscanner1Stop     0x00000010
#define KeyAutoGetSafetySysLaserscanner2Stop     0x00000040
#define KeyAutoGetSafetySysLaserscanner1Deaktiv  0x00000002
#define KeyAutoGetSafetySysLaserscanner2Deaktiv  0x00001000

#define AutoDrivePinControlWordTestMode          0x01000000
#define AutoDrivePinControlWordIsUsed            0x02000000

#define AutoDriveStateNoLane                     0x00
#define AutoDriveStateOnLane                     0x01
#define AutoDriveStateOnTagNoUsed                0x02
#define AutoDriveStateOnTagUsed                  0x03
#define AutoDriveStateInPos                      0x04
#define AutoDriveStateLiftUp                     0x05
#define AutoDriveStateLiftTop                    0x06
#define AutoDriveStateLiftDown                   0x07
#define AutoDriveStateLiftButtom                 0x08


#define ValueAutoDriveTick                       100
#define NumOfPosBand                             10

//Controller for lane track
typedef struct{
    float32 Vc;
    float32 e_n;
    float32 e_theta;
    float32 kp1;
    float32 kp2;
    float32 ki1;
    float32 ki2;
}TypeAutoDriveControllerDaten;

extern TypeAutoDriveControllerDaten AutoDriveControllerDaten;

extern sint16 AutoDriveStopPos[NumOfPosBand];
//extern sint16 AutoDriveAktivBand;

//Sampling time of the auto drive
extern float32 AutoDriveTs;

//state of the auto drive
extern uint8 AutoDriveState;

//Input Parameter of the auto drive
extern uint32 *inputAutoDriveControlWord;

//Input from safety block
extern uint32 *inputAutoDriveGetSafetyControlWord;

extern sint32 *inputAutoDriveReferenzSpeed;

extern sint32 *inputAutoDriveControlKp1;
extern sint32 *inputAutoDriveControlKp2;
extern sint32 *inputAutoDriveControlKi1;
extern sint32 *inputAutoDriveControlKi2;

extern uint8 *inputAutoDriveYp11;
extern uint8 *inputAutoDriveYp12;
extern uint8 *inputAutoDriveYp13;
extern uint8 *inputAutoDriveYp14;
extern uint8 *inputAutoDriveYp21;
extern uint8 *inputAutoDriveYp22;
extern uint8 *inputAutoDriveYp23;
extern uint8 *inputAutoDriveYp24;

extern uint8 *inputAutoDriveXp11;
extern uint8 *inputAutoDriveXp12;
extern uint8 *inputAutoDriveXp13;
extern uint8 *inputAutoDriveXp14;
extern uint8 *inputAutoDriveXp21;
extern uint8 *inputAutoDriveXp22;
extern uint8 *inputAutoDriveXp23;
extern uint8 *inputAutoDriveXp24;

extern uint8 *inputAutoDriveAG11;
extern uint8 *inputAutoDriveAG12;
extern uint8 *inputAutoDriveAG21;
extern uint8 *inputAutoDriveAG22;

extern uint8 *inputAutoDriveST11;
extern uint8 *inputAutoDriveST12;
extern uint8 *inputAutoDriveST21;
extern uint8 *inputAutoDriveST22;

extern uint8 *inputKamera1NodeStatus;
extern uint8 *inputKamera2NodeStatus;

//state of the auto drive
extern uint8 *outputAutoDriveState;

//number of the akt. band
extern sint8 *outputNumOfBand;

//Output Parameter of the auto drive
extern sint16 *outputAutoDriveY1Value;
extern sint16 *outputAutoDriveY2Value;

extern sint16 *outputAutoDriveX1Value;
extern sint16 *outputAutoDriveX2Value;

extern sint16 *outputAutoDriveAG1Value;
extern sint16 *outputAutoDriveAG2Value;

//set speed of the drive module for 2 dimensional steering
extern float32 *outputAutoDriveSetSpeedX;
extern float32 *outputAutoDriveSetSpeedY;
extern float32 *outputAutoDriveSetOmegaZ;

//Output to slave
extern sint8 *outputAutoDriveToSlaveY1Value;
extern sint8 *outputAutoDriveToSlaveY2Value;

extern uint16 *outputAutoDriveToSlaveXValue;

extern uint8 *outputAutoDriveToSlaveState;

//SDO Control word
extern uint32 *outputAutoDriveInitSDOControlWord;
extern uint32 *outputAutoDriveInitSDOContent;

extern uint32 *outputAutoDriveCameraControlWord;

//NMT of Camera
extern uint16 *outputKamera1NMT;
extern uint16 *outputKamera2NMT;

//Hupe for finish
extern uint32 *outputIOPortFinishHupe;

#endif
