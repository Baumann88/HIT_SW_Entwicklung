#ifndef _DEVICEOD_H
#define _DEVICEOD_H
#include "CANopenComm.h"
#include "ODContent.h"
#include "ODInfo.h"

/*====================================================================
Enum Type definition
====================================================================*/
enum OD_Opt{
    GetOD,
    SetOD,
    StoreODToEEP,
    LoadODFromEEP,
};

/*====================================================================
Format Definition
====================================================================*/
#define TypeS8                       0
#define TypeU8                       1
#define TypeS16                      2
#define TypeU16                      3
#define TypeU32                      4
#define TypeS32                      5
#define TypeF32                      6

/*====================================================================
OD Definition
====================================================================*/
//--1. Data memory of the object dictionary--
extern uint32 ODMem[ODMemLength];
//--2. Memory mapping for object dictionary--
/*-------------------------------------------
ODMemMapList
line 1: Index of the object dictionary
line 2: Number of the subindex's entry
-------------------------------------------*/
//-------------------------------------------
extern uint16 ODMemMapList[2][ODMemMapListLength];

/*====================================================================
Function Definition
====================================================================*/
void ODMemInit(void);
sint16 GetSetOD(uint16 index,uint8 subindex,uint16 *Addr, uint32 *value, enum OD_Opt opt);
sint16 StoreLoadOD(uint16 index,uint8 subindex,enum OD_Opt opt);
void* BindODMem(uint16 index,uint8 subindex,uint16 DataType,uint16 Pos);


#endif
