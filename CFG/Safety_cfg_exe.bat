@echo off 
C:

cd C:\Users\wsun\Dropbox\HIT_Workspace\CFG\SafetyConceptMaster
start python GenerateSafteyFahrSys.py
start python GenerateSafteyNormal.py
start python GenerateSafteyPLC.py
 
cd C:\Users\wsun\Dropbox\HIT_Workspace\CFG\SafetyConceptSlave
start python GenerateSafteyHubSys.py
start python GenerateSafteyNormal.py
start python GenerateSafteyPLC.py

cd C:\Users\wsun\Dropbox\HIT_Workspace\CFG\ErrorTestGenerate
start python ErrorTextGenerate.py
 
exit 