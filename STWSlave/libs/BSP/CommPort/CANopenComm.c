#include "CANopenComm.h"

//---Module Global Function Prototypes-------------------------------------------------------------
void Callback(const uint32 ou32_CallbackParameter, void * const opv_Handle);
sint16 StoreLoadOD(uint16 index,uint8 subindex,enum OD_Opt opt);
sint16 GetSetOD(uint16 index,uint8 subindex,uint16 *Addr, uint32 *value, enum OD_Opt opt);
void SyncInit(void);
void NMTInit(void);
void NMTManagement(void);
sint16 ResetNode(void);

//---Constant variable definition -----------------------------------------------------------------
void * mpv_Bus[4];
static void * oppv_Timer;

//---internal variable of the CANOpen communication -----------------------------------------------
//--1. Handle of the SDO Server--------------
static void * SDOServerhandle1;
static void * SDOServerhandle2;
static void * SDOServerhandle3;
static void * SDOServerhandle4;
//--2. Sync of the CANopen-------------------
SyncType SyncPara1;
SyncType SyncPara2;
SyncType SyncPara3;
SyncType SyncPara4;
//--3. Timer of the CANopen------------------
TimeType CANopenTimer;
//--4. NMT Info.-----------------------------
static NMTType NodeNMTStatus[NMTEntry];

//can bus status
static uint8 *CANBusStatus;


//---Function definition --------------------------------------------------------------------------
//=================================================================================================
/*!
    Function: Initialize the CANopen Communication
*/
//=================================================================================================
void CANopenCommInit(void){
    T_col2_config t_LibraryConfig1;
    T_col2_config t_LibraryConfig2;
    T_col2_config t_LibraryConfig3;
    T_col2_config t_LibraryConfig4;
    uint32 TimerCallbackParameter=0;
    uint32 Value;
    uint16 ODMemAdr;
    sint16 err;

    x_can_bus_init(CANOpenBusChannel1,DefaultBaudrate); //initial the CAN Bus with the def. Channel and Baudrate
    x_can_bus_init(CANOpenBusChannel2,DefaultBaudrate); //initial the CAN Bus with the def. Channel and Baudrate
    x_can_bus_init(CANOpenBusChannel3,DefaultBaudrate); //initial the CAN Bus with the def. Channel and Baudrate
    x_can_bus_init(CANOpenBusChannel4,DefaultBaudrate); //initial the CAN Bus with the def. Channel and Baudrate

    t_LibraryConfig1.u16_Channel = CANOpenBusChannel1;
    t_LibraryConfig1.u16_TxFifo = CANTxFIFOSize;
    t_LibraryConfig1.u16_RxFifo = CANRxFIFOSize;

    t_LibraryConfig2.u16_Channel = CANOpenBusChannel2;
    t_LibraryConfig2.u16_TxFifo = CANTxFIFOSize;
    t_LibraryConfig2.u16_RxFifo = CANRxFIFOSize;

    t_LibraryConfig3.u16_Channel = CANOpenBusChannel3;
    t_LibraryConfig3.u16_TxFifo = CANTxFIFOSize;
    t_LibraryConfig3.u16_RxFifo = CANRxFIFOSize;

    t_LibraryConfig4.u16_Channel = CANOpenBusChannel4;
    t_LibraryConfig4.u16_TxFifo = CANTxFIFOSize;
    t_LibraryConfig4.u16_RxFifo = CANRxFIFOSize;

    col2_init(&t_LibraryConfig1,DefaultSDOTimeOut,DefaultNodeID,&mpv_Bus[0]); // initial the Server of the CANopen
    col2_init(&t_LibraryConfig2,DefaultSDOTimeOut,DefaultNodeID,&mpv_Bus[1]); // initial the Server of the CANopen
    col2_init(&t_LibraryConfig3,DefaultSDOTimeOut,DefaultNodeID,&mpv_Bus[2]); // initial the Server of the CANopen
    col2_init(&t_LibraryConfig4,DefaultSDOTimeOut,DefaultNodeID,&mpv_Bus[3]); // initial the Server of the CANopen

    ODMemInit(); //initial the Memory of the object dictionary

    col2_pdo_register(mpv_Bus[0],RxSDO_COB+DefaultNodeID,&SDOServerhandle1); //register the SDO handle-function
    col2_pdo_register(mpv_Bus[1],RxSDO_COB+DefaultNodeID,&SDOServerhandle2); //register the SDO handle-function
    col2_pdo_register(mpv_Bus[2],RxSDO_COB+DefaultNodeID,&SDOServerhandle3); //register the SDO handle-function
    col2_pdo_register(mpv_Bus[3],RxSDO_COB+DefaultNodeID,&SDOServerhandle4); //register the SDO handle-function

    StoreLoadOD(0x0000,0x00,LoadODFromEEP);//
    PDOListSetup();

    CANopenTimer.tick=0;
    //GetSetOD(DevParaStartIndex,SubindexNodeTimerCycle,&ODMemAdr,&Value,GetOD);

    //if(Value==0)
    CANopenTimer.Timeout=DefaultTimeout;
    //else CANopenTimer.Timeout=(uint16)Value;

    NMTInit();

    SyncInit();

    CANBusStatus=BindODMem(DevParaStartIndex,SubindexSysStatus,TypeU8,1); *CANBusStatus=0x00;

    x_tim_init (X_TIM_PRIO_01,TimerCallbackParameter,Callback,&oppv_Timer);
    x_tim_set(oppv_Timer,DelayTime,CycleTime);
}

