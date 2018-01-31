import matplotlib.pyplot as plt
import numpy as np
import threading
import time
from WndHubMonitor import *
from HubPlot import *


RECE_ID=0x583
SEND_ID=0x603
SDO_Read=0x40
SDO_Write=0x23


ParameterList={'BypassVentil':[0x00,0x62,0x1e],
               'WegVentil11Heben':[0x00,0x62,0x14],
               'WegVentil11Sinken':[0x00,0x62,0x15],
               'WegVentil12Heben':[0x00,0x62,0x16],
               'WegVentil12Sinken':[0x00,0x62,0x17],
               'WegVentil21Heben':[0x00,0x62,0x1a],
               'WegVentil21Sinken':[0x00,0x62,0x1b],
               'WegVentil22Heben':[0x00,0x62,0x18],
               'WegVentil22Sinken':[0x00,0x62,0x19],
               'ControlWord':[0x00,0x64,0x00],
               'DefaultPumpeRPM':[0x00,0x64,0x1c],
               'Druck11':[0x00,0x64,0x06],
               'Druck12':[0x00,0x64,0x07],
               'Druck21':[0x00,0x64,0x08],
               'Druck22':[0x00,0x64,0x09],
               'DruckMain':[0x00,0x64,0x05],
               'DruckTemperatur':[0x00,0x64,0x1b],
               'Height11':[0x00,0x64,0x01],
               'Height12':[0x00,0x64,0x02],
               'Height21':[0x00,0x64,0x03],
               'Height22':[0x00,0x64,0x04]
               }


