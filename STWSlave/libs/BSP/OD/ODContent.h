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
#define SubindexSysStatus                   0x0b //Bit 0: Ignition On/Off | Byte 1: CAN Bus status
#define SubindexSysCycleTime                0x0c
#define SubindexSysDateTime1                0x0d
#define SubindexSysDateTime2                0x0e

//====================================================================
//*2 Drive System
#define DriveModuleStartIndex               0x6000
#define NrEntryDriveModule                  1

//*2.0 control word of the drive system
#define SubindexDriveSysControlWord         0x00

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
#define NrEntryIOPort                       36

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
#define SubindexInput36                     0x10
#define SubindexInput37                     0x11
#define SubindexInput38                     0x12
#define SubindexInput39                     0x13

//*4.2 Output Value
#define SubindexOutput01                    0x14
#define SubindexOutput02                    0x15
#define SubindexOutput03                    0x16
#define SubindexOutput04                    0x17
#define SubindexOutput05                    0x18
#define SubindexOutput06                    0x19
#define SubindexOutput07                    0x1a
#define SubindexOutput08                    0x1b
#define SubindexOutput24                    0x1c
#define SubindexOutput25                    0x1d
#define SubindexOutput26                    0x1e
#define SubindexOutput27                    0x1f
#define SubindexOutput28                    0x20
#define SubindexOutput29                    0x21
#define SubindexOutput30                    0x22
#define SubindexOutput31                    0x23

//====================================================================
//*5 Remote Control
#define RemoteControlStartIndex             0x6300
#define NrEntryRemoteControl                18

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

//*5.2 Remote Control RPDO List
#define SubindexRemoteCtrlRPDO1LowDWORD     0x0c
#define SubindexRemoteCtrlRPDO1HighDWORD    0x0d
#define SubindexRemoteCtrlRPDO2LowDWORD     0x0e
#define SubindexRemoteCtrlRPDO2HighDWORD    0x0f
#define SubindexRemoteCtrlRPDO3LowDWORD     0x10
#define SubindexRemoteCtrlRPDO3HighDWORD    0x11

//====================================================================
//*6 Hub System
#define HubSystemStartIndex                 0x6400
#define NrEntryHubSystem                    39

//*6.1 hydraulic system control word
#define SubindexHubSystemControlWord        0x00    //bit 0: test mode (1)/ normal mode (0)
                                                    //Byte 1: which axel is choice in test mode
                                                    //Byte 2-3: value of height to be set (in mm)
//*6.3 height and pressure sensor
#define SubindexHeightHubAxel11             0x01
#define SubindexHeightHubAxel12             0x02
#define SubindexHeightHubAxel21             0x03
#define SubindexHeightHubAxel22             0x04
#define SubindexPressureSensorPump          0x05
#define SubindexPressureSensorAxel11        0x06
#define SubindexPressureSensorAxel12        0x07
#define SubindexPressureSensorAxel21        0x08
#define SubindexPressureSensorAxel22        0x09

//*6.4 hub system control
#define SubindexControlKpAxel11             0x0a
#define SubindexControlKiAxel11             0x0b
#define SubindexControlKpAxel12             0x0c
#define SubindexControlKiAxel12             0x0d
#define SubindexControlKpAxel21             0x0e
#define SubindexControlKiAxel21             0x0f
#define SubindexControlKpAxel22             0x10
#define SubindexControlKiAxel22             0x11

//*6.5 parameter
#define SubindexHeightSensor11FactA         0x12
#define SubindexHeightSensor11FactB         0x13
#define SubindexHeightSensor12FactA         0x14
#define SubindexHeightSensor12FactB         0x15
#define SubindexHeightSensor21FactA         0x16
#define SubindexHeightSensor21FactB         0x17
#define SubindexHeightSensor22FactA         0x18
#define SubindexHeightSensor22FactB         0x19

//*6.6 temperature sensor
#define SubindexTemperatureSensor           0x1a
#define SubindexActualTemperature           0x1b

//*6.8 normal Parameter
#define SubindexDefaultHydraulicMotorRPM    0x1c
#define SubindexDefaultMaxHeight            0x1d
#define SubindexDefaultMinHeight            0x1e

//*6.9 Weight
#define SubindexWeight                      0x1f
#define SubindexXValueCG                    0x20
#define SubindexYValueCG                    0x21

//*6.10 Telegramm to Master
#define SubindexHubSystemTelegramm          0x22  //Byte 0: status of the hub system | Byte 1: height of the hub system

//*6.11 Speed of the Hub
#define SubindexHubSpeedAxel11              0x23
#define SubindexHubSpeedAxel12              0x24
#define SubindexHubSpeedAxel21              0x25
#define SubindexHubSpeedAxel22              0x26

//====================================================================
//*7 Safety
#define SafetyStartIndex                    0x6500
#define NrEntrySafety                       108

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

//*7.4 Error List Master CPU
#define SubindexMasterCPUErrorRegister01    0x61
#define SubindexMasterCPUErrorRegister02    0x62
#define SubindexMasterCPUErrorRegister03    0x63
#define SubindexMasterCPUErrorRegister04    0x64
#define SubindexMasterCPUErrorRegister05    0x65
#define SubindexMasterCPUErrorRegister06    0x66
#define SubindexMasterCPUErrorRegister07    0x67
#define SubindexMasterCPUErrorRegister08    0x68


//*7.5 Parameter of the Safety
#define SubindexSafetyControlWord           0x69
#define SubindexSafetyControlWordMaster     0x6a
#define SubindexSafetyMasterNumOfError      0x6b

//====================================================================
//*8 Auto Drive System
#define AutoDriveStartIndex                 0x6600
#define NrEntryAutoDrive                    1

//*8.1 Auto Drive Parameter
#define SubindexAutoDriveControlWord        0x00

#endif
