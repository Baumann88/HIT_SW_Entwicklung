//-----------------------------------------------------------------------------
/*!
   \internal
   \file
   \brief       J1939 PGN processing module

   Define the Pararameter Groups

   \implementation
   project     J1939 Protocolstack
   copyright   STW (c) 2010
   license     use only under terms of contract / confidential

   created     21.04.2010  STW/M.Greiner
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)   Author           Description
   21.04.2010         STW/M.Greiner    file created
   \endhistory
*/
//------------------------------------------------------------------------------


#ifndef _J1939_PGN_H_                      // Avoid multiple/recursive inclusion
#define _J1939_PGN_H_


// -- Includes ----------------------------------------------------------------
#include "stwtypes.h"


#if defined(__cplusplus)
extern "C" {     // Make sure we have C-declarations in C++ programs
#endif


// -- Defines -----------------------------------------------------------------
#define J1939_PGN_TSC1       (uint32)0x0000U          // TSC1   PGN
#define J1939_PGN_TC1        (uint32)0x0100U          // TC1    PGN
#define J1939_PGN_XBR        (uint32)0x0400U          // XBR    PGN
#define J1939_PGN_ERC1       (uint32)0xF000U          // ERC1   PGN
#define J1939_PGN_EEC1       (uint32)0xF004U          // EEC1   PGN
#define J1939_PGN_EEC2       (uint32)0xF003U          // EEC2   PGN
#define J1939_PGN_ET1        (uint32)0xFEEEU          // ET1    PGN
#define J1939_PGN_HOURS      (uint32)0xFEE5U          // HOURS  PGN
#define J1939_PGN_EFLP1      (uint32)0xFEEFU          // EFL/P1 PGN
#define J1939_PGN_LFE        (uint32)0xFEF2U          // LFE    PGN
#define J1939_PGN_AMB        (uint32)0xFEF5U          // AMB    PGN
#define J1939_PGN_CCVS       (uint32)0xFEF1U          // CCVS   PGN
#define J1939_PGN_VEP1       (uint32)0xFEF7U          // VEP1   PGN
#define J1939_PGN_IC1        (uint32)0xFEF6U          // IC1    PGN
#define J1939_PGN_TRF1       (uint32)0xFEF8U          // TRF1   PGN
#define J1939_PGN_TI1        (uint32)0xFE56U          // TI1    PGN
#define J1939_PGN_WFI        (uint32)0xFEFFU          // WFI    PGN
#define J1939_PGN_RF         (uint32)0xFEFBU          // RF     PGN
#define J1939_PGN_DD         (uint32)0xFEFCU          // DD     PGN
#define J1939_PGN_CTL        (uint32)0xCF00U          // CTL    PGN


// -- Types -------------------------------------------------------------------
typedef struct
{
   uint8 u8_ValidDataFlag;                            // for Rx PGs: TRUE if data received in the specified cycle time
                                                      //     Tx PGs: TRUE enable cyclic sending
   uint8 u8_NewDataFlag;                              // for Rx PGs: TRUE new data received (application must clear)
                                                      //     Tx PGs: TRUE trigger sending of non cyclic PGs (stack clear after each send)
}
T_J1939_PG_ctrl;                                      // control/state informations for PG

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8  u8_OverrideControlMode;                     // SPN 695: 2 Bits
   uint8  u8_RequestedSpeedCntrlConditions;           // SPN 696: 2 Bits
   uint8  u8_OverrideCntrlModePriority;               // SPN 897: 2 Bits
   uint16 u16_RequestedSpeedLimit;                    // SPN 898: 2 Bytes, 0.125rpm / bit
   uint8  u8_RequestedTorqueLimit;                    // SPN 518: 1 Byte,  1% / bit
   // --- scaled parameter ---
   uint16 u16_RequestedSpeedLimit_rpm;                // SPN 898: [0 .. 8031]rpm
   sint8  s8_RequestedTorqueLimit_perc;               // SPN 518: [-125 .. +125]%
}
T_J1939_PGN_TSC1;                                     // Torque/Speed Control

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8  u8_GearShiftInhibitRequest;                 // SPN 681:  2 Bits
   uint8  u8_TorqueConvertLockupDisableRequest;       // SPN 682:  2 Bits
   uint8  u8_DisengageDrivelineRequest;               // SPN 683:  2 Bits
   uint8  u8_RequestedPercentClutchSlip;              // SPN 684:  1 Byte, 0.4% / bit
   uint8  u8_RequestedGear;                           // SPN 525:  1 Byte, 1GearValue / bit
   uint8  u8_DisengDifferentLockReqFrntAx1;           // SPN 685:  2 Bits
   uint8  u8_DisengDifferentLockReqFrntAx2;           // SPN 686:  2 Bits
   uint8  u8_DisengDifferentLockReqRearAx1;           // SPN 687:  2 Bits
   uint8  u8_DisengDifferentLockReqRearAx2;           // SPN 688:  2 Bits
   uint8  u8_DisengDifferentLockReqCentral;           // SPN 689:  2 Bits
   uint8  u8_DisengDifferentLockReqCentralFrnt;       // SPN 690:  2 Bits
   uint8  u8_DisengDifferentLockReqCentralRear;       // SPN 691:  2 Bits
   // --- scaled parameter ---
   uint16 u16_RequestedPercentClutchSlip_permill;     // SPN 684:  [0 .. 1000]%%
   sint8  s8_RequestedGear_gv;                        // SPN 525:  [-125 .. +125]GearValue
}
T_J1939_PGN_TC1;                                      // Transmission Control

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint16 u16_ExternalAccelerationDemand;             // SPN 2920: 2 Bytes, 1/2048(m/s^2) / bit
   uint8  u8_XBREBIMode;                              // SPN 2914: 2 Bits
   uint8  u8_XBRPriority;                             // SPN 2915: 2 Bits
   uint8  u8_XBRControlMode;                          // SPN 2916: 2 Bits
   uint8  u8_XBRMessageCounter;                       // SPN 3189: 4 Bits
   uint8  u8_XBRMessageChecksum;                      // SPN 3188: 4 Bits
   // --- scaled parameter ---
   sint16 s16_ExternalAccelerationDemand_mm_s2;       // SPN 2920: [-15687 .. +15687]mm/s^2
}
T_J1939_PGN_XBR;                                      // External Brake Request

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8  u8_RetarderTorqueMode;                      // SPN 900:  4 Bits
   uint8  u8_RetarderEnableBrakeAssistSwitch;         // SPN 571:  2 Bits
   uint8  u8_RetarderEnableShiftAssistSwitch;         // SPN 572:  2 Bits
   uint8  u8_ActualRetarderPercentTorque;             // SPN 520:  1 Byte, 1% / bit
   uint8  u8_IntendedRetarderPercentTorque;           // SPN 1085: 1 Byte, 1% / bit
   uint8  u8_EngineCoolantLoadIncrease;               // SPN 1082: 2 Bits
   uint8  u8_RetarderRequestingBrakeLight;            // SPN 1667: 2 Bits
   uint8  u8_SrcAddrOfCntrlDeviceForRetCntrl;         // SPN 1480: 1 Byte
   uint8  u8_DriversDemandRetarderPercTorq;           // SPN 1715: 1 Byte, 1% / bit
   uint8  u8_RetarderSelectionNonEngine;              // SPN 1716: 1 Byte, 0.4% / bit
   uint8  u8_ActMaxAvlblRetarderPercTorque;           // SPN 1717: 1 Byte, 1% / bit
   // --- scaled parameter ---
   sint8  s8_ActualRetarderPercentTorque_perc;        // SPN 520:  [-125 .. +125]%
   sint8  s8_IntendedRetarderPercentTorque_perc;      // SPN 1085: [-125 .. +125]%
   sint8  s8_DriversDemandRetarderPercTorq_perc;      // SPN 1715: [-125 .. +125]%
   uint16 u16_RetarderSelectionNonEngine_permill;     // SPN 1716: [0 .. 1000]%%
   sint8  s8_ActMaxAvlblRetarderPercTorque_perc;      // SPN 1717: [-125 .. +125]%
}
T_J1939_PGN_ERC1;                                     // Electronic Retarder Controller 1

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8  u8_EngineTorqueMode;                        // SPN 899:  4 Bits
   uint8  u8_DrvrDemandEngPercTorque;                 // SPN 512:  1 Byte,  1% / bit
   uint8  u8_ActualEngPercentTorque;                  // SPN 513:  1 Byte,  1% / bit
   uint16 u16_EngineSpeed;                            // SPN 190:  2 Bytes, 0.125rpm / bit
   uint8  u8_SrcAddrCtrlDevEngCtrl;                   // SPN 1483: 1 Byte
   uint8  u8_EngineStarterMode;                       // SPN 1675: 4 Bits
   // --- scaled parameter ---
   sint8  s8_DrvrDemandEngPercTorque_perc;            // SPN 512:  [-125 .. +125]%
   sint8  s8_ActualEngPercentTorque_perc;             // SPN 513:  [-125 .. +125]%
   uint16 u16_EngineSpeed_rpm;                        // SPN 190:  [0 .. 8031]rpm
}
T_J1939_PGN_EEC1;                                     //PGN Electronic Engine Controller 1

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8  u8_AcceleratorPedal1LowIdleSwitch;          // SPN 558:  2 Bits
   uint8  u8_AcceleratorPedalKickdownSwitch;          // SPN 559:  2 Bits
   uint8  u8_RoadSpeedLimitStatus;                    // SPN 1437: 2 Bits
   uint8  u8_AcceleratorPedal2LowIdleSwitch;          // SPN 2970: 2 Bits
   uint8  u8_AcceleratorPedalPosition1;               // SPN 91:   1 Byte, 0.4% / bit
   uint8  u8_EnginePercLoadAtCurrentSpeed;            // SPN 92:   1 Byte
   uint8  u8_RemoteAcceleratorPedalPosition;          // SPN 974:  1 Byte, 0.4% / bit
   uint8  u8_AcceleratorPedalPosition2;               // SPN 29:   1 Byte
   uint8  u8_VehicleAccelRateLimitStatus;             // SPN 2979: 2 Bits
   uint8  u8_ActMaxAvailableEnginePercTorque;         // SPN 3357: 1 Byte, 0.4% / bit
   // --- scaled parameter ---
   uint16 u16_AcceleratorPedalPosition1_permil;       // SPN 91:   [0 .. 1000]%%
   uint16 u16_RemoteAccelPedalPosition_permil;        // SPN 974:  [0 .. 1000]%%
   uint16 u16_ActMaxAvailEnginePercTorque_permil;     // SPN 3357: [0 .. 1000]%%
}
T_J1939_PGN_EEC2;                                     //PGN Electronic Engine Controller 2

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8  u8_EngineCoolantTemp;                       // SPN 110:  1 Byte, 1°C / bit
   uint8  u8_FuelTemp;                                // SPN 174:  1 Byte, 1°C / bit
   uint16 u16_EngineOilTemp1;                         // SPN 175:  2 Byte, (1/32)°C / bit
   uint16 u16_TurboOilTemp;                           // SPN 176:  2 Byte, (1/32)°C / bit
   uint8  u8_EngineIntercoolerTemp;                   // SPN 52:   1 Byte, 1°C / bit
   uint8  u8_EngIntercoolerThermostatOpn;             // SPN 1134: 1 Byte, 1 Byte, 0.4% / bit
   // --- scaled parameter ---
   sint16 s16_EngineCoolantTemp_degC;                 // SPN 110:  [-40 .. +210]°C
   sint16 s16_FuelTemp_degC;                          // SPN 174:  [-40 .. +210]°C
   sint16 s16_EngineOilTemp1_01degC;                  // SPN 175:  [-2730 .. +17350]0.1°C
   sint16 s16_TurboOilTemp_01degC;                    // SPN 176:  [-2730 .. +17350]0.1°C
   sint16 s16_EngineIntercoolerTemp_degC;             // SPN 52:   [-40 .. +210]°C
   uint16 u16_EngIntercoolerThermostatOpn_permil;     // SPN 1134: [0 .. 1000]%%
}
T_J1939_PGN_ET1;                                      //PGN Engine Temperature 1

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint32 u32_TotalEngineHours;                       // SPN 247: 4 Byte, 0.05=3minutes / bit
   uint32 u32_TotalEngineRevolutions;                 // SPN 249: 4 Byte, 1000r / bit
}
T_J1939_PGN_HOURS;                                    //PGN Hours

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8  u8_EngineFuelDelivPressure;                 // SPN 94:  1 Byte, 4kPa / bit
   uint8  u8_EngineExtCcasePressure;                  // SPN 22:  1 Byte, 50Pa / bit
   uint8  u8_EngineOilLevel;                          // SPN 98:  1 Byte, 0.4% / bit
   uint8  u8_EngineOilPressure;                       // SPN 100: 1 Byte, 4kPa / bit
   uint16 u16_EngineCcasePressure;                    // SPN 101: 2 Byte, 1/128kPa / bit
   uint8  u8_EngineCoolantPressure;                   // SPN 109: 1 Byte, 2kPa / bit
   uint8  u8_EngineCoolantLevel;                      // SPN 111: 1 Byte, 0.4% / bit
   // --- scaled parameter ---
   uint16 u16_EngineFuelDelivPressure_kPa;            // SPN 94:  [0 .. 1000]kPa
   uint16 u16_EngineExtCcasePressure_Pa;              // SPN 22:  [0 .. 12500]Pa
   uint16 u16_EngineOilLevel_permil;                  // SPN 98:  [0 .. 1000]%%
   uint16 u16_EngineOilPressure_kPa;                  // SPN 100: [0 .. 1000]kPa
   sint16 s16_EngineCcasePressure_10Pa;               // SPN 101: [-25000 .. +25199]10Pa (dPa)
   uint16 u16_EngineCoolantPressure_kPa;              // SPN 109: [0 .. 500]kPa
   uint16 u16_EngineCoolantLevel_permil;              // SPN 111: [0 .. 1000]%%
}
T_J1939_PGN_EFLP1;                                    //PGN Engine Fluid Level/Pressure 1

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint16 u16_EngineFuelRate;                         // SPN 183: 2 Byte, (0.05L / h) / bit
   uint16 u16_EngineInstantFuelEconomy;               // SPN 184: 2 Byte, (1000/512 m/L) / bit
   uint16 u16_EngineAverageFuelEconomy;               // SPN 185: 2 Byte, (1000/512 m/L) / bit
   uint8  u8_EngineThrottlePosition;                  // SPN 51:  1 Byte,  0.4% / bit
   // --- scaled parameter ---
   uint16 u16_EngineFuelRate_01Lperh;                 // SPN 183: [0 .. 32127]0.1L/h
   uint16 u16_EngineInstantFuelEconomy_10mperL;       // SPN 184: [0 .. 12550]10m/L
   uint16 u16_EngineAverageFuelEconomy_10mperL;       // SPN 185: [0 .. 12550]10m/L
   uint16 u16_EngineThrottlePosition_permil;          // SPN 51:  [0 .. 1000]%%
}
T_J1939_PGN_LFE;                                      //PGN Fuel Economy (Liquid)

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8  u8_BarometricPressure;                      // SPN 108: 1 Byte, 0.5kPa / bit
   uint16 u16_CabInteriorTemperature;                 // SPN 170: 2 Byte, 2 Byte, (1/32)°C / bit
   uint16 u16_AmbientAirTemperature;                  // SPN 171: 2 Byte, 2 Byte, (1/32)°C / bit
   uint8  u8_AirInletTemperature;                     // SPN 172: 1 Byte, 1°C / bit
   uint16 u16_RoadSurfaceTemperature;                 // SPN 79:  2 Byte, 2 Byte, (1/32)°C / bit
   // --- scaled parameter ---
   uint16 u16_BarometricPressure_100Pa;               // SPN 108: [0 .. 1250]100Pa
   sint16 s16_CabInteriorTemperature_01degC;          // SPN 170: [-2730 .. +17350]0.1°C
   sint16 s16_AmbientAirTemperature_01degC;           // SPN 171: [-2730 .. +17350]0.1°C
   sint16 s16_AirInletTemperature_degC;               // SPN 172: [-40 .. +210]°C
   sint16 s16_RoadSurfaceTemperature_01degC;          // SPN 79:  [-2730 .. +17350]0.1°C
}
T_J1939_PGN_AMB;                                      //PGN Ambient Conditions

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8  u8_TwoSpeedAxleSwitch;                      // SPN 69:   2 Bits
   uint8  u8_CruiseControlPauseSwitch;                // SPN 1633: 2 Bits
   uint16 u16_WheelBasedVehicleSpeed;                 // SPN 84:   2 Byte, ((1/256)km/h) / bit
   uint8  u8_CruiseControlActive;                     // SPN 595:  2 Bits
   uint8  u8_CruiseControlEnableSwitch;               // SPN 596:  2 Bits
   uint8  u8_BrakeSwitch;                             // SPN 597:  2 Bits
   uint8  u8_ClutchSwitch;                            // SPN 598:  2 Bits
   uint8  u8_CruiseControlSetSwitch;                  // SPN 599:  2 Bits
   uint8  u8_CruiseControlCoastSwitch;                // SPN 600:  2 Bits
   uint8  u8_CruiseControlResumeSwitch;               // SPN 601:  2 Bits
   uint8  u8_CruiseControlAccelerateSwitch;           // SPN 602:  2 Bits
   uint8  u8_CruiseControlSetSpeed;                   // SPN 86:   1 Byte, (1km/h) / bit
   uint8  u8_PTOState;                                // SPN 976:  5 Bits
   uint8  u8_CruiseControlStates;                     // SPN 527:  3 Bits
   uint8  u8_IdleIncrementSwitch;                     // SPN 968:  2 Bits
   uint8  u8_IdleDecrementSwitch;                     // SPN 967:  2 Bits
   uint8  u8_EngineTestModeSwitch;                    // SPN 966:  2 Bits
   uint8  u8_EngineShutdownOverrideSwitch;            // SPN 1237: 2 Bits
   // --- scaled parameter ---
   uint16 u16_WheelBasedVehicleSpeed_10mperh;         // SPN 84:   [0 .. 25099]10m/h
}
T_J1939_PGN_CCVS;                                     //PGN Cruise Control/Vehicle Speed

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8  u8_NetBatteryCurrent;                       // SPN 114: 1 Byte, 1A / bit
   uint8  u8_AlternatorCurrent;                       // SPN 115: 1 Byte, 1A / bit
   uint16 u16_AlternatorPotentialVoltage;             // SPN 167: 2 Byte, 0.05V / bit
   uint16 u16_ElectricalPotentialVoltage;             // SPN 168: 2 Byte, 0.05V / bit
   uint16 u16_BatteryPotentialVoltSwitched;           // SPN 158: 2 Byte, 0.05V / bit
   // --- scaled parameter ---
   sint8  s8_NetBatteryCurrent_A;                     // SPN 114: [-125 .. +125]A
   uint16 u16_AlternatorCurrent_A;                    // SPN 115: [0 .. 250]A
   uint16 u16_AlternatorPotentialVoltage_01V;         // SPN 167: [0 .. 32127]100mV
   uint16 u16_ElectricalPotentialVoltage_01V;         // SPN 168: [0 .. 32127]100mV
   uint16 u16_BatteryPotentialVoltSwitched_01V;       // SPN 158: [0 .. 32127]100mV
}
T_J1939_PGN_VEP1;                                     //PGN Vehicle Electrical Power 1

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8  u8_ParticulateTrapInletPressure;            // SPN 81:  1 Byte, 0.5kPa / bit
   uint8  u8_BoostPressure;                           // SPN 102: 1 Byte, 2kPa / bit
   uint8  u8_IntakeManifold1Temperature;              // SPN 105: 1 Byte, 1°C / bit
   uint8  u8_AirInletPressure;                        // SPN 106: 1 Byte, 2kPa / bit
   uint8  u8_AirFilterDifferentialPressure;           // SPN 107: 1 Byte, 0.5kPa / bit
   uint16 u16_ExhaustGasTemperature;                  // SPN 173: 2 Byte, (1/32)°C / bit
   uint8  u8_CoolantFilterDifferentialPressure;       // SPN 112: 1 Byte, 0.5kPa / bit
   // --- scaled parameter ---
   uint16 u16_ParticulateTrapInletPres_100Pa;         // SPN 81:  [0 .. 1250]100Pa
   uint16 u16_BoostPressure_kPa;                      // SPN 102: [0 .. 500]kPa
   sint16 s16_IntakeManifold1Temperature_degC;        // SPN 105: [-40 .. +210]°C
   uint16 u16_AirInletPressure_kPa;                   // SPN 106: [0 .. 500]kPa
   uint16 u16_AirFilterDifferentialPres_100Pa;        // SPN 107: [0 .. 1250]100Pa
   sint16 s16_ExhaustGasTemperature_01degC;           // SPN 173: [-2730 .. +17350]0.1°C
   uint16 u16_CoolantFilterDiffPres_100Pa;            // SPN 112: [0 .. 1250]100Pa
}
T_J1939_PGN_IC1;                                      //PGN Inlet/Exhaust Conditions 1

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8  u8_ClutchPressure;                          // SPN 123:  1 Byte, 16kPa / bit
   uint8  u8_TransmissionOilLevel;                    // SPN 124:  1 Byte, 0.4% / bit
   uint8  u8_TransmFilterDiffPres;                    // SPN 126:  1 Byte, 2kPa / bit
   uint8  u8_TransmissionOilPressue;                  // SPN 127:  1 Byte, 16kPa / bit
   uint16 u16_TransmOilTemperature;                   // SPN 177:  2 Byte, (1/32)°C / bit
   uint8  u8_TransmOilLevelHighLow;                   // SPN 3027: 1 Byte, 0.5L / bit
   uint8  u8_TransmOilLevelCountdownTimer;            // SPN 3028: 4 Bits
   uint8  u8_TransmOilLevelMeasurStatus;              // SPN 3026: 4 Bits
   // --- scaled parameter ---
   uint16 u16_ClutchPressure_kPa;                     // SPN 123:  [0 .. 4000]kPa
   uint16 u16_TransmissionOilLevel_permil;            // SPN 124:  [0 .. 1000]%%
   uint16 u16_TransmFilterDiffPres_kPa;               // SPN 126:  [0 .. 500]kPa
   uint16 u16_TransmissionOilPressue_kPa;             // SPN 127:  [0 .. 4000]kPa
   sint16 s16_TransmOilTemperature_01degC;            // SPN 177:  [-2730 .. +17350]0.1°C
   sint16 s16_TransmOilLevelHighLow_01L;              // SPN 3027: [-625 .. +625]0.1L
}
T_J1939_PGN_TRF1;                                     //PGN Transmission Fluids

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8 u8_CatalystTankLevel;                        // SPN 1761: 1 Byte, 0.4% / bit
   // --- scaled parameter ---
   uint16 u16_CatalystTankLevel_permil;               // SPN 1761: [0 .. 1000]%%
}
T_J1939_PGN_TI1;                                      //PGN Tank Information 1

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8 u8_WaterInFuelIndicator;                     // SPN 97: 2 Bits
}
T_J1939_PGN_WFI;                                      //PGN Water in Fuel Indicator

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8 u8_HydraulicRetarderPressure;                // SPN 119: 1 Byte, 16kPa / bit
   uint8 u8_HydraulicRetarderOilTemp;                 // SPN 120: 1 Byte, 1°C / bit
   // --- scaled parameter ---
   uint16 u16_HydraulicRetarderPres_kPa;              // SPN 119: [0 .. 4000]kPa
   sint16 s16_HydraulicRetarderOilTemp_degC;          // SPN 120: [-40 .. +210]°C
}
T_J1939_PGN_RF;                                       //PGN Retarder Fluids

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8  u8_WasherFluidLevel;                        // SPN 80:  1 Byte, 0.4% / bit
   uint8  u8_FuelLevel;                               // SPN 96:  1 Byte, 0.4% / bit
   uint8  u8_FuelFilterDifferentialPressure;          // SPN 95:  1 Byte, 2kPa / bit
   uint8  u8_EngineOilFilterDiffPressure;             // SPN 99:  1 Byte, 0.5kPa / bit
   uint16 u16_CargoAmbientTemperature;                // SPN 169: 2 Byte, (1/32)°C / bit
   // --- scaled parameter ---
   uint16 u16_WasherFluidLevel_permil;                // SPN 80:  [0 .. 1000]%%
   uint16 u16_FuelLevel_permil;                       // SPN 96:  [0 .. 1000]%%
   uint16 u16_FuelFilterDiffPres_kPa;                 // SPN 95:  [0 .. 500]kPa
   uint16 u16_EngineOilFilterDiffPres_100Pa;          // SPN 99:  [0 .. 1250]100Pa
   sint16 s16_CargoAmbientTemp_01degC;                // SPN 169: [-2730 .. +17350]0.1°C
}
T_J1939_PGN_DD;                                       //PGN Dash Display

