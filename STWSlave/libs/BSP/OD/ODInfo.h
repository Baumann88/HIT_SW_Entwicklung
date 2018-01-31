#ifndef _ODINFO_H
#define _ODINFO_H


/*====================================================================
Remote Node Configuration
====================================================================*/
#define NrOfDriveSys                 1
#define NrOfMotorInverter            1
#define NrOfIOPortGroup              1
#define NrOfRemoteControl            1
#define NrOfHubSys                   1
#define NrOfSafety                   1
#define NrOfAutoDrive                1

/*====================================================================
Parameter of the memory for object dictionary definition
====================================================================*/
#define ODMemLength      (NrEntryDevPara+NrEntryDriveModule*NrOfDriveSys+NrEntryInverter*NrOfMotorInverter+NrEntryIOPort*NrOfIOPortGroup+NrEntryRemoteControl*NrOfRemoteControl+NrEntryHubSystem*NrOfHubSys+NrEntrySafety*NrOfSafety+NrEntryAutoDrive*NrOfAutoDrive)
#define ODMemMapListLength      (1+NrOfDriveSys+NrOfMotorInverter+NrOfIOPortGroup+NrOfRemoteControl+NrOfHubSys+NrOfSafety+NrOfAutoDrive)


#endif
