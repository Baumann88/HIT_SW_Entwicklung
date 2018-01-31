#ifndef _ODCONTENT_H
#define _ODCONTENT_H
/*====================================================================
OD Definition
====================================================================*/
//====================================================================
//*1 Device Parameter
#define DevParaStartIndex                   0x1000
#define NrEntryDevPara                      15

//*1.1 Parameter
#define SubindexHwtype                      0x00
#define SubindexSerNr                       0x01
#define SubindexControlWord                 0x02
#define SubindexNodeParam                   0x03 //Byte0: NodeID | Byte1-2: Time of the Heartbeat in ms | Byte3: Buadrate code
#define SubindexConfigSync12                0x04 //Byte 0 En/Disable Sync1 | Byte 1: Time Window Sync1 | Byte 2 En/Disable Sync2 | Byte 3: Time Window Sync2
#define SubindexConfigSync34                0x05 //Byte 0 En/Disable Sync3 | Byte 1: Time Window Sync3 | Byte 2 En/Disable Sync4 | Byte 3: Time Window Sync4
#define SubindexCPUTemperatur               0x06
#define SubindexCPUVoltageUb1               0x07
#define SubindexCPUCurrentUb1               0x08
#define SubindexCPUVoltageExt               0x09
#define SubindexCPUVoltageUC1               0x0a
#define SubindexSysStatus                   0x0b //Bit 0: Ignition On/Off | Byte 1: CAN Bus Status
#define SubindexSysCycleTime                0x0c
#define SubindexSysSDOControlWord           0x0d //Byte 0: Bit 0 Lock /Bit 1: read/write / Bit 2-3: BusChannel / Bit 4: send Byte/Bit 5-7: Send ID | Byte 1-2: Index | Byte 3: Subindex
#define SubindexSysSDOContent               0x0e

//====================================================================
//*2 Drive System
#define DriveModuleStartIndex               0x6000
#define NrEntryDriveModule                  46

//*2.0 control word of the drive system
#define SubindexDriveSysControlWord         0x00

//*2.1 PI Controller Parameter
#define SubindexDriveModule11Kp1            0x01
#define SubindexDriveModule11Kp2            0x02
#define SubindexDriveModule11Ki             0x03
#define SubindexDriveModule12Kp1            0x04
#define SubindexDriveModule12Kp2            0x05
#define SubindexDriveModule12Ki             0x06
#define SubindexDriveModule21Kp1            0x07
#define SubindexDriveModule21Kp2            0x08
#define SubindexDriveModule21Ki             0x09
#define SubindexDriveModule22Kp1            0x0a
#define SubindexDriveModule22Kp2            0x0b
#define SubindexDriveModule22Ki             0x0c

//*2.2 Angle Sensor
#define SubindexDriveModule11ActualAngle    0x0d
#define SubindexDriveModule12ActualAngle    0x0e
#define SubindexDriveModule21ActualAngle    0x0f
#define SubindexDriveModule22ActualAngle    0x10
#define SubindexAngleSensor11FactA          0x11
#define SubindexAngleSensor11FactB          0x12
#define SubindexAngleSensor12FactA          0x13
#define SubindexAngleSensor12FactB          0x14
#define SubindexAngleSensor21FactA          0x15
#define SubindexAngleSensor21FactB          0x16
#define SubindexAngleSensor22FactA          0x17
#define SubindexAngleSensor22FactB          0x18

//*2.3 Drive System Parameter
#define SubindexMaximalSpeed                0x19 //maximal speed of drive module
#define SubindexDriveSysOmega               0x1a
#define SubindexDriveSysAccel               0x1b
#define SubindexDriveSysDecl                0x1c
#define SubindexDriveSysSetSpeedX           0x1d
#define SubindexDriveSysSetSpeedY           0x1e
#define SubindexDriveSysSetOmegaZ           0x1f
#define SubindexDriveSysSetSpeed            0x20
#define SubindexDriveSysSetAngle            0x21

//*2.4 Drive Module
#define SubindexSetDriveModule11Angle       0x22
#define SubindexSetDriveModule12Angle       0x23
#define SubindexSetDriveModule21Angle       0x24
#define SubindexSetDriveModule22Angle       0x25
#define SubindexDriveModule11ActualSpeed    0x26
#define SubindexDriveModule12ActualSpeed    0x27
#define SubindexDriveModule21ActualSpeed    0x28
#define SubindexDriveModule22ActualSpeed    0x29
#define SubindexDriveModule11ActualOmega    0x2a
#define SubindexDriveModule12ActualOmega    0x2b
#define SubindexDriveModule21ActualOmega    0x2c
#define SubindexDriveModule22ActualOmega    0x2d



