import sys
sys.path.append("..")
from PyLib.CANopenPortMon import *
from HubTest import *
from time import *

if __name__ == '__main__':
    ShellObj = HubTestShell()
    CANport=CANopenPort()
    ShellObj.AddCANPort(CANport)
    CANport.addInterface(ShellObj)
    print "welcome to MES Hub System test"
    ShellObj.openTerminal()


