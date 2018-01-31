#include "eep_Manage.h"
#include "stwtypes.h"
#include "x_eep.h"

sint16 EEPDataStore(uint32 Value, uint16 NByte, uint32 EEPAddr){
    int i;
    uint8 Data[NByte];

    for(i=0;i<NByte;i++){
        Data[i]=(uint8)((Value>>8*i)&0xff);
    }
    return x_eep_write(EEPAddr,NByte,&Data[0]);
}

sint16 EEPDataLoad(uint32 *Value, uint16 NByte, uint32 EEPAddr){
    int i;
    uint8 Data[NByte];
    uint32 tmp=0;
    uint16 errcode;

    errcode=x_eep_read (EEPAddr,NByte,&Data[0]);
    for(i=0;i<NByte;i++){
        tmp=tmp+((uint32)Data[NByte-1-i]<<8*(NByte-1-i));
    }
    *Value=tmp;
    return errcode;
}