typedef struct
{
   T_J1939_PG_ctrl t_Ctrl;                            // control structure
   // --- unscaled parameter ---
   uint8  u8_MinContEngineSpeedLimitReq;              // SPN 1784: Byte 1, 32rpm / bit
   uint8  u8_MaxContEngineSpeedLimitReq;              // SPN 1785: Byte 1, 32rpm / bit
   uint8  u8_MinContEngineTorqueLimitReq;             // SPN 1786: Byte 1, 1% / bit
   uint8  u8_MaxContEngineTorqueLimitReq;             // SPN 1787: Byte 1, 1% / bit
   uint8  u8_MinContRetarderSpeedLimitReq;            // SPN 1788: Byte 1, 32rpm / bit
   uint8  u8_MaxContRetarderSpeedLimitReq;            // SPN 1789: Byte 1, 32rpm / bit
   uint8  u8_MinContRetarderTorqueLimitReq;           // SPN 1790: Byte 1, 1% / bit
   uint8  u8_MaxContRetarderTorqueLimitReq;           // SPN 1791: Byte 1, 1% / bit
   // --- scaled parameter ---
   uint16 u16_MinContEngineSpeedLimitReq_rpm;         // SPN 1784: [0 .. 8000]rpm
   uint16 u16_MaxContEngineSpeedLimitReq_rpm;         // SPN 1785: [0 .. 8000]rpm
   sint8  s8_MinContEngineTorqueLimitReq_perc;        // SPN 1786: [-125 .. +125]%
   sint8  s8_MaxContEngineTorqueLimitReq_perc;        // SPN 1787: [-125 .. +125]%
   uint16 u16_MinContRetarderSpeedLimitReq_rpm;       // SPN 1788: [0 .. 8000]rpm
   uint16 u16_MaxContRetarderSpeedLimitReq_rpm;       // SPN 1789: [0 .. 8000]rpm
   sint8  s8_MinContRetarderTorqueLimitReq_perc;      // SPN 1790: [-125 .. +125]%
   sint8  s8_MaxContRetarderTorqueLimitReq_perc;      // SPN 1791: [-125 .. +125]%
}
T_J1939_PGN_CTL;                                      //PGN Continuous Torque & Speed Limit Request


// -- Global Variables --------------------------------------------------------


// -- Function Prototypes -----------------------------------------------------


// -- Implementation ----------------------------------------------------------


#if defined(__cplusplus)
}                // Make sure we have C-declarations in C++ programs
#endif

#endif                // Avoid multiple/recursive inclusion

/*************************** End of file ****************************/