//=================================================================================================
/*!
    Function: check the work status of the can bus
    output: Error code
*/
//=================================================================================================
void CANBusChk(void){
    T_x_can_bus_status t_Status;

    x_can_bus_get_status (X_CAN_BUS_01,&t_Status);
    if(t_Status.u16_BusState!=X_CAN_BUS_FAILURE_BUSOFF) *CANBusStatus&=~0x01;
    else *CANBusStatus|=0x01;

    x_can_bus_get_status (X_CAN_BUS_02,&t_Status);
    if(t_Status.u16_BusState!=X_CAN_BUS_FAILURE_BUSOFF) *CANBusStatus&=~0x02;
    else *CANBusStatus|=0x02;
}

//=================================================================================================
/*!
    Function: Restoring default parameters
    output: Error code
*/
//=================================================================================================
sint16 ResetNode(void){
    sint16 errorcode;
    uint16 Addr;
    uint32 temp;
    uint16 i;
    uint32 BaudrateCode;

    for(i=0;i<ODMemLength;i++){
        ODMem[i]=0;
    }

    switch(DefaultBaudrate){
        case 125000: BaudrateCode=0;break;
        case 250000: BaudrateCode=1;break;
        case 500000: BaudrateCode=2;break;
        case 800000: BaudrateCode=3;break;
        case 1000000: BaudrateCode=4;break;
    }

    temp=NodeHWVersion;
    errorcode=GetSetOD(DevParaStartIndex,SubindexHwtype,&Addr,&temp,SetOD);
    temp=NodeSerialNummer;
    errorcode=GetSetOD(DevParaStartIndex,SubindexSerNr,&Addr,&temp,SetOD);
    temp=(uint32)DefaultNodeID+((uint32)DefaultHeartbeatTime<<8)+(BaudrateCode<<24);
    errorcode=GetSetOD(DevParaStartIndex,SubindexNodeParam,&Addr,&temp,SetOD);

    return errorcode;
}

//=================================================================================================
/*!
    Function: update the Parameter of the CANopen communication from the object dictionary
    output: None
*/
//=================================================================================================
void CANopenParaUpdate(uint16 index,uint8 subindex){
    uint16 ODMemAddr;
    uint32 Value;

    //CANopen Parameter Update: Device Parameter
    if((index>=DevParaStartIndex)&&(index<(DevParaStartIndex+0x0100))){
        GetSetOD(index,subindex,&ODMemAddr,&Value,GetOD);
        switch(subindex){
        case SubindexControlWord:
            if(Value==0x00000001){
                Value&=~0x00000001;
                GetSetOD(index,subindex,&ODMemAddr,&Value,SetOD);
                StoreLoadOD(0x0000,0x00,StoreODToEEP);
            }
            if(Value==0x00000002){
                Value&=~0x00000002;
                GetSetOD(index,subindex,&ODMemAddr,&Value,SetOD);
                ResetNode();
                StoreLoadOD(0x0000,0x00,StoreODToEEP);
            }
            break;
        }
    }
}



