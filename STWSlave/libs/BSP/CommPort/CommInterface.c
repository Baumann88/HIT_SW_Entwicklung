#include "CANopenComm.h"
#include "DeviceOD.h"
#include "CommInterface.h"
#include "AppConfig.h"

#define DefaultInterfaceEventTime       80

void InitTaskCommInterface(void){
    CANopenCommInit();
}

void TaskCommInterface(void){
    TaskCANopen();
}