class HubTestShell:
    def __init__(self):
        self.ReceBuffer = []
        self.sendBuffer = []

        self.mWndHubMonitor=WndHubMonitor(ParameterList)
        self.mHubPlot=PlotHub(ParameterList)
        self.task1Shell = threading.Thread(name='Shell_Task1', target=self.Task1_Shell)
        self.taskTerminal = threading.Thread(name='Terminal', target=self.Task_Terminal)

        self.IsOpen=0

        self.Task1IsOpen=0

    def AddCANPort(self, ObjCAN):
        self.objCAN = ObjCAN

    def openTerminal(self):
        self.IsOpen = 1
        self.taskTerminal.start()
        self.task1Shell.start()

    def Start(self):
        result = self.objCAN.open('USBBUS', '250K')
        print result
        if result == "Adapter: connected":
            self.IsOpen = 2
            self.InitHubSystem()

    def InitHubSystem(self):
        a=0
        #Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x00, 0x00, 0x01, 0x01]
        #self.WriteFrame(Send_SDO_COBID, Data)
        #time.sleep(0.02)
        #Data = [SDO_Write] + ParameterList['WegVentil11Heben'] + [0x00, 0x00, 0x02, 0x01]
        #self.WriteFrame(Send_SDO_COBID, Data)
        #time.sleep(0.02)
        #Data = [SDO_Write] + ParameterList['WegVentil12Heben'] + [0x00, 0x00, 0x02, 0x01]
        #self.WriteFrame(Send_SDO_COBID, Data)
        #time.sleep(0.02)
        #Data = [SDO_Write] + ParameterList['WegVentil21Heben'] + [0x00, 0x00, 0x02, 0x01]
        #self.WriteFrame(Send_SDO_COBID, Data)
        #time.sleep(0.02)
        #Data = [SDO_Write] + ParameterList['WegVentil22Heben'] + [0x00, 0x00, 0x02, 0x01]
        #self.WriteFrame(Send_SDO_COBID, Data)
        #time.sleep(0.02)
        #Data = [SDO_Write] + ParameterList['WegVentil11Sinken'] + [0x00, 0x00, 0x02, 0x01]
        #self.WriteFrame(Send_SDO_COBID, Data)
        #time.sleep(0.02)
        #Data = [SDO_Write] + ParameterList['WegVentil11Sinken'] + [0x00, 0x00, 0x02, 0x01]
        #self.WriteFrame(Send_SDO_COBID, Data)
        #time.sleep(0.02)
        #Data = [SDO_Write] + ParameterList['WegVentil12Sinken'] + [0x00, 0x00, 0x02, 0x01]
        #self.WriteFrame(Send_SDO_COBID, Data)
        #time.sleep(0.02)
        #Data = [SDO_Write] + ParameterList['WegVentil21Sinken'] + [0x00, 0x00, 0x02, 0x01]
        #self.WriteFrame(Send_SDO_COBID, Data)
        #time.sleep(0.02)
        #Data = [SDO_Write] + ParameterList['WegVentil22Sinken'] + [0x00, 0x00, 0x02, 0x01]
        #self.WriteFrame(Send_SDO_COBID, Data)
        #time.sleep(0.02)
        #Data = [SDO_Write] + ParameterList['ControlWord'] + [0x04, 0x00, 0x00, 0x00]
        #self.WriteFrame(Send_SDO_COBID, Data)
        #time.sleep(0.02)

    def DeInitHubSystem(self):
        if self.IsOpen == 2:
            Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x00, 0x00, 0x01, 0x00]
            self.WriteFrame(Send_SDO_COBID, Data)
            time.sleep(0.02)
            Data = [SDO_Write] + ParameterList['WegVentil11Heben'] + [0x00, 0x00, 0x02, 0x00]
            self.WriteFrame(Send_SDO_COBID, Data)
            time.sleep(0.02)
            Data = [SDO_Write] + ParameterList['WegVentil12Heben'] + [0x00, 0x00, 0x02, 0x00]
            self.WriteFrame(Send_SDO_COBID, Data)
            time.sleep(0.02)
            Data = [SDO_Write] + ParameterList['WegVentil21Heben'] + [0x00, 0x00, 0x02, 0x00]
            self.WriteFrame(Send_SDO_COBID, Data)
            time.sleep(0.02)
            Data = [SDO_Write] + ParameterList['WegVentil22Heben'] + [0x00, 0x00, 0x02, 0x00]
            self.WriteFrame(Send_SDO_COBID, Data)
            time.sleep(0.02)
            Data = [SDO_Write] + ParameterList['WegVentil11Sinken'] + [0x00, 0x00, 0x02, 0x00]
            self.WriteFrame(Send_SDO_COBID, Data)
            time.sleep(0.02)
            Data = [SDO_Write] + ParameterList['WegVentil11Sinken'] + [0x00, 0x00, 0x02, 0x00]
            self.WriteFrame(Send_SDO_COBID, Data)
            time.sleep(0.02)
            Data = [SDO_Write] + ParameterList['WegVentil12Sinken'] + [0x00, 0x00, 0x02, 0x00]
            self.WriteFrame(Send_SDO_COBID, Data)
            time.sleep(0.02)
            Data = [SDO_Write] + ParameterList['WegVentil21Sinken'] + [0x00, 0x00, 0x02, 0x00]
            self.WriteFrame(Send_SDO_COBID, Data)
            time.sleep(0.02)
            Data = [SDO_Write] + ParameterList['WegVentil22Sinken'] + [0x00, 0x00, 0x02, 0x00]
            self.WriteFrame(Send_SDO_COBID, Data)
            time.sleep(0.02)
            Data = [SDO_Write] + ParameterList['ControlWord'] + [0x00, 0x00, 0x00, 0x00]
            self.WriteFrame(Send_SDO_COBID, Data)
            time.sleep(0.5)

    def Close(self):
        self.mWndHubMonitor.closeWnd()
        #self.DeInitHubSystem()
        self.objCAN.close()
        print "Adapter: disconnected"
        self.IsOpen = 0

    # ===================================================================================================================
    # write the Frame
    def WriteFrame(self, ID, Data):
        self.sendBuffer.append(Data + [ID])

    def sendReq(self):
        Data = []

        sendData = self.mWndHubMonitor.sendReq()
        if len(sendData): Data.extend(sendData)

        sendData = self.mHubPlot.sendReq()
        if len(sendData): Data.extend(sendData)

        if len(self.sendBuffer): Data.extend(self.sendBuffer)
        self.sendBuffer=[]

        return Data

    # ===================================================================================================================
    # get the Frame
    def getMsg(self,ID,DATA,Time):
        self.mWndHubMonitor.getMsg(ID, DATA, Time)
        self.mHubPlot.getMsg(ID, DATA, Time)


    # ===================================================================================================================
    # monitor
    def Task_Terminal(self):
        print "welcome to Laser Scanner Monitor"
        while True:
            cmd = raw_input("cmd: ")
            if cmd == "start":
                print "PeakCAN Start!"
                self.Start()
            elif cmd == "close":
                print "PeakCAN Close!"
                self.Close()
            elif cmd == "quit":
                print "App end! "
                self.Close()
                break
            elif cmd == "Monitor":
                self.Task1IsOpen = 1
            elif cmd == "sinken":
                Data = [SDO_Write] + ParameterList['ControlWord'] + [0x04, 0x02, 0x00, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x01, 0x00, 0x01, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['WegVentil11Sinken'] + [0x58, 0x1b, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil12Sinken'] + [0x58, 0x1b, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil21Sinken'] + [0x58, 0x1b, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil22Sinken'] + [0x58, 0x1b, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(15)
                Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x00, 0x00, 0x01, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['ControlWord'] + [0x00, 0x00, 0x00, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x00, 0x00, 0x01, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil11Sinken'] + [0x88, 0x13, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil12Sinken'] + [0x88, 0x13, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil21Sinken'] + [0x88, 0x13, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil22Sinken'] + [0x88, 0x13, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)

            elif cmd == "h11":
                Data = [SDO_Write] + ParameterList['ControlWord'] + [0x04, 0x01, 0x00, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x01, 0x00, 0x01, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['WegVentil11Heben'] + [0xd0, 0x0a, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(10)
                Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x00, 0x00, 0x01, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['ControlWord'] + [0x00, 0x00, 0x00, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)


            elif cmd == "h12":
                Data = [SDO_Write] + ParameterList['ControlWord'] + [0x04, 0x01, 0x00, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x01, 0x00, 0x01, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['WegVentil12Heben'] + [0xd0, 0x0a, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(5)
                Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x00, 0x00, 0x01, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['ControlWord'] + [0x00, 0x00, 0x00, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)


            elif cmd == "h21":
                Data = [SDO_Write] + ParameterList['ControlWord'] + [0x04, 0x01, 0x00, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x01, 0x00, 0x01, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['WegVentil21Heben'] + [0xd0, 0x07, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(5)
                Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x00, 0x00, 0x01, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['ControlWord'] + [0x00, 0x00, 0x00, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)

            elif cmd == "h22":
                Data = [SDO_Write] + ParameterList['ControlWord'] + [0x04, 0x01, 0x00, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x01, 0x00, 0x01, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['WegVentil22Heben'] + [0x88, 0x09, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(5)
                Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x00, 0x00, 0x01, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['ControlWord'] + [0x00, 0x00, 0x00, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)

            elif cmd == "setting":
                Data = [SDO_Write] + ParameterList['ControlWord'] + [0x04, 0x01, 0x00, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x01, 0x00, 0x01, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['WegVentil11Heben'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil12Heben'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil21Heben'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil22Heben'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil11Sinken'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil12Sinken'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil21Sinken'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil22Sinken'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil11Heben'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil12Heben'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil21Heben'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil22Heben'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil11Sinken'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil12Sinken'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil21Sinken'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil22Sinken'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)



            elif cmd == "stop":
                Data = [SDO_Write] + ParameterList['WegVentil11Heben'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil12Heben'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil21Heben'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil22Heben'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil11Sinken'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil12Sinken'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil21Sinken'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil22Sinken'] + [0x00, 0x00, 0x02, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil11Heben'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil12Heben'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil21Heben'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil22Heben'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil11Sinken'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil12Sinken'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil21Sinken'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.01)
                Data = [SDO_Write] + ParameterList['WegVentil22Sinken'] + [0x00, 0x00, 0x02, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x00, 0x00, 0x01, 0x01]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.3)
                Data = [SDO_Write] + ParameterList['ControlWord'] + [0x00, 0x00, 0x00, 0x00]
                self.WriteFrame(Send_SDO_COBID, Data)


            elif cmd.find("setHeben")==0:
                str=cmd.split()
                if str[1].isdigit():
                    Data = [SDO_Write] + ParameterList['ControlWord'] + [0x04, 0x01, 0x00, 0x00]
                    self.WriteFrame(Send_SDO_COBID, Data)
                    time.sleep(0.3)
                    #Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x01, 0x00, 0x01, 0x01]
                    #self.WriteFrame(Send_SDO_COBID, Data)
                    #time.sleep(0.3)
                    self.mHubPlot.SetHeight(int(str[1]),1)
                    time.sleep(25)
                    #Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x00, 0x00, 0x01, 0x01]
                    #self.WriteFrame(Send_SDO_COBID, Data)
                    #time.sleep(0.3)
                    Data = [SDO_Write] + ParameterList['ControlWord'] + [0x00, 0x00, 0x00, 0x00]
                    self.WriteFrame(Send_SDO_COBID, Data)

            elif cmd.find("setSinken")==0:
                str=cmd.split()
                if str[1].isdigit():
                    Data = [SDO_Write] + ParameterList['ControlWord'] + [0x04, 0x02, 0x00, 0x00]
                    self.WriteFrame(Send_SDO_COBID, Data)
                    time.sleep(0.3)
                    #Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x01, 0x00, 0x01, 0x01]
                    #self.WriteFrame(Send_SDO_COBID, Data)
                    #time.sleep(0.3)
                    self.mHubPlot.SetHeight(int(str[1]),2)
                    time.sleep(20)
                    #Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x00, 0x00, 0x01, 0x01]
                    #self.WriteFrame(Send_SDO_COBID, Data)
                    #time.sleep(0.3)
                    Data = [SDO_Write] + ParameterList['ControlWord'] + [0x00, 0x00, 0x00, 0x00]
                    self.WriteFrame(Send_SDO_COBID, Data)
            elif cmd=="Training":
                mal=0
                while TRUE:
                    Data = [SDO_Write] + ParameterList['ControlWord'] + [0x04, 0x01, 0x00, 0x00]
                    self.WriteFrame(Send_SDO_COBID, Data)
                    time.sleep(0.3)
                    Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x01, 0x00, 0x01, 0x01]
                    self.WriteFrame(Send_SDO_COBID, Data)
                    time.sleep(0.3)
                    self.mHubPlot.SetHeight(80,1)
                    time.sleep(20)
                    Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x00, 0x00, 0x01, 0x01]
                    self.WriteFrame(Send_SDO_COBID, Data)
                    time.sleep(0.3)
                    Data = [SDO_Write] + ParameterList['ControlWord'] + [0x00, 0x00, 0x00, 0x00]
                    self.WriteFrame(Send_SDO_COBID, Data)
                    time.sleep(5)
                    Data = [SDO_Write] + ParameterList['ControlWord'] + [0x04, 0x02, 0x00, 0x00]
                    self.WriteFrame(Send_SDO_COBID, Data)
                    time.sleep(0.3)
                    Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x01, 0x00, 0x01, 0x01]
                    self.WriteFrame(Send_SDO_COBID, Data)
                    time.sleep(0.3)
                    self.mHubPlot.SetHeight(0,2)
                    time.sleep(20)
                    Data = [SDO_Write] + ParameterList['BypassVentil'] + [0x00, 0x00, 0x01, 0x01]
                    self.WriteFrame(Send_SDO_COBID, Data)
                    time.sleep(0.3)
                    Data = [SDO_Write] + ParameterList['ControlWord'] + [0x00, 0x00, 0x00, 0x00]
                    self.WriteFrame(Send_SDO_COBID, Data)
                    time.sleep(5)
                    mal+=1
                    if mal ==50: break


            elif cmd == "startPlot":
                self.mHubPlot.StartHubPlot()

            elif cmd == "closePlot":
                self.mHubPlot.CloseHubPlot()

            elif cmd == "clearPlot":
                self.mHubPlot.clearBuffer()

            elif cmd == "plot":
                self.mHubPlot.plot()


    def Task1_Shell(self):
        while True:
            if self.Task1IsOpen==1:
                self.mWndHubMonitor.openWnd()
                self.Task1IsOpen = 0
            if self.IsOpen==0: break