//=================================================================================================
/*!
    Function: Receive the SDO from the bus-master and handle it.
    output: Error code
*/
//=================================================================================================
void SDOHandle(void){
    uint8 Data[8];
    uint8 Length=8;
    sint16 errcode;
    uint16 index;
    uint8 subindex;
    uint16 ODMemAddr;
    uint32 Value;

    // SDO Handle of the Bus Channel1
    errcode=col2_pdo_read(SDOServerhandle1,&Data[0],&Length);
    if(errcode==C_NO_ERR){
        index=Data[2];
        index=(uint16)Data[1]+(index<<8);
        subindex=Data[3];
        //read the object dictionary
        if(Data[0]==0x40){
            GetSetOD(index,subindex,&ODMemAddr,&Value, GetOD);
            Data[0]=0x43;
            Data[4]=Value&0xff;
            Data[5]=(Value>>8)&0xff;
            Data[6]=(Value>>16)&0xff;
            Data[7]=(Value>>24)&0xff;
        }
        //write the object dictionary
        if(Data[0]==0x23){
            Value=Data[7];
            Value=(uint32)Data[6]+(Value<<8);
            Value=(uint32)Data[5]+(Value<<8);
            Value=(uint32)Data[4]+(Value<<8);
            GetSetOD(index,subindex,&ODMemAddr,&Value,SetOD);
            Data[0]=0x60;
            CANopenParaUpdate(index,subindex);
        }
        col2_pdo_write(mpv_Bus[0], TxSDO_COB+DefaultNodeID,&Data[0],8);
    }

    // SDO Handle of the Bus Channel2
    errcode=col2_pdo_read(SDOServerhandle2,&Data[0],&Length);
    if(errcode==C_NO_ERR){
        index=Data[2];
        index=(uint16)Data[1]+(index<<8);
        subindex=Data[3];
        //read the object dictionary
        if(Data[0]==0x40){
            GetSetOD(index,subindex,&ODMemAddr,&Value, GetOD);
            Data[0]=0x43;
            Data[4]=Value&0xff;
            Data[5]=(Value>>8)&0xff;
            Data[6]=(Value>>16)&0xff;
            Data[7]=(Value>>24)&0xff;
        }
        //write the object dictionary
        if(Data[0]==0x23){
            Value=Data[7];
            Value=(uint32)Data[6]+(Value<<8);
            Value=(uint32)Data[5]+(Value<<8);
            Value=(uint32)Data[4]+(Value<<8);
            GetSetOD(index,subindex,&ODMemAddr,&Value,SetOD);
            Data[0]=0x60;
            CANopenParaUpdate(index,subindex);
        }
        col2_pdo_write(mpv_Bus[1], TxSDO_COB+DefaultNodeID,&Data[0],8);
    }

    // SDO Handle of the Bus Channel3
    errcode=col2_pdo_read(SDOServerhandle3,&Data[0],&Length);
    if(errcode==C_NO_ERR){
        index=Data[2];
        index=(uint16)Data[1]+(index<<8);
        subindex=Data[3];
        //read the object dictionary
        if(Data[0]==0x40){
            GetSetOD(index,subindex,&ODMemAddr,&Value, GetOD);
            Data[0]=0x43;
            Data[4]=Value&0xff;
            Data[5]=(Value>>8)&0xff;
            Data[6]=(Value>>16)&0xff;
            Data[7]=(Value>>24)&0xff;
        }
        //write the object dictionary
        if(Data[0]==0x23){
            Value=Data[7];
            Value=(uint32)Data[6]+(Value<<8);
            Value=(uint32)Data[5]+(Value<<8);
            Value=(uint32)Data[4]+(Value<<8);
            GetSetOD(index,subindex,&ODMemAddr,&Value,SetOD);
            Data[0]=0x60;
            CANopenParaUpdate(index,subindex);
        }
        col2_pdo_write(mpv_Bus[2], TxSDO_COB+DefaultNodeID,&Data[0],8);
    }
    // SDO Handle of the Bus Channel4
    errcode=col2_pdo_read(SDOServerhandle4,&Data[0],&Length);
    if(errcode==C_NO_ERR){
        index=Data[2];
        index=(uint16)Data[1]+(index<<8);
        subindex=Data[3];
        //read the object dictionary
        if(Data[0]==0x40){
            GetSetOD(index,subindex,&ODMemAddr,&Value, GetOD);
            Data[0]=0x43;
            Data[4]=Value&0xff;
            Data[5]=(Value>>8)&0xff;
            Data[6]=(Value>>16)&0xff;
            Data[7]=(Value>>24)&0xff;
        }
        //write the object dictionary
        if(Data[0]==0x23){
            Value=Data[7];
            Value=(uint32)Data[6]+(Value<<8);
            Value=(uint32)Data[5]+(Value<<8);
            Value=(uint32)Data[4]+(Value<<8);
            GetSetOD(index,subindex,&ODMemAddr,&Value,SetOD);
            Data[0]=0x60;
            CANopenParaUpdate(index,subindex);
        }
        col2_pdo_write(mpv_Bus[3], TxSDO_COB+DefaultNodeID,&Data[0],8);
    }
}

