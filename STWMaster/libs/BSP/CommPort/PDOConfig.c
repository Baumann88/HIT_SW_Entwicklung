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
    TPDOList[0].COBID=0x182; 
    TPDOList[0].BusNumber=0; 
    TPDOList[0].EventTime=4; 
    TPDOList[0].DataCount=0; 

    Value=0x64000004; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[0].Data[TPDOList[0].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[0].DataCount++;} 

    Value=0x65006104; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[0].Data[TPDOList[0].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[0].DataCount++;} 



    //TPDO1
    TPDOList[1].enable=1; 
    TPDOList[1].COBID=0x192; 
    TPDOList[1].BusNumber=0; 
    TPDOList[1].EventTime=1; 
    TPDOList[1].DataCount=0; 

    Value=0x63001204; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[1].Data[TPDOList[1].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[1].DataCount++;} 

    Value=0x63001304; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[1].Data[TPDOList[1].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[1].DataCount++;} 



    //TPDO2
    TPDOList[2].enable=1; 
    TPDOList[2].COBID=0x202; 
    TPDOList[2].BusNumber=0; 
    TPDOList[2].EventTime=1; 
    TPDOList[2].DataCount=0; 

    Value=0x63001404; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[2].Data[TPDOList[2].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[2].DataCount++;} 

    Value=0x63001504; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[2].Data[TPDOList[2].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[2].DataCount++;} 



    //TPDO3
    TPDOList[3].enable=1; 
    TPDOList[3].COBID=0x209; 
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
    TPDOList[4].COBID=0x20a; 
    TPDOList[4].BusNumber=1; 
    TPDOList[4].EventTime=1; 
    TPDOList[4].DataCount=0; 

    Value=0x61010104; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[4].Data[TPDOList[4].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[4].DataCount++;} 

    Value=0x61010204; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[4].Data[TPDOList[4].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[4].DataCount++;} 



    //TPDO5
    TPDOList[5].enable=1; 
    TPDOList[5].COBID=0x20b; 
    TPDOList[5].BusNumber=1; 
    TPDOList[5].EventTime=1; 
    TPDOList[5].DataCount=0; 

    Value=0x61020104; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[5].Data[TPDOList[5].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[5].DataCount++;} 

    Value=0x61020204; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[5].Data[TPDOList[5].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[5].DataCount++;} 



    //TPDO6
    TPDOList[6].enable=1; 
    TPDOList[6].COBID=0x20c; 
    TPDOList[6].BusNumber=1; 
    TPDOList[6].EventTime=1; 
    TPDOList[6].DataCount=0; 

    Value=0x61030104; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[6].Data[TPDOList[6].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[6].DataCount++;} 

    Value=0x61030204; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[6].Data[TPDOList[6].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[6].DataCount++;} 



    //TPDO7
    TPDOList[7].enable=1; 
    TPDOList[7].COBID=0x210; 
    TPDOList[7].BusNumber=1; 
    TPDOList[7].EventTime=1; 
    TPDOList[7].DataCount=0; 

    Value=0x61040104; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[7].Data[TPDOList[7].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[7].DataCount++;} 

    Value=0x61040204; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[7].Data[TPDOList[7].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[7].DataCount++;} 



    //TPDO8
    TPDOList[8].enable=1; 
    TPDOList[8].COBID=0x20f; 
    TPDOList[8].BusNumber=1; 
    TPDOList[8].EventTime=1; 
    TPDOList[8].DataCount=0; 

    Value=0x61050104; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[8].Data[TPDOList[8].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[8].DataCount++;} 

    Value=0x61050204; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[8].Data[TPDOList[8].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[8].DataCount++;} 



    //TPDO9
    TPDOList[9].enable=1; 
    TPDOList[9].COBID=0x20e; 
    TPDOList[9].BusNumber=1; 
    TPDOList[9].EventTime=1; 
    TPDOList[9].DataCount=0; 

    Value=0x61060104; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[9].Data[TPDOList[9].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[9].DataCount++;} 

    Value=0x61060204; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[9].Data[TPDOList[9].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[9].DataCount++;} 



    //TPDO10
    TPDOList[10].enable=1; 
    TPDOList[10].COBID=0x20d; 
    TPDOList[10].BusNumber=1; 
    TPDOList[10].EventTime=1; 
    TPDOList[10].DataCount=0; 

    Value=0x61070104; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[10].Data[TPDOList[10].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[10].DataCount++;} 

    Value=0x61070204; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[10].Data[TPDOList[10].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[10].DataCount++;} 



    //TPDO11
    TPDOList[11].enable=1; 
    TPDOList[11].COBID=0x205; 
    TPDOList[11].BusNumber=3; 
    TPDOList[11].EventTime=3; 
    TPDOList[11].DataCount=0; 

    Value=0x66001404; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[11].Data[TPDOList[11].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[11].DataCount++;} 

    Value=0x66001504; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[11].Data[TPDOList[11].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[11].DataCount++;} 



    //TPDO12
    TPDOList[12].enable=1; 
    TPDOList[12].COBID=0x206; 
    TPDOList[12].BusNumber=3; 
    TPDOList[12].EventTime=3; 
    TPDOList[12].DataCount=0; 

    Value=0x66001404; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[12].Data[TPDOList[12].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[12].DataCount++;} 

    Value=0x66001504; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        TPDOList[12].Data[TPDOList[12].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        TPDOList[12].DataCount++;} 



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
    RPDOList[2].COBID=0x183; 
    RPDOList[2].BusNumber=0; 
    RPDOList[2].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[2].BusNumber], RPDOList[2].COBID, &RPDOList[2].RPDOHandle);

    Value=0x63001004; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[2].Data[RPDOList[2].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[2].DataCount++;} 

    Value=0x63001104; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[2].Data[RPDOList[2].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[2].DataCount++;} 



    //RPDO3
    RPDOList[3].enable=1; 
    RPDOList[3].COBID=0x189; 
    RPDOList[3].BusNumber=1; 
    RPDOList[3].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[3].BusNumber], RPDOList[3].COBID, &RPDOList[3].RPDOHandle);

    Value=0x61000304; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[3].Data[RPDOList[3].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[3].DataCount++;} 

    Value=0x61000404; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[3].Data[RPDOList[3].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[3].DataCount++;} 



    //RPDO4
    RPDOList[4].enable=1; 
    RPDOList[4].COBID=0x18a; 
    RPDOList[4].BusNumber=1; 
    RPDOList[4].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[4].BusNumber], RPDOList[4].COBID, &RPDOList[4].RPDOHandle);

    Value=0x61010304; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[4].Data[RPDOList[4].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[4].DataCount++;} 

    Value=0x61010404; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[4].Data[RPDOList[4].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[4].DataCount++;} 



    //RPDO5
    RPDOList[5].enable=1; 
    RPDOList[5].COBID=0x18b; 
    RPDOList[5].BusNumber=1; 
    RPDOList[5].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[5].BusNumber], RPDOList[5].COBID, &RPDOList[5].RPDOHandle);

    Value=0x61020304; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[5].Data[RPDOList[5].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[5].DataCount++;} 

    Value=0x61020404; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[5].Data[RPDOList[5].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[5].DataCount++;} 



    //RPDO6
    RPDOList[6].enable=1; 
    RPDOList[6].COBID=0x18c; 
    RPDOList[6].BusNumber=1; 
    RPDOList[6].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[6].BusNumber], RPDOList[6].COBID, &RPDOList[6].RPDOHandle);

    Value=0x61030304; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[6].Data[RPDOList[6].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[6].DataCount++;} 

    Value=0x61030404; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[6].Data[RPDOList[6].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[6].DataCount++;} 



    //RPDO7
    RPDOList[7].enable=1; 
    RPDOList[7].COBID=0x190; 
    RPDOList[7].BusNumber=1; 
    RPDOList[7].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[7].BusNumber], RPDOList[7].COBID, &RPDOList[7].RPDOHandle);

    Value=0x61040304; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[7].Data[RPDOList[7].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[7].DataCount++;} 

    Value=0x61040404; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[7].Data[RPDOList[7].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[7].DataCount++;} 



    //RPDO8
    RPDOList[8].enable=1; 
    RPDOList[8].COBID=0x18f; 
    RPDOList[8].BusNumber=1; 
    RPDOList[8].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[8].BusNumber], RPDOList[8].COBID, &RPDOList[8].RPDOHandle);

    Value=0x61050304; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[8].Data[RPDOList[8].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[8].DataCount++;} 

    Value=0x61050404; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[8].Data[RPDOList[8].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[8].DataCount++;} 



    //RPDO9
    RPDOList[9].enable=1; 
    RPDOList[9].COBID=0x18e; 
    RPDOList[9].BusNumber=1; 
    RPDOList[9].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[9].BusNumber], RPDOList[9].COBID, &RPDOList[9].RPDOHandle);

    Value=0x61060304; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[9].Data[RPDOList[9].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[9].DataCount++;} 

    Value=0x61060404; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[9].Data[RPDOList[9].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[9].DataCount++;} 



    //RPDO10
    RPDOList[10].enable=1; 
    RPDOList[10].COBID=0x18d; 
    RPDOList[10].BusNumber=1; 
    RPDOList[10].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[10].BusNumber], RPDOList[10].COBID, &RPDOList[10].RPDOHandle);

    Value=0x61070304; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[10].Data[RPDOList[10].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[10].DataCount++;} 

    Value=0x61070404; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[10].Data[RPDOList[10].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[10].DataCount++;} 



    //RPDO11
    RPDOList[11].enable=1; 
    RPDOList[11].COBID=0x185; 
    RPDOList[11].BusNumber=3; 
    RPDOList[11].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[11].BusNumber], RPDOList[11].COBID, &RPDOList[11].RPDOHandle);

    Value=0x66000804; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[11].Data[RPDOList[11].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[11].DataCount++;} 

    Value=0x66000904; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[11].Data[RPDOList[11].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[11].DataCount++;} 



    //RPDO12
    RPDOList[12].enable=1; 
    RPDOList[12].COBID=0x285; 
    RPDOList[12].BusNumber=3; 
    RPDOList[12].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[12].BusNumber], RPDOList[12].COBID, &RPDOList[12].RPDOHandle);

    Value=0x66000a04; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[12].Data[RPDOList[12].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[12].DataCount++;} 

    Value=0x66000b04; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[12].Data[RPDOList[12].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[12].DataCount++;} 



    //RPDO13
    RPDOList[13].enable=1; 
    RPDOList[13].COBID=0x385; 
    RPDOList[13].BusNumber=3; 
    RPDOList[13].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[13].BusNumber], RPDOList[13].COBID, &RPDOList[13].RPDOHandle);

    Value=0x66000c04; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[13].Data[RPDOList[13].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[13].DataCount++;} 

    Value=0x66000d04; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[13].Data[RPDOList[13].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[13].DataCount++;} 



    //RPDO14
    RPDOList[14].enable=1; 
    RPDOList[14].COBID=0x186; 
    RPDOList[14].BusNumber=3; 
    RPDOList[14].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[14].BusNumber], RPDOList[14].COBID, &RPDOList[14].RPDOHandle);

    Value=0x66000e04; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[14].Data[RPDOList[14].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[14].DataCount++;} 

    Value=0x66000f04; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[14].Data[RPDOList[14].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[14].DataCount++;} 



    //RPDO15
    RPDOList[15].enable=1; 
    RPDOList[15].COBID=0x286; 
    RPDOList[15].BusNumber=3; 
    RPDOList[15].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[15].BusNumber], RPDOList[15].COBID, &RPDOList[15].RPDOHandle);

    Value=0x66001004; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[15].Data[RPDOList[15].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[15].DataCount++;} 

    Value=0x66001104; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[15].Data[RPDOList[15].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[15].DataCount++;} 



    //RPDO16
    RPDOList[16].enable=1; 
    RPDOList[16].COBID=0x386; 
    RPDOList[16].BusNumber=3; 
    RPDOList[16].DataCount=0; 
    col2_pdo_register(mpv_Bus[RPDOList[16].BusNumber], RPDOList[16].COBID, &RPDOList[16].RPDOHandle);

    Value=0x66001204; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[16].Data[RPDOList[16].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[16].DataCount++;} 

    Value=0x66001304; 
    Index=(uint16)((Value&0xffff0000)>>16); 
    Subindex=(uint16)((Value&0x0000ff00)>>8); 
    tmp = (uint16)(Value & 0x000000ff); 
    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); 
    for(iByte=0;iByte<tmp;iByte++){
        RPDOList[16].Data[RPDOList[16].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; 
        RPDOList[16].DataCount++;} 



}