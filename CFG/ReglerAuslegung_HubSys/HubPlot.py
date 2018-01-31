import matplotlib.pyplot as plt
import numpy as np
import thread
import time

RECE_ID11=0x183
RECE_ID12=0x193
RECE_ID21=0x203
RECE_ID22=0x213
Send_SDO_COBID=0x603
SDO_Write=0x23

class PlotHub:
    def __init__(self,ParaList):
        self.ParaList = ParaList
        self.ReceBuffer11 = []
        self.ReceBuffer12 = []
        self.ReceBuffer21 = []
        self.ReceBuffer22 = []
        self.sendBuffer = []

        self.IsOpen=0
        self.IsPlot=0



    def StartHubPlot(self):
        self.IsOpen = 1
        self.clearBuffer()

    def CloseHubPlot(self):
        self.IsOpen = 0

    # ===================================================================================================================
    # write the Frame
    def WriteFrame(self, ID, Data):
        self.sendBuffer.append(Data + [ID])

    def sendReq(self):
        tmp = self.sendBuffer
        self.sendBuffer = []
        return tmp

    # ===================================================================================================================
    # get the Frame
    def getMsg(self,ID,DATA,Time):
        if self.IsPlot==0:
            self.DataLoggen(ID, DATA, Time)


    def DataLoggen(self,ID,DATA,Time):
        if ID == RECE_ID11:
            self.ReceBuffer11.append([Time,DATA])
        if ID == RECE_ID12:
            self.ReceBuffer12.append([Time, DATA])
        if ID == RECE_ID21:
            self.ReceBuffer21.append([Time, DATA])
        if ID == RECE_ID22:
            self.ReceBuffer22.append([Time, DATA])

    def clearBuffer(self):
        self.ReceBuffer11 = []
        self.ReceBuffer12 = []
        self.ReceBuffer21 = []
        self.ReceBuffer22 = []

    def SetHeight(self,Height,heben):
        Data1 = Height & 0xff
        Data2 = (Height >> 8) & 0xff
        if heben == 1:
            Data = [SDO_Write] + self.ParaList['ControlWord'] + [0x04, 0x01, Data1, Data2]
        elif heben == 2:
            Data = [SDO_Write] + self.ParaList['ControlWord'] + [0x04, 0x02, Data1, Data2]
        else:
            Data = [SDO_Write] + self.ParaList['ControlWord'] + [0x04, 0x00, Data1, Data2]
        self.WriteFrame(Send_SDO_COBID, Data)


    def plot(self):
        self.IsPlot=1
        Height11 = []
        Druck11 = []
        Height12 = []
        Druck12 = []
        Height21 = []
        Druck21 = []
        Height22 = []
        Druck22 = []
        TimeStamp11 = []
        TimeStamp12 = []
        TimeStamp21 = []
        TimeStamp22 = []

        DataLen = len(self.ReceBuffer11)
        startTime=self.ReceBuffer11[0][0]
        for iRow in range(DataLen):
            Msg=self.ReceBuffer11[iRow][1]
            tmp=Msg[0]+(Msg[1]<<8)+(Msg[2]<<16)+(Msg[3]<<24)
            if tmp>2147483647 : tmp-=4294967296
            Height11.append(float(tmp))
            tmp = Msg[4] + (Msg[5] << 8) + (Msg[6] << 16) + (Msg[7] << 24)
            if tmp > 2147483647: tmp -= 4294967296
            Druck11.append(float(tmp)*0.001)
            TimeStamp11.append(round(0.001*(self.ReceBuffer11[iRow][0]-startTime)))

        DataLen = len(self.ReceBuffer12)
        startTime = self.ReceBuffer12[0][0]
        for iRow in range(DataLen):
            Msg = self.ReceBuffer12[iRow][1]
            tmp = Msg[0] + (Msg[1] << 8) + (Msg[2] << 16) + (Msg[3] << 24)
            if tmp > 2147483647: tmp -= 4294967296
            Height12.append(float(tmp))
            tmp = Msg[4] + (Msg[5] << 8) + (Msg[6] << 16) + (Msg[7] << 24)
            if tmp > 2147483647: tmp -= 4294967296
            Druck12.append(float(tmp) * 0.001)
            TimeStamp12.append(round(0.001 * (self.ReceBuffer12[iRow][0] - startTime)))

        DataLen = len(self.ReceBuffer21)
        startTime = self.ReceBuffer21[0][0]
        for iRow in range(DataLen):
            Msg = self.ReceBuffer21[iRow][1]
            tmp = Msg[0] + (Msg[1] << 8) + (Msg[2] << 16) + (Msg[3] << 24)
            if tmp > 2147483647: tmp -= 4294967296
            Height21.append(float(tmp))
            tmp = Msg[4] + (Msg[5] << 8) + (Msg[6] << 16) + (Msg[7] << 24)
            if tmp > 2147483647: tmp -= 4294967296
            Druck21.append(float(tmp) * 0.001)
            TimeStamp21.append(round(0.001 * (self.ReceBuffer21[iRow][0] - startTime)))

        DataLen = len(self.ReceBuffer22)
        startTime = self.ReceBuffer22[0][0]
        for iRow in range(DataLen):
            Msg = self.ReceBuffer22[iRow][1]
            tmp = Msg[0] + (Msg[1] << 8) + (Msg[2] << 16) + (Msg[3] << 24)
            if tmp > 2147483647: tmp -= 4294967296
            Height22.append(float(tmp))
            tmp = Msg[4] + (Msg[5] << 8) + (Msg[6] << 16) + (Msg[7] << 24)
            if tmp > 2147483647: tmp -= 4294967296
            Druck22.append(float(tmp) * 0.001)
            TimeStamp22.append(round(0.001 * (self.ReceBuffer22[iRow][0] - startTime)))

        xdataArray1 = np.array(TimeStamp11)
        xdataArray2 = np.array(TimeStamp12)
        xdataArray3 = np.array(TimeStamp21)
        xdataArray4 = np.array(TimeStamp22)

        ydataArray1 = np.array(Height11)
        ydataArray2 = np.array(Height12)
        ydataArray3 = np.array(Height21)
        ydataArray4 = np.array(Height22)

        fig1 = plt.figure(1)
        plt.title("Height")
        plt.xlabel("zeit in ms")
        plt.ylabel("Height in mm")
        plt.ylim((0,200))
        line11, = plt.plot(xdataArray1, ydataArray1, 'b')
        line12, = plt.plot(xdataArray2, ydataArray2, 'r')
        line21, = plt.plot(xdataArray3, ydataArray3, 'g')
        line22, = plt.plot(xdataArray4, ydataArray4, 'm')
        plt.legend([line11, line12, line21, line22], ['Height 11', 'Height 12', 'Height 21', 'Height 22'])
        plt.grid()

        ydataArray1 = np.array(Druck11)
        ydataArray2 = np.array(Druck12)
        ydataArray3 = np.array(Druck21)
        ydataArray4 = np.array(Druck22)
        fig2 = plt.figure(2)
        plt.title("Druck")
        plt.xlabel("zeit in ms")
        plt.ylabel("druck in bar")
        plt.ylim((-10,200))
        line11, = plt.plot(xdataArray1, ydataArray1, 'b')
        line12, = plt.plot(xdataArray2, ydataArray2, 'r')
        line21, = plt.plot(xdataArray3, ydataArray3, 'g')
        line22, = plt.plot(xdataArray4, ydataArray4, 'm')
        plt.legend([line11, line12, line21, line22], ['druck 11', 'druck 12', 'druck 21', 'druck 22'])
        plt.grid()

        plt.show()
        self.IsPlot=0

