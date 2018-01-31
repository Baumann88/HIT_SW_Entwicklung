#ifndef _HUBSYSTEMINTERFACE_H
#define _HUBSYSTEMINTERFACE_H
//=================================================================================================
//Function definition
//=================================================================================================
//=================================================================================================
/*!
    Function: generate the Interface
    output: None
*/
//=================================================================================================
void InitInterfaceHubSys(void);
//=================================================================================================
/*!
    Function: Awake the Task from sleep state, the time interval of awake is activated by toggle bit
    output: 1: awake the hub system/ 0: not to awake the hub system
*/
//=================================================================================================
void HubSysAwake(void);

#endif