//====================================================================
//*3 Motor Inverter
#define InverterStartIndex                  0x6100
#define NrEntryInverter                     8

//*3.1 Motor Control
#define SubindexInverterNodeStatus          0x00
#define SubindexInverterRPDO1LowDWord       0x01
#define SubindexInverterRPDO1HighDWord      0x02
#define SubindexInverterTPDO1LowDWord       0x03
#define SubindexInverterTPDO1HighDWord      0x04
#define SubindexInverterTPDO2LowDWord       0x05
#define SubindexInverterTPDO2HighDWord      0x06
#define SubindexInverterNMT                 0x07

//====================================================================
//*4 Multi I/O Port
#define IOPortStartIndex                    0x6200
#define NrEntryIOPort                       62

//*4.1 Input Value
#define SubindexIOPortControlWord           0x00
#define SubindexInput01                     0x01
#define SubindexInput02                     0x02
#define SubindexInput03                     0x03
#define SubindexInput04                     0x04
#define SubindexInput05                     0x05
#define SubindexInput06                     0x06
#define SubindexInput07                     0x07
#define SubindexInput08                     0x08
#define SubindexInput09                     0x09
#define SubindexInput10                     0x0a
#define SubindexInput11                     0x0b
#define SubindexInput12                     0x0c
#define SubindexInput13                     0x0d
#define SubindexInput14                     0x0e
#define SubindexInput15                     0x0f
#define SubindexInput28                     0x10
#define SubindexInput29                     0x11
#define SubindexInput30                     0x12
#define SubindexInput31                     0x13
#define SubindexInput32                     0x14
#define SubindexInput33                     0x15
#define SubindexInput34                     0x16
#define SubindexInput35                     0x17
#define SubindexInput36                     0x18
#define SubindexInput37                     0x19
#define SubindexInput38                     0x1a
#define SubindexInput39                     0x1b
#define SubindexInput41                     0x1c
#define SubindexInput42                     0x1d
#define SubindexInput43                     0x1e
#define SubindexInput44                     0x1f
#define SubindexInput45                     0x20
#define SubindexInput46                     0x21
#define SubindexInput47                     0x22
#define SubindexInput48                     0x23
#define SubindexInput49                     0x24
#define SubindexInput50                     0x25
#define SubindexInput51                     0x26
#define SubindexInput52                     0x27
#define SubindexInput62                     0x28
#define SubindexInput63                     0x29
#define SubindexInput64                     0x2a
#define SubindexInput65                     0x2b

//*4.2 Output Value
#define SubindexOutput01                    0x2c
#define SubindexOutput02                    0x2d
#define SubindexOutput03                    0x2e
#define SubindexOutput04                    0x2f
#define SubindexOutput05                    0x30
#define SubindexOutput06                    0x31
#define SubindexOutput07                    0x32
#define SubindexOutput08                    0x33
#define SubindexOutput36                    0x34
#define SubindexOutput49                    0x35
#define SubindexOutput50                    0x36
#define SubindexOutput51                    0x37
#define SubindexOutput52                    0x38
#define SubindexOutput53                    0x39
#define SubindexOutput54                    0x3a
#define SubindexOutput55                    0x3b
#define SubindexOutput56                    0x3c
#define SubindexOutput57                    0x3d

//====================================================================
//*5 Remote Control
#define RemoteControlStartIndex             0x6300
#define NrEntryRemoteControl                24

//*5.1 Remote Control Command Data
#define SubindexRemoteCtrlNodeStatus        0x00
#define SubindexRemoteCtrlTPDO1LowDWord     0x01                //COB 0x180
#define SubindexRemoteCtrlTPDO1HighDWord    0x02
#define SubindexRemoteCtrlTPDO2LowDWord     0x03                //COB 0x280
#define SubindexRemoteCtrlTPDO2HighDWord    0x04
#define SubindexRemoteCtrlRPDO1LowDWord     0x05                //COB 0x200
#define SubindexRemoteCtrlRPDO1HighDWord    0x06
#define SubindexRemoteCtrlRPDO2LowDWord     0x07                //COB 0x300
#define SubindexRemoteCtrlRPDO2HighDWord    0x08
#define SubindexRemoteCtrlRPDO4LowDWord     0x09                //COB 0x500
#define SubindexRemoteCtrlRPDO4HighDWord    0x0a
#define SubindexRemoteCtrlNMT               0x0b

