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
X_IN_09,InputCfgNoCfg,  //Main Board Input9
X_IN_10,InputCfgNoCfg,  //Main Board Input10
X_IN_11,InputCfgNoCfg,  //Main Board Input11
X_IN_12,InputCfgNoCfg,  //Main Board Input12
X_IN_13,InputCfgNoCfg,  //Main Board Input13
X_IN_14,InputCfgNoCfg,  //Main Board Input14
X_IN_15,InputCfgNoCfg,  //Main Board Input15
X02_IN_01,InputCfgDigital,  //SlotA Extern Board 02 Input28
X02_IN_02,InputCfgDigital,  //SlotA Extern Board 02 Input29
X02_IN_03,InputCfgDigital,  //SlotA Extern Board 02 Input30
X02_IN_04,InputCfgDigital,  //SlotA Extern Board 02 Input31
X02_IN_05,InputCfgDigital,  //SlotA Extern Board 02 Input32
X02_IN_06,InputCfgDigital,  //SlotA Extern Board 02 Input33
X02_IN_07,InputCfgDigital,  //SlotA Extern Board 02 Input34
X02_IN_08,InputCfgDigital,  //SlotA Extern Board 02 Input35
X02_IN_09,InputCfgDigital,  //SlotA Extern Board 02 Input36
X02_IN_10,InputCfgDigital,  //SlotA Extern Board 02 Input37
X02_IN_11,InputCfgDigital,  //SlotA Extern Board 02 Input38
X02_IN_12,InputCfgDigital,  //SlotA Extern Board 02 Input39
X02_IN_01,InputCfgDigital,  //SlotB Extern Board 02 Input41
X02_IN_02,InputCfgDigital,  //SlotB Extern Board 02 Input42
X02_IN_03,InputCfgDigital,  //SlotB Extern Board 02 Input43
X02_IN_04,InputCfgDigital,  //SlotB Extern Board 02 Input44
X02_IN_05,InputCfgDigital,  //SlotB Extern Board 02 Input45
X02_IN_06,InputCfgDigital,  //SlotB Extern Board 02 Input46
X02_IN_07,InputCfgDigital,  //SlotB Extern Board 02 Input47
X02_IN_08,InputCfgDigital,  //SlotB Extern Board 02 Input48
X02_IN_09,InputCfgDigital,  //SlotB Extern Board 02 Input49
X02_IN_10,InputCfgDigital,  //SlotB Extern Board 02 Input50
X02_IN_11,InputCfgDigital,  //SlotB Extern Board 02 Input51
X02_IN_12,InputCfgDigital,  //SlotB Extern Board 02 Input52
X05_IN_01,InputCfgNoCfg,  //SlotC Extern Board 05 Input62
X05_IN_02,InputCfgNoCfg,  //SlotC Extern Board 05 Input63
X05_IN_03,InputCfgNoCfg,  //SlotC Extern Board 05 Input64
X05_IN_04,InputCfgNoCfg  //SlotC Extern Board 05 Input65
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
X_OUT_01,OutputCfgDigital,  //Main Board Output1
X_OUT_02,OutputCfgNoCfg,  //Main Board Output2
X_OUT_03,OutputCfgNoCfg,  //Main Board Output3
X_OUT_04,OutputCfgNoCfg,  //Main Board Output4
X_OUT_05,OutputCfgNoCfg,  //Main Board Output5
X_OUT_06,OutputCfgNoCfg,  //Main Board Output6
X_OUT_07,OutputCfgDigital,  //Main Board Output7
X_OUT_08,OutputCfgNoCfg,  //Main Board Output8
X02_OUT_01,OutputCfgDigital,  //SlotA Extern Board 02 Output36
X02_OUT_01,OutputCfgDigital,  //SlotB Extern Board 02 Output49
X05_OUT_01,OutputCfgDigital,  //SlotB Extern Board 05 Output50
X05_OUT_02,OutputCfgDigital,  //SlotB Extern Board 05 Output51
X05_OUT_03,OutputCfgNoCfg,  //SlotB Extern Board 05 Output52
X05_OUT_04,OutputCfgDigital,  //SlotB Extern Board 05 Output53
X05_OUT_05,OutputCfgDigital,  //SlotB Extern Board 05 Output54
X05_OUT_06,OutputCfgDigital,  //SlotB Extern Board 05 Output55
X05_OUT_07,OutputCfgDigital,  //SlotB Extern Board 05 Output56
X05_OUT_08,OutputCfgDigital  //SlotB Extern Board 05 Output57
};
