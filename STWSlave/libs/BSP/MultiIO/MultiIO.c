#include "MultiIO.h"

#define SensorReferenceVolt      10000

static uint32 *IOPortInputArray[NumOfInput];
static uint32 *IOPortOutputArray[NumOfOutput];

#define InputCfgNoCfg               0x0000
#define InputCfgDigital             0x0001
#define InputCfgVoltage5V           0x0002
#define InputCfgVoltage10V          0x0003
#define InputCfgVoltage40V          0x0004
#define InputCfgCurrent             0x0005
#define InputCfgEventRising         0x0006
#define InputCfgEventFalling        0x0007
#define InputCfgEventBoth           0x0008
#define InputCfgFrequez             0x0009
#define InputCfgIncremental         0x000a

#define OutputCfgNoCfg              0x0000
#define OutputCfgDigital            0x0001
#define OutputCfgPWM                0x0002
#define OutputCfgCurrent            0x0003

//=================================================================================================
/*!
    Function: Initial IO Port of Main Board
    output: None
*/
//=================================================================================================
void MultiIOMainBoardInit(void){
    uint16 iPort;
    x_sys_set_sensor_supply(X_SYS_SENSOR_SUPPLY_01, SensorReferenceVolt);
    x_out_relay_set_all(X_ON);

    //Input Initial
    iPort=0;
    while(iPort<15){
        switch (inputConfig[iPort][1]){
            case InputCfgDigital:
                x_in_init(inputConfig[iPort][0],X_IN_TYPE_DIGITAL,0,(X_IN_CIRCUIT_ACTIVE_HIGH|X_IN_CIRCUIT_PULL_DOWN),0,NULL);
                *IOPortInputArray[iPort]=(uint32)InputCfgDigital<<16;
                break;
            case InputCfgVoltage10V:
                x_in_init(inputConfig[iPort][0], X_IN_TYPE_VOLTAGE_10V, inputFilterCfg[iPort], 0u, 0u, NULL);
                *IOPortInputArray[iPort]=(uint32)InputCfgVoltage10V<<16;
                break;
            case InputCfgCurrent:
                x_in_init(inputConfig[iPort][0], X_IN_TYPE_CURRENT, 0u, 0u, 0u, NULL);
                *IOPortInputArray[iPort]=(uint32)InputCfgCurrent<<16;
                break;
            case InputCfgNoCfg:
                *IOPortInputArray[iPort]=(uint32)InputCfgNoCfg<<16;
                break;
        }
        iPort++;
    }
    iPort=0;
    //Output Initial
    while(iPort<8){
        switch (outputConfig[iPort][1]){
            case OutputCfgDigital:
                x_out_init(outputConfig[iPort][0], X_OUT_TYPE_DIGITAL, 0u, 0u, NULL);
                *IOPortOutputArray[iPort]=(uint32)OutputCfgDigital<<16;
                break;
            case OutputCfgPWM:
                x_out_init(outputConfig[iPort][0], X_OUT_TYPE_PWM, 10000u, 0u, NULL);
                *IOPortOutputArray[iPort]=(uint32)OutputCfgPWM<<16;
                break;
            case OutputCfgNoCfg:
                *IOPortOutputArray[iPort]=(uint32)OutputCfgNoCfg<<16;
                break;
        }
        iPort++;
    }
}

//=================================================================================================
/*!
    Function: Initial IO Port of Extern Board 05
    output: None
*/
//=================================================================================================
void MultiIOEB05Init(void){
    uint16 iPort;
    iPort=15;
    x05_out_set_relay (X_EXPBOARD_SLOT_A, X05_OUT_RELAY_01, X05_ON);
    //Input Initial
    while(iPort<NumOfInput){
        if(inputConfig[iPort][1]!=InputCfgNoCfg){
            x05_in_init(X_EXPBOARD_SLOT_A,inputConfig[iPort][0],X05_IN_TYPE_DIGITAL,0,(X05_IN_CIRCUIT_ACTIVE_HIGH|X05_IN_CIRCUIT_PULL_DOWN),0,NULL);
            *IOPortInputArray[iPort]=(uint32)InputCfgDigital<<16;
        }
        else
            *IOPortInputArray[iPort]=(uint32)InputCfgNoCfg<<16;
        iPort++;
    }
    //Output Initial
    iPort=8;
    while(iPort<NumOfOutput){
        if(outputConfig[iPort][1]!=OutputCfgNoCfg){
            x05_out_init(X_EXPBOARD_SLOT_A,outputConfig[iPort][0],X05_OUT_TYPE_DIGITAL,0,0,NULL);
            *IOPortOutputArray[iPort]=(uint32)OutputCfgDigital<<16;
        }
        else
            *IOPortOutputArray[iPort]=(uint32)OutputCfgNoCfg<<16;
        iPort++;
    }
}