//*5.2 Parameter of the fix curve
#define SubindexXJoystickCurveParaA         0x0c
#define SubindexXJoystickCurveParaB         0x0d
#define SubindexXJoystickCurveParaC         0x0e
#define SubindexXJoystickCurveParaD         0x0f
#define SubindexTelegramm1FromSlaveLowWord  0x10 //Byte 0: status of hub system | Byte 1: actual Height of hub system
#define SubindexTelegramm1FromSlaveHighWord 0x11 //safety control word from slave
#define SubindexTelegramm1ToSlaveLowWord    0x12 //Byte 0-3: angle11 - 22 of drive system
#define SubindexTelegramm1ToSlaveHighWord   0x13 //Byte 0: speed of MES | Byte 1: status of MES | Byte 2: status of auto drive | Byte 3: Display State
#define SubindexTelegramm2ToSlaveLowWord    0x14 //Byte 0: Y1Value of auto drive | Byte 1: Y2Value of auto drive | Byte 2-3: XValue of auto drive
#define SubindexTelegramm2ToSlaveHighWord   0x15 //Byte 0: Number of Error | Byte 1: extern status of MES | Byte 2: Steering Mode of MES
#define SubindexTelegramm3ToSlaveLowWord    0x16
#define SubindexTelegramm3ToSlaveHighWord   0x17

//====================================================================
//*6 Hub System
#define HubSystemStartIndex                 0x6400
#define NrEntryHubSystem                    9

//*6.1 hydraulic system control word
#define SubindexHubSystemControlWord        0x00    //bit 0: test mode (1)/ normal mode (0)
                                                    //Byte 1: which axel is choice in test mode
                                                    //Byte 2-3: value of height to be set (in mm)

//*6.2 height and pressure sensor
#define SubindexHeightHubAxel11             0x01
#define SubindexHeightHubAxel12             0x02
#define SubindexHeightHubAxel21             0x03
#define SubindexHeightHubAxel22             0x04
#define SubindexPressureSensorAxel11        0x05
#define SubindexPressureSensorAxel12        0x06
#define SubindexPressureSensorAxel21        0x07
#define SubindexPressureSensorAxel22        0x08
//====================================================================
//*7 Safety
#define SafetyStartIndex                    0x6500
#define NrEntrySafety                       100

//*7.1 actual Number of errors
#define SubindexNumOfError                  0x00

//*7.2 Error List
#define SubindexErrorRegister01             0x01
#define SubindexErrorRegister02             0x02
#define SubindexErrorRegister03             0x03
#define SubindexErrorRegister04             0x04
#define SubindexErrorRegister05             0x05
#define SubindexErrorRegister06             0x06
#define SubindexErrorRegister07             0x07
#define SubindexErrorRegister08             0x08
#define SubindexErrorRegister09             0x09
#define SubindexErrorRegister10             0x0a
#define SubindexErrorRegister11             0x0b
#define SubindexErrorRegister12             0x0c
#define SubindexErrorRegister13             0x0d
#define SubindexErrorRegister14             0x0e
#define SubindexErrorRegister15             0x0f
#define SubindexErrorRegister16             0x10
#define SubindexErrorRegister17             0x11
#define SubindexErrorRegister18             0x12
#define SubindexErrorRegister19             0x13
#define SubindexErrorRegister20             0x14
#define SubindexErrorRegister21             0x15
#define SubindexErrorRegister22             0x16
#define SubindexErrorRegister23             0x17
#define SubindexErrorRegister24             0x18
#define SubindexErrorRegister25             0x19
#define SubindexErrorRegister26             0x1a
#define SubindexErrorRegister27             0x1b
#define SubindexErrorRegister28             0x1c
#define SubindexErrorRegister29             0x1d
#define SubindexErrorRegister30             0x1e
#define SubindexErrorRegister31             0x1f
#define SubindexErrorRegister32             0x20

