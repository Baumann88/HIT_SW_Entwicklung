#include "DataManage.h"

static uint32 DataPool[32];

static uint16 ErrorList[32];
static uint16 WarnList[16];

void* BindDataPool(uint16 ParaId, uint16 DataType, uint16 Pos){
    switch(DataType){
        case 0: return (sint8 *)&DataPool[ParaId]+Pos;
        case 1: return (uint8 *)&DataPool[ParaId]+Pos;
        case 2: return (sint16 *)&DataPool[ParaId]+Pos;
        case 3: return (uint16 *)&DataPool[ParaId]+Pos;
        case 4: return &DataPool[ParaId];
        case 5: return (sint32 *)&DataPool[ParaId];
        case 6: return (float32 *)&DataPool[ParaId];
    }
}
