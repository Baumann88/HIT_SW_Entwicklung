#ifndef _MESConfig_H
#define _MESConfig_H

/*====================================================================
Master or Slave CPU definition
====================================================================*/
#define SlaveCPU                            1

/*====================================================================
Parameter definition
====================================================================*/
#define pi                                   3.1416
#define Rad2Grad                             (180.0/pi)
#define Grad2Rad                             (pi/180.0)

#define L                                    2.63  //length of the MES (distance between two longitudinal axis)
#define B                                    1.03  //width of the MES (distance between two lateral axis)


/*====================================================================
ID of the Remote Node
====================================================================*/
#ifdef MasterCPU
#define IDRemoteControl                      0x04
#define BusChRemoteControl                   0
#define IDInverter111                        0x09
#define BusChInverter111                     1
#define IDInverter112                        0x0a
#define BusChInverter112                     1
#define IDInverter121                        0x0b
#define BusChInverter121                     1
#define IDInverter122                        0x0c
#define BusChInverter122                     1
#define IDInverter211                        0x10
#define BusChInverter211                     1
#define IDInverter212                        0x0f
#define BusChInverter212                     1
#define IDInverter221                        0x0e
#define BusChInverter221                     1
#define IDInverter222                        0x0d
#define BusChInverter222                     1
#define IDCamera1                            0x05
#define BusChCamera1                         3
#define IDCamera2                            0x06
#define BusChCamera2                         3
#endif // MasterCPU

#ifdef SlaveCPU
#define IDInverterHydraulic                  0x08
#define BusChInverterHydraulic               1
#endif // SlaveCPU

/*====================================================================
CMD of NMT CANopen
====================================================================*/
#define NODE_START                           0x01
#define NODE_STOP                            0x02
#define NODE_PREOP                           0x80
#define NODE_RESET_APPL                      0x81
#define NODE_RESET_COM                       0x82

/*====================================================================
CANopen NMT Status definition
====================================================================*/
#define NMTStatusNOT_ACTIVE                  0x00
#define NMTStatusNOT_STARTED                 0x01
#define NMTStatusALIVE                       0x02
#define NMTStatusDEAD                        0x03

/*====================================================================
CANopen Node Status definition
====================================================================*/
#define NodeStatusUNKNOWN                    0x00
#define NodeStatusDISCONNECTING              0x01
#define NodeStatusCONNECTING                 0x02
#define NodeStatusPREPARING                  0x03
#define NodeStatusPREPARED                   0x04
#define NodeStatusOPERATIONAL                0x05
#define NodeStatusPRE_OPERATIONAL            0x7f

#endif
