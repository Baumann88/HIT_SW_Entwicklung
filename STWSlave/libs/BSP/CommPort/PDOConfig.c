#include "CANopenComm.h"
 
TPDOType TPDOList[MaxNrTPDO];
RPDOType RPDOList[MaxNrRPDO];

void PDOListSetup(void){
    uint16 ODMemAddr;
    uint16 Index;
    uint8 Subindex;
    uint16 tmp;
    uint32 Value;
    uint16 iByte;

    //TPDO Configuation 
    //TPDO0
    TPDOList[0].enable=1; 
    TPDOList[0].COBID=0x304; 
    TPDOList[0].BusNumber=0; 
    TPDOList[0].EventTime=1; 
    TPDOList[0].DataCount=0; 

    Value=0x63000704; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[0].Data[TPDOList[0].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[0].DataCount++;} 

    Value=0x63000804; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[0].Data[TPDOList[0].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[0].DataCount++;} 



    //TPDO1
    TPDOList[1].enable=1; 
    TPDOList[1].COBID=0x504; 
    TPDOList[1].BusNumber=0; 
    TPDOList[1].EventTime=1; 
    TPDOList[1].DataCount=0; 

    Value=0x63000904; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[1].Data[TPDOList[1].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[1].DataCount++;} 

    Value=0x63000a04; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[1].Data[TPDOList[1].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[1].DataCount++;} 



    //TPDO2
    TPDOList[2].enable=1; 
    TPDOList[2].COBID=0x204; 
    TPDOList[2].BusNumber=0; 
    TPDOList[2].EventTime=3; 
    TPDOList[2].DataCount=0; 

    Value=0x63000504; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[2].Data[TPDOList[2].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[2].DataCount++;} 

    Value=0x63000604; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[2].Data[TPDOList[2].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[2].DataCount++;} 



    //TPDO3
    TPDOList[3].enable=1; 
    TPDOList[3].COBID=0x208; 
    TPDOList[3].BusNumber=1; 
    TPDOList[3].EventTime=1; 
    TPDOList[3].DataCount=0; 

    Value=0x61000104; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[3].Data[TPDOList[3].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[3].DataCount++;} 

    Value=0x61000204; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[3].Data[TPDOList[3].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[3].DataCount++;} 



    //TPDO4
    TPDOList[4].enable=1; 
    TPDOList[4].COBID=0x183; 
    TPDOList[4].BusNumber=0; 
    TPDOList[4].EventTime=1; 
    TPDOList[4].DataCount=0; 

    Value=0x64002204; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[4].Data[TPDOList[4].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[4].DataCount++;} 

    Value=0x65001904; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[4].Data[TPDOList[4].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[4].DataCount++;} 



    //RPDO Configuration 
    //RPDO0
    RPDOList[0].enable=1; 
    RPDOList[0].COBID=0x184; 
    RPDOList[0].BusNumber=0; 
    RPDOList[0].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[0].BusNumber], RPDOList[0].COBID, &RPDOList[0].RPDOHandle);

    Value=0x63000104; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[0].Data[RPDOList[0].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[0].DataCount++;} 

    Value=0x63000204; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[0].Data[RPDOList[0].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[0].DataCount++;} 



    //RPDO1
    RPDOList[1].enable=1; 
    RPDOList[1].COBID=0x284; 
    RPDOList[1].BusNumber=0; 
    RPDOList[1].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[1].BusNumber], RPDOList[1].COBID, &RPDOList[1].RPDOHandle);

    Value=0x63000304; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[1].Data[RPDOList[1].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[1].DataCount++;} 

    Value=0x63000404; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[1].Data[RPDOList[1].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[1].DataCount++;} 



    //RPDO2
    RPDOList[2].enable=1; 
    RPDOList[2].COBID=0x188; 
    RPDOList[2].BusNumber=1; 
    RPDOList[2].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[2].BusNumber], RPDOList[2].COBID, &RPDOList[2].RPDOHandle);

    Value=0x61000304; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[2].Data[RPDOList[2].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[2].DataCount++;} 

    Value=0x61000404; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[2].Data[RPDOList[2].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[2].DataCount++;} 



    //RPDO3
    RPDOList[3].enable=1; 
    RPDOList[3].COBID=0x288; 
    RPDOList[3].BusNumber=1; 
    RPDOList[3].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[3].BusNumber], RPDOList[3].COBID, &RPDOList[3].RPDOHandle);

    Value=0x61000504; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[3].Data[RPDOList[3].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[3].DataCount++;} 

    Value=0x61000604; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[3].Data[RPDOList[3].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[3].DataCount++;} 



    //RPDO4
    RPDOList[4].enable=1; 
    RPDOList[4].COBID=0x182; 
    RPDOList[4].BusNumber=0; 
    RPDOList[4].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[4].BusNumber], RPDOList[4].COBID, &RPDOList[4].RPDOHandle);

    Value=0x64000004; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[4].Data[RPDOList[4].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[4].DataCount++;} 

    Value=0x65006a04; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[4].Data[RPDOList[4].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[4].DataCount++;} 



    //RPDO5
    RPDOList[5].enable=1; 
    RPDOList[5].COBID=0x192; 
    RPDOList[5].BusNumber=0; 
    RPDOList[5].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[5].BusNumber], RPDOList[5].COBID, &RPDOList[5].RPDOHandle);

    Value=0x63000c04; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[5].Data[RPDOList[5].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[5].DataCount++;} 

    Value=0x63000d04; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[5].Data[RPDOList[5].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[5].DataCount++;} 



    //RPDO6
    RPDOList[6].enable=1; 
    RPDOList[6].COBID=0x202; 
    RPDOList[6].BusNumber=0; 
    RPDOList[6].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[6].BusNumber], RPDOList[6].COBID, &RPDOList[6].RPDOHandle);

    Value=0x63000e04; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[6].Data[RPDOList[6].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[6].DataCount++;} 

    Value=0x63000f04; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[6].Data[RPDOList[6].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[6].DataCount++;} 



    //RPDO7
    RPDOList[7].enable=1; 
    RPDOList[7].COBID=0x212; 
    RPDOList[7].BusNumber=0; 
    RPDOList[7].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[7].BusNumber], RPDOList[7].COBID, &RPDOList[7].RPDOHandle);

    Value=0x65003104; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[7].Data[RPDOList[7].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[7].DataCount++;} 

    Value=0x65003204; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[7].Data[RPDOList[7].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[7].DataCount++;} 



    //RPDO8
    RPDOList[8].enable=1; 
    RPDOList[8].COBID=0x222; 
    RPDOList[8].BusNumber=0; 
    RPDOList[8].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[8].BusNumber], RPDOList[8].COBID, &RPDOList[8].RPDOHandle);

    Value=0x65003304; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[8].Data[RPDOList[8].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[8].DataCount++;} 

    Value=0x65003404; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[8].Data[RPDOList[8].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[8].DataCount++;} 



}