//=================================================================================================
/*!
    Function: Filter with mean calculate
    output: None
*/
//=================================================================================================
sint16 meanFilter(uint16 inputNum, sint32 Value, sint32 *outputValue){
    if(inputNum>=16) return -1;
    *outputValue=(inputFilterCfg[inputNum]+Value)/2;
    inputFilterCfg[inputNum]=*outputValue;
    return 0;
}

//=================================================================================================
/*!
    Function: this is a Task of the I/O Port
    output: None
*/
//=================================================================================================
void Task_IOPort(void* argv){
    uint16 flag;
    uint16 iPort;
    sint32 DIValue;
    sint32 TmpValue;
    argv=argv;
    uint16 tmpCFGType;

    flag=0;

    while(TRUE){
        if(flag==0){
            for(iPort=0;iPort<15;iPort++){
                tmpCFGType=(uint16)((*IOPortInputArray[iPort]&0x00ff0000)>>16);
                if(tmpCFGType==InputCfgNoCfg) continue;
                x_in_get_value(inputConfig[iPort][0],&DIValue);
                meanFilter(iPort, DIValue, &TmpValue);
                *IOPortInputArray[iPort]&=0xffff0000;
                *IOPortInputArray[iPort]+=(uint32)TmpValue;
            }
            for(iPort=0;iPort<8;iPort++){
                tmpCFGType=(uint16)((*IOPortOutputArray[iPort]&0x00ff0000)>>16);
                if(tmpCFGType==OutputCfgNoCfg) continue;
                DIValue=(sint32)(*IOPortOutputArray[iPort]&0x0000ffff);
                x_out_set_value (outputConfig[iPort][0], DIValue);
            }
        }
        else if(flag==1){
            for(iPort=15;iPort<NumOfInput;iPort++){
                tmpCFGType=(uint16)((*IOPortInputArray[iPort]&0x00ff0000)>>16);
                if(tmpCFGType==InputCfgNoCfg) continue;
                x05_in_get_value(X_EXPBOARD_SLOT_A, inputConfig[iPort][0] ,&DIValue);
                *IOPortInputArray[iPort]&=0xffff0000;
                *IOPortInputArray[iPort]+=(uint32)DIValue;
            }
            for(iPort=8;iPort<NumOfOutput;iPort++){
                tmpCFGType=(uint16)((*IOPortOutputArray[iPort]&0x00ff0000)>>16);
                if(tmpCFGType==OutputCfgNoCfg) continue;
                DIValue=(sint32)(*IOPortOutputArray[iPort]&0x0000ffff);
                x05_out_set_value(X_EXPBOARD_SLOT_A, outputConfig[iPort][0], DIValue);
            }
        }
        flag++;
        if(flag==2) flag=0;

        x_os_wait_for_events();
    }
}

//=================================================================================================
/*!
    Function: Initial IO Port
    output: None
*/
//=================================================================================================
void InitMultiIO(void){
    uint8 i;
    uint8 StartSubindex;

    //Input
    StartSubindex=SubindexInput01;
    for(i=0;i<NumOfInput;i++){
        IOPortInputArray[i]=BindODMem(IOPortStartIndex,StartSubindex+i,TypeU32,0);
        *IOPortInputArray[i]=0x00000000;
    }

    //output
    StartSubindex=SubindexOutput01;
    for(i=0;i<NumOfOutput;i++){
        IOPortOutputArray[i]=BindODMem(IOPortStartIndex,StartSubindex+i,TypeU32,0);
        *IOPortOutputArray[i]=0x00000000;
    }

    MultiIOMainBoardInit();
    MultiIOEB05Init();
    x_os_install_task(PrioIOPort, 2, 1, Task_IOPort, 256);
}













