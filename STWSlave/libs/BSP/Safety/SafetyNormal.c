#include <SafetyData.h>
#include <Safety.h>

//====================================================================
/*!
Function: HandleSafetyNormal
Output: None
*/
//====================================================================
void HandleSafetyNormal(void){
    boolean m1,m2;
    //1. Layer
    m1=SafteyErrorAchse11lastet|SafteyErrorAchse12lastet|SafteyErrorAchse21lastet|SafteyErrorAchse22lastet;
    m2=SafteyErrorPumpeOffline|SafteyErrorVentil|SafteyErrorPumpeDrehzahlOut|SafteyErrorMainDruckHigh|SafteyErrorHubTemperaturHigh|SafteyErrorPumpeUmrichter;
    //Output
    if(m1){
         *inputSafetySafetySysControlWord|=KeySafetySetHubsystemOnlySinken;
    }
    else {
        *inputSafetySafetySysControlWord&=~KeySafetySetHubsystemOnlySinken;
    }
    if(m2){
         *inputSafetySafetySysControlWord|=KeySafetySetHubsystemStop;
    }
    else {
        *inputSafetySafetySysControlWord&=~KeySafetySetHubsystemStop;
    }
}

