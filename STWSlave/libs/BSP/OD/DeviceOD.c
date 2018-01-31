#include "eep_memmap.h"
#include "eep_Manage.h"
#include "DeviceOD.h"

//---internal variable of the OD ------------------------------------------------------------------
//--1. Data memory of the object dictionary--
uint32 ODMem[ODMemLength];
//--2. Memory mapping for object dictionary--
/*-------------------------------------------
ODMemMapList
line 1: Index of the object dictionary
line 2: Number of the subindex's entry
-------------------------------------------*/
//-------------------------------------------
uint16 ODMemMapList[2][ODMemMapListLength];

//=================================================================================================
/*!
    Function: Initialize the memory mapping list
*/
//=================================================================================================
void ODMemInit(void){
    uint16 i;
    uint16 count=0;

    ODMemMapList[0][0]=DevParaStartIndex;
    ODMemMapList[1][0]=NrEntryDevPara;
    count++;

    #ifdef DriveModuleStartIndex
    ODMemMapList[0][count]=DriveModuleStartIndex;
    ODMemMapList[1][count]=NrEntryDriveModule;
    count++;
    #endif

    #ifdef InverterStartIndex
    for(i=0;i<NrOfMotorInverter;i++){
        ODMemMapList[0][count]=InverterStartIndex+i;
        ODMemMapList[1][count]=NrEntryInverter;
        count++;
    }
    #endif

    #ifdef IOPortStartIndex
    ODMemMapList[0][count]=IOPortStartIndex;
    ODMemMapList[1][count]=NrEntryIOPort;
    count++;
    #endif

    #ifdef RemoteControlStartIndex
    ODMemMapList[0][count]=RemoteControlStartIndex;
    ODMemMapList[1][count]=NrEntryRemoteControl;
    count++;
    #endif

    #ifdef HubSystemStartIndex
    ODMemMapList[0][count]=HubSystemStartIndex;
    ODMemMapList[1][count]=NrEntryHubSystem;
    count++;
    #endif

    #ifdef SafetyStartIndex
    ODMemMapList[0][count]=SafetyStartIndex;
    ODMemMapList[1][count]=NrEntrySafety;
    count++;
    #endif

    #ifdef AutoDriveStartIndex
    ODMemMapList[0][count]=AutoDriveStartIndex;
    ODMemMapList[1][count]=NrEntryAutoDrive;
    count++;
    #endif

    for(i=0;i<ODMemLength;i++){
        ODMem[i]=0;
    }
}

//=================================================================================================
/*!
    Function: Get or set the value in the object dictionary
    input: 1. uint16  index: Index of the object dictionary
           2. uint8 suindex: Subindex of the object dictionary
           3. uint16 *Addr: Address of the inquire value in object dictionary
           4. uint32 *value: Value which must be get from or set into the object dictionary
           5. OD_Opt    opt: Set or get the value from the object dictionary

    output: Error code
*/
//=================================================================================================
sint16 GetSetOD(uint16 index,uint8 subindex,uint16 *Addr, uint32 *value, enum OD_Opt opt){
    uint16 ODMemAddr=0;
    uint16 SubIdxRelAddr;
    uint16 iODIndex;
    uint8 i;

    SubIdxRelAddr=(uint16)subindex;
    for(iODIndex=0;iODIndex<ODMemMapListLength;iODIndex++){
        if(ODMemMapList[0][iODIndex]==index){
            for(i=0x00;i<ODMemMapList[1][iODIndex];i++){
                    if(i==SubIdxRelAddr){
                        if(opt==GetOD)
                            *value=ODMem[ODMemAddr];
                        else if(opt==SetOD)
                            ODMem[ODMemAddr]=*value;
                        *Addr=ODMemAddr;
                        return C_NO_ERR;
                    }
                ODMemAddr++;
            }
            return C_RANGE;
        }
        ODMemAddr+=ODMemMapList[1][iODIndex];
    }
    return C_RANGE;
}

//=================================================================================================
/*!
    Function: Store or Load the value in Object Dictionary to or from the EEPROM
    input: 1. uint16 index: Index of the object dictionary, when this value=0x0000, the whole
                            object dictionary was stored or loaded
           2. uint8 subindex: Subindex of the object dictionary.
           3. OD_Opt    opt: Store or load the value in Object Dictionary to or from the EEPROM.

    output: Error code
*/
//=================================================================================================
sint16 StoreLoadOD(uint16 index,uint8 subindex,enum OD_Opt opt){
    uint16 ODMemAddr;
    uint16 SizeOfDataType=4;
    uint16 i;
    uint32 Data;
    sint16 errcode=0;
    uint16 StoreLength;

    StoreLength=ODMemLength;
    if(index==0){
        for(i=0;i<StoreLength;i++){
            if(opt==StoreODToEEP)
                errcode=EEPDataStore(ODMem[i],SizeOfDataType,CANOpenEEPStartAddr+i*SizeOfDataType);
            else if(opt==LoadODFromEEP)
                errcode=EEPDataLoad(&ODMem[i],SizeOfDataType,CANOpenEEPStartAddr+i*SizeOfDataType);
            if(errcode!=C_NO_ERR)
                return errcode;
        }
    }
    else{
        if(opt==StoreODToEEP){
            errcode=GetSetOD(index,subindex,&ODMemAddr,&Data,GetOD);
            if(errcode!=C_NO_ERR)
                return errcode;
            errcode=EEPDataStore(Data,SizeOfDataType,CANOpenEEPStartAddr+ODMemAddr*SizeOfDataType);
            if(errcode!=C_NO_ERR)
                return errcode;
        }
        else if(opt==LoadODFromEEP){
            errcode=GetSetOD(index,subindex,&ODMemAddr,&Data,GetOD);
            if(errcode!=C_NO_ERR)
                return errcode;
            errcode=EEPDataLoad(&Data,SizeOfDataType,CANOpenEEPStartAddr+ODMemAddr*SizeOfDataType);
            if(errcode!=C_NO_ERR)
                return errcode;
            errcode=GetSetOD(index,subindex,&ODMemAddr,&Data,SetOD);
            if(errcode!=C_NO_ERR)
                return errcode;
        }
    }
    return 0;
}

//=================================================================================================
/*!
    Function: Bind the Object Dictionary with the Interface.
    output: Address of this Object Dictionary
*/
//=================================================================================================
void* BindODMem(uint16 index,uint8 subindex,uint16 DataType,uint16 Pos){
    uint32 value;
    uint16 ODMemAddr;

    GetSetOD(index,subindex,&ODMemAddr,&value,GetOD);

    switch(DataType){
        case 0: return (sint8 *)&ODMem[ODMemAddr]+Pos;
        case 1: return (uint8 *)&ODMem[ODMemAddr]+Pos;
        case 2: return (sint16 *)&ODMem[ODMemAddr]+Pos;
        case 3: return (uint16 *)&ODMem[ODMemAddr]+Pos;
        case 4: return &ODMem[ODMemAddr];
        case 5: return (sint32 *)&ODMem[ODMemAddr];
        case 6: return (float32 *)&ODMem[ODMemAddr];
        default:return 0;
    }
}
