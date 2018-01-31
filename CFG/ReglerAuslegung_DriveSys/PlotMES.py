import matplotlib.pyplot as plt
import numpy as np
import thread
import time

RECE_ID11=0x182
RECE_ID12=0x192
RECE_ID21=0x202
RECE_ID22=0x212
SEND_ID=0x602

class PlotMES:
    def __init__(self):
        self.ReceBuffer11=[]
        self.ReceBuffer12 = []
        self.ReceBuffer21 = []
        self.ReceBuffer22 = []
        self.sendBuffer = []

        self.IsOpen=0
        self.IsPlot=0

    def AddCANPort(self, ObjCAN):
        self.objCAN = ObjCAN

    def Start(self):
        result = self.objCAN.open('USBBUS', '250K')
        print result
        if result == "Adapter: connected":
            self.IsOpen = 1
            self.clearBuffer()

    def Close(self):
        self.objCAN.close()
        print "Adapter: disconnected"
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

    def ChangeTestAngle(self,DriveModule,Angle):
        if DriveModule==11:
            self.WriteFrame(SEND_ID, [0x23,0x00,0x60,0x22,Angle&0xff,(Angle>>8)&0xff,(Angle >> 16) & 0xff,(Angle >> 24) & 0xff])
        elif DriveModule == 12:
            self.WriteFrame(SEND_ID,[0x23, 0x00, 0x60, 0x23, Angle & 0xff, (Angle >> 8) & 0xff, (Angle >> 16) & 0xff,(Angle >> 24) & 0xff])
        elif DriveModule == 21:
            self.WriteFrame(SEND_ID,[0x23, 0x00, 0x60, 0x24, Angle & 0xff, (Angle >> 8) & 0xff, (Angle >> 16) & 0xff,(Angle >> 24) & 0xff])
        elif DriveModule == 22:
            self.WriteFrame(SEND_ID,[0x23, 0x00, 0x60, 0x25, Angle & 0xff, (Angle >> 8) & 0xff, (Angle >> 16) & 0xff,(Angle >> 24) & 0xff])


    def plot(self):
        self.IsPlot=1
        Angle11 = []
        Omega11 = []
        Angle12 = []
        Omega12 = []
        Angle21 = []
        Omega21 = []
        Angle22 = []
        Omega22 = []
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
            Angle11.append(float(tmp))
            tmp = Msg[4] + (Msg[5] << 8) + (Msg[6] << 16) + (Msg[7] << 24)
            if tmp > 2147483647: tmp -= 4294967296
            Omega11.append(float(tmp)*0.001)
            TimeStamp11.append(round(0.001*(self.ReceBuffer11[iRow][0]-startTime)))

        DataLen = len(self.ReceBuffer12)
        startTime = self.ReceBuffer12[0][0]
        for iRow in range(DataLen):
            Msg = self.ReceBuffer12[iRow][1]
            tmp = Msg[0] + (Msg[1] << 8) + (Msg[2] << 16) + (Msg[3] << 24)
            if tmp > 2147483647: tmp -= 4294967296
            Angle12.append(float(tmp))
            tmp = Msg[4] + (Msg[5] << 8) + (Msg[6] << 16) + (Msg[7] << 24)
            if tmp > 2147483647: tmp -= 4294967296
            Omega12.append(float(tmp) * 0.001)
            TimeStamp12.append(round(0.001 * (self.ReceBuffer12[iRow][0] - startTime)))

        DataLen = len(self.ReceBuffer21)
        startTime = self.ReceBuffer21[0][0]
        for iRow in range(DataLen):
            Msg = self.ReceBuffer21[iRow][1]
            tmp = Msg[0] + (Msg[1] << 8) + (Msg[2] << 16) + (Msg[3] << 24)
            if tmp > 2147483647: tmp -= 4294967296
            Angle21.append(float(tmp))
            tmp = Msg[4] + (Msg[5] << 8) + (Msg[6] << 16) + (Msg[7] << 24)
            if tmp > 2147483647: tmp -= 4294967296
            Omega21.append(float(tmp) * 0.001)
            TimeStamp21.append(round(0.001 * (self.ReceBuffer21[iRow][0] - startTime)))

        DataLen = len(self.ReceBuffer22)
        startTime = self.ReceBuffer22[0][0]
        for iRow in range(DataLen):
            Msg = self.ReceBuffer22[iRow][1]
            tmp = Msg[0] + (Msg[1] << 8) + (Msg[2] << 16) + (Msg[3] << 24)
            if tmp > 2147483647: tmp -= 4294967296
            Angle22.append(float(tmp))
            tmp = Msg[4] + (Msg[5] << 8) + (Msg[6] << 16) + (Msg[7] << 24)
            if tmp > 2147483647: tmp -= 4294967296
            Omega22.append(float(tmp) * 0.001)
            TimeStamp22.append(round(0.001 * (self.ReceBuffer22[iRow][0] - startTime)))

        xdataArray1 = np.array(TimeStamp11)
        xdataArray2 = np.array(TimeStamp12)
        xdataArray3 = np.array(TimeStamp21)
        xdataArray4 = np.array(TimeStamp22)

        ydataArray1 = np.array(Angle11)
        ydataArray2 = np.array(Angle12)
        ydataArray3 = np.array(Angle21)
        ydataArray4 = np.array(Angle22)

        fig1 = plt.figure(1)
        plt.title("Angle")
        plt.xlabel("zeit in ms")
        plt.ylabel("angle in Grad")
        plt.ylim((-100,100))
        line11, = plt.plot(xdataArray1, ydataArray1, 'b')
        line12, = plt.plot(xdataArray2, ydataArray2, 'r')
        line21, = plt.plot(xdataArray3, ydataArray3, 'g')
        line22, = plt.plot(xdataArray4, ydataArray4, 'm')
        plt.legend([line11, line12, line21, line22], ['Angle 11', 'Angle 12', 'Angle 21', 'Angle 22'])
        plt.grid()

        ydataArray1 = np.array(Omega11)
        ydataArray2 = np.array(Omega12)
        ydataArray3 = np.array(Omega21)
        ydataArray4 = np.array(Omega22)
        fig2 = plt.figure(2)
        plt.title("Omega")
        plt.xlabel("zeit in ms")
        plt.ylabel("omega in rad/s")
        plt.ylim((-1.0,1.0))
        line11, = plt.plot(xdataArray1, ydataArray1, 'b')
        line12, = plt.plot(xdataArray2, ydataArray2, 'r')
        line21, = plt.plot(xdataArray3, ydataArray3, 'g')
        line22, = plt.plot(xdataArray4, ydataArray4, 'm')
        plt.legend([line11, line12, line21, line22], ['omega 11', 'omega 12', 'omega 21', 'omega 22'])
        plt.grid()

        plt.show()
        self.IsPlot=0