//=================================================================================================
/*!
    Function: Handle the PDO.
    output: Error code
*/
//=================================================================================================
sint16 PDOHandle(void){
    uint8 PDOLen;
    uint8 Data[8];
    uint16 iTPDO,iRPDO;
    uint16 iData;
    sint16 PDOReadResult;
    sint16 errorcode=0;

    PDOLen=8;

    //PDO send:
    for(iTPDO=0;iTPDO<MaxNrTPDO;iTPDO++){
        if(TPDOList[iTPDO].enable==Disable) continue;

        if(TPDOList[iTPDO].SendTrigger==1){
            TPDOList[iTPDO].SendTrigger=0;

            if(TPDOList[iTPDO].DataCount==0) continue;
            for(iData=0;iData<PDOLen;iData++){
                if(iData<TPDOList[iTPDO].DataCount) Data[iData]=*TPDOList[iTPDO].Data[iData];
                else Data[iData]=0;
            }
            errorcode=col2_pdo_write(mpv_Bus[TPDOList[iTPDO].BusNumber],TPDOList[iTPDO].COBID,&Data[0],8);
        }
    }

    //PDO receive:
    for(iRPDO=0;iRPDO<MaxNrRPDO;iRPDO++){
        if(RPDOList[iRPDO].enable==Disable) continue;
        PDOReadResult=col2_pdo_read(RPDOList[iRPDO].RPDOHandle,&Data[0],&PDOLen);

        if(PDOReadResult==C_NO_ERR){
            if(RPDOList[iRPDO].DataCount==0) continue;

            for(iData=0;iData<RPDOList[iRPDO].DataCount;iData++){
                *RPDOList[iRPDO].Data[iData]=Data[iData];
            }
        }
    }
    return errorcode;
}

//=================================================================================================
/*!
    Function: CANopenComm Task.
    output: None
*/
//=================================================================================================
void TaskCANopen(void){
    col2_task(mpv_Bus[0]);
    col2_task(mpv_Bus[1]);
    col2_task(mpv_Bus[2]);
    col2_task(mpv_Bus[3]);
    NMTManagement();
    SDOHandle();
    PDOHandle();
    CANBusChk();
}

//=================================================================================================
/*!
    Function: Sync Initial
    output: None
*/
//=================================================================================================
void SyncInit(void){
    uint32 value=0;
    uint16 ODMemAddr;

    GetSetOD(DevParaStartIndex,SubindexConfigSync12,&ODMemAddr,&value,GetOD);
    SyncPara1.Status=(uint8 *)&ODMem[ODMemAddr];
    SyncPara1.TimeWnd=(uint8 *)&ODMem[ODMemAddr]+1;
    SyncPara2.Status=(uint8 *)&ODMem[ODMemAddr]+2;
    SyncPara2.TimeWnd=(uint8 *)&ODMem[ODMemAddr]+3;

    GetSetOD(DevParaStartIndex,SubindexConfigSync34,&ODMemAddr,&value,GetOD);
    SyncPara3.Status=(uint8 *)&ODMem[ODMemAddr];
    SyncPara3.TimeWnd=(uint8 *)&ODMem[ODMemAddr]+1;
    SyncPara4.Status=(uint8 *)&ODMem[ODMemAddr]+2;
    SyncPara4.TimeWnd=(uint8 *)&ODMem[ODMemAddr]+3;
}

