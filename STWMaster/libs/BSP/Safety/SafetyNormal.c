#include <SafetyData.h>
#include <Safety.h>

//====================================================================
/*!
Function: HandleSafetyNormal
Output: None
*/
//====================================================================
void HandleSafetyNormal(void){
    boolean m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12,m13,m14,m15,m16;
    //1. Layer
    m1=SafetyErrorNotAusEckVorne|SafetyErrorNotAusEckHinten|SafetyErrorNotAusFunke|SafetyErrorDriveModule11AngleOut|SafetyErrorDriveModule12AngleOut|SafetyErrorDriveModule21AngleOut|SafetyErrorDriveModule22AngleOut|SafetyErrorLS1Abschalten|SafetyErrorLS2Abschalten;
    m2=SafetyErrorNotAusSchutzAus|SafetyErrorCANBus;
    m3=SafetyErrorNotAusEckVorne|SafetyErrorNotAusEckHinten|SafetyErrorNotAusFunke|SafetyErrorDriveModule11AngleOut|SafetyErrorDriveModule12AngleOut|SafetyErrorDriveModule21AngleOut|SafetyErrorDriveModule22AngleOut|SafetyErrorLS1Abschalten|SafetyErrorLS2Abschalten|SafetyErrorHubSystemOnlySinken|SafetyErrorMotorUmrichterOffline|SafetyErrorKameraOffline|SafetyErrorRCOffline;
    m4=SafetyErrorLS1Quit;
    m5=SafetyErrorLS2Quit;
    m6=SafetyErrorLS1Warn1;
    m7=SafetyErrorLS1Warn2;
    m8=SafetyErrorLS2Warn1;
    m9=SafetyErrorLS2Warn2;
    m10=SafetyErrorLS1Abschalten;
    m11=SafetyErrorLS2Abschalten;
    m12=SafetyErrorNotAusEckVorne|SafetyErrorNotAusEckHinten|SafetyErrorNotAusFunke;
    m13=SafetyErrorLadenZustand;
    m14=SafetyErrorMotorUmrichterOffline|SafetyErrorKameraOffline|SafetyErrorRCOffline;
    m15=SafetyErrorHubSystemStopReq;
    m16=SafetyErrorMESTimeOut;
    //Output
    if(m1){
         *outputSafetyIOMotorSafetyStop&=0xffff0000;
    }
    else {
        *outputSafetyIOMotorSafetyStop&=0xffff0000;
        *outputSafetyIOMotorSafetyStop+=0x00000001;
    }
    if(m2){
         *outputSafetyIOLeistungSchutz1&=0xffff0000;
        *outputSafetyIOLeistungSchutz2&=0xffff0000;
    }
    else {
        *outputSafetyIOLeistungSchutz1&=0xffff0000;
        *outputSafetyIOLeistungSchutz1+=0x00000001;
        *outputSafetyIOLeistungSchutz2&=0xffff0000;
        *outputSafetyIOLeistungSchutz2+=0x00000001;
    }
    if(m3){
         *inputSafetySafetySysControlWord|=KeySafetySetRCDriveSysStop;
    }
    else {
        *inputSafetySafetySysControlWord&=~KeySafetySetRCDriveSysStop;
    }
    if(m4){
         *outputSafetyIOQuittierungLS1&=0xffff0000;
    }
    else {
        *outputSafetyIOQuittierungLS1&=0xffff0000;
        *outputSafetyIOQuittierungLS1+=0x00000001;
    }
    if(m5){
         *outputSafetyIOQuittierungLS2&=0xffff0000;
    }
    else {
        *outputSafetyIOQuittierungLS2&=0xffff0000;
        *outputSafetyIOQuittierungLS2+=0x00000001;
    }
    if(m6){
         *inputSafetySafetySysControlWord|=KeySafetySetRCLaserscanner1Warn;
    }
    else {
        *inputSafetySafetySysControlWord&=~KeySafetySetRCLaserscanner1Warn;
    }
    if(m7){
         *inputSafetySafetySysControlWord|=KeySafetySetRCLaserscanner1Slow;
    }
    else {
        *inputSafetySafetySysControlWord&=~KeySafetySetRCLaserscanner1Slow;
    }
    if(m8){
         *inputSafetySafetySysControlWord|=KeySafetySetRCLaserscanner2Warn;
    }
    else {
        *inputSafetySafetySysControlWord&=~KeySafetySetRCLaserscanner2Warn;
    }
    if(m9){
         *inputSafetySafetySysControlWord|=KeySafetySetRCLaserscanner2Slow;
    }
    else {
        *inputSafetySafetySysControlWord&=~KeySafetySetRCLaserscanner2Slow;
    }
    if(m10){
         *inputSafetySafetySysControlWord|=KeySafetySetRCLaserscanner1Stop;
    }
    else {
        *inputSafetySafetySysControlWord&=~KeySafetySetRCLaserscanner1Stop;
    }
    if(m11){
         *inputSafetySafetySysControlWord|=KeySafetySetRCLaserscanner2Stop;
    }
    else {
        *inputSafetySafetySysControlWord&=~KeySafetySetRCLaserscanner2Stop;
    }
    if(m12){
         *inputSafetySafetySysControlWord|=KeySafetySetRCNotAusStatus;
    }
    else {
        *inputSafetySafetySysControlWord&=~KeySafetySetRCNotAusStatus;
    }
    if(m13){
         *inputSafetySafetySysControlWord|=KeySafetySetRCLadeStatus;
    }
    else {
        *inputSafetySafetySysControlWord&=~KeySafetySetRCLadeStatus;
    }
    if(m14){
         *inputSafetySafetySysControlWord|=KeySafetySetRCAutoDriveStop;
    }
    else {
        *inputSafetySafetySysControlWord&=~KeySafetySetRCAutoDriveStop;
    }
    if(m15){
         *inputSafetySafetySysControlWord|=KeySafetySetRCHubSysStop;
    }
    else {
        *inputSafetySafetySysControlWord&=~KeySafetySetRCHubSysStop;
    }
    if(m16){
         *outputSafetyIO15minAus&=0xffff0000;
        *outputSafetyIO15minAus+=0x00000001;
    }
    else {
        *outputSafetyIO15minAus&=0xffff0000;
    }
}

