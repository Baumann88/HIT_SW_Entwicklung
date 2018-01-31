import sys
sys.path.append("..")
from PyLib.CANopenPortMon import *
from LaserScannerTest import *
from time import *

if __name__ == '__main__':
    LSObj = LaserScannerTest()
    CANport=CANopenPort()
    LSObj.AddCANPort(CANport)
    CANport.addInterface(LSObj)
    LSObj.openMonitor()


