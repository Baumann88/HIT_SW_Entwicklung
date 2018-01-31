#include "MultiIO.h"

//Pin | Configuration
uint16 inputConfig[NumOfInput][2]={
X_IN_01,InputCfgVoltage10V, //Main Board Input1
X_IN_02,InputCfgVoltage10V, //Main Board Input2
X_IN_03,InputCfgVoltage10V,  //Main Board Input3
X_IN_04,InputCfgVoltage10V,  //Main Board Input4
X_IN_05,InputCfgNoCfg,  //Main Board Input5
X_IN_06,InputCfgNoCfg,  //Main Board Input6
X_IN_07,InputCfgNoCfg,  //Main Board Input7
X_IN_08,InputCfgNoCfg,  //Main Board Input8
X_IN_09,InputCfgCurrent,  //Main Board Input9
X_IN_10,InputCfgCurrent,  //Main Board Input10
X_IN_11,InputCfgCurrent,  //Main Board Input11
X_IN_12,InputCfgCurrent,  //Main Board Input12
X_IN_13,InputCfgCurrent,  //Main Board Input13
X_IN_14,InputCfgCurrent,  //Main Board Input14
X_IN_15,InputCfgNoCfg,  //Main Board Input15
X05_IN_01,InputCfgNoCfg,  //SlotA Extern Board 05 Input36
X05_IN_02,InputCfgNoCfg,  //SlotA Extern Board 05 Input37
X05_IN_03,InputCfgNoCfg,  //SlotA Extern Board 05 Input38
X05_IN_04,InputCfgNoCfg  //SlotA Extern Board 05 Input39
};

sint32 inputFilterCfg[15]={
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0
};


//Pin | Configuration
uint16 outputConfig[NumOfOutput][2]={
X_OUT_01,OutputCfgPWM,  //Main Board Output1
X_OUT_02,OutputCfgPWM,  //Main Board Output2
X_OUT_03,OutputCfgPWM,  //Main Board Output3
X_OUT_04,OutputCfgPWM,  //Main Board Output4
X_OUT_05,OutputCfgPWM,  //Main Board Output5
X_OUT_06,OutputCfgPWM,  //Main Board Output6
X_OUT_07,OutputCfgPWM,  //Main Board Output7
X_OUT_08,OutputCfgPWM,  //Main Board Output8
X05_OUT_01,OutputCfgDigital,  //SlotB Extern Board 05 Output24
X05_OUT_02,OutputCfgDigital,  //SlotB Extern Board 05 Output25
X05_OUT_03,OutputCfgDigital,  //SlotB Extern Board 05 Output26
X05_OUT_04,OutputCfgNoCfg,  //SlotB Extern Board 05 Output27
X05_OUT_05,OutputCfgNoCfg,  //SlotB Extern Board 05 Output28
X05_OUT_06,OutputCfgNoCfg,  //SlotB Extern Board 05 Output29
X05_OUT_07,OutputCfgDigital,  //SlotB Extern Board 05 Output30
X05_OUT_08,OutputCfgDigital  //SlotB Extern Board 05 Output31
};
