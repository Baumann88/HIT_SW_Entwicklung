import sys
sys.path.append("..")
from PyLib.CANopenPortMon import *
from PlotMES import *
from time import *

if __name__ == '__main__':
    PlotObj = PlotMES()
    CANport=CANopenPort()
    PlotObj.AddCANPort(CANport)
    CANport.addInterface(PlotObj)
    print "welcome to MES Plot"
    while True:
        cmd=raw_input("cmd: ")
        if cmd=="start":
            print "PeakCAN Start!"
            PlotObj.Start()
        elif cmd=="close":
            print "PeakCAN Close!"
            PlotObj.Close()
        elif cmd=="quit":
            print "App end! "
            PlotObj.Close()
            break
        elif cmd.find("setAngle")==0:
            str=cmd.split()
            PlotObj.ChangeTestAngle(int(str[1]),int(str[2]))
        elif cmd=="plot":
            print "begin plot for drive module11"
            PlotObj.plot()
        elif cmd=="clear":
            print "buffer is clear"
            PlotObj.clearBuffer()