//*7.3 Timestamp of the Error List
#define SubindexErrorRegister01Timestamp1   0x21
#define SubindexErrorRegister01Timestamp2   0x22
#define SubindexErrorRegister02Timestamp1   0x23
#define SubindexErrorRegister02Timestamp2   0x24
#define SubindexErrorRegister03Timestamp1   0x25
#define SubindexErrorRegister03Timestamp2   0x26
#define SubindexErrorRegister04Timestamp1   0x27
#define SubindexErrorRegister04Timestamp2   0x28
#define SubindexErrorRegister05Timestamp1   0x29
#define SubindexErrorRegister05Timestamp2   0x2a
#define SubindexErrorRegister06Timestamp1   0x2b
#define SubindexErrorRegister06Timestamp2   0x2c
#define SubindexErrorRegister07Timestamp1   0x2d
#define SubindexErrorRegister07Timestamp2   0x2e
#define SubindexErrorRegister08Timestamp1   0x2f
#define SubindexErrorRegister08Timestamp2   0x30
#define SubindexErrorRegister09Timestamp1   0x31
#define SubindexErrorRegister09Timestamp2   0x32
#define SubindexErrorRegister10Timestamp1   0x33
#define SubindexErrorRegister10Timestamp2   0x34
#define SubindexErrorRegister11Timestamp1   0x35
#define SubindexErrorRegister11Timestamp2   0x36
#define SubindexErrorRegister12Timestamp1   0x37
#define SubindexErrorRegister12Timestamp2   0x38
#define SubindexErrorRegister13Timestamp1   0x39
#define SubindexErrorRegister13Timestamp2   0x3a
#define SubindexErrorRegister14Timestamp1   0x3b
#define SubindexErrorRegister14Timestamp2   0x3c
#define SubindexErrorRegister15Timestamp1   0x3d
#define SubindexErrorRegister15Timestamp2   0x3e
#define SubindexErrorRegister16Timestamp1   0x3f
#define SubindexErrorRegister16Timestamp2   0x40
#define SubindexErrorRegister17Timestamp1   0x41
#define SubindexErrorRegister17Timestamp2   0x42
#define SubindexErrorRegister18Timestamp1   0x43
#define SubindexErrorRegister18Timestamp2   0x44
#define SubindexErrorRegister19Timestamp1   0x45
#define SubindexErrorRegister19Timestamp2   0x46
#define SubindexErrorRegister20Timestamp1   0x47
#define SubindexErrorRegister20Timestamp2   0x48
#define SubindexErrorRegister21Timestamp1   0x49
#define SubindexErrorRegister21Timestamp2   0x4a
#define SubindexErrorRegister22Timestamp1   0x4b
#define SubindexErrorRegister22Timestamp2   0x4c
#define SubindexErrorRegister23Timestamp1   0x4d
#define SubindexErrorRegister23Timestamp2   0x4e
#define SubindexErrorRegister24Timestamp1   0x4f
#define SubindexErrorRegister24Timestamp2   0x50
#define SubindexErrorRegister25Timestamp1   0x51
#define SubindexErrorRegister25Timestamp2   0x52
#define SubindexErrorRegister26Timestamp1   0x53
#define SubindexErrorRegister26Timestamp2   0x54
#define SubindexErrorRegister27Timestamp1   0x55
#define SubindexErrorRegister27Timestamp2   0x56
#define SubindexErrorRegister28Timestamp1   0x57
#define SubindexErrorRegister28Timestamp2   0x58
#define SubindexErrorRegister29Timestamp1   0x59
#define SubindexErrorRegister29Timestamp2   0x5a
#define SubindexErrorRegister30Timestamp1   0x5b
#define SubindexErrorRegister30Timestamp2   0x5c
#define SubindexErrorRegister31Timestamp1   0x5d
#define SubindexErrorRegister31Timestamp2   0x5e
#define SubindexErrorRegister32Timestamp1   0x5f
#define SubindexErrorRegister32Timestamp2   0x60

//*7.5 Parameter of the Safety
#define SubindexSafetyControlWord           0x61
#define SubindexSafetyDateTime1             0x62
#define SubindexSafetyDateTime2             0x63

//====================================================================
//*8 Auto Drive System
#define AutoDriveStartIndex                 0x6600
#define NrEntryAutoDrive                    27

//*8.1 Auto Drive Parameter
#define SubindexAutoDriveControlWord        0x00
#define SubindexAutoDriveYValue             0x01
#define SubindexAutoDriveXValue             0x02
#define SubindexAutoDriveAGValue            0x03
#define SubindexAutoDriveRefenerzSpeed      0x04
#define SubindexAutoDriveControlKp1         0x05
#define SubindexAutoDriveControlKp2         0x06
#define SubindexAutoDriveControlKi1         0x07

//*8.2 Camera Parameter
#define SubindexCamera1RPDO1LowWord         0x08
#define SubindexCamera1RPDO1HighWord        0x09
#define SubindexCamera1RPDO2LowWord         0x0a
#define SubindexCamera1RPDO2HighWord        0x0b
#define SubindexCamera1RPDO3LowWord         0x0c
#define SubindexCamera1RPDO3HighWord        0x0d
#define SubindexCamera2RPDO1LowWord         0x0e
#define SubindexCamera2RPDO1HighWord        0x0f
#define SubindexCamera2RPDO2LowWord         0x10
#define SubindexCamera2RPDO2HighWord        0x11
#define SubindexCamera2RPDO3LowWord         0x12
#define SubindexCamera2RPDO3HighWord        0x13
#define SubindexCameraTPDO1LowWord          0x14
#define SubindexCameraTPDO1HighWord         0x15

//8.3 NMT Camera
#define SubindexCamera1NodeStatus           0x16
#define SubindexCamera2NodeStatus           0x17
#define SubindexCamera1NMT                  0x18
#define SubindexCamera2NMT                  0x19

//8.4 Steering factor
#define SubindexAutoDriveControlKi2         0x1a

#endif