//=================================================================================================
/*!
    Function: Send Sync Message
    output: None
*/
//=================================================================================================
void SyncHandle(void){
    uint8 Data=0;

    //Sync Message in Bus Channel 1
    if((*SyncPara1.Status)&SyncEnable){
        if(CANopenTimer.tick==*SyncPara1.TimeWnd) col2_pdo_write(mpv_Bus[0],0x80,&Data,0);
    }

    //Sync Message in Bus Channel 2
    if((*SyncPara2.Status)&SyncEnable){
        if(CANopenTimer.tick==*SyncPara2.TimeWnd) col2_pdo_write(mpv_Bus[1],0x80,&Data,0);
    }

    //Sync Message in Bus Channel 3
    if((*SyncPara3.Status)&SyncEnable){
        if(CANopenTimer.tick==*SyncPara3.TimeWnd) col2_pdo_write(mpv_Bus[2],0x80,&Data,0);
    }

    //Sync Message in Bus Channel 4
    if((*SyncPara4.Status)&SyncEnable){
        if(CANopenTimer.tick==*SyncPara4.TimeWnd) col2_pdo_write(mpv_Bus[3],0x80,&Data,0);
    }
}


//=================================================================================================
/*!
    Function: Callback function of the Timer.
    output: None
*/
//=================================================================================================
void Callback(const uint32 ou32_CallbackParameter, void * const opv_Handle){
    void *Opv;
    uint32 InputParameter;
    uint16 i;

    InputParameter=ou32_CallbackParameter;
    Opv=opv_Handle;

    //Sync Message handle
    SyncHandle();

    //tick increment
    CANopenTimer.tick++;
    if(CANopenTimer.tick==CANopenTimer.Timeout){
        CANopenTimer.tick=0;
        //check the event time of TPDO
        for(i=0;i<MaxNrTPDO;i++){
            if(!TPDOList[i].enable) continue;
            if(TPDOList[i].timer>=(TPDOList[i].EventTime)){
                TPDOList[i].SendTrigger=1;
                TPDOList[i].timer=0;
            }
            TPDOList[i].timer++;
        }
    }
}



//=================================================================================================
/*!
    Function: Initial the NMT Management for each node
    output: None
*/
//=================================================================================================
void NMTInit(void){
    uint32 value;
    uint16 ODMemAddr;
    uint16 iNMT;

    GetSetOD(InverterStartIndex,SubindexInverterNodeStatus,&ODMemAddr,&value,GetOD);
    NodeNMTStatus[0].NMTStatus=(uint8 *)&ODMem[ODMemAddr];
    NodeNMTStatus[0].NodeStatus=(uint8 *)&ODMem[ODMemAddr]+1;
    GetSetOD(InverterStartIndex,SubindexInverterNMT,&ODMemAddr,&value,GetOD);
    NodeNMTStatus[0].NMTSend=(uint16 *)&ODMem[ODMemAddr];
    NodeNMTStatus[0].NodeID=IDInverterHydraulic;
    NodeNMTStatus[0].BusChannel=BusChInverterHydraulic;


    for(iNMT=0;iNMT<NMTEntry;iNMT++){
        col2_heartbeat_register_consumer(mpv_Bus[NodeNMTStatus[iNMT].BusChannel],NodeNMTStatus[iNMT].NodeID,5000);
    }
}

//=================================================================================================
/*!
    Function: get the current node Status during the NMT Management
    output: None
*/
//=================================================================================================
void NMTManagement(void){
    uint16 tmp;
    uint8 cmdNMT;
    uint16 iNMT;

    //Gurading the Node
    for(iNMT=0;iNMT<NMTEntry;iNMT++){
        col2_nmt_get_slave_status(mpv_Bus[NodeNMTStatus[iNMT].BusChannel],NodeNMTStatus[iNMT].NodeID, NodeNMTStatus[iNMT].NMTStatus, NodeNMTStatus[iNMT].NodeStatus);
    }
    //NMT Send
    for(iNMT=0;iNMT<NMTEntry;iNMT++){
        tmp=*NodeNMTStatus[iNMT].NMTSend;
        if (tmp&0x0001){
            cmdNMT=(uint8)(tmp>>8);
            col2_nmt_send (mpv_Bus[NodeNMTStatus[iNMT].BusChannel], NodeNMTStatus[iNMT].NodeID,cmdNMT);
            *NodeNMTStatus[iNMT].NMTSend=0x0000;
            return;
        }
    }
}


