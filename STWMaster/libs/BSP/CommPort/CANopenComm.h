#ifndef _CANOPENCOMM_H
#define _CANOPENCOMM_H
#include "stwtypes.h"
#include "DeviceOD.h"
#include "ODContent.h"
#include "CANopenDeviceConfig.h"
#include "MESConfig.h"
#include "col2.h"
#include "x_sys.h"
#include "x_tim.h"

/*====================================================================
Format Definition
====================================================================*/
#define Enable                       0x01
#define Disable                      0x00

#define TxPDO                        0x00
#define RxPDO                        0x01

#define DirIn                        0x00
#define DirOut                       0x01

/*====================================================================
bus handle Definition
====================================================================*/
extern void *mpv_Bus[4];

/*====================================================================
NMT Parameter Configuration
====================================================================*/
#ifdef MasterCPU
#define NMTEntry                     (NrOfMotorInverter+NrOfRemoteControl+NrOfCamera)
#endif // MasterCPU

#ifdef SlaveCPU
#define NMTEntry                     (NrOfHubSys)
#endif // SlaveCPU



typedef struct{
    uint8 *NMTStatus;
    uint8 *NodeStatus;
    uint16 *NMTSend;
    uint8 NodeID;
    uint16 BusChannel;
}NMTType;

/*====================================================================
Host Node Configuration
====================================================================*/
#define NodeHWVersion                101
#define NodeSerialNummer             10

#ifdef MasterCPU
#define DefaultNodeID                0x002
#endif // MasterCPU

#ifdef SlaveCPU
#define DefaultNodeID                0x003
#endif // SlaveCPU

#define DefaultWifiModuleID          0x001
#define DefaultSDOTimeOut            500
#define DefaultHeartbeatTime         0

/*====================================================================
Sync Definition
====================================================================*/
#define SyncEnable                   0x01

typedef struct{
    uint8 *Status;
    uint8 *TimeWnd;
}SyncType;

extern SyncType SyncPara1;
extern SyncType SyncPara2;
extern SyncType SyncPara3;
extern SyncType SyncPara4;
/*====================================================================
SDO Definition
====================================================================*/
#define TxSDO_COB                    0x580
#define RxSDO_COB                    0x600

#define RemoteTxSDO_COB              0x600
#define RemoteRxSDO_COB              0x580


/*====================================================================
PDO Definition
====================================================================*/
#define MaxNrTPDO                    32
#define MaxNrRPDO                    32

#define DefaultTransmissionType      0x00
#define DefaultEventTime             40 //at the time of tick

typedef struct{
    uint16 COBID;
    uint8 enable;
    uint16 EventTime;
    uint16 timer;
    uint16 SendTrigger;
    uint16 DataCount;
    uint16 BusNumber;
    uint8 *Data[8];
}TPDOType;

typedef struct{
    uint16 COBID;
    uint8 enable;
    uint16 DataCount;
    uint16 BusNumber;
    uint8 *Data[8];
    void *RPDOHandle;
}RPDOType;

extern TPDOType TPDOList[MaxNrTPDO];
extern RPDOType RPDOList[MaxNrRPDO];


/*====================================================================
Timer Definition
====================================================================*/
#define CycleTime                   1
#define DelayTime                   0

#define DefaultTimeout              200

typedef struct{
    uint32 tick;
    uint32 Timeout;
}TimeType;

extern TimeType CANopenTimer;

/*====================================================================
Function Definition
====================================================================*/
void CANopenCommInit(void);
void TaskCANopen(void);
void PDOListSetup(void);


#endif
